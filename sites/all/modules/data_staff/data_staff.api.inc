<?php

function array_staff_level(){
    return array(
        'Ahli/Staff',
        'Wakil Pengurus',
        'Pengurus',
        'Bod',
        'Ibu',
        'SUK-M 3',
        'SUK-M 2',
        'SUK-M 1',
        'SUK 3',
        'SUK 2',
        'SUK 1',
        'PZ',
        'IZ',
        'IZ1-2',
        'PZ1-2',
        'IZ1',
        'PZ1',
    );
}

function array_jenis_kelamin(){
    return array(t('Laki-laki'), t('Perempuan'));
}

function get_data_staff($id_zon = null, $option = false, $id_staff = null, $where_clause = null){
  global $user;
  $data_return = null;
  db_set_active('master');
  $field_array = [
    'id_number', 'id_zon', 'zon', 'id_kawasan', 'id_staff', 'id_ayah', 'id_ibu', 'nama_lengkap', 'nama_hijrah',
    'jantina', 'tempat_lahir', 'tarikh_lahir', 'bangsa', 'negara', 'no_ic', 'no_kk', 'alamat',
    'no_hp', 'email', 'id_suami', 'nama_suami', 'nama_ayah', 'nama_ibu', 'created', 'changed',
    'uid', 'uid_changed', 'nama_sekolah', 'staff_level'
  ];
  $field_array2 = array(
    'id', 'zon_name',
  );
  $field_array3 = array(
    'id_kawasan', 'kawasan',
  );
  $conditionArray = null;
  if (!empty($id_zon)){
    $conditionArray = array();
    $consData = new stdClass();
    $consData->fieldName = 'ta.id_zon';
    $consData->value = $id_zon;
    if (is_array($id_zon)){
      $consData->operator = 'IN';
    }
    $conditionArray[] = $consData;
  }
  if (!empty($id_staff)){
    $conditionArray = array();
    $consData = new stdClass();
    $consData->fieldName = 'ta.id_number';
    $consData->value = $id_staff;
    if (is_array($id_zon)){
      $consData->operator = 'IN';
    }
    $conditionArray[] = $consData;
  }
  $leftJoinArray = array(
    array(
      'tablename' => 'zons',
      'tablealias' => 'zons',
      'field_source' => 'id',
      'field_join' => 'id_zon',
      'fieldArray' => $field_array2,
    ),
    array(
      'tablename' => 'master_data_kawasan',
      'tablealias' => 'kawasan',
      'field_source' => 'id_kawasan',
      'field_join' => 'id_kawasan',
      'fieldArray' => $field_array3,
    ),
  );
  $data_return = getTableDataByField(
    'master_data_staff', 'access data staff', $field_array,
    null, null, null, $leftJoinArray, $conditionArray, null, $where_clause
  );
  if (count($data_return) == 1){
    $data_return = $data_return[0];
  }
  if ($option){
    $DataOption = array();
    foreach ($data_return as $DataStaff){
      $DataOption[$DataStaff->id_number] = $DataStaff->nama_lengkap;
    }
    $data_return = $DataOption;
  }
  db_set_active();
  return $data_return;
}
function list_staff()
{
  $whereClause = null;
  if (isset($_GET['jenis_kelamin'])) {
    $whereClause = array();
    /*$PremisId = $_REQUEST['premis'];
    if (!empty($PremisId) && COUNT($PremisId) && !isset($PremisId[0])) {
      $whereData = new stdClass();
      $whereData->clause = 'id_premis IN (:arg1)';
      $whereData->value = array(':arg1' => $PremisId);
      $whereClause[] = $whereData;
    }*/
    $BulanMilad = $_GET['month'];
    if ($BulanMilad != 0) {
      $whereData = new stdClass();
      $whereData->clause = 'SUBSTRING(tarikh_lahir,6,2) = :arg2';
      $whereData->value = array(':arg2' => $BulanMilad);
      $whereClause[] = $whereData;
    }
    $JenisKelamin = $_GET['jenis_kelamin'];
    if ($JenisKelamin != -1) {
      $whereData = new stdClass();
      $whereData->clause = 'jantina = :arg3';
      $whereData->value = array(':arg3' => $JenisKelamin);
      $whereClause[] = $whereData;
    }
    $UmurMin = $_GET['umur_min'];
    $UmurMax = $_GET['umur_max'];
    if ($UmurMin <= $UmurMax) {
      $whereData = new stdClass();
      $whereData->clause = '(TIMESTAMPDIFF(YEAR,tarikh_lahir,CURDATE()) >= :arg4 ';
      $whereData->clause .= 'AND TIMESTAMPDIFF(YEAR,tarikh_lahir,CURDATE()) <= :arg5)';
      $whereData->value = array(':arg4' => $UmurMin, ':arg5' => $UmurMax);
      $whereClause[] = $whereData;
    }
  }
  $id_zon = null;
  if (isset($_GET['id_zon']) && !empty($_GET['id_zon'])) {
    $id_zon = [];
    foreach ($_GET['id_zon'] as $idx => $selected_zon){
      if (!empty($selected_zon)){
        $id_zon[] = $selected_zon;
      }
    }
    if (empty($id_zon)){
      $id_zon = null;
    }
  }
  $core_module_path = drupal_get_path('module', 'ikhwan_core');
  $csspath = $core_module_path . '/css/custom-style.css';
  drupal_add_css($csspath);
  $jquery_path = drupal_get_path('module', 'jquery_update');
  $csspath = $jquery_path . '/replace/ui/themes/base/jquery-ui.css';
  drupal_add_css($csspath);
  //$csspath = 'sites/all/libraries/datatables/extras/ColVis/media/css/ColVis.css';
  //drupal_add_css($csspath);
  $jspath = $jquery_path . '/replace/ui/ui/jquery-ui.js';
  drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
  _add_jeditable_plugins();
  $LevelStaff = array_staff_level();
  drupal_add_js(
    array(
      'level_staff' => $LevelStaff,
    )
    , 'setting');
  //$jspath = 'sites/all/libraries/datatables/extras/ColVis/media/js/ColVis.js';
  //drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
  $module_path = drupal_get_path('module', 'data_staff');
  $jspath = $module_path . '/js/list_staff.js';
  drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
  add_chosen_jquery_plugins();
  // Table settings.
  $attributes['datatable_options'] = array(
    'bFilter' => TRUE,
    'bInfo' => TRUE,
    'bStateSave' => TRUE,
    'sPaginationType' => 'full_numbers',
    'iDisplayLength' => 100,
    'aLengthMenu' => [[100, 250, 500, -1], [100, 250, 500, "All"]],
  );
  // Define table columns
  $header = array(
    array(
      'data' => t('ID Staff'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    array(
      'data' => t('Nama Lengkap'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    array(
      'data' => t('Nama Hijrah'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    array(
      'data' => t('Jantina'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    array(
      'data' => t('No. KTP/IC'),
      'class' => array('align-center'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    array(
      'data' => t('No. KK'),
      'class' => array('align-center'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    array(
      'data' => t('No. HP'),
      'class' => array('align-center'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    array(
      'data' => t('Alamat'),
      'class' => array('col-input-number align-center'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    array(
      'data' => t('Tgl. Lahir'),
      'class' => array('col-input-number align-center'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    array(
      'data' => t('Tempat Lahir'),
      'datatable_options' => array(
        'bSortable' => FALSE,
        'bSearchable' => FALSE,
      ),
    ),
    array(
      'data' => t('Umur'),
      'class' => array('col-input-number-small align-center'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    array(
      'data' => t('Suami/Istri'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    array(
      'data' => t('Anak'),
      'datatable_options' => array(
        'bSortable' => FALSE,
        'bSearchable' => FALSE,
      ),
    ),
    array(
      'data' => t('Ayah'),
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
      'data' => t('Kawasan'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    array(
      'data' => t('Zone'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
    array(
      'data' => t('Level'),
      'datatable_options' => array(
        'bSortable' => TRUE,
        'bSearchable' => TRUE,
      ),
    ),
  );
  $keuanganZone = cek_keuangan_zone();
  $userZone = null;
  if ($keuanganZone) {
    $userZone = get_user_zone();
  }
  $user_zon = null;
  if ($userZone[0]) {
    $user_zon = $userZone[1]['zone'];
    //$dataPremis = $userZone[1]['id_premis'];
  } else {
    $getDataZone = getZoneByCode();
    $dataPremis = get_data_premis_by_id();
    $newDataPremis = array();
    for ($i = 0; $i < count($dataPremis); $i++) {
      $newDataPremis[] = $dataPremis[$i]->id;
    }
    $dataPremis = $newDataPremis;
  }
  $namaZone = array();
  $listZone = getZoneByCode();
  if (count($listZone)) {
    for ($i = 0; $i < count($listZone); $i++) {
      if ($keuanganZone) {
        if (in_array($listZone[$i]->id, $user_zon)) {
          $namaZone[$listZone[$i]->id] = $listZone[$i]->zon_name;
        }
      } else {
        $namaZone[$listZone[$i]->id] = $listZone[$i]->zon_name;
      }
    }
  }
  $namaKawasan = array();
  /*if (count($namaZone)){
      foreach ($namaZone as $idZone => $zoneName){
          $dataKawasan = get_data_kawasan($idZone);
          if (count($dataKawasan)){
              for ($i = 0;$i < count($dataKawasan);$i++){
                $namaKawasan[$dataKawasan[$i]->id_kawasan] = $dataKawasan[$i]->kawasan;
              }
          }
      }
  }*/
  /*$dataStaff = array();
  for ($i = 0;$i < count($dataPremis);$i++){
      $ListStaff = get_data_staff_premis($dataPremis[$i],null,$whereClause);
      for ($j = 0;$j < count($ListStaff);$j++){
          $dataStaff[] = $ListStaff[$j];
      }
  }*/
  if (!empty($user_zon)){
    $dataStaff = get_data_staff($user_zon, false, null, $whereClause);
  }else {
    $dataStaff = get_data_staff(null, false, null, $whereClause);
  }
  $rows = array();
  $arrayJK = array_jenis_kelamin();
  $ArrayLevel = array_staff_level();
  $array_jawatan_premis = array_jabatan_premis();
  /*count($dataStaff)*/
  foreach ($dataStaff as $idStaff => $detailStaff) {
    $premisData = array();
    $premisData[] = array(
      'data' => $detailStaff->id_staff,
      'class' => 'edit-field',
      'id' => 'id_staff-' . $detailStaff->id_number,
    );
    $premisData[] = array(
      'data' => $detailStaff->nama_lengkap,
      'class' => 'edit-field',
      'id' => 'nama_lengkap-' . $detailStaff->id_number,
    );
    $premisData[] = array(
      'data' => $detailStaff->nama_hijrah,
      'class' => 'edit-field',
      'id' => 'nama_hijrah-' . $detailStaff->id_number,
    );
    if (isset($detailStaff->jantina) && isset($arrayJK[$detailStaff->jantina])) {
      $premisData[] = array(
        'data' => $arrayJK[$detailStaff->jantina],
        'class' => 'edit-jantina',
        'id' => 'jantina-' . $detailStaff->id_number . '-' . $detailStaff->jantina,
      );
    } else {
      $premisData[] = array(
        'data' => '-',
        'class' => 'edit-jantina',
        'id' => 'jantina-' . $detailStaff->id_number,
      );
    }
    $premisData[] = array(
      'data' => $detailStaff->no_ic,
      'class' => 'edit-field',
      'id' => 'no_ic-' . $detailStaff->id_number,
    );
    $premisData[] = array(
      'data' => $detailStaff->no_kk,
      'class' => 'edit-field',
      'id' => 'no_kk-' . $detailStaff->id_number,
    );
    $premisData[] = array(
      'data' => $detailStaff->no_hp,
      'class' => 'edit-field',
      'id' => 'no_hp-' . $detailStaff->id_number,
    );
    $premisData[] = array(
      'data' => $detailStaff->alamat,
      'class' => 'edit-alamat',
      'id' => 'alamat-' . $detailStaff->id_number,
    );
    $premisData[] = array(
      'data' => $detailStaff->tarikh_lahir,
      'class' => 'edit-tanggal align-center',
      'id' => 'tarikh_lahir-' . $detailStaff->id_number,
    );
    $premisData[] = array(
      'data' => $detailStaff->tempat_lahir,
      'class' => 'edit-field',
      'id' => 'tempat_lahir-' . $detailStaff->id_number,
    );
    $umur = 0;
    if (!empty($detailStaff->tarikh_lahir)) {
      $SplitTgl = explode('-', $detailStaff->tarikh_lahir);
      $umur = count_age($SplitTgl[2], $SplitTgl[1], $SplitTgl[0]);
    }
    $premisData[] = array(
      'data' => $umur,
      'class' => 'align-right',
      'id' => 'umur-' . $detailStaff->id_number,
    );
    if (!empty($detailStaff->id_suami)) {
      $dataSuami = get_data_staff(null, false, $detailStaff->id_suami);
      if (count($dataSuami)) {
        $namaSuami = $dataSuami->nama_lengkap;
      } else {
        $namaSuami = '-';
      }
    } else {
      if (!empty($detailStaff->nama_suami)) {
        $namaSuami = $detailStaff->nama_suami;
      } else {
        $namaSuami = '-';
      }
    }
    $DataAnak = '-';
    if ($detailStaff->jantina == 1) {
      $premisData[] = array(
        'data' => $namaSuami,
        'class' => 'select-suami',
        'id' => 'id_suami-' . $detailStaff->id_number,
      );
    } else {
      if ($umur > 17) {
        $DataIstri = get_data_staff_only_by_id($detailStaff->id_number, 'id_suami');
        $NamaIstri = '-';
        if (count($DataIstri)) {
          $NamaIstri = '<ul class="padding-left-15 margin-bottom-5">';
          $wrapper_anak = '<div id="list-anak-'.$detailStaff->id_number.'" class="list-anak">';
          for ($i = 0; $i < count($DataIstri); $i++) {
            $Istri = !empty($DataIstri[$i]->nama_lengkap) ? $DataIstri[$i]->nama_lengkap : $DataIstri[$i]->nama_hijrah;
            $NamaIstri .= '<li>' . $Istri . '</li>';
            $ListAnak = get_data_staff_only_by_id($DataIstri[$i]->id_number, 'id_ibu', 'ta', 'tarikh_lahir');
            if (count($ListAnak)) {
              if ($DataAnak == '-') {
                $DataAnak = '<h5>Ibu : ' . $Istri . '</h5><ol class="padding-left-15 margin-bottom-5">';
              } else {
                $DataAnak .= '<h5>Ibu : ' . $Istri . '</h5><ol class="padding-left-15 margin-bottom-5">';
              }
              for ($j = 0; $j < count($ListAnak); $j++) {
                $NamaAnak = !empty($ListAnak[$j]->nama_lengkap) ? $ListAnak[$j]->nama_lengkap : $ListAnak[$j]->nama_hijrah;
                $DataAnak .= '<li>' . $NamaAnak . '</li>';
              }
              $DataAnak .= '</ol>';
            }
          }
          if ($DataAnak != '-'){
            $DataAnak = $wrapper_anak.$DataAnak.'</div>';
          }
          $NamaIstri .= '</ul>';
        }
      } else {
        $NamaIstri = '-';
      }
      $premisData[] = $NamaIstri;
    }
    $anakIcon = '<i class="fa fa-user"></i>';
    if ($detailStaff->jantina == 1 && (!empty($detailStaff->id_suami) || !empty($detailStaff->nama_suami))) {
      $anakButtonVar = array(
        'element' => array(
          '#attributes' => array(
            'class' => array('btn-info', 'btn-xs', 'no-margin', 'add-anak', 'btn-block'),
            'id' => 'add-anak-' . $detailStaff->id_number,
            'name' => 'add-anak-' . $detailStaff->id_number,
            'onclick' => 'add_anak(\'' . $detailStaff->id_number . '\')',
          ),
          '#button_type' => 'button',
          '#value' => $anakIcon . ' ADD ANAK',
        )
      );
      $ShowAnakButtonVar = array(
        'element' => array(
          '#attributes' => array(
            'class' => array('btn-success', 'btn-xs', 'no-margin', 'show-anak', 'btn-block'),
            'id' => 'show-anak-' . $detailStaff->id_number,
          ),
          '#button_type' => 'button',
          '#value' => $anakIcon . ' SHOW ANAK',
        )
      );
      $ListAnak = get_data_staff_only_by_id($detailStaff->id_number, 'id_ibu', 'ta', 'tarikh_lahir');
      $DataAnak = '-';
      if (count($ListAnak)) {
        $DataAnak = '<ol id="list-anak-'.$detailStaff->id_number.'" class="padding-left-15 margin-bottom-5 list-anak">';
        for ($j = 0; $j < count($ListAnak); $j++) {
          $NamaAnak = !empty($ListAnak[$j]->nama_lengkap) ? $ListAnak[$j]->nama_lengkap : $ListAnak[$j]->nama_hijrah;
          $DataAnak .= '<li>' . $NamaAnak . '</li>';
        }
        $DataAnak .= '</ol>';
      }
      if($DataAnak != '-') {
        $anakButton = $DataAnak .'<div style="font-size: 3px;">&nbsp;</div>'.theme('button', $ShowAnakButtonVar).'<div style="font-size: 3px;">&nbsp;</div>'.theme('button', $anakButtonVar);
      }else{
        $anakButton = $DataAnak .'<div style="font-size: 3px;">&nbsp;</div>'.theme('button', $anakButtonVar);
      }
      $premisData[] = $anakButton;
    } else {
      $ShowAnakButtonVar = array(
        'element' => array(
          '#attributes' => array(
            'class' => array('btn-success', 'btn-xs', 'no-margin', 'show-anak', 'btn-block'),
            'id' => 'show-anak-' . $detailStaff->id_number,
          ),
          '#button_type' => 'button',
          '#value' => $anakIcon . ' SHOW ANAK',
        )
      );
      if($DataAnak != '-') {
        $anakButton = $DataAnak .'<div style="font-size: 3px;">&nbsp;</div>'.theme('button', $ShowAnakButtonVar);
      }else{
        $anakButton = $DataAnak;
      }
      $premisData[] = $anakButton;
    }
    if (!empty($dataStaff[$i]->id_ayah)) {
      $dataAyah = get_data_staff(null, false, $detailStaff->id_ayah);
      $namaAyah = $dataAyah->nama_lengkap;
    } else {
      if (!empty($detailStaff->nama_ayah)) {
        $namaAyah = $detailStaff->nama_ayah;
      } else {
        $namaAyah = '-';
      }
    }
    $premisData[] = $namaAyah;
    $related_premis = get_data_staff_premis(null,$detailStaff->id_number);
    $list_premis = '-';
    if (count($related_premis)) {
      $list_premis = '<ul>';
      foreach ($related_premis as $idx_premis => $premis){
        $list_premis .= '<li>'.$array_jawatan_premis[$premis->id_jawatan].' '.$premis->nama.'</li>';
      }
      $list_premis .= '</ul>';
    }
    $premisData[] = $list_premis;//$detailStaff->info_premis;
    //$premisData[] = $DataJawatan[$dataStaff[$i]->id_jawatan];
    $premisData[] = array(
      'data' => $detailStaff->kawasan,
      'class' => 'select-kawasan',
      'id' => 'id_kawasan-' . $detailStaff->id_number,
    );
    $premisData[] = array(
      'data' => $detailStaff->zon_name,
      'class' => 'select-zon',
      'id' => 'id_zon-' . $detailStaff->id_number,
    );
    $StaffLevel = isset($ArrayLevel[$detailStaff->staff_level]) ? $ArrayLevel[$detailStaff->staff_level] : '';
    $premisData[] = array(
      'data' => $StaffLevel,
      'class' => 'edit-level',
      'id' => 'staff_level-' . $detailStaff->id_number,
    );
    $rows[] = $premisData;
  }
  $variables = array(
    'attributes' => $attributes,
    'header' => $header,
    'rows' => $rows,
    'footer' => null,
  );
  $FormVar = array();
  $month = isset($_GET['month']) && !is_null($_GET['month']) ? $_GET['month'] : 0;
  $JenisKelamin = isset($_GET['jenis_kelamin']) && !is_null($_GET['jenis_kelamin']) ? $_GET['jenis_kelamin'] : -1;
  $UmurMin = isset($_GET['umur_min']) && !is_null($_GET['umur_min']) ? $_GET['umur_min'] : 0;
  $UmurMax = isset($_GET['umur_max']) && !is_null($_GET['umur_max']) ? $_GET['umur_max'] : 0;
  $FormVar['month'] = $month;
  $FormVar['alamat'] = 'masterdata/staff';
  //$FormVar['data_premis'] = $dataPremis;
  $FormVar['id_zon'] = $user_zon;
  $FormVar['jenis_kelamin'] = $JenisKelamin;
  $FormVar['umur_min'] = $UmurMin;
  $FormVar['umur_max'] = $UmurMax;
  $form = drupal_get_form('filter_staff_form', $FormVar);
  $FilterForm = drupal_render($form);
  $listStaff = theme('datatable', $variables);
  $button_group = '<div class="btn-group btn-group-sm" role="group" aria-label="Small button group">';
  $col_title = [
    'ID Staff','Nama Lengkap','Nama Hijrah','Jantina','No. KTP/IC','No. KK','No. HP','Alamat', 'Tgl. Lahir',
    'Tempat Lahir','Umur','Suami/Istri','Anak','Ayah','Premis','Kawasan','Zon','Level'
  ];
  for ($i = 0;$i < 18;$i++){
    $button_group .= '<button title="click to show or hide related column" id="column-'.$i.'" type="button" class="btn btn-secondary btn-show-hide">'.$col_title[$i].'</button>';
  }
  $button_group .= '</div>';
  return $FilterForm . $button_group . $listStaff;
}

function create_staff_form_header(){
  $tableHeader = array();
  $tableHeader[] = array(
    'data' => t('No.'),
    'class' => array(
      'col-number'
    ),
  );
  $tableHeader[] = t('ID STAFF');
  $tableHeader[] = t('NAMA LENGKAP');
  $tableHeader[] = t('JAWATAN');
  $tableHeader[] = t('JANTINA');
  $tableHeader[] = t('NO.IC / KTP');
  $tableHeader[] = t('TARIKH LAHIR');
  $tableHeader[] = t('TEMPAT LAHIR');
  $tableHeader[] = t('ZON');
  $tableHeader[] = t('KAWASAN');
  $tableHeader[] = t('PREMIS');
  return $tableHeader;
}
function create_staff_form_row()
{
  $tableRow = array();
  $tableRow['#tree'] = TRUE;
  $nextCounter = 1;
  //get zon base on login users
  $getDataZone = getZoneByCode();
  $keuanganZone = cek_keuangan_zone();
  $userZone = get_user_zone();
  $arrayZone = array();
  $arrayZone[0] = 'TIADA ZON';
  for ($i = 0; $i < count($getDataZone); $i++) {
    if ($userZone[0]) {
      if (in_array($getDataZone[$i]->id, $userZone[1]['zone'])) {
        $arrayZone[$getDataZone[$i]->id] = $getDataZone[$i]->zon_name;
      }
    } else {
      $arrayZone[$getDataZone[$i]->id] = $getDataZone[$i]->zon_name;
    }
  }
  //end get data zon
  $option_premis = get_data_premis_by_id(null,null,null,null,null, true);
  $option_premis[0] = 'TIADA PREMIS';
  $option_kawasan = get_data_kawasan(null, null, true);
  $option_kawasan[0] = 'TIADA KAWASAN';
  for ($i = 0; $i < 5; $i++) {
    $colData = array();
    $colData['no-' . $nextCounter] = array(
      '#type' => 'hidden',
      '#prefix' => ($nextCounter),
      '#attributes' => array(
        'class' => array('align-right'),
        'id' => 'no-' . $nextCounter,
        'outerclass' => array('align-right'),
      ),
      '#default_value' => '',
    );
    $colData['id_staff-' . $nextCounter] = array(
      '#type' => 'textfield',
      '#default_value' => '',
      '#attributes' => array('class' => array('id-staff')),
    );
    $colData['nama_lengkap-' . $nextCounter] = array(
      '#type' => 'textfield',
      '#default_value' => '',
      '#attributes' => array('class' => array('nama-lengkap')),
    );
    $colData['staff_level-' . $nextCounter] = array(
      '#type' => 'select',
      '#default_value' => 0,
      '#options' => array_staff_level(),
      '#select2' => array(
        'placeholder' => 'Pilih Jawatan Staff',
        'width' => '130px',
      ),
    );
    $colData['jantina-' . $nextCounter] = array(
      '#type' => 'select',
      '#default_value' => 3,
      '#options' => ['Laki-laki','Perempuan'],
      '#select2' => array(
        'placeholder' => 'Pilih Jantina',
        'width' => '130px',
      ),
    );
    $colData['no_ic-' . $nextCounter] = array(
      '#type' => 'textfield',
      '#default_value' => '',
    );
    $colData['tarikh_lahir-' . $nextCounter] = array(
      '#type' => 'textfield',
      '#default_value' => '',
      '#attributes' => array('class' => array('tarikh-lahir')),
    );
    $colData['tempat_lahir-' . $nextCounter] = array(
      '#type' => 'textfield',
      '#default_value' => '',
    );
    $colData['id_zon-' . $nextCounter] = array(
      '#type' => 'select',
      '#required' => TRUE,
      '#options' => $arrayZone,
      '#default_value' => 0,
      '#select2' => array(
        'placeholder' => 'Select Zone',
        'width' => '130px',
      ),
      '#attributes' => array('class' => array('select-zon')),
    );
    $colData['id_kawasan-' . $nextCounter] = array(
      '#type' => 'select',
      '#required' => TRUE,
      '#options' => $option_kawasan,
      '#default_value' => 0,
      '#select2' => array(
        'placeholder' => 'Select Kawasan',
        'width' => '130px',
      ),
      '#attributes' => array('class' => array('select-kawasan')),
    );
    $colData['id_premis-' . $nextCounter] = array(
      '#type' => 'select',
      '#required' => TRUE,
      '#options' => $option_premis,
      '#default_value' => 0,
      '#select2' => array(
        'placeholder' => 'Select Premis',
        'width' => '130px',
      ),
    );
    $tableRow['r' . $nextCounter] = $colData;
    $nextCounter++;
  }
  return $tableRow;
}
function input_staff_form($form, &$form_state, $variables = null)
{
  set_default_time_zone();
  $tableHeader = create_staff_form_header();
  $tableRow = create_staff_form_row();
  $tableFooter = array(create_staff_form_header());
  $form['basic'] = array(
    '#type' => 'fieldset',
    '#title' => 'FORM DATA STAFF',
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
    '#value' => t('SAVE DATA STAFF'),
  );
  return $form;
}
function input_data_staff(){
  $core_module_path = drupal_get_path('module','ikhwan_core');
  $csspath = $core_module_path.'/css/custom-style.css';
  drupal_add_css($csspath);
  $jquery_path = drupal_get_path('module','jquery_update');
  $csspath = $jquery_path.'/replace/ui/themes/base/jquery-ui.css';
  drupal_add_css($csspath);
  $jspath = $jquery_path . '/replace/ui/ui/jquery-ui.js';
  drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
  $module_path = drupal_get_path('module', 'data_staff');
  $jspath = $module_path . '/js/form_add_staff.js';
  drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
  $form = drupal_get_form('input_staff_form');
  $formStaff = drupal_render($form);
  return $formStaff;
}
function input_staff_form_submit($form, &$form_state){
  global $user;
  if (isset($form_state['values']['rows'])) {
    $values = $form_state['values']['rows'];
  } else {
    $values = $form_state['values'];
  }
  $returnData = array();
  if (count($values)) {
    $rowSaved = [];
    foreach ($values as $idx => $rowData) {
      if (count($rowData)){
        $savedData = [];
        $staff_premis = [];
        foreach ($rowData as $idxData => $colValues) {
          $splitData = explode('-', $idxData);
          if ($splitData[0] != 'no' && $splitData[0] != 'id_premis') {
            $savedData[$splitData[0]] = $colValues;
          }else if($splitData[0] == 'id_premis' && $colValues != ''){
            $staff_premis[$savedData['nama_lengkap']] = $colValues;
          }
        }
        if ($savedData['nama_lengkap'] != '') {
          $rowSaved[] = $savedData;
        }
      }
    }
    db_set_active('master');
    foreach ($rowSaved as $idx => $saved_data) {
      $returnData[$saved_data['nama_lengkap']] = saveTableData('master_data_staff', 'admin data staff', $saved_data, null);
    }
    if (count($staff_premis)){
      foreach ($staff_premis as $idx_nama => $id_premis){
        if (isset($returnData[$idx_nama]) && !empty($returnData[$idx_nama])){
          $saved_data_staff_premis = [];
          $saved_data_staff_premis['id_premis'] = $id_premis;
          $saved_data_staff_premis['id_staff'] = $returnData[$idx_nama];
          saveTableData('master_data_staff_premis', 'admin data premis', $saved_data_staff_premis, null);
        }
      }
    }
    db_set_active();
  }
  if (count($returnData)){
    drupal_set_message('Data Staff Berhasil Disimpan..!!');
  }
  return $returnData;
}

function delete_staff_data(){

}

function update_staff_data()
{
  db_set_active('master');
  if (isset($_REQUEST['id']) && !empty($_REQUEST['id']) && isset($_REQUEST['value'])) {
    $ArrayJK = array_jenis_kelamin();
    $LevelStaff = array_staff_level();
    $IdPost = explode('-', $_REQUEST['id']);
    $PostValue = $_REQUEST['value'];
    $TableName = 'master_data_staff';
    $PrimaryId = 'id_number';
    $SavedData[$IdPost[0]] = $PostValue;
    if ($IdPost[0] == 'id_kawasan'){
      $data_kawasan = get_data_kawasan(null, $PostValue);
      db_set_active('master');
      $SavedData['id_zon'] = $data_kawasan->id_zon;
    }
    saveTableData(
      $TableName, 'admin data staff',
      $SavedData, $PrimaryId, $IdPost[1]
    );
    if ($IdPost[0] == 'jantina') {
      $PostValue = $ArrayJK[$PostValue];
    } else if ($IdPost[0] == 'id_suami') {
      $DataSuami = get_data_staff_only_by_id($PostValue);
      if (count($DataSuami)) {
        $PostValue = $DataSuami[0]->nama_lengkap;
      }
    } else if ($IdPost[0] == 'staff_level') {
      $PostValue = $LevelStaff[$PostValue];
    } else if ($IdPost[0] == 'id_zon') {
      $data_zon = getZoneByCode($PostValue);
      $PostValue = $data_zon->zon_name;
    } else if ($IdPost[0] == 'id_kawasan') {
      $PostValue = $data_kawasan->kawasan;
    }
    db_set_active();
    print $PostValue;
    exit();
  }
}

function get_data_staff_by_id()
{
  db_set_active('master');
  $namaStaff = $_GET['term'];
  $JenisKelamin = null;
  if (isset($_GET['jk'])) {
    $JenisKelamin = $_GET['jk'];
  }
  $ChosenInput = false;
  if (isset($_GET['chosen_input'])) {
    $ChosenInput = true;
  }
  if (!empty($namaStaff)) {
    $fieldArray = array(
      'id_number', 'id_zon', 'zon', 'id_kawasan', 'id_staff', 'id_ayah', 'id_ibu', 'nama_lengkap', 'nama_hijrah',
      'jantina', 'tempat_lahir', 'tarikh_lahir', 'bangsa', 'negara', 'no_ic', 'no_kk', 'alamat',
      'no_hp', 'email', 'id_suami', 'nama_suami', 'nama_ayah', 'nama_ibu', 'created', 'changed',
      'uid', 'uid_changed', 'nama_sekolah', 'staff_level'
    );
    $conditionArray = array();
    $consData = new stdClass();
    $consData->fieldName = 'ta.nama_lengkap';
    $consData->value = '%' . $namaStaff . '%';
    $consData->operator = 'LIKE';
    $conditionArray[] = $consData;
    if ($JenisKelamin != null) {
      $consData = new stdClass();
      $consData->fieldName = 'ta.jantina';
      $consData->value = $JenisKelamin;
      $conditionArray[] = $consData;
    }
    $dataStaff = getTableDataByField('master_data_staff', 'access data staff', $fieldArray, 'nama_lengkap', null, null, null, $conditionArray);
    $maxView = count($dataStaff);
    if ($maxView > 50) {
      $maxView = 50;
    }
    for ($i = 0; $i < $maxView; $i++) {
      $items[] = array(
        'nama' => $dataStaff[$i]->nama_lengkap,
        'alamat' => $dataStaff[$i]->alamat,
        'telepon' => $dataStaff[$i]->no_hp,
        'id' => $dataStaff[$i]->id_number,
        'value' => $dataStaff[$i]->nama_lengkap,
        'tanggal_lahir' => $dataStaff[$i]->tarikh_lahir,
        'tempat_lahir' => $dataStaff[$i]->tempat_lahir,
        'jenis_kelamin' => $dataStaff[$i]->jantina,
        'nama_hijrah' => $dataStaff[$i]->nama_hijrah,
      );
    }
    db_set_active();
    header('Access-Control-Allow-Origin: *');
    echo json_encode($items);
    exit();
  } else {
    if ($ChosenInput) {
      $fieldArray = array(
        'id_number', 'nama_lengkap'
      );
      $conditionArray = null;
      if ($JenisKelamin != null) {
        $conditionArray = array();
        $consData = new stdClass();
        $consData->fieldName = 'ta.jantina';
        $consData->value = $JenisKelamin;
        $conditionArray[] = $consData;
      }
      $dataStaff = getTableDataByField('master_data_staff', 'access data staff', $fieldArray, 'nama_lengkap', null, null, null, $conditionArray);
      $ChosenData = array();
      for ($i = 0; $i < count($dataStaff); $i++) {
        $ChosenData[$dataStaff[$i]->id_number] = $dataStaff[$i]->nama_lengkap;
      }
      print json_encode($ChosenData);
      exit();
    }
  }
}
function get_data_staff_only_by_id($FieldValue = null, $FieldName = 'id_number', $TableAlias = 'ta', $OrderField = 'nama_lengkap', $WhereClause = null, $telegram_bot = false)
{
  db_set_active('master');
  $field_array = [
    'id_number', 'id_zon', 'zon', 'id_staff', 'id_ayah', 'id_ibu', 'nama_lengkap', 'nama_hijrah',
    'jantina', 'tempat_lahir', 'tarikh_lahir', 'bangsa', 'negara', 'no_ic', 'no_kk', 'alamat',
    'no_hp', 'email', 'id_suami', 'nama_suami', 'nama_ayah', 'nama_ibu', 'created', 'changed',
    'uid', 'uid_changed', 'nama_sekolah', 'staff_level', 'id_sekolah'
  ];
  $field_array2 = array(
    'id', 'zon_name',
  );
  $leftJoinArray = array(
    array(
      'tablename' => 'zons',
      'tablealias' => 'zons',
      'field_source' => 'id',
      'field_join' => 'id_zon',
      'fieldArray' => $field_array2,
    ),
  );
  $conditionArray = null;
  if (!empty($FieldValue)) {
    $conditionArray = array();
    $consData = new stdClass();
    $consData->fieldName = $TableAlias . '.' . $FieldName;
    $consData->value = $FieldValue;
    $conditionArray[] = $consData;
  }
  if ($telegram_bot) {
    $dataStaff = getTableDataByField(
      'master_data_staff', 'access telegram bot', $field_array, $OrderField, null, null,
      $leftJoinArray, $conditionArray, null, $WhereClause
    );
  } else {
    $dataStaff = getTableDataByField(
      'master_data_staff', 'access data staff', $field_array, $OrderField, null, null,
      $leftJoinArray, $conditionArray, null, $WhereClause
    );
  }
  db_set_active();
  return $dataStaff;
}

function filter_staff_form($form, &$form_state, $variables = null)
{
  global $user;
  if (!isset($variables['content'])) {
    $variables['content'] = t('Isi field sesuai keperluan pencarian dan tekan Show untuk melihat hasil pencarian');
  }
  $monthArray = array(
    0 => t('Tanpa filter milad'),
    1 => t('Januari'),
    2 => t('Februari'),
    3 => t('Maret'),
    4 => t('April'),
    5 => t('Mei'),
    6 => t('Juni'),
    7 => t('Juli'),
    8 => t('Agustus'),
    9 => t('September'),
    10 => t('Oktober'),
    11 => t('November'),
    12 => t('Desember'),
  );
  $form['info_content'] = array(
    '#type' => 'item',
    '#markup' => $variables['content'],
    '#prefix' => '<div>',
    '#suffix' => '</div>',
  );
  if (isset($variables['month'])) {
    $month = $variables['month'];
  } else {
    $month = 0;
  }
  if (isset($variables['alamat']) && !empty($variables['alamat'])) {
    $alamat = $variables['alamat'];
  } else {
    $alamat = 'masterdata/datastaff';
  }
  if (isset($variables['id_zon']) && !empty($variables['id_zon'])) {
    $Zons = $variables['id_zon'];
  } else {
    $Zons = 0;
  }
  $keuanganZone = cek_keuangan_zone();
  $userZone = null;
  if ($keuanganZone) {
    $userZone = get_user_zone();
  }
  $filtered_zon = null;
  if ($userZone[0]) {
    $filtered_zon = $userZone[1]['zone'];
    //$dataPremis = $userZone[1]['id_premis'];
  } else {
    $getDataZone = getZoneByCode();
    $dataPremis = get_data_premis_by_id();
    $newDataPremis = array();
    for ($i = 0; $i < count($dataPremis); $i++) {
      $newDataPremis[] = $dataPremis[$i]->id;
    }
    $dataPremis = $newDataPremis;
  }
  $AllZon = getZoneByCode();
  $ZonList = getZoneByCode($filtered_zon);
  $NewZone = array();
  if (!empty($ZonList) && !empty($AllZon) && count($ZonList) == count($AllZon)){
    $NewZone[0] = t('Seluruh Zon');
  }
  for ($i = 0; $i < count($ZonList); $i++) {
    $NewZone[$ZonList[$i]->id] = $ZonList[$i]->zon_name;
  }
  $form['#attributes'] = array('class' => array('form-inline'));
  $form['id_zon'] = array(
    '#type' => 'select',
    '#title' => t('Zon'),
    '#default_value' => $Zons,
    '#options' => $NewZone,
    '#multiple' => TRUE,
    '#select2' => array(
      'placeholder' => 'Pilih Zon Staff',
      'width' => '250px',
    ),
  );
  $form['month'] = array(
    '#type' => 'select',
    '#title' => t('Bulan'),
    '#default_value' => $month,
    '#options' => $monthArray,
    '#select2' => array(
      'placeholder' => 'Pilih Bulan Kelahiran/Milad',
      'width' => '100px',
    ),
  );
  $ArrJK = array_jenis_kelamin();
  $ArrJK[-1] = t('Semua');
  ksort($ArrJK);
  $JenisKelamin = isset($variables['jenis_kelamin']) && !is_null($variables['jenis_kelamin']) ? $variables['jenis_kelamin'] : -1;
  $form['jenis_kelamin'] = array(
    '#type' => 'select',
    '#title' => t('Jenis Kelamin'),
    '#default_value' => $JenisKelamin,
    '#options' => $ArrJK,
    '#select2' => array(
      'placeholder' => 'Pilih jenis kelamin',
      'width' => '100px',
    ),
  );
  $UmurMin = isset($variables['umur_min']) && !empty($variables['umur_min']) ? $variables['umur_min'] : 0;
  $form['umur_min'] = array(
    '#type' => 'textfield',
    '#title' => t('Umur Min'),
    '#default_value' => $UmurMin,
    '#size' => 5,
    '#maxlength' => 3,
  );
  $UmurMax = isset($variables['umur_max']) && !empty($variables['umur_max']) ? $variables['umur_max'] : 100;
  $form['umur_max'] = array(
    '#type' => 'textfield',
    '#title' => t('Umur Max'),
    '#default_value' => $UmurMax,
    '#size' => 5,
    '#maxlength' => 3,
  );
  $form['alamat'] = array(
    '#type' => 'hidden',
    '#default_value' => $alamat,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Show'),
    '#attributes' => array('class' => array('btn-sm btn-warning'), 'style' => 'margin: -8px 10px 0 !important;'),
  );
  return $form;
}

function filter_staff_form_submit($form, &$form_state){
    set_default_time_zone();
    $values = $form_state['values'];
    $QueryArr = array(
        'query' => array(
            'id_zon' => $values['id_zon'],
            'month' => $values['month'],
            'jenis_kelamin' => $values['jenis_kelamin'],
            'umur_min' => $values['umur_min'],
            'umur_max' => $values['umur_max'],
        )
    );
    drupal_goto($values['alamat'],$QueryArr);
}

function array_milad_staff($month = null, $OrderField = 'tanggal_lahir', $birth_date = null, $user_id = null, $telegram_bot =  false){
    if (!empty($month)) {
        $keuanganZone = cek_keuangan_zone($user_id);
        $userZone = null;
        if ($keuanganZone) {
            $userZone = get_user_zone($user_id, $telegram_bot);
        }
        if ($userZone[0]){
            //$getDataZone = $userZone[1]['zone'];
            $dataPremis = $userZone[1]['id_premis'];
        }else{
            $dataPremis = get_data_premis_by_id();
            $NewDataPremis = array();
            for ($i = 0;$i < count($dataPremis);$i++){
                $NewDataPremis[$i] = $dataPremis[$i]->id;
            }
            $dataPremis = $NewDataPremis;
        }
        $whereClause = array();
        $whereData = new stdClass();
        $whereData->clause = 'SUBSTRING(tanggal_lahir,6,2) = :arg';
        $whereData->value = array(':arg' => $month);
        $whereClause[] = $whereData;
        if (!empty($birth_date)){
            $whereData = new stdClass();
            $whereData->clause = 'SUBSTRING(tanggal_lahir,9,2) = :arg2';
            $whereData->value = array(':arg2' => $birth_date);
            $whereClause[] = $whereData;
        }
        $dataStaff = get_data_staff_premis($dataPremis, null, $whereClause, $OrderField, null, $telegram_bot);
        $newDataStaff = array();
        $DataJawatan = array_jabatan_premis();
        for ($i = 0;$i < count($dataStaff);$i++){
            if (!empty($dataStaff[$i]->tanggal_lahir)){
                $SplitTgl = explode('-',$dataStaff[$i]->tanggal_lahir);
                $UmurStaff = count_age($SplitTgl[2], $SplitTgl[1], $SplitTgl[0]);
                $dataStaff[$i]->umur = $UmurStaff;
            }
            if (isset($newDataStaff[$dataStaff[$i]->id_staff])) {
                $newDataStaff[$dataStaff[$i]->id_staff]->info_premis .= '<ul class="padding-left-15 margin-bottom-5"><li class="mdl-list__item">' . $DataJawatan[$dataStaff[$i]->id_jawatan];
                $newDataStaff[$dataStaff[$i]->id_staff]->info_premis .= ' ' . $dataStaff[$i]->nama . '</li></ul>';
            } else {
                $newDataStaff[$dataStaff[$i]->id_staff] = $dataStaff[$i];
                $newDataStaff[$dataStaff[$i]->id_staff]->info_premis = '<ul class="padding-left-15 margin-bottom-5"><li class="mdl-list__item">' . $DataJawatan[$dataStaff[$i]->id_jawatan];
                $newDataStaff[$dataStaff[$i]->id_staff]->info_premis .= ' ' . $dataStaff[$i]->nama . '</li></ul>';
            }
        }
        $dataStaff = $newDataStaff;
        return $dataStaff;
    }
}

function header_tabel_milad(){
    // Define table columns
    $header = array(
        array(
            'data' => t('No.'),
            'datatable_options' => array(
                'bSortable' => FALSE,
                'bSearchable' => FALSE,
            ),
        ),
        array(
            'data' => t('Nama Staff'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Nama Lengkap'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Nama Hijrah'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('JK'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Tgl. Lahir'),
            'class' => array('col-input-number align-center'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Tempat Lahir'),
            'datatable_options' => array(
                'bSortable' => FALSE,
                'bSearchable' => FALSE,
            ),
        ),
        array(
            'data' => t('Umur'),
            'class' => array('col-input-number-small align-center'),
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
            'data' => t('Negeri'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Zone'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
    );
    return $header;
}

function header_tabel_milad_anak(){
    // Define table columns
    $header = array(
        array(
            'data' => t('No.'),
            'datatable_options' => array(
                'bSortable' => FALSE,
                'bSearchable' => FALSE,
            ),
        ),
        array(
            'data' => t('Nama Anak'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Ayah'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Ibu'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('JK'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Tgl. Lahir'),
            'class' => array('col-input-number align-center'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Tempat Lahir'),
            'datatable_options' => array(
                'bSortable' => FALSE,
                'bSearchable' => FALSE,
            ),
        ),
        array(
            'data' => t('Umur'),
            'class' => array('col-input-number-small align-center'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Sekolah'),
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
            'data' => t('Zone'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
    );
    return $header;
}

function tabel_milad_staff($month = null){
    $header = header_tabel_milad();
    $attributes['datatable_options'] = array(
        'bFilter'   => TRUE,
        'bInfo'     => TRUE,
        'bPaginate' => FALSE,
        'bLengthChange' => FALSE,
    );
    if (empty($month)){
        $month = date('m');
    }
    $dataStaff = array_milad_staff($month);
    $arrayJK = array_jenis_kelamin();
    $DataPremis = get_data_premis_by_id();
    $ArrayPremis = array();
    for ($i = 0;$i < count($DataPremis);$i++){
        $ArrayPremis[$DataPremis[$i]->id] = $DataPremis[$i];
    }
    $counter = 0;
    $MiladStaff = array();
    foreach ($dataStaff as $idx => $detailStaff){
        $staffData = array();
        $staffData[] = $counter + 1;
        $staffData[] = $detailStaff->staff_nama;
        $staffData[] = $detailStaff->nama_lengkap;
        $staffData[] = $detailStaff->nama_hijrah;
        if (isset($detailStaff->jenis_kelamin) && isset($arrayJK[$detailStaff->jenis_kelamin])) {
            $staffData[] = $arrayJK[$detailStaff->jenis_kelamin];
        }else{
            $staffData[] = '-';
        }
        $staffData[] = $detailStaff->tanggal_lahir;
        $staffData[] = $detailStaff->tempat_lahir;
        $SplitTgl = explode('-',$detailStaff->tanggal_lahir);
        if ((int)$SplitTgl[2] > date('j')){
            $staffData[] = $detailStaff->umur + 1;
        }else{
            $staffData[] = $detailStaff->umur;
        }
        $staffData[] = $detailStaff->info_premis;
        $staffData[] = $detailStaff->negri_nama;
        $staffData[] = $detailStaff->tzone_nama;
        $rows[] = $staffData;
        $counter++;
        $MiladStaff[] = $detailStaff->id_staff;
    }
    $variables = array(
        'attributes' => $attributes,
        'header' => $header,
        'rows' => $rows,
        'footer' => null,
    );
    $listStaff = theme('datatable', $variables);
    $headerAnak = header_tabel_milad_anak();
    $dataAnak = data_anak_staff(true, $month);
    $ArrayZone = getZoneByCode();
    $DataZone = array();
    for ($i = 0;$i < count($ArrayZone);$i++){
        $DataZone[$ArrayZone[$i]->zone] = $ArrayZone[$i]->nama;
    }
    $rows = array();
    if (count($dataAnak)){
        $counter++;
        foreach ($dataAnak as $IdxIbu => $DetailAnak){
            $NamaAyah = $DetailAnak->ayah[0]->nama;
            $NamaIbu = $DetailAnak->ibu[0]->nama;
            if (count($DetailAnak->anak)){
                foreach ($DetailAnak->anak as $idxAnak => $InfoAnak){
                    if (!in_array($InfoAnak->id, $MiladStaff)) {
                        $anakData = array();
                        $anakData[] = $counter;
                        $anakData[] = $InfoAnak->nama;
                        $anakData[] = $NamaAyah;
                        $anakData[] = $NamaIbu;
                        if (isset($InfoAnak->jenis_kelamin) && isset($arrayJK[$InfoAnak->jenis_kelamin])) {
                            $anakData[] = $arrayJK[$InfoAnak->jenis_kelamin];
                        } else {
                            $anakData[] = '-';
                        }
                        $anakData[] = $InfoAnak->tanggal_lahir;
                        $anakData[] = $InfoAnak->tempat_lahir;
                        $SplitTgl = explode('-', $InfoAnak->tanggal_lahir);
                        if ((int)$SplitTgl[2] > date('j')) {
                            $anakData[] = $InfoAnak->umur + 1;
                        } else {
                            $anakData[] = $InfoAnak->umur;
                        }
                        if (!empty($InfoAnak->idsekolah) && isset($ArrayPremis[$InfoAnak->idsekolah])) {
                            $anakData[] = $ArrayPremis[$InfoAnak->idsekolah]->nama;
                            $anakData[] = $ArrayPremis[$InfoAnak->idsekolah]->negeri_nama;
                            if (isset($DataZone[$ArrayPremis[$InfoAnak->idsekolah]->zone])) {
                                $anakData[] = $DataZone[$ArrayPremis[$InfoAnak->idsekolah]->zone];
                            } else {
                                $anakData[] = '-';
                            }
                        } else {
                            $anakData[] = '-';
                            $anakData[] = '-';
                            $anakData[] = '-';
                        }
                        $rows[] = $anakData;
                        $counter++;
                    }
                }
            }
        }
        $variables = array(
            'attributes' => $attributes,
            'header' => $headerAnak,
            'rows' => $rows,
            'footer' => null,
            'table_tools' => true,
        );
        $listStaff .= theme('datatable', $variables);
    }
    return $listStaff;
}

function get_detail_staff_data($IdStaff = null){
    $DetailStaff = null;
    if (!empty($IdStaff)){
        $fieldArray = array(
            'id_staff','nama_lengkap','nama_hijrah','jenis_kelamin','no_ktp','no_kk',
            'tanggal_lahir','id_suami','id_ayah','nama_suami','nama_ayah','tempat_lahir',
            'id_ibu','idsekolah','nama_sekolah'
        );
        $conditionArray = null;
        if (!empty($IdStaff)){
            $conditionArray = array();
            $consData = new stdClass();
            $consData->fieldName = 'id_staff';
            $consData->value = $IdStaff;
            $conditionArray[] = $consData;
        }
        $dataStaff = getTableDataByField(
            'zdatastaff_detail','access data staff',$fieldArray,null,null,null,
            null,$conditionArray
        );
        if (count($dataStaff)){
            $DetailStaff = $dataStaff[0];
        }else{
            $DetailStaff = null;
        }
    }
    return $DetailStaff;
}

function server_side_data_staff($request){
    global $baseDirectory;
    $pageStart = $_GET['start'];
    $pageLength = $_GET['length'];
    $searchArray = $_REQUEST['search'];
    $searchQuery = $searchArray['value'];
    $arrayColumn = array(

    );
    $orderColumnArray = $_REQUEST['order'];
    $orderColumn = $arrayColumn[$orderColumnArray[0]['column']].' '.$orderColumnArray[0]['dir'];
    if (is_null($pageStart)){
        $pageStart = 0;
    }
    if (is_null($pageLength)){
        $pageLength = 25;
    }
    $firstRecord = $pageStart;
    $lastRecord = $pageStart + $pageLength;
    $strSQL = "SELECT plg.idpelanggan,plg.kodepelanggan,plg.namapelanggan,plg.telp,plg.alamat,plg.email,";
    $strSQL .= "plg.url_database, plg.username, plg.password, plg.status_pelanggan, ";
    $strSQL .= "ptg.besarhutang, ptg.pembayaranterakhir, SUBSTR(ptg.last_update,1,10) AS bayarterakhir ";
    $strSQL .= "FROM pelanggan AS plg ";
    $strSQL .= "LEFT JOIN piutang AS ptg ON ptg.idpelanggan = plg.idpelanggan WHERE 1=1 ";
    $strSQLFilteredTotal = "SELECT COUNT(plg.idpelanggan) ";
    $strSQLFilteredTotal .= "FROM pelanggan AS plg ";

    $strSQLFilteredTotal .= "LEFT JOIN piutang AS ptg ON ptg.idpelanggan = plg.idpelanggan WHERE 1=1 ";
    $strCriteria = "";
    if (!empty($searchQuery)){
        $strCriteria .= "AND (plg.kodepelanggan LIKE '%%%s%%' OR plg.namapelanggan LIKE '%%%s%%' ";
        $strCriteria .= "OR plg.alamat LIKE '%%%s%%' OR plg.email LIKE '%%%s%%')";
    }
    $strSQL .= $strCriteria." ORDER BY $orderColumn LIMIT %d, %d";
    $strSQLFilteredTotal .= $strCriteria;
    if (!empty($searchQuery)){
        $result = db_query($strSQL,$searchQuery,$searchQuery,$searchQuery,$searchQuery,$firstRecord,$lastRecord);
        $recordsFiltered = db_result(db_query($strSQLFilteredTotal,$searchQuery,$searchQuery,$searchQuery,$searchQuery));
    }else{
        $result = db_query($strSQL,$firstRecord,$lastRecord);
        $recordsFiltered = db_result(db_query($strSQLFilteredTotal));
    }
    $output = array();
    $StatusPelanggan = array('Eksternal','Internal');
    while ($data = db_fetch_object($result)){
        $rowData = array();
        $lihathutang = "<img title=\"Klik untuk melihat detail hutang\" src=\"$baseDirectory/misc/media/images/forward_enabled.ico\" onclick=\"view_detail_hutang(".$data->idpelanggan.",'".$data->namapelanggan."','".round($data->besarhutang)."');\">";
        $bayarhutang = "<img title=\"Klik untuk mengisi form pembayaran\" src=\"$baseDirectory/misc/media/images/money2_24.png\" onclick=\"pembayaran(".$data->idpelanggan.",'".$data->namapelanggan."','".$data->besarhutang."','".$data->besarhutang."');\">";
        $lihatdiskon = "<img title=\"Klik untuk melihat dan menambah diskon pelanggan\" src=\"$baseDirectory/misc/media/images/diskon.png\" onclick=\"tabeldiskon(".$data->idpelanggan.",'".$data->namapelanggan."')\">";
        $rowData[] = $lihathutang;
        $rowData[] = $bayarhutang;
        $rowData[] = $lihatdiskon;
        $rowData[] = $data->kodepelanggan;
        $rowData[] = $data->namapelanggan;
        $rowData[] = $data->telp;
        $rowData[] = $data->alamat;
        $rowData[] = $data->email;
        $rowData[] = $data->url_database;
        $rowData[] = $data->username;
        $rowData[] = $data->password;
        $rowData[] = number_format($data->besarhutang,0,",",".");
        $rowData[] = number_format($data->pembayaranterakhir,0,",",".");
        $rowData[] = $data->bayarterakhir;
        $rowData[] = $StatusPelanggan[$data->status_pelanggan];
        $rowData[] = $data->idpelanggan;
        $output[] = $rowData;
    }
    $recordsTotal = db_result(db_query("SELECT COUNT(idpelanggan) FROM pelanggan"));
    return array(
        "draw"            => isset ( $request['draw'] ) ?
            intval( $request['draw'] ) :
            0,
        "recordsTotal"    => intval( $recordsTotal ),
        "recordsFiltered" => intval( $recordsFiltered ),
        "data"            => $output
    );
}

function get_data_staff_milad_by_date($month = null, $birth_date = null, $user_id = null, $telegram_bot = false){
    date_default_timezone_set('Asia/Jakarta');
    if (empty($month) || empty($birth_date)){
        $month = date('m');
        $birth_date = date('d');
    }
    $dataStaff = array_milad_staff($month, 'tanggal_lahir', $birth_date, $user_id, $telegram_bot);
    $counter = 0;
    $StaffMilad = '';
    $MiladStaff = array();
    foreach ($dataStaff as $idx => $detailStaff){
        $NamaStaff = $detailStaff->nama_lengkap;
        if (!empty($detailStaff->nama_hijrah) && $detailStaff->nama_hijrah != '-'){
            $NamaStaff = $detailStaff->nama_hijrah;
        }
        if ($counter == 0) {
            $StaffMilad .= $NamaStaff;
        }else{
            $StaffMilad .= ', '.$NamaStaff;
        }
        $MiladStaff[] = $detailStaff->id_staff;
        $counter++;
    }
    $DataAnakStaff = data_anak_staff(true, $month, $birth_date, $user_id, $telegram_bot);
    $AnakMilad = '';
    if (count($DataAnakStaff)){
        $counter = 0;
        foreach ($DataAnakStaff as $IdxIbu => $DetailAnak){
            $NamaAyah = $DetailAnak->ayah[0]->nama;
            if (count($DetailAnak->anak)){
                foreach ($DetailAnak->anak as $idxAnak => $InfoAnak){
                    if (!in_array($InfoAnak->id, $MiladStaff)) {
                        $NamaAnak = $InfoAnak->nama;
                        if (isset($InfoAnak->jenis_kelamin)) {
                            if ($InfoAnak->jenis_kelamin == 0 && !empty($NamaAyah)){
                                $NamaAnak .= ' Bin '.$NamaAyah;
                            }else if ($InfoAnak->jenis_kelamin == 1 && !empty($NamaAyah)){
                                $NamaAnak .= ' Binti '.$NamaAyah;
                            }
                        }
                        if ($counter == 0){
                            $AnakMilad = $NamaAnak;
                        }else{
                            $AnakMilad .= ', '.$NamaAnak;
                        }
                        $counter++;
                    }
                }
            }
        }
    }
    if ($StaffMilad != '' || $AnakMilad != '') {
        $KataKataMilad = "Selamat bersyukur di hari milad ".date('d M Y').", kepada :  \n\n";
        if ($StaffMilad != ''){
            $KataKataMilad .= "*".$StaffMilad."*";
            $KataKataMilad .= "\n\n";
        }
        if ($AnakMilad != '' && $StaffMilad != '') {
            $KataKataMilad .= "dan kepada ananda";
            $KataKataMilad .= "\n\n";
            $KataKataMilad .= "*" . $AnakMilad . "*";
            $KataKataMilad .= "\n\n";
        }else if ($AnakMilad != '' && $StaffMilad == ''){
            $KataKataMilad .= "Ananda";
            $KataKataMilad .= "\n\n";
            $KataKataMilad .= "*" . $AnakMilad . "*";
            $KataKataMilad .= "\n\n";
        }
        $KataKataMilad .= "Semoga Allah terus memberkati kehidupannya, dipanjangkan umur di dalam keberkatan,";
        $KataKataMilad .= "mendapatkan hati ikhwan bersama PH. Semakin dipecutkan hati untuk dapat takutkan Allah ";
        $KataKataMilad .= "dan rindukan Nabi, diperkemaskan roh dan lahir dalam membantu  kemenangan Islam. Aamiin..";
        $KataKataMilad .= "\n\n";
        $KataKataMilad .= "Dgn keberkatan TDPMRAPDIGP";
    }else{
        $KataKataMilad = "Tidak ada staff yang milad hari ini";
    }
    return $KataKataMilad;
}
function get_data_staff_milad_by_date_ajax($month = null, $birth_date = null){
    if (empty($month) || empty($birth_date)){
        $month = date('m');
        $birth_date = date('d');
    }
    print get_data_staff_milad_by_date($month, $birth_date);
    exit();
}
