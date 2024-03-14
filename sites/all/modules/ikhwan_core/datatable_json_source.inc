<?php

function get_zons_record(){
  //iSortCol_0 => order, sSortDir_0 => order direction
  //sSearch => term search
  $aColumns = array( 'id', 'zon_name', 'telepon','whatsapp' );
  $OrderBy = isset($_GET['iSortCol_0']) ? $_GET['iSortCol_0'] : null;
  $sSearch = isset($_GET['sSearch']) && $_GET['sSearch'] != '' && !is_null($_GET['sSearch']) ? $_GET['sSearch'] : null;
  $month = isset($_GET['month']) ? $_GET['month'] : date('n');
  $year = isset($_GET['year']) ? $_GET['year'] : date('Y');
  $OrderData = null;
  if (!is_null($OrderBy)){
    $Operator = isset($_GET['sSortDir_0']) ? $_GET['sSortDir_0'] : 'asc';
    $OrderData = [];
    $OrderInfo = [];
    $OrderInfo['fieldname'] = $aColumns[$OrderBy];
    $OrderInfo['operator'] = $Operator;
    $OrderData[] = $OrderInfo;
  }
  $data_zon = getZoneByCode(null, $OrderData, null, null, $sSearch);
  $output = array(
    "sEcho" => intval($_GET['sEcho']),
    "iTotalRecords" => count($data_zon),
    "iTotalDisplayRecords" => count($data_zon),
    "aaData" => array()
  );
  $editIcon = '<i class="fa fa-edit"></i>';
  $addIcon = '<i class="fa fa-plus"></i>';
  $DeleteIcon = '<i class="fa fa-trash"></i>';
  for ($i = 0;$i < count($data_zon);$i++){
    $row = array();
    for ( $j=0 ; $j<count($aColumns) ; $j++ ){
      $row[] = $data_zon[$i]->{$aColumns[$j]};
    }
    $row[] = '0';
    $row[] = '0';
    $row[] = '0';
    $editButtonVar = array(
      'element' => array(
        '#attributes' => array(
          'class' => array('btn-success', 'btn-xs', 'no-margin', 'edit-zone'),
          'id' => 'edit-zone-' . $data_zon[$i]->id,
          'name' => 'edit-zone-' . $data_zon[$i]->id,
          'onclick' => 'edit_zon(\'' . $data_zon[$i]->id . '\')',
        ),
        '#button_type' => 'button',
        '#value' => $editIcon . ' EDIT',
      )
    );
    $editButton = theme('button', $editButtonVar);
    $row[] = $editButton;
    $addButtonVar = array(
      'element' => array(
        '#attributes' => array(
          'class' => array('btn-primary', 'btn-xs', 'no-margin', 'add-pendapatan'),
          'id' => 'add-pendapatan-' . $data_zon[$i]->id,
          'name' => 'add-pendapatan-' . $data_zon[$i]->id,
          'onclick' => 'entry_pemasukan(\'' . $data_zon[$i]->id . '\', ' . $month . ',' . $year . ')',
        ),
        '#button_type' => 'button',
        '#value' => $editIcon . ' ENTRY KEWANGAN',
      )
    );
    $addButton = theme('button', $addButtonVar);
    $row[] = $addButton;
    $DeleteButtonVar = array(
      'element' => array(
        '#attributes' => array(
          'class' => array('btn-danger', 'btn-xs', 'no-margin', 'delete-zone'),
          'id' => 'delete-zone-' . $data_zon[$i]->id,
          'name' => 'delete-zone-' . $data_zon[$i]->id,
          'onclick' => 'delete_zon(\'' . $data_zon[$i]->id . '\')',
        ),
        '#button_type' => 'button',
        '#value' => $DeleteIcon . ' DELETE',
      )
    );
    $DeleteButton = theme('button', $DeleteButtonVar);
    $row[] = $DeleteButton;
    $output['aaData'][] = $row;
  }
  echo json_encode( $output );
  exit();
}
