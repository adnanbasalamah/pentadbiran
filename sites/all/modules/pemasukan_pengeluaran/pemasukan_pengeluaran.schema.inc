<?php

/* Schema For Data Pemasukan dan Pengeluaran */
$schema['zdatazone_pemasukan_pengeluaran'] = array(
    'description' => 'Stores information about pemasukan dan pengeluaran zone.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'random_number',
            'description' => 'Pemasukan pengeluaran ID',
        ),
        'zone' => array(
            'type' => 'varchar',
            'length' => 3,
            'not null' => TRUE,
            'default' => '000',
            'description' => 'Kode zon',
        ),
        'entry_date' => array(
            'type' => 'int',
            'default' => 0,
            'not null' => TRUE,
            'description' => 'The time that the pengeluaran entried, as a Unix timestamp.',
        ),
        'jumlah_pemasukan' => array(
            'type' => 'float',
            'size' => 'big',
            'description' => 'Besar Pemasukan.',
        ),
        'jumlah_pemasukan_entry' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'Besar Pemasukan entry character.',
        ),
        'jumlah_pengeluaran' => array(
            'type' => 'float',
            'size' => 'big',
            'description' => 'Besar pengeluaran.',
        ),
        'jumlah_pengeluaran_entry' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'Besar pengeluaran entry character.',
        ),
        'description' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'pengeluaran description.',
        ),
        'month' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Month when entry pemasukan & pengeluaran.',
        ),
        'year' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Year when entry pemasukan & pengeluaran.',
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
        'zone'                      => array('zone'),
        'entry_date'                => array('entry_date'),
        'jumlah_pemasukan'          => array('jumlah_pemasukan'),
        'jumlah_pengeluaran'        => array('jumlah_pengeluaran'),
        'uid'                       => array('uid'),
        'uid_changed'               => array('uid_changed'),
        'created'                   => array('created'),
        'changed'                   => array('changed'),
        'year'                      => array('year'),
        'month'                     => array('month'),
    ),
);
/* End Schema Data Pemasukan dan Pengeluaran */