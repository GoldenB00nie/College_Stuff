<?php
include 'conexao.php';

$mensagem = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $nome = $_POST['nome'];
    $telefone = $_POST['telefone'];
    $cpf = $_POST['cpf'];

    $stmt = $conn->prepare("INSERT INTO cliente (nome, telefone, cpf) VALUES (?, ?, ?)");
    $stmt->bind_param("sss", $nome, $telefone, $cpf);

    if ($stmt->execute()) {
        $mensagem = "Cliente cadastrado com sucesso!";
    } else {
        $mensagem = "Erro ao cadastrar: " . $conn->error;
    }

    $stmt->close();
}
?>

<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <title>Cadastrar Cliente</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">
    <link href="css/estilo.css" rel="stylesheet">
</head>
<body>

<div class="sidebar">
    <h4 class="text-center py-3">Menu</h4>
    <a href="index.php" class="<?= basename($_SERVER['PHP_SELF']) == 'index.php' ? 'active' : '' ?>">Cadastrar Cliente</a>
    <a href="listar.php" class="<?= basename($_SERVER['PHP_SELF']) == 'listar.php' ? 'active' : '' ?>">Listar Clientes</a>
    <a href="#">Relatórios</a>
    <a href="#">Configurações</a>
</div>

<div class="content">
    <h2>Cadastrar Cliente</h2>

    <?php if (!empty($mensagem)): ?>
        <div class="alert alert-info"><?= $mensagem ?></div>
    <?php endif; ?>

    <form method="post" action="index.php" class="row g-3">
        <div class="col-md-6">
            <label for="nome" class="form-label">Nome Completo</label>
            <input type="text" name="nome" id="nome" class="form-control" required>
        </div>
        <div class="col-md-6">
            <label for="telefone" class="form-label">Telefone</label>
            <input type="text" name="telefone" id="telefone" class="form-control">
        </div>
        <div class="col-md-6">
            <label for="cpf" class="form-label">CPF</label>
            <input type="text" name="cpf" id="cpf" class="form-control" required>
        </div>
        <div class="col-12">
            <button type="submit" class="btn btn-primary">Salvar</button>
        </div>
    </form>
</div>

</body>
</html>
