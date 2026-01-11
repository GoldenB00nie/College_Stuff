# api_produtos.py
from flask import Flask, jsonify, request

app = Flask(__name__)

# Simulação de um banco de dados de produtos
produtos = [
    {"id": 101, "nome": "Notebook", "preco": 3500.00},
    {"id": 102, "nome": "Mouse Sem Fio", "preco": 120.50}
]
next_id = 103

# --- Rota GET (Listar Todos) e POST (Criar) ... (mantidas) ---
@app.route('/produtos', methods=['GET'])
def listar_produtos():
    """Endpoint para listar todos os produtos."""
    return jsonify(produtos), 200

@app.route('/produtos', methods=['POST'])
def cadastrar_produto():
    """Endpoint para cadastrar um novo produto."""
    global next_id
    novo_produto_data = request.get_json()

    if not novo_produto_data or 'nome' not in novo_produto_data or 'preco' not in novo_produto_data:
        return jsonify({"erro": "Dados inválidos. 'nome' e 'preco' são obrigatórios."}), 400

    novo_produto = {
        "id": next_id,
        "nome": novo_produto_data['nome'],
        "preco": novo_produto_data['preco']
    }
    
    produtos.append(novo_produto)
    next_id += 1
    return jsonify(novo_produto), 201

# --- Rota GET por ID e PUT (Atualizar) ... (mantidas) ---
@app.route('/produtos/<int:produto_id>', methods=['GET'])
def buscar_produto(produto_id):
    """Endpoint para buscar um produto pelo ID."""
    for produto in produtos:
        if produto['id'] == produto_id:
            return jsonify(produto), 200
    return jsonify({"erro": "Produto não encontrado."}), 404

@app.route('/produtos/<int:produto_id>', methods=['PUT'])
def atualizar_produto(produto_id):
    """Endpoint para atualizar um produto pelo ID."""
    dados_atualizados = request.get_json()

    if not dados_atualizados or ('nome' not in dados_atualizados and 'preco' not in dados_atualizados):
        return jsonify({"erro": "Dados inválidos. Forneça 'nome' e/ou 'preco' para atualizar."}), 400

    for produto in produtos:
        if produto['id'] == produto_id:
            if 'nome' in dados_atualizados:
                produto['nome'] = dados_atualizados['nome']
            if 'preco' in dados_atualizados:
                produto['preco'] = dados_atualizados['preco']
            return jsonify(produto), 200

    return jsonify({"erro": "Produto não encontrado."}), 404


# --- NOVO ENDPOINT: DELETE (Remover) ---
@app.route('/produtos/<int:produto_id>', methods=['DELETE'])
def remover_produto(produto_id):
    """Endpoint para remover um produto pelo ID."""
    global produtos
    
    produtos_antes = len(produtos)
    produtos = [p for p in produtos if p['id'] != produto_id]
    
    produtos_depois = len(produtos)

    if produtos_depois < produtos_antes:
        # 204 No Content: O padrão para DELETE bem-sucedido
        return '', 204 
    else:
        # 404 Not Found
        return jsonify({"erro": "Produto não encontrado."}), 404


if __name__ == '__main__':
    app.run(port=5002, debug=True)
