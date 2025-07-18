-- CRIANDO O DATABASE E AS TABELAS

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
    status ENUM('livre', 'ocupada', 'reservada') NOT NULL
) DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;


CREATE TABLE reserva (
    id_reserva INT AUTO_INCREMENT PRIMARY KEY,
    id_cliente INT NOT NULL,
    id_vaga INT NOT NULL,
    data_hora_reserva DATETIME NOT NULL,
    status ENUM('ativa', 'expirada', 'cancelada') NOT NULL DEFAULT 'ativa',
    FOREIGN KEY (id_cliente) REFERENCES cliente(id_cliente),
    FOREIGN KEY (id_vaga) REFERENCES vaga(id_vaga)
) DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;


CREATE TABLE controle_saida (
    id_controle INT AUTO_INCREMENT PRIMARY KEY,
    placa VARCHAR(10) NOT NULL,
    id_vaga INT NOT NULL,
    id_reserva INT NULL,
    data_hora_entrada DATETIME NOT NULL,
    data_hora_saida DATETIME,
    FOREIGN KEY (placa) REFERENCES carro(placa),
    FOREIGN KEY (id_vaga) REFERENCES vaga(id_vaga),
    FOREIGN KEY (id_reserva) REFERENCES reserva(id_reserva)
) DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;


CREATE TABLE tarifa (
    id_tarifa INT AUTO_INCREMENT PRIMARY KEY,
    descricao VARCHAR(50) NOT NULL,
    preco_por_hora DECIMAL(10,2) NOT NULL
) DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;


CREATE TABLE pagamento (
    id_pagamento INT AUTO_INCREMENT PRIMARY KEY,
    id_controle INT NOT NULL,
    id_reserva INT NULL,
    valor DECIMAL(10,2) NOT NULL,
    data_hora_pagamento DATETIME NOT NULL,
    status ENUM('pendente', 'pago', 'cancelado') NOT NULL DEFAULT 'pendente',
    FOREIGN KEY (id_controle) REFERENCES controle_saida(id_controle),
    FOREIGN KEY (id_reserva) REFERENCES reserva(id_reserva)
) DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;


CREATE TABLE usuario (
    id_usuario INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    tipo ENUM('administrador', 'operador') NOT NULL
) DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;


-- INSERINDO UMA VAGA COM RESERVA (carlos) E UMA VAGA SEM RESERVA (mariana).

-- Inserindo o cliente Carlos Silva (com reserva)
INSERT INTO cliente (nome, telefone, cpf) VALUES ('Carlos Silva', '(11) 98765-4321', '123.456.789-00');

-- Inserindo um veículo para Carlos
INSERT INTO carro (placa, modelo, cor, id_cliente) 
VALUES ('ABC1234', 'Toyota Corolla', 'Prata', (SELECT id_cliente FROM cliente WHERE cpf = '123.456.789-00'));

-- Inserindo uma vaga para Carlos
INSERT INTO vaga (codigo, status) VALUES ('V001', 'reservada');

-- Criando uma reserva para Carlos na vaga V001
INSERT INTO reserva (id_cliente, id_vaga, data_hora_reserva, status) 
VALUES ((SELECT id_cliente FROM cliente WHERE cpf = '123.456.789-00'),
        (SELECT id_vaga FROM vaga WHERE codigo = 'V001'),
        NOW(), 'ativa');

-- Atualizando a vaga para ocupada quando Carlos estaciona
UPDATE vaga 
SET status = 'ocupada' 
WHERE codigo = 'V001';

-- Registrando entrada do veículo de Carlos
INSERT INTO controle_saida (placa, id_vaga, id_reserva, data_hora_entrada) 
VALUES ('ABC1234', (SELECT id_vaga FROM vaga WHERE codigo = 'V001'), 
        (SELECT id_reserva FROM reserva WHERE id_cliente = (SELECT id_cliente FROM cliente WHERE cpf = '123.456.789-00')), NOW());

-- Inserindo o cliente Mariana Souza (sem reserva)
INSERT INTO cliente (nome, telefone, cpf) VALUES ('Mariana Souza', '(21) 99876-5432', '987.654.321-00');

-- Inserindo um veículo para Mariana
INSERT INTO carro (placa, modelo, cor, id_cliente) 
VALUES ('XYZ5678', 'Honda Civic', 'Preto', (SELECT id_cliente FROM cliente WHERE cpf = '987.654.321-00'));

-- Inserindo uma vaga livre para Mariana
INSERT INTO vaga (codigo, status) VALUES ('V002', 'livre');

-- Registrando entrada do veículo de Mariana sem reserva em uma vaga livre
INSERT INTO controle_saida (placa, id_vaga, id_reserva, data_hora_entrada) 
VALUES ('XYZ5678', (SELECT id_vaga FROM vaga WHERE status = 'livre' LIMIT 1), NULL, NOW());

-- Atualizando manualmente o status da vaga para ocupada após a entrada do carro de Mariana
UPDATE vaga 
SET status = 'ocupada' 
WHERE id_vaga = (SELECT id_vaga FROM controle_saida WHERE placa = 'XYZ5678');

-- Verificando o status das vagas
SELECT v.codigo, v.status, c.placa 
FROM vaga v 
LEFT JOIN controle_saida cs ON v.id_vaga = cs.id_vaga 
LEFT JOIN carro c ON cs.placa = c.placa;

-- AGORA CALCULANDO A TARIFA E COLOCANDO A VAGA DO CARLOS E DA MARIANA COMO LIVRE.

-- tarifa padrão (se ainda não existir)
INSERT INTO tarifa (descricao, preco_por_hora) 
VALUES ('Tarifa Padrão', 5.00);

-- Atualiza a saída de Carlos (com reserva)
UPDATE controle_saida 
SET data_hora_saida = NOW() 
WHERE placa = 'ABC1234' AND data_hora_saida IS NULL;

-- Atualiza a saída de Mariana (sem reserva)
UPDATE controle_saida 
SET data_hora_saida = NOW() 
WHERE placa = 'XYZ5678' AND data_hora_saida IS NULL;

-- para exibir valores para serem pagos antes da inserção
SELECT 
    cs.placa,
    ROUND(TIMESTAMPDIFF(MINUTE, cs.data_hora_entrada, cs.data_hora_saida) / 60, 2) AS horas_estacionadas,
    t.preco_por_hora,
    ROUND((TIMESTAMPDIFF(MINUTE, cs.data_hora_entrada, cs.data_hora_saida) / 60) * t.preco_por_hora, 2) AS valor_a_pagar
FROM controle_saida cs
JOIN tarifa t ON t.id_tarifa = 1
WHERE cs.data_hora_saida IS NOT NULL;

-- Inserindo os pagamentos
INSERT INTO pagamento (id_controle, id_reserva, valor, data_hora_pagamento, status)
SELECT 
    cs.id_controle, 
    cs.id_reserva, 
    ROUND((TIMESTAMPDIFF(MINUTE, cs.data_hora_entrada, cs.data_hora_saida) / 60) * t.preco_por_hora, 2), 
    NOW(), 
    'pago'
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


