<?php

function edit_status_pernikahan_staff($id_staff = null){
  $core_module_path = drupal_get_path('module','ikhwan_core');
  $csspath = $core_module_path.'/css/custom-style.css';
  drupal_add_css($csspath);
  $jquery_path = drupal_get_path('module','jquery_update');
  $csspath = $jquery_path.'/replace/ui/themes/base/jquery-ui.css';
  drupal_add_css($csspath);
  $jspath = $jquery_path . '/replace/ui/ui/jquery-ui.js';
  drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
  $module_path = drupal_get_path('module', 'data_staff');
  $jspath = $module_path . '/js/form_status_pernikahan_staff.js';
  drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
  if (!empty($id_staff)){
    $variables['id_staff'] = $id_staff;
    $form = drupal_get_form('status_pernikahan_staff_form',$variables);
    $formZonStaff = drupal_render($form);
    return $formZonStaff;
  }else{
    drupal_set_message(t('Mohon edit status pernikahan Staff Dari Data Staff...!!!'));
    drupal_goto('masterdata/staff');
  }
}

function status_pernikahan_staff_form($form, &$form_state, $variables = null){
  if (isset($variables['id_staff']) && !empty($variables['id_staff'])) {
    $tableHeader = create_status_pernikahan_staff_header();
    $DataStaff = get_data_staff_only_by_id(null, false, $variables['id_staff']);
    $tableRow = create_status_pernikahan_staff_row($variables['id_staff']);
    $tableFooter = array(create_status_pernikahan_staff_header());
    $form['id_staff'] = array(
      '#type' => 'hidden',
      '#default_value' => $DataStaff[0]->id_number,
    );
    $form['basic'] = array(
      '#type' => 'fieldset',
      '#title' => 'STATUS PERNIKAHAN STAFF ' . $DataStaff[0]->nama_lengkap,
      '#collapsible' => FALSE, // Added
      '#collapsed' => FALSE,  // Added
    );
    $form['basic']['table'] = array(
      '#theme' => 'formtable_form_table',
      '#header' => $tableHeader,
      'rows' => $tableRow,
      '#footer' => $tableFooter,
    );
    $form['basic']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('SAVE STATUS PERNIKAHAN'),
    );
  }
  return $form;
}
function create_status_pernikahan_staff_header(){
  $tableHeader = array();
  $tableHeader[] = array(
    'data' => t('No.'),
    'class' => array(
      'col-number'
    ),
  );
  $tableHeader[] = t('NAMA LENGKAP');
  $tableHeader[] = t('STATUS');
  $tableHeader[] = t('TARIKH STATUS');
  $tableHeader[] = t('TEMPAT STATUS');
  $tableHeader[] = t('DELETE');
  return $tableHeader;
}
