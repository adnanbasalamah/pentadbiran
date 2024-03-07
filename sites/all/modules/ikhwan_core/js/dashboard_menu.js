jQuery(function ($) {
    $('#assigment-chart').on('click', function (){
        window.location = Drupal.settings.basePath + 'assignmentdashboard/'+ Drupal.settings.month +'/'+ Drupal.settings.year;
    });
    $('#overhead-chart').on('click', function (){
        window.location = Drupal.settings.basePath + 'overheaddashboard/'+ Drupal.settings.month +'/'+ Drupal.settings.year;
    });
    $('#cashflow-chart').on('click', function (){
        window.location = Drupal.settings.basePath + 'cashflowdashboard/'+ Drupal.settings.month +'/'+ Drupal.settings.year;
    });
})