<?php

/* Schema For Jenis Alat */
$schema['zangsuran_jenis_alat'] = array(
    'description' => 'Stores information about jenis alat terkait angsuran sewa dan pajak.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'Random ID',
            'description' => 'ID Jenis Alat, random value',
        ),
        'nama' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'default' => 'Nama Alat',
            'description' => 'Nama alat terkait angsuran sewa dan pajak',
        ),
        'deskripsi' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'Deskripsi alat.',
        ),
        'weight' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Weight of alat, supaya dapat di urutkan.',
        ),
        'created' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'The time that the row was created, as a Unix timestamp.',
        ),
        'changed' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'The time that the row was last edited, as a Unix timestamp.',
        ),
        'uid' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Uid that created the record.',
        ),
        'uid_changed' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Uid that changing the record.',
        ),
    ),
    'primary key' => array('id'),
    'indexes' => array(
        'nama'          => array('nama'),
        'weight'        => array('weight'),
        'uid_changed'   => array('uid_changed'),
        'created'       => array('created'),
        'changed'       => array('changed'),
    ),
);

/* Schema For Angsuran Premis */
$schema['zangsuran_premis'] = array(
    'description' => 'Stores information about angsuran sewa dan pajak premis.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'Random ID',
            'description' => 'ID Angsuran, random value',
        ),
        'id_premis' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'ID Premis',
            'description' => 'ID premis',
        ),
        'id_jenis_alat' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'ID Jenis Alat',
            'description' => 'ID Jenis Alat',
        ),
        'id_vendor' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'ID Vendor',
            'description' => 'ID Vendor',
        ),
        'periode' => array(
            'type' => 'int',
            'default' => 0,
            'not null' => TRUE,
            'description' => 'Periode angsuran, Tahunan/Bulanan/Mingguan/Harian/Jam Jam an.',
        ),
        'nomer' => array(
            'type' => 'varchar',
            'length' => 255,
            'default' => 'Nomer Alat',
            'description' => 'Nomer alat terkait angsuran sewa dan pajak',
        ),
        'nama' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'default' => 'Nama Alat',
            'description' => 'Nama terkait angsuran sewa dan pajak',
        ),
        'deskripsi' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'Deskripsi angsuran.',
        ),
        'start_angsuran' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Waktu start angsuran, as a Unix timestamp.',
        ),
        'jumlah_periode' => array(
            'type' => 'float',
            'size' => 'big',
            'default' => 1,
            'description' => 'jumlah periode.',
        ),
        'jenis_kewajiban' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Jenis kewajiban, apakah angsuran, sewa dll.',
        ),
        'nilai_kewajiban' => array(
            'type' => 'float',
            'size' => 'big',
            'default' => 0,
            'description' => 'nilai dari kewajiban yang harus dibayar per jumlah periode.',
        ),
        'alamat' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'Alamat kewajiban jika berupa rumah, ruko dll, bisa juga alamat perpanjangan.',
        ),
        'weight' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Weight of alat, supaya dapat di urutkan.',
        ),
        'created' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'The time that the row was created, as a Unix timestamp.',
        ),
        'changed' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'The time that the row was last edited, as a Unix timestamp.',
        ),
        'uid' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Uid that created the record.',
        ),
        'uid_changed' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Uid that changing the record.',
        ),
    ),
    'primary key' => array('id'),
    'indexes' => array(
        'nama'              => array('nama'),
        'nomer'             => array('nomer'),
        'periode'           => array('periode'),
        'jumlah_periode'    => array('jumlah_periode'),
        'jenis_kewajiban'   => array('jenis_kewajiban'),
        'id_premis'         => array('id_premis'),
        'weight'            => array('weight'),
        'uid_changed'       => array('uid_changed'),
        'created'           => array('created'),
        'changed'           => array('changed'),
    ),
);

/* Schema For Pembayaran Angsuran Premis */
$schema['zangsuran_premis_bayar'] = array(
    'description' => 'Stores information about pembayaran angsuran sewa dan pajak premis.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'Random ID',
            'description' => 'ID Pembayaran, random value',
        ),
        'id_angsuran' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'ID Angsuran',
            'description' => 'ID Angsuran',
        ),
        'id_vendor' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'ID Vendor',
            'description' => 'ID Vendor',
        ),
        'pembayaran_ke' => array(
            'type' => 'int',
            'default' => 1,
            'not null' => TRUE,
            'description' => 'Pembayaran angsuran keberapa.',
        ),
        'nomer' => array(
            'type' => 'varchar',
            'length' => 255,
            'default' => 'Nomer Pembayaran',
            'description' => 'Nomer pembauaran angsuran sewa dan pajak',
        ),
        'deskripsi' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'Deskripsi angsuran.',
        ),
        'tgl_pembayaran' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Waktu pembayaran angsuran, as a Unix timestamp.',
        ),
        'nilai_kewajiban' => array(
            'type' => 'float',
            'size' => 'big',
            'default' => 0,
            'description' => 'nilai dari kewajiban yang harus dibayar per jumlah periode.',
        ),
        'nilai_pembayaran' => array(
            'type' => 'float',
            'size' => 'big',
            'default' => 0,
            'description' => 'nilai dari pembayaran yang dibayar.',
        ),
        'created' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'The time that the row was created, as a Unix timestamp.',
        ),
        'changed' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'The time that the row was last edited, as a Unix timestamp.',
        ),
        'uid' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Uid that created the record.',
        ),
        'uid_changed' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Uid that changing the record.',
        ),
    ),
    'primary key' => array('id'),
    'indexes' => array(
        'nomer'             => array('nomer'),
        'id_angsuran'       => array('id_angsuran'),
        'tgl_pembayaran'    => array('tgl_pembayaran'),
        'uid'               => array('uid'),
        'uid_changed'       => array('uid_changed'),
    ),
);

/* Schema For Vendor */
$schema['zangsuran_vendor'] = array(
    'description' => 'Stores information about vendor terkait angsuran sewa dan pajak.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'Random ID',
            'description' => 'ID Vendor, random value',
        ),
        'nama' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'default' => 'Nama Vendor',
            'description' => 'Nama vendor terkait angsuran sewa dan pajak',
        ),
        'telepon' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'default' => 'Telepon Vendor',
            'description' => 'Telepon vendor terkait angsuran sewa dan pajak',
        ),
        'alamat' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'Alamat vendor.',
        ),
        'email' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'default' => 'Email Vendor',
            'description' => 'Email vendor terkait angsuran sewa dan pajak',
        ),
        'website' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'default' => 'Website Vendor',
            'description' => 'Website vendor terkait angsuran sewa dan pajak',
        ),
        'deskripsi' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'Deskripsi vendor.',
        ),
        'weight' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Weight of vendor, supaya dapat di urutkan.',
        ),
        'created' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'The time that the row was created, as a Unix timestamp.',
        ),
        'changed' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'The time that the row was last edited, as a Unix timestamp.',
        ),
        'uid' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Uid that created the record.',
        ),
        'uid_changed' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Uid that changing the record.',
        ),
    ),
    'primary key' => array('id'),
    'indexes' => array(
        'nama'          => array('nama'),
        'weight'        => array('weight'),
        'uid'           => array('uid_changed'),
        'uid_changed'   => array('uid_changed'),
        'created'       => array('created'),
        'changed'       => array('changed'),
    ),
);