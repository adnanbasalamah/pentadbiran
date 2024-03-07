<?php

/**
 *
 */
function _add_jeditable_plugins(){
    drupal_add_js('sites/all/libraries/jeditable.datepicker/jquery.jeditable.mini.js',array('scope' => 'footer', 'weight' => 5));
    drupal_add_js('sites/all/libraries/jeditable.datepicker/jquery.jeditable.datepicker.js',array('scope' => 'footer', 'weight' => 5));
}

function add_chosen_jquery_plugins(){
    drupal_add_css('sites/all/libraries/chosen/chosen.min.css');
    drupal_add_js('sites/all/libraries/chosen/chosen.jquery.min.js',array('scope' => 'footer', 'weight' => 5));
}