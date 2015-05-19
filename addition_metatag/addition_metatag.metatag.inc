<?php
/**
 * @file
 * Meta tag integration for the metatag_views module.
 */

/**
 * Implements hook_metatag_config_instance_info().
 */
function addition_metatag_metatag_config_instance_info() {
  $info = array();
  
  $routers = variable_get('addition_metatag_paths', array());
  foreach($routers as $router){
    $info[$router['name']] = array(
      'label' => $router['title'],
    );
  }
  
  return $info;
}

/**
 * Implements hook_metatag_config_default().
 */
function addition_metatag_metatag_config_default() {
  $configs = array();

  $routers = variable_get('addition_metatag_paths', array());
  foreach($routers as $router){
    $config = new stdClass();
    $config->instance = $router['name'];
    $config->api_version = 1;
    $config->disabled = false;
    $config->config = array(
      'title' => array('value' => '[current-page:title] | [site:name]'),
    );
    $configs[$config->instance] = $config;
  }

  return $configs;
}
