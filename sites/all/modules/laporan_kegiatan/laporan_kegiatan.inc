<?php

function create_kegiatan_header(){
    $tableHeader = array();
    $tableHeader[] = array(
        'data' => t('No.'),
        'class' => array(
            'col-number'
        ),
    );
    $tableHeader[] = t('KEGIATAN');
    $tableHeader[] = t('DESKRIPSI');
    $tableHeader[] = t('JENIS JAWABAN');
    $tableHeader[] = t('WEIGHT');
    $tableHeader[] = t('DELETE');
    return $tableHeader;
}
function create_kegiatan_row(){
    $tableRow = array();
    $tableRow['#tree'] = TRUE;
    $DataKegiatan = get_array_kegiatan();
    if (!is_null($DataKegiatan) && count($DataKegiatan)){
        for ($i = 0;$i < count($DataKegiatan);$i++){
            $IdKegiatan = $DataKegiatan[$i]->id;
            $colData = array();
            $colData['id-'.$IdKegiatan.'-edit'] = array(
                '#type' => 'hidden', '#prefix' => ($i + 1),
                '#attributes' => array(
                    'class' => array('align-right'),
                    'id' => 'nid-kegiatan-'.$IdKegiatan,
                    'outerclass' => array('align-right'),
                ),
                '#default_value' => $IdKegiatan,
            );
            $colData['nama-'.$IdKegiatan.'-edit'] = array(
                '#type' => 'textfield',
                '#default_value' => $DataKegiatan[$i]->nama,
                '#attributes' => array('class' => array('nama-kegiatan')),
            );
            $colData['deskripsi-'.$IdKegiatan.'-edit'] = array(
                '#type' => 'textfield',
                '#default_value' => $DataKegiatan[$i]->deskripsi,
                '#attributes' => array('class' => array('deskripsi')),
            );
            $colData['jenis_kegiatan-'.$IdKegiatan.'-edit'] = array(
                '#type' => 'select',
                '#default_value' => $DataKegiatan[$i]->jenis_kegiatan,
                '#options' => array_jenis_kegiatan(),
                '#select2' => array(
                    'placeholder' => t('Pilih Jenis Isian Kegiatan'),
                    'width' => '100px',
                ),
            );
            $colData['weight-'.$IdKegiatan.'-edit'] = array(
                '#type' => 'textfield',
                '#default_value' => $DataKegiatan[$i]->weight,
                '#attributes' => array('class' => array('weight')),
            );
            $colData['delete-'.$IdKegiatan] = array(
                '#type' => 'hidden',
                '#default_value' => 0,
                '#attributes' => array(
                    'id' => 'delete-'.$IdKegiatan,
                ),
                '#suffix' => '<input type="checkbox" id="checkdel-'.$IdKegiatan.'" value="1" class="checkdel">',
            );
            $tableRow['r'.($i + 1).'-'.$IdKegiatan] = $colData;
        }
        $nextCounter = $i + 1;
        for ($i = 0;$i < 3;$i++){
            $colData = array();
            $colData['id-new-'.$nextCounter] = array(
                '#type' => 'hidden', '#prefix' => ($nextCounter),
                '#attributes' => array(
                    'class' => array('align-right'),
                    'id' => 'nid-kegiatan-'.$nextCounter,
                    'outerclass' => array('align-right'),
                ),
                '#default_value' => '',
            );
            $colData['nama-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#attributes' => array('class' => array('nama-kegiatan')),
            );
            $colData['deskripsi-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#attributes' => array('class' => array('deskripsi')),
            );
            $colData['jenis_kegiatan-new-'.$nextCounter] = array(
                '#type' => 'select',
                '#options' => array_jenis_kegiatan(),
                '#select2' => array(
                    'placeholder' => t('Pilih Jenis Isian Kegiatan'),
                    'width' => '100px',
                ),
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
                    'id' => 'nid-kegiatan-'.$nextCounter,
                    'outerclass' => array('align-right'),
                ),
                '#default_value' => '',
            );
            $colData['nama-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#attributes' => array('class' => array('nama-kegiatan')),
            );
            $colData['deskripsi-new-'.$nextCounter] = array(
                '#type' => 'textfield',
                '#attributes' => array('class' => array('deskripsi')),
            );
            $colData['jenis_kegiatan-new-'.$nextCounter] = array(
                '#type' => 'select',
                '#options' => array_jenis_kegiatan(),
                '#select2' => array(
                    'placeholder' => t('Pilih Jenis Isian Kegiatan'),
                    'width' => '100px',
                ),
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

function kegiatan_form($form, &$form_state, $variables = null)
{
    $tableHeader = create_kegiatan_header();
    $tableRow = create_kegiatan_row();
    $tableFooter = array(create_kegiatan_header());
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

function list_kegiatan()
{
    $core_module_path = drupal_get_path('module', 'ikhwan_core');
    $csspath = $core_module_path . '/css/custom-style.css';
    drupal_add_css($csspath);
    $jquery_path = drupal_get_path('module', 'jquery_update');
    $csspath = $jquery_path . '/replace/ui/themes/base/jquery-ui.css';
    drupal_add_css($csspath);
    $jspath = $jquery_path . '/replace/ui/ui/jquery-ui.js';
    drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
    //$module_path = drupal_get_path('module', 'data_staff');
    //$jspath = $module_path . '/js/form_anak_staff.js';
    //drupal_add_js($jspath, array('scope' => 'footer', 'weight' => 5));
    $Form = drupal_get_form('kegiatan_form');
    $FormKegiatan = drupal_render($Form);
    return $FormKegiatan;
}

function kegiatan_form_submit($form, &$form_state)
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
                $KegiatanExist = false;
                $SavedData = array();
                $DeletedId = '';
                $InsertData = true;
                foreach ($rowData as $idxField => $FieldValue){
                    $SplitIdxField = explode('-', $idxField);
                    if ($SplitIdxField[1] == 'new'){
                        if ($SplitIdxField[0] == 'id'){
                            if (!empty($FieldValue)){
                                $KegiatanExist = true;
                                $SavedData['id'] = $FieldValue;
                            }
                        }else if ($SplitIdxField[0] != 'delete'){
                            if ($SplitIdxField[0] == 'nama'){
                                $SavedData['nama'] = $FieldValue;
                            }else{
                                $SavedData[$SplitIdxField[0]] = $FieldValue;
                            }
                        }
                    }else{
                        if ($SplitIdxField[0] == 'delete'){
                            if ($FieldValue == '1'){
                                $DeletedId = $SplitIdxField[1];
                                $InsertData = false;
                            }
                        }else{
                            $KegiatanExist = true;
                            if ($SplitIdxField[0] == 'id'){
                                $SavedData['id'] = $FieldValue;
                            }else{
                                $SavedData[$SplitIdxField[0]] = $FieldValue;
                            }
                        }
                    }
                }
                if (count($SavedData) && $SavedData['nama'] && $InsertData){
                    if ($KegiatanExist) {
                        if (!empty($SavedData) && isset($SavedData['id']) && !empty($SavedData['id'])) {
                            $DataKegiatan = saveTableData(
                                'zkegiatan_jemaah', 'admin laporan kegiatan module',
                                $SavedData, 'id', $SavedData['id']
                            );
                        }
                        drupal_set_message('Data kegiatan jemaah : '.$SavedData['nama'].' berhasil diupdate');
                    }else{
                        $DataKegiatan = saveTableData(
                            'zkegiatan_jemaah', 'admin laporan kegiatan module',
                            $SavedData, 'id'
                        );
                        drupal_set_message('Penambahan data kegiatan jemaah : '.$SavedData['nama'].' berhasil');
                    }
                    $returnData[] = $DataKegiatan;
                }
                if (!empty($DeletedId)){
                    if (isset($SavedData['id']) && !empty($SavedData['id'])) {
                        $conditionData = array();
                        $consObj = new stdClass();
                        $consObj->fieldName = 'id';
                        $consObj->fieldValue = $DeletedId;
                        $consObj->status = 'and';
                        $conditionData[] = $consObj;
                        deleteTableData('zkegiatan_jemaah', 'admin laporan kegiatan module', $conditionData);
                        drupal_set_message('Data kegiatan : '.$SavedData['nama'].' berhasil dihapus..!!!');
                    }
                }
            }
        }
    }
    return $returnData;
}