<?php

function get_data_unit_premis($id_unit = null, $id_premis = null, $id_zon = null){
  $conditionArray = null;
  if (!empty($id_unit)){
    $conditionArray = [];
    $consData = new stdClass();
    $consData->fieldName = 'ta.id';
    $consData->value = $id_unit;
    if (is_array($id_unit)) {
      $consData->operator = 'IN';
    }
    $conditionArray[] = $consData;
  }
  if (!empty($id_premis)){
    $conditionArray = [];
    $consData = new stdClass();
    $consData->fieldName = 'ta.id_premis';
    $consData->value = $id_premis;
    if (is_array($id_premis)) {
      $consData->operator = 'IN';
    }
    $conditionArray[] = $consData;
  }
  if (!empty($id_zon)){
    $conditionArray = [];
    $consData = new stdClass();
    $consData->fieldName = 'premis.zone';
    $consData->value = $id_zon;
    if (is_array($id_zon)) {
      $consData->operator = 'IN';
    }
    $conditionArray[] = $consData;
  }
  $fieldArray = array(
    'id', 'id_premis', 'nama_unit', 'alamat', 'telepon', 'whatsapp', 'bbm',
    'telegram', 'email', 'created', 'changed', 'uid', 'uid_changed'
  );
  $leftJoinArray = array(
    array(
      'tablename' => 'zdatapremis',
      'tablealias' => 'premis',
      'field_source' => 'id',
      'field_join' => 'id_premis',
      'fieldArray' => array(
        'nama','zone','idnegeri'
      ),
    ),
    array(
      'tablename' => 'zdatanegeri',
      'tablealias' => 'negeri',
      'sourcealias' => 'premis',
      'field_source' => 'id',
      'field_join' => 'idnegeri',
      'fieldArray' => array(
        'nama'
      ),
    ),
  );
  $DataUnit = getTableDataByField(
    'zdatapremis_unit','access unit premis',
    $fieldArray,null,null,null, $leftJoinArray, $conditionArray);
  return $DataUnit;
}

function delete_unit_data($id_unit = null){
  $DeletedData = null;
  if (!empty($id_unit)){
    $conditionData = array();
    $consObj = new stdClass();
    $consObj->fieldName = 'id';
    $consObj->fieldValue = $id_unit;
    $consObj->status = 'and';
    $conditionData[] = $consObj;
    $deletedData = deleteTableData('zdatapremis_unit', 'admin unit premis',$conditionData);
    drupal_set_message('Unit premis berhasil dihapus...!!','error');
    drupal_goto('masterdata/premis/unit');
  }
  return $DeletedData;
}
