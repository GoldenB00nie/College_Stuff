# api_pedidos.py
from flask import Flask, jsonify, request
import requests

app = Flask(__name__)

# Configuração das URLs dos outros serviços
URL_USUARIOS = "http://localhost:5001/usuarios"
URL_PRODUTOS = "http://localhost:5002/produtos"

# Simulação de um banco de dados de pedidos
pedidos = []
next_id = 1

def buscar_recurso(url_base, item_id):
    """Tenta buscar um recurso (usuário ou produto) em outra API."""
    try:
        # A URL é construída com o ID do item, exemplo: http://localhost:5001/usuarios/1
        response = requests.get(f"{url_base}/{item_id}")
        if response.status_code == 200:
            return response.json()
        return None  # Retorna None se 404 Not Found, etc.
    except requests.exceptions.ConnectionError:
        # Erro de conexão (a outra API não está rodando)
        return {"erro": "Erro de conexão com o serviço externo. Verifique se a API está rodando."}

@app.route('/pedidos', methods=['POST'])
def criar_pedido():
    """Cria um novo pedido, orquestrando informações de Usuários (5001) e Produtos (5002)."""
    global next_id
    dados_pedido = request.get_json()

    # 1. Validação Básica de Estrutura
    if not dados_pedido or 'usuario_id' not in dados_pedido or 'itens' not in dados_pedido or not dados_pedido['itens']:
        return jsonify({"erro": "Dados inválidos. 'usuario_id' e 'itens' (lista não vazia) são obrigatórios."}), 400

    usuario_id = dados_pedido['usuario_id']
    
    # 2. VERIFICAÇÃO COM API DE USUÁRIOS (5001)
    usuario = buscar_recurso(URL_USUARIOS, usuario_id)
    if usuario is None or "erro" in usuario:
        mensagem = usuario.get("erro", "Usuário não encontrado.") if isinstance(usuario, dict) else "Usuário não encontrado."
        return jsonify({"erro": f"Falha ao criar pedido: {mensagem}"}), 404

    # 3. VERIFICAÇÃO COM API DE PRODUTOS (5002)
    itens_processados = []
    total_pedido = 0.0

    for item in dados_pedido['itens']:
        produto_id = item.get('produto_id')
        quantidade = item.get('quantidade')

        if not produto_id or not isinstance(quantidade, int) or quantidade <= 0:
            return jsonify({"erro": "Item inválido no pedido."}), 400

        produto = buscar_recurso(URL_PRODUTOS, produto_id)

        if produto is None or "erro" in produto:
            mensagem = produto.get("erro", f"Produto com ID {produto_id} não encontrado.") if isinstance(produto, dict) else f"Produto com ID {produto_id} não encontrado."
            return jsonify({"erro": f"Falha ao criar pedido: {mensagem}"}), 404

        # Cálculo
        subtotal = produto['preco'] * quantidade
        total_pedido += subtotal
        
        itens_processados.append({
            "produto_id": produto_id,
            "nome": produto['nome'],
            "quantidade": quantidade,
            "subtotal": subtotal
        })

    # 4. Criação do Pedido
    novo_pedido = {
        "id": next_id,
        "usuario_id": usuario_id,
        "nome_usuario": usuario['nome'],
        "total": round(total_pedido, 2),
        "itens": itens_processados
    }
    
    pedidos.append(novo_pedido)
    next_id += 1

    return jsonify(novo_pedido), 201

@app.route('/pedidos', methods=['GET'])
def listar_pedidos():
    """Endpoint para listar todos os pedidos."""
    return jsonify(pedidos), 200

if __name__ == '__main__':
    app.run(port=5003, debug=True)
