from flask import Flask, request, jsonify
import jwt
import datetime
import time

app = Flask(__name__)
# CHAVE SECRETA: Use uma chave forte e armazene em variável de ambiente (.env)
app.config['SECRET_KEY'] = 'chave_secreta_super_segura_123' 
app.config['JWT_EXPIRATION_SECONDS'] = 10 # Default: 5 minutos

# Usuários simulados (em um ambiente real, estaria em um DB)
USERS = {
    "usuario1": "senha123",
    "usuario2": "outrasenha"
}

# Rota 1: Login
@app.route('/login', methods=['POST'])
def login():
    data = request.get_json()
    username = data.get('username')
    password = data.get('password')

    # 1. Validação de Credenciais
    if username in USERS and USERS[username] == password:
        # 2. Geração do Payload do JWT
        tempo_expiracao = datetime.datetime.utcnow() + datetime.timedelta(seconds=app.config['JWT_EXPIRATION_SECONDS'])
        
        payload = {
            'exp': tempo_expiracao,
            'iat': datetime.datetime.utcnow(),
            'sub': username,  # Assunto: Identificador do usuário
            'role': 'user'  # Exemplo de claim de permissão
        }
        
        # 3. Codificação do JWT (Criação do token assinado)
        token = jwt.encode(payload, app.config['SECRET_KEY'], algorithm='HS256')
        
        return jsonify({'token': token}), 200
    else:
        return jsonify({'msg': 'Credenciais inválidas'}), 401

if __name__ == '__main__':
    # Modificar para o Teste 3: Token Expirado (10 segundos)
    # app.config['JWT_EXPIRATION_SECONDS'] = 10 
    app.run(port=5000, debug=True)