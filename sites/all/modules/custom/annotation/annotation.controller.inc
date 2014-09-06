<?php

// /**
//  * Annotation entity api controller class
//  */
// class AnnotationAPIController extends EntityAPIController {
//   public function __construct($entityType) {
//     parent::__construct($entityType);
//   }

//   public function load($ids = array(), $conditions = array()) {
//     $entities = parent::load($ids, $conditions);
//     foreach ($entities as $id => $entity) {
//       //$entity->annotator_schema_version = ANNOTATOR_SCHEMA_VERSION;
//       $op = 'load';
//       drupal_alter('annotation', $entity, $op);
//       $entities[$id] = $entity;
//     }
//     return $entities;
//   }

//   public function save($entity, DatabaseTransaction $transaction = NULL) {
//     $op = 'save';
//     drupal_alter('annotation', $entity, $op);
//     parent::save($entity, $transaction);
//   }

//   public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
//     $wrapper = entity_metadata_wrapper('annotation', $entity);
//     $content['quote'] = array(
//       '#theme' => 'field',
//       '#weight' => 0,
//       '#title' =>t('Quote'),
//       '#access' => TRUE,
//       '#label_display' => 'above',
//       '#view_mode' => 'full',
//       '#language' => LANGUAGE_NONE,
//       '#field_name' => 'field_fake_quote',
//       '#field_type' => 'text',
//       '#entity_type' => 'annotation',
//       '#bundle' => $entity->type,
//       '#items' => array(
//         array('value' => $entity->quote)
//       ),
//       '#formatter' => 'text_default',
//       0 => array(
//         '#markup' => '<blockquote cite="' . check_plain($entity->uri) . '">' . check_plain($entity->quote) . '</blockquote>'
//       )
//     );
//     $content['text'] = array(
//       '#theme' => 'field',
//       '#weight' => 0,
//       '#title' =>t('Annotation'),
//       '#access' => TRUE,
//       '#label_display' => 'above',
//       '#view_mode' => 'full',
//       '#language' => LANGUAGE_NONE,
//       '#field_name' => 'field_fake_text',
//       '#field_type' => 'text',
//       '#entity_type' => 'annotation',
//       '#bundle' => $entity->type,
//       '#items' => array(
//         array('value' => $entity->text)
//       ),
//       '#formatter' => 'text_default',
//       0 => array(
//         '#markup' => check_plain($entity->text)
//       )
//     );

//     $content['tags'] = array(
//       '#theme' => 'field',
//       '#weight' => 0,
//       '#title' =>t('Tags'),
//       '#access' => TRUE,
//       '#label_display' => 'inline',
//       '#view_mode' => 'full',
//       '#language' => LANGUAGE_NONE,
//       '#field_name' => 'field_tags',
//       '#field_type' => 'text',
//       '#entity_type' => 'annotation',
//       '#bundle' => $entity->type,
//       '#items' => array(
//         array('value' => implode(',', $entity->tags))
//       ),
//       '#formatter' => 'text_default',
//       0 => array(
//         '#markup' => check_plain(implode(',', $entity->tags)))
//     );
//     // $content['author'] = array(
//     //   '#markup' => t('Created by: @author on @date at !uri', array(
//     //     '@author' => $wrapper->user->name->value(array('sanitize' => TRUE)),
//     //     '@date' => format_date($wrapper->created->value(array('sanitize' => TRUE))),
//     //     '!uri' => l($wrapper->uri->value(array('sanitize' => TRUE)), $wrapper->uri->value(array('sanitize' => TRUE))),
//     //   ))
//     // );
//     // $user = $wrapper->user->name->value();
//     // dsm(get_properties($wrapper));
//     // dsm($user);
//     $content['#view_mode'] = $view_mode;
//     return parent::buildContent($entity, $view_mode, $langcode, $content);
//   }
// }

// function get_properties($obj, $values=false)
// {
//     $obj_dump  = print_r($obj, 1);
//     $matches =  array();
//     preg_match_all('/^\s+\[(\w+).*\] => (\w*)/m', $obj_dump, $matches);
//     if ($values)
//     {
//         $output = array();
//         foreach ($matches[1] as $key => $property)
//         {
//             $output[$property] = $matches[2][$key];
//         }
//         return $output;
//     }
//     else
//     {
//         return $matches[1];
//     }
// }
