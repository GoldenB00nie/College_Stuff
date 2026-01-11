from socket import *
import base64
nomeServer = "localhost"
portaServer = 12345

socketCliente = socket(AF_INET, SOCK_DGRAM)
mensagem = input("Insira um texto em UTF-8: ")
socketCliente.sendto(mensagem.encode('utf-8'), (nomeServer, portaServer))
print("Mensagem enviada:\t", mensagem)

msgMod, serverAddress = socketCliente.recvfrom(2048)
print("\nMensagem recebida em base64:\t", msgMod.decode())

sampleBytes = base64.b64decode(msgMod)
msgDeco = sampleBytes.decode('utf-8')
print("Mensagem decodificada para UTF-8: ", msgDeco)

socketCliente.close()