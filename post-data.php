<?php
 
$servername = "localhost";
$dbname = "id20887875_posturedetection";
$username = "id20887875_arman";
$password = "Manju@1210";
 
$api_key_value = "54321";
$api_key= $TopDistance = $BottomDistance = $SetDistance = $Delay = "";
 
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        $TopDistance = test_input($_POST["TopDistance"]);
        $BottomDistance = test_input($_POST["BottomDistance"]);
        $SetDistance = test_input($_POST["SetDistance"]);
        $Delay = test_input($_POST["Delay"]);
        
        
        $conn = new mysqli($servername, $username, $password, $dbname);
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        
        $sql = "INSERT INTO ESPData (TopDistance, BottomDistance, SetDistance, Delay)
        VALUES ('" . $TopDistance . "', '" . $BottomDistance . "', '" . $SetDistance . "', '" . $Delay. "')";
        
        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else {
        echo "Wrong API Key";
    }
 
}
else {
    echo "No data posted HTTP POST.";
}
 
function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}