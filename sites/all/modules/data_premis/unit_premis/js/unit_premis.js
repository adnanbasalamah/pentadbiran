function edit_unit(id_unit){
  window.location = Drupal.settings.basePath + 'masterdata/premis/unit/'+ id_unit;
}
function delete_unit(id_unit, nama_unit){
  var konfirmasi = confirm('Yakin ingin menghapus data unit '+ nama_unit +'...??!');
  if (konfirmasi){
    window.location = Drupal.settings.basePath + 'masterdata/premis/unit/delete/'+ id_unit;
  }
}
