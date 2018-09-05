<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="utf-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
  <meta name="description" content="Sistema de monitoreo IoT de EcoCasa">
  <meta name="author" content="Emanuel Murillo">
  <link rel="icon" type="image/png" sizes="96x96" href="css/casa.png">
  <title>Monitoreo IoT</title>
  <!-- Bootstrap core CSS-->
  <link href="vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">
  <!-- Custom fonts for this template-->
  <link href="vendor/font-awesome/css/font-awesome.min.css" rel="stylesheet" type="text/css">
  <!-- Custom styles for this template-->
  <link href="css/sb-admin.css" rel="stylesheet">
</head>

<body class="fixed-nav sticky-footer bg-dark" id="page-top">
  <!-- Navigation-->
  <nav class="navbar navbar-expand-lg navbar-dark bg-dark fixed-top" id="mainNav">
    <a class="navbar-brand" href="index.html">Sistema de monitoreo IoT de EcoCasa</a>
    <button class="navbar-toggler navbar-toggler-right" type="button" data-toggle="collapse" data-target="#navbarResponsive" aria-controls="navbarResponsive" aria-expanded="false" aria-label="Toggle navigation">
      <span class="navbar-toggler-icon"></span>
    </button>
    <div class="collapse navbar-collapse" id="navbarResponsive">
      <ul class="navbar-nav navbar-sidenav" id="exampleAccordion">

           <li class="nav-item" data-toggle="tooltip" data-placement="right" title="Monitoreo">
          <a class="nav-link nav-link-collapse collapsed" data-toggle="collapse" href="#collapseMonitoreo" data-parent="#exampleAccordion">
            <i class="fa fa-fw fa-dashboard"></i>
            <span class="nav-link-text">Monitero</span>
          </a>
          <ul class="sidenav-second-level collapse" id="collapseMonitoreo">
            <li>
              <a href="index.html">Confort</a>
            </li>
            <li>
              <a href="panel.html">Panel Solar</a>
            </li>
            <li>
              <a href="aero.html">Aerogenerador</a>
            </li>
            <li>
              <a href="consumo.html">Consumo</a>
            </li>
            <li>
              <a href="bateria.html">Bateria</a>
            </li>
          
          </ul>
        </li>
        <li class="nav-item" data-toggle="tooltip" data-placement="right" title="Historial">
          <a class="nav-link nav-link-collapse collapsed" data-toggle="collapse" href="#collapseHistorial" data-parent="#exampleAccordion">
            <i class="fa fa-fw fa-area-chart"></i>
            <span class="nav-link-text">Historial</span>
          </a>
          <ul class="sidenav-second-level collapse" id="collapseHistorial">
            <li>
              <a href="historialTemp.php">Temperatura/humedad</a>
            </li>
            <li>
              <a href="historialPanel.php">Panel Solar</a>
            </li>
            <li>
              <a href="historialAero.php">Aerogenerador</a>
            </li>
            <li>
              <a href="historialConsumo.php">Consumo</a>
            </li>
            <li>
              <a href="historialBateria.php">Batería</a>
            </li>
            <li>
              <a href="historialLux.php">Iluminación</a>
            </li>
            <li>
              <a href="historialRad.php">Radiación</a>
            </li>
            <li>
              <a href="historialRad.php">Radiación</a>
            </li>
          </ul>
        </li>

        <li class="nav-item" data-toggle="tooltip" data-placement="right" title="Tables">
          <a class="nav-link" href="exportar.html">
            <i class="fa fa-fw fa-table"></i>
            <span class="nav-link-text">Exportar</span>
          </a>
        </li>
        
          </ul>
        </li>
      </ul>
      <ul class="navbar-nav sidenav-toggler">
        <li class="nav-item">
          <a class="nav-link text-center" id="sidenavToggler">
            <i class="fa fa-fw fa-angle-left"></i>
          </a>
        </li>
      </ul>
      <ul class="navbar-nav ml-auto">
        <li class="nav-item dropdown">
          
            <img src="css/NegativoITSON.png" alt="itson" height="65" width="175">

        </li>
      </ul>
     
    </div>
  </nav>
  <div class="content-wrapper">
    <div class="container-fluid">
      <!-- Breadcrumbs-->
      <ol class="breadcrumb">
        <li class="breadcrumb-item">
          <a href="#">Dashboard</a>
        </li>
        <li class="breadcrumb-item active">Historial</li>
      </ol>
      <div class="card mb-3">
          <div class="card-header">
            <i class="fa fa-area-chart"></i>Aerogenerador</div>
          <div class="card-body">
             <?php include'aero.php'; ?>
             <div id="vaero" style="height: 400px; min-width: 310px"></div>
             <br />
             <div id="iaero" style="height: 400px; min-width: 310px"></div>
             <br />
             <div id="waero" style="height: 400px; min-width: 310px"></div>
          </div>
        </div>
      </div>

    <!-- /.container-fluid-->
    <!-- /.content-wrapper-->
    <footer class="sticky-footer">
      <div class="container">
        <div class="text-center">
          <small>Copyright © Emanuel Murillo 2018</small>
        </div>
      </div>
    </footer>
    <!-- Scroll to Top Button-->
    <a class="scroll-to-top rounded" href="#page-top">
      <i class="fa fa-angle-up"></i>
    </a>
    <!-- Logout Modal-->
    <div class="modal fade" id="exampleModal" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
      <div class="modal-dialog" role="document">
        <div class="modal-content">
          <div class="modal-header">
            <h5 class="modal-title" id="exampleModalLabel">¿Cerrar sesión?</h5>
            <button class="close" type="button" data-dismiss="modal" aria-label="Close">
              <span aria-hidden="true">×</span>
            </button>
          </div>
          <div class="modal-body">Select "Logout" below if you are ready to end your current session.</div>
          <div class="modal-footer">
            <button class="btn btn-secondary" type="button" data-dismiss="modal">Cancel</button>
            <a class="btn btn-primary" href="login.html">Logout</a>
          </div>
        </div>
      </div>
    </div>
    
 
        <!-- Importo el archivo Javascript de Highcharts directamente desde su servidor -->
    <script src="http://code.highcharts.com/stock/highstock.js"></script>
    <script src="http://code.highcharts.com/modules/exporting.js"></script>
    
    <script src="http://code.highcharts.com/stock/highstock.js"></script>
    <script src="http://code.highcharts.com/modules/exporting.js"></script> 
    <!-- Bootstrap core JavaScript-->
    <script src="vendor/jquery/jquery.min.js"></script>
    <script src="vendor/bootstrap/js/bootstrap.bundle.min.js"></script>
    <!-- Core plugin JavaScript-->
    <script src="vendor/jquery-easing/jquery.easing.min.js"></script>
    <!-- Page level plugin JavaScript-->
    <script src="vendor/chart.js/Chart.min.js"></script>
    <!-- Custom scripts for all pages-->
    <script src="js/sb-admin.min.js"></script>
    <!-- Custom scripts for this page-->
    <script src="js/sb-admin-charts.min.js"></script>

    <script src="https://code.jquery.com/jquery.js"></script>
    <!-- Importo el archivo Javascript de Highcharts directamente desde su servidor -->
    
     <script>
    chartCPU1 = new Highcharts.StockChart({
        chart: {
            renderTo: 'vaero'
            //defaultSeriesType: 'spline'

        },
        rangeSelector: {
                    buttons: [{
                        type: 'hour',
                        count: 1,
                        text: '1h'
                    }, {
                        type: 'day',
                        count: 1,
                        text: '1D'
                    }, {
                        type: 'all',
                        count: 1,
                        text: 'All'
                    }],
                    selected: 1,
                    inputEnabled: false
                },
        title: {
            text: 'Voltaje del aerogenerador'
        },
        xAxis: {
            type: 'datetime'
            //tickPixelInterval: 150,
            //maxZoom: 20 * 1000
        },
        yAxis: {
            minPadding: 0.2,
            maxPadding: 0.2,
            title: {
                text: 'V',
                margin: 10
            }
        },
        series: [{
            name: 'valor',
            data: (function() {
                    // generate an array of random data
                    var data = [];
                    <?php
                        for($i = 0 ;$i<count($rawdata);$i++){
                    ?>
                    data.push([<?php echo $timeArray[$i];?>,<?php echo $vaeroArray[$i];?>]);
                    <?php } ?>
                    return data;
                })()
        }],
        credits: {
                enabled: false
        }
    });

    chartCPU2 = new Highcharts.StockChart({
        chart: {
            renderTo: 'iaero'
            //defaultSeriesType: 'spline'

        },
        rangeSelector: {
                    buttons: [{
                        type: 'hour',
                        count: 1,
                        text: '1h'
                    }, {
                        type: 'day',
                        count: 1,
                        text: '1D'
                    }, {
                        type: 'all',
                        count: 1,
                        text: 'All'
                    }],
                    selected: 1,
                    inputEnabled: false
                },
        title: {
            text: 'Corriene del Aerogenerador'
        },
        xAxis: {
            type: 'datetime'
            //tickPixelInterval: 150,
            //maxZoom: 20 * 1000
        },
        yAxis: {
            minPadding: 0.2,
            maxPadding: 0.2,
            title: {
                text: 'A',
                margin: 10
            }
        },
        series: [{
            name: 'valor',
            data: (function() {
                    // generate an array of random data
                    var data = [];
                    <?php
                        for($i = 0 ;$i<count($rawdata);$i++){
                    ?>
                    data.push([<?php echo $timeArray[$i];?>,<?php echo $iaeroArray[$i];?>]);
                    <?php } ?>
                    return data;
                })()
        }],
        credits: {
                enabled: false
        }
    });

     chartCPU3 = new Highcharts.StockChart({
        chart: {
            renderTo: 'waero'
            //defaultSeriesType: 'spline'

        },
        rangeSelector: {
                    buttons: [{
                        type: 'hour',
                        count: 1,
                        text: '1h'
                    }, {
                        type: 'day',
                        count: 1,
                        text: '1D'
                    }, {
                        type: 'all',
                        count: 1,
                        text: 'All'
                    }],
                    selected: 1,
                    inputEnabled: false
                },
        title: {
            text: 'Potencia del Aerogenerador'
        },
        xAxis: {
            type: 'datetime'
            //tickPixelInterval: 150,
            //maxZoom: 20 * 1000
        },
        yAxis: {
            minPadding: 0.2,
            maxPadding: 0.2,
            title: {
                text: 'W',
                margin: 10
            }
        },
        series: [{
            name: 'valor',
            data: (function() {
                    // generate an array of random data
                    var data = [];
                    <?php
                        for($i = 0 ;$i<count($rawdata);$i++){
                    ?>
                    data.push([<?php echo $timeArray[$i];?>,<?php echo $waeroArray[$i];?>]);
                    <?php } ?>
                    return data;
                })()
        }],
        credits: {
                enabled: false
        }
    }); 

  </script>  

</body>

</html>
