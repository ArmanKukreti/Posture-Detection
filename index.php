<!DOCTYPE html>
<html><body>
<?php
 
$servername = "localhost";
$dbname = "id20887875_posturedetection";
$username = "id20887875_arman";
$password = "Manju@1210";
 
 
$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
 
$sql = "SELECT id, TopDistance, BottomDistance, SetDistance, Delay, reading_time FROM ESPData ORDER BY id DESC";
 
echo '<table cellspacing="5" cellpadding="5">
      <tr> 
        <td>ID</td> 
        <td>TopDistance</td> 
        <td>BottomDistance</td> 
        <td>SetDistance</td> 
        <td>Delay</td>
        <td>Timestamp</td> 
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_TopDistance = $row["TopDistance"];
        $row_BottomDistance = $row["BottomDistance"];
        $row_SetDistance = $row["SetDistance"];
        $row_Delay = $row["Delay"]; 
        $row_reading_time = $row["reading_time"];
        
      
        echo '<tr> 
                <td>' . $row_id . '</td> 
                <td>' . $row_TopDistance . '</td> 
                <td>' . $row_BottomDistance . '</td> 
                <td>' . $row_SetDistance . '</td> 
                <td>' . $row_Delay . '</td>
                <td>' . $row_reading_time . '</td> 
              </tr>';
    }
    $result->free();
}
 
$conn->close();
?> 
</table>
</body>
</html>