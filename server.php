<?php 
include("connection.php");
 ?>
<table class="table">
			<thead>
			    <th>ID</th>
				<th>TopDistance</th>
				<th>BottomDistance</th>
				<th>SetDistance</th>
				<th>Delay</th>
				<th>Timestamp</th>
			</thead>
<?php 
	$query = mysqli_query($db, "SELECT * FROM ESPDATA");
	if ($result = $conn->query($query)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_TopDistance = $row["TopDistance"];
        $row_BottomDistance = $row["BottomDistance"];
        $row_SetDistance = $row["SetDistance"];
        $row_Delay = $row["Delay"]; 
        $row_reading_time = $row["reading_time"];
 ?>
			<tbody>
				<tr>
				    <td><?php echo $row_ID; ?></td>
					<td><?php echo $row_TopDistance; ?></td>
					<td><?php echo $row_BottomDistance; ?></td>
					<td><?php echo $row_SetDistance; ?></td>
					<td><?php echo $row_Delay; ?></td>
					<td><?php echo $row_Timestamp; ?></td>
					
				</tr>
			</tbody>
<?php 	} ?>
		</table>