<?php

function create_tempat_kegiatan_header(){
    $tableHeader = array();
    $tableHeader[] = array(
        'data' => t('No.'),
        'class' => array(
            'col-number'
        ),
    );
    $tableHeader[] = t('ZON');
    $tableHeader[] = t('NEGERI');
    $tableHeader[] = t('NAMA TEMPAT');
    $tableHeader[] = t('DESKRIPSI');
    $tableHeader[] = t('WEIGHT');
    $tableHeader[] = t('DELETE');
    return $tableHeader;
}
function create_tempat_kegiatan_row(){
    $tableRow = array();
    $tableRow['#tree'] = TRUE;
    $DataTempat = get_array_tempat_kegiatan();
    $ArrayZone = getZoneByCode();
    $OptZone = array();
    for ($i = 0;$i < count($ArrayZone);$i++){
        $OptZone[$ArrayZone[$i]->zone] = $ArrayZone[$i]->nama;
    }
    $ArrayNegeri = get_data_negeri_by_id();
    $OptionNegri = array();
    for ($i = 0;$i < count($ArrayNegeri);$i++){
        $OptionNegri[$ArrayNegeri[$i]->id] = $ArrayNegeri[$i]->nama;
    }
    if (!is_null($DataTempat) && count($DataTempat)){
        for ($i = 0;$i < count($DataTempat);$i++){
            $IdTempat = $DataTempat[$i]->id;
            $colData = array();
            $colData['id-'.$IdTempat.'-edit'] = array(
                '#type' => 'hidden', '#prefix' => ($i + 1),
                '#attributes' => array(
                    'class' => array('align-right'),
                    'id' => 'nid-tempat_kegiatan-'.$IdTempat,
                    'outerclass' => array('align-right'),
                ),
                '#default_value' => $IdTempat,
            );
            $colData['zone-'.$IdTempat.'-edit'] = array(
                '#type' => 'select',
                '#options' => $OptZone,
                '#default_value' => $DataTempat[$i]->zone,
                '#select2' => array(
                    'placeholder' => t('Pilih Zone'),
                    'width' => '180px',
                ),
                '#attributes' => array(
                    'class' => array('align-right','zon-select'),
                    'id' => 'zone-tempatkegiatan-'.$IdTempat,
                    'style' => 'width: 180px;',
                ),
            );
            $colData['idnegeri-'.$IdTempat.'-edit'] = array(
                '#type' => 'select',
                '#options' => $OptionNegri,
                '#default_value' => $DataTempat[$i]->idnegeri,
                '#select2' => array(
                    'placeholder' => t('Pilih Negeri/Kota'),
                    'width' => '180px',
                ),
                '#attributes' => array(
                    'class' => array('negeri-select'),
                    'id' => 'negeri-tempatkegiatan-'.$IdTempat,
                    'style' => 'width: 180px;',
                ),
            );
            $colData['nama-'.$IdTempat.'-edit'] = array(
                '#type' => 'textfield',
                '#default_value' => $DataTempat[$i]->nama,
                '#attributes' => array('class' => array('nama-tempat_kegiatan')),
            );
            $colData['deskripsi-'.$IdTempat.'-edit'] = array(
                '#type' => 'textfield',
                '#default_value' => $DataTempat[$i]->deskripsi,
                '#attributes' => array('class' => array('deskripsi')),
            );
            $colData['weight-'.$IdTempat.'-edit'] = array(
                '#type' => 'textfield',
                '#default_value' => $DataTempat[$i]->weight,
                '#attributes' => array('class' => array('weight')),
            );
            $colData['delete-'.$IdTempat] = array(
                '#type' => 'hidden',
                '#default_value' => 0,
                '#attributes' => array(
                    'id' => 'delete-'.$IdTempat,
                ),
                '#suffix' => '<input type="checkbox" id="checkdel-'.$IdTempat.'" value="1" class="checkdel">',
            );
            $tableRow['r'.($i + 1).'-'.$IdTempat] = $colData;
        }
        $nextCounter = $i + 1;
        for ($i = 0;$i < 3;$i++){
            $colData = array();
            $colData['id-new-'.$nextCounter] = array(
                '#type' => 'hidden', '#prefix' => ($nextCounter),
                '#attributes' => array(
                    'class' => array('align-right'),
                    'id' => 'nid-tempat_kegiatan-'.$nextCounter,
                    'outerclass' => array('align-right'),
                ),
                '#default_value' => '',
            );
            $colData['zone-new-'.$nextCounter] = array(
                '#type' => 'select',
                '#options' => $OptZone,
                '#select2' => array(
                    'placeholder' => t('Pilih Zone'),
                    'width' => '180px',
                ),
                '#attributes' => array(
                    'class' => array('align-right','zon-select'),
                    'id' => 'zone-tempatkegiatan-'.$nextCounter,
                    'style' => 'width: 180px;',
                ),
            );
            $colData['idnegeri-new-'.$nextCounter] = array(
                '#type' => 'select',
                '#options' => $OptionNegri,
                '#select2' => array(
                    'placeholder' => t('Pilih Negeri/Kota'),
                    'width' => '180px',
                ),
                '#attributes' => array(
                    'class' => array('negeri-select'),
                    'id' => 'negeri-tempatkegiatan-'.$nextCounter,
                    'style' => 'width: 180px;',
                ),
            );
            $colData['nama-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#attributes' => array('class' => array('nama-tempat_kegiatan')),
            );
            $colData['deskripsi-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#attributes' => array('class' => array('deskripsi')),
            );
            $colData['weight-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#attributes' => array('class' => array('weight')),
            );
            $tableRow['r'.$nextCounter] = $colData;
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
                    'id' => 'nid-tempat_kegiatan-'.$nextCounter,
                    'outerclass' => array('align-right'),
                ),
                '#default_value' => '',
            );
            $colData['zone-new-'.$nextCounter] = array(
                '#type' => 'select',
                '#options' => $OptZone,
                '#select2' => array(
                    'placeholder' => t('Pilih Zone'),
                    'width' => '180px',
                ),
                '#attributes' => array(
                    'class' => array('align-right','zon-select'),
                    'id' => 'zone-tempatkegiatan-'.$nextCounter,
                    'style' => 'width: 180px;',
                ),
            );
            $colData['idnegeri-new-'.$nextCounter] = array(
                '#type' => 'select',
                '#options' => $OptionNegri,
                '#select2' => array(
                    'placeholder' => t('Pilih Negeri/Kota'),
                    'width' => '180px',
                ),
                '#attributes' => array(
                    'class' => array('negeri-select'),
                    'id' => 'negeri-tempatkegiatan-'.$nextCounter,
                    'style' => 'width: 180px;',
                ),
            );
            $colData['nama-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#attributes' => array('class' => array('nama-tempat_kegiatan')),
            );
            $colData['deskripsi-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#attributes' => array('class' => array('deskripsi')),
            );
            $colData['weight-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#attributes' => array('class' => array('weight')),
            );
            $tableRow['r'.$nextCounter] = $colData;
            $nextCounter++;
        }
    }
    return $tableRow;
}

function tempat_kegiatan_form($form, &$form_state, $variables = null)
{
    $tableHeader = create_tempat_kegiatan_header();
    $tableRow = create_tempat_kegiatan_row();
    $tableFooter = array(create_tempat_kegiatan_header());
    $form['basic'] = array(
        '#type' => 'fieldset',
        '#title' => 'DATA KEGIATAN JEMAAH',
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
        '#value' => t('SAVE DATA KEGIATAN'),
    );
    return $form;
}

function list_tempat_kegiatan()
{
    $core_module_path = drupal_get_path('module', 'ikhwan_core');
    $csspath = $core_module_path . '/css/custom-style.css';
    drupal_add_css($csspath);
    $jquery_path = drupal_get_path('module', 'jquery_update');
    $csspath = $jquery_path . '/replace/ui/themes/base/jquery-ui.css';
    drupal_add_css($csspath);
    $jspath = $jquery_path . '/replace/ui/ui/jquery-ui.js';
    drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
    $module_path = drupal_get_path('module', 'laporan_kegiatan');
    $jspath = $module_path . '/js/tempat_kegiatan.js';
    drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
    $Form = drupal_get_form('tempat_kegiatan_form');
    $FormKegiatan = drupal_render($Form);
    return $FormKegiatan;
}

function tempat_kegiatan_form_submit($form, &$form_state)
{
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
                $TempatExist = false;
                $SavedData = array();
                $DeletedId = '';
                $InsertData = true;
                foreach ($rowData as $idxField => $FieldValue){
                    $SplitIdxField = explode('-', $idxField);
                    if ($SplitIdxField[1] == 'new'){
                        if ($SplitIdxField[0] == 'id'){
                            if (!empty($FieldValue)){
                                $TempatExist = true;
                                $SavedData['id'] = $FieldValue;
                            }
                        }else if ($SplitIdxField[0] != 'delete'){
                            $SavedData[$SplitIdxField[0]] = $FieldValue;
                        }
                    }else{
                        if ($SplitIdxField[0] == 'delete'){
                            if ($FieldValue == '1'){
                                $DeletedId = $SplitIdxField[1];
                                $InsertData = false;
                            }
                        }else{
                            $TempatExist = true;
                            if ($SplitIdxField[0] == 'id'){
                                $SavedData['id'] = $FieldValue;
                            }else{
                                $SavedData[$SplitIdxField[0]] = $FieldValue;
                            }
                        }
                    }
                }
                if (count($SavedData) && $SavedData['nama'] && $InsertData){
                    if ($TempatExist) {
                        if (!empty($SavedData) && isset($SavedData['id']) && !empty($SavedData['id'])) {
                            $DataTempat = saveTableData(
                                'ztempat_kegiatan', 'admin laporan kegiatan module',
                                $SavedData, 'id', $SavedData['id']
                            );
                        }
                        drupal_set_message('Data tempat_kegiatan jemaah : '.$SavedData['nama'].' berhasil diupdate');
                    }else{
                        $DataTempat = saveTableData(
                            'ztempat_kegiatan', 'admin laporan kegiatan module',
                            $SavedData, 'id'
                        );
                        drupal_set_message('Penambahan data tempat_kegiatan jemaah : '.$SavedData['nama'].' berhasil');
                    }
                    $returnData[] = $DataTempat;
                }
                if (!empty($DeletedId)){
                    if (isset($SavedData['id']) && !empty($SavedData['id'])) {
                        $conditionData = array();
                        $consObj = new stdClass();
                        $consObj->fieldName = 'id';
                        $consObj->fieldValue = $DeletedId;
                        $consObj->status = 'and';
                        $conditionData[] = $consObj;
                        deleteTableData('ztempat_kegiatan', 'admin laporan kegiatan module', $conditionData);
                        drupal_set_message('Data tempat_kegiatan : '.$SavedData['nama'].' berhasil dihapus..!!!');
                    }
                }
            }
        }
    }
    return $returnData;
}