import os 
import re
import requests
from bs4 import BeautifulSoup
from collections import defaultdict
from html.parser import HTMLParser
import obter_dados_jogos as obter

clear = lambda: os.system('cls')

class MyHTMLParser(HTMLParser):
    def __init__(self):
        super().__init__()
        self.reset()
        self.HTMLDATA = ""
    def handle_data(self, data):
        self.HTMLDATA = data
    def clean(self):
        self.HTMLDATA = ""

def obter_dados_steamSpy(link):
    def pegar_nome_jogo():
        try: a = f"{tr.find("a")}"
        except: return None
        parser = MyHTMLParser()
        parser.feed(f"{a}")
        nome_jogo = parser.HTMLDATA[1:]
        assert nome_jogo != None, "Erro: Não foi possível obter o nome do jogo"
        nome_jogo = re.sub(r'[^\w\s]', '', nome_jogo)
        parser.clean()
        print("Jogo carregado: ", nome_jogo)
        return nome_jogo

    try: pagina_spy = requests.get(link)
    except: return None

    if pagina_spy.status_code != 200: print("Erro: não foi possível carregar a página."); return None
    soup = BeautifulSoup(pagina_spy.content, "html.parser")
    page_container = soup.find("div", {"class": "page-container"})

    try: tbody = page_container.find("tbody")
    except: return None

    try: lista_tr = tbody.findAll("tr", limit=20)
    except: return None

    count = 0
    lista_nomes_jogos = []
    for tr in lista_tr:
        lista_nomes_jogos.append(pegar_nome_jogo())
        count += 1
    print(count)
    return lista_nomes_jogos


count_lista = {}
lista = {}

def inserir_lista(ano, mes, dia, link):
    if ano not in lista:
        lista[ano] = {"Meses": {}, "CountAno": {}}
    if mes not in lista[ano]["Meses"]:
        lista[ano]["Meses"][mes] = {"Dias": {}, "CountMes": {}}

    lista_jogos = obter_dados_steamSpy(link)
    if lista_jogos == None: print("Não foi possível conectar ao website."); return 0

    aux = obter.contar_categorias(lista_jogos)
    
    # Redefine count_dia para cada novo dia
    count_dia = {}
    for categoria, count in aux.items():
        if categoria in count_dia:
            count_dia[categoria] += count
        else:
            count_dia[categoria] = count
    
    if not count_dia:  # Verifica se count_dia está vazio
        return 0
    
    lista[ano]["Meses"][mes]["Dias"][dia] = {"Jogos": lista_jogos, "CountDia": count_dia}

    for categoria in count_dia:
        # Atualiza o mês
        if categoria in lista[ano]["Meses"][mes]["CountMes"]:
            lista[ano]["Meses"][mes]["CountMes"][categoria] += count_dia[categoria]
        else:
            lista[ano]["Meses"][mes]["CountMes"][categoria] = count_dia[categoria]

        # Atualiza o ano
        if categoria in lista[ano]["CountAno"]:
            lista[ano]["CountAno"][categoria] += count_dia[categoria]
        else:
            lista[ano]["CountAno"][categoria] = count_dia[categoria]

        # Atualiza a lista
        if categoria in count_lista:
            count_lista[categoria] += count_dia[categoria]
        else:
            count_lista[categoria] = count_dia[categoria]
    return 1



#inserir_lista(spy_ano, spy_mes, spy_dia)
api_url = "https://web.archive.org/cdx/search/cdx"
params = {
    "url": "https://steamspy.com",
    "limit": -773,
    "output": "json"
}

response = requests.get(api_url, params=params)

assert response.status_code == 200, "Erro: Não foi possível abrir a API do Wayback Machine"
data = response.json()
columns = ["urlkey", "timestamp", "original", "mimetype", "statuscode", "digest", "length"]

daily_saves = defaultdict(list)
for row in data[1:]:
    timestamp = row[1]
    date = timestamp[:8]  # Extrair a data (AAAAmmdd) do timestamp
    daily_saves[date].append(row)

latest_saves = []
for date, saves in daily_saves.items():
    latest_save = max(saves, key=lambda x: x[1])  # Selecionar o save com o timestamp mais alto
    latest_saves.append(dict(zip(columns, latest_save)))
for save in latest_saves:
    ano, mes, dia = save['timestamp'][:4], save['timestamp'][4:6], save['timestamp'][6:8],
    link = "https://web.archive.org/web/" + save['timestamp'] + "/" + params["url"]
    print(save)
    print(link)
    print(f"\tAno: {ano}, Mês: {mes}, Dia: {dia}")
    teste_existe = inserir_lista(ano, mes, dia, link)
    if teste_existe == 0: print("Jogo não existe na Steam."); continue
    clear()
    print("Lista de jogos inserido com sucesso. Iniciando a próxima...\n\n")

dados_lista = {
    "Lista": lista,
    "CountLista": count_lista
}

# Exibindo os resultados finais
print("Dados:", dados_lista)
