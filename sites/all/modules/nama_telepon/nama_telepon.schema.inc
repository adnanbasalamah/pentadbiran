<?php

/* Schema For Data Pemasukan dan Pengeluaran */
$schema['znomertelepon'] = array(
    'description' => 'Stores information about pemasukan dan pengeluaran zone.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'random_number',
            'description' => 'Nama telepon ID',
        ),
        'nama' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'default' => 'Nama',
            'description' => 'Nama telepon',
        ),
        'telepon' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'default' => 'Telepon',
            'description' => 'Nama telepon',
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
        'nama'                      => array('nama'),
        'telepon'                => array('telepon'),
        'uid'                       => array('uid'),
        'uid_changed'               => array('uid_changed'),
        'created'                   => array('created'),
        'changed'                   => array('changed'),
    ),
);
/* End Schema Data Pemasukan dan Pengeluaran */