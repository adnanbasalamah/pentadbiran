<?php

function setoran_pengeluaran($idPremis = null, $month = null, $year = null){
    set_default_time_zone();
    $module_path = drupal_get_path('module','ikhwan_core');
    $csspath = $module_path.'/css/custom-style.css';
    drupal_add_css($csspath);
    $jspath = $module_path.'/js/jquery.masknumber.js';
    drupal_add_js($jspath,array('scope' => 'footer', 'weight' => 5));
    $jspath = $module_path.'/js/notify.js';
    drupal_add_js($jspath,array('scope' => 'footer', 'weight' => 5));
    $module_path  = drupal_get_path('module','setoran_pengeluaran');
    $jspath = $module_path.'/js/input_setoran.js';
    drupal_add_js($jspath,array('scope' => 'footer', 'weight' => 5));
    $variables['id_premis'] = $idPremis;
    $variables['month'] = $month;
    $variables['year'] = $year;
    $form = drupal_get_form('setoran_form',$variables);
    $formAssignment = '<div class="col-md-5">'.drupal_render($form).'</div>';
    $totalPengeluaran = total_pengeluaran_row($idPremis, $month, $year);
    drupal_add_js(
        array(
            'totalKetentuan' => $totalPengeluaran[1],
            'totalPengeluaran' => $totalPengeluaran[2],
            'totalKekurangan' => $totalPengeluaran[3],
        )
        , 'setting'
    );
    $variables = array(
        'header' => total_pengeluaran_header(),
        'rows' => $totalPengeluaran[0],
        'footer' => array(total_pengeluaran_footer($totalPengeluaran[1],$totalPengeluaran[2],$totalPengeluaran[3])),
    );
    $tablePengeluaran = theme('table', $variables);
    $intDate = mktime(7,0,0,$month,1,$year);
    $dataPremis = get_data_premis_by_id(null, $idPremis);
    $formTitle = '<div class="col-md-12"><h3 class="title">OVERHEAD DAN SERAHAN <span class="blue">'.strtoupper($dataPremis->nama).'</span> '.date('M',$intDate).' '.date('Y',$intDate).'</h3></div>';
    $formAssignment .= '<div class="col-md-7">'.$tablePengeluaran.'</div>';
    return $formTitle.$formAssignment;
}

function setoran_form_header(){
    $tableHeader = array();
    $tableHeader[] = array(
        'data' => t('TARIKH'),
            'class' => array(
                'col-input-number-small',
            ),
        );
        $tableHeader[] = t('PERKARA');
        $tableHeader[] = array(
            'data' => t('SERAHAN'),
            'class' => array(
                'col-input-number',
            ),
        );
        $tableHeader[] = array(
            'data' => t('TOTAL'),
            'class' => array(
                'col-input-number',
            ),
        );
    return $tableHeader;
}
function setoran_form_footer(){
    $tableHeader = array();
    $tableHeader[] = array(
        'data' => t('TOTAL SETORAN'),
        'colspan' => 2,
    );
    $tableHeader[] = array(
        'data' => '<div id="grand-total" class="align-right"></div>',
        'class' => array(
            'col-input-number',
        ),
    );
    $tableHeader[] = array(
        'data' => '<div id="grand-total-2" class="align-right"></div>',
        'class' => array(
            'col-input-number',
        ),
    );
    return $tableHeader;
}
function setoran_form_row($idpremis = null, $month = null, $year = null){
    $tableRow = array();
    $tableRow['#tree'] = TRUE;
    $dataSetoran = get_setoran_premis_data($idpremis, $month, $year);
    if (!empty($idpremis)){
        $lastDate = get_last_day($month,$year);
        $intDate = mktime(7,0,0,$month,1,$year);
        $startDate = date('Y-m-',$intDate).'01';
        $finishDate = date('Y-m-',$intDate).$lastDate;
        $dateArray = create_date_range_array($startDate,$finishDate, 'UNIX');
        $dateArray2 = create_date_range_array($startDate,$finishDate, 'd-m-Y');
        for ($i = 0;$i < count($dateArray);$i++){
            if (isset($dataSetoran[$dateArray[$i]])){
                $idSetoran = $dataSetoran[$dateArray[$i]]->id;
                $description = $dataSetoran[$dateArray[$i]]->description;
                //$jumlah = $dataSetoran[$dateArray[$i]]->jumlah;
                $jumlah_entry = $dataSetoran[$dateArray[$i]]->jumlah_entry;
            }else{
                $idSetoran = null;
                $description = t('SETORAN');
                //$jumlah = 0;
                $jumlah_entry = 0;
            }
            $rowData = array();
            if (!empty($idSetoran)){
                $idxDate = 'date-'.$idpremis.'-'.$dateArray[$i].'-'.($i + 1).'-'.$idSetoran;
            }else{
                $idxDate = 'date-'.$idpremis.'-'.$dateArray[$i].'-'.($i + 1);
            }
            $rowData[$idxDate] = array(
                '#type' => 'item', '#title' => $dateArray2[$i],
                '#attributes' => array('outerclass' => array('align-center')),
            );
            if (!empty($idSetoran)){
                $idxDesc = 'description-'.$idpremis.'-'.$dateArray[$i].'-'.($i + 1).'-'.$idSetoran;
            }else{
                $idxDesc = 'description-'.$idpremis.'-'.$dateArray[$i].'-'.($i + 1);
            }
            $rowData[$idxDesc] = array(
                '#type' => 'textfield',
                '#default_value' => $description,
                '#attributes' => array('outerclass' => array('align-left')),
            );
            if (!empty($idSetoran)){
                $idxJumlah = 'jumlah-'.$idpremis.'-'.$dateArray[$i].'-'.($i + 1).'-'.$idSetoran;
            }else{
                $idxJumlah = 'jumlah-'.$idpremis.'-'.$dateArray[$i].'-'.($i + 1);
            }
            $rowData[$idxJumlah] = array(
                '#type' => 'textfield',
                '#default_value' => $jumlah_entry,
                '#attributes' => array('class' => array(
                        'align-right','setoran-value','setoran-'.($i + 1)
                    ),
                ),
            );
            if (!empty($idSetoran)){
                $idxTotal = 'total-'.$dateArray[$i].'-'.($i + 1).'-'.$idSetoran;
            }else{
                $idxTotal = 'total-'.$dateArray[$i].'-'.($i + 1);
            }
            $rowData[$idxTotal] = array(
                '#type' => 'item', '#title' => '<div id="total-'.($i + 1).'">TOTAL</div>',
                '#attributes' => array('outerclass' => array('align-right')),
            );
            $tableRow['r'.($i + 1)] = $rowData;
        }
    }
    return $tableRow;
}
function setoran_form($form, &$form_state, $variables = null){
    set_default_time_zone();
    if (isset($variables['id_premis']) && !empty($variables['id_premis'])){
        $dataPremis = get_data_premis_by_id(null, $variables['id_premis']);
        $month = $variables['month'];
        $year = $variables['year'];
        if (!empty($month) && !empty($year)){
        }else{
            $month = date('n');
            $year = date('Y');
        }
        $intDate = mktime(7,0,0,$month,1,$year);
        $tableHeader = setoran_form_header();
        $tableFooter[] = setoran_form_footer();
        $tableRow = setoran_form_row($variables['id_premis'], $month, $year);
        $form['id_premis'] = array(
            '#type' => 'hidden',
            '#default_value' => $variables['id_premis'],
        );
        $form['table'] = array(
            '#theme' => 'formtable_form_table',
            '#header' => $tableHeader,
            'rows' => $tableRow,
            '#footer' => $tableFooter,
        );
        $form['submit'] = array(
            '#type' => 'submit',
            '#value' => t('Save Setoran'),
        );
    }
    return $form;
}
function setoran_form_submit($form, &$form_state)
{
    global $user;
    if (function_exists('set_user_number_format')){
        set_user_number_format($desIn, $desOut, $separator);
    }else{
        $desIn = '.';
        $desOut = ',';
        $separator = '.';
    }
    set_default_time_zone();
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
                    $savedData['id_premis'] = $explodeIdx[1];
                    $savedData['setoran_date'] = $explodeIdx[2];
                    $savedData['month'] = date('n',$explodeIdx[2]);
                    $savedData['year'] = date('Y',$explodeIdx[2]);
                    $savedData['uid'] = $user->uid;
                    if ($explodeIdx[0] == 'jumlah'){
                        $savedValue = str_replace($separator,'',$colData);
                        $savedValue = str_replace($desOut,'.',$savedValue);
                        $savedData[$explodeIdx[0]] = eval('return '.$savedValue.';');
                        $savedData['jumlah_entry'] = $colData;
                    }else{
                        $savedValue = $colData;
                        $savedData[$explodeIdx[0]] = $savedValue;
                    }
                }
                if (isset($savedData['id']) && !empty($savedData['id'])){
                    //Update record
                    $returnData[] = saveTableData('zpremis_setoran','admin data setoran',$savedData,'id',$savedData['id']);
                    $updated++;
                }else{
                    //Insert record
                    $returnData[] = saveTableData('zpremis_setoran','admin data setoran',$savedData,'id');
                    $inserted++;
                }
            }
        }
        drupal_set_message(t('Data setoran berhasil di save...!!!'));
    }
}

function get_setoran_premis_data($idPremis = null, $month = null, $year = null, $idSetoran = null){
    $tableName = 'zpremis_setoran';
    $fieldArray = array(
        'id', 'id_premis', 'setoran_date', 'jumlah', 'jumlah_entry',
        'description', 'month', 'year', 'created', 'changed', 'uid', 'uid_changed'
    );
    $fieldOrder = array(
        array ('fieldname' => 'id_premis'),
        array('fieldname' => 'setoran_date'),
    );
    $dataSetoran = array();
    if (empty($idSetoran)) {
        $conditionArray = array();
        if (!empty($idPremis)) {
            $consData = new stdClass();
            $consData->fieldName = 'ta.id_premis';
            $consData->value = $idPremis;
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
        $setoranPremis = getTableDataByField(
            $tableName,'access data setoran',$fieldArray,
            $fieldOrder,null,null,null,$conditionArray
        );
        if (!empty($idPremis)) {
            if (count($setoranPremis)){
                for ($i = 0;$i < count($setoranPremis);$i++){
                    $dataSetoran[$setoranPremis[$i]->setoran_date] = $setoranPremis[$i];
                }
            }
        }else{
            if (count($setoranPremis)){
                for ($i = 0;$i < count($setoranPremis);$i++){
                    $dataSetoran[$setoranPremis[$i]->id_premis][] = $setoranPremis[$i];
                }
            }
        }
    }else{
        $setoranPremis = getTableDataByField(
            $tableName,'access data setoran',$fieldArray,
            $fieldOrder,'id',$idSetoran
        );
        $dataSetoran = $setoranPremis[0];
    }
    return $dataSetoran;
}

function get_total_setoran_premis($month = null, $year = null, $idPremis = null){
    $strSQL = 'SELECT id_premis, SUM(jumlah) AS total_setoran ';
    $strSQL .= 'FROM {zpremis_setoran} ';
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
    if (!empty($idPremis)) {
        if ($strSQLCond == ''){
            $strSQLCond .= 'id_premis = :id_premis ';
        }else{
            $strSQLCond .= 'AND id_premis = :id_premis ';
        }
        $arrayValue[':id_premis'] = $idPremis;
    }
    $strSQL .= $strSQLCond.' GROUP BY id_premis';
    $dataSetoran = db_query($strSQL, $arrayValue)->fetchAll();
    $arraySetoran = array();
    if (empty($zone)){
        for ($i = 0;$i < count($dataSetoran);$i++){
            $arraySetoran[$dataSetoran[$i]->id_premis] = $dataSetoran[$i];
        }
    }else{
        $arraySetoran = $dataSetoran[0];
    }
    return $arraySetoran;
}
function total_pengeluaran_header(){
    $tableHeader = array();
    $tableHeader[] = t('KETERANGAN');
    $tableHeader[] = array(
        'data' => t('TARGET'),
        'class' => array(
            'col-input-number', 'align-center'
        ),
    );
    $tableHeader[] = array(
        'data' => t('KELUARAN'),
        'class' => array(
            'col-input-number', 'align-center'
        ),
    );
    $tableHeader[] = array(
        'data' => t('KURANG'),
        'class' => array(
            'col-input-number', 'align-center'
        ),
    );
    $tableHeader[] = array(
        'data' => t('ENTRY'),
        'class' => array(
            'col-input-number',
        ),
    );
    return $tableHeader;
}
function total_pengeluaran_footer($totalKetentuan = 0, $totalPengeluaran = 0, $totalKekurangan = 0){
    global $user;
    if (function_exists('set_user_number_format')){
        set_user_number_format($desIn, $desOut, $separator);
    }else{
        $desIn = '.';
        $desOut = ',';
        $separator = '.';
    }
    $tableHeader = array();
    $tableHeader[] = array(
        'data' => '<strong>'.t('TOTAL').'</strong>',
        'class' => array(
            'align-right'
        ),
    );
    $tableHeader[] = array(
        'data' => '<strong>'.number_format($totalKetentuan,0,$desOut,$separator).'</strong>',
        'class' => array(
            'align-right'
        ),
    );
    $tableHeader[] = array(
        'data' => '<strong>'.number_format($totalPengeluaran,0,$desOut,$separator).'</strong>',
        'class' => array(
            'align-right'
        ),
    );
    $tableHeader[] = array(
        'data' => '<strong>'.number_format($totalKekurangan,0,$desOut,$separator).'</strong>',
        'class' => array(
            'align-right'
        ),
    );
    $tableHeader[] = array(
        'data' => '&nbsp;',
    );
    return $tableHeader;
}
function total_pengeluaran_row($idPremis = null, $month = null, $year = null){
    global $user;
    if (function_exists('set_user_number_format')){
        set_user_number_format($desIn, $desOut, $separator);
    }else{
        $desIn = '.';
        $desOut = ',';
        $separator = '.';
    }
    $tableRow = array();
    if (!empty($month) && !empty($year)){
    }else{
        $month = date('n');
        $year = date('Y');
    }
    if (!empty($idPremis) && !empty($month) && !empty($year)){
        $dataKetentuan = get_total_ketentuan_by_premis($idPremis, $month, $year);
        $addIcon = '<i class="fa fa-plus"></i>';
        $totalKetentuan = 0;
        $totalPengeluaran = 0;
        $totalKekurangan = 0;
        $arrPengeluaran = get_total_pengeluaran_premis($idPremis, $month, $year);
        for ($i = 0;$i < count($dataKetentuan);$i++){
            $rowData = array();
            $rowData[] = $dataKetentuan[$i]['oh_name'];
            $rowData[] = array(
                'data' => number_format($dataKetentuan[$i]['overhead_value'],0,$desOut,$separator),
                'class' => 'align-right',
            );
            $pengeluaran = isset($arrPengeluaran[$dataKetentuan[$i]['id_overhead']]) ? $arrPengeluaran[$dataKetentuan[$i]['id_overhead']] : 0;
            $rowData[] = array(
                'data' => number_format($pengeluaran,0,$desOut,$separator),
                'class' => 'align-right',
            );
            $kekurangan = $dataKetentuan[$i]['overhead_value'] - $pengeluaran;
            $rowData[] = array(
                'data' => number_format($kekurangan,0,$desOut,$separator),
                'class' => 'align-right',
            );
            $totalKetentuan = $totalKetentuan + $dataKetentuan[$i]['overhead_value'];
            $totalPengeluaran = $totalPengeluaran + $pengeluaran;
            $totalKekurangan = $totalKekurangan + ($dataKetentuan[$i]['overhead_value'] - $pengeluaran);
            $outButtonVar = array(
                'element' => array(
                    '#attributes' => array(
                        'class' => array('btn-danger', 'btn-xs', 'no-margin', 'add-oh'),
                        'id' => 'add-out-' . $dataKetentuan[$i]['id'],
                        'name' => 'add-out-' . $dataKetentuan[$i]['id'],
                        'onclick' => 'pengeluaran_premis(\'' . $idPremis . '\', '.$month.','.$year.',\''.$dataKetentuan[$i]['id_overhead'].'\')',
                    ),
                    '#button_type' => 'button',
                    '#value' => $addIcon . ' PENGELUARAN',
                )
            );
            $outButton = theme('button', $outButtonVar);
            $rowData[] = $outButton;
            $tableRow[] = $rowData;
        }
    }
    return array($tableRow,$totalKetentuan,$totalPengeluaran,$totalKekurangan);
}
function get_total_ketentuan_by_premis($idpremis = null, $month = null, $year = null){
    global $user;
    $arrayKetentuan = array();
    if (!empty($idpremis)){
        $arrayOH = get_data_overhead();
        $ohName = array();
        for ($i = 0;$i < count($arrayOH);$i++){
            $ohName[$arrayOH[$i]->id] = $arrayOH[$i]->nama;
        }
        $currMonth = date('n');
        $currYear = date('Y');
        $strSQL = 'SELECT SUM(overhead_value) AS total_oh, id_overhead, id_premis FROM {zoverhead_staff} ';
        $strSQL .= 'WHERE id_premis = :id_premis ';
        $strSQL .= 'GROUP BY id_premis, id_overhead ORDER BY id_premis, id_overhead';
        $dataOverhead = db_query($strSQL, array(':id_premis' => $idpremis))->fetchAll();
        $arrOverhead = array();
        for ($i = 0;$i < count($dataOverhead);$i++){
            $arrOverhead[$dataOverhead[$i]->id_overhead] = $dataOverhead[$i]->total_oh;
        }
        $strSQL = 'SELECT pket.id, pket.id_overhead, pket.overhead_value,';
        $strSQL .= 'pket.id_premis, pket.month, pket.year FROM {zpremis_ketentuan} pket ';
        $strSQL .= 'LEFT JOIN {zoverhead} oh ON pket.id_overhead = oh.id ';
        $strSQL .= 'LEFT JOIN {zoverhead_category} ohc ON oh.id_category = ohc.id ';
        $strSQL .= 'WHERE id_premis = :id_premis AND month = :month AND year = :year ';
        $strSQL .= 'ORDER BY ohc.weight, oh.weight';
        $arrayValue = array(':id_premis' => $idpremis, ':month' => $month, ':year' => $year);
        $dataKetentuan = db_query($strSQL, $arrayValue)->fetchAll();
        if (count($dataKetentuan)){
            for ($i = 0;$i < count($dataKetentuan);$i++){
                $idKetentuan = $dataKetentuan[$i]->id;
                $idOverhead = $dataKetentuan[$i]->id_overhead;
                $ketentuanValue = $dataKetentuan[$i]->overhead_value;
                $savedData = array();
                $savedData['id'] = $idKetentuan;
                $savedData['id_premis'] = $idpremis;
                $savedData['month'] = $month;
                $savedData['year'] = $year;
                $savedData['uid_changed'] = $user->uid;
                $newData = null;
                if (isset($arrOverhead[$idOverhead]) && $month == $currMonth && $year == $currYear){
                    if ($ketentuanValue != $arrOverhead[$idOverhead]){
                        $savedData['id_overhead'] = $idOverhead;
                        $savedData['overhead_value'] = $arrOverhead[$idOverhead];
                        $newData = saveTableData('zpremis_ketentuan','admin data pengeluaran',$savedData,'id',$savedData['id']);
                    }
                }
                if (!empty($newData)){
                    $newData['oh_name'] = $ohName[$newData['id_overhead']];
                    $arrayKetentuan[] = $newData;
                }else{
                    $newData['id'] = $dataKetentuan[$i]->id;
                    $newData['id_premis'] = $dataKetentuan[$i]->id_premis;
                    $newData['month'] = $dataKetentuan[$i]->month;
                    $newData['year'] = $dataKetentuan[$i]->year;
                    $newData['id_overhead'] = $dataKetentuan[$i]->id_overhead;
                    $newData['overhead_value'] = $dataKetentuan[$i]->overhead_value;
                    $newData['oh_name'] = $ohName[$newData['id_overhead']];
                    $arrayKetentuan[] = $newData;
                }
            }
        }else{
            if (count($arrOverhead)){
                foreach($arrayOH as $ohData){
                    $savedData = array();
                    $savedData['id_premis'] = $idpremis;
                    $savedData['month'] = $month;
                    $savedData['year'] = $year;
                    $savedData['uid'] = $user->uid;
                    $savedData['id_overhead'] = $ohData->id;
                    if (isset($arrOverhead[$ohData->id])){
                        $overheadValue = $arrOverhead[$ohData->id];
                    }else{
                        $overheadValue = 0;
                    }
                    $savedData['overhead_value'] = $overheadValue;
                    $newData = saveTableData('zpremis_ketentuan','admin data pengeluaran',$savedData,'id');
                    $newData['oh_name'] = $ohName[$ohData->id];
                    $arrayKetentuan[] = $newData;
                }
            }
        }
    }
    return $arrayKetentuan;
}
function form_detail_pengeluaran($form, &$form_state, $variables = null){
    global $user;
    if (function_exists('set_user_number_format')){
        set_user_number_format($desIn, $desOut, $separator);
    }else{
        $desIn = '.';
        $desOut = ',';
        $separator = '.';
    }
    if (isset($variables['month']) && isset($variables['year'])){
        $month = $variables['month'];
        $year = $variables['year'];
    }else {
        $month = date('n');
        $year = date('Y');
    }
    $currDate = 1;
    if ($month == date('n') && $year == date('Y')){
        $currDate = date('d');
    }
    $dataOverhead = null;
    if (isset($variables['id_overhead'])){
        $dataOverhead = get_data_overhead(null, $variables['id_overhead']);
    }
    $intDate = mktime(7, 0, 0, $month, 1, $year);
    $form['#attributes'] = array('class' => array('form-inline'));
    $form['id_pengeluaran'] = array(
        '#type' => 'hidden',
        '#default_value' => 0,
        '#attributes' => array('id' => 'id-pengeluaran',),
    );
    if (isset($variables['id_premis']) && !empty($variables['id_premis'])){
        $dataPremis = get_data_premis_by_id(null, $variables['id_premis']);
        $form['info_premis'] = array(
            '#type' => 'item',
            '#markup' => t('Premis').' : '.$dataPremis->nama,
            '#prefix' => '<div><strong>',
            '#suffix' => '</strong></div>',
        );
        $form['id_premis'] = array(
            '#type' => 'hidden',
            '#default_value' => $variables['id_premis'],
        );
    }
    if ($dataOverhead !== null){
        $form['info_overhead'] = array(
            '#type' => 'item',
            '#markup' => t('Overhead').' : '.$dataOverhead->nama,
            '#prefix' => '<div><strong>',
            '#suffix' => '</strong></div>',
        );
        $form['id_overhead'] = array(
            '#type' => 'hidden',
            '#default_value' => $dataOverhead->id,
        );
    }
    $form['tanggal'] = array(
        '#type' => 'textfield',
        '#title' => t('Tanggal'),
        '#default_value' => $currDate,
        '#attributes' => array('class' => array('col-number')),
        //'#suffix' => '-'.date('M', $intDate).'-'.date('Y',$intDate).'&nbsp;&nbsp;',
    );
    $form['info_bulan'] = array(
        '#type' => 'item',
        '#markup' => date('M-Y', $intDate).'&nbsp;&nbsp;',
        '#prefix' => '<strong>',
        '#suffix' => '</strong>',
    );
    $form['month'] = array(
        '#type' => 'hidden',
        '#default_value' => $month,
    );
    $form['year'] = array(
        '#type' => 'hidden',
        '#default_value' => $year,
    );
    $form['jumlah'] = array(
        '#type' => 'textfield',
        '#title' => t('Jumlah'),
        '#default_value' => 0,
        '#attributes' => array('class' => array('col-number jumlah-pengeluaran')),
    );
    $form['keterangan'] = array(
        '#type' => 'textfield',
        '#title' => t('Keterangan'),
        '#default_value' => '',
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save Pengeluaran'),
        '#attributes' => array('class' => array('btn-sm btn-primary')),
        '#prefix' => '<div>',
    );
    $form['backtosetoran'] = array(
        '#type' => 'submit',
        '#value' => t('Kembali Ke Setoran'),
        '#attributes' => array('class' => array('btn-sm btn-danger')),
        '#suffix' => '</div>',
    );
    return $form;
}

function form_detail_pengeluaran_submit($form, &$form_state)
{
    global $user;
    if (function_exists('set_user_number_format')){
        set_user_number_format($desIn, $desOut, $separator);
    }else{
        $desIn = '.';
        $desOut = ',';
        $separator = '.';
    }
    set_default_time_zone();
    $values = $form_state['values'];
    $savedData = array();
    if ($values['op'] == 'Kembali Ke Setoran'){
        drupal_goto('setoran/'.$values['id_premis'].'/'.$values['month'].'/'.$values['year']);
    }else {
        if (!empty($values['tanggal']) && !empty($values['jumlah'])) {
            if (isset($values['id_pengeluaran']) && !empty($values['id_pengeluaran'])) {
                $savedData['id'] = $values['id_pengeluaran'];
            }
            $savedData['id_premis'] = $values['id_premis'];
            $savedData['id_overhead'] = $values['id_overhead'];
            $savedData['pengeluran_date'] = mktime(7, 0, 0, $values['month'], $values['tanggal'], $values['year']);
            $savedData['jumlah_entry'] = $values['jumlah'];
            $savedValue = str_replace($separator, '', $values['jumlah']);
            $savedValue = str_replace($desOut, '.', $savedValue);
            $savedData['jumlah'] = eval('return ' . $savedValue . ';');
            $savedData['month'] = $values['month'];
            $savedData['year'] = $values['year'];
            $savedData['description'] = $values['keterangan'];
            $savedData['uid'] = $user->uid;
            $returnData = array();
            if (isset($savedData['id']) && !empty($savedData['id'])) {
                $returnData[] = saveTableData('zpremis_pengeluaran', 'admin data pengeluaran', $savedData, 'id', $savedData['id']);
            } else {
                $returnData[] = saveTableData('zpremis_pengeluaran', 'admin data pengeluaran', $savedData, 'id');
            }
            if (count($returnData)) {
                drupal_set_message('Data pengeluaran berhasil disimpan..!!');
            } else {
                drupal_set_message('Data pengeluaran gagal disimpan..!!', 'error');
            }
        }
    }
}

function input_detail_pengeluaran($idPremis = null, $month = null, $year = null, $idOverhead = null){
    $module_path = drupal_get_path('module','ikhwan_core');
    $csspath = $module_path.'/css/custom-style.css';
    drupal_add_css($csspath);
    $jspath = $module_path.'/js/jquery.masknumber.js';
    drupal_add_js($jspath,array('scope' => 'footer', 'weight' => 5));
    $module_path  = drupal_get_path('module','setoran_pengeluaran');
    $jspath = $module_path.'/js/input_pengeluaran.js';
    drupal_add_js($jspath,array('scope' => 'footer', 'weight' => 5));
    $variables['month'] = $month;
    $variables['year'] = $year;
    $variables['id_premis'] = $idPremis;
    $variables['id_overhead'] = $idOverhead;
    $form = drupal_get_form('form_detail_pengeluaran',$variables);
    $formDetPengeluaran = drupal_render($form);
    $tablePengeluaran = create_table_detail_pengeluaran($idPremis, $month, $year, $idOverhead);
    return $formDetPengeluaran.$tablePengeluaran;
}
function create_table_detail_pengeluaran($idPremis = null, $month = null, $year = null, $idOverhead = null){
    global $user;
    if (function_exists('set_user_number_format')){
        set_user_number_format($desIn, $desOut, $separator);
    }else{
        $desIn = '.';
        $desOut = ',';
        $separator = '.';
    }
    set_default_time_zone();
    $attributes['datatable_options'] = array(
        'bFilter'   => TRUE,
        'bInfo'     => TRUE,
        'bStateSave' => TRUE,
        'bPaginate' => FALSE,
        'bSort' => FALSE,
    );
    $header = array(
        array(
            'data' => t('No.'),
            'datatable_options' => array(
                'bSortable' => FALSE,
                'bSearchable' => FALSE,
            ),
            'class' => 'col-number',
        ),
        array(
            'data' => t('Tanggal'),
            'datatable_options' => array(
                'bSortable' => FALSE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Jumlah'),
            'datatable_options' => array(
                'bSortable' => FALSE,
                'bSearchable' => TRUE,
            ),
        ),
        array(
            'data' => t('Keterangan'),
            'datatable_options' => array(
                'bSortable' => FALSE,
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
            'data' => t('Hapus'),
            'class' => array('col-number'),
            'datatable_options' => array(
                'bSortable' => FALSE,
                'bSearchable' => FALSE,
            ),
        ),
    );
    $dataPengeluaran = get_data_pengeluaran_premis($idPremis, $month, $year, $idOverhead);
    $totalPengeluaran = 0;
    $rows = array();
    for ($i = 0;$i < count($dataPengeluaran);$i++){
        $pengeluaran = array();
        $pengeluaran[] = array(
            'data' => ($i + 1),
            'class' => 'align-right',
        );
        $pengeluaran[] = date('d-M-Y', $dataPengeluaran[$i]->pengeluran_date);
        $pengeluaran[] = array(
            'data' => number_format($dataPengeluaran[$i]->jumlah,2,$desOut,$separator),
            'class' => 'align-right',
        );
        $totalPengeluaran = $totalPengeluaran + $dataPengeluaran[$i]->jumlah;
        $pengeluaran[] = $dataPengeluaran[$i]->description;
        $editIcon = '<i class="fa fa-edit"></i>';
        $editButtonVar = array(
            'element' => array(
                '#attributes' => array(
                    'class' => array('btn-info', 'btn-xs', 'no-margin', 'edit-pengeluaran'),
                    'id' => 'edit-pengeluaran-' . $dataPengeluaran[$i]->id,
                    'name' => 'edit-pengeluaran-' . $dataPengeluaran[$i]->id,
                    'onclick' => 'edit_pengeluaran(\'' . $dataPengeluaran[$i]->id . '\')',
                ),
                '#button_type' => 'button',
                '#value' => $editIcon . ' EDIT',
            )
        );
        $editButton = theme('button', $editButtonVar);
        $pengeluaran[] = $editButton;
        $delIcon = '<i class="fa fa-trash-o"></i>';
        $delButtonVar = array(
            'element' => array(
                '#attributes' => array(
                    'class' => array('btn-danger', 'btn-xs', 'no-margin', 'del-pengeluaran'),
                    'id' => 'del-pengeluaran-' . $dataPengeluaran[$i]->id,
                    'name' => 'del-pengeluaran-' . $dataPengeluaran[$i]->id,
                    'onclick' => 'delete_pengeluaran(\'' . $dataPengeluaran[$i]->id . '\')',
                ),
                '#button_type' => 'button',
                '#value' => $delIcon . ' HAPUS',
            )
        );
        $delButton = theme('button', $delButtonVar);
        $pengeluaran[] = $delButton;
        $rows[] = $pengeluaran;
    }
    $footer[] = array(
        array(
            'data' => '<strong>'.t('TOTAL').'</strong>',
            'class' => 'align-right',
            'colspan' => 2,
        ),
        array(
            'data' => '<strong>'.number_format($totalPengeluaran,2,$desOut,$separator).'</strong>',
            'class' => 'align-right',
        ),
        array(
            'data' => '&nbsp;',
            'colspan' => 3,
        ),
    );
    $variables = array(
        'attributes' => $attributes,
        'header' => $header,
        'rows' => $rows,
        'footer' => $footer,
    );
    $tablePengeluaran = theme('datatable', $variables);
    return $tablePengeluaran;
}

function get_data_pengeluaran_premis($idPremis = null, $month = null, $year = null, $idOverhead = null){
    $strSQL = 'SELECT id, id_overhead, id_premis, pengeluran_date, jumlah, ';
    $strSQL .= 'jumlah_entry, description, month, year, created, changed, ';
    $strSQL .= 'uid, uid_changed FROM {zpremis_pengeluaran} ';
    $strSQL .= 'WHERE id_premis = :id_premis AND id_overhead = :id_overhead AND ';
    $strSQL .= 'year = :year AND month = :month ORDER BY pengeluran_date';
    $arrValue = array(
        ':id_premis' => $idPremis,
        ':id_overhead' => $idOverhead,
        ':year' => $year,
        ':month' => $month,
    );
    $dataPengeluaran = db_query($strSQL, $arrValue)->fetchAll();
    return $dataPengeluaran;
}
function get_data_pengeluaran_premis_by_id($idPengeluaran = null){
    $strSQL = 'SELECT id, id_overhead, id_premis, pengeluran_date, jumlah, ';
    $strSQL .= 'jumlah_entry, description, month, year, created, changed, ';
    $strSQL .= 'uid, uid_changed FROM {zpremis_pengeluaran} ';
    $strSQL .= 'WHERE id = :id_pengeluaran';
    $arrValue = array(
        ':id_pengeluaran' => $idPengeluaran,
    );
    $dataPengeluaran = db_query($strSQL, $arrValue)->fetchAll();
    $arrPengeluaran = array();
    for ($i = 0;$i < count($dataPengeluaran);$i++){
        $dataPengeluaran[$i]->tanggal = date('j',$dataPengeluaran[$i]->pengeluran_date);
        $arrPengeluaran[] = $dataPengeluaran[$i];
    }
    return $dataPengeluaran;
}
function get_data_pengeluaran_ajax($idPengeluaran = null){
    $dataPengeluaran = get_data_pengeluaran_premis_by_id($idPengeluaran);
    print json_encode($dataPengeluaran);
    exit();
}
function get_total_pengeluaran_premis($idPremis = null, $month = null, $year = null, $idOverhead = null){
    $arrValue = array(
        ':id_premis' => $idPremis,
        ':year' => $year,
        ':month' => $month,
    );
    $strSQL = 'SELECT SUM(jumlah) AS total_pengeluaran,id_premis,id_overhead FROM {zpremis_pengeluaran} ';
    $strSQL .= 'WHERE id_premis = :id_premis AND ';
    if (!empty($idOverhead)){
        $strSQL .= 'id_overhead = :id_overhead AND ';
        $arrValue[':id_overhead'] = $idOverhead;
    }
    $strSQL .= 'year = :year AND month = :month GROUP BY id_premis, id_overhead';
    $dataPengeluaran = db_query($strSQL, $arrValue)->fetchAll();
    $arrTotal = array();
    for ($i = 0;$i < count($dataPengeluaran);$i++){
        if (empty($idPremis)){
            $arrTotal[$dataPengeluaran[$i]->id_premis][$dataPengeluaran[$i]->id_overhead] = $dataPengeluaran[$i]->total_pengeluaran;
        }else{
            $arrTotal[$dataPengeluaran[$i]->id_overhead] = $dataPengeluaran[$i]->total_pengeluaran;
        }
    }
    return $arrTotal;
}
function delete_detail_pengeluaran($idPengeluaran = null){
    $dataPengeluaran = get_data_pengeluaran_premis_by_id($idPengeluaran);
    if (!empty($idPengeluaran)){
        $conditionData = array();
        $consObj = new stdClass();
        $consObj->fieldName = 'id';
        $consObj->fieldValue = $idPengeluaran;
        $consObj->status = 'and';
        $conditionData[] = $consObj;
        $returnData = deleteTableData('zpremis_pengeluaran','admin data pengeluaran',$conditionData);
        drupal_set_message('Detail pengeluaran berhasil dihapus...!!!','error');
    }
    drupal_goto('inputdetailpengeluaran/'.$dataPengeluaran[0]->id_premis.'/'.$dataPengeluaran[0]->month.'/'.$dataPengeluaran[0]->year.'/'.$dataPengeluaran[0]->id_overhead);
    return $returnData;
}
function get_total_overhead_by_zone($month = null, $year = null, $zone = null){
    $dataOverheadZone = null;
    if ($month !== null && $year !== null){
        $dataZone = getZoneByCode($zone);
        if (count($dataZone)){
            $dataOverheadZone = array();
            for ($i = 0;$i < count($dataZone);$i++){
                $strSQL = 'SELECT SUM(overhead_value) AS total_oh FROM {zpremis_ketentuan} pket ';
                $strSQL .= 'LEFT JOIN {zdatapremis} prem ON pket.id_premis = prem.id ';
                $strSQL .= 'LEFT JOIN {zdatazone} zon ON prem.zone = zon.zone ';
                $strSQL .= 'WHERE pket.month = :month AND pket.year = :year ';
                $strSQL .= 'AND zon.zone = :zone GROUP BY prem.zone';
                $arrValue = array(':month' => $month, ':year' => $year, ':zone' => $dataZone[$i]->zone);
                $totalOhZone = db_query($strSQL,$arrValue)->fetchAll();
                if (!count($totalOhZone)){
                    $strSQL = 'SELECT SUM(overhead_value) AS total_oh FROM {zoverhead_staff} ohs ';
                    $strSQL .= 'LEFT JOIN {zdatapremis} prem ON ohs.id_premis = prem.id ';
                    $strSQL .= 'LEFT JOIN {zdatazone} zon ON prem.zone = zon.zone ';
                    $strSQL .= 'WHERE zon.zone = :zone GROUP BY prem.zone';
                    $arrValue = array(':zone' => $dataZone[$i]->zone);
                    $totalOhZone = db_query($strSQL,$arrValue)->fetchAll();
                }
                if (count($totalOhZone)){
                    $dataOverheadZone[$dataZone[$i]->zone] = $totalOhZone[0]->total_oh;
                }else{
                    $dataOverheadZone[$dataZone[$i]->zone] = 0;
                }

            }
        }
    }
    arsort($dataOverheadZone);
    return $dataOverheadZone;
}
function get_total_pengeluaran_overhead_by_zone($month = null, $year = null, $zone = null){
    $dataPemgeluaranOhZone = null;
    if ($month !== null && $year !== null){
        $dataZone = getZoneByCode($zone);
        if (count($dataZone)){
            $dataPemgeluaranOhZone = array();
            for ($i = 0;$i < count($dataZone);$i++){
                $strSQL = 'SELECT SUM(jumlah) AS total_out FROM {zpremis_pengeluaran} ohs ';
                $strSQL .= 'LEFT JOIN {zdatapremis} prem ON ohs.id_premis = prem.id ';
                $strSQL .= 'LEFT JOIN {zdatazone} zon ON prem.zone = zon.zone ';
                $strSQL .= 'WHERE zon.zone = :zone GROUP BY prem.zone';
                $arrValue = array(':zone' => $dataZone[$i]->zone);
                $totalPengeluaranOh = db_query($strSQL,$arrValue)->fetchAll();
                if (count($totalPengeluaranOh)){
                    $dataPemgeluaranOhZone[$dataZone[$i]->zone] = $totalPengeluaranOh[0]->total_out;
                }else{
                    $dataPemgeluaranOhZone[$dataZone[$i]->zone] = 0;
                }
            }
        }
    }
    return $dataPemgeluaranOhZone;
}
function get_total_pengeluaran_oh_by_premis($month = null, $year = null, $idPremis = null){
    $dataPengeluaranOhPremis = null;
    if ($month !== null && $year !== null){
        $dataPremis = get_data_premis_by_id($idPremis);
        if (count($dataPremis)){
            if (empty($idPremis)) {
                $dataPengeluaranOhPremis = array();
                for ($i = 0; $i < count($dataPremis); $i++) {
                    $strSQL = 'SELECT SUM(jumlah) AS total_out FROM {zpremis_pengeluaran} ';
                    $strSQL .= 'WHERE id_premis = :id_premis GROUP BY id_premis';
                    $arrValue = array(':id_premis' => $dataPremis[$i]->id);
                    $totalPengeluaranOh = db_query($strSQL,$arrValue)->fetchAll();
                    if (count($totalPengeluaranOh)) {
                        $dataPengeluaranOhPremis[$dataPremis[$i]->id] = $totalPengeluaranOh[0]->total_out;
                    } else {
                        $dataPengeluaranOhPremis[$dataPremis[$i]->id] = 0;
                    }
                }
            }
        }
    }
    return $dataPengeluaranOhPremis;
}
function get_total_overhead_by_zone_converted($month = null, $year = null, $zone = null){
    $dataOverheadZone = null;
    $convertedVal = get_currency_premis_to_myr();
    if ($month !== null && $year !== null){
        $dataZone = getZoneByCode($zone);
        if (count($dataZone)){
            $dataOverheadZone = array();
            for ($i = 0;$i < count($dataZone);$i++){
                $strSQL = 'SELECT prem.id, SUM(overhead_value) AS total_oh, prem.currency FROM {zpremis_ketentuan} pket ';
                $strSQL .= 'LEFT JOIN {zdatapremis} prem ON pket.id_premis = prem.id ';
                $strSQL .= 'LEFT JOIN {zdatazone} zon ON prem.zone = zon.zone ';
                $strSQL .= 'WHERE pket.month = :month AND pket.year = :year ';
                $strSQL .= 'AND zon.zone = :zone GROUP BY prem.id';
                $arrValue = array(':month' => $month, ':year' => $year, ':zone' => $dataZone[$i]->zone);
                $totalOhZone = db_query($strSQL,$arrValue)->fetchAll();
                if (!count($totalOhZone)){
                    $strSQL = 'SELECT prem.id, SUM(overhead_value) AS total_oh, prem.currency FROM ';
                    $strSQL .= '{zoverhead_staff} ohs ';
                    $strSQL .= 'LEFT JOIN {zdatapremis} prem ON ohs.id_premis = prem.id ';
                    $strSQL .= 'LEFT JOIN {zdatazone} zon ON prem.zone = zon.zone ';
                    $strSQL .= 'WHERE zon.zone = :zone GROUP BY prem.id';
                    $arrValue = array(':zone' => $dataZone[$i]->zone);
                    $totalOhZone = db_query($strSQL,$arrValue)->fetchAll();
                }
                if (count($totalOhZone)){
                    $gtOhZone = 0;
                    for ($j = 0;$j < count($totalOhZone);$j++){
                        $gtOhZone = $gtOhZone + ($convertedVal[$totalOhZone[$j]->id]*$totalOhZone[$j]->total_oh);
                    }
                    $dataOverheadZone[$dataZone[$i]->zone] = $gtOhZone;
                }else{
                    $dataOverheadZone[$dataZone[$i]->zone] = 0;
                }
            }
        }
    }
    arsort($dataOverheadZone);
    return $dataOverheadZone;
}
function get_currency_premis_to_myr(){
    $dataPremis = get_data_premis_by_id();
    $currencyConvert = array();
    $defaultCurrency = variable_get('google_currency_converter_to', '');
    $calculatedCurr = array();
    $arrCalcCurrency = array();
    for ($i = 0;$i < count($dataPremis);$i++){
        if ($dataPremis[$i]->currency != $defaultCurrency) {
            if (!in_array($dataPremis[$i]->currency, $calculatedCurr)) {
                $calculatedCurr[] = $dataPremis[$i]->currency;
                $arrCalcCurrency[$dataPremis[$i]->currency] = get_google_convertion(1, $dataPremis[$i]->currency, $defaultCurrency);
                $currencyConvert[$dataPremis[$i]->id] = $arrCalcCurrency[$dataPremis[$i]->currency];
            } else {
                $currencyConvert[$dataPremis[$i]->id] = $arrCalcCurrency[$dataPremis[$i]->currency];
            }
        }else {
            $currencyConvert[$dataPremis[$i]->id] = 1;
        }
    }
    return $currencyConvert;
}
function get_google_convertion($amount, $from, $to){
    $url = $url = "https://www.google.com/finance/converter?a=$amount&from=$from&to=$to";
    $ch = curl_init();
    //set the url, number of POST vars, POST data
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1); //Set curl to return the data instead of printing it to the browser.
    curl_setopt($ch, CURLOPT_POST, 0);
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_COOKIEJAR, 'cookie.txt');
    $result = curl_exec($ch);
    preg_match("/<span class=bld>(.*)<\/span>/", $result, $converted);
    $converted = preg_replace("/[^0-9.]/", "", isset($converted[1]) ? $converted[1] : NULL);
    return $converted;
}