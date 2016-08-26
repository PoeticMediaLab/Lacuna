<?php

/**
 * Expose themes as context reactions.
 */
class bg_image_context_reaction_bg_image extends context_reaction {

  /**
   * Allow admins to provide a section title, section subtitle and section class.
   */
  function options_form($context) {
    $values = $this->fetch_from_context($context);
    $form = array(
      '#tree' => TRUE,
      '#title' => t('Background Image'),
    );
    if (bg_image_node_is_configured()) {
      $node_type = variable_get('bg_image_node_type', '');
      $node_options = bg_image_node_options();
      if (!$node_options) {
        $form['no_nodes_msg'] = array(
          '#markup' => t('There are no nodes yet for the configured node type. You must create at least one @type node before you can apply a background image reaction.', array('@type' => variable_get('bg_image_node_type', ''))),
        );
        return $form;
      }
      $form['bg_image_node_ref_nid'] = array(
        '#type' => 'select',
        '#title' => t('Select A Node'),
        '#description' => t('Choose a node, whose image field specified on the <a href="/admin/config/content/background_image">settings page</a> will be used for the background image'),
        '#options' => $node_options,
        '#default_value' => isset($values['bg_image_node_ref_nid']) ? $values['bg_image_node_ref_nid'] : 0,
      );

      $form['bg_image_weight'] = array(
        '#type' => 'textfield',
        '#title' => t('weight'),
        '#description' => t('If you want you can set a weight for this background image. This helps if you have overlapping conditions in different contexts trying to add multiple background images. Higher values take precedence.'),
        '#default_value' => isset($values['bg_image_weight']) ? $values['bg_image_weight'] : 0,
      );

      $form['bg_image_style'] = array(
        '#type' => 'select',
        '#title' => t('Image Style'),
        '#description' => t('Apply an image style to the image'),
        '#options' => image_style_options(),
        '#default_value' => isset($values['bg_image_style']) ? $values['bg_image_style'] : variable_get('bg_image_style', ''),
      );

      $form['override_css_settings'] = array(
        '#type' => 'checkbox',
        '#title' => t('Override the default css settings'),
        '#description' => t('If selected the css settings provided below will be used instead of the default css settings from the <a href="/admin/config/content/background-image">background image configuration page</a>'),
        '#default_value' => isset($values['override_css_settings']) ? $values['override_css_settings'] : 0,
      );

      // Default CSS Settings can be overridden here
      // Fieldset for css settings
      $form['css_settings'] = array(
        '#type' => 'fieldset',
        '#title' => t('Override Default CSS Settings'),
        '#description' => t('Override the default css settings from the <a href="admin/config/admin/config/content/background-image">Background Image Settings Page</a>'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      // The selector for the background property
      $form['css_settings']['bg_image_selector'] = array(
        '#type' => 'textfield',
        '#title' => t('Selector'),
        '#description' => t('A valid CSS selector that will be used to apply the background image.'),
        '#default_value' => isset($values['css_settings']['bg_image_selector']) ? $values['css_settings']['bg_image_selector'] : variable_get('bg_image_selector', ''),
      );
      // The selector for the background property
      $form['css_settings']['bg_image_color'] = array(
        '#type' => 'textfield',
        '#title' => t('Color'),
        '#description' => t('The background color formatted as any valid css color format (e.g. hex, rgb, text, hsl) [<a href="http://www.w3schools.com/css/pr_background-color.asp">css property: background-color</a>]'),
        '#default_value' => isset($values['css_settings']['bg_image_color']) ? $values['css_settings']['bg_image_color'] : variable_get('bg_image_color', '#FFFFFF'),
      );
      // The selector for the background property
      $form['css_settings']['bg_image_x'] = array(
        '#type' => 'textfield',
        '#title' => t('Horizontal Alignment'),
        '#description' => t('The horizontal alignment of the background image formatted as any valid css alignment. [<a href="http://www.w3schools.com/css/pr_background-position.asp">css property: background-position</a>]'),
        '#default_value' => isset($values['css_settings']['bg_image_x']) ? $values['css_settings']['bg_image_x'] : variable_get('bg_image_x', 'left'),
      );
      // The selector for the background property
      $form['css_settings']['bg_image_y'] = array(
        '#type' => 'textfield',
        '#title' => t('Vertical Alignment'),
        '#description' => t('The vertical alignment of the background image formatted as any valid css alignment. [<a href="http://www.w3schools.com/css/pr_background-position.asp">css property: background-position</a>]'),
        '#default_value' => isset($values['css_settings']['bg_image_y']) ? $values['css_settings']['bg_image_y'] : variable_get('bg_image_y', 'top'),
      );
      // The selector for the background property
      $form['css_settings']['bg_image_attachment'] = array(
        '#type' => 'radios',
        '#title' => t('Background Attachment'),
        '#description' => t('The attachment setting for the background image. [<a href="http://www.w3schools.com/css/pr_background-attachment.asp">css property: background-attachment</a>]'),
        '#options' => array('scroll' => 'Scroll', 'fixed' => 'Fixed'),
        '#default_value' => isset($values['css_settings']['bg_image_attachment']) ? $values['css_settings']['bg_image_attachment'] : variable_get('bg_image_attachment', 'scroll'),
      );
      // The background-repeat property
      $form['css_settings']['bg_image_repeat'] = array(
        '#type' => 'radios',
        '#title' => t('Background Repeat'),
        '#description' => t('Define the repeat settings for the background image. [<a href="http://www.w3schools.com/css/pr_background-repeat.asp">css property: background-repeat</a>]'),
        '#options' => bg_image_css_repeat_options(),
        '#default_value' => isset($values['css_settings']['bg_image_repeat']) ? $values['css_settings']['bg_image_repeat'] : variable_get('bg_image_repeat', 0),
      );
      // The background-size property
      $form['css_settings']['bg_image_background_size'] = array(
        '#type' => 'textfield',
        '#title' => t('Background Size'),
        '#description' => t('The size of the background (NOTE: CSS3 only. Useful for responsive designs) [<a href="http://www.w3schools.com/cssref/css3_pr_background-size.asp">css property: background-size</a>]'),
        '#default_value' => isset($values['css_settings']['bg_image_background_size']) ? $values['css_settings']['bg_image_background_size'] : variable_get('bg_image_background_size', ''),
      );
      // background-size:cover suppor for IE8
      $form['css_settings']['bg_image_background_size_ie8'] = array(
        '#type' => 'checkbox',
        '#title' => t('Add background-size:cover support for ie8'),
        '#description' => t('The background-size css property is only supported on browsers that support CSS3. However, there is a workaround for IE using Internet Explorer\'s built-in filters (http://msdn.microsoft.com/en-us/library/ms532969%28v=vs.85%29.aspx). Check this box to add the filters to the css. Sometimes it works well, sometimes it doesn\'t. Use at your own risk'),
        '#default_value' => isset($values['css_settings']['bg_image_background_size_ie8']) ? $values['css_settings']['bg_image_background_size_ie8'] : variable_get('bg_image_background_size_ie8', 0),
      );
      // The media query specifics
      $form['css_settings']['bg_image_media_query'] = array(
        '#type' => 'textfield',
        '#title' => t('Media Query'),
        '#description' => t('Apply this background image css using a media query. Useful for responsive designs. example: only screen and (min-width:481px) and (max-width:768px) [<a href="http://www.w3.org/TR/css3-mediaqueries/">Read about media queries</a>]'),
        '#default_value' => isset($values['css_settings']['bg_image_media_query']) ? $values['css_settings']['bg_image_media_query'] : variable_get('bg_image_media_query', 'all'),
      );
      $form['css_settings']['bg_image_important'] = array(
        '#type' => 'checkbox',
        '#title' => t('Add "!important" to the background property.'),
        '#description' => t('This can be helpful to override any existing background image or color properties added by the theme.'),
        '#default_value' => isset($values['css_settings']['bg_image_important']) ? $values['css_settings']['bg_image_important'] : variable_get('bg_image_important', 1),
      );
    }
    else {
      $form['settings_first_msg'] = array(
        '#markup' => t('You must specify a content type and field on the <a href="/admin/config/content/background_image">settings page</a> before you can set a background image. Once configured you will be able to reference a specific node here, whose image field will be used to set the background image.'),
      );
    }
    return $form;
  }

  /**
   * Organizes the background image data into an array
   * keyed by the selector, then applies the background
   * image with the highest weight for each selector
   */
  function execute() {
    //dpm(context_enabled_contexts());
    // An array to hold all the bg_image reactions
    $bg_image_nodes = array();
    $contexts = $this->get_contexts();
    // Loop through the contexts
    foreach ($contexts as $context) {
      // As long as the reaction is a bg_image reaction
      if (!empty($context->reactions[$this->plugin])) {
        // Grab the weight and the selector
        $weight = $context->reactions[$this->plugin]['bg_image_weight'];
        $selector = $context->reactions[$this->plugin]['css_settings']['bg_image_selector'];
        $bg_image_style = $context->reactions[$this->plugin]['bg_image_style'];
        // If the css settings are selected to be overridden we use them
        if ($context->reactions[$this->plugin]['override_css_settings']) {
          $css_settings = $context->reactions[$this->plugin]['css_settings'];
        }
        else {
          $css_settings = array();
        }
        // Add the reaction to the container array first by selector, then by weight
        $bg_image_nodes[$selector][$weight] = array(
          'nid' => $context->reactions[$this->plugin]['bg_image_node_ref_nid'],
          'css_settings' => $css_settings,
          'bg_image_style' => $bg_image_style,
        );
      }
    }
    // As long as there is at least one reaction
    if ($bg_image_nodes) {
      // Loop through the stored reactions
      foreach($bg_image_nodes as $selector => $values) {
        // Sort the items that are using the same selector
        ksort($values);
        // Just use the last item from the list, since it has the greatest weight
        $bg_image_node = end($values);
        bg_image_add_background_image_from_node($bg_image_node['nid'], $bg_image_node['css_settings'], $bg_image_node['bg_image_style']);
      }
    }
  }
}
