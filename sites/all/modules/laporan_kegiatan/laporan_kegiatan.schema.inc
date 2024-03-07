<?php

/* Schema For Kegiatan Jemaah */
$schema['zkegiatan_jemaah'] = array(
    'description' => 'Stores information about kegiatan jemaah.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'Random ID',
            'description' => 'ID Kegiatan, random value',
        ),
        /*'zone' => array(
            'type' => 'varchar',
            'length' => 3,
            'default' => '-',
            'description' => 'Kode zon terkait kegiatan',
        ),
        'idnegeri' => array(
            'type' => 'varchar',
            'length' => 30,
            'default' => 'Id Negeri',
            'description' => 'Id negeri terkait kegiatan',
        ),*/
        'nama' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'default' => 'Nama Kegiatan',
            'description' => 'Nama kegiatan',
        ),
        'deskripsi' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'Deskripsi kegiatan.',
        ),
        'jenis_kegiatan' => array(
            'type' => 'int',
            'size' => 'tiny',
            'default' => 0,
            'description' => 'Jenis isian kegiatan 0 => Pilihan, 1 => Isian',
        ),
        'weight' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Weight of kegiatan, supaya dapat di urutkan.',
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
        'status' => array(
            'type' => 'int',
            'size' => 'tiny',
            'default' => 1,
            'description' => 'Status kegiatan 0 => Tidak Aktif, 1 => Aktif',
        ),
    ),
    'primary key' => array('id'),
    'indexes' => array(
        /*'zone'          => array('zone'),
        'idnegeri'      => array('idnegeri'),*/
        'nama'          => array('nama'),
        'jenis_kegiatan'=> array('jenis_kegiatan'),
        'weight'        => array('weight'),
        'uid_changed'   => array('uid_changed'),
        'created'       => array('created'),
        'changed'       => array('changed'),
        'status'=> array('status'),
    ),
);

/* Schema For Pilihan Jawaban Kegiatan Jemaah */
$schema['zpilihan_jawaban_kegiatan'] = array(
    'description' => 'Stores information about pilihan jawaban kegiatan jemaah.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'Random ID',
            'description' => 'ID Pilihan Jawaban Kegiatan, random value',
        ),
        'id_kegiatan_jemaah' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'Random ID',
            'description' => 'ID Kegiatan',
        ),
        'pilihan' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'default' => 'Pilihan',
            'description' => 'Pilihan Jawaban',
        ),
        'value' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'default' => 'Pilihan',
            'description' => 'Nilai Pilihan Jawaban',
        ),
        'weight' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Weight of kegiatan, supaya dapat di urutkan.',
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
        'status' => array(
            'type' => 'int',
            'size' => 'tiny',
            'default' => 1,
            'description' => 'Status kegiatan 0 => Tidak Aktif, 1 => Aktif',
        ),
    ),
    'primary key' => array('id'),
    'indexes' => array(
        'id_kegiatan_jemaah' => array('id_kegiatan_jemaah'),
        'pilihan'            => array('pilihan'),
        'value'              => array('value'),
        'weight'             => array('weight'),
        'uid_changed'        => array('uid_changed'),
        'created'            => array('created'),
        'changed'            => array('changed'),
        'status'             => array('status'),
    ),
);

/* Schema For Tempat Kegiatan*/
$schema['ztempat_kegiatan'] = array(
    'description' => 'Stores information about tempat kegiatan.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'Random ID',
            'description' => 'ID Tempat, random value',
        ),
        'zone' => array(
            'type' => 'varchar',
            'length' => 3,
            'default' => '-',
            'description' => 'Kode zon terkait kegiatan',
        ),
        'idnegeri' => array(
            'type' => 'varchar',
            'length' => 30,
            'default' => 'Id Negeri',
            'description' => 'Id negeri terkait kegiatan',
        ),
        'nama' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'default' => 'Nama Kegiatan',
            'description' => 'Nama kegiatan',
        ),
        'deskripsi' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'Deskripsi kegiatan.',
        ),
        'weight' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Weight of kegiatan, supaya dapat di urutkan.',
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
        'zone'          => array('zone'),
        'idnegeri'      => array('idnegeri'),
        'nama'          => array('nama'),
        'weight'        => array('weight'),
        'uid_changed'   => array('uid_changed'),
        'created'       => array('created'),
        'changed'       => array('changed'),
    ),
);

/* Schema For Kegiatan Jemaah */
$schema['zdata_kegiatan_staff'] = array(
    'description' => 'Stores information about pelaksanaan kegiatan staff.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'Random ID',
            'description' => 'ID pelaksanaan, Random ID',
        ),
        'id_kegiatan' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'Id Kegiatan',
            'description' => 'Id kegiatan terkait pelaksanaan',
        ),
        'id_tempat' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'Nama Kegiatan',
            'description' => 'Nama kegiatan',
        ),
        'id_staff' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'Id Kegiatan',
            'description' => 'Id kegiatan terkait pelaksanaan',
        ),
        'waktu_kegiatan' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Waktu pelaksaan kegiatan, as a Unix timestamp.',
        ),
        'value' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'default' => 'Pilihan',
            'description' => 'Nilai Pilihan Jawaban',
        ),
        'deskripsi' => array(
            'type' => 'text',
            'size' => 'big',
            'description' => 'Deskripsi kegiatan.',
        ),
        'weight' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Weight of kegiatan, supaya dapat di urutkan.',
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
        'idkegiatan'    => array('id_kegiatan'),
        'idtempat'      => array('id_tempat'),
        'idstaff'       => array('id_staff'),
        'waktu_kegiatan'=> array('waktu_kegiatan'),
        'value'         => array('value'),
        'uid'           => array('uid'),
        'uid_changed'   => array('uid_changed'),
        'created'       => array('created'),
        'changed'       => array('changed'),
    ),
);