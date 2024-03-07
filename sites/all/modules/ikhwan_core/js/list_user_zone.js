function arrayCompare(a1, a2) {
    if (a1.length != a2.length) return false;
    var length = a2.length;
    for (var i = 0; i < length; i++) {
        if (a1[i] !== a2[i]) return false;
    }
    return true;
}

function inArray(needle, haystack) {
    var length = haystack.length;
    for(var i = 0; i < length; i++) {
        if(typeof haystack[i] == 'object') {
            if(arrayCompare(haystack[i], needle)) return true;
        } else {
            if(haystack[i] == needle) return true;
        }
    }
    return false;
}
jQuery(function ($) {
    var userPremis = new Array;
    $('.select-premis').each(function(){
        userPremis[$(this).attr('id')] = new Array;
        userPremis[$(this).attr('id')].push($(this).val());
    });
    console.log(userPremis);
    $('.select-zone').on('change', function (e){
        e.preventDefault();
        var splitID = $(this).attr('id').split('-');
        console.log(splitID);
        var premisInputID = '';
        for (var i = 0;i < splitID.length;i++){
            if (i == 0){
                premisInputID = splitID[i];
            }
            if (i != 4 && i != 0){
                premisInputID += '-'+ splitID[i];
            }else if(i == 4){
                premisInputID += '-premis';
            }
        }
        var request = new Object;
        request.id_zone = $(this).val();
        var that = this;
        var AjaxAddress = Drupal.settings.basePath + 'masterdata/premis/getajax';
        $.ajax({
            url: AjaxAddress,
            type: 'POST',
            data: request,
            dataType: 'json',
            success: function (data) {
                var returnData = eval(data);
                if (returnData){
                    $('#'+ premisInputID).select2('destroy');
                    $('#'+ premisInputID).empty();
                    for (key in returnData){
                        if (userPremis[premisInputID][0]){
                            if (inArray(key,userPremis[premisInputID][0])){
                                $('#'+ premisInputID).append('<option value="'+ key +'" selected>'+ returnData[key] +'</option>');
                            }else{
                                $('#'+ premisInputID).append('<option value="'+ key +'">'+ returnData[key] +'</option>');
                            }
                        }else{
                            $('#'+ premisInputID).append('<option value="'+ key +'">'+ returnData[key] +'</option>');
                        }
                    }
                    $('#'+ premisInputID).select2();
                }else{
                    $('#'+ premisInputID).empty();
                }
            }
        });
    });
    $('.select-zone').change();
})
