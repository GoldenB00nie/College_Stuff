import requests
import json
import time

AUTH_URL = 'http://127.0.0.1:5000/login'
DATA_URL = 'http://127.0.0.1:5001/protected'
TOKEN = None # Variável global para armazenar o token

# --- Funções de Teste ---

def test_login_sucesso(username, password):
    global TOKEN
    print(f"\n--- Teste 1: Tentativa de Login para {username} ---")
    payload = {'username': username, 'password': password}
    try:
        response = requests.post(AUTH_URL, json=payload)
        print(f"Status Login: {response.status_code}")
        print(f"Resposta: {response.json()}")
        
        if response.status_code == 200:
            TOKEN = response.json().get('token')
            print(f"Token Recebido (Verificado?): {'Sim' if TOKEN else 'Não'}")
            return True
    except requests.exceptions.ConnectionError:
        print("ERRO: Certifique-se de que a API de Autenticação (5000) está em execução.")
    return False

def test_acesso_protegido(token):
    print("\n--- Teste 2: Acesso a Dados Protegidos ---")
    headers = {'Authorization': f'Bearer {token}'}
    try:
        response = requests.get(DATA_URL, headers=headers)
        print(f"Status Acesso: {response.status_code}")
        print(f"Resposta: {response.json()}")
        return response
    except requests.exceptions.ConnectionError:
        print("ERRO: Certifique-se de que a API de Dados (5001) está em execução.")
    return None

def test_expiracao_token(tempo_espera):
    print(f"\n--- Teste 3: Token Expirado (Aguardando {tempo_espera} segundos) ---")
    print(f"Aguardando {tempo_espera} segundos...")
    time.sleep(tempo_espera) # Aguarda o tempo de expiração
    
    print("Tentando acessar dados protegidos com token expirado...")
    test_acesso_protegido(TOKEN)

def test_token_invalido():
    print("\n--- Teste 4.1: Acesso Sem Token ---")
    try:
        # Acesso sem o cabeçalho Authorization
        response = requests.get(DATA_URL)
        print(f"Status Acesso: {response.status_code}")
        print(f"Resposta: {response.json()}")
    except requests.exceptions.ConnectionError:
        print("ERRO: Certifique-se de que a API de Dados (5001) está em execução.")

    print("\n--- Teste 4.2: Acesso com Token Inválido (Modificado) ---")
    # Altera um caractere no token para invalidar a assinatura
    if TOKEN:
        token_adulterado = TOKEN[:-4] + 'AAAA' 
        test_acesso_protegido(token_adulterado)
    else:
        print("Não foi possível realizar o teste 4.2: Token de sucesso não gerado.")

# --- Execução dos Testes ---
if __name__ == '__main__':
    # Certifique-se de executar as APIs 5000 e 5001 ANTES de rodar o cliente!
    
    # TESTE 1: Login Bem-sucedido
    if test_login_sucesso("usuario1", "senha123"):
        # TESTE 2: Acesso a Dados Protegidos
        test_acesso_protegido(TOKEN)
    
    # Requer que você reinicie a API de Autenticação com app.config['JWT_EXPIRATION_SECONDS'] = 10
    # TESTE 3: Token Expirado
    # test_login_sucesso("usuario1", "senha123") # Novo login com token de 10s
    # test_expiracao_token(11) # Aguarda 11 segundos
    
    # TESTE 4: Token Inválido
    test_token_invalido()