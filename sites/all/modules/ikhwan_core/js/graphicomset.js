jQuery(function ($) {
    $('#daily-report').on('click', function(){
        window.location = Drupal.settings.basePath + 'datapremis/graphomset/daily';
    });
    $('#weekly-report').on('click', function(){
        window.location = Drupal.settings.basePath + 'datapremis/graphomset/weekly';
    });
    $('#month-before').on('click', function(){
        var monthValue = $('#month_before').val();
        var splitMonth = monthValue.split('_');
        window.location = Drupal.settings.basePath + 'datapremis/graphomset/monthly/'+ splitMonth[0] +'/'+ splitMonth[1];
    });
    $('#curr-month').on('click', function(){
        var monthValue = $('#curr_month').val();
        var splitMonth = monthValue.split('_');
        window.location = Drupal.settings.basePath + 'datapremis/graphomset/monthly/'+ splitMonth[0] +'/'+ splitMonth[1];
    });
    $('#year-before').on('click', function(){
        window.location = Drupal.settings.basePath + 'datapremis/graphomset/yearly/'+ $('#year_before').val();
    });
    $('#curr-year').on('click', function(){
        window.location = Drupal.settings.basePath + 'datapremis/graphomset/yearly/'+ $('#curr_year').val();
    });
})