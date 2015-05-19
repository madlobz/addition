<?php

function addition_settings_form($form, $form_state){
  $form['addition_title_tabs'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show admin tabs in page title'),
    '#default_value' => variable_get('addition_title_tabs', 1),
  );
  if(variable_get('user_register', 2)){
    $form['registration'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="form-item form-required">'.t('Attention! Registration is enabled.').'</div>',
      '#weight' => -1000,
    );
  }
  
  return system_settings_form($form);
}