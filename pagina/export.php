 <?php
// Range.php
if(isset($_POST["export"]))
{
      $conn = mysqli_connect("localhost", "root", "password", "monitoreo");
      header('Content-Type: text/csv; charset=utf-8');  
      header('Content-Disposition: attachment; filename=data.csv');  
      $output = fopen("php://output", "w");  
      fputcsv($output, array('fecha', 'v_ac', 'i_ac', 'w_ac', 'v_panel', 'i_panel', 'w_panel', 'v_aero', 'i_aero', 'w_aero', 'temp_int', 'temp_ext', 'hum_int', 'hum_ext', 'v_bat', 't_bat', 'lux', 'tpanel', 'ipanel', 'rad'));  
      $query = "SELECT fecha, vac, iac, wac, vpanel, ipanel, wpanel, vaero, iaero, waero, temp_int, temp_ext, hum_int, hum_ext, vbat, tbat, lux, tpanel, i_panel, rad FROM sistema WHERE fecha BETWEEN '".$_POST["From"]."' AND '".$_POST["to"]."'";
      $result = mysqli_query($conn, $query);
     while($row = mysqli_fetch_assoc($result))  
      {  
           fputcsv($output, $row);  
      }  
      fclose($output); 
}
?> 


