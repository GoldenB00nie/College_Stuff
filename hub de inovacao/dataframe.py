import pandas as pd
import gspread
from gspread_dataframe import set_with_dataframe
from google.colab import auth
from google.auth import default

# Autenticando com a conta Google
auth.authenticate_user()
creds, _ = default()
gc = gspread.authorize(creds)

# Abrindo a planilha pelo nome
spreadsheet = gc.open("NomeDaSuaPlanilha")  # Substitua pelo nome real
worksheet = spreadsheet.sheet1

# Lendo o CSV
csv_path = '/content/seu_arquivo.csv'  # Altere para o caminho real do seu CSV
df_csv = pd.read_csv(csv_path)

# Lista para armazenar resultados processados
processed_data = []

# Processando linha por linha
for _, row in df_csv.iterrows():
    comment = row['comment']  # Substitua 'comment' pelo nome correto da coluna
    
    # Aqui entraria a lógica da IA
    abusive_status = "Abusive"  # ou "Non-Abusive" — substituam pela saída da IA
    dark_pattern_type = ""      # Vocês vão preencher esse campo depois
    status = "In Progress"      # Ou "Done", dependendo do estágio de revisão

    # Adicionando ao conjunto processado
    processed_data.append({
        "Comment": comment,
        "Abusive Status": abusive_status,
        "Dark Pattern Type": dark_pattern_type,
        "Review Status": status
    })

# Convertendo para DataFrame
df_processed = pd.DataFrame(processed_data)

# Escrevendo no Google Sheets
# Opcional: limpar planilha antes de escrever
worksheet.clear()

# Enviar o DataFrame para a planilha
set_with_dataframe(worksheet, df_processed)
