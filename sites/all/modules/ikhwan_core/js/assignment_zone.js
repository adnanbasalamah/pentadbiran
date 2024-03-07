var CurrActiveId = 0;
var CurrActiveAssignmentId = 0;
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
    $('.assignment-value').each(function(){
        if ($(this).val()){
            grandTotal = grandTotal + parseFloat($(this).val());
        }
    });
    return grandTotal;
}
jQuery(function ($) {
  $('.input-assignment').on('click', function (e) {
    e.preventDefault();
    var splitID = $(this).attr('id').split('-');
    window.location = Drupal.settings.basePath + 'assignmentzone/' + splitID[1] + '/0/' + $('#edit-month').val() + '/' + $('#edit-year').val();
  });
  $('.assignment-value').on('keyup', function () {
    var strID = $(this).attr('id');
    var splitID = strID.split('-');
    var totalValue = 0;
    if (Drupal.settings.jenisAssignment.periode == 0) {
      var columnIdentity = splitID[5];
    } else {
      var columnIdentity = splitID[3];
    }
    $('.assignment-column-' + columnIdentity).each(function () {
      if ($(this).val()) {
        totalValue = totalValue + parseFloat($(this).val());
      }
    });
    $('#foot-' + columnIdentity).html('<strong>' + addCommas(totalValue) + '</strong>');
    var grandTotal = calculateGrandTotal($);
    $('#grand-total').html('<strong>GRAND TOTAL : ' + addCommas(grandTotal) + '</strong>');
  });
  var grandTotal = 0;
  $('.assignment-value').each(function () {
    if ($(this).val()) {
      grandTotal = grandTotal + parseFloat($(this).val());
    }
  });
  $('#grand-total').html('<strong>GRAND TOTAL : ' + addCommas(grandTotal) + '</strong>');
  $('.input-offset').on('click', function () {
    var splitID = $(this).attr('id').split('-');
    if (typeof splitID[1] != 'undefined') {
      window.location = Drupal.settings.basePath + 'assignmentzone/' + Drupal.settings.assigmentId + '/' + splitID[1] + '/' + Drupal.settings.bulan + '/' + Drupal.settings.tahun;
    }
  });
  $('.assignment-value').on('click', function () {
    var FieldId = $(this).attr('id');
    CurrActiveId = FieldId;
    var ArrId = FieldId.split('-');
    if (parseInt(ArrId[6]) > 0 && $(this).val() > 0) {
      CurrActiveAssignmentId = ArrId[6];
      var ParentId = ArrId[0] + '-' + ArrId[1] + '-' + ArrId[2] + '-' + ArrId[3] + '-' + ArrId[4];
      var DateInt = parseInt(ArrId[5]) * 1000;
      var AssgDate = new Date(DateInt);
      var StrDate = AssgDate.getDate() + '-' + (AssgDate.getMonth() + 1) + '-' + AssgDate.getFullYear();
      $('#zone').val($('#' + ParentId + ' label').html());
      $('#assg-date').val(StrDate);
      $('#bank-in').val($(this).val());
      $('#exampleModal').modal('show');
    }
  });
  $('#exampleModal').on('shown.bs.modal', function () {
    var request = new Object;
    var ArrId = CurrActiveId.split('-');
    request.id_assignment = ArrId[6];
    var AjaxAddress = Drupal.settings.basePath + 'assigment_resit';
    $.ajax({
      url: AjaxAddress,
      type: 'POST',
      data: request,
      dataType: 'json',
      success: function (data) {
        var ResultDt = eval(data);
        $('#edit-image-file').val('');
        if (ResultDt.file_path != 'no_file') {
          $('#im-area').html('<img src="' + ResultDt.file_path + '" width="250" />');
        } else {
          $('#im-area').html('');
        }
        $('#keterangan').val(ResultDt.denied_desc);
        if (ResultDt.approval_status == 1){
          $('#myModalLabel').html('Assignment Bank In Information (Verified)');
          $('#myModalLabel').parent().css('background-color','royalblue');
        }else if (ResultDt.approval_status == 2){
          $('#myModalLabel').html('Assignment Bank In Information (Denied)');
          $('#myModalLabel').parent().css('background-color','red');
        }else{
          $('#myModalLabel').html('Assignment Bank In Information');
          $('#myModalLabel').parent().css('background-color','#444444');
        }
      }
    });
    $('#assignment-id').val(ArrId[6]);
    $('#bank-in').select();
  });
  $('#bank-in').on('keyup', function (e) {
    if (e.keyCode != 13) {
      $('#' + CurrActiveId).val($(this).val());
      $('#'+ CurrActiveId).keyup();
    }
  });
  $('#save-assignment-info').on('click', function () {
    var request = new Object;
    request.assignment_id = CurrActiveAssignmentId;
    request.bank_in = $('#bank-in').val();
    var AjaxAddress = Drupal.settings.basePath + 'assigment_update';
    $.ajax({
      url: AjaxAddress,
      type: 'POST',
      data: request,
      dataType: 'json',
      success: function (data) {
        alert('Assignment Updated...!!');
      }
    });
  });
  $('#verify-bankin').on('click', function () {
    var request = new Object;
    request.assignment_id = CurrActiveAssignmentId;
    request.status = 1;
    request.bank_in = $('#bank-in').val();
    var AjaxAddress = Drupal.settings.basePath + 'assigment_approval';
    $.ajax({
      url: AjaxAddress,
      type: 'POST',
      data: request,
      dataType: 'json',
      success: function (data) {
        alert('Assignment Verified...!!');
        $('#'+ CurrActiveId).removeClass('not-verified');
        $('#'+ CurrActiveId).removeClass('not-key-in');
        $('#'+ CurrActiveId).removeClass('denied');
        $('#'+ CurrActiveId).addClass('verified');
        $('#myModalLabel').html('Assignment Bank In Information (Verified)');
        $('#myModalLabel').parent().css('background-color','royalblue');
      }
    });
  });
  $('#deny-bankin').on('click', function () {
    var request = new Object;
    request.assignment_id = CurrActiveAssignmentId;
    request.status = 2;
    request.bank_in = $('#bank-in').val();
    if ($('#keterangan').val() != '') {
      request.denied_description = $('#keterangan').val();
      var AjaxAddress = Drupal.settings.basePath + 'assigment_approval';
      $.ajax({
        url: AjaxAddress,
        type: 'POST',
        data: request,
        dataType: 'json',
        success: function (data) {
          alert('Assignment Denied...!!');
          $('#'+ CurrActiveId).removeClass('not-verified');
          $('#'+ CurrActiveId).removeClass('not-key-in');
          $('#'+ CurrActiveId).removeClass('verified');
          $('#'+ CurrActiveId).addClass('denied');
          $('#myModalLabel').html('Assignment Bank In Information (Denied)');
          $('#myModalLabel').parent().css('background-color','red');
        }
      });
    }else {
      alert('Deny description could not be empty...!!!');
    }
  });
  var oTable = $("#table-assignment").dataTable( {
    "sScrollY": "300px",
    "sScrollX": "100%",
    "sScrollXInner": "300%",
    "bScrollCollapse": true,
    "bPaginate": false,
    "bAutoWidth": false,
  } );
  new FixedColumns( oTable, {
    "iLeftColumns": 2,
  } );
})
