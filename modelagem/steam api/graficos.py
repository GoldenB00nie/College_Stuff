import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

tipo_transf = None
ano = None
mes = None
dia = None

def definir_tipo(tipo, ano_ins, mes_ins, dia_ins):
    global tipo_transf
    global ano
    global mes
    global dia
    if tipo in ["Dia", "Mes", "Ano", "ListaAnos"]:
        tipo_transf = tipo
        ano = ano_ins
        mes = mes_ins
        dia = dia_ins
    else:
        raise ValueError("Tipo inválido. Use 'Dia', 'Mes' ou 'Ano'.")

def transformar_dados(dados_lista):
    global tipo_transf
    global ano
    global mes
    global dia
    data = []
    
    if tipo_transf == "Dia":
        for mes, conteudo_mes in dados_lista['Lista'][ano]['Meses'][mes]['Dias'][dia].items():
            for dia, conteudo_dia in conteudo_mes['Dias'].items():
                row = conteudo_dia['CountDia']
                data.append(row)
    elif tipo_transf == "Mes":
        for mes, conteudo in dados_lista['Lista'][ano]['Meses'].items():
            row = conteudo['CountMes']
            data.append(row)
    elif tipo_transf == "Ano":
        row = dados_lista['Lista'][ano]['CountAno']
        data.append(row)
    elif tipo_transf == "ListaAnos":
        for ano, conteudo_ano in dados_lista['Lista'].items():
            row = conteudo_ano['CountAno']
            data.append(row)
    else:
        raise ValueError("Tipo de transformação não definido. Chame 'definir_tipo' primeiro.")
    
    df = pd.DataFrame(data)
    df = df.apply(pd.to_numeric, errors='coerce')
    return df

def total_categorias(dados_lista):
    plt.figure(figsize=(12, 8))
    
    anos = list(dados_lista['Lista'].keys())
    categorias = set()
    
    # Coletar todas as categorias
    for ano in anos:
        categorias.update(dados_lista['Lista'][ano]['CountAno'].keys())
    
    # Inicializar DataFrame para armazenar os dados
    data = {categoria: [] for categoria in categorias}
    data['Ano'] = []
    
    for ano in anos:
        counts = dados_lista['Lista'][ano]['CountAno']
        for categoria in categorias:
            data[categoria].append(counts.get(categoria, 0))
        data['Ano'].append(ano)
    
    df = pd.DataFrame(data)
    df.set_index('Ano', inplace=True)
    df = df.transpose()
    
    # Criar gráfico de barras horizontal
    colors = plt.cm.viridis(np.linspace(0, 1, len(anos)))
    for i, ano in enumerate(anos):
        plt.barh(df.index, df[ano], label=ano, color=colors[i], alpha=0.7)
    
    plt.grid(color='grey', linestyle='-.', linewidth=0.5, alpha=0.4)
    plt.xlabel('Quantidade')
    plt.title('Quantidade de Categorias por Ano')
    plt.legend(title='Ano')
    
    # Adicionar valores em cima das barras
    for i, ano in enumerate(anos):
        for j, categoria in enumerate(df.index):
            plt.text(df[ano][j], j + (i * 0.1) - 0.15, f"{df[ano][j]}", va='center', ha='left', fontsize=8)

    plt.tight_layout()
    plt.savefig('C:/Users/T-GAMER/OneDrive/Imagens/Total categorias')

def medidas_centralidade(dados_lista):
    def adicionar_texto(ax, x, y): 
        for i in range(len(x)): ax.text(i, y[i], f"{y[i]:.1f}", ha='center', va='bottom')
    
    df = transformar_dados(dados_lista)
    moda_categ = df.mode().iloc[0]
    media_categ = df.mean()
    mediana_categ = df.median()

    fig, axs = plt.subplots(1, 3, figsize=(12, 6))

    axs[0].bar(moda_categ.index, moda_categ.values)
    axs[0].set_title('Moda das Categorias')
    axs[0].set_xlabel('Categorias')
    axs[0].grid(color ='grey', linestyle ='-.', linewidth = 0.5, alpha = 0.4)
    axs[0].tick_params(axis='x', rotation=90)
    adicionar_texto(axs[0], moda_categ.index, moda_categ.values)

    # Plot da Média
    axs[1].bar(media_categ.index, media_categ.values)
    axs[1].set_title('Média das Categorias')
    axs[1].set_xlabel('Categorias')
    axs[1].grid(color ='grey', linestyle ='-.', linewidth = 0.5, alpha = 0.4)
    axs[1].tick_params(axis='x', rotation=90)
    adicionar_texto(axs[1], media_categ.index, media_categ.values)

    # Plot da Mediana
    axs[2].bar(mediana_categ.index, mediana_categ.values)
    axs[2].set_title('Mediana das Categorias')
    axs[2].set_xlabel('Categorias')
    axs[2].grid(color ='grey', linestyle ='-.', linewidth = 0.5, alpha = 0.4)
    axs[2].tick_params(axis='x', rotation=90)
    adicionar_texto(axs[2], mediana_categ.index, mediana_categ.values)

    plt.tight_layout()
    plt.savefig('C:/Users/T-GAMER/OneDrive/Imagens/Medidas de Centralidade')

def amplitude(dados_lista):
    df = transformar_dados(dados_lista)
    amplitude_categorias = df.max() - df.min()

    plt.figure(figsize=(10, 6))
    plt.bar(amplitude_categorias.index, amplitude_categorias.values)
    plt.title('Amplitude das Categorias analisadas')
    plt.xlabel('Categorias')
    plt.xticks(rotation=90)
    for i in range(len(amplitude_categorias)):
        plt.text(i, amplitude_categorias[i], f"{amplitude_categorias[i]:.2f}", ha='center', va='bottom')
    plt.grid(color ='grey', linestyle ='-.', linewidth = 0.5, alpha = 0.4)

    plt.tight_layout()
    plt.savefig('C:/Users/T-GAMER/OneDrive/Imagens/Amplitude')


def variancia_desvio(dados_lista):
    def adicionar_texto(ax, x, y):
        for i in range(len(x)):
            ax.text(i, y[i], f"{y[i]:.2f}", ha="center", va="bottom")
    df = transformar_dados(dados_lista)
    variancia_categorias = df.var().rename("Variância")
    desvio_padrao_categorias = df.std().rename("Desvio")
    estatistica = pd.concat([variancia_categorias, desvio_padrao_categorias], axis=1)
    fig, axs = plt.subplots(1, 2, figsize=(12, 6))
    
    axs[0].bar(estatistica.index, estatistica['Variância'])
    axs[0].set_title('Variância das Categorias analisadas')
    axs[0].set_xlabel('Categorias')
    axs[0].tick_params(axis='x', rotation=90)
    axs[0].grid(color ='grey', linestyle ='-.', linewidth = 0.5, alpha = 0.4)
    adicionar_texto(axs[0], estatistica.index, estatistica['Variância'].values)

    axs[1].bar(estatistica.index, estatistica['Desvio'])
    axs[1].set_title('Desvio Padrão das Categorias analisadas')
    axs[1].set_xlabel('Categorias')
    axs[1].tick_params(axis='x', rotation=90)
    axs[1].grid(color ='grey', linestyle ='-.', linewidth = 0.5, alpha = 0.4)
    adicionar_texto(axs[1], estatistica.index, estatistica['Desvio'].values)

    plt.tight_layout()
    plt.savefig('C:/Users/T-GAMER/OneDrive/Imagens/Variancia e Desvio')

def boxplot(dados_lista):
    df = transformar_dados(dados_lista)
    plt.figure(figsize=(12, 6))
    df.boxplot(vert=False)
    plt.title('Boxplot das Contagens de Categorias')
    plt.xlabel('Contagens')
    plt.xticks(rotation=90)
    plt.savefig('C:/Users/T-GAMER/OneDrive/Imagens/Boxplot')