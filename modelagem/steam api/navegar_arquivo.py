import json
import difflib

# Função para verificar se o jogo já está no arquivo
def jogo_existente(nome_jogo, nome_arquivo="dados_jogos.txt"):
    with open(nome_arquivo, "r") as file:
        for line in file:
            jogo = json.loads(line)
            if jogo["nomeJogo"] == nome_jogo:
                return True
    return False

def inserir_jogo_database(dados, nome_arquivo="dados_jogos.txt"):
    if not jogo_existente(dados["nomeJogo"]):
        with open(nome_arquivo, "a") as file:
            file.write(json.dumps(dados) + "\n")
            print("Jogo inserido com sucesso.")

# Função para ler um jogo específico pelo nome do jogo
def ler_jogo(nome_jogo_procurado, nome_arquivo="dados_jogos.txt"):
    with open(nome_arquivo, "r") as file:
        jogos = [json.loads(line) for line in file]
    
    # Obtenção dos nomes dos jogos no arquivo
    nomes_jogos = [jogo["nomeJogo"] for jogo in jogos]
    
    # Encontrando o nome mais próximo
    nome_jogo_mais_proximo = difflib.get_close_matches(nome_jogo_procurado, nomes_jogos, n=1, cutoff=0.6)
    
    if nome_jogo_mais_proximo:
        nome_jogo_mais_proximo = nome_jogo_mais_proximo[0]
        for jogo in jogos:
            if jogo["nomeJogo"].lower() == nome_jogo_mais_proximo.lower():
                return jogo
    return None