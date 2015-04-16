<?php
    /**
     * Implements hook_preprocess_views_view().
     */
    // function lacuna_stories_preprocess_views_view(&$vars) {
    //  // Assign to your specific view.
    //   if ($vars['view']->name === 'Artifacts') {
    //     // Wrap exposed filters in a fieldset.
    //     if ($vars['exposed']) {
    //       drupal_add_js('misc/form.js');
    //       drupal_add_js('misc/collapse.js');
    //       // Default collapsed
    //       $collapsed = TRUE;
    //       $class = array('collapsible', 'collapsed');
    //       if (count($_GET) > 1){
    //         // assume other get vars are exposed filters, so expand fieldset
    //         // to show applied filters
    //         $collapsed = FALSE;
    //         $class = array('collapsible');
    //       }
    //       $fieldset['element'] = array(
    //         '#title' => t('Filter'),
    //         '#collapsible' => TRUE,
    //         '#collapsed' => $collapsed,
    //         '#attributes' => array('class' => $class),
    //         '#children' => $vars['exposed'],
    //       );
    //       $vars['exposed'] = theme('fieldset', $fieldset);
    //     }
    //   }
    // }
?>
