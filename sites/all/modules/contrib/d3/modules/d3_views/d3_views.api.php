<?php
/**
 * @file
 * Describes hooks and related information about the d3_views module.
 */

/**
 * Values for d3.[library name].libraries.info.
 *
 * - views[version]: (optional) Version of views that this library will be compatible with.
 * - views[fields]: Associative array of field values required by
 *     the visualization.
 *
 *     e.g.,
 *     @code
 *     views[fields][rows][name][label] = Field Name
 *     views[fields][rows][name][type] = integer
 *
 *     views[fields][rows][name] = { label: Field Name, type: integer }
 *     @endcode
 *
 * All entries for views[fields] are mapped from the views return rows. Data
 * can be extracted out of those rows into different arrays, but all data
 * will originate from the views rows.
 *
 * All entries for views[settings] will be single static values. This will
 * require [__form_element] to be defined so that the settings page will know
 * how the data is to be entered in. These are helpful for variables like width
 * and height.
 *
 * Magic meta keys
 * - __cardinality: Define the number of elements in an array. Only used for certain
 *   arrays.
 * - __repeated: Define if there might be a dynamic amount of instances of a certain
 *   field, (or column). See d3.linegraph.libraries.info for an example.
 * - __data_type: This defines how the array will be processed.
 *
 * - s:     single field / label 
 * 'field value'
 * - sv:    single row value (string / int)
 * 'field row value' / 49
 * - 1dn:   1-dimensional numeric array of fields / labels
 * array('field value 1', 'field value 2', 'field value 3')
 * - 1dnv:  1-dimensional numeric array of row values 
 * array('field row value 1', 'field row value 2', 'field row value 3')
 * - 1da:   1-dimensional associative array of fields / labels
 * array(
 *  'fieldValue1' => 'field value 1',
 *  'fieldValue2' => 'field value 2',
 *  'fieldValue3' => 'field value 3',
 * )
 * - 2dnnv: 2-dimensional numeric array of numeric arrays of row values 
 * array(
 *  array('field row value 1', 'field row value 2', 'field row value 3')
 *  array('field row value 1', 'field row value 2', 'field row value 3')
 *  array('field row value 1', 'field row value 2', 'field row value 3')
 * )
 * - 2dnav: 2-dimensional numeric array of associative (mapped) arrays of row values 
 * array(
 *  array(
 *    'field1' => 'field value 1',
 *    'field2' => 'field value 2',
 *    'field3' => 'field value 3'
 *  )
 *  array(
 *    'field1' => 'field value 1',
 *    'field2' => 'field value 2',
 *    'field3' => 'field value 3'
 *  )
 *  array(
 *    'field1' => 'field value 1',
 *    'field2' => 'field value 2',
 *    'field3' => 'field value 3'
 *  )
 * )
 */
