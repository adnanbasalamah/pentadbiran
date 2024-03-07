jQuery(function ($) {
  $(document).ready(function () {
    $('.nama-staff').autocomplete({
      source: Drupal.settings.basePath + 'masterdata/staff/getajax',
      select: function (event, ui) {
        var splitID = $(this).attr('id').split('-');
        $('#nidstaff-' + splitID[4] + '-' + splitID[5]).val(ui.item.id);
        if (ui.item.id_jawatan) {
          $('#' + splitID[0] + '-' + splitID[1] + '-' + splitID[2] + '-idjawatan-' + splitID[4] + '-' + splitID[5]).val(ui.item.id_jawatan);
        }
        if (ui.item.alamat) {
          $('#' + splitID[0] + '-' + splitID[1] + '-' + splitID[2] + '-alamat-' + splitID[4] + '-' + splitID[5]).val(ui.item.alamat);
        }
        if (ui.item.telepon) {
          $('#' + splitID[0] + '-' + splitID[1] + '-' + splitID[2] + '-nohp-' + splitID[4] + '-' + splitID[5]).val(ui.item.telepon);
        }
        if (ui.item.email) {
          $('#' + splitID[0] + '-' + splitID[1] + '-' + splitID[2] + '-email-' + splitID[4] + '-' + splitID[5]).val(ui.item.email);
        }
      }
    });
    $('.nama-staff').on('keyup', function (e) {
      e.preventDefault();
      if ($(this).val() === '') {
        var split_id = $(this).attr('id').split('-');
        var staff_nid_id = 'nidstaff-';
        var alamat_id = '';
        var telepon_id = '';
        var email_id = '';
        var jawatan_id = '';
        var namalengkap_id = $(this).attr('id');
        for (var i = 0; i < split_id.length; i++) {
          if (i === split_id.length - 2) {
            staff_nid_id += split_id[i];
          } else if (i === split_id.length - 1) {
            staff_nid_id += '-'+ split_id[i];
          }
          if (split_id[i] !== 'namalengkap') {
            if (i === 0) {
              alamat_id = split_id[i];
              telepon_id = split_id[i];
              email_id = split_id[i];
              jawatan_id = split_id[i];
            } else {
              alamat_id += '-' + split_id[i];
              telepon_id += '-' + split_id[i];
              email_id += '-' + split_id[i];
              jawatan_id += '-' + split_id[i];
            }
          } else {
            alamat_id += '-alamat';
            telepon_id += '-nohp';
            email_id += '-email';
            jawatan_id += '-idjawatan';
          }
        }
        $('#' + staff_nid_id).val('');
        $('#' + alamat_id).val('');
        $('#' + telepon_id).val('');
        $('#' + email_id).val('');
        $('#' + jawatan_id).val('');
        $('#' + namalengkap_id).val('');
      }
    });
    $('.checkdel').on('change', function (e) {
      var SplitId = $(this).attr('id').split('-');
      if (this.checked) {
        $('#delete-' + SplitId[1] + '-' + SplitId[2]).val(1);
      } else {
        $('#delete-' + SplitId[1] + '-' + SplitId[2]).val(0);
      }
    });
  });
});
