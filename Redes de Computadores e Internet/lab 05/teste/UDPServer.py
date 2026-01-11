from socket import *

portaServidor = 12345
socketServer = socket(AF_INET, SOCK_DGRAM)
socketServer.bind(("", portaServidor))
print("O servidor está pronto para receber requests")

while(True):
    mensagem, enderecoServer = socketServer.recvfrom(2048)
    msgMod = mensagem.decode().upper()
    socketServer.sendto(msgMod.encode(), enderecoServer)