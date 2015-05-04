<?php
/**
 * @file
 * Describe hooks provided by the d3 module.
 */

/**
 * @mainpage D3 API Manual
 */

/**
 * Add custom library info handlers.
 *
 * @return
 *   An array of new handler info. The key is important as it will define
 *   what in the library .info file is actually being handled. In the case of
 *   the example below, the handlers would search for anything in the info
 *   file with the key "views".
 *   Examples:
 *     views[version] = 3
 *     views[fields][rows][name] = { label: Name, description: Name of the row }
 *   - processor: The custom library processor class.
 *   - controller: The custom library controller class.
 *   - mapping: The custom library mapping class.
 */
function hook_library_info_handlers() {
  return array(
    'views' => array(
      'processor' => 'D3ViewsLibraryInfoProcessor',
      'controller' => 'D3ViewsLibraryInfoController',
      'mapping' => 'D3ViewsDataMapping',
    ),
  );
}

function hook_library_info_handlers_alter() {

}
