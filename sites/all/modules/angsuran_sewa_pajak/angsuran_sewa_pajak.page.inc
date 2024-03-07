<?php

function kewajiban_premis(){
    return 'Test Page';
}

function table_jenis_alat_premis(){
    return 'Jenis Alat Premis';
}

function form_jenis_alat_premis(){
    $variables = array();
    $form = drupal_get_form('jenis_alat_premis_form',$variables);
    $FormJenisAlat = drupal_render($form);
    return $FormJenisAlat;
}