import requests
import json
import time

AUTH_URL = 'http://127.0.0.1:5000/login'
DATA_URL = 'http://127.0.0.1:5001/protected'
TOKEN = None # Variável global para armazenar o token

# --- Funções de Teste ---

def test_login_sucesso(username, password):
    global TOKEN
    print(f"\n==============================================")
    print(f"--- TESTE 1: LOGIN BEM-SUCEDIDO ({username}) ---")
    print(f"==============================================")
    
    payload = {'username': username, 'password': password}
    
    try:
        # Requisição POST para a API de Autenticação (porta 5000)
        response = requests.post(AUTH_URL, json=payload)
        
        print(f"Status Login: {response.status_code}")
        print(f"Resposta: {response.json()}")
        
        if response.status_code == 200:
            TOKEN = response.json().get('token')
            print(f"Token Recebido (Verificado?): {'SIM' if TOKEN else 'NÃO'}")
            return True
        else:
            print("Login falhou inesperadamente.")
            return False
            
    except requests.exceptions.ConnectionError:
        print("ERRO: Certifique-se de que a API de Autenticação (5000) está em execução.")
        return False
    except Exception as e:
        print(f"Ocorreu um erro durante o login: {e}")
        return False


def test_acesso_protegido(token, test_name):
    print(f"\n--- {test_name}: Acesso a Dados Protegidos ---")
    
    if token is None:
        # Se o token for None, envia sem o cabeçalho Authorization (Teste 4.1)
        headers = {}
        print("Tentando acesso SEM TOKEN...")
    else:
        # Envia o token no formato Bearer
        headers = {'Authorization': f'Bearer {token}'}
        print("Tentando acesso COM TOKEN...")

    try:
        # Requisição GET para a API de Dados Protegidos (porta 5001)
        response = requests.get(DATA_URL, headers=headers)
        
        print(f"Status Acesso: {response.status_code}")
        print(f"Resposta: {response.json()}")
        return response
    except requests.exceptions.ConnectionError:
        print("ERRO: Certifique-se de que a API de Dados (5001) está em execução.")
        return None


def test_expiracao(tempo_espera):
    global TOKEN
    print(f"\n=======================================================")
    print(f"--- TESTE 3: TOKEN EXPIRADO (Espera de {tempo_espera}s) ---")
    print(f"=======================================================")

    if not TOKEN:
        print("[AVISO] Teste 3 pulado, pois nenhum token foi obtido no Teste 1.")
        return

    print(f"1. Aguardando {tempo_espera} segundos para o token expirar...")
    time.sleep(tempo_espera) # Pausa o script
    
    # Tentativa de acesso com o token expirado
    test_acesso_protegido(TOKEN, "Teste 3: Acesso Pós-Expiração")


def test_token_invalido():
    print(f"\n==============================================")
    print(f"--- TESTE 4: TOKEN INVÁLIDO OU AUSENTE ---")
    print(f"==============================================")
    
    # Teste 4.1: Acesso Sem Token (Passa None como token)
    test_acesso_protegido(None, "Teste 4.1: Acesso Sem Token")

    # Teste 4.2: Token Inválido/Adulterado
    if TOKEN:
        # Adulterar a assinatura (últimos 4 caracteres)
        token_adulterado = TOKEN[:-4] + 'JUNK' 
        print("\n--- Teste 4.2: Acesso com Token Adulterado (Assinatura Inválida) ---")
        test_acesso_protegido(token_adulterado, "Teste 4.2: Token Adulterado")
    else:
        print("[AVISO] Teste 4.2 pulado, pois nenhum token de base foi obtido.")


# --- Execução dos Testes ---
if __name__ == '__main__':
    # =========================================================================
    # CONFIGURAÇÃO DE AMBIENTE NECESSÁRIA ANTES DE EXECUTAR:
    # 1. Terminal 1: python auth_api_expiracao.py (Porta 5000, Expiração 10s)
    # 2. Terminal 2: python data_api.py (Porta 5001)
    # =========================================================================
    
    # TESTE 1: Login Bem-sucedido
    if test_login_sucesso("usuario1", "senha123"):
        
        # TESTE 2: Acesso a Dados Protegidos (IMEDIATAMENTE após login, token VÁLIDO)
        test_acesso_protegido(TOKEN, "TESTE 2: ACESSO COM TOKEN VÁLIDO")

        # TESTE 3: Token Expirado (O script fará a pausa de 11 segundos)
        test_expiracao(11)
        
    # TESTE 4: Token Inválido ou Ausente (Pode ser feito independente do Teste 1)
    test_token_invalido()
    
    print("\n==============================================")
    print("--- FIM DOS TESTES AUTOMATIZADOS ---")
    print("==============================================")