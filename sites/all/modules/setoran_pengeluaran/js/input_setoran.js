var lang = '';
var desIn = '.';
var desOut = ',';
var separator = '.';
function addCommas(nStr) {
    nStr += "";
    x = nStr.split(".");
    x1 = x[0];
    x2 = x.length > 1 ? "." + x[1] : "";
    var rgx = /(\d+)(\d{3})/;
    while (rgx.test(x1)) {
        x1 = x1.replace(rgx, "$1" + "." + "$2");
    }
    return x1 + x2;
}
function addSeparatorsNF(nStr, inD, outD, sep)
{
    nStr += '';
    var dpos = nStr.indexOf(inD);
    var nStrEnd = '';
    if (dpos != -1) {
        nStrEnd = outD + nStr.substring(dpos + 1, nStr.length);
        nStr = nStr.substring(0, dpos);
    }
    var rgx = /(\d+)(\d{3})/;
    while (rgx.test(nStr)) {
        nStr = nStr.replace(rgx, '$1' + sep + '$2');
    }
    return nStr + nStrEnd;
}
function calculateTotal($){
    var totalValue = 0;
    $('.setoran-value').each(function () {
        if ($(this).val() != ''){
            try {
                if (separator == '.'){
                    var nilai = $(this).val().replace(/\./g,'');
                }else{
                    var nilai = $(this).val().replace(/\,/g,'');
                }
                totalValue = totalValue + eval(nilai);
            } catch (e) {
            }
        }
    });
    return totalValue;
}
function pengeluaran_premis(idpremis, month, year, idoverhead){
    window.location = Drupal.settings.basePath + 'inputdetailpengeluaran/'+ idpremis + '/' + month +'/'+ year +'/'+ idoverhead;
}
jQuery(function ($) {
    var lang = $('html').attr('lang');
    if (lang != 'id'){
        desIn = '.';
        desOut = '.';
        separator = ',';
    }
    $('.setoran-value').maskNumber({
        thousands: separator,
        integer: true,
    });
    $.notify("TOTAL SETORAN : ", {
        clickToHide: false,
        autoHide: false,
        style: 'bootstrap',
        className: 'error total-setoran',
        globalPosition: 'bottom right',
    });
    $('.setoran-value').on('keyup', function () {
        totalValue = calculateTotal($);
        var splitStrID = $(this).attr('id').split('-');
        var strID = parseInt(splitStrID[splitStrID.length - 1]);
        var komulatif = 0;
        for (var i = 1;i <= $('.setoran-value').length;i++) {
            if (separator == '.') {
                var nilaiSetoran = $('.setoran-' + i).val().replace(/\./g, '');
            }else{
                var nilaiSetoran = $('.setoran-' + i).val().replace(/\,/g, '');
            }
            komulatif = komulatif + parseFloat(eval(nilaiSetoran));
            $('#total-'+ i).html(addSeparatorsNF(komulatif,desIn,desOut,separator));
        }
        totalSaldo = totalValue - Drupal.settings.totalPengeluaran;
        //$('#total-'+ strID).html(addSeparatorsNF(komulatif));
        $('#grand-total,#grand-total-2').html('<strong>'+ addSeparatorsNF(totalValue,desIn,desOut,separator) +'</strong>');
        var totalSetoranView = '<div><div class="pull-left"><strong>TOTAL SERAHAN : </strong>&nbsp;&nbsp;</div><div class="pull-right"><strong>'+ addSeparatorsNF(totalValue,desIn,desOut,separator) +'</strong></div></div><br>';
        totalSetoranView += '<div><div class="pull-left"><strong>SALDO/BAKI : </strong>&nbsp;&nbsp;</div><div class="pull-right"><strong>'+ addSeparatorsNF(totalSaldo,desIn,desOut,separator) +'</strong></div></div><br>';
        totalSetoranView += '<div><div class="pull-left"><strong>TOTAL KETENTUAN/OH : </strong>&nbsp;&nbsp;</div><div class="pull-right"><strong>'+ addSeparatorsNF(Drupal.settings.totalKetentuan,desIn,desOut,separator) +'</strong></div></div><br>';
        totalSetoranView += '<div><div class="pull-left"><strong>TOTAL PENGELUARAN : </strong>&nbsp;&nbsp;</div><div class="pull-right"><strong>'+ addSeparatorsNF(Drupal.settings.totalPengeluaran,desIn,desOut,separator) +'</strong></div></div><br>';
        totalSetoranView += '<div><div class="pull-left"><strong>TOTAL KEKURANGAN : </strong>&nbsp;&nbsp;</div><div class="pull-right"><strong>'+ addSeparatorsNF(Drupal.settings.totalKekurangan,desIn,desOut,separator) +'</strong></div></div><br>';
        $('.notifyjs-container .total-setoran span').html(totalSetoranView);
    });
    $('.setoran-value').keyup();
})