<?php
/* Schema For Data Premis */
$schema['zproperti_jenis'] = array(
    'description' => 'Stores information about jenis properti premis.',
    'fields' => array(
        'id' => array(
            'type' => 'serial',
            'unsigned' => TRUE,
            'not null' => TRUE,
            'description' => 'Id jenis properti auto increment',
        ),
        'jenis_properti' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'default' => 'Premis',
            'description' => 'Nama jenis properti',
        ),
        'keterangan' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'Keterangan jenis properti',
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
        'jenis_properti'=> array('jenis_properti'),
        'uid_changed'   => array('uid_changed'),
        'created'       => array('created'),
        'changed'       => array('changed'),
    ),
);
$schema['zproperti_premis'] = array(
    'description' => 'Stores information about data properti premis.',
    'fields' => array(
        'id' => array(
            'type' => 'serial',
            'unsigned' => TRUE,
            'not null' => TRUE,
            'description' => 'Id properti premis auto increment',
        ),
        'idpremis' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'ID prmeis',
            'description' => 'Related ID from data premis',
        ),
        'id_jenis_properi' => array(
            'type' => 'int',
            'not null' => TRUE,
            'default' => 0,
            'description' => 'Related ID from jenis properti',
        ),
        'alamat' => array(
            'type' => 'text',
            'size' => 'big',
            'not null' => TRUE,
            'description' => 'alamat properti',
        ),
        'telpon' => array(
            'type' => 'varchar',
            'length' => 255,
            'default' => '8888888',
            'description' => 'Nomor telpon premis',
        ),
        'status_properti' => array(
            'type' => 'int',
            'not null' => TRUE,
            'default' => 0,
            'description' => '0 => sewa, 1 => kredit, 2 => cash, 3 => pajak, 4 => hutang, 5 => wakaf/hibah',
        ),
        'jenis_status_properti' => array(
            'type' => 'int',
            'default' => 2,
            'description' => '0 => jam jaman, 1 => harian, 2 => bulanan, 3 => tahunan',
        ),
        'jumlah_angsuran' => array(
            'type' => 'int',
            'default' => 1,
            'description' => 'Jumlah angsuran',
        ),
        'mulai_sewa' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Tanggal mulai properti',
        ),
        'jatuh_tempo' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'jatuh tempo angsuran/sewa properti',
        ),
        'nilai_properti' => array(
            'type' => 'float',
            'size' => 'big',
            'not null' => TRUE,
            'default' => 0,
            'description' => 'nilai properti',
        ),
        'angsuran' => array(
            'type' => 'float',
            'size' => 'big',
            'default' => 0,
            'description' => 'nilai angsuran properti',
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
    'foreign keys' => array(
        'idpremis' => array(
            'table' => 'zdatapremis',
            'columns' => array('idpremis' => 'idpremis'),
        ),
        'id_jenis_properi' => array(
            'table' => 'zproperti_jenis',
            'columns' => array('id_jenis_properi' => 'id'),
        ),
    ),
);
