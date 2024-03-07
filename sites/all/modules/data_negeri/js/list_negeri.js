function edit_negeri(idNegeri){
    window.location = Drupal.settings.basePath + 'masterdata/negeri/add/'+ idNegeri;
}
function manage_staff(idNegeri){
    window.location = Drupal.settings.basePath + 'masterdata/negeri/staff/'+ idNegeri;
}
function overhead_negeri(idNegeri){
    window.location = Drupal.settings.basePath + 'masterdata/overhead_staff/'+ idNegeri;
}
function setoran_negeri(idNegeri, bulan, tahun) {
    window.location = Drupal.settings.basePath + 'setoran/'+ idNegeri +'/'+ bulan +'/'+ tahun;
}
function delete_negeri(idNegeri){
    var konfirmasi = confirm('Yakin ingin menghapus data negeri terkait...??!');
    if (konfirmasi){
        window.location = Drupal.settings.basePath + 'masterdata/negeri/delete/'+ idNegeri;
    }
}
jQuery(function ($) {
    $('#new-negeri').on('click', function (e){
        e.preventDefault();
        window.location = Drupal.settings.basePath + 'masterdata/negeri/add';
    });
})
