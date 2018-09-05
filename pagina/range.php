<?php
// Range.php
if(isset($_POST["From"], $_POST["to"]))
{
	$conn = mysqli_connect("localhost", "root", "password", "monitoreo");
	$result = '';
	$query = "SELECT * FROM sistema WHERE fecha BETWEEN '".$_POST["From"]."' AND '".$_POST["to"]."'";
	$sql = mysqli_query($conn, $query);
	$result .='
	<table class="table table-bordered">
<tr>
 								<th width="13%">fecha</th>  
                               <th width="15%">vac</th>  
                               <th width="5%">iac</th>  
                               <th width="5%">wac</th>  
                               <th width="5%">vpanel</th> 
                               <th width="5%">ipanel</th>  
                               <th width="5%">wpanel</th>  
                               <th width="5%">vaero</th>  
                               <th width="5%">iaero</th>  
                               <th width="5%">waero</th>
                               <th width="5%">temp_int</th>  
                               <th width="5%">temp_ext</th>
                               <th width="5%">hum_int</th>  
                               <th width="5%">hum_ext</th> 
                               <th width="5%">vbat</th>  
                               <th width="5%">tbat</th>
                               <th width="5%">lux</th>  
                               <th width="5%">tpanel</th>  
                               <th width="5%">tpanel</th>  
                               <th width="5%">i_panel</th> 
                               <th width="5%">rad</th>  
                             
</tr>';
	if(mysqli_num_rows($sql) > 0)
	{
		while($row = mysqli_fetch_array($sql))
		{
			$result .='
			<tr>
    						   <td>'.$row["fecha"].'</td>
    						   <td>'.$row["vac"].'</td>
    						   <td>'.$row["iac"].'</td>
    						   <td>'.$row["wac"].'</td>
    						    <td>'.$row["vpanel"].'</td>
    						   <td>'.$row["ipanel"].'</td>
    						   <td>'.$row["wpanel"].'</td>
    						    <td>'.$row["vaero"].'</td>
    						   <td>'.$row["iaero"].'</td>
    						   <td>'.$row["waero"].'</td>
    						   <td>'.$row["temp_int"].'</td>
    						   <td>'.$row["temp_ext"].'</td>
                   <td>'.$row["hum_int"].'</td>
                   <td>'.$row["hum_ext"].'</td>
                    <td>'.$row["vbat"].'</td>
                   <td>'.$row["tbat"].'</td>
                   <td>'.$row["lux"].'</td>
                   <td>'.$row["tpanel"].'</td>
                   <td>'.$row["i_panel"].'</td>
                   <td>'.$row["rad"].'</td>		  
    </tr>';
		}
	}
	else
	{
		$result .='
		<tr>
		<td colspan="5">No Purchased Item Found</td>
		</tr>';
	}
	$result .='</table>';
	echo $result;
}
?>