<?php
/**
 * @file
 * WMD's session handler.
 *
 */
class WebAuthSession {

  /**
   * Session data.
   */
  protected $data;

  /**
   * Auth URL
   */
  protected $authUrl;

  /**
   * Headers from WebAuth.
   */
  protected $headers = array();

  /**
   * WebAuth AT Cookie.
   */
  protected $atCookie;

  /**
   * Return URL.
   */
  protected $returnUrl;

  /**
   * Logged in status.
   */
  protected $loggedIn;

  /**
   * Initialize the object.
   */
  public function __construct() {
    // Initialize the object and populate the headers.
    $this->__init();

    // Check for WebAuth AT Cookie.
    $this->getAtCookie();

    // If we don't have an at_cookie, we have not authenticated yet.
    if (empty($this->atCookie)) {
      $this->loggedIn = FALSE;
    }
    else {
      $this->loggedIn = TRUE;
    }
  }

  private function __init() {

    // Set our authentication redirect URL.
    $this->makeAuthUrl();

    // Get AT cookie.
    $this->getAtCookie();

    // Get our session data.
    $this->loadSessionData();
  }

  public function getSessionData($key = NULL) {
    if (isset($this->data[$key]) && !empty($key)) {
      return $this->data[$key];
    }
    elseif (!empty($key)) {
      // If set but not available.
      return NULL;
    }
    else {
      return $this->data;
    }
  }

  public function getReturnUrl() {
    return $this->returnUrl;
  }

  // Save the token expiration date in the session object so that it can be checked
  // later without having to call check.php
  public function writeSessionData() {
    if (isset($_SERVER['HTTPS'])) {
      $_SESSION['wa_session_data']['wa_token_expiration'] = $this->data['wa_token_expiration'];
    }
  }

  public function loadSessionData() {
    if (isset($_SESSION['wa_session_data'])) {
      $this->data = $_SESSION['wa_session_data'];
    }
    elseif ($this->isLoggedIn()) {
      $this->getHeaderData();
      foreach ($this->headers as $k => $v) {
        // Check for WA_LDAPPRIVGROUP.
        if (drupal_substr($k, 0, 16) == 'wa_ldapprivgroup') {
          $this->data['ldap_groups'][$v] = $v;
        }
        else {
          $this->data[$k] = $v;
        }
      }
      if ($this->isLoggedIn()) {
        $this->writeSessionData();
      }
    }
  }

  public function isValidSession() {
    if (isset($this->atCookie)) {
      if (empty($this->data)) {
        $this->loadSessionData();
      }
      if (!empty($this->data)) {
        if (REQUEST_TIME <= $this->data['wa_token_expiration'] && $this->isLoggedIn()) {
          return TRUE;
        }
      }
    }
    return FALSE;
  }

  public function isLoggedIn() {
    return (bool) $this->loggedIn;
  }

  public function getLdapGroups() {
    return isset($this->data['ldap_groups']) ? $this->data['ldap_groups'] : array();
  }

  public function getAtCookie() {
    if (isset($_COOKIE['webauth_at']) && $_COOKIE['webauth_at']) {
      $this->atCookie = $_COOKIE['webauth_at'];
    }
  }

  public function getWeblogin() {
    $this->makeAuthUrl();
    header("Location: " . $this->authUrl);
    exit();
  }

  public function makeReturnUrl() {
    // if there is a post-login destination set, that's the destination
	// otherwise, it's the regular drupal destination
    $post_login_destination = trim(variable_get('webauth_destination', ''));

	if (!empty($post_login_destination)) {
      $this->returnUrl  = $post_login_destination;
    }
	else {
	  $destination = drupal_get_destination();
      $this->returnUrl  = $destination['destination'];
	}
  }

  public function makeAuthUrl() {
    // Create auth URL.
    $this->authUrl = $this->getLoginUrl();
  }

  public function getLoginUrl() {
    // Make sure we create a return url before we make a login url.
    $this->makeReturnUrl();

    // This is a fix for non-clean urls.  Need to provide a link to the full
    // path so that we hit the webauth dir. That dir will redirect to proper
    // non-clean path after authentication via webauth.
	// Without this, a person who's not logged in to WebAuth will end up
	// in a redirect loop. Unfortunately, we lose the destination if someone logs in and clean URLs are off
    if (!variable_get('clean_url', FALSE)) {
      $return = 'https://' . $_SERVER['SERVER_NAME'] . base_path() . variable_get('webauth_path', conf_path() . '/webauth')
                . '/login';
      if (isset($this->returnUrl)) {
        $return .= '?destination=' . $this->returnUrl;
      }
    }
    else {
      $return = url(variable_get('webauth_path', conf_path() . '/webauth') . '/login',
                    array('absolute' => TRUE, 'query' => array('destination' => $this->returnUrl)));
    }
    return $return;
  }

  /**
   * Retrieves the headers from a WebAuth-protected resource using the user's webauth_at cookie
   *
   * Also sets the class' isLoggedIn property
   */
  public function getHeaderData() {
    $url = parse_url(url(variable_get('webauth_path', conf_path() . '/webauth') . '/check.php', array('absolute' => TRUE)));
    if (variable_get('clean_url', FALSE) == FALSE) {
      $url['path'] = base_path() . variable_get('webauth_path', conf_path() . '/webauth') . '/check.php';
    }

    // Add the webauth_at cookie to the request and don't follow redirects
    $request_options = array(
      'headers'       => array('Cookie' => "webauth_at=" . urlencode($_COOKIE['webauth_at'])),
      'max_redirects' => 0,
    );

    $request_result = drupal_http_request("https://" . $url['host'] . $url['path'], $request_options);
	
    // If check.php is not found, log it and return.
    if ($request_result->code == 404) {
      watchdog('webauth', 'Connecting to check.php failed, check.php not found at %path".', array('%path' => 'https://' . $url['host'] . $url['path']), WATCHDOG_WARNING);
      drupal_set_message(t('Error: Login failed. Please contact the administrator of this website.'),'error');
      $this->loggedIn = FALSE;
      drupal_goto('<front>');
      return;
    }

    // If there are is an error, log it and return.
    if (isset($request_result->error)) {
      watchdog('webauth', 'Connecting to check.php failed, due to "%error".', array('%error' => $request_result->code . ' ' . $request_result->error), WATCHDOG_WARNING);
      $this->loggedIn = FALSE;
      return;
    }

    // If the request succeeded and it returned a header with the username,
    // save all headers in the class.
    if (($request_result->code == 200) && isset($request_result->headers['wa_user'])) {
      foreach ($request_result->headers as $name => $value) {
        if (substr($name, 0, 3) == 'wa_') {
          $this->headers[$name] = $value;
        }
      }
      $this->loggedIn = TRUE;
    }
    else {
      $this->loggedIn = FALSE;
    }
  }

}
