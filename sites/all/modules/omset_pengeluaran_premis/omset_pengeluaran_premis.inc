<?php

/**
 * @return string
 */
function omset_pengeluaran_premis($EntryDate = null){
    $variables = NULL;
    drupal_add_js('misc/collapse.js');
    $jquery_path = drupal_get_path('module', 'jquery_update');
    $csspath = $jquery_path . '/replace/ui/themes/base/jquery-ui.css';
    drupal_add_css($csspath);
    $jspath = $jquery_path . '/replace/ui/ui/jquery-ui.js';
    drupal_add_js($jspath, ['scope' => 'footer', 'weight' => 5]);
    $core_module_path = drupal_get_path('module','ikhwan_core');
    $jspath = $core_module_path.'/js/jquery.masknumber.js';
    drupal_add_js($jspath,array('scope' => 'footer', 'weight' => 5));
    $jspath = $core_module_path.'/js/notify.js';
    drupal_add_js($jspath,array('scope' => 'footer', 'weight' => 5));
    $module_path = drupal_get_path('module', 'omset_pengeluaran_premis');
    $jspath = $module_path . '/js/omset_pengeluaran_premis.js';
    drupal_add_js($jspath, ['scope' => 'footer', 'weight' => 5]);
    if (!empty($EntryDate)){
      $SplitEntryDate = explode('-', $EntryDate);
      if (count($SplitEntryDate) <= 1){
        $EntryDate = date('d-m-Y', $EntryDate);
      }
      $DataOmset = get_omset_premis_data('entry_date',$EntryDate);
      if (isset($DataOmset['info']) && isset($DataOmset['info'][0])){
        $variables['entry_date'] = $EntryDate;
        $variables['keterangan'] = $DataOmset['info'][0]->description;
        $variables['detail_omset'] = $DataOmset['detail'];
      }else{
        $variables['entry_date'] = $EntryDate;
        $variables['keterangan'] = '';
        $variables['detail_omset'] = null;
      }
    }
    $Form = drupal_get_form('form_laporan_omset', $variables);
    $FormLaporan = drupal_render($Form);
    return $FormLaporan;
}

function form_laporan_omset($form, &$form_state, $variables = null) {
    if (!empty($variables) && isset($variables['entry_date'])) {
        $tableRow = create_laporan_omset_form_row($variables['detail_omset']);
    }
    else {
        $tableRow = create_laporan_omset_form_row();
    }
    $tableHeader = create_laporan_omset_form_header();
    $tableFooter = [create_laporan_omset_form_footer()];
    $form['basic'] = [
      '#type' => 'fieldset',
      '#title' => 'INPUT OMSET & PENGELUARAN PREMIS',
      '#collapsible' => TRUE, // Added
      '#collapsed' => FALSE,  // Added
    ];
    $form['basic']['entry_date'] = [
      '#type' => 'textfield',
      '#title' => t('Tanggal'),
      '#required' => TRUE,
      '#default_value' => isset($variables['entry_date']) ? $variables['entry_date'] : date('d-m-Y'),
      '#prefix' => '<div class="col-md-3">',
    ];
    $form['basic']['keterangan'] = [
      '#type' => 'textfield',
      '#title' => t('Keterangan'),
      '#required' => FALSE,
      '#default_value' => isset($variables['keterangan']) ? $variables['keterangan'] : '',
    ];
    $form['basic']['view_button'] = [
      '#type' => 'submit',
      '#value' => t('VIEW LAPORAN'),
      '#attributes' => ['class' => ['btn-primary','btn-sm']],
      '#prefix' => '<div class="row col-md-12">',
    ];
    $form['basic']['send_button'] = [
      '#type' => 'submit',
      '#value' => t('KIRIM LAPORAN'),
      '#attributes' => ['class' => ['btn-warning','btn-sm']],
      '#suffix' => '</div></div>',
    ];
    $form['basic']['table'] = [
        '#theme' => 'formtable_form_table',
        '#header' => $tableHeader,
        'rows' => $tableRow,
        '#footer' => $tableFooter,
        '#color_new_rows' => FALSE,
        '#prefix' => '<div class="col-md-9">',
    ];
    $form['basic']['submit'] = [
        '#type' => 'submit',
        '#value' => t('SAVE LAPORAN'),
        '#prefix' => '<div class="row col-md-12">',
        '#suffix' => '</div></div>',
    ];
    return $form;
}
function create_laporan_omset_form_header(){
  $tableHeader = [];
  $tableHeader[] = [
    'data' => t('NO.'),
    'class' => [
      'col-number'
    ],
  ];
  $tableHeader[] = t('PREMIS');
  $tableHeader[] = array(
    'data' => t('OMSET'),
    'class' => array(
      'col-input-number',
    ),
  );
  $tableHeader[] = array(
    'data' => t('PENGELUARAN'),
    'class' => array(
      'col-input-number',
    ),
  );
  return $tableHeader;
}
function create_laporan_omset_form_footer()
{
  $tableHeader = [];
  $tableHeader[] = [
    'data' => ' ',
    'class' => [
      'col-number'
    ],
  ];
  $tableHeader[] = '<strong>'.t('TOTAL').'</strong>';
  $tableHeader[] = array(
    'data' => '<div id="total-omset" class="align-right">0</div>',
    'class' => array(
      'col-input-number',
    ),
  );
  $tableHeader[] = array(
    'data' => '<div id="total-pengeluaran" class="align-right">0</div>',
    'class' => array(
      'col-input-number',
    ),
  );
  return $tableHeader;
}

function create_laporan_omset_form_row($post_vars = null)
{
  global $user;
  if (function_exists('set_user_number_format')){
    set_user_number_format($desIn, $desOut, $separator);
  }else{
    $desIn = '.';
    $desOut = ',';
    $separator = '.';
  }
  $DefaultData = $post_vars;
  $keuanganZone = cek_keuangan_zone();
  $userZone = null;
  if ($keuanganZone) {
    $userZone = get_user_zone();
  }
  if (count($userZone) && isset($userZone[0])) {
    //$getDataZone = $userZone[1]['zone'];
    $dataPremis = $userZone[1]['id_premis'];
  } else {
    //$getDataZone = getZoneByCode();
    $dataPremis = get_data_premis_by_id();
  }
  $rows = [];
  $rows['#tree'] = TRUE;
  $nextCounter = 1;
  $CounterView = 1;
  $ValidPremis = [];
  for ($i = 0; $i < count($dataPremis); $i++) {
    if ($keuanganZone) {
      $detailPremis = get_data_premis_by_id(null, $dataPremis[$i]);
    } else {
      $detailPremis = $dataPremis[$i];
    }
    if (isset($detailPremis->id) && !empty($detailPremis->id)) {
      $ValidPremis[] = $detailPremis->id;
      $premisData = array();
      $premisData['no-' . $nextCounter] = array(
        '#type' => 'item', '#title' => ($CounterView),
        '#attributes' => array('outerclass' => array('align-right')),
      );
      $premisData['id_premis-new-' . $nextCounter] = [
        '#type' => 'hidden',
        '#prefix' => strtoupper($detailPremis->nama),
        '#attributes' => [
          'class' => ['align-right'],
          'id' => 'nid-premis-' . $nextCounter,
        ],
        '#default_value' => $detailPremis->id,
      ];
      $DataUnit = get_data_unit_premis(null,$detailPremis->id);
      if (count($DataUnit)) {
        $premisData['jumlah_omset-new-' . $nextCounter] = [
          '#type' => 'hidden',
          '#prefix' => '',
        ];
        $premisData['jumlah_pengeluaran-new-' . $nextCounter] = [
          '#type' => 'hidden',
          '#prefix' => '',
        ];
        $rows[] = $premisData;
        for ($j = 0; $j < count($DataUnit); $j++){
          $premisData = [];
          $premisData['no-' . $nextCounter] = array(
            '#type' => 'item', '#title' => '',
            '#attributes' => array('outerclass' => array('align-right')),
          );
          $premisData['id_unit-new-' . $nextCounter] = [
            '#type' => 'hidden',
            '#prefix' => strtoupper($DataUnit[$j]->nama_unit),
            '#attributes' => [
              'class' => ['align-right'],
              'id' => 'nid-premis-' . $nextCounter,
            ],
            '#default_value' => $detailPremis->id.'_'.$DataUnit[$j]->id,
          ];
          $premisData['jumlah_omset-new-' . $nextCounter] = [
            '#type' => 'textfield',
            '#attributes' => [
              'class' => [
                'jumlah-omset',
                'input-omset',
                'col-number',
                'col-input-number'
              ]
            ],
            '#default_value' => isset($DefaultData[$detailPremis->id][$DataUnit[$j]->id]) ? $DefaultData[$detailPremis->id][$DataUnit[$j]->id]->jumlah_omset : 0,
          ];
          $premisData['jumlah_pengeluaran-new-' . $nextCounter] = [
            '#type' => 'textfield',
            '#attributes' => [
              'class' => [
                'jumlah-pengeluaran',
                'input-omset',
                'col-number',
                'col-input-number'
              ]
            ],
            '#default_value' => isset($DefaultData[$detailPremis->id][$DataUnit[$j]->id]) ? $DefaultData[$detailPremis->id][$DataUnit[$j]->id]->jumlah_pengeluaran : 0,
          ];
          $rows[] = $premisData;
          $nextCounter++;
        }
      }else{
        $premisData['jumlah_omset-new-' . $nextCounter] = [
          '#type' => 'textfield',
          '#attributes' => [
            'class' => [
              'jumlah-omset',
              'input-omset',
              'col-number',
              'col-input-number'
            ]
          ],
          '#default_value' => isset($DefaultData[$detailPremis->id][0]) ? $DefaultData[$detailPremis->id][0]->jumlah_omset : 0,
        ];
        $premisData['jumlah_pengeluaran-new-' . $nextCounter] = [
          '#type' => 'textfield',
          '#attributes' => [
            'class' => [
              'jumlah-pengeluaran',
              'input-pengeluaran',
              'col-number',
              'col-input-number'
            ]
          ],
          '#default_value' => isset($DefaultData[$detailPremis->id][0]) ? $DefaultData[$detailPremis->id][0]->jumlah_pengeluaran : 0,
        ];
        $rows[] = $premisData;
        $nextCounter++;
      }
      $CounterView++;
    }
  }
  if (count($ValidPremis) && $keuanganZone){
    $SavedData = [];
    $SavedData['id_premis'] = implode(',', $ValidPremis);
    $SavedData['related_uid'] = $user->uid;
    saveTableData(
      'zuser_zone','admin omset pengeluaran premis module',$SavedData,
      'related_uid',$user->uid);
  }
  return $rows;
}

function form_laporan_omset_submit($form, &$form_state)
{
  global $user;
  if (function_exists('set_user_number_format')){
    set_user_number_format($desIn, $desOut, $separator);
  }else{
    $desIn = '.';
    $desOut = ',';
    $separator = '.';
  }
  $values = $form_state['values'];
  if ($values['op'] == 'VIEW LAPORAN') {
    $SplitEntryDate = explode('-', $values['entry_date']);
    $EntryDateInt = mktime(
      date('H'), date('i'), date('s'),
      (int)$SplitEntryDate[1], (int)$SplitEntryDate[0], (int)$SplitEntryDate[2]
    );
    drupal_goto('masterdata/premis/laporanomset/' . $EntryDateInt);
  }else if ($values['op'] == 'KIRIM LAPORAN') {
    $ReturnData = true;
    send_telegram_message_omset($values['entry_date']);
  } else {
    $SavedData = [];
    $SplitEntryDate = explode('-', $values['entry_date']);
    $DataOmsetExist = get_omset_premis_data('entry_date',$values['entry_date']);
    $IdData = null;
    $FieldPrimary = null;
    if (isset($DataOmsetExist['detail']) && isset($DataOmsetExist['info'][0]) &&
      !empty($DataOmsetExist['info'][0]->id)
    ){
      $FieldPrimary = 'id';
      $IdData = $DataOmsetExist['info'][0]->id;
      $ConditionData = array();
      $ConsObj = new stdClass();
      $ConsObj->fieldName = 'id_laporan_omset';
      $ConsObj->fieldValue = $IdData;
      $ConsObj->status = 'and';
      $ConditionData[] = $ConsObj;
      deleteTableData('zdatapremis_omset_premis',
        'admin omset pengeluaran premis module',$ConditionData
      );
    }
    $EntryDateInt = mktime(
      date('H'), date('i'), date('s'),
      (int)$SplitEntryDate[1], (int)$SplitEntryDate[0], (int)$SplitEntryDate[2]
    );
    $SavedData['entry_date'] = $EntryDateInt;
    $SavedData['description'] = $values['keterangan'];
    $SavedData['month'] = (int)$SplitEntryDate[1];
    $SavedData['year'] = (int)$SplitEntryDate[2];
    $SavedData['uid'] = $user->uid;
    $DataId = saveTableData(
      'zdatapremis_omset', 'admin omset pengeluaran premis module',
      $SavedData,$FieldPrimary,$IdData
    );
    $FieldDataArray['fieldname'] = array(
      'id_laporan_omset', 'id_premis', 'id_unit', 'jumlah_omset',
      'jumlah_pengeluaran'
    );
    $FieldDataArray['values'] = array();
    foreach ($values['rows'] as $RowValues) {
      $DataSaved = [];
      $DataSaved['id_laporan_omset'] = $DataId;
      foreach ($RowValues as $Idx => $Values) {
        $SplitRows = explode('-', $Idx);
        if (isset($SplitRows[0]) && $SplitRows[0] != 'id') {
          if ($SplitRows[0] == 'id_unit'){
            $SplitValue = explode('_', $Values);
            $DataSaved['id_premis'] = $SplitValue[0];
            if (isset($SplitValue[1])){
              $DataSaved[$SplitRows[0]] = $SplitValue[1];
            }
          }else if($SplitRows[0] == 'id_premis'){
            $DataSaved[$SplitRows[0]] = $Values;
            $DataSaved['id_unit'] = 0;
          }else{
            $DataValue = empty($Values) ? 0 : $Values;
            $calcValue = str_replace($separator,'',$DataValue);
            $calcValue = str_replace($desOut,'.',$calcValue);
            $DataSaved[$SplitRows[0]] = $calcValue;
          }
        }
      }
      //if ($DataSaved['jumlah_omset'] > 0 || $DataSaved['jumlah_pengeluaran'] > 0) {
      $FieldDataArray['values'][] = $DataSaved;
      //}
    }
    $ReturnData = save_table_data_multiple(
      'zdatapremis_omset_premis', 'admin omset pengeluaran premis module',
      $FieldDataArray, null, false
    );
    drupal_set_message('Omset Premis Berhasil Disimpan...!!!');
    //drupal_goto('masterdata/premis/laporanomset/' . $EntryDateInt);
  }
  return $ReturnData;
}

function send_telegram_message_omset($entry_date = null)
{
  $TelegramBot = true;
  date_default_timezone_set('Asia/Jakarta');
  $telegramMessage = get_data_omset_by_date($entry_date);
  $parseMode = 'markdown';
  $token = '717685021:AAFG98dkd5za3wjjSyfHKGltX6L2m94sR6Y';
  $telegramPath = 'https://api.telegram.org/bot' . $token . '/sendMessage';
  $chatId = '-492883206';
  $queryString = array(
    'query' => array(
      'chat_id' => $chatId,
      /*'parse_mode' => $parseMode,*/
      'text' => $telegramMessage,
    ),
  );
  drupal_goto($telegramPath, $queryString);
}

function get_data_omset_by_date($entry_date = null){
  date_default_timezone_set('Asia/Jakarta');
  if (empty($entry_date)){
    $entry_date = date('d-m-Y');
  }
  $SplitDate = explode('-', $entry_date);
  $DataOmset = get_omset_premis_data('entry_date', $entry_date);
  $counter = 1;
  $LaporanOmset = '';
  $TotalOmset = 0;
  $TotalPengeluaran = 0;
  if (isset($DataOmset['detail']) && count($DataOmset['detail'])){
    foreach ($DataOmset['detail'] as $idx => $DetailOmset){
      if (count($DetailOmset) > 1){
        $LaporanOmsetUnit = '';
        $NamaPremis = '';
        foreach ($DetailOmset as $idx2 => $UnitOmset){
          $NamaPremis = $UnitOmset->nama;
          if (!empty($UnitOmset->nama_unit)) {
            $LaporanOmsetUnit .= str_pad(" ", 3, " ");
            $LaporanOmsetUnit .= ucwords(strtolower($UnitOmset->nama_unit));
            $LaporanOmsetUnit .= "\n";
            $LaporanOmsetUnit .= str_repeat(" ", 3);
            $Omset = empty($UnitOmset->jumlah_omset) ? 0 : $UnitOmset->jumlah_omset;
            $LaporanOmsetUnit .= number_format($Omset, 0, ',', '.');
            $LaporanOmsetUnit .= " / ";
            $Pengeluaran = empty($UnitOmset->jumlah_pengeluaran) ? 0 : $UnitOmset->jumlah_pengeluaran;
            $LaporanOmsetUnit .= number_format($Pengeluaran, 0, ',', '.');
            $LaporanOmsetUnit .= "\n";
            $TotalOmset = $TotalOmset + $UnitOmset->jumlah_omset;
            $TotalPengeluaran = $TotalPengeluaran + $UnitOmset->jumlah_pengeluaran;
          }
        }
        $LaporanOmset .= str_pad($counter.".",3," ");
        $LaporanOmset .= ucwords(strtolower($NamaPremis));
        $LaporanOmset .= "\n";
        $LaporanOmset .= $LaporanOmsetUnit;
        $counter++;
      }else{
        $LaporanOmset .= str_pad($counter.".",3," ");
        $LaporanOmset .= ucwords(strtolower($DetailOmset[0]->nama));
        $LaporanOmset .= "\n";
        $LaporanOmset .= str_repeat(" ", 3);
        $Omset = empty($DetailOmset[0]->jumlah_omset) ? 0 : $DetailOmset[0]->jumlah_omset;
        $LaporanOmset .= number_format($Omset,0,',','.');
        $LaporanOmset .= " / ";
        $Pengeluaran = empty($DetailOmset[0]->jumlah_pengeluaran) ? 0 : $DetailOmset[0]->jumlah_pengeluaran;
        $LaporanOmset .= number_format($Pengeluaran,0,',','.');
        $LaporanOmset .= "\n";
        $counter++;
        $TotalOmset = $TotalOmset + $DetailOmset[0]->jumlah_omset;
        $TotalPengeluaran = $TotalPengeluaran + $DetailOmset[0]->jumlah_pengeluaran;
      }
    }
  }
  $ArrayBulan = array_bulan();
  if ($LaporanOmset != '') {
    $KataLaporan = "Update OH Harian Bandar Sentul\n";
    $KataLaporan .= "*Rabu, ".$SplitDate[0]." ".$ArrayBulan[(int)$SplitDate[1]]." ".$SplitDate[2]."*\n\n";
    $KataLaporan .= "No Unit/Omset/Pengeluaran ```\n";
    $KataLaporan .= $LaporanOmset;
    $KataLaporan .= "\n";
    $KataLaporan .= "Total\n";
    $KataLaporan .= "Pemasukan  : Rp.".number_format($TotalOmset,0,',','.')."\n";
    $KataLaporan .= "Pengeluaran: Rp.".number_format($TotalPengeluaran,0,',','.')."\n";
    $KataLaporan .= "Ampun Tuan..Ibu..";
    $KataLaporan .= "```";
  }else{
    $KataLaporan = "Belum ada laporan omset hari ini";
  }
  return $KataLaporan;
}
