<?php
$servername = "localhost";
$username = "root";
$password = "";
$database = "estacionamento";

// Criando a conexão
$conn = new mysqli($servername, $username, $password, $database);

// Verificando a conexão
if ($conn->connect_error) {
    die("Erro na conexão: " . $conn->connect_error);
}
?>