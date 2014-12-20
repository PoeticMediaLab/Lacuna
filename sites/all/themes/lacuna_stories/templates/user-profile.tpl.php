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
<!--div class="profile"<?php print $attributes; ?>>
  <?php print render($user_profile); ?>
</div-->

<section id="user-profile-main">
	<div class="column left-part">
		<div id="user-avatar-space" class="profile-section">
			<div id="user-command-buttons">
				<i class="fa fa-edit fa-2x"></i>
				<i class="fa fa-bell-o fa-2x"></i>
				<i class="fa fa-cog fa-2x"></i>
			</div>
			<?php print $user_profile["user_picture"]["#markup"]; ?>
		</div>
		<div id="how-I-Learn-space" class="profile-section">
			<span class="caption">How I Learn</span>
			<div class="field-wrapper">
			</div>			
		</div>
	</div>

	<div class="column right-part">
		<div id="user-bio-space" class="profile-section">
			<div class="field-wrapper">
				<p>Today's Bio Bit: Brian's hometown is Big Sandy, MT</p>
			</div>
		</div>
		<div id="user-about-space" class="profile-section">
			<span class="caption">About</span>
			<div class="field-wrapper">				
			</div>
		</div>
		<div id="user-contributions-space" class="profile-section">
			<span class="caption">Recent Contributions</span>
			<div class="field-wrapper">
				<p>Responses</p>
				<?php $block = block_load("views", "user_s_responses-block");
				$render_array = _block_get_renderable_array(_block_render_blocks(array($block)));
				print render($render_array); ?>
			</div>
			<div class="field-wrapper">
				<p>Comments</p>
			</div>
			<div class="field-wrapper">
				<p>Annotations</p>
				<?php $block = block_load("views", "my_annotations_view-block");
				$render_array = _block_get_renderable_array(_block_render_blocks(array($block)));
				print render($render_array); ?>			
			</div>			
		</div>
		<div id="user-learning-goals-space" class="profile-section">
			<span class="caption">Learning Goals</span>
			<div class="field-wrapper">
			</div>			
		</div>
	</div>	
</section>
