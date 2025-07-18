DROP TABLE IF EXISTS reservas;

-- CRIANDO O DATABASE E AS TABELAS ATUALIZADAS
CREATE DATABASE estacionamento
CHARACTER SET utf8mb4
COLLATE utf8mb4_unicode_ci;
USE estacionamento;

CREATE TABLE cliente (
    id_cliente INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    telefone VARCHAR(20),
    cpf VARCHAR(14) NOT NULL
) DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE carro (
    placa VARCHAR(10) PRIMARY KEY,
    modelo VARCHAR(50) NOT NULL,
    cor VARCHAR(20),
    id_cliente INT NOT NULL,
    FOREIGN KEY (id_cliente) REFERENCES cliente(id_cliente)
) DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE vaga (
    id_vaga INT AUTO_INCREMENT PRIMARY KEY,
    codigo VARCHAR(10) UNIQUE NOT NULL,
    status ENUM('livre', 'ocupada') NOT NULL
) DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE tag_estacionamento (
    id_tag INT AUTO_INCREMENT PRIMARY KEY,
    id_cliente INT NOT NULL,
    codigo_tag VARCHAR(50) UNIQUE NOT NULL,
    status ENUM('ativa', 'inativa', 'problema_técnico') NOT NULL DEFAULT 'inativa',
    FOREIGN KEY (id_cliente) REFERENCES cliente(id_cliente)
) DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE controle_saida (
    id_controle INT AUTO_INCREMENT PRIMARY KEY,
    placa VARCHAR(10) NOT NULL,
    id_vaga INT NOT NULL,
    data_hora_entrada DATETIME NOT NULL,
    data_hora_saida DATETIME,
    FOREIGN KEY (placa) REFERENCES carro(placa),
    FOREIGN KEY (id_vaga) REFERENCES vaga(id_vaga)
) DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE tarifa (
    id_tarifa INT AUTO_INCREMENT PRIMARY KEY,
    descricao VARCHAR(50) NOT NULL,
    preco_por_hora DECIMAL(10,2) NOT NULL
) DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE pagamento (
    id_pagamento INT AUTO_INCREMENT PRIMARY KEY,
    id_controle INT NOT NULL,
    valor DECIMAL(10,2) NOT NULL,
    data_hora_pagamento DATETIME NOT NULL,
    status ENUM('pendente', 'pago', 'cancelado') NOT NULL DEFAULT 'pendente',
    forma_pagamento ENUM('Visa', 'Mastercard', 'Dinheiro', 'Outro') NOT NULL,
    meses_gratuitos BOOLEAN NOT NULL DEFAULT FALSE,
    FOREIGN KEY (id_controle) REFERENCES controle_saida(id_controle)
) DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE usuario (
    id_usuario INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    tipo ENUM('administrador', 'operador') NOT NULL
) DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- INSERINDO UMA VAGA PARA UM CLIENTE COM TAG (CARLOS) E SEM TAG (MARIANA)

-- Inserindo o cliente Carlos Silva (com tag)
INSERT INTO cliente (nome, telefone, cpf) VALUES ('Carlos Silva', '(11) 98765-4321', '123.456.789-00');

-- Inserindo um veículo para Carlos
INSERT INTO carro (placa, modelo, cor, id_cliente) 
VALUES ('ABC1234', 'Toyota Corolla', 'Prata', (SELECT id_cliente FROM cliente WHERE cpf = '123.456.789-00'));

-- Inserindo uma tag ativa para Carlos
INSERT INTO tag_estacionamento (id_cliente, codigo_tag, status) 
VALUES ((SELECT id_cliente FROM cliente WHERE cpf = '123.456.789-00'), 'TAG12345', 'ativa');

-- Inserindo uma vaga para Carlos
INSERT INTO vaga (codigo, status) VALUES ('V001', 'ocupada');

-- Registrando entrada do veículo de Carlos
INSERT INTO controle_saida (placa, id_vaga, data_hora_entrada) 
VALUES ('ABC1234', (SELECT id_vaga FROM vaga WHERE codigo = 'V001'), NOW());

-- Inserindo o cliente Mariana Souza (sem tag)
INSERT INTO cliente (nome, telefone, cpf) VALUES ('Mariana Souza', '(21) 99876-5432', '987.654.321-00');

-- Inserindo um veículo para Mariana
INSERT INTO carro (placa, modelo, cor, id_cliente) 
VALUES ('XYZ5678', 'Honda Civic', 'Preto', (SELECT id_cliente FROM cliente WHERE cpf = '987.654.321-00'));

-- Inserindo uma vaga livre para Mariana
INSERT INTO vaga (codigo, status) VALUES ('V002', 'livre');

-- Registrando entrada do veículo de Mariana sem tag em uma vaga livre
INSERT INTO controle_saida (placa, id_vaga, data_hora_entrada) 
VALUES ('XYZ5678', (SELECT id_vaga FROM vaga WHERE status = 'livre' LIMIT 1), NOW());

-- Atualizando manualmente o status da vaga para ocupada após a entrada do carro de Mariana
UPDATE vaga 
SET status = 'ocupada' 
WHERE id_vaga = (SELECT id_vaga FROM controle_saida WHERE placa = 'XYZ5678');

-- Verificando o status das vagas
SELECT v.codigo, v.status, c.placa 
FROM vaga v 
LEFT JOIN controle_saida cs ON v.id_vaga = cs.id_vaga 
LEFT JOIN carro c ON cs.placa = c.placa;

-- CALCULANDO A TARIFA E LIBERANDO AS VAGAS

-- Tarifa padrão (se ainda não existir)
INSERT INTO tarifa (descricao, preco_por_hora) 
VALUES ('Tarifa Padrão', 5.00);

-- Atualiza a saída de Carlos
UPDATE controle_saida 
SET data_hora_saida = NOW() 
WHERE placa = 'ABC1234' AND data_hora_saida IS NULL;

-- Atualiza a saída de Mariana
UPDATE controle_saida 
SET data_hora_saida = NOW() 
WHERE placa = 'XYZ5678' AND data_hora_saida IS NULL;

-- Exibir valores para serem pagos antes da inserção
SELECT 
    cs.placa,
    ROUND(TIMESTAMPDIFF(MINUTE, cs.data_hora_entrada, cs.data_hora_saida) / 60, 2) AS horas_estacionadas,
    t.preco_por_hora,
    ROUND((TIMESTAMPDIFF(MINUTE, cs.data_hora_entrada, cs.data_hora_saida) / 60) * t.preco_por_hora, 2) AS valor_a_pagar
FROM controle_saida cs
JOIN tarifa t ON t.id_tarifa = 1
WHERE cs.data_hora_saida IS NOT NULL;

-- Inserindo os pagamentos
INSERT INTO pagamento (id_controle, valor, data_hora_pagamento, status, forma_pagamento, meses_gratuitos)
SELECT 
    cs.id_controle, 
    ROUND((TIMESTAMPDIFF(MINUTE, cs.data_hora_entrada, cs.data_hora_saida) / 60) * t.preco_por_hora, 2), 
    NOW(), 
    'pago',
    'Visa',
    TRUE
FROM controle_saida cs
JOIN tarifa t ON t.id_tarifa = 1
WHERE cs.data_hora_saida IS NOT NULL 
AND NOT EXISTS (
    SELECT 1 FROM pagamento p WHERE p.id_controle = cs.id_controle
);

-- Exibir os pagamentos feitos
SELECT * FROM pagamento;

-- Atualizar as vagas para o status 'livre' após o pagamento
UPDATE vaga 
SET status = 'livre' 
WHERE id_vaga IN (
    SELECT cs.id_vaga 
    FROM controle_saida cs
    JOIN pagamento p ON p.id_controle = cs.id_controle
    WHERE p.status = 'pago'
);

-- Remover as placas com a vaga no controle de saída
UPDATE controle_saida 
SET placa = NULL 
WHERE id_controle IN (
    SELECT p.id_controle 
    FROM pagamento p 
    WHERE p.status = 'pago'
);

-- Verificando se as vagas foram liberadas
SELECT v.codigo, v.status 
FROM vaga v;
