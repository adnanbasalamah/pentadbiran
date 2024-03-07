function addCommas(nStr){
    nStr += "";
    x = nStr.split(".");
    x1 = x[0];
    x2 = x.length > 1 ? "." + x[1] : "";
    var rgx = /(\d+)(\d{3})/;
    while (rgx.test(x1)) {
        x1 = x1.replace(rgx, "$1" + "," + "$2");
    }
    return x1 + x2;
}
function calculateGrandTotal($){
    var grandTotal = 0;
    $('.jumlah-pengeluaran').each(function(){
        if ($(this).val()){
            grandTotal = grandTotal + parseFloat($(this).val());
        }
    });
    return grandTotal;
}
jQuery(function ($) {
    $('.input-assignment-out').on('click', function (e){
        e.preventDefault();
        var splitID = $(this).attr('id').split('-');
        var Bulan = 0;
        var Tahun = 0;
        if (typeof $('#edit-month').val() != 'undefined'){
            Bulan = $('#edit-month').val();
        }else{
            Bulan = Drupal.settings.bulan;
        }
        if (typeof $('#edit-year').val() != 'undefined'){
            Tahun = $('#edit-year').val();
        }else{
            Tahun = Drupal.settings.tahun;
        }
        window.location = Drupal.settings.basePath + 'pengeluaranassignment/'+ splitID[1] + '/' + Bulan + '/' + Tahun;
    });
    $('.jumlah-pengeluaran').on('keyup', function () {
        var splitID = $(this).attr('id').split('-');
        if (typeof splitID[5] != 'undefined'){
            var dateUnix = splitID[5];
            var totalDay = 0;
            $('.jumlah-'+ dateUnix).each(function () {
                totalDay += parseFloat($(this).val());
            });
            if (totalDay > 0){
                $('.total-'+ dateUnix).val(addCommas(totalDay));
            }
        }
        var grandTotalPengeluaran = calculateGrandTotal($);
        $('#grand-total').html(addCommas(grandTotalPengeluaran));
    });
    $('.jumlah-pengeluaran').keyup();
})
