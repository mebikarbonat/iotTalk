<html>
<head>
<title>IOT Demo AI Week Talk</title>
<script src="//cdn.zingchart.com/zingchart.min.js"></script>
<meta http-equiv="refresh" content="5">
</head>
<body>
<h2>Kita plot value sensor</h2>
<div id="myChart"></div>

<a href="index.php">Kembali</a></br>

<?php

#ini_set('display_errors', '1');
#ini_set('display_startup_errors', '1');
#error_reporting(E_ALL);

//Muhammad Azizi Mohd Ariffin
//mazizi@fskm.uitm.edu.my

include 'ZC.php';
use ZingChart\PHPWrapper\ZC;

$host = "127.0.0.1";
$port = 3306;
$username = "iot";
$password = "iot123";
$db = "esp_data";

$myQuery  = "SELECT value1 AS 'Temperature', value2 AS 'Humidity' FROM SensorData";

$zc = new ZC("myChart");
$zc->connect($host,$port,$username,$password,$db);
$data = $zc->query($myQuery, false);
$zc->setSeriesData($data);
$zc->render();
$zc->closeConnection();

?>


</body>
</html>
