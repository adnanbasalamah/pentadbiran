jQuery(function ($) {
    $('#year-before').on('click', function (){
        var yearBefore = $('#year_before').val();
        window.location = Drupal.settings.basePath + 'assignmentdashboard/-1/'+ yearBefore;
    });
    $('#month-before').on('click', function (){
        var monthBefore = $('#month_before').val().split('_');
        window.location = Drupal.settings.basePath + 'assignmentdashboard/'+ monthBefore[1] +'/'+ monthBefore[0];
    });
    $('#curr-month').on('click', function (){
        var currMonth = $('#curr_month').val().split('_');
        window.location = Drupal.settings.basePath + 'assignmentdashboard/'+ currMonth[1] +'/'+ currMonth[0];
    });
    if (Drupal.settings.chart_id.length > 0){
        var ChartIdAll = '';
        for (var i = 0;i < Drupal.settings.chart_id.length;i++){
            if (i == 0){
                ChartIdAll += '#'+ Drupal.settings.chart_id[i];
            }else{
                ChartIdAll += ',#'+ Drupal.settings.chart_id[i];
            }
        }
    }
    jQuery(document).on( 'shown.bs.tab', 'a[data-toggle="tab"]', function (e) { // on tab selection event
        jQuery(ChartIdAll).each(function() {
            var chart = jQuery(this).highcharts(); // target the chart itself
            chart.reflow() // reflow that chart
        });
    })
})