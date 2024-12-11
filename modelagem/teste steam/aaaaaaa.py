import json
import functions
          # ! / Usr / bin / python
          # - * - Coding : <UTF-8> - * -

# Definindo as variáveis
nomePesquisado = "Minecraft"
nomeJogo = "Geometry dash"
idJogo = 178842
categorias = ['Casual', 'RPG', 'Aventura']

# Criando um dicionário com as variáveis
novo_jogo = {
    "nomeJogo": nomeJogo,
    "idJogo": idJogo,
    "categorias": categorias
}

# Escrevendo o dicionário em uma única linha no arquivo de texto
#functions.inserir_jogo_database(novo_jogo)

# Lendo a segunda linha do arquivo
jogo = functions.ler_jogo_nome("terrari")

# Verificando e exibindo o jogo lido
if jogo:
    print("nomeJogo:", jogo["nomeJogo"])
    print("idJogo:", jogo["idJogo"])
    print("categorias:", jogo["categorias"])
else:
    print("Jogo não encontrado.")
