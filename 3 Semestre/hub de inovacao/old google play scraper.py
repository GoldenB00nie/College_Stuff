import multiprocessing
from google_play_scraper import Sort, reviews_all
import nltk

from nltk.sentiment import SentimentIntensityAnalyzer
nltk.download('vader_lexicon')

def getReviews():
    result = reviews_all(
        'com.fantome.penguinisle',
        sleep_milliseconds=0,  # defaults to 0
        lang='en',  # defaults to 'en'
        country='us',  # defaults to 'us'
        sort=Sort.RATING,  # defaults to Sort.MOST_RELEVANT
        filter_score_with=1 # defaults to None (means all score)
    )
    return result

def processarComentario(comentario):
    if 'content' in comentario and comentario['content'] is not None:
        palavras_chave = ['cancel', 'cant', 'trial', 'end', "can't cancel", "cant cancel", "cannot cancel", "unable to cancel",
    "won't cancel", "cancel won't go through", "won't let me cancel",
    "can't stop", "stuck with", "cancel keeps failing",
    "impossible to cancel", "problem cancelling", "trouble cancelling",
    "difficulty cancelling", "can't end", "cannot end",
    "cannot stop", "never cancels", "cancel button not working",
    "clicking cancel does nothing", "cancel link broken",
    "service won't end", "ended but still charge", "account still active",
    "cancel request ignored", "cancel request denied",
    "asking to cancel but no response", "cancel subscription", "can't cancel subscription", "cant cancel subscription",
    "cannot cancel subscription", "unable to cancel subscription",
    "won't cancel subscription", "subscription won't cancel",
    "subscription keeps renewing", "subscription never ends",
    "subscription does not cancel",  "unsubscribe", "can't unsubscribe", "cant unsubscribe", "cannot unsubscribe",
    "unable to unsubscribe", "unsubscribe won't work", "unsubscribe link broken",
    "unsubscribe request denied", "unsubscribe keeps failing",
    "trouble unsubscribing", "difficulty unsubscribing", "never unsubscribes", "kept charging", "still charged", "keeps billing", "keeps charging me", "charge stuck", 
    "charged fee after cancel", "charged after cancel", "charg* after cancel", "subscription", "account", "membership", "service", "plan", "trial", "auto-renew", "renewal"]
        linhas_enganosas = []
        sia = SentimentIntensityAnalyzer()

        conteudo = comentario['content'].lower()
        if any(palavra in conteudo for palavra in palavras_chave):
            linhas_enganosas.append(comentario['content'])
        elif sia.polarity_scores(comentario['content'])['compound'] < 0:
            linhas_enganosas.append(comentario['content'])

        return '\n'.join(linhas_enganosas) if linhas_enganosas else None
    else:
        return None

def processarComentariosPool(nucleos):
    pool = multiprocessing.Pool(processes=nucleos)
    resultado_processado = [linha for linha in pool.map(processarComentario, getReviews()) if linha is not None]
    pool.close()
    pool.join()
    return resultado_processado

def escreverComentariosProcessados(resultado_processado):
    with open('comentariosProcessados.txt', 'w') as f:
        for linha in resultado_processado:
            if linha is not None and len(linha) > 0:
                f.write(linha + '\n')

if __name__ == '__main__':
    nucleos = multiprocessing.cpu_count()  # Utilize o número de núcleos disponíveis
    resultado_processado = processarComentariosPool(nucleos)
    escreverComentariosProcessados(resultado_processado)