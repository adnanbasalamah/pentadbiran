<?php

/* Schema For Master Data Pemasukan dan Pengeluaran */
$schema['zdatapremis_omset'] = array(
    'description' => 'Stores information about omset dan pengeluaran premis.',
    'fields' => array(
        'id' => array(
            'type' => 'serial',
            'size' => 'big',
            'not null' => TRUE,
            'description' => t('ID record.'),
        ),
        'entry_date' => array(
            'type' => 'int',
            'default' => 0,
            'not null' => TRUE,
            'description' => 'The time that the omset & pengeluaran entried, as a Unix timestamp.',
        ),
        'description' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'omset dan pengeluaran description.',
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
        'entry_date'                => array('entry_date'),
        'uid'                       => array('uid'),
        'uid_changed'               => array('uid_changed'),
        'created'                   => array('created'),
        'changed'                   => array('changed'),
        'year'                      => array('year'),
        'month'                     => array('month'),
    ),
);
/* End Schema Master Data Omset dan Pengeluaran Premis */

/* Schema For Detail Data Pemasukan dan Pengeluaran Premis */
$schema['zdatapremis_omset_premis'] = array(
    'description' => 'Stores information about omset dan pengeluaran premis.',
    'fields' => array(
        'id_laporan_omset' => array(
            'type' => 'int',
            'size' => 'big',
            'not null' => TRUE,
            'default' => 0,
            'description' => 'ID Master data omset dan pengeluaran premis',
        ),
        'id_premis' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => '000',
            'description' => 'Id Premis',
        ),
        'id_unit' => array(
          'type' => 'int',
          'size' => 'big',
          'default' => 0,
          'description' => 'Id Unit',
        ),
        'jumlah_omset' => array(
            'type' => 'float',
            'size' => 'big',
            'description' => 'Besar Pemasukan.',
        ),
        'jumlah_pengeluaran' => array(
            'type' => 'float',
            'size' => 'big',
            'description' => 'Besar pengeluaran.',
        ),
    ),
    'primary key' => array('id_laporan_omset','id_premis','id_unit'),
    'indexes' => array(
        'id_laporan_omset'          => array('id_laporan_omset'),
        'id_premis'                 => array('id_premis'),
        'id_unit'                   => array('id_unit'),
        'jumlah_omset'              => array('jumlah_omset'),
        'jumlah_pengeluaran'        => array('jumlah_pengeluaran'),
    ),
);
/* End Schema Detail Data Omset dan Pengeluaran Premis */
