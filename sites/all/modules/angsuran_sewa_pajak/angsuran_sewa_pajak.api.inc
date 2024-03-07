<?php

/**
 * @return array
 */
function array_jenis_kewajiban(){
    return array(
      'Angsuran', 'Sewa', 'Pajak', 'Perpanjangan', 'Service/Maintenance'
    );
}

/**
 * @return array
 */
function array_periode_kewajiban(){
    return array(
        'Tahunan', 'Bulanan', 'Mingguan', 'Harian', 'Jam-jaman'
    );
}

/**
 * @return array
 */
function status_kewajiban(){
    return array(
        'aktif', 'proses', 'lunas'
    );
}