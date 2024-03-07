function addCommas(nStr){
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
    $('.input-oh').each(function () {
        if ($(this).val() != ''){
            try {
                if (Drupal.settings.separator == '.'){
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

jQuery(function ($) {
    $('.input-oh').maskNumber({
        thousands: Drupal.settings.separator,
        integer: true,
    });
    $.notify("TOTAL OH SEBULAN : \nTOTAL OH HARIAN : ", {
        clickToHide: false,
        autoHide: false,
        style: 'bootstrap',
        className: 'error total-oh',
        globalPosition: 'bottom right',
    });
    $('.input-oh').on('keyup', function () {
        totalValue = calculateTotal($);
        $('#grand-total').html('<strong>TOTAL PER-BULAN : '+ addSeparatorsNF(totalValue, Drupal.settings.desIn, Drupal.settings.desOut, Drupal.settings.separator) +'</strong>');
        $('#total-harian').html('<strong>TOTAL PER-HARI : '+ addSeparatorsNF(Math.round(totalValue/30), Drupal.settings.desIn, Drupal.settings.desOut, Drupal.settings.separator) +'</strong>');
        var totalOHView = '<div><div class="pull-left"><strong>TOTAL PER-BULAN : </strong>&nbsp;&nbsp;</div><div class="pull-right"><strong>'+ addSeparatorsNF(totalValue, Drupal.settings.desIn, Drupal.settings.desOut, Drupal.settings.separator) +'</strong></div></div><br>';
        totalOHView += '<div><div class="pull-left"><strong>TOTAL PER-HARI : </strong>&nbsp;&nbsp;</div><div class="pull-right"><strong>'+ addSeparatorsNF(Math.round(totalValue/30), Drupal.settings.desIn, Drupal.settings.desOut, Drupal.settings.separator) +'</strong></div></div><br>';
        $('.notifyjs-container .total-oh span').html(totalOHView);
    });
    $('.input-oh').keyup();
})