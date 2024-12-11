import ctypes
#import simpy
import random

""" OBS: Eu não sabia se era para usar o simpy para fazer o programa e tentei fazer com ele, mas não consegui
então fiz normal.

cliente chega
entra na fila
espera ser atendido
é atendido
sai
"""

"""def Paciente(env, fila, id_paciente, atendimentos):
    chegada = env.now
    with atendimentos.request() as pedido:
        yield pedido # Espera o caixa ser liberado
        remove_fila(fila)
        tempo_espera = env.now - chegada
        print(f"O paciente {id_paciente} foi atendido em t = {env.now}, depois de esperar t = {tempo_espera}")

        yield env.timeout(random.randrange(5, 16)) # Espera o tempo do atendimento
        print(f"O paciente {id_paciente} terminou o atendimento em t = {env.now}")

def gera_paciente(env, fila, atendimentos):
    for id_paciente in range(1, 6):
        idade_paciente = random.randint(1, 80)
        yield env.timeout(1)
        chegada = env.now
        print(f"O paciente {id_paciente} chegou em t = {chegada}")
        insere_fila(fila, id_paciente, idade_paciente)

        id_inicio = id_inicio_fila(fila)
        env.process(Paciente(env, fila, id_inicio, atendimentos))
        imprime_fila(fila, 0)
"""
lib = ctypes.CDLL('./libfila.dll')
lib.cria_fila.restype = ctypes.POINTER(ctypes.c_void_p)
lib.insere_fila.argtype = [ctypes.POINTER(ctypes.c_void_p), ctypes.c_int, ctypes.c_int]
lib.remove_fila.argtype = [ctypes.POINTER(ctypes.c_void_p)]
lib.remove_fila.restype = ctypes.c_int
lib.idade_inicio_fila.argtypes = [ctypes.POINTER(ctypes.c_void_p)]
lib.idade_inicio_fila.restype = ctypes.c_int
lib.id_inicio_fila.argtypes = [ctypes.POINTER(ctypes.c_void_p)]
lib.id_inicio_fila.restype = ctypes.c_int
lib.imprime_fila.argtype = [ctypes.POINTER(ctypes.c_void_p), ctypes.c_int]

fila = lib.cria_fila()

def insere_fila(fila, id, idade):
    lib.insere_fila(fila, id, idade)
def idade_inicio_fila(fila):
    return lib.idade_inicio_fila(fila)
def id_inicio_fila(fila):
    return lib.id_inicio_fila(fila)
def remove_fila(fila):
    lib.remove_fila(fila)
def imprime_fila(fila, tipo):
    lib.imprime_fila(fila, tipo)
# Configuração do ambiente de simulação
#env = simpy.Environment()
#atendimentos = simpy.Resource(env, capacity=1)
#env.process(gera_paciente(env, fila, atendimentos))
#env.run()

id = 0
for num_clientes in range(20):
    id += 1
    idade = random.randint(20, 80)
    insere_fila(fila, id, idade)
imprime_fila(fila, 0) # 0 para todos, 1 para fila do coracao, 2 para fila da cornea, 3 para fila da medula
print("\n\n---------------------------------\n\n")

for num_remocoes in range(10):
    remove_fila(fila)
imprime_fila(fila, 0)


#valor = lib.remove_fila(fila)
#lib.imprime_fila(fila)