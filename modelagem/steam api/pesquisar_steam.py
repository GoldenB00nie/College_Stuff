import os
from steam_web_api import Steam

KEY = os.environ.get("STEAM_API_KEY")

steam = Steam(KEY) # Pega a chave da sua steam api

def pegar_dados_jogo(nome_procurado):
    try: jogo_procurado = steam.apps.search_games(nome_procurado)
    except: print("Erro ao procurar o jogo."); return None
    if not jogo_procurado or len(jogo_procurado.get('apps', [])) == 0:
        print("Jogo procurado não encontrado.")
        return None

    try: nomeJogo = jogo_procurado['apps'][0]['name']
    except: return None
    try: idJogo = jogo_procurado['apps'][0]['id'][0]
    except: return None

    if not idJogo:
        print("Não foi possível obter o id do jogo.")
        return None

    try: jogo_detalhado = steam.apps.get_app_details(idJogo)
    except: print("Não foi possível obter o jogo detalhado."); return None
    if not jogo_detalhado or str(idJogo) not in jogo_detalhado or 'data' not in jogo_detalhado[str(idJogo)]:
        print(f"Detalhes do jogo não encontrados ou incompletos para ID {idJogo}.")
        return None

    try: tipoJogo = jogo_detalhado[str(idJogo)]['data'].get('type')
    except: print("Erro ao obter o tipo do jogo."); return None
    if not tipoJogo:
        print("Tipo de jogo não encontrado.")
        return None

    try: jogo_genres = steam.apps.get_app_details(idJogo, filters="genres")
    except: print("Erro ao obter o tipo do jogo."); return None
    if not jogo_genres or str(idJogo) not in jogo_genres or 'data' not in jogo_genres[str(idJogo)]:
        print(f"Gêneros do jogo não encontrados para ID {idJogo}.")
        return None

    try: genres_data = jogo_genres[str(idJogo)]['data']['genres']
    except: print("Impossível obter os gêneros do jogo"); return None
    if isinstance(genres_data, list):
        categorias = [genre['description'] for genre in genres_data]
    else:
        print("Formato inesperado nos dados dos gêneros.")
        return None

    dados_jogo = {
        "nomeJogo": nomeJogo,
        "tipoJogo": tipoJogo,
        "idJogo": idJogo,
        "categorias": categorias
    }

    if dados_jogo:
        return dados_jogo
    else:
        print("Erro ao obter dados do jogo.")
        return None