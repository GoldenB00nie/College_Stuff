<?php
include 'conexao.php';

$sql = "SELECT * FROM cliente ORDER BY id_cliente DESC";
$result = $conn->query($sql);
?>

<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <title>Listar Usuários</title>
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
    <h2>Usuários Cadastrados</h2>

    <?php if ($result && $result->num_rows > 0): ?>
        <table class="table table-striped">
            <thead>
                <tr>
                    <th>ID</th>
                    <th>Nome</th>
                    <th>Telefone</th>
                    <th>CPF</th>
                </tr>
            </thead>
            <tbody>
                <?php while ($row = $result->fetch_assoc()): ?>
                    <tr>
                        <td><?= $row['id_cliente'] ?></td>
                        <td><?= htmlspecialchars($row['nome']) ?></td>
                        <td><?= htmlspecialchars($row['telefone']) ?></td>
                        <td><?= htmlspecialchars($row['cpf']) ?></td>
                    </tr>
                <?php endwhile; ?>
            </tbody>
        </table>
    <?php else: ?>
        <div class="alert alert-info">Nenhum usuário encontrado.</div>
    <?php endif; ?>
</div>

</body>
</html>
