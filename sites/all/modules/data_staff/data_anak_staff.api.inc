<?php

function create_anak_staff_header(){
    $tableHeader = array();
    $tableHeader[] = array(
        'data' => t('No.'),
        'class' => array(
            'col-number'
        ),
    );
    $tableHeader[] = t('NAMA LENGKAP');
    $tableHeader[] = t('NAMA HIJRAH');
    $tableHeader[] = t('JK');
    $tableHeader[] = t('TGL LAHIR');
    $tableHeader[] = t('TEMPAT LAHIR');
    $tableHeader[] = t('UMUR');
    $tableHeader[] = t('SEKOLAH(JEMAAH)');
    $tableHeader[] = t('SEKOLAH(LUAR)');
    $tableHeader[] = t('DELETE');
    return $tableHeader;
}
function create_anak_staff_row($IdIbu = null){
    $tableRow = array();
    $tableRow['#tree'] = TRUE;
    $dataAnak = null;
    if (!empty($IdIbu)){
        $dataAnak = get_data_staff_only_by_id($IdIbu,'id_ibu','ta', 'tarikh_lahir');
    }
    $keuanganZone = cek_keuangan_zone();
    $userZone = null;
    if ($keuanganZone) {
        $userZone = get_user_zone();
    }
    if (isset($userZone[0])){
        $dataPremis = get_data_premis_by_id();
        $optionPremis = array();
        $optionPremis['0'] = '-';
        for ($i = 0;$i < count($dataPremis);$i++){
            $optionPremis[$dataPremis[$i]->id] = $dataPremis[$i]->nama;
        }
    }else{
        $dataPremis = get_data_premis_by_id();
        $optionPremis = array();
        $optionPremis[0] = '-';
        for ($i = 0;$i < count($dataPremis);$i++){
            $optionPremis[$dataPremis[$i]->id] = $dataPremis[$i]->nama;
        }
    }
    if (!is_null($dataAnak) && count($dataAnak)){
        for ($i = 0;$i < count($dataAnak);$i++){
            $IdStaff = $dataAnak[$i]->id_number;
            $colData = array();
            $colData['id-'.$IdStaff.'-edit'] = array(
                '#type' => 'hidden', '#prefix' => ($i + 1),
                '#attributes' => array(
                    'class' => array('align-right'),
                    'id' => 'nidstaff-'.$IdStaff,
                    'outerclass' => array('align-right'),
                ),
                '#default_value' => $IdStaff,
            );
            $colData['nama-'.$IdStaff.'-edit'] = array(
                '#type' => 'textfield',
                '#default_value' => $dataAnak[$i]->nama_lengkap,
                '#attributes' => array('class' => array('nama-staff')),
            );
            $colData['nama_hijrah-'.$IdStaff.'-edit'] = array(
                '#type' => 'textfield',
                '#default_value' => $dataAnak[$i]->nama_hijrah,
                '#attributes' => array('class' => array('nama-hijrah')),
            );
            $colData['jantina-'.$IdStaff.'-edit'] = array(
                '#type' => 'select',
                '#default_value' => $dataAnak[$i]->jantina,
                '#options' => array_jenis_kelamin(),
                '#select2' => array(
                    'placeholder' => t('Pilih Jenis Kelamin'),
                    'width' => '100px',
                ),
            );
            $colData['tarikh_lahir-'.$IdStaff.'-edit'] = array(
                '#type' => 'textfield',
                '#default_value' => $dataAnak[$i]->tarikh_lahir,
                '#attributes' => array('class' => array('tgl-lahir')),
            );
            $colData['tempat_lahir-'.$IdStaff.'-edit'] = array(
                '#type' => 'textfield',
                '#default_value' => $dataAnak[$i]->tempat_lahir,
                '#attributes' => array('class' => array('tempat-lahir')),
            );
            $UmurAnak = 0;
            if (!empty($dataAnak[$i]->tarikh_lahir)){
                $ExplodeTgl = explode('-',$dataAnak[$i]->tarikh_lahir);
                $UmurAnak = count_age($ExplodeTgl[2],$ExplodeTgl[1],$ExplodeTgl[0]);
            }
            $colData['umur-'.$IdStaff.'-edit'] = array(
                '#type' => 'item',
                '#title' => '<span id="umur-'.$IdStaff.'">'.$UmurAnak.'</span>',
                '#attributes' => array('outerclass' => array('align-right'), ),
            );
            $colData['id_sekolah-'.$IdStaff.'-edit'] = array(
                '#type' => 'select',
                '#default_value' => $dataAnak[$i]->id_sekolah,
                '#options' => $optionPremis,
                '#select2' => array(
                    'placeholder' => t('Pilih Sekolah Anak'),
                    'width' => '250px',
                ),
            );
            $colData['nama_sekolah-'.$IdStaff.'-edit'] = array(
                '#type' => 'textfield',
                '#default_value' => $dataAnak[$i]->nama_sekolah,
            );
            $colData['delete-'.$IdStaff] = array(
                '#type' => 'hidden',
                '#default_value' => 0,
                '#attributes' => array(
                    'id' => 'delete-'.$IdStaff,
                ),
                '#suffix' => '<input type="checkbox" id="checkdel-'.$IdStaff.'" value="1" class="checkdel">',
            );
            $tableRow['r'.($i + 1).'-'.$IdIbu] = $colData;
        }
        $nextCounter = $i + 1;
        for ($i = 0;$i < 3;$i++){
            $colData = array();
            $colData['id-new-'.$nextCounter] = array(
                '#type' => 'hidden', '#prefix' => ($nextCounter),
                '#attributes' => array(
                    'class' => array('align-right'),
                    'id' => 'nidstaff-'.$nextCounter,
                    'outerclass' => array('align-right'),
                ),
                '#default_value' => '',
            );
            $colData['nama-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#attributes' => array('class' => array('nama-staff')),
            );
            $colData['nama_hijrah-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#attributes' => array('class' => array('nama-hijrah')),
            );
            $colData['jantina-new-'.$nextCounter] = array(
                '#type' => 'select',
                '#options' => array_jenis_kelamin(),
                '#select2' => array(
                    'placeholder' => t('Pilih Jantina'),
                    'width' => '100px',
                ),
            );
            $colData['tarikh_lahir-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#attributes' => array('class' => array('tgl-lahir')),
            );
            $colData['tempat_lahir-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#attributes' => array('class' => array('tempat-lahir')),
            );
            $colData['umur-new-'.$nextCounter] = array(
                '#type' => 'item',
                '#title' => '<span id="umur-'.$nextCounter.'">0</span>',
                '#attributes' => array('outerclass' => array('align-right'),),
            );
            $colData['id_sekolah-new-'.$nextCounter] = array(
                '#type' => 'select',
                '#options' => $optionPremis,
                '#select2' => array(
                    'placeholder' => t('Pilih Sekolah Anak'),
                    'width' => '250px',
                ),
            );
            $colData['nama_sekolah-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#default_value' => '',
            );
            $tableRow['r'.$nextCounter.'-'.$IdIbu] = $colData;
            $nextCounter++;
        }
    }else{
        $nextCounter = 1;
        for ($i = 0;$i < 5;$i++){
            $colData = array();
            $colData['id-new-'.$nextCounter] = array(
                '#type' => 'hidden', '#prefix' => ($nextCounter),
                '#attributes' => array(
                    'class' => array('align-right'),
                    'id' => 'nidstaff-'.$nextCounter,
                    'outerclass' => array('align-right'),
                ),
                '#default_value' => '',
            );
            $colData['nama-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#attributes' => array('class' => array('nama-staff')),
            );
            $colData['nama_hijrah-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#attributes' => array('class' => array('nama-hijrah')),
            );
            $colData['jantina-new-'.$nextCounter] = array(
                '#type' => 'select',
                '#options' => array_jenis_kelamin(),
                '#select2' => array(
                    'placeholder' => t('Pilih Jantina'),
                    'width' => '100px',
                ),
            );
            $colData['tarikh_lahir-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#attributes' => array('class' => array('tgl-lahir')),
            );
            $colData['tempat_lahir-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#attributes' => array('class' => array('tempat-lahir')),
            );
            $colData['umur-new-'.$nextCounter] = array(
                '#type' => 'item',
                '#title' => '<span id="umur-'.$nextCounter.'">0</span>',
                '#attributes' => array(
                    'outerclass' => array('align-right'),
                ),
            );
            $colData['id_sekolah-new-'.$nextCounter] = array(
                '#type' => 'select',
                '#options' => $optionPremis,
                '#select2' => array(
                    'placeholder' => t('Pilih Sekolah Anak'),
                    'width' => '250px',
                ),
            );
            $colData['nama_sekolah-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#default_value' => '',
            );
            $tableRow['r'.$nextCounter.'-'.$IdIbu] = $colData;
            $nextCounter++;
        }
    }
    return $tableRow;
}
function premis_anak_staff_form($form, &$form_state, $variables = null)
{
  if (isset($variables['id_ibu']) && !empty($variables['id_ibu'])) {
    $tableHeader = create_anak_staff_header();
    $dataIbu = get_data_staff_only_by_id(null, false, $variables['id_ibu']);
    $dataAyah = get_data_staff_only_by_id(null, false, $dataIbu[0]->id_suami);
    $tableRow = create_anak_staff_row($variables['id_ibu']);
    $tableFooter = array(create_anak_staff_header());
    $form['id_zon_ibu'] = array(
      '#type' => 'hidden',
      '#default_value' => $dataIbu[0]->id_zon,
    );
    $form['basic'] = array(
      '#type' => 'fieldset',
      '#title' => 'DATA ANAK STAFF ' . $dataIbu[0]->nama_lengkap . ', AYAH : ' . $dataAyah[0]->nama_lengkap,
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
      '#value' => t('SAVE DATA ANAK'),
    );
  }
  return $form;
}
function add_anak_staff($IdIbu = null){
    $core_module_path = drupal_get_path('module','ikhwan_core');
    $csspath = $core_module_path.'/css/custom-style.css';
    drupal_add_css($csspath);
    $jquery_path = drupal_get_path('module','jquery_update');
    $csspath = $jquery_path.'/replace/ui/themes/base/jquery-ui.css';
    drupal_add_css($csspath);
    $jspath = $jquery_path . '/replace/ui/ui/jquery-ui.js';
    drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
    $module_path = drupal_get_path('module', 'data_staff');
    $jspath = $module_path . '/js/form_anak_staff.js';
    drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
    if (!empty($IdIbu)){
        $variables['id_ibu'] = $IdIbu;
        $form = drupal_get_form('premis_anak_staff_form',$variables);
        $formAnakStaff = drupal_render($form);
        return $formAnakStaff;
    }else{
        drupal_set_message(t('Mohon Tambah Anak Staff Dari Data Staff...!!!'));
        drupal_goto('masterdata/staff');
    }
}

function premis_anak_staff_form_submit($form, &$form_state)
{
  global $user;
  db_set_active('master');
  $id_zon_ibu = isset($form_state['values']['id_zon_ibu']) ? $form_state['values']['id_zon_ibu'] : 0;
  if (isset($form_state['values']['rows'])) {
    $values = $form_state['values']['rows'];
  } else {
    $values = $form_state['values'];
  }
  $returnData = array();
  if (count($values)) {
    foreach ($values as $idx => $rowData) {
      $SplitIdx = explode('-', $idx);
      $IdIbu = $SplitIdx[1];
      if (count($rowData)) {
        $StaffExist = false;
        $SavedData = array();
        $SavedDataDetail = array();
        $DeletedId = '';
        $DeletedNama = '';
        $InsertData = true;
        foreach ($rowData as $idxField => $FieldValue) {
          $SplitIdxField = explode('-', $idxField);
          if ($SplitIdxField[1] == 'new') {
            if ($SplitIdxField[0] == 'id') {
              if (!empty($FieldValue)) {
                $StaffExist = true;
                $SavedData['id_number'] = $FieldValue;
              }
            } else if ($SplitIdxField[0] != 'delete') {
              if ($SplitIdxField[0] == 'nama') {
                $SavedData['nama_lengkap'] = $FieldValue;
              } else {
                $SavedData[$SplitIdxField[0]] = $FieldValue;
              }
            }
          } else {
            if ($SplitIdxField[0] == 'delete') {
              if ($FieldValue == '1') {
                $DeletedId = $SplitIdxField[1];
                $InsertData = false;
              }
            } else {
              if ($SplitIdxField[0] == 'id_sekolah') {
                if ($FieldValue != null) {
                  $SavedData['id_sekolah'] = $FieldValue;
                }
              } else if ($SplitIdxField[0] == 'id') {
                $SavedData['id_number'] = $FieldValue;
              } else if ($SplitIdxField[0] == 'nama') {
                $DeletedNama = $FieldValue;
                $SavedData['nama_lengkap'] = $FieldValue;
                $StaffExist = true;
              }
            }
          }
        }
        if (count($SavedData) && $SavedData['nama_lengkap'] && $InsertData) {
          $SavedData['id_ibu'] = $IdIbu;
          if ($StaffExist) {
            $DataStaff = get_data_staff(null, false, $SavedData['id_number']);
            db_set_active('master');
            if (isset($DataStaff->id_number) && !empty($DataStaff->id_number)) {
              $DataStaffDetail = saveTableData(
                'master_data_staff', 'admin data staff',
                $SavedData, 'id_number', $SavedData['id_number']
              );
            } else {
              $SavedData['id_zon'] = $id_zon_ibu;
              $DataStaffDetail = saveTableData(
                'master_data_staff', 'admin data staff',
                $SavedData, null, null
              );
            }
            drupal_set_message('Data anak bernama : ' . $SavedData['nama_lengkap'] . ' berhasil diupdate');
          } else {
            unset($SavedData['id_number']);
            $SavedData['id_zon'] = $id_zon_ibu;
            $DataStaff = saveTableData(
              'master_data_staff', 'admin data staff',
              $SavedData,null,null,false
            );
            drupal_set_message('Penambahan data anak bernama : ' . $SavedData['nama_lengkap'] . ' berhasil');
          }
          $returnData[] = $DataStaff;
        }
        if (!empty($DeletedId)) {
          if (isset($SavedData['id_sekolah']) && !empty($SavedData['id_sekolah'])) {
            $conditionData = array();
            $consObj = new stdClass();
            $consObj->fieldName = 'id_number';
            $consObj->fieldValue = $DeletedId;
            $consObj->status = 'and';
            $conditionData[] = $consObj;
            deleteTableData('master_data_staff', 'admin data staff', $conditionData);
            drupal_set_message('Data anak bernama : ' . $DeletedNama . ' berhasil dihapus..!!!');
          } else {
            $SavedData['id_ibu'] = null;
            $DataStaff = saveTableData(
              'master_data_staff', 'admin data dtaff',
              $SavedData, 'id_number', $SavedData['id_number']
            );
            $returnData[] = $DataStaff;
            drupal_set_message('Data anak bernama : ' . $DeletedNama . ' berhasil dihapus dari daftar anak staff..!!!', 'error');
          }
        }
      }
    }
  }
  db_set_active();
  return $returnData;
}

function data_anak_staff($milad = false, $month = null, $birth_date = null, $user_id = null, $telegram_bot = false){
    $keuanganZone = cek_keuangan_zone($user_id);
    $userZone = null;
    if ($keuanganZone) {
        $userZone = get_user_zone($user_id, $telegram_bot);
    }
    if ($userZone[0]){
        $dataPremis = $userZone[1]['id_premis'];
    }else{
        $dataPremis = get_data_premis_by_id();
        $NewData = array();
        for ($i = 0;$i < count($dataPremis);$i++){
            $NewData[] = $dataPremis[$i]->id;
        }
        $dataPremis = $NewData;
    }
    $whereClause = array();
    $whereData = new stdClass();
    $whereData->clause = 'jenis_kelamin = :arg';
    $whereData->value = array(':arg' => 1);
    $whereClause[] = $whereData;
    $DataStaffPremis = get_data_staff_premis($dataPremis,null, $whereClause,'id_jawatan',null, $telegram_bot);
    $DataAnak = array();
    $whereClause = null;
    if ($milad){
        if (empty($month)) {
            $month = date('m');
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
    }
    for ($i = 0;$i < count($DataStaffPremis);$i++){
        $ArrayAnak = get_data_staff_only_by_id(
            $DataStaffPremis[$i]->id_staff,'id_ibu','detail', 'tanggal_lahir',$whereClause, $telegram_bot
        );
        $DataIbu = get_data_staff_only_by_id(
            $DataStaffPremis[$i]->id_staff,'id','ta','nama', null, $telegram_bot
        );
        $idSuami = $DataIbu[0]->id_suami;
        $DataSuami = null;
        if (!empty($idSuami)){
            $DataSuami = get_data_staff_only_by_id($idSuami,'id','ta','nama', null, $telegram_bot);
        }
        if (count($ArrayAnak)) {
            for ($j = 0;$j < count($ArrayAnak);$j++){
                if (!empty($ArrayAnak[$j]->tanggal_lahir)){
                    $SplitTgl = explode('-',$ArrayAnak[$j]->tanggal_lahir);
                    $UmurAnak = count_age($SplitTgl[2], $SplitTgl[1], $SplitTgl[0]);
                    $ArrayAnak[$j]->umur = $UmurAnak;
                }
            }
            $DataAnak[$DataStaffPremis[$i]->id_staff] = new stdClass();
            $DataAnak[$DataStaffPremis[$i]->id_staff]->ibu = $DataIbu;
            $DataAnak[$DataStaffPremis[$i]->id_staff]->ayah = $DataSuami;
            $DataAnak[$DataStaffPremis[$i]->id_staff]->anak = $ArrayAnak;
        }
    }
    return $DataAnak;
}

function header_tabel_anak_staff(){
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
function tabel_anak_staff(){
    $attributes['datatable_options'] = array(
        'bFilter'   => TRUE,
        'bInfo'     => TRUE,
        'bStateSave' => TRUE,
        'sPaginationType' => 'full_numbers',
    );
    $arrayJK = array_jenis_kelamin();
    $DataPremis = get_data_premis_by_id();
    $ArrayPremis = array();
    for ($i = 0;$i < count($DataPremis);$i++){
        $ArrayPremis[$DataPremis[$i]->id] = $DataPremis[$i];
    }
    $counter = 0;
    $headerAnak = header_tabel_anak_staff();
    $dataAnak = data_anak_staff();
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
                    $anakData = array();
                    $anakData[] = $counter;
                    $anakData[] = $InfoAnak->nama;
                    $anakData[] = $NamaAyah;
                    $anakData[] = $NamaIbu;
                    if (isset($InfoAnak->jenis_kelamin) && isset($arrayJK[$InfoAnak->jenis_kelamin])) {
                        $anakData[] = $arrayJK[$InfoAnak->jenis_kelamin];
                    }else{
                        $anakData[] = '-';
                    }
                    $anakData[] = $InfoAnak->tanggal_lahir;
                    $anakData[] = $InfoAnak->tempat_lahir;
                    $SplitTgl = explode('-',$InfoAnak->tanggal_lahir);
                    if ((int)$SplitTgl[2] > date('j')){
                        $anakData[] = $InfoAnak->umur + 1;
                    }else{
                        $anakData[] = $InfoAnak->umur;
                    }
                    if (!empty($InfoAnak->idsekolah) && isset($ArrayPremis[$InfoAnak->idsekolah])){
                        $anakData[] = $ArrayPremis[$InfoAnak->idsekolah]->nama;
                        $anakData[] = $ArrayPremis[$InfoAnak->idsekolah]->negeri_nama;
                        if (isset($DataZone[$ArrayPremis[$InfoAnak->idsekolah]->zone])){
                            $anakData[] = $DataZone[$ArrayPremis[$InfoAnak->idsekolah]->zone];
                        }else{
                            $anakData[] = '-';
                        }
                    }else{
                        $anakData[] = '-';
                        $anakData[] = '-';
                        $anakData[] = '-';
                    }
                    $rows[] = $anakData;
                    $counter++;
                }
            }
        }
        $variables = array(
            'attributes' => $attributes,
            'header' => $headerAnak,
            'rows' => $rows,
            'footer' => null,
        );
        $listAnakStaff = theme('datatable', $variables);
    }
    return $listAnakStaff;
}
