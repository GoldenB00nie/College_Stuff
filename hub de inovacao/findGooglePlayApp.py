from google_play_scraper import search

def searchAppId(nomeApp):
    result = search(nomeApp, lang="en", country="us", n_hits=1)[0]['appId']
    print(f"AppId encontrado para o App {nomeApp}: {result}")
    return result