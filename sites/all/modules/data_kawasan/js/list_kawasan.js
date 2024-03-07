function edit_kawasan(idKawasan){
  window.location = Drupal.settings.basePath + 'masterdata/kawasan/add/'+ idKawasan;
}
function delete_kawasan(idKawasan){
  var konfirmasi = confirm('Yakin ingin menghapus data kawasan terkait...??!');
  if (konfirmasi){
    window.location = Drupal.settings.basePath + 'masterdata/kawasan/delete/'+ idKawasan;
  }
}
jQuery(function ($) {
  $('#new-kawasan').on('click', function (e){
    e.preventDefault();
    window.location = Drupal.settings.basePath + 'masterdata/kawasan/add';
  });
})
