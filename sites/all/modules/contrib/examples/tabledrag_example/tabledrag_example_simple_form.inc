<?php
/**
 * @file
 * Example demonstrating a simple (i.e. 'sort' only) tabledrag form
 */

/**
 * Build the tabledrag_simple_example_form form.
 *
 * @return array
 *   A form array set for theming by theme_tabledrag_example_simple_form()
 *
 * @ingroup tabledrag_example
 */
function tabledrag_example_simple_form($form_state) {
  // Identify that the elements in 'example_items' are a collection, to
  // prevent Form API from flattening the array when submitted.
  $form['example_items']['#tree'] = TRUE;

  // Fetch the example data from the database, ordered by weight ascending.
  //
  // This query excludes the last two tabledrag_example database rows, as
  // they are intended only for the 'parent/child' tabledrag examples.
  $result = db_query('SELECT id, name, description, weight FROM {tabledrag_example} WHERE id < 8 ORDER BY weight ASC');

  // Iterate through each database result.
  foreach ($result as $item) {

    // Create a form entry for this item.
    //
    // Each entry will be an array using the the unique id for that item as
    // the array key, and an array of table row data as the value.
    $form['example_items'][$item->id] = array(

      // We'll use a form element of type '#markup' to display the item name.
      'name' => array(
        '#markup' => check_plain($item->name),
      ),

      // We'll use a form element of type '#textfield' to display the item
      // description, which will allow the value to be changed via the form.
      // We limit the input to 255 characters, which is the limit we set on
      // the database field.
      'description' => array(
        '#type' => 'textfield',
        '#default_value' => check_plain($item->description),
        '#size' => 20,
        '#maxlength' => 255,
      ),

      // The 'weight' field will be manipulated as we move the items around in
      // the table using the tabledrag activity.  We use the 'weight' element
      // defined in Drupal's Form API.
      'weight' => array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#default_value' => $item->weight,
        '#delta' => 10,
        '#title_display' => 'invisible',
      ),
    );
  }

  // Now we add our submit button, for submitting the form results.
  //
  // The 'actions' wrapper used here isn't strictly necessary for tabledrag,
  // but is included as a Form API recommended practice.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save Changes'));
  return $form;
}

/**
 * Theme callback for the tabledrag_example_simple_form form.
 *
 * The theme callback will format the $form data structure into a table and
 * add our tabledrag functionality.  (Note that drupal_add_tabledrag should be
 * called from the theme layer, and not from a form declaration.  This helps
 * keep template files clean and readable, and prevents tabledrag.js from
 * being added twice accidently.
 *
 * @return array
 *   The rendered tabledrag form
 *
 * @ingroup tabledrag_example
 */
function theme_tabledrag_example_simple_form($variables) {
  $form = $variables['form'];

  // Initialize the variable which will store our table rows.
  $rows = array();

  // Iterate over each element in our $form['example_items'] array.
  foreach (element_children($form['example_items']) as $id) {

    // Before we add our 'weight' column to the row, we need to give the
    // element a custom class so that it can be identified in the
    // drupal_add_tabledrag call.
    //
    // This could also have been done during the form declaration by adding
    // '#attributes' => array('class' => 'example-item-weight'),
    // directy to the 'weight' element in tabledrag_example_simple_form().
    $form['example_items'][$id]['weight']['#attributes']['class'] = array('example-item-weight');

    // We are now ready to add each element of our $form data to the $rows
    // array, so that they end up as individual table cells when rendered
    // in the final table.  We run each element through the drupal_render()
    // function to generate the final html markup for that element.
    $rows[] = array(
      'data' => array(
        // Add our 'name' column.
        drupal_render($form['example_items'][$id]['name']),
        // Add our 'description' column.
        drupal_render($form['example_items'][$id]['description']),
        // Add our 'weight' column.
        drupal_render($form['example_items'][$id]['weight']),
      ),
      // To support the tabledrag behaviour, we need to assign each row of the
      // table a class attribute of 'draggable'. This will add the 'draggable'
      // class to the <tr> element for that row when the final table is
      // rendered.
      'class' => array('draggable'),
    );
  }

  // We now define the table header values.  Ensure that the 'header' count
  // matches the final column count for your table.
  $header = array(t('Name'), t('Description'), t('Weight'));

  // We also need to pass the drupal_add_tabledrag() function an id which will
  // be used to identify the <table> element containing our tabledrag form.
  // Because an element's 'id' should be unique on a page, make sure the value
  // you select is NOT the same as the form ID used in your form declaration.
  $table_id = 'example-items-table';

  // We can render our tabledrag table for output.
  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => $table_id),
  ));

  // And then render any remaining form elements (such as our submit button).
  $output .= drupal_render_children($form);

  // We now call the drupal_add_tabledrag() function in order to add the
  // tabledrag.js goodness onto our page.
  //
  // For a basic sortable table, we need to pass it:
  // - the $table_id of our <table> element,
  // - the $action to be performed on our form items ('order'),
  // - a string describing where $action should be applied ('siblings'),
  // - and the class of the element containing our 'weight' element.
  drupal_add_tabledrag($table_id, 'order', 'sibling', 'example-item-weight');

  return $output;
}

/**
 * Submit callback for the tabledrag_example_simple_form form.
 *
 * Updates the 'weight' column for each element in our table, taking into
 * account that item's new order after the drag and drop actions have been
 * performed.
 *
 * @ingroup tabledrag_example
 */
function tabledrag_example_simple_form_submit($form, &$form_state) {
  // Because the form elements were keyed with the item ids from the database,
  // we can simply iterate through the submitted values.
  foreach ($form_state['values']['example_items'] as $id => $item) {
    db_query(
      "UPDATE {tabledrag_example} SET weight = :weight WHERE id = :id",
      array(':weight' => $item['weight'], ':id' => $id)
    );
  }
}
