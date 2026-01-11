# teste_cliente.py
import requests
import json

# --- Configurações das APIs ---
URL_USUARIOS = "http://localhost:5001/usuarios"
URL_PRODUTOS = "http://localhost:5002/produtos"
URL_PEDIDOS = "http://localhost:5003/pedidos"

# Variáveis para armazenar IDs criados dinamicamente
USUARIO_TESTE_ID = None
PRODUTO_TESTE_ID = None

def fazer_requisicao(metodo, url, payload=None):
    """Realiza uma requisição HTTP e exibe a resposta."""
    print(f"\n--- REQUISIÇÃO {metodo}: {url} ---")
    
    headers = {'Content-Type': 'application/json'}
    
    try:
        if metodo == 'GET':
            response = requests.get(url)
        elif metodo == 'POST':
            response = requests.post(url, json=payload, headers=headers)
        elif metodo == 'PUT':
            response = requests.put(url, json=payload, headers=headers)
        elif metodo == 'DELETE':
            response = requests.delete(url)
        else:
            print(f"Método {metodo} não suportado pela função de teste.")
            return None

        print(f"Status Code: {response.status_code}")
        
        # Trata as diferentes respostas
        if response.status_code in (200, 201):
            dados = response.json()
            print("Resposta JSON:")
            print(json.dumps(dados, indent=4, ensure_ascii=False))
            return dados
        elif response.status_code == 204:
            print("Recurso Removido (204 No Content).")
            return True
        elif response.status_code in (400, 404):
            dados = response.json()
            print(f"Erro Recebido ({response.status_code}): {dados.get('erro')}")
            return dados
        else:
            print(f"Resposta inesperada. Conteúdo: {response.text}")
            return None
            
    except requests.exceptions.ConnectionError:
        print(" ERRO DE CONEXÃO: Não foi possível conectar. Verifique se a API está rodando na porta correta.")
        return None

if __name__ == '__main__':
    print("======================================================")
    print(" INICIANDO TESTES COMPLETOS DO CLIENTE PYTHON (V2) ")
    print("======================================================")

    
    # -------------------------------------------------------------------
    # 1. TESTES DA API DE USUÁRIOS (CRUD Completo)
    # -------------------------------------------------------------------
    print("\n##### 1. TESTES DA API DE USUÁRIOS (localhost:5001) #####")
    
    # POST - Cadastrar novo usuário (necessário para testes de PUT/DELETE/PEDIDOS)
    novo_user_data = {"nome": "Teste Cliente", "email": "cliente@teste.com"}
    resultado_post = fazer_requisicao('POST', URL_USUARIOS, novo_user_data)
    if resultado_post and 'id' in resultado_post:
        USUARIO_TESTE_ID = resultado_post['id']
        print(f" Usuário de Teste Criado com ID: {USUARIO_TESTE_ID}")
    
    # GET por ID - Buscar o usuário recém-criado
    fazer_requisicao('GET', f"{URL_USUARIOS}/{USUARIO_TESTE_ID}")
    
    # PUT - Atualizar o usuário
    atualizacao_user = {"nome": "Cliente ATUALIZADO", "email": "novo.email@teste.com"}
    fazer_requisicao('PUT', f"{URL_USUARIOS}/{USUARIO_TESTE_ID}", atualizacao_user)
    
    # GET - Listar todos (para checar a atualização)
    fazer_requisicao('GET', URL_USUARIOS)
    
    
    # -------------------------------------------------------------------
    # 2. TESTES DA API DE PRODUTOS (CRUD Completo)
    # -------------------------------------------------------------------
    print("\n##### 2. TESTES DA API DE PRODUTOS (localhost:5002) #####")

    # POST - Cadastrar novo produto (necessário para testes de PUT/DELETE/PEDIDOS)
    novo_prod_data = {"nome": "Monitor de Teste", "preco": 1500.00}
    resultado_post = fazer_requisicao('POST', URL_PRODUTOS, novo_prod_data)
    if resultado_post and 'id' in resultado_post:
        PRODUTO_TESTE_ID = resultado_post['id']
        print(f"Produto de Teste Criado com ID: {PRODUTO_TESTE_ID}")

    # PUT - Atualizar o produto
    atualizacao_prod = {"preco": 1350.00}
    fazer_requisicao('PUT', f"{URL_PRODUTOS}/{PRODUTO_TESTE_ID}", atualizacao_prod)

    # DELETE - Remover um produto existente (Produto 102 deve existir)
    fazer_requisicao('DELETE', f"{URL_PRODUTOS}/102")


    # -------------------------------------------------------------------
    # 3. TESTES DA API DE PEDIDOS (Orquestração)
    # -------------------------------------------------------------------
    print("\n##### 3. TESTES DA API DE PEDIDOS (localhost:5003) - Orquestração #####")
    
    # TESTE DE SUCESSO: Cria pedido com os IDs recém-criados
    pedido_sucesso = {
        "usuario_id": USUARIO_TESTE_ID, 
        "itens": [ 
            {"produto_id": PRODUTO_TESTE_ID, "quantidade": 2},
            {"produto_id": 101, "quantidade": 1} # Produto 101 (Notebook)
        ]
    }
    fazer_requisicao('POST', URL_PEDIDOS, pedido_sucesso)

    # TESTE DE FALHA: Usuário Inexistente (999)
    pedido_falha_user = {
        "usuario_id": 999, 
        "itens": [{"produto_id": PRODUTO_TESTE_ID, "quantidade": 1}]
    }
    fazer_requisicao('POST', URL_PEDIDOS, pedido_falha_user)

    # TESTE DE FALHA: Produto Inexistente (999)
    pedido_falha_prod = {
        "usuario_id": USUARIO_TESTE_ID, 
        "itens": [{"produto_id": 999, "quantidade": 1}]
    }
    fazer_requisicao('POST', URL_PEDIDOS, pedido_falha_prod)

    # GET - Listar todos os pedidos
    fazer_requisicao('GET', URL_PEDIDOS)
    
    
    # -------------------------------------------------------------------
    # 4. LIMPEZA (DELETE Final)
    # -------------------------------------------------------------------
    print("\n##### 4. LIMPEZA DOS RECURSOS DE TESTE #####")
    if USUARIO_TESTE_ID:
        fazer_requisicao('DELETE', f"{URL_USUARIOS}/{USUARIO_TESTE_ID}")
    if PRODUTO_TESTE_ID:
        fazer_requisicao('DELETE', f"{URL_PRODUTOS}/{PRODUTO_TESTE_ID}")
