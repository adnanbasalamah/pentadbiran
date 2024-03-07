<?php

/**
 * @file
 * Admin page callbacks for the google currency converter module.
 */

 /**
  * Configuration form for the google currency converter settings.
  */
function google_currency_converter_settings_form($form_state, &$from_state) {
  $form = array();
  $form['currency_converter'] = array(
    '#type' => 'fieldset',
    '#title' => t('Please Select Your Defaut Block Currency'),
  );
  $form['currency_converter']['google_currency_converter_from'] = array(
    '#type' => 'select',
    '#title' => t('Select Your Currency From'),
    '#options' => google_currency_converter_country_list(),
    '#default_value' => variable_get('google_currency_converter_from', ''),
    '#required' => TRUE,
  );
  $form['currency_converter']['google_currency_converter_to'] = array(
    '#type' => 'select',
    '#title' => t('Select Your Currency To'),
    '#options' => google_currency_converter_country_list(),
    '#default_value' => variable_get('google_currency_converter_to', ''),
    '#required' => TRUE,
  );
  return system_settings_form($form);
}

/**
 * Validates the submitted google currency converter settings form.
 */
function google_currency_converter_settings_form_validate(&$form, &$form_state) {
  if ($form_state['values']['google_currency_converter_from'] == $form_state['values']['google_currency_converter_to']) {
    form_set_error('google_currency_converter_to', t('Please select different currency both currency are same.'));
  }
}
