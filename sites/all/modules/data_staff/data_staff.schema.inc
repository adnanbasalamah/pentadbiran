<?php

/* Schema For Detail Data Staff */
$schema['zdatastaff_detail'] = array(
    'description' => 'Stores information about detail data staff.',
    'fields' => array(
        'id_staff' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'random_number',
            'description' => 'Staff id from data staff',
        ),
        'nama_lengkap' => array(
            'type' => 'varchar',
            'length' => 255,
            'description' => 'Nama staff from premis data',
        ),
        'nama_hijrah' => array(
            'type' => 'varchar',
            'length' => 255,
            'description' => 'Nama staff from premis data',
        ),
        'jenis_kelamin' => array(
            'type' => 'int',
            'description' => '0 -> Laki laki, 1 -> Perempuan',
        ),
        'no_ktp' => array(
            'type' => 'varchar',
            'length' => 100,
            'description' => 'No. KTP/ ID Number staff',
        ),
        'no_kk' => array(
            'type' => 'varchar',
            'length' => 100,
            'description' => 'No. KK/ Family ID staff',
        ),
        'tanggal_lahir' => array(
            'type' => 'varchar',
            'mysql_type' => 'date',
            'description' => 'Tanggal lahir staff',
        ),
        'tempat_lahir' => array(
            'type' => 'varchar',
            'length' => 255,
            'description' => 'Tempat lahir staff/ahli',
        ),
        'id_suami' => array(
            'type' => 'varchar',
            'length' => 30,
            'description' => 'ID Suami staff',
        ),
        'id_ayah' => array(
            'type' => 'varchar',
            'length' => 30,
            'description' => 'ID Ayah staff',
        ),
        'nama_suami' => array(
            'type' => 'varchar',
            'length' => 255,
            'description' => 'Nama suami staff, diisi jika suami bukan staff/ahli',
        ),
        'nama_ayah' => array(
            'type' => 'varchar',
            'length' => 255,
            'description' => 'Nama ayah staff, diisi jika suami bukan staff/ahli',
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
    'primary key' => array('id_staff'),
    'indexes' => array(
        'nama_lengkap'  => array('nama_lengkap'),
        'nama_hijrah'   => array('nama_hijrah'),
        'id_suami'      => array('id_suami'),
        'id_ayah'       => array('id_ayah'),
        'nama_suami'    => array('nama_suami'),
        'nama_ayah'     => array('nama_ayah'),
        'uid_changed'   => array('uid_changed'),
        'created'       => array('created'),
        'changed'       => array('changed'),
    ),
    'foreign keys' => array(
        'id_staff' => array(
            'table' => 'zdatastaff',
            'columns' => array('id_staff' => 'id'),
        ),
    ),
);
/* End Schema Detail Data Staff*/