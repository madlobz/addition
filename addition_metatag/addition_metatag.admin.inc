<?php

function addition_metatag_settings_form($form, $form_state, $path){ 
  $path = str_replace('--', '/', $path);
  $info = menu_get_item($path);
  $root_path = $info['path'];
  $metatags = metatag_url_load($path);

  $form['path'] = array(
    '#type' => 'value',
    '#value' => $path,
  );
  $form['actions'] = array(
    '#type' => 'actions',
    '#weight' => 100,
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['#submit'][] = 'addition_metatag_settings_form_submit';
  
  $options['token types'] = array();
  
  $tokens = token_info();
  foreach($tokens['types'] as $data => $token){
    $path = str_replace('--', '/', $data);
    if($path == $root_path) $options['token types'][] = $data;
  }
  
  metatag_metatags_form($form, 'path', $metatags, $options);
  $form['metatags']['#collapsible'] = false;
  
  return $form;
}

function addition_metatag_settings_form_submit($form, $form_state){
  $metatags = $form_state['values']['metatags'];
  metatag_filter_values_from_defaults($metatags);

  $path = $form_state['values']['path'];
  metatag_url_save($path, $metatags);
}