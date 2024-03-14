<?php

function assignment_all_by_assignment_3d_column_chart($month = null, $year = null, $zone = null)
{
    $detect = mobile_detect_get_object();
    $assignmentTotal = '';
    $getDataZone = getZoneByCode(null, 'zone');
    $namaZone = array();
    if (count($getDataZone)) {
        for ($i = 0; $i < count($getDataZone); $i++) {
            $namaZone[$getDataZone[$i]->zone] = $getDataZone[$i]->nama;
        }
    }
    $strSQL = 'SELECT asdt.assignment_name, asz.zone, asz.assignment_id, ';
    $strSQL .= 'sum(asz.bank_in) AS total_bank_in FROM {zassigment_zone} AS asz ';
    $strSQL .= 'LEFT JOIN {zdata_assigment} asdt ON asz.assignment_id = asdt.id ';
    $strSQL .= 'WHERE asz.month = :month AND asz.year = :year ';
    $strSQL .= 'GROUP BY asz.zone,asz.assignment_id ORDER BY asz.zone,asz.assignment_id';
    $arrValue = array(':month' => $month, ':year' => $year);
    $arrAssignment = db_query($strSQL, $arrValue)->fetchAll();
    $assignmentData = array();
    $intDate = mktime(7, 0, 0, $month, 1, $year);
    $assignmentData['title'] = 'Assignment Zon ' . date('M Y', $intDate);
    $assignmentName = array();
    $seriesData = array();
    $zoneData = array();
    $totalAssignmentVal = 0;
    $totalByZone = array();
    for ($i = 0; $i < count($arrAssignment); $i++) {
        if ($i == 0){
            $zoneData[] = $arrAssignment[$i]->zone;
            $assignmentData['categories'][] = $namaZone[$arrAssignment[$i]->zone];
        }else{
            if (!in_array($arrAssignment[$i]->zone,$zoneData)){
                $zoneData[] = $arrAssignment[$i]->zone;
                $assignmentData['categories'][] = $namaZone[$arrAssignment[$i]->zone];
            }
        }
        $seriesData[$arrAssignment[$i]->assignment_id][] = (float)$arrAssignment[$i]->total_bank_in;
        $totalAssignmentVal = $totalAssignmentVal + $arrAssignment[$i]->total_bank_in;
        $assignmentName[$arrAssignment[$i]->assignment_id] = $arrAssignment[$i]->assignment_name;
        if (isset($totalByZone[$arrAssignment[$i]->zone])){
            $totalByZone[$arrAssignment[$i]->zone] = $totalByZone[$arrAssignment[$i]->zone] + $arrAssignment[$i]->total_bank_in;
        }else{
            $totalByZone[$arrAssignment[$i]->zone] = $arrAssignment[$i]->total_bank_in;
        }
    }
    $assignmentData['subtitle'] = 'Total Assignment : RM ' . number_format($totalAssignmentVal,0,'.',',');
    if (count($seriesData)){
        foreach ($seriesData as $assKey => $assData){
            $assignmentData['series'][] = (object)array(
                'name' => $assignmentName[$assKey],
                'data' => $assData,
            );
        }
    }
    $options = assignment_all_3d_column_stacked_chart_options($assignmentData);
    if (is_object($options)) {
        // Optionally add styles or any other valid attributes, suitable for
        // drupal_attributes().
        if ($detect->isMobile()){
            $attributes = array('style' => array('height: 450px;'));
        }else {
            $attributes = array('style' => array('height: 600px;'));
        }
        // Return block definition.
        $assignmentTotal = highcharts_render($options, $attributes);
    }
    return $assignmentTotal;
}

function assignment_all_3d_column_chart($month = null, $year = null, $zone = null, $SeriesColor = null)
{
    $detect = mobile_detect_get_object();
    $assignmentTotal = '';
    $getDataZone = getZoneByCode(null, 'zone');
    $namaZone = array();
    if (count($getDataZone)) {
        for ($i = 0; $i < count($getDataZone); $i++) {
            $namaZone[$getDataZone[$i]->zone] = $getDataZone[$i]->nama;
        }
    }
    $strSQL = 'SELECT asz.zone, ';
    $strSQL .= 'sum(asz.bank_in) AS total_bank_in FROM {zassigment_zone} AS asz ';
    $strSQL .= 'WHERE asz.month = :month AND asz.year = :year ';
    $strSQL .= 'GROUP BY asz.zone ORDER BY total_bank_in DESC';
    $arrValue = array(':month' => $month, ':year' => $year);
    $arrAssignment = db_query($strSQL, $arrValue)->fetchAll();
    $assignmentData = array();
    $intDate = mktime(7, 0, 0, $month, 1, $year);
    $assignmentData['title'] = 'Aliran Tunai Kemasukan Keseluruhan ' . date('M Y', $intDate);
    $assignmentName = array();
    $seriesData = array();
    $zoneData = array();
    $totalAssignmentVal = 0;
    $totalByZone = array();
    for ($i = 0; $i < count($arrAssignment); $i++) {
        if ($i == 0){
            $zoneData[] = $arrAssignment[$i]->zone;
            $assignmentData['categories'][] = $namaZone[$arrAssignment[$i]->zone];
        }else{
            if (!in_array($arrAssignment[$i]->zone,$zoneData)){
                $zoneData[] = $arrAssignment[$i]->zone;
                $assignmentData['categories'][] = $namaZone[$arrAssignment[$i]->zone];
            }
        }
        $seriesData['Aliran Tunai Kemasukan'][] = (float)$arrAssignment[$i]->total_bank_in;
        $totalAssignmentVal = $totalAssignmentVal + $arrAssignment[$i]->total_bank_in;
        //$assignmentName[$arrAssignment[$i]->assignment_id] = $arrAssignment[$i]->assignment_name;
        if (isset($totalByZone[$arrAssignment[$i]->zone])){
            $totalByZone[$arrAssignment[$i]->zone] = $totalByZone[$arrAssignment[$i]->zone] + $arrAssignment[$i]->total_bank_in;
        }else{
            $totalByZone[$arrAssignment[$i]->zone] = $arrAssignment[$i]->total_bank_in;
        }
    }
    $assignmentData['subtitle'] = 'Total Assignment : RM ' . number_format($totalAssignmentVal,0,'.',',');
    if (count($seriesData)){
        foreach ($seriesData as $assKey => $assData){
            $assignmentData['series'][] = (object)array(
                'name' => 'Aliran Tunai Kemasukan',
                'data' => $assData,
            );
        }
    }
    $SeriesColor = '#FFC300';
    $options = assignment_all_3d_column_stacked_chart_options($assignmentData, $SeriesColor);
    if (is_object($options)) {
        // Optionally add styles or any other valid attributes, suitable for
        // drupal_attributes().
        if ($detect->isMobile()){
            $attributes = array('style' => array('height: 450px;'));
        }else {
            $attributes = array('style' => array('height: 600px;'));
        }
        // Return block definition.
        $assignmentTotal = highcharts_render($options, $attributes);
    }
    return $assignmentTotal;
}

function assignment_total_3d_column_chart($assignmentId = null, $month = null, $year = null, $zone = null, $seriesColor = null, $limit_data = null, $use_title = true, $show_label = true, $order = 'DESC')
{
    $detect = mobile_detect_get_object();
    $assignmentTotal = '';
    if (!empty($assignmentId)) {
        $jenisAssignment = get_assignment_by_id($assignmentId);
        $getDataZone = getZoneByCode();
        $namaZone = array();
        if (count($getDataZone)) {
            for ($i = 0; $i < count($getDataZone); $i++) {
                $namaZone[$getDataZone[$i]->zone] = $getDataZone[$i]->nama;
            }
        }
        if ($month != -1) {
            $strSQL = 'SELECT sum(bank_in) AS total_bank_in, asz.zone FROM {zassigment_zone} AS asz ';
            $strSQL .= 'LEFT JOIN {zdatazone} AS zon ON zon.zone = asz.zone ';
            $strSQL .= 'WHERE assignment_id = :assignment_id AND month = :month AND year = :year AND zon.view_aliran = 1 ';
            $strSQL .= 'GROUP BY asz.zone ORDER BY total_bank_in ' . $order . ' ';
            if (!empty($limit_data)) {
                $strSQL .= 'LIMIT ' . $limit_data;
            }
            $arrValue = array(':assignment_id' => $assignmentId, ':month' => $month, ':year' => $year);
        }else{
            $strSQL = 'SELECT sum(bank_in) AS total_bank_in, asz.zone FROM {zassigment_zone} AS asz ';
            $strSQL .= 'LEFT JOIN {zdatazone} AS zon ON zon.zone = asz.zone ';
            $strSQL .= 'WHERE assignment_id = :assignment_id AND year = :year AND zon.view_aliran = 1 ';
            $strSQL .= 'GROUP BY asz.zone ORDER BY total_bank_in ' . $order . ' ';
            if (!empty($limit_data)) {
                $strSQL .= 'LIMIT ' . $limit_data;
            }
            $arrValue = array(':assignment_id' => $assignmentId, ':year' => $year);
        }
        $arrAssignment = db_query($strSQL, $arrValue)->fetchAll();
        $assignmentData = array();
        $seriesData = array();
        $intDate = mktime(7, 0, 0, $month, 1, $year);
        if ($use_title){
            if ($month != -1) {
                $assignmentData['title'] = $jenisAssignment->assignment_name . ' ' . date('M Y', $intDate);
            }else{
                $assignmentData['title'] = $jenisAssignment->assignment_name . ' ' . date('Y', $intDate);
            }
        }else {
            $assignmentData['title'] = '';
        }
        $totalAssignment = 0;
        for ($i = 0; $i < count($arrAssignment); $i++) {
            if (isset($namaZone[$arrAssignment[$i]->zone])) {
                $assignmentData['categories'][] = $namaZone[$arrAssignment[$i]->zone];
                $seriesData[] = (float)$arrAssignment[$i]->total_bank_in;
                $totalAssignment = $totalAssignment + $arrAssignment[$i]->total_bank_in;
            }
        }
        if ($use_title) {
            $assignmentData['subtitle'] = 'Total ' . $jenisAssignment->assignment_name . ' : RM ' . number_format($totalAssignment, 0, '.', ',');
        }else{
            $assignmentData['subtitle'] = '';
        }
        $assignmentData['series'] = (object)array(
            'name' => $jenisAssignment->assignment_name,
            'data' => $seriesData,
        );
        $options = assignment_harian_3d_column_chart_options($assignmentData, $seriesColor, $show_label);
        if (is_object($options)) {
            // Optionally add styles or any other valid attributes, suitable for
            // drupal_attributes().
            //$attributes = array('style' => array('height: 600px;'));
            if ($detect->isMobile()) {
                $attributes = array('style' => array('height: 450px;'));
            } else {
                if (!empty($limit_data)){
                    $attributes = array('style' => array('height: 500px;'));
                }else{
                    $attributes = array('style' => array('height: 650px;'));
                }
            }
            // Return block definition.
            $assignmentTotal = highcharts_render($options, $attributes);
            global $ChartId;
            $ChartId[] = $options->chart->renderTo;
        }
    }
    return $assignmentTotal;
}

function assignment_harian_3d_column_chart_options($assignmentData = null, $seriesColor = null, $show_label = true){
    $options = null;
    if (!empty($assignmentData) && isset($assignmentData['categories']) && !empty($assignmentData['categories'])) {
        $options = new stdClass();
        // Chart.
        $options->chart = (object)array(
            'renderTo' => 'container',
            'type' => 'column',
            'backgroundColor' => 'transparent',
            'marginTop' => '30',
            'options3d' => (object)array(
                'enabled' => TRUE,
                'alpha' => 15,
                'beta' => 15,
                'viewDistance' => 25,
                'depth' => 60,
            ),
        );
        // Title.
        $options->title = new stdClass();
        $options->title->text = strtoupper($assignmentData['title']);
        $options->title->style = (object)array('fontSize' => '32px');

        // Sub Title
        $options->subtitle = new stdClass();
        $options->subtitle->text = strtoupper($assignmentData['subtitle']);
        $options->subtitle->style = (object)array('fontSize' => '22px');
        // Plot options.
        $options->plotOptions = new stdClass();
        $options->plotOptions->column = (object)array(
            'depth' => 35,
        );
        if (!empty($seriesColor)){
            $options->plotOptions->series = (object)array(
                'color' => $seriesColor,
            );
        }
        //X-axis.
        $options->xAxis = new stdClass();
        $options->xAxis = (object)array(
            'categories' => $assignmentData['categories'],
        );

        //Y-axis
        $options->yAxis = new stdClass();
        $options->yAxis = (object)array(
            'title' => (object)array(
                'text' => 'Total Bank In',
             ),
        );

        // Legend.
        $options->legend = new stdClass();
        $options->legend = (object)array(
            'enabled' => false,
        );

        // Series.
        $options->series = array();
        $series = new StdClass();
        $series->name = $assignmentData['series']->name;
        $series->data = $assignmentData['series']->data;
        if ($show_label) {
            $series->dataLabels = (object)array(
                'enabled' => true,
                'rotation' => -90,
                'color' => '#FFFFFF',
                'align' => 'right',
                'format' => '{point.y:,.0f}',
                'y' => 10, // 10 pixels down from the top
                'style' => (object)array(
                    'fontSize' => '13px',
                    'fontFamily' => 'Verdana, sans-serif',
                ),
            );
        }
        $options->series[] = $series;
        // Disable credits.
        $options->credits = new stdClass();
        $options->credits->enabled = FALSE;
    }
    return $options;
}
function assignment_all_3d_column_stacked_chart_options($assignmentData = null, $SeriesColor = null){
    $options = null;
    if (!empty($assignmentData) && isset($assignmentData['categories']) && !empty($assignmentData['categories'])) {
        $options = new stdClass();
        // Chart.
        $options->chart = (object)array(
            'renderTo' => 'container',
            'type' => 'column',
            'backgroundColor' => 'transparent',
            'marginTop' => '10',
            'marginBottom' => '110',
            'options3d' => (object)array(
                'enabled' => TRUE,
                'alpha' => 15,
                'beta' => 15,
                'viewDistance' => 25,
                'depth' => 60,
            ),
        );
        // Title.
        $options->title = new stdClass();
        $options->title->text = strtoupper($assignmentData['title']);
        $options->title->style = (object)array('fontSize' => '32px');
        // Sub Title
        $options->subtitle = new stdClass();
        $options->subtitle->text = strtoupper($assignmentData['subtitle']);
        $options->subtitle->style = (object)array('fontSize' => '22px');
        // Plot options.
        $options->plotOptions = new stdClass();
        $options->plotOptions->column = (object)array(
            'depth' => 35,
            'stacking' => 'normal',
        );
        if (!empty($SeriesColor)){
            $options->plotOptions->series = (object)array(
                'color' => $SeriesColor,
            );
        }
        //X-axis.
        $options->xAxis = new stdClass();
        $options->xAxis = (object)array(
            'categories' => $assignmentData['categories'],
        );

        //Y-axis
        $options->yAxis = new stdClass();
        $options->yAxis = (object)array(
            'title' => (object)array(
                'text' => 'Total Bank In',
            ),
        );

        // Legend.
        $options->legend = new stdClass();
        $options->legend = (object)array(
            'align' => 'right',
            'x' => -30,
            'verticalAlign' => 'top',
            'y' => 75,
            'floating' => true,
            'backgroundColor' => 'transparent',
            'borderColor' => '#CCC',
            'borderWidth' => 1,
            'shadow' => false,
        );

        // Tooltip
        $options->tooltip = new stdClass();
        $options->tooltip = (object)array(
            'headerFormat' => '<b>{point.x}</b><br/>',
            'pointFormat' => '{series.name}: {point.y}<br/>Total Assignment: {point.stackTotal}',
        );

        // Series.
        $options->series = array();
        $options->series = $assignmentData['series'];

        // Disable credits.
        $options->credits = new stdClass();
        $options->credits->enabled = FALSE;
    }
    return $options;
}
function overhead_total_3d_column_chart($month = null, $year = null, $zone = null, $seriesColor = null)
{
    $ohTotal = '';
    $getDataZone = getZoneByCode();
    $namaZone = array();
    if (count($getDataZone)) {
        for ($i = 0; $i < count($getDataZone); $i++) {
            $namaZone[$getDataZone[$i]->zone] = $getDataZone[$i]->nama;
        }
    }
    $arrOverhead = array();
    if (function_exists('get_total_overhead_by_zone_converted')){
        $arrOverhead = get_total_overhead_by_zone_converted($month, $year, $zone);
    }
    $overheadData = array();
    $seriesData = array();
    $intDate = mktime(7, 0, 0, $month, 1, $year);
    $totalOverhead = 0;
    if (count($arrOverhead)) {
        foreach ($arrOverhead as $idxZone => $ohTotal) {
            $overheadData['categories'][] = $namaZone[$idxZone];
            $seriesData[] = (float)$ohTotal;
            $totalOverhead = $totalOverhead + (float)$ohTotal;
        }
    }
    $overheadData['title'] = 'OVERHEAD ZON ' . date('M Y', $intDate);
    $overheadData['subtitle'] = 'TOTAL OVERHEAD : RM. '.number_format($totalOverhead,0,',','.');
    $overheadData['series'] = (object)array(
        'name' => t('OVERHEAD'),
        'data' => $seriesData,
    );
    $options = overhead_total_3d_column_chart_options($overheadData, $seriesColor);
    if (is_object($options)) {
        // Optionally add styles or any other valid attributes, suitable for
        // drupal_attributes().
        $attributes = array('style' => array('height: 450px;'));

        // Return block definition.
        $overheadTotal = highcharts_render($options, $attributes);
    }
    return $overheadTotal;
}

function overhead_total_3d_column_chart_options($assignmentData = null, $seriesColor = null){
    $options = null;
    if (!empty($assignmentData)) {
        $options = new stdClass();
        // Chart.
        $options->chart = (object)array(
            'renderTo' => 'container',
            'type' => 'column',
            'backgroundColor' => 'transparent',
            'marginTop' => '30',
            'options3d' => (object)array(
                'enabled' => TRUE,
                'alpha' => 15,
                'beta' => 15,
                'viewDistance' => 25,
                'depth' => 60,
            ),
        );
        // Title.
        $options->title = new stdClass();
        $options->title->text = strtoupper($assignmentData['title']);
        $options->subtitle = new stdClass();
        $options->subtitle->text = strtoupper($assignmentData['subtitle']);
        // Plot options.
        $options->plotOptions = new stdClass();
        $options->plotOptions->column = (object)array(
            'depth' => 35,
        );
        if (!empty($seriesColor)){
            $options->plotOptions->series = (object)array(
                'color' => $seriesColor,
            );
        }
        //X-axis.
        $options->xAxis = new stdClass();
        $options->xAxis = (object)array(
            'categories' => $assignmentData['categories'],
        );

        //Y-axis
        $options->yAxis = new stdClass();
        $options->yAxis = (object)array(
            'title' => (object)array(
                'text' => 'Total OH ('.variable_get('google_currency_converter_to', '').')',
            ),
        );

        // Legend.
        $options->legend = new stdClass();
        $options->legend = (object)array(
            'enabled' => false,
        );

        // Series.
        $options->series = array();
        $series = new StdClass();
        $series->name = $assignmentData['series']->name;
        $series->data = $assignmentData['series']->data;
        /*$series->dataLabels = (object)array(
            'enabled' => true,
            'rotation' => -90,
            'color' => '#FFFFFF',
            'align' => 'right',
            'format' => '{point.y}',
            'y' => 10, // 10 pixels down from the top
            'style' => (object)array(
                'fontSize' => '13px',
                'fontFamily' => 'Verdana, sans-serif',
            ),
        );*/
        $options->series[] = $series;
        // Disable credits.
        $options->credits = new stdClass();
        $options->credits->enabled = FALSE;
    }
    return $options;
}

function cash_flow_zon_chart($month = null, $year = null, $zone = null){
    $detect = mobile_detect_get_object();
    //$assignmentTotal = '';
    $getDataZone = getZoneByCode();
    $namaZone = array();
    if (count($getDataZone)) {
        for ($i = 0; $i < count($getDataZone); $i++) {
            $namaZone[$getDataZone[$i]->zone] = $getDataZone[$i]->nama;
        }
    }
    /*$strSQL = 'SELECT COUNT(*) AS total_record ';
    $strSQL .= 'FROM {zdatazone_pemasukan_pengeluaran} ';
    $strSQL .= 'WHERE month = :month AND year = :year GROUP BY zone ';
    $TotalRec = db_query($strSQL, $arrValue)->fetchField();*/

    if ($month != -1) {
        $arrValue = array(':month' => $month, ':year' => $year);
        $strSQL = 'SELECT zone, SUM(jumlah_pemasukan) AS total_pemasukan, SUM(jumlah_pengeluaran) AS total_pengeluaran ';
        $strSQL .= 'FROM {zdatazone_pemasukan_pengeluaran} ';
        $strSQL .= 'WHERE month = :month AND year = :year GROUP BY zone ';
        $strSQL .= 'ORDER BY total_pemasukan DESC, total_pengeluaran DESC';
    }else{
        $arrValue = array(':year' => $year);
        $strSQL = 'SELECT zone, SUM(jumlah_pemasukan) AS total_pemasukan, SUM(jumlah_pengeluaran) AS total_pengeluaran ';
        $strSQL .= 'FROM {zdatazone_pemasukan_pengeluaran} ';
        $strSQL .= 'WHERE year = :year GROUP BY zone ';
        $strSQL .= 'ORDER BY total_pemasukan DESC, total_pengeluaran DESC';
    }
    $arrCashflow = db_query($strSQL, $arrValue)->fetchAll();
    $cashflowData = array();
    if ($month != -1) {
        $intDate = mktime(7, 0, 0, $month, 1, $year);
        $cashflowData['title'] = 'ALIRAN TUNAI ' . date('M Y', $intDate);
    }else{
        $intDate = mktime(7, 0, 0, 1, 1, $year);
        $cashflowData['title'] = 'ALIRAN TUNAI ' . date('Y', $intDate);
    }
    $seriesData = array();
    $zoneData = array();
    $totalPemasukan = 0;
    $totalPengeluaran = 0;
    for ($i = 0; $i < count($arrCashflow); $i++) {
        if ($i < 6 || $i > count($arrCashflow) - 7) {
            if ($i == 0) {
                $zoneData[] = $arrCashflow[$i]->zone;
                $cashflowData['categories'][] = $namaZone[$arrCashflow[$i]->zone];
            } else {
                if (!in_array($arrCashflow[$i]->zone, $zoneData)) {
                    $zoneData[] = $arrCashflow[$i]->zone;
                    $cashflowData['categories'][] = $namaZone[$arrCashflow[$i]->zone];
                }
            }
            $seriesData['Pemasukan'][] = (float)$arrCashflow[$i]->total_pemasukan;
            $seriesData['Pengeluaran'][] = (float)$arrCashflow[$i]->total_pengeluaran;
        }
        $totalPemasukan = $totalPemasukan + $arrCashflow[$i]->total_pemasukan;
        $totalPengeluaran = $totalPengeluaran + $arrCashflow[$i]->total_pengeluaran;
    }
    $totalBaki = $totalPemasukan - $totalPengeluaran;
    $cashflowData['subtitle'] = 'Total Pemasukan : RM ' . number_format($totalPemasukan,0,'.',',');
    $cashflowData['subtitle'] .= ' Total Pengeluaran : RM '.number_format($totalPengeluaran,0,'.',',');
    $cashflowData['subtitle'] .= ' Total Baki : RM '.number_format($totalBaki,0,'.',',');
    if (count($seriesData)){
        foreach ($seriesData as $assKey => $assData){
            $cashflowData['series'][] = (object)array(
                'name' => $assKey,
                'data' => $assData,
            );
        }
    }
    $options = cash_flow_zon_chart_options($cashflowData);
    if (is_object($options)) {
        // Optionally add styles or any other valid attributes, suitable for
        // drupal_attributes().
        if ($detect->isMobile()){
            $attributes = array('style' => array('height: 450px;'));
        }else {
            $attributes = array('style' => array('height: 600px;'));
        }
        // Return block definition.
        $cashFlowChart = highcharts_render($options, $attributes);
        global $ChartId;
        $ChartId[] = $options->chart->renderTo;
    }
    return $cashFlowChart;
}

function cash_flow_zon_chart_options($cashflowData = null, $seriesColor = null){
    $options = null;
    if (!empty($cashflowData) && isset($cashflowData['categories']) && !empty($cashflowData['categories'])) {
        $options = new stdClass();
        // Chart.
        $options->chart = (object)array(
            'renderTo' => 'container',
            'type' => 'column',
            'backgroundColor' => 'transparent',
            'options3d' => (object)array(
                'enabled' => TRUE,
                'alpha' => 15,
                'beta' => 15,
                'viewDistance' => 25,
                'depth' => 60,
            ),
        );
        // Title.
        $options->title = new stdClass();
        $options->title->text = strtoupper($cashflowData['title']);
        $options->title->style = (object)array('fontSize' => '32px');
        // Sub Title
        $options->subtitle = new stdClass();
        $options->subtitle->text = strtoupper($cashflowData['subtitle']);
        $options->subtitle->style = (object)array('fontSize' => '22px');
        //X-axis.
        $options->xAxis = new stdClass();
        $options->xAxis = (object)array(
            'categories' => $cashflowData['categories'],
        );

        //Y-axis
        $options->yAxis = new stdClass();
        $options->yAxis = (object)array(
            'title' => (object)array(
                'text' => 'Total',
            ),
        );

        // Legend.
        $options->legend = new stdClass();
        $options->legend = (object)array(
            'align' => 'center',
            'x' => -30,
            'verticalAlign' => 'top',
            'y' => 85,
            'floating' => true,
            'backgroundColor' => 'transparent',
            'borderColor' => '#CCC',
            'borderWidth' => 1,
            'shadow' => false,
        );

        // Tooltip
        $options->tooltip = new stdClass();
        $options->tooltip = (object)array(
            'headerFormat' => '<b>{point.x}</b><br/>',
            'pointFormat' => '{series.name}: {point.y}<br/>Total Baki: {point.stackTotal}',
        );

        // Series.
        $options->series = array();
        $options->series = $cashflowData['series'];
        // Disable credits.
        $options->credits = new stdClass();
        $options->credits->enabled = FALSE;
    }
    return $options;
}

function assignment_all_3d_pie_chart($month = null, $year = null, $zone = null){
    $detect = mobile_detect_get_object();
    $assignmentTotal = '';
    $strSQL = 'SELECT sum(asz.bank_in) AS total_bank_in, assignment_id FROM {zassigment_zone} AS asz ';
    $strSQL .= 'LEFT JOIN {zdata_assigment} AS dasg ON asz.assignment_id = dasg.id ';
    $strSQL .= 'WHERE asz.month = :month AND asz.year = :year ';
    $strSQL .= 'GROUP BY asz.assignment_id ORDER BY dasg.weight ASC';
    $arrValue = array(':month' => $month, ':year' => $year);
    $arrAssignment = db_query($strSQL, $arrValue)->fetchAll();
    $assignmentData = array();
    $intDate = mktime(7, 0, 0, $month, 1, $year);
    $assignmentData['title'] = 'Aliran Tunai Kemasukan Keseluruhan ' . date('M Y', $intDate);
    $assignmentList = get_assignment_by_id();
    $assignmentName = array();
    $assignmentCode = array();
    for ($i = 0;$i < count($assignmentList);$i++){
        $assignmentName[$assignmentList[$i]->id] = $assignmentList[$i]->assignment_name;
        $assignmentCode[$assignmentList[$i]->id] = $assignmentList[$i]->assignment_code;
    }
    $seriesData = array();
    $totalAssignmentVal = 0;
    $DetailTotal = '';
    for ($i = 0; $i < count($arrAssignment); $i++) {
        $SeriesValue = (float)$arrAssignment[$i]->total_bank_in;
        $seriesData[] = array($assignmentName[$arrAssignment[$i]->assignment_id], $SeriesValue);
        $totalAssignmentVal = $totalAssignmentVal + $arrAssignment[$i]->total_bank_in;
        $DetailTotal .= ', '.$assignmentName[$arrAssignment[$i]->assignment_id].' : <b>RM '.number_format($arrAssignment[$i]->total_bank_in,0,'.',',').'<b>';
    }
    $assignmentData['subtitle'] = 'Total Assignment : <b>RM ' . number_format($totalAssignmentVal,0,'.',',').'<b>'.$DetailTotal;
    if (count($seriesData)) {
        $assignmentData['series'][] = (object)array(
            'type' => 'pie',
            'name' => 'Aliran Tunai Kemasukan',
            'data' => $seriesData,
        );
    }
    $options = assignment_all_3d_pie_chart_options($assignmentData);
    if (is_object($options)) {
        // Optionally add styles or any other valid attributes, suitable for
        // drupal_attributes().
        if ($detect->isMobile()){
            $attributes = array('style' => array('height: 450px;'));
        }else {
            $attributes = array('style' => array('height: 600px;'));
        }
        // Return block definition.
        $assignmentTotal = highcharts_render($options, $attributes);
        global $ChartId;
        $ChartId[] = $options->chart->renderTo;
    }
    return $assignmentTotal;
}
function assignment_all_3d_pie_chart_options($assignmentData = null){
    $options = null;
    if (!empty($assignmentData)) {
        $options = new stdClass();
        // Chart.
        $options->chart = (object)array(
            'renderTo' => 'container',
            'type' => 'pie',
            'backgroundColor' => 'transparent',
            'options3d' => (object)array(
                'enabled' => TRUE,
                'alpha' => 45,
                'beta' => 0,
            ),
        );
        // Title.
        $options->title = new stdClass();
        $options->title->text = strtoupper($assignmentData['title']);
        $options->title->style = (object)array('fontSize' => '32px');
        // Sub Title
        $options->subtitle = new stdClass();
        $options->subtitle->text = strtoupper($assignmentData['subtitle']);
        $options->subtitle->style = (object)array('fontSize' => '22px');
        // Tooltip
        $options->tooltip = (object)array(
            'pointFormat' => '{point.y}',
        );

        // Plot options.
        $options->plotOptions = new stdClass();

        $options->plotOptions->pie = (object)array(
            'allowPointSelect' => true,
            'cursor' => 'pointer',
            'depth' => 35,
            'dataLabels' => (object)array(
                'enabled' => true,
                'format' => '{point.name}<br>{point.y:,.0f}',
            ),
        );

        // Series.
        $options->series = $assignmentData['series'];

        // Disable credits.
        $options->credits = new stdClass();
        $options->credits->enabled = FALSE;
    }
    return $options;
}
function compare_two_month_Assignment_chart($month = null, $year = null, $zone = null, $assignment_id = null, $use_title = true){
    global $totalCurr;
    global $totalBefore;
    if (!empty($assignment_id)){
        $AssignmentData = get_assignment_by_id($assignment_id);
    }
    $detect = mobile_detect_get_object();
    $assignmentTotal = '';
    if ($month != -1) {
        $strSQL = 'SELECT sum(asz.bank_in) AS total_bank_in FROM {zassigment_zone} AS asz ';
        $strSQL .= 'WHERE asz.month = :month AND asz.year = :year ';
        if (!empty($assignment_id)) {
            $strSQL .= 'AND asz.assignment_id = :assignment_id ';
            $arrValue = array(':month' => $month, ':year' => $year, ':assignment_id' => $assignment_id);
        } else {
            $arrValue = array(':month' => $month, ':year' => $year);
        }
    }else{
        $strSQL = 'SELECT sum(asz.bank_in) AS total_bank_in FROM {zassigment_zone} AS asz ';
        $strSQL .= 'WHERE asz.year = :year ';
        if (!empty($assignment_id)) {
            $strSQL .= 'AND asz.assignment_id = :assignment_id ';
            $arrValue = array(':year' => $year, ':assignment_id' => $assignment_id);
        } else {
            $arrValue = array(':year' => $year);
        }
    }
    $arrAssignment = db_query($strSQL, $arrValue)->fetchAll();
    $assignmentData = array();
    $intDate = mktime(7, 0, 0, $month, 1, $year);
    $intDateBefore = mktime(7, 0, 0, $month - 1, 1, $year);
    if ($use_title) {
        if ($month != -1) {
            $assignmentData['title'] = 'Aliran Tunai ' . date('M Y', $intDate) . ' berbanding ' . date('M Y', $intDateBefore);
        }else{
            $assignmentData['title'] = 'Aliran Tunai ' . date('Y', $intDate) . ' berbanding ' . date('Y', $intDateBefore);
        }
    }else{
        $assignmentData['title'] = '';
    }
    $seriesData = array();
    $DetailTotal = '';
    $Perubahan = 0;
    for ($i = 0; $i < count($arrAssignment); $i++) {
        $SeriesValue = (float)$arrAssignment[$i]->total_bank_in;
        if (!empty($assignment_id)){
            if ($month != -1) {
                $seriesData[] = array($AssignmentData->assignment_code . ' ' . date('M Y', $intDate), $SeriesValue);
            }else{
                $seriesData[] = array($AssignmentData->assignment_code . ' ' . date('Y', $intDate), $SeriesValue);
            }
        }else{
            if ($month != -1) {
                $seriesData[] = array('Total Assignment ' . date('M Y', $intDate), $SeriesValue);
            }else{
                $seriesData[] = array('Total Assignment ' . date('Y', $intDate), $SeriesValue);
            }
        }
        $Perubahan = $SeriesValue;
        $totalCurr['value'] = $SeriesValue;
        $totalCurr['date'] = date('M Y', $intDate);
        if (!empty($assignment_id)){
            if ($month != -1) {
                $DetailTotal .= $AssignmentData->assignment_code . ' ' . date('M Y', $intDate) . ' : <b>RM ' . number_format($arrAssignment[$i]->total_bank_in, 0, '.', ',') . '<b>';
            }else{
                $DetailTotal .= $AssignmentData->assignment_code . ' ' . date('Y', $intDate) . ' : <b>RM ' . number_format($arrAssignment[$i]->total_bank_in, 0, '.', ',') . '<b>';
            }
        }else {
            if ($month != -1) {
                $DetailTotal .= 'Total Assignment ' . date('M Y', $intDate) . ' : <b>RM ' . number_format($arrAssignment[$i]->total_bank_in, 0, '.', ',') . '<b>';
            }else{
                $DetailTotal .= 'Total Assignment ' . date('Y', $intDate) . ' : <b>RM ' . number_format($arrAssignment[$i]->total_bank_in, 0, '.', ',') . '<b>';
            }
        }
    }

    if ($month != -1) {
        //Calculate before
        $MonthBefore = $month - 1;
        $YearBefore = $year;
        if ($MonthBefore == 0) {
            $MonthBefore = 12;
            $YearBefore = $year - 1;
        }
        $strSQL = 'SELECT sum(asz.bank_in) AS total_bank_in FROM {zassigment_zone} AS asz ';
        $strSQL .= 'WHERE asz.month = :month AND asz.year = :year ';
        if (!empty($assignment_id)) {
            $strSQL .= 'AND asz.assignment_id = :assignment_id ';
            $arrValue = array(':month' => $MonthBefore, ':year' => $YearBefore, ':assignment_id' => $assignment_id);
        } else {
            $arrValue = array(':month' => $MonthBefore, ':year' => $YearBefore);
        }
        $arrAssignment = db_query($strSQL, $arrValue)->fetchAll();
        for ($i = 0; $i < count($arrAssignment); $i++) {
            $SeriesValue = (float)$arrAssignment[$i]->total_bank_in;
            if (!empty($assignment_id)) {
                $seriesData[] = array($AssignmentData->assignment_code . ' ' . date('M Y', $intDateBefore), $SeriesValue);
            } else {
                $seriesData[] = array('Total Assignment ' . date('M Y', $intDateBefore), $SeriesValue);
            }
            //$seriesData[] = array('Total Assignment '.date('M Y', $intDateBefore), $SeriesValue);
            $Perubahan = $Perubahan - $SeriesValue;
            $totalBefore['value'] = $SeriesValue;
            $totalBefore['date'] = date('M Y', $intDateBefore);
            if (!empty($assignment_id)) {
                $DetailTotal .= ', Total ' . $AssignmentData->assignment_name . ' ' . date('M Y', $intDateBefore) . ' : <b>RM ' . number_format($arrAssignment[$i]->total_bank_in, 0, '.', ',') . '<b>';
            } else {
                $DetailTotal .= ', Total Assignment ' . date('M Y', $intDateBefore) . ' : <b>RM ' . number_format($arrAssignment[$i]->total_bank_in, 0, '.', ',') . '<b>';
            }
        }
        if ($Perubahan < 0) {
            $DetailTotal .= ', Kekurangan Sebanyak : RM ' . number_format(abs($Perubahan), 0, '.', ',');
        } else {
            $DetailTotal .= ', Kelebihan Sebanyak : RM ' . number_format(abs($Perubahan), 0, '.', ',');
        }
        if ($use_title) {
            $assignmentData['subtitle'] = $DetailTotal;
        } else {
            $assignmentData['subtitle'] = '';
        }
    }else{
        $assignmentData['subtitle'] = '';
    }
    //Create Series Data

    if (count($seriesData)) {
        $assignmentData['series'][] = (object)array(
            'type' => 'pie',
            'name' => 'Perbandingan Aliran Tunai Kemasukan',
            'data' => $seriesData,
        );
    }
    $options = assignment_all_3d_pie_chart_options($assignmentData);
    if (is_object($options)) {
        // Optionally add styles or any other valid attributes, suitable for
        // drupal_attributes().
        if ($detect->isMobile()){
            $attributes = array('style' => array('height: 450px;'));
        }else {
            if ($use_title){
                $attributes = array('style' => array('height: 600px;'));
            }else{
                $attributes = array('style' => array('height: 500px;'));
            }
        }
        // Return block definition.
        $assignmentTotal = highcharts_render($options, $attributes);
        global $ChartId;
        $ChartId[] = $options->chart->renderTo;
    }
    return $assignmentTotal;
}
function compare_assignment_vs_cashflow_chart($month = null, $year = null, $zone = null){
    $detect = mobile_detect_get_object();
    $assignmentTotal = '';
    $strSQL = 'SELECT sum(asz.bank_in) AS total_bank_in FROM {zassigment_zone} AS asz ';
    $strSQL .= 'WHERE asz.month = :month AND asz.year = :year ';
    $arrValue = array(':month' => $month, ':year' => $year);
    $arrAssignment = db_query($strSQL, $arrValue)->fetchAll();
    $assignmentData = array();
    $intDate = mktime(7, 0, 0, $month, 1, $year);
    $intDateBefore = mktime(7, 0, 0, $month - 1, 1, $year);
    $assignmentData['title'] = 'Aliran Tunai ' . date('M Y', $intDate).' berbanding Keuntungan Perniagaan '.date('M Y', $intDate);
    $seriesData = array();
    $DetailTotal = '';
    $Perubahan = 0;
    for ($i = 0; $i < count($arrAssignment); $i++) {
        $SeriesValue = (float)$arrAssignment[$i]->total_bank_in;
        $seriesData[] = array('Total Assignment '.date('M Y', $intDate), $SeriesValue);
        $Perubahan = $SeriesValue;
        $DetailTotal .= 'Total Assignment '.date('M Y', $intDate).' : <b>RM '.number_format($arrAssignment[$i]->total_bank_in,0,'.',',').'<b>';
    }
    //Calculate before
    $strSQL = 'SELECT SUM(jumlah_pemasukan - jumlah_pengeluaran) AS keuntungan ';
    $strSQL .= 'FROM {zdatazone_pemasukan_pengeluaran} ';
    $strSQL .= 'WHERE month = :month AND year = :year ';
    $arrValue = array(':month' => $month, ':year' => $year);
    $arrCashflow = db_query($strSQL, $arrValue)->fetchAll();
    for ($i = 0; $i < count($arrCashflow); $i++) {
        $SeriesValue = (float)$arrCashflow[$i]->keuntungan;
        $seriesData[] = array('Keuntungan Perniagaan '.date('M Y', $intDateBefore), $SeriesValue);
        $Perubahan = $Perubahan - $SeriesValue;
        $DetailTotal .= ', Keuntungan Perniagaan '.date('M Y', $intDateBefore).' : <b>RM '.number_format($arrCashflow[$i]->keuntungan,0,'.',',').'<b>';
    }
    if ($Perubahan < 0 ){
        $DetailTotal .= ', Kekurangan Sebanyak : RM '.number_format(abs($Perubahan),0,'.',',');
    }else{
        $DetailTotal .= ', Kelebihan Sebanyak : RM '.number_format(abs($Perubahan),0,'.',',');
    }
    $assignmentData['subtitle'] = $DetailTotal;
    //Create Series Data

    if (count($seriesData)) {
        $assignmentData['series'][] = (object)array(
            'type' => 'pie',
            'name' => 'Perbandingan Aliran Tunai Kemasukan Dan Keuntungan Perniagaan',
            'data' => $seriesData,
        );
    }
    $options = assignment_all_3d_pie_chart_options($assignmentData);
    if (is_object($options)) {
        // Optionally add styles or any other valid attributes, suitable for
        // drupal_attributes().
        if ($detect->isMobile()){
            $attributes = array('style' => array('height: 450px;'));
        }else {
            $attributes = array('style' => array('height: 600px;'));
        }
        // Return block definition.
        $assignmentTotal = highcharts_render($options, $attributes);
        global $ChartId;
        $ChartId[] = $options->chart->renderTo;
    }
    return $assignmentTotal;
}

function assignment_all_3d_bar_chart($month = null, $year = null, $zone = null){
    //$detect = mobile_detect_get_object();
    $assignmentTotal = '';
    if ($month != -1) {
        $strSQL = 'SELECT sum(asz.bank_in) AS total_bank_in, assignment_id FROM {zassigment_zone} AS asz ';
        $strSQL .= 'LEFT JOIN {zdata_assigment} AS dasg ON asz.assignment_id = dasg.id ';
        $strSQL .= 'WHERE asz.month = :month AND asz.year = :year ';
        $strSQL .= 'GROUP BY asz.assignment_id ORDER BY dasg.weight ASC';
        $arrValue = array(':month' => $month, ':year' => $year);
        $arrAssignment = db_query($strSQL, $arrValue)->fetchAll();
    }else{
        $strSQL = 'SELECT sum(asz.bank_in) AS total_bank_in, assignment_id FROM {zassigment_zone} AS asz ';
        $strSQL .= 'LEFT JOIN {zdata_assigment} AS dasg ON asz.assignment_id = dasg.id ';
        $strSQL .= 'WHERE asz.year = :year ';
        $strSQL .= 'GROUP BY asz.assignment_id ORDER BY dasg.weight ASC';
        $arrValue = array(':year' => $year);
        $arrAssignment = db_query($strSQL, $arrValue)->fetchAll();
    }
    $assignmentData = array();
    //$intDate = mktime(7, 0, 0, $month, 1, $year);
    $assignmentData['title'] = '';
    $assignmentList = get_assignment_by_id();
    $assignmentName = array();
    $assignmentCode = array();
    for ($i = 0;$i < count($assignmentList);$i++){
        $assignmentName[$assignmentList[$i]->id] = $assignmentList[$i]->assignment_name;
        $assignmentCode[$assignmentList[$i]->id] = $assignmentList[$i]->assignment_code;
    }
    $seriesData = array();
    $totalAssignmentVal = 0;
    $DetailTotal = '';
    for ($i = 0; $i < count($arrAssignment); $i++) {
        $SeriesValue = (float)$arrAssignment[$i]->total_bank_in;
        $seriesData[] = array($assignmentName[$arrAssignment[$i]->assignment_id], $SeriesValue);
        $totalAssignmentVal = $totalAssignmentVal + $arrAssignment[$i]->total_bank_in;
        $DetailTotal .= ', '.$assignmentName[$arrAssignment[$i]->assignment_id].' : <b>RM '.number_format($arrAssignment[$i]->total_bank_in,0,'.',',').'<b>';
    }
    $assignmentData['subtitle'] = '';//'Total Assignment : <b>RM ' . number_format($totalAssignmentVal,0,'.',',').'<b>'.$DetailTotal;
    if (count($seriesData)) {
        $assignmentData['series'][] = (object)array(
            'type' => 'column',
            'name' => 'Aliran Tunai Kemasukan',
            'data' => $seriesData,
        );
    }
    $options = assignment_all_3d_bar_chart_options($assignmentData);
    if (is_object($options)) {
        // Optionally add styles or any other valid attributes, suitable for
        // drupal_attributes().
        $attributes = array('style' => array('height: 400px;'));
        // Return block definition.
        $assignmentTotal = highcharts_render($options, $attributes);
        global $ChartId;
        $ChartId[] = $options->chart->renderTo;
    }
    return $assignmentTotal;
}
function assignment_all_3d_bar_chart_options($assignmentData = null){
    $options = null;
    if (!empty($assignmentData)) {
        $options = new stdClass();
        // Chart.
        $options->chart = (object)array(
            'renderTo' => 'container',
            'type' => 'column',
            'backgroundColor' => 'transparent',
            'options3d' => (object)array(
                'enabled' => TRUE,
                'alpha' => 15,
                'beta' => 15,
                'depth' => 50,
                'viewDistance' => 25,
            ),
        );
        // Title.
        $options->title = new stdClass();
        $options->title->text = strtoupper($assignmentData['title']);
        //$options->title->style = (object)array('fontSize' => '32px');
        // Sub Title
        //$options->subtitle = new stdClass();
        //$options->subtitle->text = strtoupper($assignmentData['subtitle']);
        //$options->subtitle->style = (object)array('fontSize' => '22px');
        // Tooltip
        $options->xAxis = new stdClass();
        $options->xAxis->categories = array('PKH','MMI','DY');
        $options->xAxis->labels = (object) array(
            'skew3d' => true,
        );
        $options->tooltip = (object)array(
            'pointFormat' => '{point.y}',
        );

        // Plot options.
        $options->plotOptions = new stdClass();

        $options->plotOptions->pie = (object)array(
            'allowPointSelect' => true,
            'cursor' => 'pointer',
            'depth' => 35,
            'dataLabels' => (object)array(
                'enabled' => true,
                'format' => '{point.name}<br>{point.y:,.0f}',
            ),
        );

        // Series.
        $options->series = $assignmentData['series'];

        // Disable credits.
        $options->credits = new stdClass();
        $options->credits->enabled = FALSE;
    }
    return $options;
}

function create_ringkasan_kemasukan_table($month = null, $year = null, $zone = null){
    $strSQL2 = '';
    if ($month != -1) {
        $strSQL = 'SELECT sum(asz.bank_in) AS total_bank_in, assignment_id FROM {zassigment_zone} AS asz ';
        $strSQL .= 'LEFT JOIN {zdata_assigment} AS dasg ON asz.assignment_id = dasg.id ';
        $strSQL .= 'WHERE asz.month = :month AND asz.year = :year ';
        $strSQL .= 'GROUP BY asz.assignment_id ORDER BY dasg.weight ASC';
        $arrValue = array(':month' => $month, ':year' => $year);
        $strSQL2 = 'SELECT sum(asz.bank_in) AS total_bank_in, assignment_id FROM {zassigment_zone} AS asz ';
        $strSQL2 .= 'LEFT JOIN {zdata_assigment} AS dasg ON asz.assignment_id = dasg.id ';
        $strSQL2 .= 'WHERE asz.month = :month AND asz.year = :year ';
        $strSQL2 .= 'GROUP BY asz.assignment_id ORDER BY dasg.weight ASC';
        $arrValue2 = array(':month' => $month, ':year' => ($year - 1));
    }else{
        $strSQL = 'SELECT sum(asz.bank_in) AS total_bank_in, assignment_id FROM {zassigment_zone} AS asz ';
        $strSQL .= 'LEFT JOIN {zdata_assigment} AS dasg ON asz.assignment_id = dasg.id ';
        $strSQL .= 'WHERE asz.year = :year ';
        $strSQL .= 'GROUP BY asz.assignment_id ORDER BY dasg.weight ASC';
        $arrValue = array(':year' => $year);
    }
    $arrAssignment = db_query($strSQL, $arrValue)->fetchAll();
    if (!empty($strSQL2)) {
        $arrAssignment2 = db_query($strSQL2, $arrValue2)->fetchAll();
    }
    $assignmentList = get_assignment_by_id();
    $assignmentName = array();
    $assignmentCode = array();
    for ($i = 0;$i < count($assignmentList);$i++){
        $assignmentName[$assignmentList[$i]->id] = $assignmentList[$i]->assignment_name;
        $assignmentCode[$assignmentList[$i]->id] = $assignmentList[$i]->assignment_code;
    }
    $AssigmentData = array();
    $AssigmentTotal = 0;
    $AssigmentTotal2 = 0;
    for ($i = 0; $i < count($arrAssignment); $i++) {
        $AssigmentData[$assignmentName[$arrAssignment[$i]->assignment_id]] = array(number_format($arrAssignment[$i]->total_bank_in,0,'.',','), number_format($arrAssignment2[$i]->total_bank_in,0,'.',','));
        $AssigmentTotal = $AssigmentTotal + $arrAssignment[$i]->total_bank_in;
        $AssigmentTotal2 = $AssigmentTotal2 + $arrAssignment2[$i]->total_bank_in;
    }
    $AssigmentData['Total'] = array(number_format($AssigmentTotal,0,'.',','),number_format($AssigmentTotal2,0,'.',','));
    $Rows = array();
    foreach($AssigmentData as $AssName => $AssValue){
        $Rows[] = array($AssName, array('data' => $AssValue[0], 'class' => 'align-right'),array('data' => $AssValue[1], 'class' => 'align-right'));
    }
    $table_attributes = array('style' => 'font-size: 25px;');
    return theme('table', array('header' => create_ringkasan_header($month, $year), 'rows' => $Rows, 'attributes' => $table_attributes));
}

function create_ringkasan_header($month = null, $year = null){
    set_default_time_zone();
    $tableHeader = array();
    $tableHeader[] = t('KEMASUKAN');
    if ($month != -1) {
        $intDate = mktime(7, 0, 0, $month, 1, $year);
        $tableHeader[] = t('BULAN ' . strtoupper(date('M Y', $intDate)));
        $intDate = mktime(7, 0, 0, $month, 1, ($year - 1));
        $tableHeader[] = t('BULAN ' . strtoupper(date('M Y', $intDate)));
    }else{
        $intDate = mktime(7, 0, 0, 1, 1, $year);
        $tableHeader[] = t('TAHUN ' . strtoupper(date('Y', $intDate)));
    }
    return $tableHeader;
}

function create_pisb_table($month = null, $year = null, $zone = null){
    $AssigmentData = array();
    $AssigmentData['Jualan'] = 'RM 2,315,464.05';
    $AssigmentData['Belian'] = 'RM 1,463,520.90';
    $AssigmentData['Keuntungan'] = '<strong>RM 366,634.58</strong>';
    $Rows = array();
    foreach($AssigmentData as $AssName => $AssValue){
        $Rows[] = array($AssName, array('data' => $AssValue, 'class' => 'align-right'));
    }
    $table_attributes = array('style' => 'font-size: 25px;');
    $TableSum = theme('table', array('header' => create_pisb_header($month, $year), 'rows' => $Rows, 'attributes' => $table_attributes));
    $Keterangan = '<div style="font-size: 25px;">Keuntungan adalah berdasarkan jualan dan ianya bukan baki dari belian</div>';
    $TableSum .= $Keterangan;
    $AssigmentData = array();
    $AssigmentData['Ayam Segar'] = 'RM 78,900';
    $AssigmentData['Ikhwan Chocolate Dark (55gm)'] = 'RM 24,900';
    $AssigmentData['Udang'] = 'RM 24,700';
    $AssigmentData['Beras Faiza Emas (10kg)'] = 'RM 21,900';
    $AssigmentData['Kiwi Paste SP Neutral (45ml)'] = 'RM 1';
    $AssigmentData['Pantai Jintan Manis (10gm)'] = 'RM 0.9';
    $AssigmentData['Faiza Rempah Kari ikan (25gm)'] = 'RM 0.8';
    $AssigmentData['Indomie Soto Sup'] = 'RM 0.65';
    $Rows = array();
    foreach($AssigmentData as $AssName => $AssValue){
        $Rows[] = array($AssName, array('data' => $AssValue, 'class' => 'align-right'));
    }
    $TableItem = theme('table', array('header' => create_pisb_header_2(), 'rows' => $Rows, 'attributes' => $table_attributes));
    $TitleProductSales = '<h2 align="center">PISB Product Sales</h2>';
    return $TableSum.$TitleProductSales.$TableItem;
}

function create_pisb_header($month = null, $year = null){
    set_default_time_zone();
    $tableHeader = array();
    $tableHeader[] = t('KETERANGAN');
    if ($month != -1) {
        $intDate = mktime(7, 0, 0, $month, 1, $year);
        $tableHeader[] = t('BULAN ' . strtoupper(date('M Y', $intDate)));
    }else{
        $intDate = mktime(7, 0, 0, 1, 1, $year);
        $tableHeader[] = t('TAHUN ' . strtoupper(date('Y', $intDate)));
    }
    return $tableHeader;
}

function create_pisb_header_2(){
    set_default_time_zone();
    $tableHeader = array();
    $tableHeader[] = t('PRODUCT');
    $tableHeader[] = t('JUALAN');
    return $tableHeader;
}

function cashflow_sum_3d_bar_chart($month = null, $year = null, $zone = null){
    $assignmentTotal = '';
    if ($month != -1) {
        $strSQL = 'SELECT SUM(jumlah_pemasukan) AS total_pemasukan, SUM(jumlah_pengeluaran) AS total_pengeluaran ';
        $strSQL .= 'FROM {zdatazone_pemasukan_pengeluaran} ';
        $strSQL .= 'WHERE month = :month AND year = :year ';
        $strSQL .= 'ORDER BY total_pemasukan DESC, total_pengeluaran DESC';
        $arrValue = array(':month' => $month, ':year' => $year);
    }else{
        $strSQL = 'SELECT SUM(jumlah_pemasukan) AS total_pemasukan, SUM(jumlah_pengeluaran) AS total_pengeluaran ';
        $strSQL .= 'FROM {zdatazone_pemasukan_pengeluaran} ';
        $strSQL .= 'WHERE year = :year ';
        $strSQL .= 'ORDER BY total_pemasukan DESC, total_pengeluaran DESC';
        $arrValue = array(':year' => $year);
    }
    $arrCashflow = db_query($strSQL, $arrValue)->fetchAll();
    $assignmentData['title'] = '';
    for ($i = 0; $i < count($arrCashflow); $i++) {
        $Pendapatan = (float)$arrCashflow[$i]->total_pemasukan;
        $Pengeluaran = (float)$arrCashflow[$i]->total_pengeluaran;
        $seriesData[] = array('Pendapatan', $Pendapatan);
        $seriesData[] = array('Perbelanjaan', $Pengeluaran);
    }
    $assignmentData['subtitle'] = '';//'Total Assignment : <b>RM ' . number_format($totalAssignmentVal,0,'.',',').'<b>'.$DetailTotal;
    if (count($seriesData)) {
        $assignmentData['series'][] = (object)array(
            'type' => 'column',
            'name' => 'Pendapatan dan Perbelanjaan dari Zon-zon',
            'data' => $seriesData,
        );
    }
    $options = cashflow_sum_3d_bar_chart_options($assignmentData);
    if (is_object($options)) {
        // Optionally add styles or any other valid attributes, suitable for
        // drupal_attributes().
        $attributes = array('style' => array('height: 400px;'));
        // Return block definition.
        $assignmentTotal = highcharts_render($options, $attributes);
        global $ChartId;
        $ChartId[] = $options->chart->renderTo;
    }
    return $assignmentTotal;
}
function cashflow_sum_3d_bar_chart_options($assignmentData = null){
    $options = null;
    if (!empty($assignmentData)) {
        $options = new stdClass();
        // Chart.
        $options->chart = (object)array(
            'renderTo' => 'container',
            'type' => 'column',
            'backgroundColor' => 'transparent',
            'options3d' => (object)array(
                'enabled' => TRUE,
                'alpha' => 15,
                'beta' => 15,
                'depth' => 50,
                'viewDistance' => 25,
            ),
        );
        // Title.
        $options->title = new stdClass();
        $options->title->text = strtoupper($assignmentData['title']);
        //$options->title->style = (object)array('fontSize' => '32px');
        // Sub Title
        //$options->subtitle = new stdClass();
        //$options->subtitle->text = strtoupper($assignmentData['subtitle']);
        //$options->subtitle->style = (object)array('fontSize' => '22px');
        // Tooltip
        $options->xAxis = new stdClass();
        $options->xAxis->categories = array('Pendapatan','Perbelanjaan');
        $options->xAxis->labels = (object) array(
            'skew3d' => true,
        );
        $options->tooltip = (object)array(
            'pointFormat' => '{point.y}',
        );

        // Plot options.
        $options->plotOptions = new stdClass();

        $options->plotOptions->pie = (object)array(
            'allowPointSelect' => true,
            'cursor' => 'pointer',
            'depth' => 35,
            'dataLabels' => (object)array(
                'enabled' => true,
                'format' => '{point.name}<br>{point.y:,.0f}',
            ),
        );

        // Series.
        $options->series = $assignmentData['series'];

        // Disable credits.
        $options->credits = new stdClass();
        $options->credits->enabled = FALSE;
    }
    return $options;
}

function create_ringkasan_cashflow_table($month = null, $year = null, $zone = null){
    if ($month != -1) {
        $strSQL = 'SELECT SUM(jumlah_pemasukan) AS total_pemasukan, SUM(jumlah_pengeluaran) AS total_pengeluaran ';
        $strSQL .= 'FROM {zdatazone_pemasukan_pengeluaran} ';
        $strSQL .= 'WHERE month = :month AND year = :year ';
        $strSQL .= 'ORDER BY total_pemasukan DESC, total_pengeluaran DESC';
        $arrValue = array(':month' => $month, ':year' => $year);
    }else{
        $strSQL = 'SELECT SUM(jumlah_pemasukan) AS total_pemasukan, SUM(jumlah_pengeluaran) AS total_pengeluaran ';
        $strSQL .= 'FROM {zdatazone_pemasukan_pengeluaran} ';
        $strSQL .= 'WHERE year = :year ';
        $strSQL .= 'ORDER BY total_pemasukan DESC, total_pengeluaran DESC';
        $arrValue = array(':year' => $year);
    }
    $arrCashflow = db_query($strSQL, $arrValue)->fetchAll();
    $CashFlowData = array();
    $Baki = 0;
    for ($i = 0; $i < count($arrCashflow); $i++) {
        $CashFlowData['Pendapatan'] = number_format($arrCashflow[$i]->total_pemasukan,0,'.',',');
        $CashFlowData['Perbelanjaan'] = number_format($arrCashflow[$i]->total_pengeluaran,0,'.',',');
        $Baki = $Baki + $arrCashflow[$i]->total_pemasukan - $arrCashflow[$i]->total_pengeluaran;
    }
    $CashFlowData['Baki'] = number_format($Baki,0,'.',',');
    $Rows = array();
    foreach($CashFlowData as $AssName => $AssValue){
        $Rows[] = array($AssName, array('data' => $AssValue, 'class' => 'align-right'));
    }
    $table_attributes = array('style' => 'font-size: 25px;');
    return theme('table', array('header' => create_ringkasan_cf_header($month, $year), 'rows' => $Rows, 'attributes' => $table_attributes));
}

function create_ringkasan_cf_header($month = null, $year = null){
    set_default_time_zone();
    $tableHeader = array();
    $tableHeader[] = t('KETERANGAN');
    if ($month != -1) {
        $intDate = mktime(7, 0, 0, $month, 1, $year);
        $tableHeader[] = t('BULAN ' . strtoupper(date('M Y', $intDate)));
    }else{
        $intDate = mktime(7, 0, 0, 1, 1, $year);
        $tableHeader[] = t('TAHUN ' . strtoupper(date('Y', $intDate)));
    }
    return $tableHeader;
}

function pisb_sum_3d_bar_chart($month = null, $year = null, $zone = null){
    $assignmentTotal = '';
    $assignmentData['title'] = '';
    $Penjualan = 2315464.05;
    $Pembelian = 1463520.90;
    $seriesData[] = array('Penjualan', $Penjualan);
    $seriesData[] = array('PEmbelian', $Pembelian);
    $assignmentData['subtitle'] = '';//'Total Assignment : <b>RM ' . number_format($totalAssignmentVal,0,'.',',').'<b>'.$DetailTotal;
    if (count($seriesData)) {
        $assignmentData['series'][] = (object)array(
            'type' => 'column',
            'name' => 'Jualan dan Pembelian Pasaraya Ikhwan Sg Buloh (PISB)',
            'data' => $seriesData,
        );
    }
    $options = pisb_sum_3d_bar_chart_options($assignmentData);
    if (is_object($options)) {
        // Optionally add styles or any other valid attributes, suitable for
        // drupal_attributes().
        $attributes = array('style' => array('height: 400px;'));
        // Return block definition.
        $assignmentTotal = highcharts_render($options, $attributes);
        global $ChartId;
        $ChartId[] = $options->chart->renderTo;
    }
    return $assignmentTotal;
}

function pisb_sum_3d_bar_chart_options($assignmentData = null){
    $options = null;
    if (!empty($assignmentData)) {
        $options = new stdClass();
        // Chart.
        $options->chart = (object)array(
            'renderTo' => 'container',
            'type' => 'column',
            'backgroundColor' => 'transparent',
            'options3d' => (object)array(
                'enabled' => TRUE,
                'alpha' => 15,
                'beta' => 15,
                'depth' => 50,
                'viewDistance' => 25,
            ),
        );
        // Title.
        $options->title = new stdClass();
        $options->title->text = strtoupper($assignmentData['title']);
        //$options->title->style = (object)array('fontSize' => '32px');
        // Sub Title
        //$options->subtitle = new stdClass();
        //$options->subtitle->text = strtoupper($assignmentData['subtitle']);
        //$options->subtitle->style = (object)array('fontSize' => '22px');
        // Tooltip
        $options->xAxis = new stdClass();
        $options->xAxis->categories = array('Penjualan','Pembelian');
        $options->xAxis->labels = (object) array(
            'skew3d' => true,
        );
        $options->tooltip = (object)array(
            'pointFormat' => '{point.y}',
        );

        // Plot options.
        $options->plotOptions = new stdClass();

        $options->plotOptions->pie = (object)array(
            'allowPointSelect' => true,
            'cursor' => 'pointer',
            'depth' => 35,
            'dataLabels' => (object)array(
                'enabled' => true,
                'format' => '{point.name}<br>{point.y:,.0f}',
            ),
        );

        // Series.
        $options->series = $assignmentData['series'];

        // Disable credits.
        $options->credits = new stdClass();
        $options->credits->enabled = FALSE;
    }
    return $options;
}

function create_ringkasan_pisbsum_table($month = null, $year = null, $zone = null){
    $CashFlowData = array();
    $Penjualan = 2315464.05;
    $Pembelian = 1463520.90;
    $Margin = 366634.58;
    $CashFlowData['Penjualan'] = number_format($Penjualan,0,'.',',');
    $CashFlowData['Pembelian'] = number_format($Pembelian,0,'.',',');
    $CashFlowData['Margin'] = number_format($Margin,0,'.',',');
    $Rows = array();
    foreach($CashFlowData as $AssName => $AssValue){
        $Rows[] = array($AssName, array('data' => $AssValue, 'class' => 'align-right'));
    }
    $table_attributes = array('style' => 'font-size: 25px;');
    return theme('table', array('header' => create_ringkasan_pisbsum_header($month, $year), 'rows' => $Rows, 'attributes' => $table_attributes));
}

function create_ringkasan_pisbsum_header($month = null, $year = null){
    set_default_time_zone();
    $tableHeader = array();
    $tableHeader[] = t('KETERANGAN');
    if ($month != -1) {
        $intDate = mktime(7, 0, 0, $month, 1, $year);
        $tableHeader[] = t('BULAN ' . strtoupper(date('M Y', $intDate)));
    }else{
        $intDate = mktime(7, 0, 0, 1, 1, $year);
        $tableHeader[] = t('TAHUN ' . strtoupper(date('Y', $intDate)));
    }
    return $tableHeader;
}

function cash_flow_pisb_chart($month = null, $year = null){
    $detect = mobile_detect_get_object();
    //$assignmentTotal = '';

    $ArrPenjualan = get_pisb_data($month, $year, 'total');
    $ArrModal = get_pisb_data($month, $year, 'total_modal');
    $cashflowData = array();
    if ($month != -1) {
        $intDate = mktime(7, 0, 0, $month, 1, $year);
        $cashflowData['title'] = 'SALES & MARGIN ' . date('M Y', $intDate);
    }else{
        $intDate = mktime(7, 0, 0, 1, 1, $year);
        $cashflowData['title'] = 'SALES & MARGIN ' . date('Y', $intDate);
    }
    $seriesData = array();
    $zoneData = array();
    $totalSales = 0;
    $totalModal = 0;
    foreach($ArrPenjualan as $IdxDate => $Sales){
        $cashflowData['categories'][] = $IdxDate;
        $seriesData['Sales'][] = (float)$Sales;
        $seriesData['Margin'][] = (float)$ArrModal[$IdxDate];
        $totalSales = $totalSales + $Sales;
        $totalModal = $totalModal + $ArrModal[$IdxDate];
    }
    $totalBaki = $totalSales - $totalModal;
    $cashflowData['subtitle'] = 'Total Sales : RM ' . number_format($totalSales,0,'.',',');
    $cashflowData['subtitle'] .= ' Total Modal : RM '.number_format($totalModal,0,'.',',');
    $cashflowData['subtitle'] .= ' Total Margin : RM '.number_format($totalBaki,0,'.',',');
    if (count($seriesData)){
        foreach ($seriesData as $assKey => $assData){
            $cashflowData['series'][] = (object)array(
                'name' => $assKey,
                'data' => $assData,
            );
        }
    }
    $options = cash_flow_pisb_chart_options($cashflowData);
    if (is_object($options)) {
        // Optionally add styles or any other valid attributes, suitable for
        // drupal_attributes().
        if ($detect->isMobile()){
            $attributes = array('style' => array('height: 450px;'));
        }else {
            $attributes = array('style' => array('height: 600px;'));
        }
        // Return block definition.
        $cashFlowChart = highcharts_render($options, $attributes);
        global $ChartId;
        $ChartId[] = $options->chart->renderTo;
    }
    return $cashFlowChart;
}

function cash_flow_pisb_chart_options($cashflowData = null, $seriesColor = null){
    $options = null;
    if (!empty($cashflowData) && isset($cashflowData['categories']) && !empty($cashflowData['categories'])) {
        $options = new stdClass();
        // Chart.
        $options->chart = (object)array(
            'renderTo' => 'container',
            'type' => 'column',
            'backgroundColor' => 'transparent',
            'options3d' => (object)array(
                'enabled' => TRUE,
                'alpha' => 15,
                'beta' => 15,
                'viewDistance' => 25,
                'depth' => 60,
            ),
        );
        // Title.
        $options->title = new stdClass();
        $options->title->text = strtoupper($cashflowData['title']);
        $options->title->style = (object)array('fontSize' => '32px');
        // Sub Title
        $options->subtitle = new stdClass();
        $options->subtitle->text = strtoupper($cashflowData['subtitle']);
        $options->subtitle->style = (object)array('fontSize' => '22px');
        //X-axis.
        $options->xAxis = new stdClass();
        $options->xAxis = (object)array(
            'categories' => $cashflowData['categories'],
        );

        //Y-axis
        $options->yAxis = new stdClass();
        $options->yAxis = (object)array(
            'title' => (object)array(
                'text' => 'Total',
            ),
        );

        // Legend.
        $options->legend = new stdClass();
        $options->legend = (object)array(
            'align' => 'center',
            'x' => -30,
            'verticalAlign' => 'top',
            'y' => 85,
            'floating' => true,
            'backgroundColor' => 'transparent',
            'borderColor' => '#CCC',
            'borderWidth' => 1,
            'shadow' => false,
        );

        // Tooltip
        $options->tooltip = new stdClass();
        $options->tooltip = (object)array(
            'headerFormat' => '<b>{point.x}</b><br/>',
            'pointFormat' => '{series.name}: {point.y}<br/>Total Baki: {point.stackTotal}',
        );

        // Series.
        $options->series = array();
        $options->series = $cashflowData['series'];
        // Disable credits.
        $options->credits = new stdClass();
        $options->credits->enabled = FALSE;
    }
    return $options;
}

function dashboard_pentadbiran(){
  $chart = array(
    '#type' => 'chart',
    '#chart_type' => 'line',
    '#chart_library' => 'highcharts', // Allowed values: 'google' or 'highcharts'
    '#title' => t('Simple Column Chart'),
  );
  $chart['female'] = array(
    '#type' => 'chart_data',
    '#title' => t('Female'),
    '#data' => array(12, 22, 32),
    '#suffix' => 'lbs',
  );
  $chart['xaxis'] = array(
    '#type' => 'chart_xaxis',
    '#labels' => array('Jan', 'Feb', 'Mar'),
  );
  $example['chart'] = $chart;

  return drupal_render($example);
}
