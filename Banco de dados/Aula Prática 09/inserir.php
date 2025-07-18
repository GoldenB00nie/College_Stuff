<?php
include 'conexao.php';

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Pega os dados do formulário
    $nome = trim($_POST["nome"]);
    $email = trim($_POST["email"]);
    $cpf = trim($_POST["cpf"]);

    // Verifica se os campos estão preenchidos
    if (empty($nome) || empty($email) || empty($cpf)) {
        echo "Todos os campos são obrigatórios.";
        exit;
    }

    // Prepara e executa o INSERT
    $stmt = $conn->prepare("INSERT INTO cliente (nome, email, cpf) VALUES (?, ?, ?)");
    $stmt->bind_param("ssss", $nome, $email, $cpf);

    try {
        $stmt->execute();
        echo "Cadastro feito com sucesso! <a href='listar.php'>Ver cadastros</a>";
    } catch (mysqli_sql_exception $e) {
        if (strpos($e->getMessage(), 'Duplicate') !== false) {
            echo "Erro: E-mail ou CPF já cadastrado.";
        } else {
            echo "Erro ao cadastrar: " . $e->getMessage();
        }
    }
}
?>