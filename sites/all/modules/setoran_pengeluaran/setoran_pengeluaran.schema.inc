<?php
/* Schema For Data Setoran */
$schema['zpremis_setoran'] = array(
    'description' => 'Stores information about setoran/serahan premis.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'random_number',
            'description' => 'Setoran ID',
        ),
        'id_premis' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'random_number',
            'description' => 'Premis ID related to pengeluaran',
        ),
        'setoran_date' => array(
            'type' => 'int',
            'default' => 0,
            'not null' => TRUE,
            'description' => 'The time that the setoran entried, as a Unix timestamp.',
        ),
        'jumlah' => array(
            'type' => 'float',
            'size' => 'big',
            'description' => 'Besar setoran.',
        ),
        'jumlah_entry' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'Besar setoran entry character.',
        ),
        'description' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'setoran description.',
        ),
        'month' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Month when entry setoran.',
        ),
        'year' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Year when entry setoran.',
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
        'id_premis'     => array('id_premis'),
        'setoran_date'  => array('setoran_date'),
        'uid'           => array('uid'),
        'uid_changed'   => array('uid_changed'),
        'created'       => array('created'),
        'changed'       => array('changed'),
        'year'          => array('year'),
        'month'         => array('month'),
    ),
);
/* End Schema Data Setoran */

/* Schema For Data Pengeluaran */
$schema['zpremis_pengeluaran'] = array(
    'description' => 'Stores information about pengeluaran.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'random_number',
            'description' => 'Setoran ID',
        ),
        'id_overhead' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'random_number',
            'description' => 'Overhead ID related to pengeluaran',
        ),
        'id_premis' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'random_number',
            'description' => 'Premis ID related to pengeluaran',
        ),
        'pengeluran_date' => array(
            'type' => 'int',
            'default' => 0,
            'not null' => TRUE,
            'description' => 'The time that the pengeluaran entried, as a Unix timestamp.',
        ),
        'jumlah' => array(
            'type' => 'float',
            'size' => 'big',
            'description' => 'Besar pengeluaran.',
        ),
        'jumlah_entry' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'Besar setoran entry character.',
        ),
        'description' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'pengeluaran description.',
        ),
        'month' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Month when entry setoran.',
        ),
        'year' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Year when entry setoran.',
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
        'id_premis'         => array('id_premis'),
        'id_overhead'       => array('id_overhead'),
        'pengeluran_date'   => array('pengeluran_date'),
        'uid'               => array('uid'),
        'uid_changed'       => array('uid_changed'),
        'created'           => array('created'),
        'changed'           => array('changed'),
        'year'              => array('year'),
        'month'             => array('month'),
    ),
);
/* End Schema Data Pengeluaran */
