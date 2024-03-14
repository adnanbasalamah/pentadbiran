function entry_pemasukan(zoneCode, month, year){
    window.location = Drupal.settings.basePath + "pemasukanpengeluaran/"+ zoneCode +"/"+ month +"/"+ year;
}
function edit_zon(zonId){
  if (zonId !== "" && zonId !== 0){
    window.location = Drupal.settings.basePath + "masterdata/zone/add/" + zonId;
  }
}

function delete_zon(zonId){
  if (zonId !== "" && zonId !== 0){
    var Konfirmasi = confirm("Yakin menghapus zone ini???");
    if (Konfirmasi) {
      window.location = Drupal.settings.basePath + "masterdata/zone/delete/" + zonId;
    }
  }
}
jQuery(function ($) {
  $("#new-zone").on("click", function (e) {
    e.preventDefault();
    window.location = Drupal.settings.basePath + "masterdata/zone/add";
  });
});
