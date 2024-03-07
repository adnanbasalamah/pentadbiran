jQuery(function ($) {
    $('.edit-assignment').on('click', function (e){
        e.preventDefault();
        var splitID = $(this).attr('id').split('-');
        if (splitID.length > 0 && typeof splitID[2] != 'undefined'){
            window.location = Drupal.settings.basePath + 'masterdata/assignment/add/'+ splitID[2];
        }
    });
    $('#new-assignment').on('click', function (e){
        e.preventDefault();
        window.location = Drupal.settings.basePath + 'masterdata/assignment/add';
    });
})
