import unicodedata
import re
from multiprocessing import Pool, cpu_count
import csv
import os

# Categorias com palavras-chave associadas
temas_enganosos = {
    "Can't cancel": [
        "can't cancel", "cant cancel", "cannot cancel", "unable to cancel",
        "won't cancel", "cancel won't go through", "won't let me cancel",
        "can't stop", "stuck with", "cancel keeps failing",
        "impossible to cancel", "problem cancelling", "trouble cancelling",
        "difficulty cancelling", "can't end", "cannot end",
        "cannot stop", "never cancels", "cancel button not working",
        "clicking cancel does nothing", "cancel link broken",
        "service won't end", "ended but still charge", "account still active",
        "cancel request ignored", "cancel request denied",
        "asking to cancel but no response", "no option to cancel",
        "hidden cancel button", "can't find cancel", "where to cancel",
        "how do i cancel", "how to cancel", "cancel account",
        "terminate account", "deactivate account", "remove account",
    ],
    "Cancel subscription": [
        "cancel subscription", "can't cancel subscription", "cant cancel subscription",
        "cancel my subscription", "can't cancel my subscription",
        "cant cancel my subscription", "cannot cancel my subscription",
        "unable to cancel my subscription",
        "cannot cancel subscription", "unable to cancel subscription",
        "won't cancel subscription", "subscription won't cancel",
        "subscription keeps renewing", "subscription never ends",
        "subscription does not cancel", "renewal trap",
        "subscription trap", "end my subscription", "stop my subscription",
        "stop subscription", "remove subscription", "subscription still active",
        "how do i cancel my subscription", "how to cancel subscription",
        "how to stop subscription", "can't find where to cancel subscription",
        "where do i cancel subscription", "where cancel subscription",
        "where stop subscription"
    ],
    "Unsubscribe": [
        "unsubscribe", "can't unsubscribe", "cant unsubscribe", "cannot unsubscribe",
        "unable to unsubscribe", "unsubscribe won't work", "unsubscribe link broken",
        "unsubscribe request denied", "unsubscribe keeps failing",
        "trouble unsubscribing", "difficulty unsubscribing", "never unsubscribes",
        "can't remove subscription", "can't stop subscription", "stop subscription",
        "unenroll", "opt out"
    ],
    "Billing or charge": [
        "kept charging", "still charged", "keeps billing", "keeps charging me", "charge stuck",
        "charged fee after cancel", "charged after cancel", "charged after ended",
        "billed after cancel", "charged despite cancel", "fradulent charges", "continued billing",
        "debit after cancel", "recurring charges"
    ]
}

def limpar_texto(texto):
    texto = unicodedata.normalize('NFKD', texto).encode('ASCII', 'ignore').decode('utf-8')
    texto = re.sub(r'[^\w\s]', '', texto)
    return texto.lower()

def categorizar_comentario(comentario):
    texto_limpo = limpar_texto(comentario)
    melhor_categoria = "Outros"
    max_correspondencias = 0

    for categoria, palavras in temas_enganosos.items():
        correspondencias = sum(1 for palavra in palavras if palavra in texto_limpo)
        if correspondencias > max_correspondencias:
            max_correspondencias = correspondencias
            melhor_categoria = categoria

    return (melhor_categoria, comentario)

def categorizeToCSV(input_path, appId):
    output_path = f"programs/dadosResumidos/{appId}.csv"

    if not os.path.exists(input_path):
        print(f"Arquivo {input_path} não encontrado.")
        exit()

    with open(input_path, "r", encoding="utf-8") as f:
        comentarios = [linha.strip() for linha in f if linha.strip()]

    print(f"Lidos {len(comentarios)} comentários para categorização.")

    with Pool(cpu_count()) as pool:
        resultados = pool.map(categorizar_comentario, comentarios)

    # Agrupando
    categorias_agrupadas = {categoria: [] for categoria in temas_enganosos.keys()}
    categorias_agrupadas["Outros"] = []

    for categoria, comentario in resultados:
        categorias_agrupadas[categoria].append(comentario)

    categorias_ordenadas = list(temas_enganosos.keys()) + ["Outros"]
    max_linhas = max(len(categorias_agrupadas[c]) for c in categorias_ordenadas)

    # Montar linhas
    linhas_csv = [categorias_ordenadas]  # Cabeçalho
    for i in range(max_linhas):
        linha = []
        for cat in categorias_ordenadas:
            if i < len(categorias_agrupadas[cat]):
                linha.append(categorias_agrupadas[cat][i])
            else:
                linha.append("")
        linhas_csv.append(linha)

    with open(output_path, "w", encoding="utf-8", newline="") as f:
        writer = csv.writer(f)
        writer.writerows(linhas_csv)

    print(f"Arquivo CSV gerado: {output_path}")