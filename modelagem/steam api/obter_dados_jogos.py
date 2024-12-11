import navegar_arquivo as file
import pesquisar_steam as searchSteam

def inserir_dados_objeto(nome_procurar):
    if file.jogo_existente(nome_procurar):
        print("Jogo ja existe nos arquivos.")
        jogo = file.ler_jogo(nome_procurar)
    else:
        jogo = searchSteam.pegar_dados_jogo(nome_procurar)
        if jogo == None: return None
        file.inserir_jogo_database(jogo)

    jogoData = {
        "nomeJogo": jogo["nomeJogo"],
        "tipoJogo": jogo["tipoJogo"],
        "idJogo": jogo["idJogo"],
        "categorias": jogo["categorias"]
    }
    return jogoData

def contar_categorias(lista_jogos):
    count_categorias = {}
    for nome_jogo in lista_jogos:
        jogo = inserir_dados_objeto(nome_jogo)
        if jogo == None: continue
        for j in range (len(jogo['categorias'])):
            if jogo['categorias'][j] not in count_categorias:
                count_categorias[jogo["categorias"][j]] = 1
            else: count_categorias[jogo["categorias"][j]] += 1
    return count_categorias

