CREATE DATABASE estacionamento;
USE estacionamento;

CREATE TABLE Veiculos (
    id_veiculo INT PRIMARY KEY AUTO_INCREMENT,
    placa VARCHAR(8) NOT NULL,
    modelo VARCHAR(50) NOT NULL,
    cor VARCHAR(20) NOT NULL,
    nome_proprietario VARCHAR(100) NOT NULL
);

CREATE TABLE clientes (
    id_cliente INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(255) NOT NULL,
    id_veiculo INT,
    FOREIGN KEY (id_veiculo) REFERENCES Veiculos(id_veiculo)
);

CREATE TABLE Vagas (
    id_vaga INT PRIMARY KEY AUTO_INCREMENT,
    codigo_vaga VARCHAR(10) NOT NULL,
    status ENUM('livre', 'ocupada', 'reservada') NOT NULL
);

CREATE TABLE Entradas (
    id_entrada INT PRIMARY KEY AUTO_INCREMENT,
    id_vaga INT,
    id_veiculo INT,
    data_hora_entrada DATETIME NOT NULL,
    FOREIGN KEY (id_vaga) REFERENCES Vagas(id_vaga),
    FOREIGN KEY (id_veiculo) REFERENCES Veiculos(id_veiculo)
);

CREATE TABLE Saidas (
    id_saida INT PRIMARY KEY AUTO_INCREMENT,
    id_entrada INT,
    data_hora_saida DATETIME NOT NULL,
    FOREIGN KEY (id_entrada) REFERENCES Entradas(id_entrada)
);

CREATE TABLE Tarifas (
    id_tarifa INT PRIMARY KEY AUTO_INCREMENT,
    tempo_minimo INT NOT NULL,
    valor_minimo DECIMAL(10,2) NOT NULL,
    valor_hora_adicional DECIMAL(10,2) NOT NULL
);

CREATE TABLE Reservas (
    id_reserva INT PRIMARY KEY AUTO_INCREMENT,
    id_vaga INT,
    id_veiculo INT,
    data_hora_reserva DATETIME NOT NULL,
    data_hora_inicio_reserva DATETIME NOT NULL,
    data_hora_fim_reserva DATETIME NOT NULL,
    FOREIGN KEY (id_vaga) REFERENCES Vagas(id_vaga),
    FOREIGN KEY (id_veiculo) REFERENCES Veiculos(id_veiculo)
);