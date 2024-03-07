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
  var totalValue = [0,0];
  $('.input-omset').each(function () {
    if ($(this).val() != ''){
      try {
        if (Drupal.settings.separator == '.'){
          var nilai = $(this).val().replace(/\./g,'');
        }else{
          var nilai = $(this).val().replace(/\,/g,'');
        }
        totalValue[0] = totalValue[0] + eval(nilai);
      } catch (e) {
      }
    }
  });
  $('.input-pengeluaran').each(function () {
    if ($(this).val() != ''){
      try {
        if (Drupal.settings.separator == '.'){
          var nilai = $(this).val().replace(/\./g,'');
        }else{
          var nilai = $(this).val().replace(/\,/g,'');
        }
        totalValue[1] = totalValue[1] + eval(nilai);
      } catch (e) {
      }
    }
  });
  return totalValue;
}
jQuery(function ($) {
  $('.input-omset,.input-pengeluaran').maskNumber({
    thousands: Drupal.settings.separator,
    integer: true,
  });
  $.notify("TOTAL OMSET : \nTOTAL PENGELUARAN : ", {
    clickToHide: false,
    autoHide: false,
    style: 'bootstrap',
    className: 'error total-omset',
    globalPosition: 'bottom right',
  });
  $('.input-omset,.input-pengeluaran').on('keyup', function () {
    totalValue = calculateTotal($);
    $('#total-omset').html('<strong>'+ addSeparatorsNF(totalValue[0], Drupal.settings.desIn, Drupal.settings.desOut, Drupal.settings.separator) +'</strong>');
    $('#total-pengeluaran').html('<strong>'+ addSeparatorsNF(totalValue[1], Drupal.settings.desIn, Drupal.settings.desOut, Drupal.settings.separator) +'</strong>');
    var TotalOmset = '<div><div class="pull-left"><strong>TOTAL OMSET : </strong>&nbsp;&nbsp;</div><div class="pull-right"><strong>'+ addSeparatorsNF(totalValue[0], Drupal.settings.desIn, Drupal.settings.desOut, Drupal.settings.separator) +'</strong></div></div><br>';
    TotalOmset += '<div><div class="pull-left"><strong>TOTAL PER-HARI : </strong>&nbsp;&nbsp;</div><div class="pull-right"><strong>'+ addSeparatorsNF(totalValue[1], Drupal.settings.desIn, Drupal.settings.desOut, Drupal.settings.separator) +'</strong></div></div><br>';
    $('.notifyjs-container .total-omset span').html(TotalOmset);
  });
  $('.input-omset').keyup();
  $('.input-pengeluaran').keyup();
  $("#edit-entry-date").datepicker({
    changeMonth: true,
    changeYear: true,
    dateFormat: "dd-mm-yy",
  });
})
