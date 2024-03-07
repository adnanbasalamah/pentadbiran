function edit_premis(idPremis){
    window.location = Drupal.settings.basePath + 'masterdata/premis/add/'+ idPremis;
}
function manage_staff(idPremis){
    window.location = Drupal.settings.basePath + 'masterdata/premis/staff/'+ idPremis;
}
function overhead_premis(idPremis){
    window.location = Drupal.settings.basePath + 'masterdata/overhead_staff/'+ idPremis;
}
function setoran_premis(idPremis, bulan, tahun) {
    window.location = Drupal.settings.basePath + 'setoran/'+ idPremis +'/'+ bulan +'/'+ tahun;
}
function delete_premis(idPremis){
    var konfirmasi = confirm('Yakin ingin menghapus data premis terkait...??!');
    if (konfirmasi){
        window.location = Drupal.settings.basePath + 'masterdata/premis/delete/'+ idPremis;
    }
}
jQuery(function ($) {
    $('#new-premis').on('click', function (e){
        e.preventDefault();
        window.location = Drupal.settings.basePath + 'masterdata/premis/add';
    });
    alamatupdate = Drupal.settings.basePath + 'masterdata/premis/updatepremis';
    alamatnegeri = Drupal.settings.basePath + 'masterdata/negeri/getajax';
    $('.edit-negeri').editable(alamatupdate, {
        'submitdata': function ( value, settings ) {
            return { 'row_id': this.parentNode.getAttribute('id'), 'kol_id': 11 };
        },
        'loadurl' : alamatnegeri,
        'loaddata' : function(value, settings) {
            var cellId = this.getAttribute('id').split('-');
            return {zone: cellId[1]};
        },
        'width': '140px',
        'height': '20px',
        'submit': 'Ok',
        'type': 'select',
        'indicator': 'Menyimpan...',
        'tooltip': 'Klik untuk mengubah...'
    });
    $('#datatable-1').dataTable().fnSettings().aoDrawCallback.push( {
        "fn": function () {
            $('.edit-negeri').editable('destroy');
            $('.edit-negeri').editable(alamatupdate, {
                'submitdata': function ( value, settings ) {
                    return { 'cell_id': this.getAttribute('id') };
                },
                'loadurl' : alamatnegeri,
                'loaddata' : function(value, settings) {
                    var cellId = this.getAttribute('id').split('-');
                    return {zone: cellId[1]};
                },
                'width': '140px',
                'height': '20px',
                'submit': 'Ok',
                'type': 'select',
                'indicator': 'Menyimpan...',
                'tooltip': 'Klik untuk mengubah...'
            });
        },
    });
})
