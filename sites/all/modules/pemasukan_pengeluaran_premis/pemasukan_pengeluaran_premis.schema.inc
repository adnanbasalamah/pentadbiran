<?php

/* Schema For Data Jenis Pemasukan Premis */
$schema['zjenis_pemasukan_premis'] = array(
    'description' => 'Stores information about jenis pemasukan premis.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'random_number',
            'description' => 'Jenis pemasukan premis ID',
        ),
        'id_premis' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'id_premis',
            'description' => 'Premis ID',
        ),
        'jenis_pemasukan' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'default' => '',
            'description' => 'Judul jenis pemasukan premis',
        ),
        'keterangan' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'Keterangan jenis pemasukan.',
        ),
        'weight' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'weight or order for jenis pemasukan.',
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
        'id_premis'                 => array('id_premis'),
        'jenis_pemasukan'           => array('jenis_pemasukan'),
        'jumlah_pengeluaran'        => array('jumlah_pengeluaran'),
        'weight'                    => array('weight'),
        'uid'                       => array('uid'),
        'uid_changed'               => array('uid_changed'),
        'created'                   => array('created'),
        'changed'                   => array('changed'),
    ),
);
/* End Schema Jenis Pemasukan premis */