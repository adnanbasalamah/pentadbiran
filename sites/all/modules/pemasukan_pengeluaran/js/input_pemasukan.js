function addCommas(nStr)
{
    nStr += '';
    var x = nStr.split('.');
    var x1 = x[0];
    var x2 = x.length > 1 ? '.' + x[1] : '';
    var rgx = /(\d+)(\d{3})/;
    while (rgx.test(x1)) {
        x1 = x1.replace(rgx, '$1' + ',' + '$2');
    }
    return x1 + x2;
}
function calculateTotal($,fieldCalc){
    var totalValue = 0;
    $('.'+ fieldCalc +'-value').each(function () {
        if ($(this).val() != ''){
            try {
                var nilai = $(this).val().replace(/\,/g,'');
                totalValue = totalValue + eval(nilai);
            } catch (e) {
            }
        }
    });
    return totalValue;
}
jQuery(function ($) {
    $('.pemasukan-value,.pengeluaran-value').maskNumber({
        thousands: ',',
    });
    $.notify("TOTAL PEMASUKAN & PENGELUARAN : ", {
        clickToHide: false,
        autoHide: false,
        style: 'bootstrap',
        className: 'error total-setoran',
        globalPosition: 'bottom right',
    });
    $('.pemasukan-value').on('keyup', function () {
        totalValue = calculateTotal($, 'pemasukan');
        var splitStrID = $(this).attr('id').split('-');
        if (splitStrID.length == 7){
            var strID = parseInt(splitStrID[splitStrID.length - 1]);
        }else if(splitStrID.length == 8){
            var strID = parseInt(splitStrID[splitStrID.length - 2]);
        }
        var baki = 0;
        var pemasukan =  $(this).val().replace(/\,/g,'');
        try {
            pemasukan = eval(pemasukan);
        }catch (e) {
        }
        var pengeluaran = $('.pengeluaran-'+ strID).val().replace(/\,/g,'');
        try {
            pengeluaran = eval(pengeluaran);
            baki = pemasukan - pengeluaran;
            totalValue2 = calculateTotal($, 'pengeluaran');
            totalValue3 = totalValue - totalValue2;
            $('#total-'+ strID).html(addCommas(baki.toFixed(2)));
            $('#total-baki').html('<strong>'+ addCommas(totalValue3.toFixed(2)) +'</strong>');
            $('#total-pemasukan').html('<strong>'+ addCommas(totalValue.toFixed(2)) +'</strong>');
            var totalPemasukanView = '<div><div class="pull-left"><strong>TOTAL PENDAPATAN : </strong>&nbsp;&nbsp;</div><div class="pull-right"><strong>'+ addCommas(totalValue.toFixed(2)) +'</strong></div></div><br>';
            totalPemasukanView += '<div><div class="pull-left"><strong>TOTAL PENGELUARAN : </strong>&nbsp;&nbsp;</div><div class="pull-right"><strong>'+ addCommas(totalValue2.toFixed(2)) +'</strong></div></div><br>';
            totalPemasukanView += '<div><div class="pull-left"><strong>TOTAL BAKI : </strong>&nbsp;&nbsp;</div><div class="pull-right"><strong>'+ addCommas(totalValue3.toFixed(2)) +'</strong></div></div><br>';
            $('.notifyjs-container .total-setoran span').html(totalPemasukanView);
        }catch (e) {
        }
    });
    $('.pengeluaran-value').on('keyup', function () {
        totalValue = calculateTotal($, 'pengeluaran');
        var splitStrID = $(this).attr('id').split('-');
        if (splitStrID.length == 7){
            var strID = parseInt(splitStrID[splitStrID.length - 1]);
        }else if(splitStrID.length == 8){
            var strID = parseInt(splitStrID[splitStrID.length - 2]);
        }
        var baki = 0;
        var pengeluaran =  $(this).val().replace(/\,/g,'');
        try {
            pengeluaran = eval(pengeluaran);
        }catch (e) {
        }
        var pemasukan = $('.pemasukan-'+ strID).val().replace(/\,/g,'');
        try {
            pemasukan = eval(pemasukan);
            baki = pemasukan - pengeluaran;
            totalValue2 = calculateTotal($, 'pemasukan');
            totalValue3 = totalValue2 - totalValue;
            $('#total-'+ strID).html(addCommas(baki.toFixed(2)));
            $('#total-baki').html('<strong>'+ addCommas(totalValue3.toFixed(2)) +'</strong>');
            $('#total-pengeluaran').html('<strong>'+ addCommas(totalValue.toFixed(2)) +'</strong>');
            var totalPemasukanView = '<div><div class="pull-left"><strong>TOTAL PENDAPATAN : </strong>&nbsp;&nbsp;</div><div class="pull-right"><strong>'+ addCommas(totalValue2.toFixed(2)) +'</strong></div></div><br>';
            totalPemasukanView += '<div><div class="pull-left"><strong>TOTAL PENGELUARAN : </strong>&nbsp;&nbsp;</div><div class="pull-right"><strong>'+ addCommas(totalValue.toFixed(2)) +'</strong></div></div><br>';
            totalPemasukanView += '<div><div class="pull-left"><strong>TOTAL BAKI : </strong>&nbsp;&nbsp;</div><div class="pull-right"><strong>'+ addCommas(totalValue3.toFixed(2)) +'</strong></div></div><br>';
            $('.notifyjs-container .total-setoran span').html(totalPemasukanView);
        }catch (e) {
        }
    });
    $('.pemasukan-value').keyup();
    $('.pengeluaran-value').keyup();
})