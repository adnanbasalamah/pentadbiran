jQuery(function ($) {
    $('#month-before').on('click', function (){
        var monthBefore = $('#month_before').val().split('_');
        window.location = Drupal.settings.basePath + 'cashflowdashboard/'+ monthBefore[1] +'/'+ monthBefore[0];
    });
    $('#curr-month').on('click', function (){
        var currMonth = $('#curr_month').val().split('_');
        window.location = Drupal.settings.basePath + 'cashflowdashboard/'+ currMonth[1] +'/'+ currMonth[0];
    });
})