function entry_pemasukan(zoneCode, month, year){
    window.location = Drupal.settings.basePath + 'pemasukanpengeluaran/'+ zoneCode +'/'+ month +'/'+ year;
}
jQuery(function ($) {
    $('.edit-zone').on('click', function (e){
        e.preventDefault();
        var splitID = $(this).attr('id').split('-');
        if (splitID.length > 0 && typeof splitID[2] != 'undefined'){
            window.location = Drupal.settings.basePath + 'masterdata/zone/add/'+ splitID[2];
        }
    });
  $('.delete-zone').on('click', function (e){
    e.preventDefault();
    var Konfirmasi = confirm('Yakin menghapus zone ini???');
    if (Konfirmasi) {
      var splitID = $(this).attr('id').split('-');
      if (splitID.length > 0 && typeof splitID[2] != 'undefined') {
        alert(splitID[2]);
        window.location = Drupal.settings.basePath + 'masterdata/zone/delete/' + splitID[2];
      }
    }
  });
    $('#new-zone').on('click', function (e){
        e.preventDefault();
        window.location = Drupal.settings.basePath + 'masterdata/zone/add';
    });
})
