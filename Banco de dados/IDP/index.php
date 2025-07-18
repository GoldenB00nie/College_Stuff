<?php
include 'conexao.php';

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $nome = $conn->real_escape_string($_POST['nome']);
    $sobrenome = $conn->real_escape_string($_POST['sobrenome']);
    $email = $conn->real_escape_string($_POST['email']);
    $cpf = $conn->real_escape_string($_POST['cpf']);

    $sql = "INSERT INTO usuarios (nome, sobrenome, email, cpf)
            VALUES ('$nome', '$sobrenome', '$email', '$cpf')";

    $mensagem = $conn->query($sql) === TRUE 
        ? "Cadastro realizado com sucesso!" 
        : "Erro: " . $conn->error;
}
?>

<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <title>Cadastro de Usuário</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">
    <link href="css/estilo.css" rel="stylesheet">
</head>
<body>

<div class="sidebar">
    <h4 class="text-center py-3">Menu</h4>
    <a href="index.php" class="<?= basename($_SERVER['PHP_SELF']) == 'index.php' ? 'active' : '' ?>">Cadastrar Usuário</a>
    <a href="listar.php" class="<?= basename($_SERVER['PHP_SELF']) == 'listar.php' ? 'active' : '' ?>">Listar Usuários</a>
    <a href="#">Relatórios</a>
    <a href="#">Configurações</a>
</div>

<div class="content">
    <h2>Cadastro de Usuário</h2>

    <?php if (isset($mensagem)): ?>
        <div class="alert alert-info"><?= $mensagem ?></div>
    <?php endif; ?>

    <form method="post" action="">
        <div class="mb-3">
            <label class="form-label">Nome</label>
            <input type="text" name="nome" class="form-control" required>
        </div>
        <div class="mb-3">
            <label class="form-label">Sobrenome</label>
            <input type="text" name="sobrenome" class="form-control" required>
        </div>
        <div class="mb-3">
            <label class="form-label">Email</label>
            <input type="email" name="email" class="form-control" required>
        </div>
        <div class="mb-3">
            <label class="form-label">CPF</label>
            <input type="text" name="cpf" class="form-control" required>
        </div>
        <button type="submit" class="btn btn-primary">Salvar</button>
    </form>
</div>

</body>
</html>
