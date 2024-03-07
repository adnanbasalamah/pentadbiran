<?php

function pemasukan_pengeluaran($zone = null, $month = null, $year = null){
    $module_path = drupal_get_path('module','ikhwan_core');
    $csspath = $module_path.'/css/custom-style.css';
    drupal_add_css($csspath);
    $jspath = $module_path.'/js/jquery.masknumber.js';
    drupal_add_js($jspath,array('scope' => 'footer', 'weight' => 5));
    $jspath = $module_path.'/js/notify.js';
    drupal_add_js($jspath,array('scope' => 'footer', 'weight' => 5));
    $module_path  = drupal_get_path('module','pemasukan_pengeluaran');
    $jspath = $module_path.'/js/input_pemasukan.js';
    drupal_add_js($jspath,array('scope' => 'footer', 'weight' => 5));
    $variables['zone'] = $zone;
    $variables['month'] = $month;
    $variables['year'] = $year;
    $form = drupal_get_form('pemasukan_pengeluaran_form',$variables);
    $formPendapatan = '<div class="col-md-6">'.drupal_render($form).'</div>';
    return $formPendapatan;
}

function pemasukan_pengeluaran_header()
{
    $tableHeader = array();
    $tableHeader[] = array(
        'data' => t('TARIKH'),
        'class' => array(
            'col-input-number-small',
        ),
    );
    $tableHeader[] = array(
        'data' => t('PENDAPATAN'),
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
    $tableHeader[] = array(
        'data' => t('BAKI'),
        'class' => array(
            'col-input-number',
        ),
    );
    $tableHeader[] = t('KETERANGAN');
    return $tableHeader;
}
function pemasukan_pengeluaran_footer()
{
    $tableHeader = array();
    $tableHeader[] = array(
        'data' => t('TOTAL'),
        'class' => array(
            'col-input-number-small',
        ),
    );
    $tableHeader[] = array(
        'data' => '<div id="total-pemasukan" class="align-right">0</div>',
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
    $tableHeader[] = array(
        'data' => '<div id="total-baki" class="align-right">0</div>',
        'class' => array(
            'col-input-number',
        ),
    );
    $tableHeader[] = '&nbsp;';
    return $tableHeader;
}
function pemasukan_pengeluaran_row($zone = null, $month = null, $year = null){
    $tableRow = array();
    $tableRow['#tree'] = TRUE;
    $dataPendapatan = get_pendapatan_zone_data($zone, $month, $year);
    if (!empty($zone) && !empty($month) && !empty($year)){
        $lastDate = get_last_day($month,$year);
        $intDate = mktime(7,0,0,$month,1,$year);
        $startDate = date('Y-m-',$intDate).'01';
        $finishDate = date('Y-m-',$intDate).$lastDate;
        $dateArray = create_date_range_array($startDate,$finishDate, 'UNIX');
        $dateArray2 = create_date_range_array($startDate,$finishDate, 'j-M');
        for ($i = 0;$i < count($dateArray);$i++){
            if (isset($dataPendapatan[$dateArray[$i]])){
                $idPendapatan = $dataPendapatan[$dateArray[$i]]->id;
                $description = $dataPendapatan[$dateArray[$i]]->description;
                //$jumlah = $dataPendapatan[$dateArray[$i]]->jumlah;
                $jumlah_pemasukan_entry = $dataPendapatan[$dateArray[$i]]->jumlah_pemasukan_entry;
                $jumlah_pengeluaran_entry = $dataPendapatan[$dateArray[$i]]->jumlah_pengeluaran_entry;
            }else{
                $idPendapatan = null;
                $description = '';
                //$jumlah = 0;
                $jumlah_pemasukan_entry = 0;
                $jumlah_pengeluaran_entry = 0;
            }
            $rowData = array();
            if (!empty($idPendapatan)){
                $idxDate = 'date-'.$zone.'-'.$dateArray[$i].'-'.($i + 1).'-'.$idPendapatan;
            }else{
                $idxDate = 'date-'.$zone.'-'.$dateArray[$i].'-'.($i + 1);
            }
            $rowData[$idxDate] = array(
                '#type' => 'item', '#title' => $dateArray2[$i],
                '#attributes' => array('outerclass' => array('align-center')),
            );
            if (!empty($idPendapatan)){
                $idxJumlahPemasukan = 'pemasukan-'.$zone.'-'.$dateArray[$i].'-'.($i + 1).'-'.$idPendapatan;
            }else{
                $idxJumlahPemasukan = 'pemasukan-'.$zone.'-'.$dateArray[$i].'-'.($i + 1);
            }
            $rowData[$idxJumlahPemasukan] = array(
                '#type' => 'textfield',
                '#default_value' => $jumlah_pemasukan_entry,
                '#attributes' => array('class' => array(
                    'align-right','pemasukan-value','pemasukan-'.($i + 1)
                ),
                ),
            );
            if (!empty($idPendapatan)){
                $idxJumlahPengeluaran = 'pengeluaran-'.$zone.'-'.$dateArray[$i].'-'.($i + 1).'-'.$idPendapatan;
            }else{
                $idxJumlahPengeluaran = 'pengeluaran-'.$zone.'-'.$dateArray[$i].'-'.($i + 1);
            }
            $rowData[$idxJumlahPengeluaran] = array(
                '#type' => 'textfield',
                '#default_value' => $jumlah_pengeluaran_entry,
                '#attributes' => array('class' => array(
                    'align-right','pengeluaran-value','pengeluaran-'.($i + 1)
                ),
                ),
            );
            if (!empty($idPendapatan)){
                $idxTotal = 'total-'.$dateArray[$i].'-'.($i + 1).'-'.$idPendapatan;
            }else{
                $idxTotal = 'total-'.$dateArray[$i].'-'.($i + 1);
            }
            $rowData[$idxTotal] = array(
                '#type' => 'item', '#title' => '<div id="total-'.($i + 1).'">BAKI</div>',
                '#attributes' => array('outerclass' => array('align-right')),
            );
            if (!empty($idPendapatan)){
                $idxDesc = 'description-'.$zone.'-'.$dateArray[$i].'-'.($i + 1).'-'.$idPendapatan;
            }else{
                $idxDesc = 'description-'.$zone.'-'.$dateArray[$i].'-'.($i + 1);
            }
            $rowData[$idxDesc] = array(
                '#type' => 'textfield',
                '#default_value' => $description,
                '#attributes' => array('outerclass' => array('align-left')),
            );
            $tableRow['r'.($i + 1)] = $rowData;
        }
    }
    return $tableRow;
}
function get_pendapatan_zone_data($zone = null, $month = null, $year = null, $idPendapatan = null){
    $tableName = 'zdatazone_pemasukan_pengeluaran';
    $fieldArray = array(
        'id', 'zone', 'entry_date', 'jumlah_pemasukan', 'jumlah_pemasukan_entry',
        'jumlah_pengeluaran', 'jumlah_pengeluaran_entry', 'description', 'month',
        'year', 'created', 'changed', 'uid', 'uid_changed'
    );
    $fieldOrder = array(
        array ('fieldname' => 'zone'),
        array('fieldname' => 'entry_date'),
    );
    $dataPendapatan = array();
    if (empty($idPendapatan)) {
        $conditionArray = array();
        if (!empty($zone)) {
            $consData = new stdClass();
            $consData->fieldName = 'ta.zone';
            $consData->value = $zone;
            $conditionArray[] = $consData;
        }
        if (!empty($month) && !empty($year)) {
            $consData = new stdClass();
            $consData->fieldName = 'ta.month';
            $consData->value = $month;
            $conditionArray[] = $consData;
            $consData = new stdClass();
            $consData->fieldName = 'ta.year';
            $consData->value = $year;
            $conditionArray[] = $consData;
        }
        $pendapatanZone = getTableDataByField(
            $tableName,'access data pemasukan pengeluaran',$fieldArray,
            $fieldOrder,null,null,null,$conditionArray
        );
        if (!empty($zone)) {
            if (count($pendapatanZone)){
                for ($i = 0;$i < count($pendapatanZone);$i++){
                    $dataPendapatan[$pendapatanZone[$i]->entry_date] = $pendapatanZone[$i];
                }
            }
        }else{
            if (count($pendapatanZone)){
                for ($i = 0;$i < count($pendapatanZone);$i++){
                    $dataPendapatan[$pendapatanZone[$i]->zone][] = $pendapatanZone[$i];
                }
            }
        }
    }else{
        $pendapatanZone = getTableDataByField(
            $tableName,'access data pemasukan pengeluaran',$fieldArray,
            $fieldOrder,'id',$idPendapatan
        );
        $dataPendapatan = $pendapatanZone[0];
    }
    return $dataPendapatan;
}
function pemasukan_pengeluaran_form($form, &$form_state, $variables = null){
    set_default_time_zone();
    if (isset($variables['zone']) && !empty($variables['zone'])){
        $dataZone = getZoneByCode($variables['zone']);
        $month = $variables['month'];
        $year = $variables['year'];
        if (!empty($month) && !empty($year)){
        }else{
            $month = date('n');
            $year = date('Y');
        }
        $intDate = mktime(7,0,0,$month,1,$year);
        $tableHeader = pemasukan_pengeluaran_header();
        $tableFooter[] = pemasukan_pengeluaran_footer();
        $tableRow = pemasukan_pengeluaran_row($variables['zone'], $month, $year);
        $form['form-title'] = array(
            '#type' => 'item',
            '#markup' => '<h3 class="title">PENDAPATAN DAN PENGELUARAN ZONE '.$dataZone->nama.' '.date('M',$intDate).' '.date('Y',$intDate).'</h3>',
        );
        $form['zone'] = array(
            '#type' => 'hidden',
            '#default_value' => $variables['zone'],
        );
        $form['table'] = array(
            '#theme' => 'formtable_form_table',
            '#header' => $tableHeader,
            'rows' => $tableRow,
            '#footer' => $tableFooter,
        );
        $form['submit'] = array(
            '#type' => 'submit',
            '#value' => t('Save Pendapatan & Pengeluaran'),
        );
    }
    return $form;
}
function pemasukan_pengeluaran_form_submit($form, &$form_state)
{
    global $user;
    set_default_time_zone();
    $tableName = 'zdatazone_pemasukan_pengeluaran';
    if (isset($form_state['values']['rows'])) {
        $values = $form_state['values']['rows'];
    } else {
        $values = $form_state['values'];
    }
    $returnData = array();
    if (count($values)) {
        $inserted = 0;
        $updated = 0;
        foreach ($values as $idxRow => $rowData){
            if (count($rowData)){
                $savedData = array();
                foreach ($rowData as $idxCol => $colData){
                    $explodeIdx = explode('-',$idxCol);
                    if (isset($explodeIdx[4])){
                        $savedData['id'] =  $explodeIdx[4];
                    }
                    $savedData['zone'] = $explodeIdx[1];
                    $savedData['entry_date'] = $explodeIdx[2];
                    $savedData['month'] = date('n',$explodeIdx[2]);
                    $savedData['year'] = date('Y',$explodeIdx[2]);
                    $savedData['uid'] = $user->uid;
                    if ($explodeIdx[0] == 'pemasukan' || $explodeIdx[0] == 'pengeluaran') {
                        $savedValue = str_replace(',', '', $colData);
                        $savedData['jumlah_'.$explodeIdx[0]] = eval('return ' . $savedValue . ';');
                        $savedData['jumlah_'.$explodeIdx[0].'_entry'] = $colData;
                    }else{
                        $savedValue = $colData;
                        $savedData[$explodeIdx[0]] = $savedValue;
                    }
                }
                if (isset($savedData['id']) && !empty($savedData['id'])){
                    //Update record
                    $returnData[] = saveTableData(
                        $tableName,'admin data pemasukan pengeluaran',
                        $savedData,'id',$savedData['id']
                    );
                    $updated++;
                }else{
                    //Insert record
                    $returnData[] = saveTableData($tableName,'admin data pemasukan pengeluaran',$savedData,'id');
                    $inserted++;
                }
            }
        }
        drupal_set_message(t('Data pendapatan dan pengeluaran berhasil di save...!!!'));
    }
}
function get_total_pemasukan_pengeluaran_zon($month = null, $year = null, $zone = null){
    $strSQL = 'SELECT zone, SUM(jumlah_pemasukan) AS total_pemasukan, SUM(jumlah_pengeluaran) AS total_pengeluaran, ';
    $strSQL .= 'SUM(jumlah_pemasukan - jumlah_pengeluaran) AS total_baki FROM {zdatazone_pemasukan_pengeluaran} ';
    $strSQL .= 'WHERE ';
    $arrayValue = array();
    $strSQLCond = '';
    if (!empty($month)){
        if ($strSQLCond == ''){
            $strSQLCond .= 'month = :month ';
        }else{
            $strSQLCond .= 'AND month = :month ';
        }
        $arrayValue[':month'] = $month;
    }
    if (!empty($year)){
        if ($strSQLCond == ''){
            $strSQLCond .= 'year = :year ';
        }else {
            $strSQLCond .= 'AND year = :year ';
        }
        $arrayValue[':year'] = $year;
    }
    if (!empty($zone)) {
        if ($strSQLCond == ''){
            $strSQLCond .= 'zone = :zone ';
        }else{
            $strSQLCond .= 'AND zone = :zone ';
        }
        $arrayValue[':zone'] = $zone;
    }
    $strSQL .= $strSQLCond.' GROUP BY zone';
    $dataPendapatan = db_query($strSQL, $arrayValue)->fetchAll();
    $arrayPendapatan = array();
    if (empty($zone)){
        for ($i = 0;$i < count($dataPendapatan);$i++){
            $arrayPendapatan[$dataPendapatan[$i]->zone] = $dataPendapatan[$i];
        }
    }else{
        $arrayPendapatan = $dataPendapatan[0];
    }
    return $arrayPendapatan;
}