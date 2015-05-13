<?php

/**
 * @file
 * Default theme implementation to present all user profile data.
 *
 * This template is used when viewing a registered member's profile page,
 * e.g., example.com/user/123. 123 being the users ID.
 *
 * Use render($user_profile) to print all profile items, or print a subset
 * such as render($user_profile['user_picture']). Always call
 * render($user_profile) at the end in order to print all remaining items. If
 * the item is a category, it will contain all its profile items. By default,
 * $user_profile['summary'] is provided, which contains data on the user's
 * history. Other data can be included by modules. $user_profile['user_picture']
 * is available for showing the account picture.
 *
 * Available variables:
 *   - $user_profile: An array of profile items. Use render() to print them.
 *   - Field variables: for each field instance attached to the user a
 *     corresponding variable is defined; e.g., $account->field_example has a
 *     variable $field_example defined. When needing to access a field's raw
 *     values, developers/themers are strongly encouraged to use these
 *     variables. Otherwise they will have to explicitly specify the desired
 *     field language, e.g. $account->field_example['en'], thus overriding any
 *     language negotiation rule that was previously applied.
 *
 * @see user-profile-category.tpl.php
 *   Where the html is handled for the group.
 * @see user-profile-item.tpl.php
 *   Where the html is handled for each item in the group.
 * @see template_preprocess_user_profile()
 *
 * @ingroup themeable
 */
?>

<?php

/*
 * Function customPrintViewsBlock()
 * returns true if block with name $blockName is not empty and returns true;
 * otherwise returns false and does not print anything
 */
function customPrintViewsBlock($blockName)
{
    $block = block_load("views", $blockName);
    $blocks_to_render = _block_render_blocks(array($block));
    if(count($blocks_to_render) > 0)
    {
        $render_array = _block_get_renderable_array($blocks_to_render);
        print render($render_array);
        return true;
    }
    return false;
}
?>

<section id="user-profile-main">
	<div class="column left-part">
		<div id="user-avatar-space" class="profile-section">
            <?php $userInView = menu_get_object('user');
            $basePath = base_path();
            if($userInView->uid === $user->uid):?>
                <div id="user-command-buttons">
                    <a href="<?php print $basePath."user/".$user->uid."/edit"?>"><i class="fa fa-cog fa-2x"></i></a>
                    <a href="<?php print $basePath."user/".$user->uid."/notify"?>"><i class="fa fa-bell-o fa-2x"></i></a>
                    <a href="<?php print $basePath."user/".$user->uid."/contact"?>"><i class="fa fa-comment-o fa-2x"></i></a>
                </div>
            <?php endif; ?>
			<?php print $user_profile["user_picture"]["#markup"]; ?>
		</div>
		<div id="how-I-Learn-space" class="profile-section">
			<span class="caption">About My Case</span>
			<div class="field-wrapper">
                <?php   if(isset($field_how_i_learn)) print "<p>{$field_how_i_learn[0]["value"]} </p>";
                        else print "<p>Empty</p>"
                ?>
			</div>
		</div>
	</div>

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
                <?php $responsesIsEmpty = !customPrintViewsBlock("user_s_responses-block");
                    if($responsesIsEmpty)
                    {
                        print "<p class='no-results'>{$field_display_name[0]['value']} has not written any responses</p>";
                    } ?>
			</div>
			<div class="field-wrapper">
                <p class="title">Comments</p>
                <?php $commentsIsEmpty = !customPrintViewsBlock("user_s_comments-block");
                    if($commentsIsEmpty)
                    {
                        print "<p class='no-results'>{$field_display_name[0]['value']} has not made any comments</p>";
                    } ?>
			</div>
			<div class="field-wrapper">
                <p class="title">Annotations</p>
                <?php $annotationsIsEmpty = !customPrintViewsBlock("my_annotations_view-block");
                    if($annotationsIsEmpty)
                    {
                        print "<p class='no-results'>{$field_display_name[0]['value']} has not made any annotations</p>";
                    } ?>
			</div>
		</div>
		<div id="user-learning-goals-space" class="profile-section">
			<span class="caption">Collaboration Goals</span>
            <div class="field-wrapper">
                <?php   if(isset($field_learning_goals))
                {
                    foreach($field_learning_goals as $goal) print "<p>{$goal["value"]}</p>";
                }
                else print "<p>Empty</p>"
                ?>
			</div>
		</div>
	</div>
    <div class="profile-section" id="user-learning">
        <?php
            $bPath = base_path();
            $themePath = $bPath . path_to_theme();
            $anVisImgURL = $themePath . "/images/user-profile-images/annotation_visualization_logo.png";
            $anImgURL = $themePath . "/images/user-profile-images/annotation_logo.png";
            $resMapImgURL = $themePath . "/images/user-profile-images/responses_map_logo.png";
            $annotationsURL = $annotationsIsEmpty ? "#" : $bPath . "sewing-kit"."?field_display_name_value={$field_display_name[0]['value']}";
            $anVisualizationURL = $annotationsIsEmpty ? "#" : $bPath . "visualization/dashboard?u_id={$userInView->uid}";
            $responsesMapURL = $responsesIsEmpty ? "#" : $bPath . "visualization/responses?u_id={$userInView->uid}";
        ?>
        <span class="caption">My Learning</span>
        <div class="field-wrapper">
            <table>
                <tr>
                    <td>
                        <div class="user-link-item <?php print $annotationsIsEmpty ? 'is-empty' : '' ?>">
                            <a href="<?php print $anVisualizationURL?>"><img id="annotation-visual-logo" src="<?php print $anVisImgURL?>"/></a>
                            <p>Annotation Visualization</p>
                        </div>
                    </td>
                    <td>
                        <div class="user-link-item <?php print $annotationsIsEmpty ? 'is-empty' : '' ?>">
                            <a href="<?php print $annotationsURL?>"><img id="annotation-view-logo" src="<?php print $anImgURL?>"/></a>
                            <p><?php print $field_display_name[0]['value'] ?>'s Annotations</p>
                        </div>
                    </td>
                    <td>
                        <div class="user-link-item <?php print $responsesIsEmpty ? 'is-empty' : '' ?>">
                            <a href="<?php print $responsesMapURL?>"><img id="response-map-logo" src="<?php print $resMapImgURL?>"/></a>
                            <p><?php print $field_display_name[0]['value'] ?>'s Response Map</p>
                        </div>
                    </td>
                </tr>
            </table>
        </div>
    </div>
</section>
