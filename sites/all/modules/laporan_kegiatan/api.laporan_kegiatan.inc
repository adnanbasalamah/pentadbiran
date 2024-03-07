<?php

function get_array_kegiatan(){
    $FieldArray = array(
        'id', 'nama', 'deskripsi', 'jenis_kegiatan', 'weight',
        'created', 'changed', 'uid', 'uid_changed', 'status'
    );
    $ArrayKegiatan = getTableDataByField('zkegiatan_jemaah','access laporan kegiatan module',
        $FieldArray, 'weight', 'status', 1
    );
    return $ArrayKegiatan;
}

function array_jenis_kegiatan(){
    return array('PILIHAN', 'ISIAN');
}

function get_array_tempat_kegiatan(){
    $FieldArray = array(
        'id', 'zone', 'idnegeri', 'nama', 'deskripsi', 'weight',
        'created', 'changed', 'uid', 'uid_changed'
    );
    $ArrayTempatKegiatan = getTableDataByField('ztempat_kegiatan','access laporan kegiatan module',
        $FieldArray, 'weight'
    );
    return $ArrayTempatKegiatan;
}