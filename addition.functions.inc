<?php

function drupal_is_ajax(){
  if(isset($_SERVER['HTTP_X_REQUESTED_WITH']) && !empty($_SERVER['HTTP_X_REQUESTED_WITH']) && strtolower($_SERVER['HTTP_X_REQUESTED_WITH']) == 'xmlhttprequest') return true;
  return false;
}

function drupal_get_html($url){
  $curl = curl_init(); 
	 
	$header[] = "Accept:*/*"; 
	$header[] = "Accept-Encoding:gzip,deflate,sdch"; 
	$header[] = "Accept-Language:ru-RU,ru;q=0.8,en-US;q=0.6,en;q=0.4"; 
	$header[] = "Connection:keep-alive"; 
	$header[] = "Host:translate.google.com"; 
	
	curl_setopt($curl, CURLOPT_URL, $url); 
	curl_setopt($curl, CURLOPT_USERAGENT, $_SERVER["HTTP_USER_AGENT"]); 
	curl_setopt($curl, CURLOPT_HTTPHEADER, $header); 
	curl_setopt($curl, CURLOPT_REFERER, 'http://google.com/'); 
	curl_setopt($curl, CURLOPT_ENCODING, 'gzip,deflate'); 
	curl_setopt($curl, CURLOPT_AUTOREFERER, true); 
	curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1); 
	curl_setopt($curl, CURLOPT_TIMEOUT, 4); 
	$result = curl_exec($curl);
	curl_close($curl);
	
	return $result; 
}

if(!function_exists('mb_ucfirst')){
  function mb_ucfirst($str, $enc='utf-8'){ 
    return mb_strtoupper(mb_substr($str, 0, 1, $enc), $enc).mb_substr($str, 1, mb_strlen($str, $enc), $enc); 
  }
}

function drupal_google_translate($text, $from='en', $to='ru'){  
  $translate = @drupal_get_html('http://translate.google.ru/translate_a/t?client=x&text='.str_replace(' ', '+', $text).'&hl='.$from.'&sl='.$from.'&tl='.$to.'&ie=UTF-8&oe=UTF-8');   
  $translate = @json_decode($translate);
  $translate = @$translate->sentences[0]->trans;
  
  return $translate?mb_ucfirst($translate):$text;
}

function drupal_get_geolocation(){
	require_once(drupal_get_path('module', 'addition').'/includes/geo.class.php');
	$geo = new Geo(array('charset'=>'utf-8'));
	$geo = @$geo->get_value(false, false);
	
	return $geo?$geo:array(
	  'inetnum' => '',
	  'country' => 'RU',
	  'city' => 'Москва',
	  'region' => 'Москва',
	  'district' => 'Центральный федеральный округ',
	  'lat' => '55.751667',
	  'lng' => '37.617778',
	);
}