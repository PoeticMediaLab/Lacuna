<?php
/**
 * Displays the annotation type admin overview page.
 */
function annotation_admin_types() {
  $annotation_entity = entity_get_info('annotation');
  $bundles = $annotation_entity['bundles'];
  //dpm($bundles);
  $field_ui = module_exists('field_ui');
  $header = array(t('Name'), array('data' => t('Operations'), 'colspan' => $field_ui ? '4' : '2'));
  $rows = array();

  foreach ($bundles as $key => $bundle) {
    $type = check_plain($key);
    $name = check_plain($bundle['label']);
    $row = array($name . ' <small>' . t('(Machine name: @type)', array('@type' => $type)) . '</small><div class="description">' . filter_xss_admin($bundle['description']) . '</div>');
    // Set the edit column.
    $row[] = array('data' => l(t('edit'), $bundle['admin']['real path']));
    /*
    if ($field_ui) {
      // Manage fields.
      $row[] = array('data' => l(t('manage fields'), 'admin/annotation/annotation_types/manage/' . check_plain($type) . '/fields'));
      // Display fields.
      $row[] = array('data' => l(t('manage display'), 'admin/annotation/annotation_types/manage/' . check_plain($type) . '/display'));
    }*/
    // Set the delete column.
    if ($bundle['custom']) {
      $row[] = array('data' => l(t('delete'), 'admin/annotation/annotation_types/manage/' . check_plain($type) . '/delete'));
    }
    else {
      $row[] = array('data' => '');
    }

    $rows[] = $row;
  }

  $build['node_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    //'#empty' => t('No content types available. <a href="@link">Add content type</a>.', array('@link' => url('admin/structure/types/add'))),
  );

  return $build;
}

function annotation_admin_content($form, $form_state) {
  $admin_access = user_access('administer annotations');

  // Build the 'Update options' form.
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update options'),
    '#attributes' => array('class' => array('container-inline')),
    '#access' => $admin_access,
  );
  $form['options']['operation'] = array(
    '#type' => 'select',
    '#title' => t('Operation'),
    '#title_display' => 'invisible',
    '#options' => array('delete' => ('Delete')),
    '#default_value' => 'approve',
  );
  $form['options']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#validate' => array('annotation_admin_validate'),
    '#submit' => array('annoation_admin_submit'),
  );

  // Build the sortable table header.
  $header = array(
    'text' => array('data' => t('Text'), 'field' => 'a.text'),
    'type' => array('data' => t('Type'), 'field' => 'a.type'),
    'quote' => array('data' => t('Quote'), 'field' => 'a.quote'),
    'uri' => array('data' => t('Uri'), 'field' => 'a.uri'),
    'author' => t('Author'),
    'timestamp' => array('data' => t('Updated'), 'field' => 'a.updated', 'sort' => 'desc'),
    'operations' => array('data' => t('Operations')),
  );

  $query = db_select('annotation', 'a')->extend('PagerDefault')->extend('TableSort');
  //file_entity_build_filter_query($query);

  $result = $query
    ->fields('a', array('id', 'uid'))
    ->limit(50)
    ->orderByHeader($header)
    //->addTag('file_access')
    ->execute()
    ->fetchAllKeyed();
  $annotations = entity_load_multiple_by_name('annotation', array_keys($result));
  $accounts = user_load_multiple(array_unique($result));
  
  $destination = drupal_get_destination();
  $options = array();

  foreach ($annotations as $annotation) {
    $annotation_type = annotation_type_load($annotation->type);
    $options[$annotation->id] = array(
      'text' => $annotation->field_annotation_text,
      'quote' => $annotation->field_annotation_quote,
      'uri' => l($annotation->field_annotation_uri, $annotation->field_annotation_uri),
      'type' => $annotation_type->label,
      'author' => theme('username', array('account' => $accounts[$annotation->uid])),
      'timestamp' => format_date($annotation->updated, 'short'),
      'operations' => array(),
    );
    $operations = array();
    if ($admin_access) {
      $operations['view'] = array(
        'title' => t('view'),
        'href' => 'annotation/' . $annotation->id,
      );
      $operations['delete'] = array(
        'title' => t('Delete'),
        'href' => 'annotation/' . $annotation->id . '/delete',
        'query' => $destination,
      );
    }
    if (count($operations) > 1) {
      // Render an unordered list of operations links.
      $options[$annotation->id]['operations'] = array(
        'data' => array(
          '#theme' => 'links__file_entity_operations',
          '#links' => $operations,
          '#attributes' => array('class' => array('links', 'inline')),
        ),
      );
    }
    elseif (!empty($operations)) {
      // Render the first and only operation as a link.
      $link = reset($operations);
      $options[$annotation->id]['operations'] = array(
        'data' => array(
          '#type' => 'link',
          '#title' => $link['title'],
          '#href' => $link['href'],
          '#options' => array('query' => $link['query']),
        ),
      );
    }
  }

  if ($admin_access) {
    $form['annotations'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $options,
      '#empty' => t('No annotation available.'),
    );
  }
  else {
    $form['annotations'] = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $options,
      '#empty' => t('No annotation available.'),
    );
  }

  $form['pager'] = array('#markup' => theme('pager'));
  return $form;
}

function annotation_type_form($form, &$form_state, $type = NULL) {
  if (!isset($type)) {
    // This is a new type.
    $type = (object) array(
      'type' => '',
      'label' => '',
      'description' => '',
      'custom' => TRUE,
      'plugin' => '',
      'path' => '',
      'area' => '',
    );
  }
  $form['#annotation_type'] = $type;

  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('This is the human readable name of the file type.'),
    '#required' => TRUE,
    '#default_value' => $type->label,
  );

  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => $type->type,
    '#maxlength' => 255,
    '#disabled' => (bool) $type->type,
    '#machine_name' => array(
      'exists' => 'file_type_load',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this file type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#description' => t('This is the description of the file type.'),
    '#default_value' => $type->description,
  );
  $form['plugin'] = array(
    '#type' => 'select',
    '#title' => t('Annotation plugin'),
    '#description' => t('This is the plugin to make annotation.'),
    '#options' => array(
      'annotator' => t('Annotator'),
      'textus' => t('Textus'),
    ),
    '#default_value' => $type->plugin,
  );
  if (!($type->custom)) {
    $form['plugin']['#disabled'] = TRUE;
  }

  return $form;
}

function annotation_type_submit($form, &$form_state) {
  if (!empty($form['#file_type']->type)) {
    $type = file_type_load($form['#file_type']->type);
  }
  else {
    $type = (object) array(
      'type' => $form_state['values']['type'],
    );
  }
  if ($form_state['values']['op'] == t('Delete')) {
    $form_state['redirect'] = 'admin/structure/file-types/manage/' . $type->type . '/delete';
    return;
  }
  $type->label = $form_state['values']['label'];
  $type->description = $form_state['values']['description'];
  $type->mimetypes = array_filter(array_map('trim', explode("\n", $form_state['values']['mimetypes'])));

  file_type_save($type);

  drupal_set_message(t('The annotation type %type has been updated.', array('%type' => $type->label)));
  $form_state['redirect'] = 'admin/structure/annotation';
}

