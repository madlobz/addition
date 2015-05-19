<?php

function addition_views_edit_page($view_name, $display_name){
  $view = views_get_view($view_name);
  
  if(!$view) {
    drupal_not_found();
    drupal_exit();
  }
  
  $display_name = isset($view->display[$display_name])?$display_name:'default';
  $view->set_display($display_name);
  
  $title = $view->display_handler->get_option('title');
  drupal_set_title($title);
  
  return drupal_get_form('addition_views_edit_form', $view);
}

function addition_views_edit_form($form, $form_state, $view) {  
  $title = $view->display_handler->get_option('title');
  $header = $view->display_handler->get_option('header');
  $footer = $view->display_handler->get_option('footer');
  $empty = $view->display_handler->get_option('empty');
  
  $form['view_name'] = array(
    '#type' => 'value',
    '#value' => $view->name,
  );
  $form['display_name'] = array(
    '#type' => 'value',
    '#value' => $view->current_display,
  );
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => $title,
  );
  $form['header'] = array(
    '#type' => 'text_format',
    '#title' => t('Header'),
    '#default_value' => isset($header['area'])?$header['area']['content']:'',
    '#format' => isset($header['area'])?$header['area']['format']:'filtered_html',
  );
  $form['footer'] = array(
    '#type' => 'text_format',
    '#title' => t('Footer'),
    '#default_value' => isset($footer['area'])?$footer['area']['content']:'',
    '#format' => isset($footer['area'])?$footer['area']['format']:'filtered_html',
  );
  $form['empty'] = array(
    '#type' => 'text_format',
    '#title' => t('Empty text'),
    '#default_value' => isset($empty['area'])?$empty['area']['content']:'',
    '#format' => isset($empty['area'])?$empty['area']['format']:'filtered_html',
  );
  
  if(module_exists('metatag_views')){
    $instance = 'view:' . $view->name;
    $metatags = $view->display_handler->get_option('metatags');
    $metatags = !empty($metatags) ? $metatags : array();
    $options['token types'] = array('view');
    $options['context'] = 'view';
    metatag_metatags_form($form, $instance, $metatags, $options);
    $form['metatags']['#type'] = 'fieldset';
  }
  
  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['#submit'][] = 'addition_views_edit_form_submit';
  
  return $form;
}

function addition_views_edit_form_submit($form, &$form_state){
  $view_name = $form_state['values']['view_name'];
  $display_name = $form_state['values']['display_name'];
  $title = $form_state['values']['title'];
  $header_value = $form_state['values']['header'];
  $footer_value = $form_state['values']['footer'];
  $empty_value = $form_state['values']['empty'];
  
  $view = views_get_view($view_name);
  $view->set_display($display_name);
  
  $header = $view->display_handler->get_option('header');
  if($header_value['value']) {
    $header['area'] = array(
      'content' => $header_value['value'],
      'format' => $header_value['format'],
      'table' => 'views',
      'field' => 'area',
      'id' => 'area',
    );
    $view->display_handler->set_override('header', false);
  } else {
    unset($header['area']);
  }
  $footer = $view->display_handler->get_option('footer');
  if($footer_value['value']) {
    $footer['area'] = array(
      'content' => $footer_value['value'],
      'format' => $footer_value['format'],
      'table' => 'views',
      'field' => 'area',
      'id' => 'area',
    );
    $view->display_handler->set_override('footer', false);
  } else {
    unset($footer['area']);
  }
  $empty = $view->display_handler->get_option('empty');
  if($empty_value['value']) {
    $empty['area'] = array(
      'content' => $empty_value['value'],
      'format' => $empty_value['format'],
      'table' => 'views',
      'field' => 'area',
      'id' => 'area',
    );
    $view->display_handler->set_override('empty', false);
  } else {
    unset($empty['area']);
  }

  $view->display_handler->set_option('title', $title);
  $view->display_handler->set_option('header', $header);
  $view->display_handler->set_option('footer', $footer);
  $view->display_handler->set_option('empty', $empty);
  
  if (isset($form_state['input']['metatags'])) {
    $metatags = $form_state['values']['metatags'];
    metatag_filter_values_from_defaults($metatags);
    $view->display_handler->set_option('metatags', $metatags);
  }
  
  $view->save();
}