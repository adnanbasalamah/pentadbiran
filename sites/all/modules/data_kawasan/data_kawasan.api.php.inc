<?php

function list_kawasan(){
  global $user;
  $core_module_path = drupal_get_path('module', 'ikhwan_core');
  $csspath = $core_module_path . '/css/custom-style.css';
  drupal_add_css($csspath);
  $module_path = drupal_get_path('module', 'data_kawasan');
  $jspath = $module_path . '/js/list_kawasan.js';
  drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
  // Table settings.
  $attributes['datatable_options'] = array(
    'bFilter' => TRUE,
    'bInfo' => TRUE,
    'bStateSave' => FALSE,
    'sPaginationType' => 'full_numbers',
    'iDisplayLength' => 100,
    'aLengthMenu' => [[100, 250, 500, -1], [100, 250, 500, "All"]],
  );
  // Define table columns
  $header = array(
    array(
      'data' => t('Zon'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    array(
      'data' => t('Kawasan'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    array(
      'data' => t('Premis'),
      'datatable_options' => array(
        'bSortable' => FALSE,
        'bSearchable' => TRUE,
      ),
    ),
  );
  if (user_access('admin data kawasan')){
    $header[] = array(
      'data' => t('Edit'),
      'class' => array('col-number'),
      'datatable_options' => array(
        'bSortable' => FALSE,
        'bSearchable' => FALSE,
      ),
    );
    $header[] = array(
      'data' => t('Hapus'),
      'class' => array('col-number'),
      'datatable_options' => array(
        'bSortable' => FALSE,
        'bSearchable' => FALSE,
      ),
    );
  }
  // Table data.
  $rows = array();
  $dataKawasan = get_data_kawasan();
  for ($i = 0; $i < count($dataKawasan); $i++) {
    $kawasanData = [];
    $data_zon = $dataKawasan[$i]->zon;
    $list_zon = '-';
    if (count($data_zon) > 1) {
      $list_zon = '<ul>';
      foreach ($data_zon as $idx_zon => $zon){
        $list_zon .= '<li>'.$zon->zon_name.'</li>';
      }
      $list_zon .= '</ul>';
    }else if(count($data_zon) == 1) {
      $list_zon = $data_zon[0]->zon_name;
    }
    $kawasanData[] = $list_zon;
    $kawasanData[] = $dataKawasan[$i]->kawasan;
    $dataPremis = get_data_premis_by_id(null, null, $dataKawasan[$i]->id_kawasan);
    $premisList = '';
    for ($j = 0;$j < count($dataPremis);$j++){
      if ($premisList == ''){
        $premisList .= $dataPremis[$j]->nama;
      }else {
        $premisList .= ', ' . $dataPremis[$j]->nama;
      }
    }
    $kawasanData[] = $premisList;
    if (user_access('admin data kawasan')) {
      $editIcon = '<i class="fa fa-edit"></i>';
      $editButtonVar = array(
        'element' => array(
          '#attributes' => array(
            'class' => array('btn-info', 'btn-xs', 'no-margin', 'edit-kawasan'),
            'id' => 'edit-kawasan-' . $dataKawasan[$i]->id_kawasan,
            'name' => 'edit-kawasan-' . $dataKawasan[$i]->id_kawasan,
            'onclick' => 'edit_kawasan(\'' . $dataKawasan[$i]->id_kawasan . '\')',
          ),
          '#button_type' => 'button',
          '#value' => $editIcon . ' EDIT',
        )
      );
      $editButton = theme('button', $editButtonVar);
      $kawasanData[] = $editButton;
      $delIcon = '<i class="fa fa-trash-o"></i>';
      $delButtonVar = array(
        'element' => array(
          '#attributes' => array(
            'class' => array('btn-danger', 'btn-xs', 'no-margin', 'del-kawasan'),
            'id' => 'del-kawasan-' . $dataKawasan[$i]->id_kawasan,
            'name' => 'del-kawasan-' . $dataKawasan[$i]->id_kawasan,
            'onclick' => 'delete_kawasan(\'' . $dataKawasan[$i]->id_kawasan . '\')',
          ),
          '#button_type' => 'button',
          '#value' => $delIcon . ' HAPUS',
        )
      );
      if (count($dataPremis) <= 0) {
        $delButton = theme('button', $delButtonVar);
      } else {
        $delButton = '';
      }
      $kawasanData[] = $delButton;
    }
    $rows[] = $kawasanData;
  }
  // Or, render using a theme function.
  $variables = array(
    'attributes' => $attributes,
    'header' => $header,
    'rows' => $rows,
  );
  $newKawasanButton = '';
  if (user_access('admin data kawasan')) {
    $newKawasanButtonVar = array(
      'element' => array(
        '#attributes' => array(
          'class' => array('btn-info btn-sm'),
          'id' => 'new-kawasan',
          'name' => 'new-kawasan',
        ),
        '#button_type' => 'button',
        '#value' => t('Tambah Data Kawasan'),
      )
    );
    $newKawasanButton = theme('button', $newKawasanButtonVar);
  }
  $listKawasan = $newKawasanButton.theme('datatable', $variables);
  return $listKawasan;
}

function form_add_kawasan($id_kawasan = null){
  $module_path = drupal_get_path('module','ikhwan_core');
  $csspath = $module_path.'/css/custom-style.css';
  drupal_add_css($csspath);
  $getDataKawasan = null;
  if (!empty($id_kawasan)){
    $getDataKawasan = get_data_kawasan(null, $id_kawasan);
  }
  if (empty($getDataKawasan)){
    $getDataKawasan = new stdClass();
    $getDataKawasan->id_kawasan = 0;
    $getDataKawasan->id_zon = 0;
    $getDataKawasan->zon_name = '';
    $getDataKawasan->kawasan = '';
  }
  $variables = $getDataKawasan;
  $form = drupal_get_form('form_data_kawasan',$variables);
  $formKawasan = drupal_render($form);
  return $formKawasan;
}

function form_data_kawasan($form, &$form_state, $variables = null){
  global $user;
  $form['#attributes'] = array('class' => array('col-sm-12'));
  $form['basic'] = array(
    '#type' => 'fieldset',
    '#title' => t('Kawasan'),
    '#collapsible' => TRUE, // Added
    '#collapsed' => FALSE,  // Added
    '#prefix' => '<div class="col-md-6">',
  );
  $getDataZone = getZoneByCode();
  $userZone = get_user_zone();
  $arrayZone = array();
  for ($i = 0;$i < count($getDataZone);$i++){
    if ($userZone[0]){
      if (in_array($getDataZone[$i]->id, $userZone[1]['zone'])){
        $arrayZone[$getDataZone[$i]->id] = $getDataZone[$i]->zon_name;
      }
    }else{
      $arrayZone[$getDataZone[$i]->id] = $getDataZone[$i]->zon_name;
    }
  }
  if (!empty($variables->id_kawasan)){
    $form['basic']['id_kawasan'] = array(
      '#type' => 'hidden',
      '#default_value' => $variables->id_kawasan,
    );
    $array_zone_kawasan = [];
    if (isset($variables->zon) && count($variables->zon)){
      foreach ($variables->zon as $idxzk => $zon){
        $array_zone_kawasan[] = $zon->id_zon;
      }
      $variables->id_zon = $array_zone_kawasan;
    }
  }
  $form['basic']['zon'] = array(
    '#title' => t('Zone'),
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => $arrayZone,
    '#multiple' => TRUE,
    '#default_value' => $variables->id_zon,
    '#select2' => array(
      'placeholder' => 'Select Zone',
    ),
  );
  $form['basic']['kawasan'] = array(
    '#type' => 'textfield',
    '#title' => t('Nama Kawasan'),
    '#required' => TRUE,
    '#default_value' => $variables->kawasan,
  );
  $form['saveButton'] = array(
    '#value' => t('Save Data Kawasan'),
    '#type' => 'submit',
    '#attributes' => array('class' => array('btn btn-primary')),
    '#prefix' => '<div class="col-md-12">',
    '#suffix' => '</div>',
  );
  return $form;
}

function form_data_kawasan_submit($form, &$form_state)
{
  global $user;
  db_set_active('master');
  $values = $form_state['values'];
  $savedData = array();
  $savedData['kawasan'] = $values['kawasan'];
  $savedDataZonKawasan['zon'] = $values['zon'];
  if (isset($values['id_kawasan']) && !empty($values['id_kawasan'])) {
    $updatedData = [];
    if (!empty($savedData['kawasan'])) {
      $updatedData[] = saveTableData(
        'master_data_kawasan', 'admin data kawasan',
        $savedData, 'id_kawasan', $values['id_kawasan']
      );
      $conditionData = array();
      $consObj = new stdClass();
      $consObj->fieldName = 'id_kawasan';
      $consObj->fieldValue = $values['id_kawasan'];
      $consObj->status = 'and';
      $conditionData[] = $consObj;
      deleteTableData('master_data_zon_kawasan', 'admin data kawasan', $conditionData);
      if (isset($values['zon']) && count($values['zon'])) {
        foreach ($values['zon'] as $idx => $id_zon) {
          $save_zon_kawasan = [];
          $save_zon_kawasan['id_kawasan'] = $values['id_kawasan'];
          $save_zon_kawasan['id_zon'] = $id_zon;
          $updatedData[] = saveTableData(
            'master_data_zon_kawasan', 'admin data kawasan',
            $save_zon_kawasan, null, null, false
          );
        }
      }
    }
    $returnData = $updatedData;
    drupal_set_message("Data kawasan berhasil di simpan");
  } else {
    $insertedData = [];
    if (!empty($savedData['kawasan'])) {
      $id_kawasan = saveTableData(
        'master_data_kawasan', 'admin data kawasan', $savedData,
        null, null, false
      );
      if (isset($values['zon']) && count($values['zon'])) {
        foreach ($values['zon'] as $idxZone => $id_zon) {
          $save_zon_kawasan = [];
          $save_zon_kawasan['id_kawasan'] = $id_kawasan;
          $save_zon_kawasan['id_zon'] = $id_zon;
          $insertedData[] = saveTableData('master_data_zon_kawasan', 'admin data kawasan', $save_zon_kawasan, null, null, false);
        }
      }
      drupal_set_message("Data kawasan berhasil di simpan");
    }
    $returnData = $insertedData;
  }
  db_set_active();
  drupal_goto('masterdata/kawasan');
  return $returnData;
}

function delete_kawasan_data(){

}
