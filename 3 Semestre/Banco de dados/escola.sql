CREATE DATABASE Escola;
USE Escola;

-- Criando a tabela Aluno
CREATE TABLE Aluno (
    id INT PRIMARY KEY,
    nome VARCHAR(50),
    idade INT,
    curso_id INT
);

-- Criando a tabela Curso
CREATE TABLE Curso (
    id INT PRIMARY KEY,
    nome_curso VARCHAR(50)
);

-- Criando a tabela Professores
CREATE TABLE Professores (
    id INT PRIMARY KEY,
    nome VARCHAR(50),
    curso_id INT
);

-- Inserindo alunos
INSERT INTO Aluno (id, nome, idade, curso_id) VALUES
(1, 'Ana', 20, 1),
(2, 'João', 22, 2),
(3, 'Maria', 19, 1),
(4, 'Pedro', 25, 3);

-- Inserindo cursos
INSERT INTO Curso (id, nome_curso) VALUES
(1, 'Sistemas de Informação'),
(2, 'Administração'),
(3, 'Ciência da Computação');

-- Inserindo professores
INSERT INTO Professores (id, nome, curso_id) VALUES
(1, 'Carlos', 1),
(2, 'Fernanda', 2),
(3, 'Marcos', 3);

