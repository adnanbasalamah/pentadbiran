<?php
/* Schema For Overhead Category */
$schema['zoverhead_category'] = array(
    'description' => 'Stores information about overhead category.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'random_number',
            'description' => 'Overhead Category ID',
        ),
        'category' => array(
            'type' => 'varchar',
            'length' => 500,
            'not null' => TRUE,
            'default' => 'Category Overhead',
            'description' => 'Overhead Category Title',
        ),
        'description' => array(
            'type' => 'varchar',
            'length' => 2000,
            'description' => 'Overhead Category Description',
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
        'category'          => array('category'),
        'uid_changed'   => array('uid_changed'),
        'created'       => array('created'),
        'changed'       => array('changed'),
    ),
);
/* End Schema Data Overhead Category */

/* Schema For Data Overhead*/
$schema['zoverhead'] = array(
    'description' => 'Stores information about data overhead.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'random_number',
            'description' => 'Overhead id',
        ),
        'id_category' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'id_category',
            'description' => 'Overhead Category ID',
        ),
        'nama' => array(
            'type' => 'varchar',
            'length' => 500,
            'not null' => TRUE,
            'default' => 'Overhead Name',
            'description' => 'Overhead Name',
        ),
        'default_value' => array(
            'type' => 'float',
            'size' => 'big',
            'description' => 'Overhead default value.',
        ),
        'description' => array(
            'type' => 'varchar',
            'length' => 700,
            'description' => 'Detail information about overhead',
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
        'id_category'   => array('id_category'),
        'nama'          => array('nama'),
        'default_value' => array('default_value'),
        'uid_changed'   => array('uid_changed'),
        'created'       => array('created'),
        'changed'       => array('changed'),
    ),
    'foreign keys' => array(
        'id_category' => array(
            'table' => 'zoverhead_category',
            'columns' => array('id_category' => 'id_category'),
        ),
    ),
);
/* End Schema Data Overhead*/
/* Schema For Data Overhead Staff */
$schema['zoverhead_staff'] = array(
    'description' => 'Stores information about data overhead staff.',
    'fields' => array(
        'id' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'random_number',
            'description' => 'Overhead Staff id',
        ),
        'id_staff' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'id_staff',
            'description' => 'ID Staff',
        ),
        'id_overhead' => array(
            'type' => 'varchar',
            'length' => 30,
            'not null' => TRUE,
            'default' => 'id_overhead',
            'description' => 'Overhead ID',
        ),
        'overhead_value' => array(
            'type' => 'float',
            'size' => 'big',
            'description' => 'Overhead default value.',
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
        'id_staff'      => array('id_staff'),
        'id_overhead'   => array('id_overhead'),
        'overhead_value'=> array('overhead_value'),
        'uid_changed'   => array('uid_changed'),
        'created'       => array('created'),
        'changed'       => array('changed'),
    ),
    'foreign keys' => array(
        'id_staff' => array(
            'table'     => 'zdatastaff',
            'columns'   => array('id_staff' => 'id_staff'),
        ),
        'id_overhead' => array(
            'table'     => 'zoverhead',
            'columns'   => array('id_overhead' => 'id_overhead'),
        ),
    ),
);
/* End Schema Data Overhead*/

