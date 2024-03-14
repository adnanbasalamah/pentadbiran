function edit_zon(id_staff){
  var AlamatZonStaff = Drupal.settings.basePath + 'masterdata/staff/zon';
  if (id_staff > 0){
    window.location = AlamatZonStaff + '/' + id_staff;
  }
}
jQuery(function ($) {
  var AlamatUpdate = Drupal.settings.basePath + 'masterdata/staff/updatestaff';
  var AlamatGetStaffLelaki = Drupal.settings.basePath + 'masterdata/staff/getajax';
  var AlamatAddAnak = Drupal.settings.basePath + 'masterdata/staff/addanak';
  var AlamatGetKawasan = Drupal.settings.basePath + 'masterdata/kawasan/getajax';
  var IconAnak = '<i class="fa fa-user"></i>';
  var IconZon= '<i class="fa fa-map"></i>';
  $(".list-zon").hide();
  $(".list-zon-button").on("click", function (e){
    e.preventDefault();
    var split_id = $(this).attr("id").split("-");
    var id_list_zon = "list-zon-"+ split_id[2];
    if ($("#"+ id_list_zon).is(":visible")){
      $("#"+ id_list_zon).hide();
      $(this).html(IconZon + ' SHOW ZON');
      $(this).removeClass('btn-warning').addClass('btn-info');
    }else{
      $("#"+ id_list_zon).show();
      $(this).html(IconZon + ' HIDE ZON');
      $(this).removeClass('btn-info').addClass('btn-warning');
    }
  });
  $(".list-istri").hide();
  $(".show-istri").on("click", function (e){
    e.preventDefault();
    var split_id = $(this).attr("id").split("-");
    var id_list_istri = "list-istri-"+ split_id[2];
    if ($("#"+ id_list_istri).is(":visible")){
      $("#"+ id_list_istri).hide();
      $(this).html(IconAnak + ' SHOW ISTRI');
      $(this).removeClass('btn-warning').addClass('btn-success');
    }else{
      $("#"+ id_list_istri).show();
      $(this).html(IconAnak + ' HIDE ISTRI');
      $(this).removeClass('btn-success').addClass('btn-warning');
    }
  });
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
    'height': '25px',
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
    'onblur': 'ignore',
    'type': 'select',
    'submit': 'Simpan',
    'cancel': 'Batal'
  }).click(function () {
    $(this).find('select').chosen();
    $(this).find('button').button().css('font-size', '12px').css('margin-right', '4px').css('margin-top', '5px');
  });
  $('.edit-ayah').editable(AlamatUpdate, {
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
    'onblur': 'ignore',
    'type': 'select',
    'submit': 'Simpan',
    'cancel': 'Batal'
  }).click(function () {
    $(this).find('select').chosen();
    $(this).find('button').button().css('font-size', '12px').css('margin-right', '4px').css('margin-top', '5px');
  });
  $('.edit-ibu').editable(AlamatUpdate, {
    //json from php script
    'loadurl': AlamatGetStaffLelaki,
    'loaddata': function (value, settings) {
      return {jk: 1, chosen_input: 1};
    },
    //or data
    //data   : " {'0':'Vilnius', '1':'Klaipėda', '2':'Kaunas', '3':'Šiauliai', '4':'Palanga', 'selected':'0'}",
    'indicator': 'Saving...',
    'tooltip': 'Click to edit...',
    'style': "inherit",
    //Click outside editable area is ignored for select clicks
    'onblur': 'ignore',
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
    'style': 'inherit',
    //Click outside editable area is ignored for select clicks
    'onblur': 'ignore',
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
      $(".list-zon").hide();
      $(".list-zon-button").on("click", function (e){
        e.preventDefault();
        var split_id = $(this).attr("id").split("-");
        var id_list_zon = "list-zon-"+ split_id[2];
        if ($("#"+ id_list_zon).is(":visible")){
          $("#"+ id_list_zon).hide();
          $(this).html(IconZon + ' SHOW ZON');
          $(this).removeClass('btn-warning').addClass('btn-info');
        }else{
          $("#"+ id_list_zon).show();
          $(this).html(IconZon + ' HIDE ZON');
          $(this).removeClass('btn-info').addClass('btn-warning');
        }
      });
      $(".list-istri").hide();
      $(".show-istri").on("click", function (e){
        e.preventDefault();
        var split_id = $(this).attr("id").split("-");
        var id_list_istri = "list-istri-"+ split_id[2];
        if ($("#"+ id_list_istri).is(":visible")){
          $("#"+ id_list_istri).hide();
          $(this).html(IconAnak + ' SHOW ISTRI');
          $(this).removeClass('btn-warning').addClass('btn-success');
        }else{
          $("#"+ id_list_istri).show();
          $(this).html(IconAnak + ' HIDE ISTRI');
          $(this).removeClass('btn-success').addClass('btn-warning');
        }
      });
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
        'width': '200px',
        'height': '25px',
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
        'height': '25px',
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
        'style': 'inherit',
        'onblur': 'ignore',
        'type': 'select',
        'submit': 'Simpan',
        'cancel': 'Batal'
      }).click(function () {
        $(this).find('select').chosen();
        $(this).find('button').button().css('font-size', '12px').css('margin-right', '4px').css('margin-top', '5px');
      });
      $('.edit-ayah').editable('destroy');
      $('.edit-ayah').editable(AlamatUpdate, {
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
        'onblur': 'ignore',
        'type': 'select',
        'submit': 'Simpan',
        'cancel': 'Batal'
      }).click(function () {
        $(this).find('select').chosen();
        $(this).find('button').button().css('font-size', '12px').css('margin-right', '4px').css('margin-top', '5px');
      });
      $('.edit-ibu').editable(AlamatUpdate, {
        //json from php script
        'loadurl': AlamatGetStaffLelaki,
        'loaddata': function (value, settings) {
          return {jk: 1, chosen_input: 1};
        },
        //or data
        //data   : " {'0':'Vilnius', '1':'Klaipėda', '2':'Kaunas', '3':'Šiauliai', '4':'Palanga', 'selected':'0'}",
        'indicator': 'Saving...',
        'tooltip': 'Click to edit...',
        'style': "inherit",
        //Click outside editable area is ignored for select clicks
        'onblur': 'ignore',
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
        'height': '25px',
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
    }
  });
  var oTable = $('#datatable-1').dataTable();
  var idx = 0;
  $.each($('.btn-show-hide'), function(){
    var bVis = oTable.fnSettings().aoColumns[idx].bVisible;
    if (!bVis){
      $(this).addClass('btn-disabled');
    }
    idx++;
  });
  $('.btn-show-hide').on('click', function (e){
    e.preventDefault();
    var IdButton = $(this).attr('id');
    var SplitId = IdButton.split('-');
    var bVis = oTable.fnSettings().aoColumns[parseInt(SplitId[1])].bVisible;
    oTable.fnSetColumnVis( parseInt(SplitId[1]), bVis ? false : true );
    if (bVis){
      $(this).addClass('btn-disabled');
    }else{
      $(this).removeClass('btn-disabled');
    }
  });
});
