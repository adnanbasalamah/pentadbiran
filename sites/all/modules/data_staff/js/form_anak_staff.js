jQuery(function ($) {
    $(document).ready(function () {
        $('.tgl-lahir').datepicker({
            changeMonth: true,
            changeYear: true,
            dateFormat: 'yy-mm-dd',
            onSelect: function(date) {
                var splitID = $(this).attr('id').split('-');
                var SplitVal = date.split('-');
                var AjaxAddress = Drupal.settings.basePath + 'calculateage/'+ SplitVal[2] +'/'+ SplitVal[1] +'/'+ SplitVal[0];
                $.ajax({
                    url: AjaxAddress,
                    type: 'POST',
                    success: function (data) {
                        if (splitID[6] == 'new') {
                            $('#umur-' + splitID[splitID.length - 1]).html(data);
                        }else{
                            $('#umur-' + splitID[splitID.length - 2]).html(data);
                        }
                    }
                });
            },
        });
        $('.nama-staff').autocomplete({
            source: Drupal.settings.basePath + 'masterdata/staff/getajax',
            select: function (event, ui) {
                var splitID = $(this).attr('id').split('-');
                if (splitID[5] == 'new'){
                    $('#nidstaff-' + splitID[splitID.length - 1]).val(ui.item.id);
                    if (ui.item.nama_hijrah){
                        $('#'+ splitID[0] +'-'+ splitID[1] +'-'+ splitID[2] +'-'+ splitID[3] +'-nama-hijrah-'+ splitID[5] +'-'+ splitID[6]).val(ui.item.nama_hijrah);
                    }
                    if (ui.item.jenis_kelamin){
                        $('#'+ splitID[0] +'-'+ splitID[1] +'-'+ splitID[2] +'-'+ splitID[3] +'-jantina-'+ splitID[5] +'-'+ splitID[6]).val(ui.item.jenis_kelamin);
                        $('#'+ splitID[0] +'-'+ splitID[1] +'-'+ splitID[2] +'-'+ splitID[3] +'-jantina-'+ splitID[5] +'-'+ splitID[6]).select2('destroy');
                        $('#'+ splitID[0] +'-'+ splitID[1] +'-'+ splitID[2] +'-'+ splitID[3] +'-jantina-'+ splitID[5] +'-'+ splitID[6]).select2();

                    }
                    if (ui.item.tanggal_lahir){
                        $('#'+ splitID[0] +'-'+ splitID[1] +'-'+ splitID[2] +'-'+ splitID[3] +'-tarikh-lahir-'+ splitID[5] +'-'+ splitID[6]).val(ui.item.tanggal_lahir);
                        var SplitVal = ui.item.tanggal_lahir.split('-');
                        var AjaxAddress = Drupal.settings.basePath + 'calculateage/'+ SplitVal[2] +'/'+ SplitVal[1] +'/'+ SplitVal[0];
                        $.ajax({
                            url: AjaxAddress,
                            type: 'POST',
                            success: function (data) {
                                $('#umur-'+ splitID[splitID.length - 1]).html(data);
                            }
                        });
                    }
                    if (ui.item.tempat_lahir){
                        $('#'+ splitID[0] +'-'+ splitID[1] +'-'+ splitID[2] +'-'+ splitID[3] +'-tempat-lahir-'+ splitID[5] +'-'+ splitID[6]).val(ui.item.tempat_lahir);
                    }
                }else {
                    $('#nidstaff-' + splitID[splitID.length - 2]).val(ui.item.id);
                    if (ui.item.nama_hijrah){
                        $('#'+ splitID[0] +'-'+ splitID[1] +'-'+ splitID[2] +'-'+ splitID[3] +'-nama-hijrah-'+ splitID[5] +'-'+ splitID[6]).val(ui.item.nama_hijrah);
                    }
                    if (ui.item.jenis_kelamin){
                        $('#'+ splitID[0] +'-'+ splitID[1] +'-'+ splitID[2] +'-'+ splitID[3] +'-jantina-'+ splitID[5] +'-'+ splitID[6]).val(ui.item.jenis_kelamin);
                    }
                    if (ui.item.tanggal_lahir){
                        $('#'+ splitID[0] +'-'+ splitID[1] +'-'+ splitID[2] +'-'+ splitID[4] +'-tarikh-lahir-'+ splitID[5] +'-'+ splitID[6]).val(ui.item.tanggal_lahir);
                        var SplitVal = ui.item.tanggal_lahir.split('-');
                        var AjaxAddress = Drupal.settings.basePath + 'calculateage/'+ SplitVal[2] +'/'+ SplitVal[1] +'/'+ SplitVal[0];
                        $.ajax({
                            url: AjaxAddress,
                            type: 'POST',
                            success: function (data) {
                                $('#umur-'+ splitID[splitID.length - 2]).html(data);
                            }
                        });
                    }
                    if (ui.item.tempat_lahir){
                        $('#'+ splitID[0] +'-'+ splitID[1] +'-'+ splitID[2] +'-'+ splitID[4] +'-tempat-lahir-'+ splitID[4] +'-'+ splitID[5] +'-'+ splitID[6]).val(ui.item.tempat_lahir);
                    }
                }
            }
        });
        $('.checkdel').on('change', function(e){
            var SplitId = $(this).attr('id').split('-');
            if (this.checked){
                $('#delete-'+ SplitId[1]).val(1);
            }else{
                $('#delete-'+ SplitId[1]).val(0);
            }
        });
    });
})
