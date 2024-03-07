<?php

/* Schema For Data Zone */
$schema['zdatazone'] = array(
    'description' => 'Stores information about data zone.',
    'fields' => array(
        'zone' => array(
            'type' => 'varchar',
            'length' => 3,
            'not null' => TRUE,
            'default' => '-',
            'description' => 'Kode zon dari data premis',
        ),
        'nama' => array(
            'type' => 'varchar',
            'length' => 500,
            'not null' => TRUE,
            'default' => 'Nama Premis',
            'description' => 'Nama premis from premis data',
        ),
        'alamat' => array(
            'type' => 'varchar',
            'length' => 700,
            'description' => 'Alamat premis from premis data',
        ),
        'telepon' => array(
            'type' => 'varchar',
            'length' => 120,
            'description' => 'Telepon premis from premis data',
        ),
        'whatsapp' => array(
            'type' => 'varchar',
            'length' => 120,
            'description' => 'Whatsapp premis from premis data',
        ),
        'bbm' => array(
            'type' => 'varchar',
            'length' => 120,
            'description' => 'Pin bbm premis from premis data',
        ),
        'telegram' => array(
            'type' => 'varchar',
            'length' => 120,
            'description' => 'Telegram premis from premis data',
        ),
        'email' => array(
            'type' => 'varchar',
            'length' => 255,
            'description' => 'Email premis from premis data',
        ),
        'website' => array(
            'type' => 'varchar',
            'length' => 255,
            'description' => 'Website premis from premis data',
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
    'primary key' => array('zone'),
    'indexes' => array(
        'nama'          => array('nama'),
        'alamat'        => array('alamat'),
        'telepon'       => array('telepon'),
        'whatsapp'      => array('whatsapp'),
        'bbm'           => array('bbm'),
        'telegram'      => array('telegram'),
        'uid_changed'   => array('uid_changed'),
        'created'       => array('created'),
        'changed'       => array('changed'),
    ),
);
/* End Schema Data Zone*/

/* Schema For Data Assigment */
$schema['zdata_assigment'] = array(
    'description' => 'Stores information about data assigment.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 13,
            'not null' => TRUE,
            'default' => 'random_number',
            'description' => 'Assignment ID from assignment data',
        ),
        'assignment_code' => array(
            'type' => 'varchar',
            'length' => 20,
            'not null' => TRUE,
            'default' => 'PKH',
            'description' => 'Kode assigment',
        ),
        'assignment_name' => array(
            'type' => 'varchar',
            'length' => 500,
            'not null' => TRUE,
            'default' => 'Pendapatan Kumpulan Harian',
            'description' => 'Nama assigment',
        ),
        'judul_periode' => array(
            'type' => 'varchar',
            'length' => 100,
            'not null' => TRUE,
            'default' => 'Nama Premis',
            'description' => 'Nama premis from premis data',
        ),
        'periode' => array(
            'type' => 'int',
            'default' => 0,
            'description' => '0 -> Harian, 1 -> Mingguan, 2 -> Bulanan, 3 -> Tahunan, 4 -> Insidentil',
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
        'assignment_code' => array('assignment_code'),
        'assignment_name' => array('assignment_name'),
        'judul_periode'   => array('judul_periode'),
        'periode'         => array('periode'),
        'uid_changed'     => array('uid_changed'),
        'created'         => array('created'),
        'changed'         => array('changed'),
    ),
);
/* End Schema Data Assignment */

/* Schema For Assigment Zone */
$schema['zassigment_zone'] = array(
    'description' => 'Stores information about data assigment zone.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 13,
            'not null' => TRUE,
            'default' => 'random_number',
            'description' => 'Assignment Zone ID from Assignment Zone data',
        ),
        'assignment_code' => array(
            'type' => 'varchar',
            'length' => 20,
            'not null' => TRUE,
            'default' => 'PKH',
            'description' => 'Kode assigment',
        ),
        'zone' => array(
            'type' => 'varchar',
            'length' => 3,
            'not null' => TRUE,
            'default' => '001',
            'description' => 'Kode Zone',
        ),
        'target' => array(
            'type' => 'float',
            'size' => 'big',
            'description' => 'Target Assignment.',
        ),
        'bank_in' => array(
            'type' => 'float',
            'size' => 'big',
            'description' => 'Total bank in.',
        ),
        'periode' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'periode of assigment, can be date, or month or year or insidentil.',
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
        'assignment_code' => array('assignment_code'),
        'zone'            => array('zone'),
        'target'          => array('target'),
        'bank_in'         => array('bank_in'),
        'uid_changed'     => array('uid_changed'),
        'created'         => array('created'),
        'changed'         => array('changed'),
    ),
    'foreign keys' => array(
        'zone' => array(
            'table' => 'zdatazone',
            'columns' => array('zone' => 'zone'),
        ),
        'assignment_code' => array(
            'table' => 'zdata_assigment',
            'columns' => array('assignment_code' => 'assignment_code'),
        ),
    ),
);
/* End Schema Assignment Zone */

/* Schema Pengeluaran Assignment Zone */
$schema['zpengeluaran_assignment'] = array(
    'description' => 'Stores information about standard graduate profile subject.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'not set',
            'description' => 'pengeluaran assignment ID.',
        ),
        'assignment_id' => array(
            'type' => 'varchar',
            'length' => 30,
            'default' => null,
            'description' => 'jenis assignment related ID.',
        ),
        'no' => array(
            'type' => 'int',
            'default' => 1,
            'description' => 'No urut pengeluaran.',
        ),
        'perkara' => array(
            'type' => 'text',
            'size' => 'big',
            'not null' => TRUE,
            'description' => 'Perkara pengeluaran.',
        ),
        'jumlah' => array(
            'type' => 'float',
            'size' => 'big',
            'description' => 'Besar pengeluaran.',
        ),
        'tglpengeluaran' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'Tanggal penjualan.',
        ),
        'uid' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'User ID that create the record.',
        ),
        'uid_changed' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'User ID that changed the record.',
        ),
        'created' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'The time that the row  was created, as a Unix timestamp.',
        ),
        'changed' => array(
            'type' => 'int',
            'default' => 0,
            'description' => 'The time that the row  was updated, as a Unix timestamp.',
        ),
    ),
    'primary key' => array(
        'id',
    ),
    'indexes' => array(
        'assignment_id' => array('assignment_id'),
        'no'            => array('no'),
        'jumlah'        => array('jumlah'),
        'tglpengeluaran'=> array('tglpengeluaran'),
        'uid'           => array('uid'),
        'uid_changed'   => array('uid_changed'),
        'created'       => array('created'),
        'changed'       => array('changed'),
    ),
    'foreign keys' => array(
        'assignment_id' => array(
            'table' => 'zdatazone',
            'columns' => array('zone' => 'zone'),
        ),
    ),
);
/* End Schema Pengeluaran Assignment Zone */