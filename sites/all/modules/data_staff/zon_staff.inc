<?php

function edit_zon_staff($id_staff = null){
  $core_module_path = drupal_get_path('module','ikhwan_core');
  $csspath = $core_module_path.'/css/custom-style.css';
  drupal_add_css($csspath);
  $jquery_path = drupal_get_path('module','jquery_update');
  $csspath = $jquery_path.'/replace/ui/themes/base/jquery-ui.css';
  drupal_add_css($csspath);
  $jspath = $jquery_path . '/replace/ui/ui/jquery-ui.js';
  drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
  $module_path = drupal_get_path('module', 'data_staff');
  $jspath = $module_path . '/js/form_zon_staff.js';
  drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
  if (!empty($id_staff)){
    $variables['id_staff'] = $id_staff;
    $form = drupal_get_form('zon_staff_form',$variables);
    $formZonStaff = drupal_render($form);
    return $formZonStaff;
  }else{
    drupal_set_message(t('Mohon edit zon Staff Dari Data Staff...!!!'));
    drupal_goto('masterdata/staff');
  }
}

function zon_staff_form($form, &$form_state, $variables = null)
{
  if (isset($variables['id_staff']) && !empty($variables['id_staff'])) {
    $tableHeader = create_zon_staff_header();
    $dataStaff = get_data_staff_only_by_id($variables['id_staff']);
    $tableRow = create_zon_staff_row($variables['id_staff']);
    $tableFooter = array(create_zon_staff_header());
    $form['id_staff'] = array(
      '#type' => 'hidden',
      '#default_value' => $variables['id_staff'],
    );
    $form['basic'] = array(
      '#type' => 'fieldset',
      '#title' => 'DATA ZON STAFF ' . $dataStaff[0]->nama_lengkap,
      '#collapsible' => FALSE, // Added
      '#collapsed' => FALSE,  // Added
      '#prefix' => '<div class="row col-md-6">',
      '#suffix' => '</div>',
    );
    $form['basic']['table'] = array(
      '#theme' => 'formtable_form_table',
      '#header' => $tableHeader,
      'rows' => $tableRow,
      '#footer' => $tableFooter,
    );
    $form['basic']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('SAVE ZON STAFF'),
    );
  }
  return $form;
}

function create_zon_staff_header(){
  $tableHeader = array();
  $tableHeader[] = array(
    'data' => t('No.'),
    'class' => array(
      'col-number'
    ),
  );
  $tableHeader[] = t('ZON');
  $tableHeader[] = t('JAWATAN');
  $tableHeader[] = t('DELETE');
  return $tableHeader;
}

function create_zon_staff_row($IdStaff = null){
  $tableRow = array();
  $tableRow['#tree'] = TRUE;
  $dataStaff = null;
  if (!empty($IdStaff)){
    $dataStaff = get_data_staff(null, false, $IdStaff, null,'ta.id_staff ASC',null,true);
  }
  if (!is_null($dataStaff) && count($dataStaff)) {
    if (isset($dataStaff[0]->zon_jawatan)) {
      $split_data = explode(',', $dataStaff[0]->zon_jawatan);
      if (!empty($split_data)) {
        $array_zon_staff = [];
        foreach ($split_data as $idx => $zon_jawatan_staff) {
          $zon_jawatan = new stdClass();
          $split_data2 = explode('-', $zon_jawatan_staff);
          if (!empty($split_data2)) {
            if (isset($split_data2[0]) && !empty($split_data2[0])) {
              $zon_jawatan->id_zon = (int)$split_data2[0];
            }
            if (isset($split_data2[1]) && !empty($split_data2[1])) {
              $zon_jawatan->id_jawatan = (int)$split_data2[1];
            }
            if (isset($zon_jawatan->id_zon) && !empty($zon_jawatan->id_zon)) {
              $array_zon_staff[] = $zon_jawatan;
            }
          }
        }
      }
    }
    $array_zon = getZoneByCode(null, 'zd.weight');
    $option_zon = [];
    if (!empty($array_zon)) {
      $option_zon[0] = 'Pilih Zon Staff';
      foreach ($array_zon as $idx => $zon_data) {
        $option_zon[$zon_data->id] = $zon_data->zon_name;
      }
    }
    $array_jawatan = array_staff_level();
    if (!empty($array_zon_staff)) {
      for ($i = 0; $i < count($array_zon_staff); $i++) {
        $colData = array();
        $colData['id-' . ($i + 1)] = array(
          '#type' => 'hidden',
          '#prefix' => ($i + 1),
          '#attributes' => array(
            'class' => array('align-right'),
            'id' => 'nidstaff-' . ($i + 1),
            'outerclass' => array('align-right'),
          ),
          '#default_value' => $IdStaff,
        );
        $colData['id_zon-' . ($i + 1)] = array(
          '#type' => 'select',
          '#default_value' => $array_zon_staff[$i]->id_zon,
          '#options' => $option_zon,
          '#select2' => array(
            'placeholder' => t('Pilih Zon Staff'),
            'width' => '100%',
          ),
        );
        $colData['id_jawatan-' . ($i + 1)] = array(
          '#type' => 'select',
          '#default_value' => isset($array_zon_staff[$i]->id_jawatan) && !empty($array_zon_staff[$i]->id_jawatan) ? $array_zon_staff[$i]->id_jawatan : 0,
          '#options' => $array_jawatan,
          '#select2' => array(
            'placeholder' => t('Pilih Jawatan Staff'),
            'width' => '100%',
          ),
        );
        $colData['delete-' . ($i + 1)] = array(
          '#type' => 'hidden',
          '#default_value' => 0,
          '#attributes' => array(
            'id' => 'delete-' . ($i + 1),
          ),
          '#suffix' => '<input type="checkbox" id="checkdel-' . ($i + 1) . '" value="1" class="checkdel">',
        );
        $tableRow['r' . ($i + 1)] = $colData;
      }
      $nextCounter = $i + 1;
      for ($i = 0; $i < 3; $i++) {
        $colData = array();
        $colData['id-' . $nextCounter] = array(
          '#type' => 'hidden', '#prefix' => ($nextCounter),
          '#attributes' => array(
            'class' => array('align-right'),
            'id' => 'nidstaff-' . $nextCounter,
            'outerclass' => array('align-right'),
          ),
          '#default_value' => '',
        );
        $colData['id_zon-' . $nextCounter] = array(
          '#type' => 'select',
          '#options' => $option_zon,
          '#select2' => array(
            'placeholder' => t('Pilih Zon Staff'),
            'width' => '100%',
          ),
          '#default_value' => 0,
        );
        $colData['id_jawatan-' . $nextCounter] = array(
          '#type' => 'select',
          '#options' => $array_jawatan,
          '#select2' => array(
            'placeholder' => t('Pilih Jawatan Staff'),
            'width' => '100%',
          ),
          '#default_value' => 0,
        );
        $tableRow['r' . $nextCounter] = $colData;
        $nextCounter++;
      }
    } else {
      $nextCounter = 1;
      for ($i = 0; $i < 5; $i++) {
        $colData = array();
        $colData['id-' . $nextCounter] = array(
          '#type' => 'hidden', '#prefix' => ($nextCounter),
          '#attributes' => array(
            'class' => array('align-right'),
            'id' => 'nidstaff-' . $nextCounter,
            'outerclass' => array('align-right'),
          ),
          '#default_value' => '',
        );
        $colData['id_zon-' . $nextCounter] = array(
          '#type' => 'select',
          '#options' => $option_zon,
          '#select2' => array(
            'placeholder' => t('Pilih Zon Staff'),
            'width' => '100%',
          ),
        );
        $colData['id_jawatan-' . $nextCounter] = array(
          '#type' => 'select',
          '#options' => $array_jawatan,
          '#select2' => array(
            'placeholder' => t('Pilih Jawatan Staff'),
            'width' => '100%',
          ),
        );
        $tableRow['r' . $nextCounter] = $colData;
        $nextCounter++;
      }
    }
  }
  return $tableRow;
}

function zon_staff_form_submit($form, &$form_state)
{
  global $user;
  $IdStaff = null;
  $FormValues = [];
  if (isset($form_state['values']) && isset($form_state['values']['id_staff']) && !empty($form_state['values']['id_staff'])){
    $IdStaff = $form_state['values']['id_staff'];
    if (isset($form_state['values']['rows'])){
      $FormValues = $form_state['values']['rows'];
    }
  }
  if (!empty($IdStaff) && !empty($FormValues)) {
    db_set_active('master');
    $conditionData = array();
    $consObj = new stdClass();
    $consObj->fieldName = 'id_staff';
    $consObj->fieldValue = $IdStaff;
    $consObj->status = 'and';
    $conditionData[] = $consObj;
    deleteTableData('master_data_zon_staff', 'admin data staff', $conditionData);
    $DeletedZon = [];
    foreach ($FormValues as $idx => $RowValues){
      $SavedData = [];
      foreach ($RowValues as $FieldId => $FieldValue){
        $SplitId = explode('-', $FieldId);
        if ($SplitId[0] != 'id' && $SplitId[0] != 'delete'){
          $SavedData[$SplitId[0]] = $FieldValue;
        }else if ($SplitId[0] == 'delete'){
          if ($FieldValue == '1') {
            $DeletedInfo = new stdClass();
            $DeletedInfo->id_zon = $SavedData['id_zon'];
            $DeletedInfo->id_jawatan = $SavedData['id_jawatan'];
            $DeletedInfo->id_staff = $IdStaff;
            $DeletedZon[] = $DeletedInfo;
          }
        }
      }
      if (isset($SavedData['id_zon']) && !empty($SavedData['id_zon'])){
        $SavedData['id_staff'] = $IdStaff;
        saveTableData('master_data_zon_staff', 'admin data staff', $SavedData, null, null,false);
      }
    }
    if (!empty($DeletedZon)){
      foreach ($DeletedZon as$idx => $ZonData){
        $conditionData = array();
        $consObj = new stdClass();
        $consObj->fieldName = 'id_staff';
        $consObj->fieldValue = $ZonData->id_staff;
        $consObj->status = 'and';
        $conditionData[] = $consObj;
        $consObj = new stdClass();
        $consObj->fieldName = 'id_zon';
        $consObj->fieldValue = $ZonData->id_zon;
        $consObj->status = 'and';
        $conditionData[] = $consObj;
        $consObj = new stdClass();
        $consObj->fieldName = 'id_jawatan';
        $consObj->fieldValue = $ZonData->id_jawatan;
        $consObj->status = 'and';
        $conditionData[] = $consObj;
        deleteTableData('master_data_zon_staff', 'admin data staff', $conditionData);
      }
    }
    $dataStaff = get_data_staff(null, false, $IdStaff, null,'ta.id_staff ASC',null,true);
    if (empty($dataStaff)){
      $SavedData = [];
      $SavedData['id_zon'] = 0;
      $SavedData['id_staff'] = $IdStaff;
      $SavedData['id_jawatan'] = 0;
      saveTableData('master_data_zon_staff', 'admin data staff', $SavedData, null, null,false);
    }
    db_set_active();
  }
}
