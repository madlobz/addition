<?php

function metatag_url_has_metatags($path=null){
  $info = menu_get_item($path);
  $path = $info['path'];
  
  $routers = variable_get('addition_metatag_paths', array());
  return isset($routers[$path])?$routers[$path]:false;
}

function metatag_url_access($path){
  if(!user_access('edit meta tags')) return false;
  
  $path = str_replace('--', '/', $path);
  return metatag_url_has_metatags($path);
}

function metatag_url_load($path){
  $result = db_select('metatag_url', 'm')
    ->fields('m')
    ->condition('path', $path)
    ->execute()
    ->fetchObject();
  if(!$result) return array();
  return unserialize($result->data);
}

function metatag_url_save($path, $data){
  $data = serialize($data);
  
  if(metatag_url_load($path)){
    db_update('metatag_url')
      ->fields(array(
        'data' => $data,
      ))
      ->condition('path', $path)
      ->execute();
  } else {
    metatag_url_delete($path);
    db_insert('metatag_url')
      ->fields(array(
        'data' => $data,
        'path' => $path,
      ))
      ->execute();
  }
}

function metatag_url_delete($path){
  db_delete('metatag_url')
    ->condition('path', $path)
    ->execute();
}

function metatag_url_token_set($data=null){
  $metatag_url_token = &drupal_static(__FUNCTION__);
  
  if($data){
    $info = menu_get_item();
    $name = str_replace('/', '--', $info['path']);
    $name = str_replace('%', '', $name);
    $metatag_url_token[$name] = $data;
  }

  return $metatag_url_token;
}

function metatag_url_token_get(){
  return metatag_url_token_set();
}