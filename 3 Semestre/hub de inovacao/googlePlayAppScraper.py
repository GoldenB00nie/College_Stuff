from google_play_scraper import Sort, reviews_all

def get_all_reviews(appId):
    result = reviews_all(
        app_id=appId,
        sleep_milliseconds=0,
        lang='en',
        country='us',
        sort=Sort.NEWEST, # Coletando os mais recentes, para não focar em rating
        filter_score_with=None # Coletando todos os scores
    )
    # Extrai apenas o conteúdo do comentário, se existir
    return [review['content'] for review in result if 'content' in review and review['content'] is not None]

def write_reviews_to_file(reviews, appId):
    filename = f"programs/dadosComentarios/{appId}.txt"
    with open(filename, 'w', encoding='utf-8') as f:
        for review in reviews:
            f.write(review + '\n')

def coletarComentarios(appId):
    print("Coletando comentários da Google Play Store...")
    all_comments = get_all_reviews(appId)
    
    print("Inserindo comentários no arquivo...")
    if all_comments:
        write_reviews_to_file(all_comments, appId)
        print(f"Total de {len(all_comments)} comentários coletados e salvos em '{appId}.txt'.")
        return f"programs/dadosComentarios/{appId}.txt"
    else:
        print("Nenhum comentário foi encontrado ou coletado.")
        return None