<?php

function get_omset_premis_data($field_name = null, $field_value = null){
  if (!empty($field_name) && !empty($field_value)){
    $FieldArray = ['id','entry_date','description','month','year'];
    if ($field_name == 'entry_date'){
      $WhereClause = [];
      $WhereData = new stdClass();
      $WhereData->clause = "FROM_UNIXTIME(entry_date,'%d-%m-%Y') = :entrydate";
      $WhereData->value = [':entrydate' => $field_value];
      $WhereClause[] = $WhereData;
      $DataOmset['info'] = getTableDataByField(
        'zdatapremis_omset','access omset pengeluaran premis module',
        $FieldArray,null, null, null, null,
        null, null,$WhereClause
      );
    }else {
      $ConditionArray = [];
      $ConsData = new stdClass();
      $ConsData->fieldName = $field_name;
      $ConsData->value = $field_value;
      $ConditionArray[] = $ConsData;
      $DataOmset['info'] = getTableDataByField(
        'zdatapremis_omset','access omset pengeluaran premis module',
        $FieldArray,null, null, null, null,
        $ConditionArray
      );
    }
  }
  if (!empty($DataOmset['info']) && isset($DataOmset['info'][0])){
    $IdLaporan = $DataOmset['info'][0]->id;
    $FieldArrayDetail = ['id_laporan_omset','id_premis','id_unit','jumlah_omset','jumlah_pengeluaran'];
    $LeftJoinArray = array(
      array(
        'tablename' => 'zdatapremis',
        'tablealias' => 'premis',
        'field_source' => 'id',
        'field_join' => 'id_premis',
        'fieldArray' => array(
          'nama'
        ),
      ),
      array(
        'tablename' => 'zdatapremis_unit',
        'tablealias' => 'unit',
        'field_source' => 'id',
        'field_join' => 'id_unit',
        'fieldArray' => array(
          'nama_unit'
        ),
      ),
    );
    $DataOmset['detail'] = getTableDataByField(
      'zdatapremis_omset_premis','access omset pengeluaran premis module',
      $FieldArrayDetail,null, 'id_laporan_omset', $IdLaporan, $LeftJoinArray
    );
    $DataDetail = [];
    for ($i = 0;$i < count($DataOmset['detail']);$i++){
      $DataDetail[$DataOmset['detail'][$i]->id_premis][$DataOmset['detail'][$i]->id_unit] = $DataOmset['detail'][$i];
    }
    $DataOmset['detail'] = $DataDetail;
  }
  return $DataOmset;
}
