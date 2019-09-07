<?php
$servername = "localhost";
$username = "root";
$password = "";
$database = "test";

// Create connection
$conn = new mysqli($servername, $username, $password, $database);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
 



$query = "INSERT INTO attendees VALUES ('". $_POST["RFID_Tag"] ."')";
$conn->query($query);

echo "Connected successfully";
?>