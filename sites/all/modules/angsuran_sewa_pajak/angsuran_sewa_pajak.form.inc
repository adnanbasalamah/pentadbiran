<?php

function jenis_alat_premis_form($form, &$form_state, $variables = null)
{
    global $user;
    $form['#attributes'] = array('class' => array('col-sm-12'));
    if (!empty($variables->id)){
        $form['basic']['id'] = array(
            '#type' => 'hidden',
            '#default_value' => $variables->id,
        );
    }
    $NamaAlat = '';
    if (isset($variables->nama) && !empty($variables->nama)){
        $NamaAlat = $variables->nama;
    }
    $Deskripsi = '';
    if (isset($variables->deskripsi) && !empty($variables->deskripsi)){
        $Deskripsi = $variables->deskripsi;
    }
    $Weight = 0;
    if (isset($variables->weight) && !empty($variables->weight)){
        $Weight = $variables->weight;
    }
    $form['nama'] = array(
        '#type' => 'textfield',
        '#title' => t('Jenis Alat'),
        '#required' => TRUE,
        '#default_value' => $NamaAlat,
    );
    $form['deskripsi'] = array(
        '#title' => t('Deskripsi'),
        '#type' => 'textarea',
        '#default_value' => $Deskripsi,
    );
    $form['weight'] = array(
        '#type' => 'textfield',
        '#title' => t('Weight'),
        '#default_value' => $Weight,
    );
    $form['saveButton'] = array(
        '#value' => t('Save Data Jenis Alat'),
        '#type' => 'submit',
        '#attributes' => array('class' => array('btn btn-primary')),
    );
    return $form;
}

function jenis_alat_premis_form_submit($form, &$form_state)
{
    global $user;
    $values = $form_state['values'];
    $savedData = array();
    $savedData['nama'] = $values['nama'];
    $savedData['deskripsi'] = $values['deskripsi'];
    $savedData['weight'] = $values['weight'];
    $savedData['uid'] = $user->uid;
    if (isset($values['id']) && !empty($values['id'])){

    }else{
        $insertedData = saveTableData('zangsuran_jenis_alat','admin kewajiban premis',$savedData,'id');
        $returnData = $insertedData;
        drupal_set_message("Data jenis alat berhasil di simpan");
    }
    return $returnData;
}