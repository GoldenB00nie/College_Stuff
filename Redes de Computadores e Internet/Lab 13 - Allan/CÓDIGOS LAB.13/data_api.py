from flask import Flask, request, jsonify
import jwt
from functools import wraps
import requests # Para o cliente

app = Flask(__name__)
# CHAVE SECRETA: Deve ser A MESMA da API de Autenticação
app.config['SECRET_KEY'] = 'chave_secreta_super_segura_123' 

# Decorator para Proteger Rotas
def token_required(f):
    @wraps(f)
    def decorated(*args, **kwargs):
        token = None
        
        # O token é esperado no cabeçalho Authorization como 'Bearer <token>'
        if 'Authorization' in request.headers:
            auth_header = request.headers['Authorization']
            try:
                # Separa 'Bearer' do token
                token = auth_header.split(" ")[1] 
            except IndexError:
                # Caso o formato não seja 'Bearer <token>'
                return jsonify({'msg': 'Token inválido ou ausente no cabeçalho Authorization'}), 403

        if not token:
            return jsonify({'msg': 'Token não fornecido'}), 401

        try:
            # Tenta decodificar/validar o token
            data = jwt.decode(token, app.config['SECRET_KEY'], algorithms=['HS256'])
            current_user = data['sub']
        except jwt.ExpiredSignatureError:
            # Erro específico para token expirado
            return jsonify({'msg': 'Token expirado. Por favor, faça login novamente.'}), 401
        except jwt.InvalidSignatureError:
            # Erro específico para assinatura inválida
            return jsonify({'msg': 'Assinatura do token inválida. Token adulterado ou chave incorreta.'}), 401
        except jwt.InvalidTokenError:
            # Outros erros de token (formato, etc)
            return jsonify({'msg': 'Token inválido'}), 401

        return f(current_user, *args, **kwargs)

    return decorated

# Rota Protegida
@app.route('/protected', methods=['GET'])
@token_required
def protected_data(current_user):
    # Retorna dados específicos baseados no usuário autenticado (Teste 2)
    data = {
        'usuario1': 'Detalhes de conta e histórico de pedidos do usuario1.',
        'usuario2': 'Relatórios e estatísticas do usuario2.'
    }
    
    return jsonify({
        'msg': f'Acesso concedido para: {current_user}',
        'data': data.get(current_user, 'Dados genéricos.')
    }), 200

if __name__ == '__main__':
    app.run(port=5001, debug=True)