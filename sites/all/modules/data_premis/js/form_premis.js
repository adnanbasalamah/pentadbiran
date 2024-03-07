jQuery(function ($) {
    $('#edit-zone').on('change', function (e){
        e.preventDefault();
        var request = new Object;
        request.zone = $(this).val();
        var that = this;
        var AjaxAddress = Drupal.settings.basePath + 'masterdata/negeri/getajax';
        $.ajax({
            url: AjaxAddress,
            type: 'POST',
            data: request,
            dataType: 'json',
            success: function (data) {
                var returnData = eval(data);
                if (returnData){
                    $('#edit-idnegeri').select2('destroy');
                    $('#edit-idnegeri').empty();
                    for (key in returnData){
                        $('#edit-idnegeri').append('<option value="'+ key +'">'+ returnData[key] +'</option>');
                    }
                    $('#edit-idnegeri').select2();
                }else{
                    $('#edit-idnegeri').empty();
                }
            }
        });
    });
    $('#edit-zone').change();
})