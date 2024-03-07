<?php

function array_jabatan_premis(){
    return array(
        'Pemantau', 'Pengurus','Wakil Pengurus','Staff','Pra-Staff','Karyawan','Kursus'
    );
}

function array_sektor_premis(){
    return array(
        'Bina Insan', 'Pendidikan','Ekonomi dan Perdagangan','Media',
        'Perkhidmatan','Pertanian dan Penternakan','Pentadbiran dan hubungan Awam'
    );
}

function check_detail_premis_exists($id_premis = null){
  $dataReturn = false;
  if (!empty($id_premis)) {
    db_set_active('master');
    $fieldArray = array(
      'id', 'telepon', 'whatsapp',
      'telegram', 'email', 'created', 'changed', 'uid', 'uid_changed',
      'currency'
    );
    $conditionArray = array();
    $consData = new stdClass();
    $consData->fieldName = 'ta.id';
    $consData->value = $id_premis;
    $conditionArray[] = $consData;
    $detailPremis = getTableDataByField(
      'master_data_premis_detail', 'access ikhwan data zone', $fieldArray,
      null, null, null, null, $conditionArray
    );
    db_set_active();
    if (count($detailPremis)){
      $dataReturn = true;
    }
  }
  return $dataReturn;
}
function list_premis($month = null, $year = null){
    global $user;
    if (function_exists('set_user_number_format')){
        set_user_number_format($desIn, $desOut, $separator);
    }else{
        $desIn = '.';
        $desOut = ',';
        $separator = '.';
    }
    if (!empty($month) && !empty($year)){
    }else{
        $month = date('n');
        $year = date('Y');
    }
    if (function_exists('get_total_setoran_premis')){
        $dataSetoran = get_total_setoran_premis($month, $year);
    }else{
        $dataSetoran = array();
    }
    if (function_exists('get_total_pengeluaran_oh_by_premis')){
        $dataPengeluaran = get_total_pengeluaran_oh_by_premis($month, $year);
    }else{
        $dataPengeluaran = array();
    }
    $intDate = mktime(7,0,0,$month,1,$year);
    $core_module_path = drupal_get_path('module','ikhwan_core');
    $csspath = $core_module_path.'/css/custom-style.css';
    drupal_add_css($csspath);
    _add_jeditable_plugins();
    $module_path  = drupal_get_path('module','data_premis');
    $jspath = $module_path.'/js/list_premis.js';
    drupal_add_js($jspath,array('scope' => 'footer', 'weight' => 5));
    // Table settings.
    $attributes['datatable_options'] = array(
        'bFilter'   => TRUE,
        'bInfo'     => TRUE,
        'bStateSave' => TRUE,
        'sPaginationType' => 'full_numbers',
        'footerCallback' => 'function(row, data, start, end, display){ alert(\'Test\'); }',
    );
    // Define table columns
    $header = array(
        array(
            'data' => t('Zone'),
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
            'data' => t('Nama'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Kategori'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Currency'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Setoran').' ('.date('M', $intDate).')',
            'class' => array('col-input-number align-center'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Pengeluaran').' ('.date('M', $intDate).')',
            'class' => array('col-input-number align-center'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Saldo').' ('.date('M', $intDate).')',
            'class' => array('col-input-number align-center'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Total OH'),
            'class' => array('col-input-number align-center'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Kekurangan'),
            'class' => array('col-input-number align-center'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Harian'),
            'class' => array('col-input-number-small align-center'),
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Edit'),
            'class' => array('col-number'),
            'datatable_options' => array(
                'bSortable' => FALSE,
                'bSearchable' => FALSE,
            ),
        ),
        array(
            'data' => t('Staff'),
            'class' => array('col-number'),
            'datatable_options' => array(
                'bSortable' => FALSE,
                'bSearchable' => FALSE,
            ),
        ),
        array(
            'data' => t('Overhead'),
            'class' => array('col-number'),
            'datatable_options' => array(
                'bSortable' => FALSE,
                'bSearchable' => FALSE,
            ),
        ),
        array(
            'data' => t('Setoran').' ('.date('M', $intDate).')',
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
    // Table data.
    $keuanganZone = cek_keuangan_zone();
    $userZone = null;
    if ($keuanganZone) {
        $userZone = get_user_zone();
    }
    if (count($userZone) && isset($userZone[0])){
        $getDataZone = $userZone[1]['zone'];
        $dataPremis = get_data_premis_by_id($getDataZone);
    }else{
        $getDataZone = getZoneByCode();
        $dataPremis = get_data_premis_by_id();
    }
    $namaZone = array();
    $listZone = getZoneByCode();
    $dataOverhead = get_data_overhead();
    $arrayOH = array();
    for ($i = 0;$i < count($dataOverhead);$i++){
        $arrayOH[] = $dataOverhead[$i]->id;
    }
    if (count($listZone)){
        for ($i = 0;$i < count($listZone);$i++){
            if ($keuanganZone){
                if (in_array($listZone[$i]->id, $getDataZone)){
                    $namaZone[$listZone[$i]->id] = $listZone[$i]->zon_name;
                }
            }else{
                $namaZone[$listZone[$i]->id] = $listZone[$i]->zon_name;
            }
        }
    }

    $rows = array();
    $totalSetoran = 0;
    $totalPengeluaran = 0;
    $totalSaldo = 0;
    $gtOverhead = 0;
    $gtOverheadHarian = 0;
    $totalKekurangan = 0;
    for ($i = 0;$i < count($dataPremis);$i++){
        $detailPremis = $dataPremis[$i];
        if (isset($detailPremis->id) && !empty($detailPremis->id)) {
            $dataStaff = get_data_staff_premis($detailPremis->id);
            $relatedStaff = array();
            $relatedStaff[] = 'UNIT';
            for ($j = 0;$j < count($dataStaff);$j++){
                $relatedStaff[] = $dataStaff[$j]->id;
            }
            $totalStaff = count($dataStaff);
            if ($totalStaff > 0) {
                $totalEntriedOH = db_query('SELECT COUNT(*) FROM {zoverhead_staff} WHERE id_premis = :id_premis', array(':id_premis' => $detailPremis->id))->fetchField();
                $totalSumOH = db_query(
                    'SELECT SUM(overhead_value) FROM {zoverhead_staff} WHERE id_premis = :id_premis
                    AND id_staff IN (:related_staff) AND id_overhead IN (:active_overhead)',
                    array(
                        ':id_premis' => $detailPremis->id,
                        ':related_staff' => $relatedStaff,
                        ':active_overhead' => $arrayOH,
                    )
                )->fetchField();
                $totalHarianOH = round($totalSumOH / 30, 0);
            }else{
                $totalEntriedOH = 0;
                $totalSumOH = 0;
                $totalHarianOH = 0;
            }
            if ($totalEntriedOH < 2){
                $badgesOH = '<span class="badge"><i class="fa fa-close" aria-hidden="true"></i></span>';
            }else{
                $badgesOH = '<span class="badge"><i class="fa fa-check" aria-hidden="true"></i></span>';
            }
            $premisData = array();
            if (isset($namaZone[$detailPremis->id_zon])) {
                $premisData[] = $namaZone[$detailPremis->id_zon];
            } else {
                $premisData[] = '-';
            }
            if (!empty($detailPremis->kawasan)){
                $premisData[] = array(
                    'data' => $detailPremis->kawasan,
                    'class' => 'edit-kawasan',
                    'id' => 'kawasan-'.$detailPremis->id_zon.'-'.$detailPremis->id,
                );
            }else{
                $premisData[] = array(
                    'data' => '-',
                    'class' => 'edit-kawasan',
                    'id' => 'kawasan-'.$detailPremis->id_zon.'-'.$detailPremis->id,
                );
            }
            $premisData[] = $detailPremis->nama;
            $premisData[] = $detailPremis->category_name;
            $premisData[] = $detailPremis->currency;
            if (isset($dataSetoran[$detailPremis->id])){
                $setoranPremis = $dataSetoran[$detailPremis->id]->total_setoran;
            }else{
                $setoranPremis = 0;
            }
            if (isset($dataPengeluaran[$detailPremis->id])) {
                $pengeluaranPremis = $dataPengeluaran[$detailPremis->id];
            }else{
                $pengeluaranPremis = 0;
            }
            $saldo = $setoranPremis - $pengeluaranPremis;
            $totalSetoran = $totalSetoran + $setoranPremis;
            $totalPengeluaran = $totalPengeluaran + $pengeluaranPremis;
            $totalSaldo = $totalSaldo + $saldo;
            $kekurangan = $totalSumOH - $pengeluaranPremis;
            $totalKekurangan = $totalKekurangan + $kekurangan;
            $premisData[] = '<div class="align-right">'.number_format($setoranPremis,0,$desOut,$separator).'</div>';
            $premisData[] = '<div class="align-right">'.number_format($pengeluaranPremis,0,$desOut,$separator).'</div>';
            $premisData[] = '<div class="align-right">'.number_format($saldo,0,$desOut,$separator).'</div>';
            $premisData[] = '<div class="align-right">'.number_format($totalSumOH,0,$desOut,$separator).'</div>';
            $premisData[] = '<div class="align-right">'.number_format($kekurangan,0,$desOut,$separator).'</div>';
            $gtOverhead = $gtOverhead + $totalSumOH;
            $premisData[] = '<div class="align-right">'.number_format($totalHarianOH,0,$desOut,$separator).'</div>';
            $gtOverheadHarian = $gtOverheadHarian + $totalHarianOH;
            $editIcon = '<i class="fa fa-edit"></i>';
            $editButtonVar = array(
                'element' => array(
                    '#attributes' => array(
                        'class' => array('btn-info', 'btn-xs', 'no-margin', 'edit-premis'),
                        'id' => 'edit-premis-' . $detailPremis->id,
                        'name' => 'edit-premis-' . $detailPremis->id,
                        'onclick' => 'edit_premis(\'' . $detailPremis->id . '\')',
                    ),
                    '#button_type' => 'button',
                    '#value' => $editIcon . ' EDIT',
                )
            );
            $editButton = theme('button', $editButtonVar);
            $premisData[] = $editButton;
            $addIcon = '<i class="fa fa-plus"></i>';
            $staffButtonVar = array(
                'element' => array(
                    '#attributes' => array(
                        'class' => array('btn-success', 'btn-xs', 'no-margin', 'add-staff'),
                        'id' => 'add-staff-' . $detailPremis->id,
                        'name' => 'add-staff-' . $detailPremis->id,
                        'onclick' => 'manage_staff(\'' . $detailPremis->id . '\')',
                    ),
                    '#button_type' => 'button',
                    '#value' => $addIcon . ' ADD STAFF&nbsp;&nbsp;&nbsp;&nbsp;<span class="badge">' . $totalStaff . '</span>',
                )
            );
            $staffButton = theme('button', $staffButtonVar);
            $premisData[] = $staffButton;
            $ohButtonVar = array(
                'element' => array(
                    '#attributes' => array(
                        'class' => array('btn-warning', 'btn-xs', 'no-margin', 'add-oh'),
                        'id' => 'add-oh-' . $detailPremis->id,
                        'name' => 'add-oh-' . $detailPremis->id,
                        'onclick' => 'overhead_premis(\'' . $detailPremis->id . '\')',
                    ),
                    '#button_type' => 'button',
                    '#value' => $addIcon . ' OVERHEAD&nbsp;&nbsp;'.$badgesOH,
                )
            );
            $ohButton = theme('button', $ohButtonVar);
            $premisData[] = $ohButton;
            $setoranButtonVar = array(
                'element' => array(
                    '#attributes' => array(
                        'class' => array('btn-primary', 'btn-xs', 'no-margin', 'add-oh'),
                        'id' => 'add-setoran-' . $detailPremis->id,
                        'name' => 'add-setoran-' . $detailPremis->id,
                        'onclick' => 'setoran_premis(\'' . $detailPremis->id . '\','.$month.','.$year.')',
                    ),
                    '#button_type' => 'button',
                    '#value' => $addIcon . ' '.t('SETORAN').'&nbsp;&nbsp;',
                )
            );
            $setoranButton = theme('button', $setoranButtonVar);
            $premisData[] = $setoranButton;
            $delIcon = '<i class="fa fa-trash-o"></i>';
            $delButtonVar = array(
                'element' => array(
                    '#attributes' => array(
                        'class' => array('btn-danger', 'btn-xs', 'no-margin', 'del-premis'),
                        'id' => 'del-premis-' . $detailPremis->id,
                        'name' => 'del-premis-' . $detailPremis->id,
                        'onclick' => 'delete_premis(\'' . $detailPremis->id . '\')',
                    ),
                    '#button_type' => 'button',
                    '#value' => $delIcon . ' HAPUS',
                )
            );
            if ($totalStaff <= 0) {
                $delButton = theme('button', $delButtonVar);
            } else {
                $delButton = '';
            }

            $premisData[] = $delButton;
            $rows[] = $premisData;
        }
    }
    $footer[] = array(
        array(
            'data' => '<strong>'.t('TOTAL').'</strong>',
            'datatable_options' => array(
                'bSortable' => TRUE,
                'bSearchable' => TRUE,
            ),
            'colspan' => 3,
            'class' => array('align-right'),
        ),
        array(
            'data' => number_format($totalSetoran,0,$desOut,$separator),
            'class' => array('col-input-number align-right'),
        ),
        array(
            'data' => number_format($totalPengeluaran,0,$desOut,$separator),
            'class' => array('col-input-number align-right'),
        ),
        array(
            'data' => number_format($totalSaldo,0,$desOut,$separator),
            'class' => array('col-input-number align-right'),
        ),
        array(
            'data' => number_format($gtOverhead,0,$desOut,$separator),
            'class' => array('col-input-number align-right'),
        ),
        array(
            'data' => number_format($totalKekurangan,0,$desOut,$separator),
            'class' => array('col-input-number align-right'),
        ),
        array(
            'data' => number_format($gtOverheadHarian,0,$desOut,$separator),
            'class' => array('col-input-number-small align-right'),
        ),
        array(
            'data' => '&nbsp;',
            'colspan' => 5,
        ),
    );
    // Or, render using a theme function.
    $variables = array(
        'attributes' => $attributes,
        'header' => $header,
        'rows' => $rows,
        'footer' => $footer,
    );
    $newPremisButtonVar = array(
        'element' => array(
            '#attributes' => array(
                'class' => array('btn-info btn-sm'),
                'id' => 'new-premis',
                'name' => 'new-premis',
            ),
            '#button_type' => 'button',
            '#value' => t('Tambah Data Premis'),
        )
    );
    $newPremisButton = theme('button', $newPremisButtonVar);
    $variables['content'] = t('Pilih Bulan dan Tahun Setoran & Pengeluaran, kemudian klik tombol show untuk melihat Setoran dan Pengeluaran');
    $variables['month'] = $month;
    $variables['year'] = $year;
    $variables['alamat'] = 'masterdata/premis';
    $form = drupal_get_form('filter_periode_form',$variables);
    $formSetoran = drupal_render($form);
    $listPremis = $newPremisButton.$formSetoran.theme('datatable', $variables);
    return $listPremis;
}

function form_add_premis($idPremis = null)
{
  $module_path = drupal_get_path('module', 'ikhwan_core');
  $csspath = $module_path . '/css/custom-style.css';
  drupal_add_css($csspath);
  $module_path = drupal_get_path('module', 'data_premis');
  $jspath = $module_path . '/js/form_premis.js';
  drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
  $getDataPremis = null;
  if (!empty($idPremis)) {
    $getDataPremis = get_data_premis_by_id(null, $idPremis);
  }
  if (empty($getDataPremis)) {
    $getDataPremis = new stdClass();
    $getDataPremis->id_zon = '';
    $getDataPremis->nama = '';
    $getDataPremis->id_kawasan = 0;
    $getDataPremis->id_sektor = 0;
    $getDataPremis->id_category = 0;
    $getDataPremis->currency = variable_get('google_currency_converter_to', '');
    $getDataPremis->alamat = '';
    $getDataPremis->telepon = '';
    $getDataPremis->whatsapp = '';
    $getDataPremis->bbm = '';
    $getDataPremis->telegram = '';
    $getDataPremis->email = '';
  }
  $variables = $getDataPremis;
  $form = drupal_get_form('form_data_premis', $variables);
  $formPremis = drupal_render($form);
  return $formPremis;
}

function get_data_premis_by_id($zone = null, $idpremis = null, $idkawasan = null, $sektor = null, $kategori = null, $option = false)
{
  global $user;
  $dataReturn = null;
  db_set_active('master');
  if (!empty($idpremis)) {
    $fieldArray = array(
      'id', 'id_zon', 'id_category', 'nama', 'alamat',
      'kawasan', 'latitude', 'longitude', 'id_sektor'
    );
    $fieldArray2 = array(
      'id', 'telepon', 'whatsapp', 'bbm',
      'telegram', 'email', 'created', 'changed', 'uid', 'uid_changed',
      'currency'
    );
    $conditionArray = array();
    $consData = new stdClass();
    $consData->fieldName = 'ta.id';
    $consData->value = $idpremis;
    if (is_array($idpremis)) {
      $consData->operator = 'IN';
    }
    $conditionArray[] = $consData;
    if ($sektor != null) {
      $consData = new stdClass();
      $consData->fieldName = 'ta.id_sektor';
      $consData->value = $sektor;
      if (is_array($sektor)) {
        $consData->operator = 'IN';
      }
      $conditionArray[] = $consData;
    }
    if ($kategori != null) {
      $consData = new stdClass();
      $consData->fieldName = 'ta.id_kategori';
      $consData->value = $kategori;
      if (is_array($kategori)) {
        $consData->operator = 'IN';
      }
      $conditionArray[] = $consData;
    }
    $leftJoinArray = array(
      array(
        'tablename' => 'master_data_premis_detail',
        'tablealias' => 'premis_detail',
        'field_source' => 'id',
        'field_join' => 'id',
        'fieldArray' => $fieldArray2,
      ),
      array(
        'tablename' => 'master_data_kawasan',
        'tablealias' => 'kawasan',
        'field_source' => 'id_kawasan',
        'field_join' => 'id_kawasan',
        'fieldArray' => array(
          'id_kawasan', 'kawasan', 'keterangan',
        ),
      ),
      array(
        'tablename' => 'master_project_category',
        'tablealias' => 'category',
        'field_source' => 'id',
        'field_join' => 'id_category',
        'fieldArray' => array(
          'id', 'category_name',
        ),
      ),
      array(
        'tablename' => 'zons',
        'tablealias' => 'zons',
        'field_source' => 'id',
        'field_join' => 'id_zon',
        'fieldArray' => array(
          'id', 'zon_name',
        ),
      ),
    );
    $dataPremis = getTableDataByField('master_data_premis', 'access data premis', $fieldArray, null, null, null, $leftJoinArray, $conditionArray);
    $dataReturn = $dataPremis;
  } else {
    $fieldArray = array(
      'id', 'id_zon', 'id_category', 'nama', 'alamat',
      'kawasan', 'latitude', 'longitude', 'id_sektor'
    );
    $fieldArray2 = array(
      'id', 'telepon', 'whatsapp', 'bbm',
      'telegram', 'email', 'created', 'changed', 'uid', 'uid_changed',
      'currency'
    );
    $leftJoinArray = array(
      array(
        'tablename' => 'master_data_premis_detail',
        'tablealias' => 'premis_detail',
        'field_source' => 'id',
        'field_join' => 'id',
        'fieldArray' => $fieldArray2,
      ),
      array(
        'tablename' => 'master_data_kawasan',
        'tablealias' => 'kawasan',
        'field_source' => 'id_kawasan',
        'field_join' => 'id_kawasan',
        'fieldArray' => array(
          'id_kawasan', 'kawasan', 'keterangan',
        ),
      ),
      array(
        'tablename' => 'master_project_category',
        'tablealias' => 'category',
        'field_source' => 'id',
        'field_join' => 'id_category',
        'fieldArray' => array(
          'id', 'category_name',
        ),
      ),
      array(
        'tablename' => 'zons',
        'tablealias' => 'zons',
        'field_source' => 'id',
        'field_join' => 'id_zon',
        'fieldArray' => array(
          'id', 'zon_name',
        ),
      ),
    );
    $conditionArray = null;
    if (!empty($zone)){
      $conditionArray = [];
      $consData = new stdClass();
      $consData->fieldName = 'ta.id_zon';
      $consData->value = $zone;
      if (is_array($zone)) {
        $consData->operator = 'IN';
      }
      $conditionArray[] = $consData;
    }
    if (!empty($idkawasan)){
      if (is_null($conditionArray)){
        $conditionArray = [];
      }
      $consData = new stdClass();
      $consData->fieldName = 'ta.id_kawasan';
      $consData->value = $idkawasan;
      if (is_array($idkawasan)) {
        $consData->operator = 'IN';
      }
      $conditionArray[] = $consData;
    }
    $dataPremis = getTableDataByField('master_data_premis', 'access data premis', $fieldArray, 'ta.nama', null, null, $leftJoinArray,$conditionArray);
    if (!empty($dataPremis)) {
      $dataReturn = $dataPremis;
    }
  }
  if ($option){
    $data_option = [];
    if (count($dataReturn)){
      foreach ($dataReturn as $idx => $data_premis){
        $data_option[$data_premis->id] = $data_premis->nama.' '.$data_premis->zon_name.' '.$data_premis->kawasan;
      }
      $dataReturn = $data_option;
    }
  }
  db_set_active();
  return $dataReturn;
}
function form_data_premis($form, &$form_state, $variables = null)
{
  global $user;
  $form['#attributes'] = array('class' => array('col-sm-12'));
  $form['basic'] = array(
    '#type' => 'fieldset',
    '#title' => t('Premis Info'),
    '#collapsible' => TRUE, // Added
    '#collapsed' => FALSE,  // Added
    '#prefix' => '<div class="col-md-6">',
  );
  $getDataZone = getZoneByCode();
  $keuanganZone = cek_keuangan_zone();
  $userZone = get_user_zone();
  $arrayZone = array();
  for ($i = 0; $i < count($getDataZone); $i++) {
    if ($userZone[0]) {
      if (in_array($getDataZone[$i]->id, $userZone[1]['zone'])) {
        $arrayZone[$getDataZone[$i]->id] = $getDataZone[$i]->zon_name;
      }
    } else {
      $arrayZone[$getDataZone[$i]->id] = $getDataZone[$i]->zon_name;
    }
  }
  if (count($arrayZone)) {
    $arrayNegeri = array();
    foreach ($arrayZone as $idZone => $namaZone) {
      $dataNegeri = get_data_negeri_by_id($idZone);
      if (count($dataNegeri)) {
        for ($i = 0; $i < count($dataNegeri); $i++) {
          $arrayNegeri[$dataNegeri[$i]->id] = $dataNegeri[$i]->nama;
        }
      }
    }
  }
  if (!empty($variables->id)) {
    $form['basic']['id'] = array(
      '#type' => 'hidden',
      '#default_value' => $variables->id,
    );
  }
  $form['basic']['zone'] = array(
    '#title' => t('Zone'),
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => $arrayZone,
    '#default_value' => $variables->id_zon,
    '#select2' => array(
      'placeholder' => 'Select Zone',
    ),
  );
  $option_kawasan = get_data_kawasan(null, null, true);
  $form['basic']['id_kawasan'] = array(
    '#title' => t('Kawasan'),
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => $option_kawasan,
    '#default_value' => $variables->id_kawasan,
    '#select2' => array(
      'placeholder' => t('Pilih Kawasan'),
    ),
  );
  $form['basic']['sektor_premis'] = array(
    '#title' => t('Sektor Premis'),
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => array_sektor_premis(),
    '#default_value' => $variables->id_sektor,
    '#select2' => array(
      'placeholder' => t('Pilih Sektor Premis'),
    ),
  );
  $option_kategori_projek = get_data_kategori_projek(null, true);
  $form['basic']['id_category'] = array(
    '#title' => t('Kategori'),
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => $option_kategori_projek,
    '#default_value' => $variables->id_category,
    '#select2' => array(
      'placeholder' => t('Pilih Kategori Premis'),
    ),
  );
  $form['basic']['nama'] = array(
    '#type' => 'textfield',
    '#title' => t('Nama Premis'),
    '#required' => TRUE,
    '#default_value' => $variables->nama,
  );
  $form['basic']['currency'] = array(
    '#type' => 'select',
    '#title' => t('Currency'),
    '#options' => google_currency_converter_country_list(),
    '#default_value' => $variables->currency,
    '#attributes' => array('class' => array('google-currency-converter-element')),
    '#required' => TRUE,
  );
  $form['basic']['alamat'] = array(
    '#title' => t('Alamat'),
    '#type' => 'textarea',
    '#default_value' => $variables->alamat,
  );
  $form['contact'] = array(
    '#type' => 'fieldset',
    '#title' => t('Premis Contact'),
    '#collapsible' => TRUE, // Added
    '#collapsed' => FALSE,  // Added
    '#prefix' => '</div><div class="col-md-6">',
  );
  $form['contact']['telepon'] = array(
    '#type' => 'textfield',
    '#title' => t('Telephone'),
    '#default_value' => $variables->telepon,
  );
  $form['contact']['whatsapp'] = array(
    '#type' => 'textfield',
    '#title' => t('Whatsapp'),
    '#default_value' => $variables->whatsapp,
  );
  $form['contact']['telegram'] = array(
    '#type' => 'textfield',
    '#title' => t('Telegram'),
    '#default_value' => $variables->telegram,
  );
  $form['contact']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#default_value' => $variables->email,
    '#suffix' => '</div>',
  );
  $form['saveButton'] = array(
    '#value' => t('Save Data Premis'),
    '#type' => 'submit',
    '#attributes' => array('class' => array('btn btn-primary')),
    '#prefix' => '<div class="col-md-12">',
    '#suffix' => '</div>',
  );
  return $form;
}

function form_data_premis_submit($form, &$form_state)
{
  global $user;
  db_set_active('master');
  $values = $form_state['values'];
  $savedData = array();
  $savedData['id_zon'] = $values['zone'];
  $savedData['id_kawasan'] = $values['id_kawasan'];
  $savedData['nama'] = $values['nama'];
  $savedData['alamat'] = $values['alamat'];
  $savedData['id_sektor'] = $values['sektor_premis'];
  $savedData['id_category'] = $values['id_category'];
  $savedDetail['telepon'] = $values['telepon'];
  $savedDetail['whatsapp'] = $values['whatsapp'];
  //$savedData['bbm'] = $values['bbm'];
  $savedDetail['telegram'] = $values['telegram'];
  $savedDetail['email'] = $values['email'];
  $savedDetail['currency'] = $values['currency'];
  if (isset($values['id']) && !empty($values['id'])) {
    if (!empty($savedData['nama'])) {
      $updatedData = saveTableData('master_data_premis', 'admin data premis', $savedData, 'id', $values['id'], false);
      $premis_exists = check_detail_premis_exists($values['id']);
      if ($premis_exists) {
        db_set_active('master');
        $savedDetail['uid_changed'] = $user->uid;
        $updatedDetail = saveTableData('master_data_premis_detail', 'admin data premis', $savedDetail, 'id', $values['id']);
      }else{
        db_set_active('master');
        $savedDetail['id'] = $values['id'];
        $savedDetail['uid'] = $user->uid;
        $insertDetail = saveTableData('master_data_premis_detail', 'admin data premis', $savedDetail, null, null);
      }
      $returnData = $updatedData;
      drupal_set_message("Data premis berhasil di update");
    }
    db_set_active();
    drupal_goto('masterdata/premis');
  } else {
    $insertedData = saveTableData('master_data_premis', 'admin data premis', $savedData, null, null, false );
    $returnData = $insertedData;
    $savedDetail['id'] = $insertedData;
    $insertDetail = saveTableData('master_data_premis_detail', 'admin data premis', $savedDetail, null, null);
    drupal_set_message("Data premis berhasil di simpan");
    db_set_active();
  }
  $fieldArray = array(
    'id', 'nama', 'related_uid', 'zone',
    'id_premis', 'uid', 'uid_changed', 'created', 'changed'
  );
  $userZonePremis = getTableDataByField(
    'zuser_zone', 'admin data premis',
    $fieldArray, 'nama', 'related_uid', $user->uid
  );
  if (count($userZonePremis)) {
    $premisData = explode(',', $userZonePremis[0]->id_premis);
    $premisData[] = $returnData['id'];
    $userPremisUpdate['id'] = $userZonePremis[0]->id;
    $userPremisUpdate['nama'] = $userZonePremis[0]->nama;
    $userPremisUpdate['related_uid'] = $userZonePremis[0]->related_uid;
    $userPremisUpdate['zone'] = $userZonePremis[0]->zone;
    $userPremisUpdate['id_premis'] = implode(',', $premisData);
    $userPremisUpdate['uid_changed'] = $user->uid;
    $userPremisUpdate['changed'] = time();
    saveTableData('zuser_zone', 'admin data premis', $userPremisUpdate, 'id', $userPremisUpdate['id']);
  }
  return $returnData;
}
function get_data_staff_premis($idPremis = null, $idStaff = null, $whereClause = null, $orderBy = 'ta.id_premis', $rangeData = null, $telegram_bot = false)
{
  db_set_active('master');
  $dataStaff = null;
  $leftJoinArray = array(
    array(
      'tablename' => 'master_data_premis',
      'tablealias' => 'premis',
      'field_source' => 'id',
      'field_join' => 'id_premis',
      'fieldArray' => array(
        'id', 'nama', 'id_zon', 'id_kawasan', 'id_category', 'id_sektor'
      ),
    ),
    array(
      'tablename' => 'master_data_kawasan',
      'tablealias' => 'kawasan',
      'sourcealias' => 'premis',
      'field_source' => 'id_kawasan',
      'field_join' => 'id_kawasan',
      'fieldArray' => array(
        'kawasan',
      ),
    ),
    array(
      'tablename' => 'zons',
      'tablealias' => 'tzone',
      'sourcealias' => 'premis',
      'field_source' => 'id',
      'field_join' => 'id_zon',
      'fieldArray' => array(
        'zon_name',
      ),
    ),
    array(
      'tablename' => 'master_data_staff',
      'tablealias' => 'staff',
      'field_source' => 'id_number',
      'field_join' => 'id_staff',
      'fieldArray' => array(
        'id_number', 'nama_lengkap', 'no_ic', 'tarikh_lahir', 'tempat_lahir', 'no_hp',
        'staff_level','alamat','email'
      ),
    ),
  );
  $AddExpression = array();
  $Exxpresion = new stdClass();
  $Exxpresion->clause = 'TIMESTAMPDIFF(YEAR,tarikh_lahir,CURDATE())';
  $Exxpresion->field_alias = 'umur_staff';
  $AddExpression[] = $Exxpresion;
  $fieldArray = array(
    'id_premis', 'id_staff', 'id_jawatan'
  );
  $conditionArray = null;
  if (!empty($idPremis)) {
    $conditionArray = array();
    $consData = new stdClass();
    $consData->fieldName = 'ta.id_premis';
    $consData->value = $idPremis;
    if (is_array($idPremis)) {
      $consData->operator = 'IN';
    }
    $conditionArray[] = $consData;
  }
  if (!empty($idStaff)) {
    if (empty($conditionArray)) {
      $conditionArray = array();
    }
    $consData = new stdClass();
    $consData->fieldName = 'ta.id_staff';
    $consData->value = $idStaff;
    if (is_array($idStaff)) {
      $consData->operator = 'IN';
    }
    $conditionArray[] = $consData;
  }
  if ($telegram_bot) {
    $dataStaff = getTableDataByField('master_data_staff_premis', 'access telegram bot',
      $fieldArray, $orderBy, null, null, $leftJoinArray, $conditionArray, $rangeData,
      $whereClause, $AddExpression
    );
  } else {
    $dataStaff = getTableDataByField('master_data_staff_premis', 'access data premis',
      $fieldArray, $orderBy, null, null, $leftJoinArray, $conditionArray, $rangeData,
      $whereClause, $AddExpression
    );
  }
  db_set_active();
  return $dataStaff;
}
function create_staff_premis_header(){
    $tableHeader = array();
    $tableHeader[] = array(
        'data' => t('No.'),
        'class' => array(
            'col-number'
        ),
    );
    $tableHeader[] = t('NAMA');
    $tableHeader[] = t('JAWATAN');
    $tableHeader[] = t('ALAMAT');
    $tableHeader[] = t('TELEPON');
    $tableHeader[] = t('EMAIL');
    $tableHeader[] = t('DELETE');
    return $tableHeader;
}
function create_staff_premis_row($idpremis = null)
{
  $tableRow = array();
  $tableRow['#tree'] = TRUE;
  $dataStaff = null;
  if (!empty($idpremis)) {
    $dataStaff = get_data_staff_premis($idpremis);
  }
  if (!is_null($dataStaff) && count($dataStaff)) {
    $nextCounter = 1;
    for ($i = 0; $i < count($dataStaff); $i++) {
      $IdStaff = $dataStaff[$i]->id_staff;
      $colData = array();
      $colData['idstaff-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'hidden',
        '#prefix' => ($i + 1),
        '#attributes' => array(
          'class' => array('align-right'),
          'id' => 'nidstaff-' . $nextCounter . '-' . $idpremis,
          'outerclass' => array('align-right'),
        ),
        '#default_value' => $IdStaff,
      );
      $colData['namalengkap-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'textfield',
        '#default_value' => $dataStaff[$i]->nama_lengkap,
        '#attributes' => array('class' => array('nama-staff')),
      );
      $colData['idjawatan-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'select',
        '#default_value' => $dataStaff[$i]->id_jawatan,
        '#options' => array_jabatan_premis(),
        '#select2' => array(
          'placeholder' => 'Pilih Jawatan',
          'width' => '130px',
        ),
      );
      $colData['alamat-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'textfield',
        '#default_value' => $dataStaff[$i]->alamat,
      );
      $colData['nohp-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'textfield',
        '#default_value' => $dataStaff[$i]->no_hp,
      );
      $colData['email-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'textfield',
        '#default_value' => $dataStaff[$i]->email,
      );
      $colData['delete-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'hidden',
        '#default_value' => 0,
        '#attributes' => array(
          'id' => 'delete-' . $nextCounter . '-' . $idpremis,
        ),
        '#suffix' => '<input type="checkbox" id="checkdel-' . $nextCounter . '-' . $idpremis . '" value="1" class="checkdel">',
      );
      $tableRow['r' . ($i + 1)] = $colData;
    }
    $nextCounter = $i + 1;
    for ($i = 0; $i < 3; $i++) {
      $colData = array();
      $colData['idstaff-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'hidden',
        '#prefix' => ($nextCounter),
        '#attributes' => array(
          'class' => array('align-right'),
          'id' => 'nidstaff-' . $nextCounter . '-' . $idpremis,
          'outerclass' => array('align-right'),
        ),
        '#default_value' => '',
      );
      $colData['namalengkap-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'textfield',
        '#default_value' => '',
        '#attributes' => array('class' => array('nama-staff')),
      );
      $colData['idjawatan-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'select',
        '#default_value' => 3,
        '#options' => array_jabatan_premis(),
        '#select2' => array(
          'placeholder' => 'Pilih Jawatan',
          'width' => '130px',
        ),
      );
      $colData['alamat-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'textfield',
        '#default_value' => '',
      );
      $colData['nohp-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'textfield',
        '#default_value' => '',
      );
      $colData['email-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'textfield',
        '#default_value' => '',
      );
      $tableRow['r' . $nextCounter] = $colData;
      $nextCounter++;
    }
  } else {
    $nextCounter = 1;
    for ($i = 0; $i < 5; $i++) {
      $colData = array();
      $colData['idstaff-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'hidden',
        '#prefix' => ($nextCounter),
        '#attributes' => array(
          'class' => array('align-right'),
          'id' => 'nidstaff-' . $nextCounter . '-' . $idpremis,
          'outerclass' => array('align-right'),
        ),
        '#default_value' => '',
      );
      $colData['namalengkap-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'textfield',
        '#default_value' => '',
        '#attributes' => array('class' => array('nama-staff')),
      );
      $colData['idjawatan-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'select',
        '#default_value' => 3,
        '#options' => array_jabatan_premis(),
        '#select2' => array(
          'placeholder' => 'Pilih Jawatan',
          'width' => '130px',
        ),
      );
      $colData['alamat-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'textfield',
        '#default_value' => '',
      );
      $colData['nohp-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'textfield',
        '#default_value' => '',
      );
      $colData['email-' . $nextCounter . '-' . $idpremis] = array(
        '#type' => 'textfield',
        '#default_value' => '',
      );
      $tableRow['r' . $nextCounter] = $colData;
      $nextCounter++;
    }
  }
  return $tableRow;
}
function premis_staff_form($form, &$form_state, $variables = null)
{
  set_default_time_zone();
  if (isset($variables['idpremis']) && !empty($variables['idpremis'])) {
    $tableHeader = create_staff_premis_header();
    $dataPremis = get_data_premis_by_id(null, $variables['idpremis']);
    $tableRow = create_staff_premis_row($variables['idpremis']);
    $tableFooter = array(create_staff_premis_header());
    $form['basic'] = array(
      '#type' => 'fieldset',
      '#title' => 'DATA STAFF PREMIS ' . $dataPremis[0]->nama,
      '#collapsible' => FALSE, // Added
      '#collapsed' => FALSE,  // Added
    );
    $form['basic']['id_premis'] = array(
      '#type' => 'hidden',
      '#default_value' => $variables['idpremis'],
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
  }
  return $form;
}
function add_premis_staff($idPremis = null){
    $core_module_path = drupal_get_path('module','ikhwan_core');
    $csspath = $core_module_path.'/css/custom-style.css';
    drupal_add_css($csspath);
    $jquery_path = drupal_get_path('module','jquery_update');
    $csspath = $jquery_path.'/replace/ui/themes/base/jquery-ui.css';
    drupal_add_css($csspath);
    $jspath = $jquery_path . '/replace/ui/ui/jquery-ui.js';
    drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
    $module_path = drupal_get_path('module', 'data_premis');
    $jspath = $module_path . '/js/form_staff_premis.js';
    drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
    if (!empty($idPremis)){
        $variables['idpremis'] = $idPremis;
        $form = drupal_get_form('premis_staff_form',$variables);
        $formStaff = drupal_render($form);
        return $formStaff;
    }else{
        drupal_set_message(t('Mohon Tambah Staff Dari Data Premis...!!!'));
        drupal_goto('masterdata/premis');
    }
}
function premis_staff_form_submit($form, &$form_state)
{
  global $user;
  db_set_active('master');
  $id_premis = $form_state['values']['id_premis'];
  if (isset($form_state['values']['rows'])) {
    $values = $form_state['values']['rows'];
  }
  $rowData = [];
  $returnData = [];
  if (count($values)) {
    $conditionData = [];
    $consObj = new stdClass();
    $consObj->fieldName = 'id_premis';
    $consObj->fieldValue = $id_premis;
    $consObj->status = 'and';
    $conditionData[] = $consObj;
    deleteTableData('master_data_staff_premis', 'admin data premis', $conditionData);
    foreach ($values as $idx => $staff_data){
      $savedData = [];
      foreach ($staff_data as $field_name => $field_value){
        $split_data = explode('-', $field_name);
        if ($split_data[0] == 'idstaff') {
            $savedData['id_staff'] = (int)$field_value;
        } else if ($split_data[0] == 'idjawatan') {
            $savedData['id_jawatan'] = (int)$field_value;
        }
      }
      if (!empty($savedData['id_staff'])) {
        $savedData['id_premis'] = (int)$id_premis;
        $rowData[] = $savedData;
      }
    }
    if (count($rowData)) {
      foreach ($rowData as $idx => $saved_data){
        $returnData[] = saveTableData(
          'master_data_staff_premis', 'admin data premis',
          $saved_data, null, null, false
        );
      }
    }
  }
  db_set_active();
  return $returnData;
}
function premis_staff_form_submit_original($form, &$form_state){
    global $user;
    if (isset($form_state['values']['rows'])) {
        $values = $form_state['values']['rows'];
    } else {
        $values = $form_state['values'];
    }
    $returnData = array();
    if (count($values)) {
        foreach ($values as $idx => $rowData) {
            if (count($rowData)){
                $savedData = array();
                $deletedStaffPremisID = null;
                foreach ($rowData as $idxData => $colValues){
                    $splitData = explode('-',$idxData);
                    if ($splitData[1] == 'new'){
                        if ($splitData[0] == 'id' && !empty($colValues)) {
                            $savedData[$splitData[0]] = $colValues;
                        }else if($splitData[0] == 'id_jawatan'){
                            $IdJawatan = $colValues;
                        }else if($splitData[0] != 'id' && $splitData[0] != 'id_jawatan' && $splitData[0] != 'delete'){
                            $savedData[$splitData[0]] =  $colValues;
                        }else if($splitData[0] == 'delete' && !empty($colValues)){
                            $deletedStaffPremisID = $splitData[1];
                        }
                        $IdPremis =  $splitData[3];
                    }else{
                        $IdPremis =  $splitData[2];
                        if ($splitData[0] == 'id' && !empty($colValues)){
                            $savedData['id'] =  $splitData[1];
                            if ($colValues != $splitData[1]){
                                $savedData['id'] = $colValues;
                                $deletedStaffPremisID = $splitData[1];
                            }else{
                                $dataStaff = get_data_staff_premis($IdPremis, $splitData[1]);
                                if ($dataStaff[0]->staff_nama != $rowData['nama-'.$splitData[1].'-'.$splitData[2].'-edit'] && !empty($rowData['nama-'.$splitData[1].'-'.$splitData[2].'-edit'])){
                                    $deletedStaffPremisID = $savedData['id'];
                                    unset($savedData['id']);
                                }
                            }
                        }else if($splitData[0] == 'id_jawatan'){
                            $IdJawatan = $colValues;
                        }else if($splitData[0] != 'id' && $splitData[0] != 'id_jawatan' && $splitData[0] != 'delete'){
                            $savedData[$splitData[0]] =  $colValues;
                        }else if($splitData[0] == 'delete' && !empty($colValues)){
                            $deletedStaffPremisID = $splitData[1];
                        }
                    }
                }
                if (!isset($savedData['id'])){
                    if (isset($savedData['nama']) && !empty($savedData['nama']) ) {
                        $NewDataStaff = saveTableData(
                            'zdatastaff', 'admin data premis',
                            $savedData, 'id'
                        );
                        $StaffPremis = array();
                        $StaffPremis['id_staff'] = $NewDataStaff['id'];
                        $StaffPremis['id_premis'] = $IdPremis;
                        $StaffPremis['id_jawatan'] = $IdJawatan;
                        $NewStaffPremis = saveTableData(
                            'zdatapremis_staff', 'admin data premis',
                            $StaffPremis
                        );
                        $returnData[] = $NewDataStaff;
                        $returnData[] = $NewStaffPremis;
                    }
                }else{
                    if ($savedData['id'] != $deletedStaffPremisID) {
                        if (isset($savedData['nama']) && !empty($savedData['nama'])) {
                            $dataStaff = get_data_staff_premis($IdPremis, $savedData['id']);
                            if (!count($dataStaff)) {
                                $StaffPremis = array();
                                $StaffPremis['id_staff'] = $savedData['id'];
                                $StaffPremis['id_premis'] = $IdPremis;
                                $StaffPremis['id_jawatan'] = $IdJawatan;
                                $NewStaffPremis = saveTableData(
                                    'zdatapremis_staff', 'admin data premis',
                                    $StaffPremis
                                );
                                $returnData[] = $NewStaffPremis;
                            } else {
                                if ($dataStaff[0]->id_jawatan != $IdJawatan) {
                                    $conditionData = array();
                                    $consObj = new stdClass();
                                    $consObj->fieldName = 'id_staff';
                                    $consObj->fieldValue = $savedData['id'];
                                    $consObj->status = 'and';
                                    $conditionData[] = $consObj;
                                    $consObj = new stdClass();
                                    $consObj->fieldName = 'id_premis';
                                    $consObj->fieldValue = $IdPremis;
                                    $consObj->status = 'and';
                                    $conditionData[] = $consObj;
                                    $consObj = new stdClass();
                                    $consObj->fieldName = 'id_jawatan';
                                    $consObj->fieldValue = $dataStaff[0]->id_jawatan;
                                    $consObj->status = 'and';
                                    $conditionData[] = $consObj;
                                    deleteTableData('zdatapremis_staff', 'admin data premis', $conditionData);
                                    $StaffPremis = array();
                                    $StaffPremis['id_staff'] = $savedData['id'];
                                    $StaffPremis['id_premis'] = $IdPremis;
                                    $StaffPremis['id_jawatan'] = $IdJawatan;
                                    $NewStaffPremis = saveTableData(
                                        'zdatapremis_staff', 'admin data premis',
                                        $StaffPremis
                                    );
                                    $returnData[] = $NewStaffPremis;
                                }
                            }
                        } else {
                            $conditionData = array();
                            $consObj = new stdClass();
                            $consObj->fieldName = 'id';
                            $consObj->fieldValue = $savedData['id'];
                            $consObj->status = 'and';
                            $conditionData[] = $consObj;
                            deleteTableData('zdatastaff', 'admin data premis', $conditionData);
                            $conditionData = array();
                            $consObj = new stdClass();
                            $consObj->fieldName = 'id_staff';
                            $consObj->fieldValue = $savedData['id'];
                            $consObj->status = 'and';
                            $conditionData[] = $consObj;
                            $consObj = new stdClass();
                            $consObj->fieldName = 'id_premis';
                            $consObj->fieldValue = $IdPremis;
                            $consObj->status = 'and';
                            $conditionData[] = $consObj;
                            deleteTableData('zdatapremis_staff', 'admin data premis', $conditionData);
                        }
                    }
                }
                if (!empty($deletedStaffPremisID)){
                    $conditionData = array();
                    $consObj = new stdClass();
                    $consObj->fieldName = 'id_staff';
                    $consObj->fieldValue = $deletedStaffPremisID;
                    $consObj->status = 'and';
                    $conditionData[] = $consObj;
                    $consObj = new stdClass();
                    $consObj->fieldName = 'id_premis';
                    $consObj->fieldValue = $IdPremis;
                    $consObj->status = 'and';
                    $conditionData[] = $consObj;
                    deleteTableData('zdatapremis_staff', 'admin data premis',$conditionData);
                }
            }
        }
    }
    if (count($returnData)){
        drupal_set_message('Data Staff Berhasil Disimpan..!!');
    }
    return $returnData;
}
function delete_premis_data($idPremis = null)
{
  $deletedData = null;
  if (!empty($idPremis)) {
    db_set_active('master');
    $conditionData = array();
    $consObj = new stdClass();
    $consObj->fieldName = 'id';
    $consObj->fieldValue = $idPremis;
    $consObj->status = 'and';
    $conditionData[] = $consObj;
    $deletedData = deleteTableData('master_data_premis', 'admin data premis', $conditionData);
    $deletedDetail = deleteTableData('master_data_premis_detail', 'admin data premis', $conditionData);
    drupal_set_message('Premis berhasil dihapus...!!', 'error');
    db_set_active();
    drupal_goto('masterdata/premis');
  }
  return $deletedData;
}
function get_data_premis_by_zone_ajax(){
    $zone = $_REQUEST['id_zon'];
    $dataPremis = get_data_premis_by_id($zone);
    $arrPremis = array();
    for ($i = 0;$i < count($dataPremis);$i++){
        $arrPremis[$dataPremis[$i]->id] = $dataPremis[$i]->nama;
    }
    print json_encode($arrPremis);
    exit();
}
function update_premis_data(){
    if (isset($_REQUEST['id']) && isset($_REQUEST['value'])){
        $splitID = explode('-',$_REQUEST['id']);
        $savedData['idnegeri'] = $_REQUEST['value'];
        $values['id'] = $splitID[2];
        saveTableData('zdatapremis','admin data premis',$savedData,'id',$values['id']);
        $dataNegeri = get_data_negeri_by_id(null, $_REQUEST['value']);
        print $dataNegeri->nama;
    }else{
        print '-';
    }
    exit();
}

function get_data_premis_negeri($idNegeri = null, $idPremis = null){
    $dataPremis = null;
    if (!empty($idNegeri) && empty($idPremis)){
        $fieldArray = array(
            'id', 'idnegeri', 'nama', 'alamat', 'telepon', 'whatsapp', 'bbm',
            'telegram', 'email', 'created', 'changed', 'uid', 'uid_changed'
        );
        $dataPremis = getTableDataByField('zdatapremis','access data negeri',$fieldArray,null,'idnegeri',$idNegeri);
    }else if (!empty($idPremis)){
        $fieldArray = array(
            'id', 'idnegeri', 'nama', 'alamat', 'telepon', 'whatsapp', 'bbm',
            'telegram', 'email', 'created', 'changed', 'uid', 'uid_changed'
        );
        $dataPremis = getTableDataByField('zdatapremis','access data negeri',$fieldArray,null,'id',$idPremis);
    }else if (empty($idNegeri) && empty($idStaff)){
        $fieldArray = array(
            'id', 'idnegeri', 'nama', 'alamat', 'telepon', 'whatsapp', 'bbm',
            'telegram', 'email', 'created', 'changed', 'uid', 'uid_changed'
        );
        $dataPremis = getTableDataByField('zdatapremis','access data negeri',$fieldArray);
    }
    return $dataPremis;
}

function fetch_data_staff_premis(){
    $strSQL = 'SELECT id, id_premis, id_jawatan FROM {zdatastaff} ORDER BY id_premis';
    $dataStaff = db_query($strSQL)->fetchAll();
    $returnData = array();
    for ($i = 0;$i < count($dataStaff);$i++){
        $savedData = array();
        $savedData['id_staff'] = $dataStaff[$i]->id;
        $savedData['id_premis'] = $dataStaff[$i]->id_premis;
        $savedData['id_jawatan'] = $dataStaff[$i]->id_jawatan;
        $returnData[] = saveTableData(
            'zdatapremis_staff', 'admin data premis',
            $savedData
        );
    }
    return $returnData;
}

function get_data_premis($id_zon = null, $id_premis = null){
   global $user;

}
