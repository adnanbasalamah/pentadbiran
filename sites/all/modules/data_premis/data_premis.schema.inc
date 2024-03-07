<?php
/* Schema For Data Premis */
$schema['zdatapremis'] = array(
    'description' => 'Stores information about data premis.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'random_number',
            'description' => 'Premis ID from premis data',
        ),
        'zone' => array(
            'type' => 'varchar',
            'length' => 3,
            'not null' => TRUE,
            'default' => 'Zon',
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
            'length' => 1000,
            'not null' => TRUE,
            'default' => 'Alamat Premis',
            'description' => 'Alamat premis from premis data',
        ),
        'telepon' => array(
            'type' => 'varchar',
            'length' => 120,
            'not null' => TRUE,
            'default' => '0000000000',
            'description' => 'Telepon premis from premis data',
        ),
        'whatsapp' => array(
            'type' => 'varchar',
            'length' => 120,
            'default' => '0000000000',
            'description' => 'Whatsapp premis from premis data',
        ),
        'bbm' => array(
            'type' => 'varchar',
            'length' => 120,
            'default' => '0000000000',
            'description' => 'Pin bbm premis from premis data',
        ),
        'telegram' => array(
            'type' => 'varchar',
            'length' => 120,
            'default' => '0000000000',
            'description' => 'Telegram premis from premis data',
        ),
        'email' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'default' => 'admin@ikhwanit.com',
            'description' => 'Email premis from premis data',
        ),
        'website' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'default' => 'www.ikhwanit.com',
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
    'primary key' => array('id'),
    'indexes' => array(
        'zone'          => array('zone'),
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
    'foreign keys' => array(
        'zone' => array(
            'table' => 'zdatazone',
            'columns' => array('zone' => 'zone'),
        ),
    ),
);
/* End Schema Data Premis*/

/* Schema For Data Staff Premis */
$schema['zdatastaff'] = array(
    'description' => 'Stores information about data staff.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'random_number',
            'description' => 'Premis Staff id',
        ),
        'id_premis' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'id_premis',
            'description' => 'Id premis dari staff',
        ),
        'nama' => array(
            'type' => 'varchar',
            'length' => 500,
            'not null' => TRUE,
            'default' => 'Nama Premis',
            'description' => 'Nama staff from premis data',
        ),
        'id_jawatan' => array(
            'type' => 'int',
            'default' => 2,
            'description' => 'Id Jawatan Staff',
        ),
        'alamat' => array(
            'type' => 'varchar',
            'length' => 1000,
            'description' => 'Alamat staff from premis data',
        ),
        'telepon' => array(
            'type' => 'varchar',
            'length' => 120,
            'description' => 'Telepon staff from premis data',
        ),
        'whatsapp' => array(
            'type' => 'varchar',
            'length' => 120,
            'description' => 'Whatsapp staff from premis data',
        ),
        'bbm' => array(
            'type' => 'varchar',
            'length' => 120,
            'description' => 'Pin bbm staff from premis data',
        ),
        'telegram' => array(
            'type' => 'varchar',
            'length' => 120,
            'description' => 'Telegram staff from premis data',
        ),
        'email' => array(
            'type' => 'varchar',
            'length' => 255,
            'description' => 'Email staff from premis data',
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
    'foreign keys' => array(
        'id_premis' => array(
            'table' => 'zdatapremis',
            'columns' => array('id_premis' => 'id_premis'),
        ),
    ),
);
/* End Schema Data Premis*/

