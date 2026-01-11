from socket import *
import base64

portaServidor = 12345
socketServer = socket(AF_INET, SOCK_DGRAM)
socketServer.bind(("", portaServidor))
print("O servidor está pronto para receber requests")

while(True):
    mensagem, enderecoServer = socketServer.recvfrom(2048)
    b = base64.b64encode(bytes(mensagem.decode(), 'utf-8'))
    msgMod = b.decode('utf-8')
    socketServer.sendto(msgMod.encode(), enderecoServer)