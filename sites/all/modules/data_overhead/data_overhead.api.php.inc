<?php

/**
 * @return string
 */
function overhead_category()
{
    $core_module_path = drupal_get_path('module','ikhwan_core');
    $csspath = $core_module_path.'/css/custom-style.css';
    drupal_add_css($csspath);
    $formOverheadCat = '';
    $form = drupal_get_form('overhead_category_form');
    $formOverheadCat = drupal_render($form);
    return $formOverheadCat;
}

/**
 * @param $form
 * @param $form_state
 * @param null $variables
 * @return mixed
 */
function overhead_category_form($form, &$form_state, $variables = null)
{
    set_default_time_zone();
    $tableHeader = create_overhead_category_header();
    $tableRow = create_overhead_category_row();
    $tableFooter[] = create_overhead_category_footer();
    $form['basic'] = array(
        '#type' => 'fieldset',
        '#title' => 'DATA OVERHEAD CATEGORY',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
    );
    $form['basic']['table'] = array(
        '#theme' => 'formtable_form_table',
        '#header' => $tableHeader,
        'rows' => $tableRow,
        '#footer' => $tableFooter,
    );
    $form['basic']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('SAVE OVERHEAD CATEGORY'),
    );
    return $form;
}
function overhead_category_form_submit($form, &$form_state)
{
    global $user;
    if (isset($form_state['values']['rows'])) {
        $values = $form_state['values']['rows'];
    } else {
        $values = $form_state['values'];
    }
    $returnData = array();
    if (count($values)){
        foreach ($values as $idxRow => $categoryArr){
            if (count($categoryArr)){
                $savedData = array();
                foreach ($categoryArr as $idxCat => $categoryData){
                    $explodeIdx = explode('-',$idxCat);
                    $savedData[$explodeIdx[0]] = $categoryData;
                    if ($explodeIdx[1] != 'new'){
                        $savedData['id'] = $explodeIdx[1];
                    }
                }
                if (!isset($savedData['weight']) || empty($savedData['weight'])){
                    $savedData['weight'] = 0;
                }
                if (isset($savedData['id']) && !empty($savedData['id'])){
                    if (isset($savedData['category']) && !empty($savedData['category'])) {
                        $returnData[] = saveTableData('zoverhead_category', 'admin data overhead', $savedData, 'id', $savedData['id']);
                    }else{
                        $relatedOverhead = get_data_overhead($savedData['id'], null);
                        if (!count($relatedOverhead)){
                            $conditionData = array();
                            $consObj = new stdClass();
                            $consObj->fieldName = 'id';
                            $consObj->fieldValue = $savedData['id'];
                            $consObj->status = 'and';
                            $conditionData[] = $consObj;
                            $returnData[] = deleteTableData('zoverhead_category', 'admin data overhead', $conditionData);
                        }
                    }
                }else{
                    if (isset($savedData['category']) && !empty($savedData['category'])) {
                        $returnData[] = saveTableData('zoverhead_category', 'admin data overhead', $savedData, 'id');
                    }
                }

            }
        }
        if (count($returnData)){
            drupal_set_message('Overhead Category berhasil disimpan...!!');
        }
    }
    return $returnData;
}
function create_overhead_category_header()
{
    $tableHeader = array();
    $tableHeader[] = array(
        'data' => t('NO.'),
        'class' => array(
            'col-number',
        ),
    );
    $tableHeader[] = array(
        'data' => t('CATEGORY'),
        'class' => array(
            'col-title',
        ),
    );
    $tableHeader[] = t('DESCRIPTION');
    $tableHeader[] = array(
        'data' => t('WEIGHT'),
        'class' => array(
            'col-input-number',
        ),
    );
    return $tableHeader;
}
function create_overhead_category_footer(){
    $tableHeader = array();
    $tableHeader[] = array(
        'data' => t('NO.'),
        'class' => array(
            'col-number',
        ),
    );
    $tableHeader[] = array(
        'data' => t('CATEGORY'),
        'class' => array(
            'col-title',
        ),
    );
    $tableHeader[] = t('DESCRIPTION');
    $tableHeader[] = array(
        'data' => t('WEIGHT'),
        'class' => array(
            'col-input-number',
        ),
    );
    return $tableHeader;
}
function create_overhead_category_row(){
    $arrayCategoryOverhead = get_data_overhead_category();
    $tableRow = array();
    $tableRow['#tree'] = TRUE;
    $counter = 1;
    for ($i = 0;$i < count($arrayCategoryOverhead);$i++){
        $colData = array();
        $colData['no-'.$counter] = array(
            '#type' => 'item', '#title' => $counter,
            '#attributes' => array('outerclass' => array('align-right')),
        );
        $colData['category-'.$arrayCategoryOverhead[$i]->id] = array(
            '#type' => 'textfield',
            '#default_value' => $arrayCategoryOverhead[$i]->category,
            '#attributes' => array('class' => array('input-category')),
        );
        $colData['description-'.$arrayCategoryOverhead[$i]->id] = array(
            '#type' => 'textarea',
            '#default_value' => $arrayCategoryOverhead[$i]->description,
            '#attributes' => array('class' => array('input-description')),
        );
        $colData['weight-'.$arrayCategoryOverhead[$i]->id] = array(
            '#type' => 'textfield',
            '#default_value' => $arrayCategoryOverhead[$i]->weight,
            '#attributes' => array('class' => array('input-weight')),
        );
        $tableRow['r-'.$counter] = $colData;
        $counter++;
    }
    for ($i = 0;$i < 2;$i++){
        $colData = array();
        $colData['no-'.$counter] = array(
            '#type' => 'item', '#title' => $counter,
            '#attributes' => array('outerclass' => array('align-right')),
        );
        $colData['category-new-'.($i+1)] = array(
            '#type' => 'textfield',
            '#default_value' => '',
            '#attributes' => array('class' => array('input-category')),
        );
        $colData['description-new-'.($i+1)] = array(
            '#type' => 'textarea',
            '#default_value' => '',
            '#attributes' => array('class' => array('input-description')),
        );
        $colData['weight-new-'.($i+1)] = array(
            '#type' => 'textfield',
            '#default_value' => '',
            '#attributes' => array('class' => array('input-weigth')),
        );
        $tableRow['r-'.$counter] = $colData;
        $counter++;
    }
    return $tableRow;
}
function list_overhead(){
    $core_module_path = drupal_get_path('module','ikhwan_core');
    $csspath = $core_module_path.'/css/custom-style.css';
    drupal_add_css($csspath);
    $formOverhead = '';
    $form = drupal_get_form('form_add_overhead');
    $formOverhead .= drupal_render($form);
    return $formOverhead;
}
function create_overhead_header(){
    $tableHeader = array();
    $tableHeader[] = array(
        'data' => t('NO.'),
        'class' => array(
            'col-number',
        ),
    );
    $tableHeader[] = array(
        'data' => t('CATEGORY'),
        'class' => array(
            'col-title',
        ),
    );
    $tableHeader[] = t('OVERHEAD');
    $tableHeader[] = t('DEFAULT VALUE');
    $tableHeader[] = t('DESCRIPTION');
    $tableHeader[] = array(
        'data' => t('WEIGHT'),
        'class' => array(
            'col-input-number',
        ),
    );
    $tableHeader[] = t('PREMIS');
    return $tableHeader;
}
function create_overhead_footer(){
    $tableHeader = array();
    $tableHeader[] = array(
        'data' => t('NO.'),
        'class' => array(
            'col-number',
        ),
    );
    $tableHeader[] = array(
        'data' => t('CATEGORY'),
        'class' => array(
            'col-title',
        ),
    );
    $tableHeader[] = t('OVERHEAD');
    $tableHeader[] = t('DEFAULT VALUE');
    $tableHeader[] = t('DESCRIPTION');
    $tableHeader[] = array(
        'data' => t('WEIGHT'),
        'class' => array(
            'col-input-number',
        ),
    );
    $tableHeader[] = array(
        'data' => t('PREMIS'),
        'class' => array(
            'col-input-number',
        ),
    );
    return $tableHeader;
}
function create_overhead_row(){
    $tableRow = array();
    $tableRow['#tree'] = TRUE;
    $overheadCategory = get_data_overhead_category();
    $counter = 1;
    $dataZone = get_data_zone();
    $arrZone = array();
    for ($i = 0;$i < count($dataZone);$i++){
        $arrZone[$dataZone[$i]->zone] = $dataZone[$i]->nama;
    }
    $dataPremis = get_data_premis_by_id();
    $premisOpt = array();
    for ($i = 0;$i < count($dataPremis);$i++){
        $premisOpt[$dataPremis[$i]->id] = $dataPremis[$i]->nama.' - '.$arrZone[$dataPremis[$i]->zone];
    }
    for ($i = 0;$i < count($overheadCategory);$i++){
        $categoryDt = $overheadCategory[$i];
        $overheadArr = get_data_overhead($categoryDt->id);
        for ($j = 0;$j < count($overheadArr);$j++) {
            $overheadDt = $overheadArr[$j];
            $colData = array();
            $colData['no-' . $counter] = array(
                '#type' => 'item', '#title' => $counter,
                '#attributes' => array('outerclass' => array('align-right')),
            );
            if ($j == 0){
                $colData['cat-' . $categoryDt->id] = array(
                    '#type' => 'item', '#title' => $categoryDt->category,
                );
            }else{
                $colData['cat-' . $categoryDt->id] = array(
                    '#type' => 'item', '#title' => '',
                );
            }
            $colData['nama-' . $overheadDt->id.'-'.$categoryDt->id] = array(
                '#type' => 'textfield',
                '#default_value' => $overheadDt->nama,
            );
            $colData['default_value-' . $overheadDt->id.'-'.$categoryDt->id] = array(
                '#type' => 'textfield',
                '#default_value' => $overheadDt->default_value,
            );
            $colData['description-'.$overheadDt->id.'-'.$categoryDt->id] = array(
                '#type' => 'textarea',
                '#default_value' => $overheadDt->description,
                '#attributes' => array('class' => array('input-description')),
            );
            $colData['weight-'.$overheadDt->id.'-'.$categoryDt->id] = array(
                '#type' => 'textfield',
                '#default_value' => $overheadDt->weight,
                '#attributes' => array('class' => array('input-weigth')),
            );
            $arrayPremis = get_premis_overhead($overheadDt->id);
            $colData['premis-'.$overheadDt->id.'-'.$categoryDt->id] = array(
                '#type' => 'select',
                '#default_value' => $arrayPremis,
                '#options' => $premisOpt,
                '#multiple' => TRUE,
                '#select2' => array(
                    'placeholder' => 'Pilih Premis Terkait',
                    'width' => 150,
                ),
            );
            $tableRow['r-'.$counter] = $colData;
            $counter++;
        }
        $existingRec = $j;
        for ($j = 0;$j < 1;$j++) {
            $colData = array();
            $colData['no-' . $counter] = array(
                '#type' => 'item', '#title' => $counter,
                '#attributes' => array('outerclass' => array('align-right')),
            );
            if ($existingRec == 0) {
                $colData['cat-' . $categoryDt->id] = array(
                    '#type' => 'item', '#title' => $categoryDt->category,
                );
            } else {
                $colData['cat-' . $categoryDt->id] = array(
                    '#type' => 'item', '#title' => '',
                );
            }
            $colData['nama-new-' . $categoryDt->id . '-' . ($j + 1)] = array(
                '#type' => 'textfield',
                '#default_value' => '',
            );
            $colData['default_value-new-' . $categoryDt->id . '-' . ($j + 1)] = array(
                '#type' => 'textfield',
                '#default_value' => '',
            );
            $colData['description-new-' . $categoryDt->id . '-' . ($j + 1)] = array(
                '#type' => 'textarea',
                '#default_value' => '',
                '#attributes' => array('class' => array('input-description')),
            );
            $colData['weight-new-' . $categoryDt->id . '-' . ($j + 1)] = array(
                '#type' => 'textfield',
                '#default_value' => '',
                '#attributes' => array('class' => array('input-weigth')),
            );
            $colData['premis-new-' . $categoryDt->id . '-' . ($j + 1)] = array(
                '#type' => 'select',
                '#default_value' => '',
                '#options' => $premisOpt,
                '#multiple' => TRUE,
                '#select2' => array(
                    'placeholder' => 'Pilih Premis Terkait',
                ),
            );
            $tableRow['r-' . $counter] = $colData;
            $counter++;
        }
    }
    return $tableRow;
}
function form_add_overhead($form, &$form_state, $variables = null){
    set_default_time_zone();
    $tableHeader = create_overhead_header();
    $tableRow = create_overhead_row();
    $tableFooter[] = create_overhead_footer();
    $form['basic'] = array(
        '#type' => 'fieldset',
        '#title' => 'DATA OVERHEAD',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
    );
    $form['basic']['table'] = array(
        '#theme' => 'formtable_form_table',
        '#header' => $tableHeader,
        'rows' => $tableRow,
        '#footer' => $tableFooter,
    );
    $form['basic']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('SAVE OVERHEAD'),
    );
    return $form;
}
function form_add_overhead_submit($form, &$form_state)
{
    global $user;
    if (isset($form_state['values']['rows'])) {
        $values = $form_state['values']['rows'];
    } else {
        $values = $form_state['values'];
    }
    $returnData = array();
    if (count($values)){
        foreach ($values as $idxRow => $rowData){
            if (count($rowData)){
                $savedData = array();
                $premisData = array();
                foreach ($rowData as $idxCol => $ohData){
                    $explodeIdx = explode('-',$idxCol);
                    $savedData['id_category'] = $explodeIdx[2];
                    if ($explodeIdx[1] != 'new'){
                        if ($explodeIdx[0] != 'premis') {
                            $savedData['id'] = $explodeIdx[1];
                            $savedData[$explodeIdx[0]] = $ohData;
                        }else{
                            $premisData = $ohData;
                        }
                    }else{
                        if ($explodeIdx[0] != 'premis'){
                            $savedData[$explodeIdx[0]] = $ohData;
                        }else{
                            $premisData = $ohData;
                        }
                    }
                }
                $insertedData = array();
                if (empty($savedData['default_value'])){
                    $savedData['default_value'] = 0;
                }
                if (isset($savedData['id']) && !empty($savedData['id'])){
                    if (!empty($savedData['nama'])){
                        $insertedData = saveTableData(
                            'zoverhead','admin master data overhead',
                            $savedData,'id',$savedData['id']
                        );
                    }else{
                        $conditionData = array();
                        $consObj = new stdClass();
                        $consObj->fieldName = 'id';
                        $consObj->fieldValue = $savedData['id'];
                        $consObj->status = 'and';
                        $conditionData[] = $consObj;
                        deleteTableData('zoverhead','admin master data overhead',$conditionData);
                    }
                }else{
                    if (!empty($savedData['nama'])) {
                        $insertedData = saveTableData(
                            'zoverhead', 'admin master data overhead',
                            $savedData, 'id'
                        );
                    }
                }
                if (count($premisData)){
                    foreach ($premisData as $premisId){
                        $savedOhPremis['id_overhead'] = $insertedData['id'];
                        $savedOhPremis['id_premis'] = $premisId;
                        $overHeadPremis = get_overhead_premis($premisId);
                        if (count($overHeadPremis)){
                            if (!in_array($savedOhPremis['id_overhead'], $overHeadPremis)){
                                saveTableData('zoverhead_premis','admin master data overhead',$savedOhPremis);
                            }
                        }else{
                            saveTableData('zoverhead_premis','admin master data overhead',$savedOhPremis);
                        }
                    }
                }else{
                    if (isset($insertedData['id'])){
                        $arrayPremis = get_premis_overhead($insertedData['id']);
                        if (count($arrayPremis)){
                            for ($i = 0;$i < count($arrayPremis);$i++){
                                $conditionData = array();
                                $consObj = new stdClass();
                                $consObj->fieldName = 'id_premis';
                                $consObj->fieldValue = $arrayPremis[$i];
                                $consObj->status = 'and';
                                $conditionData[] = $consObj;
                                $consObj = new stdClass();
                                $consObj->fieldName = 'id_overhead';
                                $consObj->fieldValue = $insertedData['id'];
                                $consObj->status = 'and';
                                $conditionData[] = $consObj;
                                deleteTableData('zoverhead_premis','admin master data overhead',$conditionData);
                            }
                        }
                    }
                }
                $returnData[] = $insertedData;
            }
        }
        if (count($returnData)){
            drupal_set_message('Data Overhead berhasil disimpan...!!');
        }
    }
    return $returnData;
}
function get_premis_overhead($idOverhead = null){
    $returnArray = array();
    if (!empty($idOverhead)){
        $fieldArray = array(
            'id_premis', 'id_overhead', 'uid',
            'uid_changed', 'created', 'changed'
        );
        $premisOverhead = getTableDataByField(
            'zoverhead_premis','access data overhead',$fieldArray,
            null,'id_overhead',$idOverhead
        );
        for ($i = 0;$i < count($premisOverhead);$i++){
            $returnArray[] = $premisOverhead[$i]->id_premis;
        }
    }else{
        $premisOverhead = getTableDataByField(
            'zoverhead_premis','access data overhead',$fieldArray
        );
        for ($i = 0;$i < count($premisOverhead);$i++){
            $returnArray[$premisOverhead[$i]->id_overhead][] = $premisOverhead[$i]->id_premis;
        }
    }
    return $returnArray;
}
function get_overhead_premis($idPremis = null){
    $returnArray = array();
    if (!empty($idPremis)){
        $fieldArray = array(
            'id_premis', 'id_overhead', 'uid',
            'uid_changed', 'created', 'changed'
        );
        $overHeadPremis = getTableDataByField(
            'zoverhead_premis','access data overhead',$fieldArray,
            null,'id_premis',$idPremis
        );
        for ($i = 0;$i < count($overHeadPremis);$i++){
            $returnArray[] = $overHeadPremis[$i]->id_overhead;
        }
    }else{
        $overHeadPremis = getTableDataByField(
            'zoverhead_premis','access data overhead',$fieldArray
        );
        for ($i = 0;$i < count($overHeadPremis);$i++){
            $returnArray[$overHeadPremis[$i]->id_premis][] = $overHeadPremis[$i]->id_overhead;
        }
    }
    return $returnArray;
}
function get_not_overhead_premis($idPremis = null){
    $returnArray = array();
    if (!empty($idPremis)){
        $fieldArray = array(
            'id_premis', 'id_overhead', 'uid',
            'uid_changed', 'created', 'changed'
        );
        $consData = new stdClass();
        $consData->fieldName = 'ta.id_premis';
        $consData->operator = '!=';
        $consData->value = $idPremis;
        $conditionArray[] = $consData;
        $overHeadPremis = getTableDataByField(
            'zoverhead_premis','access data overhead',$fieldArray,
            null,null,null,null,$conditionArray
        );
        for ($i = 0;$i < count($overHeadPremis);$i++){
            if (!in_array($overHeadPremis[$i]->id_overhead, $returnArray)){
                $returnArray[] = $overHeadPremis[$i]->id_overhead;
            }
        }
    }
    return $returnArray;
}
function add_overhead_staff($idPremis = null){
    $core_module_path = drupal_get_path('module','ikhwan_core');
    $csspath = $core_module_path.'/css/custom-style.css';
    drupal_add_css($csspath);
    $jspath = $core_module_path.'/js/jquery.masknumber.js';
    drupal_add_js($jspath,array('scope' => 'footer', 'weight' => 5));
    $jspath = $core_module_path.'/js/notify.js';
    drupal_add_js($jspath,array('scope' => 'footer', 'weight' => 5));
    $module_path  = drupal_get_path('module','data_overhead');
    $jspath = $module_path.'/js/input_oh.js';
    drupal_add_js($jspath,array('scope' => 'footer', 'weight' => 5));
    $formOverhead = '';
    if (!empty($idPremis)) {
        $variables['idpremis'] = $idPremis;
        $form = drupal_get_form('form_entry_overhead', $variables);
        $formOverhead = drupal_render($form);
    }
    return $formOverhead;
}
function form_select_premis(){

}
function get_data_overhead_category($idcategory = null){
    $dataReturn = null;
    $fieldArray = array(
        'id', 'category', 'description', 'created', 'changed', 'uid', 'uid_changed', 'weight'
    );
    if (!empty($idcategory)){
        $dataCategory = getTableDataByField('zoverhead_category','access data overhead',$fieldArray,'weight','id',$idcategory);
        if (count($dataCategory)){
            $dataReturn = $dataCategory[0];
        }
    }else{
        $dataCategory = getTableDataByField('zoverhead_category','access data overhead',$fieldArray,'weight');
        if (count($dataCategory)){
            $dataReturn = $dataCategory;
        }
    }
    return $dataReturn;
}
function get_data_overhead($idCategory = null, $idOverhead = null){
    $dataReturn = null;
    $fieldArray = array(
        'id', 'id_category', 'nama', 'default_value', 'description',
        'created', 'changed', 'uid', 'uid_changed', 'weight'
    );
    $fieldOrder = array(
        array ('fieldname' => 'id_category'),
        array('fieldname' => 'weight'),
    );
    if (!empty($idCategory) && empty($idOverhead)){
        $dataCategory = getTableDataByField('zoverhead','access data overhead',$fieldArray,$fieldOrder,'id_category',$idCategory);
        if (count($dataCategory)){
            $dataReturn = $dataCategory;
        }
    }else if (empty($idCategory) && !empty($idOverhead)){
        $dataCategory = getTableDataByField('zoverhead','access data overhead',$fieldArray,$fieldOrder,'id',$idOverhead);
        if (count($dataCategory)){
            $dataReturn = $dataCategory[0];
        }
    }else{
        $dataCategory = getTableDataByField('zoverhead','access data overhead',$fieldArray,$fieldOrder);
        if (count($dataCategory)){
            $dataReturn = $dataCategory;
        }
    }
    return $dataReturn;
}
function get_data_overhead_by_category($idCategory = null){
    $arrayOverhead = array();
    if (!empty($idCategory )){
        $dataOverhead = get_data_overhead($idCategory);
        $arrayOverhead = array();
        for ($i = 0;$i < count($dataOverhead);$i++){
            $arrayOverhead[$dataOverhead[$i]->id_category][] = $dataOverhead[$i];
        }
    }else{
        $dataOverhead = get_data_overhead();
        $arrayOverhead = array();
        for ($i = 0;$i < count($dataOverhead);$i++){
            $arrayOverhead[$dataOverhead[$i]->id_category][] = $dataOverhead[$i];
        }
    }
    return $arrayOverhead;
}
function create_overhead_entry_header($idpremis = null){
    $tableHeader = array();
    if (!empty($idpremis)) {
        $staffData = get_data_staff_premis($idpremis);
        $tableHeader[] = t('KETERANGAN');
        $tableHeader[] = array(
            'data' => t('NILAI'),
            'class' => array(
                'col-input-number-small',
            ),
        );
        $tableHeader[] = array(
            'data' => t('UNIT'),
            'class' => array(
                'col-input-number-middle',
            ),
        );
        for ($i = 0;$i < count($staffData);$i++){
            $explodeNama = explode(' ',trim($staffData[$i]->staff_nama));
            $namaStaff = '';
            for ($j = 0;$j < count($explodeNama);$j++){
                if ($j == 0){
                    $namaStaff = $explodeNama[$j];
                }else{
                    if (strlen($explodeNama[0]) <= 3 && $j == 1){
                        $namaStaff .= ' '.$explodeNama[$j];
                    }else{
                        if (isset($explodeNama[$j][0])){
                            $namaStaff .= ' '.$explodeNama[$j][0].'.';
                        }
                    }
                }
            }
            $tableHeader[] = array(
                'data' => $namaStaff,
                'class' => array(
                    'col-input-number-small',
                ),
            );
        }
    }
    return $tableHeader;
}
function create_overhead_entry_footer($idpremis = null){
    $tableHeader = array();
    if (!empty($idpremis)) {
        $staffData = get_data_staff_premis($idpremis);
        $tableHeader[] = t('KETERANGAN');
        $tableHeader[] = array(
            'data' => t('NILAI'),
            'class' => array(
                'col-input-number-small',
            ),
        );
        $tableHeader[] = array(
            'data' => t('UNIT'),
            'class' => array(
                'col-input-number-middle',
            ),
        );
        for ($i = 0;$i < count($staffData);$i++){
            $explodeNama = explode(' ',trim($staffData[$i]->nama));
            $namaStaff = '';
            for ($j = 0;$j < count($explodeNama);$j++){
                if ($j == 0){
                    $namaStaff = $explodeNama[$j];
                }else{
                    if (strlen($explodeNama[0]) <= 3 && $j == 1){
                        $namaStaff .= ' '.$explodeNama[$j];
                    }else{
                        if (isset($explodeNama[$j][0])){
                            $namaStaff .= ' '.$explodeNama[$j][0].'.';
                        }
                    }
                }
            }
            $tableHeader[] = array(
                'data' => $namaStaff,
                'class' => array(
                    'col-input-number-small',
                ),
            );
        }
    }
    return $tableHeader;
}
function create_overhead_entry_row($idpremis = null){
    global $user;
    if (function_exists('set_user_number_format')){
        set_user_number_format($desIn, $desOut, $separator);
    }else{
        $desIn = '.';
        $desOut = ',';
        $separator = '.';
    }
    $tableRow = array();
    $tableRow['#tree'] = TRUE;
    $overheadStaffData = get_data_overhead_staff($idpremis);
    $arrayCategoryOverhead = get_data_overhead_category();
    $newArrayCategory = array();
    for ($i = 0;$i < count($arrayCategoryOverhead);$i++){
        $newArrayCategory[$arrayCategoryOverhead[$i]->id] = $arrayCategoryOverhead[$i]->category;
    }
    $arrayOverHead = get_data_overhead_by_category();
    $staffData = get_data_staff_premis($idpremis);
    //get_not_overhead_premis($idpremis);
    if (!empty($idpremis)) {
        if (count($newArrayCategory)){
            foreach ($newArrayCategory as $idCategory => $categoryName){
                $colData = array();
                $colData['category-'.$idCategory] = array(
                    '#type' => 'item', '#title' => strtoupper($categoryName),
                    '#attributes' => array('outerclass' => array('category-oh','category-title')),
                );
                $colData['category-'.$idCategory.'-nilai'] = array(
                    '#type' => 'item', '#title' => '',
                    '#attributes' => array('outerclass' => array('category-oh')),
                );
                $colData['category-'.$idCategory.'-unit'] = array(
                    '#type' => 'item', '#title' => '',
                    '#attributes' => array('outerclass' => array('category-oh')),
                );
                for ($j = 0;$j < count($staffData);$j++){
                    $colData['category-'.$idCategory.'-'.$staffData[$j]->id_staff] = array(
                        '#type' => 'item', '#title' => '',
                        '#attributes' => array('outerclass' => array('category-oh')),
                    );
                }
                $tableRow['cat-'.$idCategory] = $colData;
                if (isset($arrayOverHead[$idCategory]) && count($arrayOverHead[$idCategory])) {
                    foreach ($arrayOverHead[$idCategory] as $idxOv => $overheadData) {
                        $colData = array();
                        $colData['overhead-' . $idCategory . '-' . $overheadData->id] = array(
                            '#type' => 'item', '#title' => $overheadData->nama,
                        );
                        $colData['value-' . $idCategory . '-' . $overheadData->id] = array(
                            '#type' => 'item',
                            '#title' => number_format($overheadData->default_value, 0, $desOut, $separator),
                            '#attributes' => array('outerclass' => array('align-right')),
                        );
                        if (isset($overheadStaffData[$overheadData->id]) && isset($overheadStaffData[$overheadData->id]['UNIT'])) {
                            $overheadStaff = $overheadStaffData[$overheadData->id]['UNIT'];
                            $colData['UNIT-' . $overheadData->id . '-' . $idpremis . '-' . $overheadStaff->id] = array(
                                '#type' => 'textfield',
                                '#default_value' => $overheadStaff->overhead_entry,
                                '#attributes' => array('class' => array('align-right input-oh')),
                            );
                        }else {
                            $colData['UNIT-' . $overheadData->id . '-' . $idpremis] = array(
                                '#type' => 'textfield',
                                '#default_value' => '',
                                '#attributes' => array('class' => array('align-right input-oh')),
                            );
                        }
                        for ($j = 0; $j < count($staffData); $j++) {
                            if (isset($overheadStaffData[$overheadData->id]) && isset($overheadStaffData[$overheadData->id][$staffData[$j]->id_staff])) {
                                $overheadStaff = $overheadStaffData[$overheadData->id][$staffData[$j]->id_staff];
                                $colData['overhead-' . $overheadData->id . '-' . $staffData[$j]->id_staff . '-' . $overheadStaff->id] = array(
                                    '#type' => 'textfield',
                                    '#default_value' => $overheadStaff->overhead_entry,
                                    '#attributes' => array('class' => array('align-right input-oh')),
                                );
                            }else {
                                $colData['overhead-' . $overheadData->id . '-' . $staffData[$j]->id_staff] = array(
                                    '#type' => 'textfield',
                                    '#default_value' => '',
                                    '#attributes' => array('class' => array('align-right input-oh')),
                                );
                            }
                        }
                        $tableRow['cat-' . $idpremis . '-' . $overheadData->id] = $colData;
                    }
                }
            }
        }
    }
    return $tableRow;
}
function form_entry_overhead($form, &$form_state, $variables = null){
    set_default_time_zone();
    if (isset($variables['idpremis']) && !empty($variables['idpremis'])){
        $tableHeader = create_overhead_entry_header($variables['idpremis']);
        $tableRow = create_overhead_entry_row($variables['idpremis']);
        $tableFooter = array(create_overhead_entry_header($variables['idpremis']));
        $dataPremis = get_data_premis_by_id(null,$variables['idpremis']);
        $form['basic'] = array(
            '#type' => 'fieldset',
            '#title' => 'DATA OVERHEAD STAFF '.strtoupper($dataPremis->nama),
            '#collapsible' => FALSE, // Added
            '#collapsed' => FALSE,  // Added
        );
        $form['basic']['table'] = array(
            '#theme' => 'formtable_form_table',
            '#header' => $tableHeader,
            'rows' => $tableRow,
            '#footer' => $tableFooter,
            '#attributes' => array('class' => array('table-small-pad',),),
        );
        $form['basic']['form-grand'] = array(
            '#type' => 'item',
            '#markup' => '<h4 id="grand-total" class="title"><strong>TOTAL PER-BULAN : 0</strong></h4>',
        );
        $form['basic']['form-total-harian'] = array(
            '#type' => 'item',
            '#markup' => '<h4 id="total-harian" class="title"><strong>TOTAL PER-HARI: 0</strong></h4>',
        );
        $form['basic']['submit'] = array(
            '#type' => 'submit',
            '#value' => t('SAVE DATA OVERHEAD STAFF'),
        );
    }
    return $form;
}
function form_entry_overhead_submit($form, &$form_state){
    global $user;
    if (function_exists('set_user_number_format')){
        set_user_number_format($desIn, $desOut, $separator);
    }else{
        $desIn = '.';
        $desOut = ',';
        $separator = '.';
    }
    if (isset($form_state['values']['rows'])) {
        $values = $form_state['values']['rows'];
    } else {
        $values = $form_state['values'];
    }
    $returnData = array();
    if (count($values)){
        foreach ($values as $idxRow => $overheadData){
            $savedValues = array();
            $explodeIdx = explode('-', $idxRow);
            $savedValues['id_premis'] = $explodeIdx[1];
            $savedValues['id_overhead'] = $explodeIdx[2];
            if (count($overheadData)){
                foreach ($overheadData as $idxStaff => $dataStaff){
                    $explodeIdx2 = explode('-', $idxStaff);
                    if ($explodeIdx2[0] == 'UNIT'){
                        $savedValues['id_staff'] = 'UNIT';
                    }else{
                        $savedValues['id_staff'] = $explodeIdx2[2];
                    }
                    $calcValue = str_replace($separator,'',$dataStaff);
                    $calcValue = str_replace($desOut,'.',$calcValue);
                    $savedValues['overhead_entry'] = $dataStaff;
                    $savedValues['overhead_value'] = eval('return '.$calcValue.';');
                    if ($savedValues['overhead_value'] > 0) {
                        if (!isset($explodeIdx2[3])) {
                            $returnData[] = saveTableData(
                                'zoverhead_staff', 'admin data overhead', $savedValues, 'id'
                            );
                        }else if(isset($explodeIdx2[3])){
                            if (isset($savedValues['overhead_value']) && !empty($savedValues['overhead_value'])) {
                                $returnData[] = saveTableData(
                                    'zoverhead_staff', 'admin data overhead', $savedValues, 'id', $explodeIdx2[3]
                                );
                            }
                        }
                    }else{
                        if (isset($explodeIdx2[3])) {
                            $conditionData = array();
                            $consObj = new stdClass();
                            $consObj->fieldName = 'id';
                            $consObj->fieldValue = $explodeIdx2[3];
                            $consObj->status = 'and';
                            $conditionData[] = $consObj;
                            $returnData[] = deleteTableData('zoverhead_staff', 'admin data overhead', $conditionData);
                        }
                    }
                }
            }
        }
        drupal_set_message('Data overhead staff berhasil disimpan...!!');
    }
    return $returnData;
}
function get_data_overhead_staff($idPremis = null){
    $overheadData = array();
    if (!empty($idPremis)){
        $tableName = 'zoverhead_staff';
        $fieldArray = array(
            'id', 'id_staff', 'id_overhead', 'overhead_value', 'created',
            'changed', 'uid', 'uid_changed', 'overhead_entry', 'id_premis'
        );
        $overheadArray = getTableDataByField(
            $tableName,'access data overhead',$fieldArray,'id_overhead',
            'id_premis',$idPremis
        );
        for ($i = 0;$i < count($overheadArray);$i++){
            $overheadData[$overheadArray[$i]->id_overhead][$overheadArray[$i]->id_staff] = $overheadArray[$i];
        }
    }
    return $overheadData;
}

function fix_data_overhead(){
    $DataPremis = get_data_premis_by_id();
    $tableName = 'zoverhead_staff';
    for ($i = 0;$i < count($DataPremis);$i++){
        $overheadStaffData = get_data_overhead_staff($DataPremis[$i]->id);
        //dpm($overheadStaffData);
        $DataStaff = get_data_staff_premis($DataPremis[$i]->id);
        $StaffPremis = array();
        for ($j = 0;$j < count($DataStaff);$j++){
            $StaffPremis[] = $DataStaff[$j]->id_staff;
        }
        if ($DataPremis[$i]->id == '4259824118554563213411'){
            dpm($overheadStaffData);
            dpm($DataStaff);
            dpm($StaffPremis);
        }
        //dpm($StaffPremis);
        foreach ($overheadStaffData as $IdCategory => $DataOverheadStaff){
            foreach ($DataOverheadStaff as $IdStaff => $DataOH){
                if ($DataPremis[$i]->id == '4259824118554563213411') {
                    dpm($IdStaff);
                    dpm($StaffPremis);
                }
                if (!in_array($IdStaff, $StaffPremis)){
                    //dpm($IdStaff);
                    //dpm($DataOH->id);
                    $conditionData = array();
                    $consObj = new stdClass();
                    $consObj->fieldName = 'id';
                    $consObj->fieldValue = $DataOH->id;
                    $consObj->status = 'and';
                    $conditionData[] = $consObj;
                    deleteTableData($tableName,'access data overhead',$conditionData);
                }
            }
        }
    }
}