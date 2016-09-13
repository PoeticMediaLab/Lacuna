<?php
    $profile_user = $variables['elements']['#account'];
    $username = format_username($profile_user);
?>

<section id="user-profile-main">
	<aside class="column left-part">
		<div id="user-avatar-space" class="profile-section">
            <?php $basePath = base_path();?>
            <?php print $user_profile["user_picture"]["#markup"]; ?>
            <?php print "<p class='profileUsername'>$username</p>"; ?>
                <div id="user-command-buttons">
                    <?php if (($profile_user->uid === $user->uid) || user_access('administer users')):?>
                        <div><a href="<?php print $basePath . "user/" . $profile_user->uid . "/edit"?>"><i class="fa fa-cog fa-2x"></i><span>Profile settings</span></a></div>
                        <div><a href="<?php print $basePath . "user/" . $profile_user->uid. "/notify"?>"><i class="fa fa-bell-o fa-2x"></i><span>Notification settings</span></a></div>
                    <?php endif; ?>
                    <?php if (user_access('access user contact forms')): ?>
                        <div><a href="<?php print $basePath . "user/" . $profile_user->uid . "/contact"?>"><i class="fa fa-comment-o fa-2x"></i><span>Contact</span></a></div>
                    <?php endif; ?>
                </div>
			
		</div>	
	</aside>
	<div class="column right-part">
		<div id="user-about-space" class="profile-section">
			<span class="caption">About</span>
			<div class="field-wrapper">
        <?php   if(isset($field_about_me)) print "<p>{$field_about_me[0]["value"]} </p>";
                else print "<p>Empty</p>"
        ?>
			</div>
		</div>
		<div id="user-contributions-space" class="profile-section">
			<span class="caption">Recent Contributions</span>
			<div class="field-wrapper">
				<p class="title">Responses</p>
        <?php
          print views_embed_view('responses_by_user', 'block');
          $responsesEmpty = empty(views_get_view_result('responses_by_user', 'block'));
        ?>
			</div>
			<div class="field-wrapper">
        <p class="title">Comments</p>
        <?php print views_embed_view('comments_by_user', 'block');?>
			</div>
			<div class="field-wrapper">
        <p class="title">Annotations</p>
        <?php
          print views_embed_view('annotations_by_user', 'block');
          $annotationsEmpty = empty(views_get_view_result('annotations_by_user', 'block'));
        ?>
      </div>
		</div>

	</div>
  <div class="profile-section" id="user-learning">
      <?php
        global $base_url;
        $themePath = $base_url . '/' . path_to_theme();
        $anVisImgURL = $themePath . "/images/user-profile-images/annotation_visualization_logo.png";
        $anImgURL = $themePath . "/images/user-profile-images/annotation_logo.png";
        $resMapImgURL = $themePath . "/images/user-profile-images/responses_map_logo.png";
        $annotationsURL = $base_url . "/sewing-kit?author_select[]={$profile_user->uid}";
        $anVisualizationURL = $base_url . "/visualization/dashboard?uid={$profile_user->uid}";
        $responsesMapURL = $base_url . "/visualization/responses?uid={$profile_user->uid}";
      ?>
      <span class="caption">Learning Activity</span>
      <div class="field-wrapper">
          <table>
              <tr>
                  <td>
                      <div class="user-link-item <?php print $annotationsEmpty ? 'is-empty' : '' ?>">
                          <a href="<?php print $anVisualizationURL?>"><img id="annotation-visual-logo" src="<?php print $anVisImgURL?>"/></a>
                          <p><?php print $username ?>'s Dashboard</p>
                      </div>
                  </td>
                  <td>
                      <div class="user-link-item <?php print $annotationsEmpty ? 'is-empty' : '' ?>">
                          <a href="<?php print $annotationsURL?>"><img id="annotation-view-logo" src="<?php print $anImgURL?>"/></a>
                          <p><?php print $username ?>'s Sewing Kit</p>
                      </div>
                  </td>
                  <td>
                      <div class="user-link-item <?php print $responsesEmpty ? 'is-empty' : '' ?>">
                          <a href="<?php print $responsesMapURL?>"><img id="response-map-logo" src="<?php print $resMapImgURL?>"/></a>
                          <p><?php print $username ?>'s Response Map</p>
                      </div>
                  </td>
              </tr>
          </table>
      </div>
    </div>
</section>
