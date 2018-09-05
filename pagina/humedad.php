  <?php
function conectarBD(){ 
            $server = "localhost";
            $usuario = "root";
            $pass = "password";
            $BD = "monitoreo";
            //variable que guarda la conexión de la base de datos
            $conexion = mysqli_connect($server, $usuario, $pass, $BD); 
            //Comprobamos si la conexión ha tenido exito
            if(!$conexion){ 
               echo 'Ha sucedido un error inexperado en la conexion de la base de datos<br>'; 
            } 
            //devolvemos el objeto de conexión para usarlo en las consultas  
            return $conexion; 
    }  
    /*Desconectar la conexion a la base de datos*/
    function desconectarBD($conexion){
            //Cierra la conexión y guarda el estado de la operación en una variable
            $close = mysqli_close($conexion); 
            //Comprobamos si se ha cerrado la conexión correctamente
            if(!$close){  
               echo 'Ha sucedido un error inexperado en la desconexion de la base de datos<br>'; 
            }    
            //devuelve el estado del cierre de conexión
            return $close;         
    }

    //Devuelve un array multidimensional con el resultado de la consulta
    function getArraySQL($sql){
        //Creamos la conexión
        $conexion = conectarBD();
        //generamos la consulta
        if(!$result = mysqli_query($conexion, $sql)) die();

        $rawdata = array();
        //guardamos en un array multidimensional todos los datos de la consulta
        $i=0;
        while($row = mysqli_fetch_array($result))
        {   
            //guardamos en rawdata todos los vectores/filas que nos devuelve la consulta
            $rawdata[$i] = $row;
            $i++;
        }
        //Cerramos la base de datos
        desconectarBD($conexion);
        //devolvemos rawdata
        return $rawdata;
    }
    //inserta en la base de datos un nuevo registro en la tabla usuarios
    
    $sql = "SELECT fecha,humedad FROM sistema;";
    $rawdata = getArraySQL($sql);
    //nos creamos dos arrays para almacenar el tiempo y el valor numérico
    $valoresArray;
    $timeArray;
    //en un bucle for obtenemos en cada iteración el valor númerico y 
    //el TIMESTAMP del tiempo y lo almacenamos en los arrays 
    for($i = 0 ;$i<count($rawdata);$i++){
        $valoresArray[$i]= $rawdata[$i][1];
        //OBTENEMOS EL TIMESTAMP
        $time= $rawdata[$i][0];
        $date = new DateTime($time);
        //ALMACENAMOS EL TIMESTAMP EN EL ARRAY
        $timeArray[$i] = $date->getTimestamp()*1000;
    }

?>