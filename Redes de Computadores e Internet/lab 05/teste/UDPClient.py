from socket import *
nomeServer = "localhost"
portaServer = 12345

socketCliente = socket(AF_INET, SOCK_DGRAM)
mensagem = input("Insira uma mensagem em letras minusculas: ")
socketCliente.sendto(mensagem.encode(), (nomeServer, portaServer))
msgMod, serverAddress = socketCliente.recvfrom(2048)
print(msgMod.decode())

socketCliente.close()