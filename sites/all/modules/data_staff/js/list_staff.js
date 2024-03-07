jQuery(function ($) {
  var AlamatUpdate = Drupal.settings.basePath + 'masterdata/staff/updatestaff';
  var AlamatGetStaffLelaki = Drupal.settings.basePath + 'masterdata/staff/getajax';
  var AlamatAddAnak = Drupal.settings.basePath + 'masterdata/staff/addanak';
  var AlamatGetZon = Drupal.settings.basePath + 'masterdata/zone/getajax';
  var AlamatGetKawasan = Drupal.settings.basePath + 'masterdata/kawasan/getajax';
  var IconAnak = '<i class="fa fa-user"></i>';
  $(".list-anak").hide();
  $(".show-anak").on("click", function (e){
    e.preventDefault();
    var split_id = $(this).attr("id").split("-");
    var id_list_anak = "list-anak-"+ split_id[2];
    if ($("#"+ id_list_anak).is(":visible")){
      $("#"+ id_list_anak).hide();
      $(this).html(IconAnak + ' SHOW ANAK');
      $(this).removeClass('btn-warning').addClass('btn-success');
    }else{
      $("#"+ id_list_anak).show();
      $(this).html(IconAnak + ' HIDE ANAK');
      $(this).removeClass('btn-success').addClass('btn-warning');
    }
  });
  $('.add-anak').on('click', function () {
    var SplitStrId = $(this).attr('id').split('-');
    var StrId = SplitStrId[2];
    window.location = AlamatAddAnak + '/' + StrId;
  });
  $('.edit-field').editable(AlamatUpdate, {
    'width': '100px',
    'height': '20px',
    'submit': 'Ok',
    'indicator': 'Menyimpan...',
    'tooltip': 'Klik untuk mengubah...'
  });
  $('.edit-alamat').editable(AlamatUpdate, {
    'width': '200px',
    'height': '100px',
    'type': 'textarea',
    'submit': 'Ok',
    'indicator': 'Menyimpan...',
    'tooltip': 'Klik untuk mengubah...'
  });
  $('.edit-tanggal').editable(AlamatUpdate, {
    width: 100,
    height: 18,
    style: 'margin: 0',
    tooltip: 'Klik untuk mengubah tanggal lahir',
    indicator: 'Saving...',
    type: "datepicker",
    callback: function (value, settings) {
      var SplitVal = value.split('-');
      var SplitId = $(this).attr('id').split('-');
      var AjaxAddress = Drupal.settings.basePath + 'calculateage/' + SplitVal[2] + '/' + SplitVal[1] + '/' + SplitVal[0];
      $.ajax({
        url: AjaxAddress,
        type: 'POST',
        success: function (data) {
          $('#umur-' + SplitId[2]).html(data);
        }
      });
    },
    datepicker: {
      changeMonth: true,
      changeYear: true,
      dateFormat: "yy-mm-dd"
    }
  });
  $('.edit-jantina').editable(AlamatUpdate, {
    'data': " {'0':'Laki-Laki','1':'Perempuan'} ",
    'width': '100px',
    'height': '20px',
    'type': 'select',
    'submit': 'Ok',
    'indicator': 'Menyimpan...',
    'tooltip': 'Klik untuk memilih jantina...'
  });
  $('.select-suami').editable(AlamatUpdate, {
    //json from php script
    'loadurl': AlamatGetStaffLelaki,
    'loaddata': function (value, settings) {
      return {jk: 0, chosen_input: 1};
    },
    //or data
    //data   : " {'0':'Vilnius', '1':'Klaipėda', '2':'Kaunas', '3':'Šiauliai', '4':'Palanga', 'selected':'0'}",
    'indicator': 'Saving...',
    'tooltip': 'Click to edit...',
    'style': "inherit",
    //Click outside editable area is ignored for select clicks
    'onblur': "ignore",
    'type': 'select',
    'submit': 'Simpan',
    'cancel': 'Batal'
  }).click(function () {
    $(this).find('select').chosen();
    $(this).find('button').button().css('font-size', '12px').css('margin-right', '4px').css('margin-top', '5px');
  });
  $('.select-zon').editable(AlamatUpdate, {
    //json from php script
    'loadurl': AlamatGetZon,
    'loaddata': function (value, settings) {
      return {chosen_input: 1};
    },
    //or data
    //data   : " {'0':'Vilnius', '1':'Klaipėda', '2':'Kaunas', '3':'Šiauliai', '4':'Palanga', 'selected':'0'}",
    'indicator': 'Saving...',
    'tooltip': 'Click to edit...',
    'style': "inherit",
    //Click outside editable area is ignored for select clicks
    'onblur': "ignore",
    'type': 'select',
    'submit': 'Simpan',
    'cancel': 'Batal'
  }).click(function () {
    $(this).find('select').chosen();
    $(this).find('button').button().css('font-size', '12px').css('margin-right', '4px').css('margin-top', '5px');
  });
  $('.select-kawasan').editable(AlamatUpdate, {
    //json from php script
    'loadurl': AlamatGetKawasan,
    'loaddata': function (value, settings) {
      return {chosen_input: 1};
    },
    //or data
    //data   : " {'0':'Vilnius', '1':'Klaipėda', '2':'Kaunas', '3':'Šiauliai', '4':'Palanga', 'selected':'0'}",
    'indicator': 'Saving...',
    'tooltip': 'Click to edit...',
    'style': "inherit",
    //Click outside editable area is ignored for select clicks
    'onblur': "ignore",
    'type': 'select',
    'submit': 'Simpan',
    'cancel': 'Batal'
  }).click(function () {
    $(this).find('select').chosen();
    $(this).find('button').button().css('font-size', '12px').css('margin-right', '4px').css('margin-top', '5px');
  });
  $('.edit-level').editable(AlamatUpdate, {
    'data': Drupal.settings.level_staff,
    'width': '100px',
    'height': '20px',
    'type': 'select',
    'submit': 'Ok',
    'indicator': 'Menyimpan...',
    'tooltip': 'Klik untuk memilih level staff...'
  });
  $('#datatable-1').dataTable().fnSettings().aoDrawCallback.push({
    "fn": function () {
      $(".list-anak").hide();
      $(".show-anak").on("click", function (e){
        e.preventDefault();
        var split_id = $(this).attr("id").split("-");
        var id_list_anak = "list-anak-"+ split_id[2];
        if ($("#"+ id_list_anak).is(":visible")){
          $("#"+ id_list_anak).hide();
          $(this).html(IconAnak + ' SHOW ANAK');
          $(this).removeClass('btn-warning').addClass('btn-success');
        }else{
          $("#"+ id_list_anak).show();
          $(this).html(IconAnak + ' HIDE ANAK');
          $(this).removeClass('btn-success').addClass('btn-warning');
        }
      });
      $('.add-anak').off('click');
      $('.add-anak').on('click', function () {
        var SplitStrId = $(this).attr('id').split('-');
        var StrId = SplitStrId[2];
        window.location = AlamatAddAnak + '/' + StrId;
      });
      $('.edit-field').editable('destroy');
      $('.edit-field').editable(AlamatUpdate, {
        'width': '100px',
        'height': '20px',
        'submit': 'Ok',
        'indicator': 'Menyimpan...',
        'tooltip': 'Klik untuk mengubah...'
      });
      $('.edit-tanggal').editable('destroy');
      $('.edit-tanggal').editable(AlamatUpdate, {
        width: 100,
        height: 18,
        style: 'margin: 0',
        tooltip: 'Klik untuk mengubah tanggal lahir',
        indicator: 'Saving...',
        type: "datepicker",
        callback: function (value, settings) {
          var SplitVal = value.split('-');
          var SplitId = $(this).attr('id').split('-');
          var AjaxAddress = Drupal.settings.basePath + 'calculateage/' + SplitVal[2] + '/' + SplitVal[1] + '/' + SplitVal[0];
          $.ajax({
            url: AjaxAddress,
            type: 'POST',
            success: function (data) {
              $('#umur-' + SplitId[2]).html(data);
            }
          });
        },
        datepicker: {
          changeMonth: true,
          changeYear: true,
          dateFormat: "yy-mm-dd"
        }
      });
      $('.edit-jantina').editable('destroy');
      $('.edit-jantina').editable(AlamatUpdate, {
        'data': " {'0':'Laki-Laki','1':'Perempuan'} ",
        'width': '100px',
        'height': '20px',
        'type': 'select',
        'submit': 'Ok',
        'indicator': 'Menyimpan...',
        'tooltip': 'Klik untuk memilih jantina...'
      });
      $('.select-suami').editable('destroy');
      $('.select-suami').editable(AlamatUpdate, {
        //json from php script
        'loadurl': AlamatGetStaffLelaki,
        'loaddata': function (value, settings) {
          return {jk: 0, chosen_input: 1};
        },
        'indicator': 'Saving...',
        'tooltip': 'Click to edit...',
        'style': "inherit",
        'onblur': "ignore",
        'type': 'select',
        'submit': 'Simpan',
        'cancel': 'Batal'
      }).click(function () {
        $(this).find('select').chosen();
        $(this).find('button').button().css('font-size', '12px').css('margin-right', '4px').css('margin-top', '5px');
      });
      $('.edit-level').editable('destroy');
      $('.edit-level').editable(AlamatUpdate, {
        'data': Drupal.settings.level_staff,
        'width': '100px',
        'height': '20px',
        'type': 'select',
        'submit': 'Ok',
        'indicator': 'Menyimpan...',
        'tooltip': 'Klik untuk memilih level staff...'
      });
      $('.edit-alamat').editable('destroy');
      $('.edit-alamat').editable(AlamatUpdate, {
        'width': '200px',
        'height': '100px',
        'type': 'textarea',
        'submit': 'Ok',
        'indicator': 'Menyimpan...',
        'tooltip': 'Klik untuk mengubah...'
      });
      $('.select-zon').editable('destroy');
      $('.select-zon').editable(AlamatUpdate, {
        //json from php script
        'loadurl': AlamatGetZon,
        'loaddata': function (value, settings) {
          return {chosen_input: 1};
        },
        //or data
        //data   : " {'0':'Vilnius', '1':'Klaipėda', '2':'Kaunas', '3':'Šiauliai', '4':'Palanga', 'selected':'0'}",
        'indicator': 'Saving...',
        'tooltip': 'Click to edit...',
        'style': "inherit",
        //Click outside editable area is ignored for select clicks
        'onblur': "ignore",
        'type': 'select',
        'submit': 'Simpan',
        'cancel': 'Batal'
      }).click(function () {
        $(this).find('select').chosen();
        $(this).find('button').button().css('font-size', '12px').css('margin-right', '4px').css('margin-top', '5px');
      });
    }
  });
  var oTable = $('#datatable-1').dataTable();
  $('#datatable-1').on( 'draw.dt', function () {
    $(".list-anak").hide();
    $(".show-anak").off("click");
    $(".show-anak").on("click", function (e){
      e.preventDefault();
      var split_id = $(this).attr("id").split("-");
      var id_list_anak = "list-anak-"+ split_id[2];
      if ($("#"+ id_list_anak).is(":visible")){
        $("#"+ id_list_anak).hide();
        $(this).html(IconAnak + ' SHOW ANAK');
        $(this).removeClass('btn-warning').addClass('btn-success');
      }else{
        $("#"+ id_list_anak).show();
        $(this).html(IconAnak + ' HIDE ANAK');
        $(this).removeClass('btn-success').addClass('btn-warning');
      }
    });
    $('.select-suami').editable('destroy');
    $('.select-suami').editable(AlamatUpdate, {
      //json from php script
      'loadurl': AlamatGetStaffLelaki,
      'loaddata': function (value, settings) {
        return {jk: 0, chosen_input: 1};
      },
      'indicator': 'Saving...',
      'tooltip': 'Click to edit...',
      'style': "inherit",
      'onblur': "ignore",
      'type': 'select',
      'submit': 'Simpan',
      'cancel': 'Batal'
    }).click(function () {
      $(this).find('select').chosen();
      $(this).find('button').button().css('font-size', '12px').css('margin-right', '4px').css('margin-top', '5px');
    });
  });
  var idx = 0;
  $.each($('.btn-show-hide'), function(){
    var bVis = oTable.fnSettings().aoColumns[idx].bVisible;
    if (!bVis){
      $(this).addClass('btn-white');
    }
    idx++;
  });
  /*$('.btn-show-hide').forEach(function (){

  });*/
  $('.btn-show-hide').on('click', function (){
    var IdButton = $(this).attr('id');
    var SplitId = IdButton.split('-');
    var bVis = oTable.fnSettings().aoColumns[parseInt(SplitId[1])].bVisible;
    oTable.fnSetColumnVis( parseInt(SplitId[1]), bVis ? false : true );
    if (bVis){
      $(this).addClass('btn-white');
    }else{
      $(this).removeClass('btn-white');
    }
  });
});
