<?php

function unit_premis_page($id_unit = null){
  $module_path  = drupal_get_path('module','unit_premis');
  $jspath = $module_path.'/js/unit_premis.js';
  drupal_add_js($jspath,array('scope' => 'footer', 'weight' => 5));
  $variables = [];
  if (!empty($id_unit)){
    $DataUnit = get_data_unit_premis($id_unit);
    $variables['id'] = $DataUnit->id;
    $variables['id_premis'] = $DataUnit->id_premis;
    $variables['nama_unit'] = $DataUnit->nama_unit;
    $variables['alamat'] = $DataUnit->alamat;
    $variables['telepon'] = $DataUnit->telepon;
    $variables['whatsapp'] = $DataUnit->whatsapp;
    $variables['bbm'] = $DataUnit->bbm;
    $variables['telegram'] = $DataUnit->telegram;
    $variables['email'] = $DataUnit->email;
  }
  $Form = drupal_get_form('form_unit_premis',$variables);
  $FormUnit = drupal_render($Form);
  $TableUnit = table_unit_premis();
  $UnitPage = '<div class="row"><div class="col-md-6">'.$TableUnit.'</div>';
  $UnitPage .= '<div class="col-md-6">'.$FormUnit.'</div></div>';
  return $UnitPage;
}

function form_unit_premis($form, &$form_state, $variables = null){
  global $user;
  $form['#attributes'] = array('class' => array('col-sm-12','form-inline'));
  $form['basic'] = array(
    '#type' => 'fieldset',
    '#title' => t('Unit Info'),
    '#collapsible' => TRUE, // Added
    '#collapsed' => FALSE,  // Added
  );
  $keuanganZone = cek_keuangan_zone();
  $userZone = null;
  if ($keuanganZone) {
    $userZone = get_user_zone();
  }
  $DataZon = getZoneByCode();
  $ArrayZon = [];
  foreach ($DataZon as $Idx => $ZonInfo){
    $ArrayZon[$ZonInfo->zone] = $ZonInfo->nama;
  }
  if (count($userZone) && isset($userZone[0])) {
    $getDataZone = $userZone[1]['zone'];
    $dataPremis = $userZone[1]['id_premis'];
    $dataPremis = get_data_premis_by_id($getDataZone[0],$dataPremis);
  } else {
    $getDataZone = getZoneByCode();
    $dataPremis = get_data_premis_by_id();
  }
  $OptPremis = [];
  foreach($dataPremis as $Idx => $PremisInfo){
    $InfoNegri = $PremisInfo->negeri_nama.' '.$ArrayZon[$PremisInfo->zone];
    $OptPremis[$PremisInfo->id] = $PremisInfo->nama.' -> ['.$InfoNegri.']';
  }
  if (!empty($variables['id'])){
    $form['basic']['id'] = array(
      '#type' => 'hidden',
      '#default_value' => $variables['id'],
    );
  }
  $form['basic']['id_premis'] = array(
    '#title' => t('Premis'),
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => $OptPremis,
    '#default_value' => isset($variables['id_premis']) ? $variables['id_premis'] : 0,
    '#select2' => array(
      'placeholder' => t('Pilih Premis'),
    ),
  );
  $form['basic']['nama_unit'] = array(
    '#type' => 'textfield',
    '#title' => t('Nama Unit'),
    '#required' => TRUE,
    '#default_value' => isset($variables['nama_unit']) ? $variables['nama_unit'] : '',
  );
  $form['basic']['alamat'] = array(
    '#title' => t('Alamat'),
    '#type' => 'textarea',
    '#default_value' => isset($variables['alamat']) ? $variables['alamat'] : '',
  );
  $form['basic']['telepon'] = array(
    '#type' => 'textfield',
    '#title' => t('Telephone'),
    '#default_value' => isset($variables['telepon']) ? $variables['telepon'] : '',
  );
  $form['basic']['whatsapp'] = array(
    '#type' => 'textfield',
    '#title' => t('Whatsapp'),
    '#default_value' => isset($variables['whatsapp']) ? $variables['whatsapp'] : '',
  );
  $form['basic']['bbm'] = array(
    '#type' => 'textfield',
    '#title' => t('BBM'),
    '#default_value' => isset($variables['bbm']) ? $variables['bbm'] : '',
  );
  $form['basic']['telegram'] = array(
    '#type' => 'textfield',
    '#title' => t('Telegram'),
    '#default_value' => isset($variables['telegram']) ? $variables['telegram'] : '',
  );
  $form['basic']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#default_value' => isset($variables['email']) ? $variables['email'] : '',
  );
  $form['saveButton'] = array(
    '#value' => t('Save Data Unit'),
    '#type' => 'submit',
    '#attributes' => array('class' => array('btn btn-primary')),
    '#prefix' => '<div class="col-md-12">',
    '#suffix' => '</div>',
  );
  return $form;
}

function form_unit_premis_submit($form, &$form_state) {
  $values = $form_state['values'];
  $savedData = array();
  $savedData['id_premis'] = $values['id_premis'];
  $savedData['nama_unit'] = $values['nama_unit'];
  $savedData['alamat'] = $values['alamat'];
  $savedData['telepon'] = $values['telepon'];
  $savedData['whatsapp'] = $values['whatsapp'];
  $savedData['bbm'] = $values['bbm'];
  $savedData['telegram'] = $values['telegram'];
  $savedData['email'] = $values['email'];
  if (isset($values['id']) && !empty($values['id'])){
    $updatedData = saveTableData('zdatapremis_unit','admin unit premis',$savedData,'id',$values['id']);
    $returnData = $updatedData;
    drupal_set_message("Data unit premis berhasil di update");
    //drupal_goto('masterdata/zone');
  }else{
    $insertedData = saveTableData('zdatapremis_unit','admin unit premis',$savedData);
    $returnData = $insertedData;
    drupal_set_message("Data unit premis berhasil di simpan");
  }
  return $returnData;
}

function table_unit_premis()
{
  $attributes['datatable_options'] = array(
    'bFilter' => TRUE,
    'bInfo' => TRUE,
    'bStateSave' => TRUE,
    'sPaginationType' => 'full_numbers',
  );
  $keuanganZone = cek_keuangan_zone();
  $userZone = null;
  if ($keuanganZone) {
    $userZone = get_user_zone();
  }
  if (count($userZone) && isset($userZone[0])) {
    $ZoneUser = $userZone[1]['zone'];
  }else{
    $ZoneUser = null;
  }
  $DataUnit = get_data_unit_premis(null, null, $ZoneUser);
  $DataZon = getZoneByCode();
  $ArrayZon = [];
  foreach ($DataZon as $Idx => $ZonInfo) {
    $ArrayZon[$ZonInfo->zone] = $ZonInfo->nama;
  }
  $UnitRow = [];
  foreach ($DataUnit as $Idx => $UnitInfo) {
    $UnitRec = [];
    $UnitRec[] = $ArrayZon[$UnitInfo->zone];
    $UnitRec[] = $UnitInfo->negeri_nama;
    $UnitRec[] = $UnitInfo->nama;
    $UnitRec[] = $UnitInfo->nama_unit;
    $UnitRec[] = $UnitInfo->telepon;
    //$UnitRec[] = $UnitInfo->whatsapp;
    $editIcon = '<i class="fa fa-edit"></i>';
    $editButtonVar = array(
      'element' => array(
        '#attributes' => array(
          'class' => array('btn-info', 'btn-xs', 'no-margin', 'edit-premis'),
          'id' => 'edit-unit-' . $UnitInfo->id,
          'name' => 'edit-unit-' . $UnitInfo->id,
          'onclick' => 'edit_unit(\'' . $UnitInfo->id . '\')',
        ),
        '#button_type' => 'button',
        '#value' => $editIcon . ' EDIT',
      )
    );
    $editButton = theme('button', $editButtonVar);
    $UnitRec[] = $editButton;
    $delIcon = '<i class="fa fa-trash-o"></i>';
    $delButtonVar = array(
      'element' => array(
        '#attributes' => array(
          'class' => array('btn-danger', 'btn-xs', 'no-margin', 'del-premis'),
          'id' => 'del-unit-' . $UnitInfo->id,
          'name' => 'del-unit-' . $UnitInfo->id,
          'onclick' => 'delete_unit(\'' . $UnitInfo->id . '\',\'' . $UnitInfo->nama_unit . '\')',
        ),
        '#button_type' => 'button',
        '#value' => $delIcon . ' HAPUS',
      )
    );
    $delButton = theme('button', $delButtonVar);
    $UnitRec[] = $delButton;
    $UnitRow[] = $UnitRec;
  }
  $Header = header_table_unit();
  $Footer[] = $Header;
  $variables = array(
    'attributes' => $attributes,
    'header' => $Header,
    'rows' => $UnitRow,
    'footer' => $Footer,
  );
  $TableUnit = theme('datatable', $variables);
  return $TableUnit;
}

function header_table_unit(){
  // Define table columns
  $Header = array(
    array(
      'data' => t('Zone'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    array(
      'data' => t('Negeri'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    array(
      'data' => t('Premis'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    array(
        'data' => t('Unit'),
        'datatable_options' => array(
            'bSortable' => TRUE,
            'bSearchable' => TRUE,
        ),
    ),
    array(
      'data' => t('Telepon'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    /*array(
      'data' => t('Whatsapp'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),*/
    array(
      'data' => t('Edit'),
      'class' => array('col-number'),
      'datatable_options' => array(
        'bSortable' => FALSE,
        'bSearchable' => FALSE,
      ),
    ),
    array(
      'data' => t('Hapus'),
      'class' => array('col-number'),
      'datatable_options' => array(
        'bSortable' => FALSE,
        'bSearchable' => FALSE,
      ),
    ),
  );
  return $Header;
}
