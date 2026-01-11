# api_usuarios.py
from flask import Flask, jsonify, request

app = Flask(__name__)

# Simulação de um banco de dados de usuários
usuarios = [
    {"id": 1, "nome": "Alice Silva", "email": "alice.s@exemplo.com"},
    {"id": 2, "nome": "Bruno Costa", "email": "bruno.c@exemplo.com"}
]
next_id = 3

# --- Rota GET (Listar Todos) e POST (Criar) ... (mantidas) ---
@app.route('/usuarios', methods=['GET'])
def listar_usuarios():
    """Endpoint para listar todos os usuários."""
    return jsonify(usuarios), 200

@app.route('/usuarios', methods=['POST'])
def cadastrar_usuario():
    """Endpoint para cadastrar um novo usuário."""
    global next_id
    novo_usuario_data = request.get_json()

    if not novo_usuario_data or 'nome' not in novo_usuario_data or 'email' not in novo_usuario_data:
        return jsonify({"erro": "Dados inválidos. 'nome' e 'email' são obrigatórios."}), 400

    novo_usuario = {
        "id": next_id,
        "nome": novo_usuario_data['nome'],
        "email": novo_usuario_data['email']
    }
    
    usuarios.append(novo_usuario)
    next_id += 1
    return jsonify(novo_usuario), 201

# --- Rota GET por ID e PUT (Atualizar) ... (mantidas) ---
@app.route('/usuarios/<int:usuario_id>', methods=['GET'])
def buscar_usuario(usuario_id):
    """Endpoint para buscar um usuário pelo ID."""
    for usuario in usuarios:
        if usuario['id'] == usuario_id:
            return jsonify(usuario), 200
    return jsonify({"erro": "Usuário não encontrado."}), 404

@app.route('/usuarios/<int:usuario_id>', methods=['PUT'])
def atualizar_usuario(usuario_id):
    """Endpoint para atualizar um usuário pelo ID."""
    dados_atualizados = request.get_json()
    if not dados_atualizados or ('nome' not in dados_atualizados and 'email' not in dados_atualizados):
        return jsonify({"erro": "Dados inválidos. Forneça 'nome' e/ou 'email' para atualizar."}), 400

    for usuario in usuarios:
        if usuario['id'] == usuario_id:
            if 'nome' in dados_atualizados:
                usuario['nome'] = dados_atualizados['nome']
            if 'email' in dados_atualizados:
                usuario['email'] = dados_atualizados['email']
            return jsonify(usuario), 200

    return jsonify({"erro": "Usuário não encontrado."}), 404


# --- NOVO ENDPOINT: DELETE (Remover) ---
@app.route('/usuarios/<int:usuario_id>', methods=['DELETE'])
def remover_usuario(usuario_id):
    """Endpoint para remover um usuário pelo ID."""
    global usuarios
    
    # Cria uma nova lista, excluindo o usuário com o ID fornecido
    # Isso simula a remoção no "banco de dados"
    usuarios_antes = len(usuarios)
    usuarios = [u for u in usuarios if u['id'] != usuario_id]
    
    usuarios_depois = len(usuarios)

    if usuarios_depois < usuarios_antes:
        # 204 No Content: O padrão para DELETE bem-sucedido
        # (indica sucesso, mas não há conteúdo para retornar)
        return '', 204 
    else:
        # 404 Not Found
        return jsonify({"erro": "Usuário não encontrado."}), 404


if __name__ == '__main__':
    app.run(port=5001, debug=True)
