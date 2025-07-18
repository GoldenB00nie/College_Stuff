CREATE TABLE Produto(
    cod_produto INT PRIMARY KEY,
    nome_produto VARCHAR(100),
    categoria_produto VARCHAR(50),
    preco_unitario DECIMAL(10,2)
);

CREATE TABLE Cliente (
    cpf_cliente CHAR(11) PRIMARY KEY,
    nome_cliente VARCHAR(100),
    endereco_cliente VARCHAR(255)
);

CREATE TABLE Vendedor (
    cpf_vendedor CHAR(11) PRIMARY KEY,
    nome_vendedor VARCHAR(100),
    regional_vendedor VARCHAR(100)
);

CREATE TABLE Venda (
    id_venda INT PRIMARY KEY,
    cod_produto INT,
    cpf_cliente VARCHAR(100),
    cpf_vendedor VARCHAR(100),
    data DATE,
	FOREIGN KEY (cod_produto) REFERENCES Produto(cod_produto),
    FOREIGN KEY (cpf_cliente) REFERENCES Pessoa(cpf_cliente),
    FOREIGN KEY (cpf_vendedor) REFERENCES Vendedor(cpf_vendedor)
);


INSERT INTO Produto VALUES
(101, 'Caneta Azul', 'Papelaria', 2.50),
(102, 'Caderno 200fl', 'Papelaria', 15.00),
(103, 'Mochila Escolar', 'Mochilas', 120.00);

INSERT INTO Cliente VALUES
('12345678901', 'Maria Souza', 'Rua A, 123'),
('32165498700', 'Carlos Mendes', 'Av. Central, 456'),
('45612378900', 'Bruna Rocha', 'Rua B, 789');

INSERT INTO Vendedor VALUES
('98765432100', 'João Lima', 'Sul'),
('11122233344', 'Ana Paula', 'Norte');

INSERT INTO Venda VALUES
(1, 101, '12345678901', '98765432100', '2025-05-01'),
(2, 102, '32165498700', '98765432100', '2025-05-01'),
(3, 103, '12345678901', '11122233344', '2025-05-02'),
(4, 101, '45612378900', '98765432100', '2025-05-03'),
(5, 103, '32165498700', '11122233344', '2025-05-03');

