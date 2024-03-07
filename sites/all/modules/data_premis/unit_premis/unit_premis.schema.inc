<?php

/* Schema For Data Unit Premis */
$schema['zdatapremis_unit'] = array(
  'description' => 'Stores information about data unit premis.',
  'fields' => array(
    'id' => array(
      'type' => 'serial',
      'size' => 'big',
      'not null' => TRUE,
      'description' => t('ID record.'),
    ),
    'id_premis' => array(
      'type' => 'varchar',
      'length' => 30,
      'not null' => TRUE,
      'default' => 'id_premis',
      'description' => 'Id premis dari unit',
    ),
    'nama_unit' => array(
      'type' => 'varchar',
      'length' => 500,
      'not null' => TRUE,
      'default' => 'Nama Unit',
      'description' => 'Nama unit from unit premis',
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
    'nama_unit'     => array('nama_unit'),
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
/* End Schema Unit Premis*/
