var lang = '';
var desIn = '.';
var desOut = ',';
var separator = '.';
jQuery(function ($) {
    var lang = Drupal.settings.language;
    if (lang != 'id'){
        desIn = '.';
        desOut = '.';
        separator = ',';
    }
    $('.jumlah-pengeluaran').maskNumber({
        thousands: separator,
        integer: true,
    });
    $('.edit-pengeluaran').on('click', function(e){
        e.preventDefault();
        var splitID = $(this).attr('id').split('-');
        var strID = splitID[2];
        alamat = Drupal.settings.basePath + 'getpengeluaranajax/'+ strID;
        $.ajax({
            type: 'POST',
            url: alamat,
            cache: false,
            success: function (data) {
                var returnData = eval(data);
                $('#id-pengeluaran').val(returnData[0].id);
                $('#edit-tanggal').val(returnData[0].tanggal);
                $('#edit-jumlah').val(returnData[0].jumlah_entry);
                $('#edit-keterangan').val(returnData[0].description);
                $('#edit-jumlah').select();
            }
        });
    });
    $('.del-pengeluaran').on('click', function(e) {
        e.preventDefault();
        var confirmation = confirm('Apakah yakin hendak menghapus data pengeluaran ini...??!');
        if (confirmation) {
            var splitID = $(this).attr('id').split('-');
            var strID = splitID[2];
            window.location = Drupal.settings.basePath + 'deletepengeluaran/' + strID;
        }
    });
});