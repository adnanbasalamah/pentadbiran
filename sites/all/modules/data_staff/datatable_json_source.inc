<?php

function get_staff_record(){
  $aColumns = [
    'id_staff', 'nama_lengkap','nama_hijrah', 'jantina', 'no_ic', 'no_kk', 'no_hp', 'alamat',
    'tarikh_lahir', 'tempat_lahir', 'umur', 'nama_suami', 'nama_ayah', 'anak', 'nama_ibu', 'id_premis', 'id_kawasan',
    'id_zon', 'staff_level'
  ];
  $OrderBy = isset($_GET['iSortCol_0']) ? $_GET['iSortCol_0'] : null;
  $sSearch = isset($_GET['sSearch']) && $_GET['sSearch'] != '' && !is_null($_GET['sSearch']) ? $_GET['sSearch'] : null;
  $OrderData = null;
  if (!is_null($OrderBy)){
    $Operator = isset($_GET['sSortDir_0']) ? $_GET['sSortDir_0'] : 'asc';
    $OrderData[] = $OrderBy.' '.$Operator;
  }
  $range_data = null;
  if (isset($_GET['iDisplayStart']) && isset($_GET['iDisplayLength']) && $_GET['iDisplayLength'] != -1){
    $range_data = [];
    $range_data['start'] = (int)$_GET['iDisplayStart'];
    $range_data['length'] = (int)$_GET['iDisplayLength'];
  }
  $all_staff = get_data_staff(null,false, null, null, 'ta.id_staff ASC',null,true,$sSearch);
  $data_staff = get_data_staff(null,false, null, null, 'ta.id_staff ASC', $range_data, false, $sSearch);
  //$data_zon = getZoneByCode(null, $OrderData, null, null, $sSearch);
  $output = array(
    "sEcho" => intval($_GET['sEcho']),
    "iTotalRecords" => count($all_staff),
    "iTotalDisplayRecords" => count($all_staff),
    "aaData" => array()
  );
  $arrayJK = array_jenis_kelamin();
  $ArrayLevel = array_staff_level();
  $keluargaIcon = '<i class="fa fa-users"></i>';
  $row_staff = [];
  for ($i = 0;$i < count($data_staff);$i++){
    $detailStaff = $data_staff[$i];
    $row = array();
    $row[] = $detailStaff->id_staff;
    $id_div = 'nama_lengkap-' . $detailStaff->id_number;
    $row[] = '<div id="'.$id_div.'" class="edit-field">'.$detailStaff->nama_lengkap.'</div>';
    $id_div = 'nama_hijrah-' . $detailStaff->id_number;
    $row[] = '<div id="'.$id_div.'" class="edit-field">'.$detailStaff->nama_hijrah.'</div>';
    $id_div ='jantina-' . $detailStaff->id_number . '-' . $detailStaff->jantina;
    $row[] = '<div id="'.$id_div.'" class="edit-jantina">'.$arrayJK[$detailStaff->jantina].'</div>';
    $id_div = 'no_ic-' . $detailStaff->id_number;
    $row[] = '<div id="'.$id_div.'" class="edit-field">'.$detailStaff->no_ic.'</div>';
    $id_div = 'no_kk-' . $detailStaff->id_number;
    $row[] = '<div id="'.$id_div.'" class="edit-field">'.$detailStaff->no_kk.'</div>';
    $id_div = 'no_hp-' . $detailStaff->id_number;
    $row[] = '<div id="'.$id_div.'" class="edit-field">'.$detailStaff->no_hp.'</div>';
    $id_div = 'alamat-' . $detailStaff->id_number;
    $row[] = '<div id="'.$id_div.'" class="edit-alamat">'.$detailStaff->alamat.'</div>';
    $id_div = 'tarikh_lahir-' . $detailStaff->id_number;
    $row[] = '<div id="'.$id_div.'" class="edit-tanggal align-center">'.$detailStaff->tarikh_lahir;
    $id_div = 'tempat_lahir-' . $detailStaff->id_number;
    $row[] = '<div id="'.$id_div.'" class="edit-field">'.$detailStaff->tempat_lahir.'</div>';
    $umur = 0;
    if (!empty($detailStaff->tarikh_lahir)) {
      $SplitTgl = explode('-', $detailStaff->tarikh_lahir);
      $umur = count_age($SplitTgl[2], $SplitTgl[1], $SplitTgl[0]);
      $status_pernikahan = '';
      if ($umur >= 17){
        $status_pernikahan = '<button id="status-pernikahan-' . $detailStaff->id_number . '" class="btn-danger btn-xs no-margin btn-block status-pernikahan" onclick="status_pernikahan(\'' . $detailStaff->id_number . '\')">' . $keluargaIcon . ' STATUS PERNIKAHAN</button>';
      }
    }
    $row[] = $umur;
    $row[] = $detailStaff->data_suami_istri.$status_pernikahan;
    $row[] = $detailStaff->data_anak;
    $id_div = 'id_ayah-' . $detailStaff->id_number;
    $row[] = '<div id="'.$id_div.'" class="edit-ayah">'.$detailStaff->ayah.'</div>';
    $id_div = 'id_ibu-' . $detailStaff->id_number;
    $row[] = '<div id="'.$id_div.'" class="edit-ibu">'.$detailStaff->ibu.'</div>';
    $row[] = $detailStaff->premis;
    $row[] = $detailStaff->kawasan;
    $row[] = $detailStaff->zon_name;
    $StaffLevel = isset($ArrayLevel[$detailStaff->staff_level]) ? $ArrayLevel[$detailStaff->staff_level] : '-';
    $row[] = $StaffLevel;
    $row_staff[] = $row;
    //$output['aaData'][] = $row;
  }
  $output['aaData'] = $row_staff;
  echo json_encode( $output );
  exit();
}
