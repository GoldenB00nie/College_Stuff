import simpy
import random

class Paciente:
    def __init__(self, env, tipo, idade):
        self.env = env
        self.tipo = tipo
        self.idade = idade
        self.chegada = env.now

class FilaTransplante:
    def __init__(self, env):
        self.env = env
        self.pacientes = []
    
    def adicionar(self, paciente):
        self.pacientes.append(paciente)
        self.pacientes.sort(key=lambda x: x.idade, reverse=True)  # Ordena por idade (prioridade)

    def remover(self):
        if self.pacientes:
            paciente = self.pacientes.pop(0)
            print(f"{self.env.now}: Paciente removido: Tipo: {paciente.tipo}, Idade: {paciente.idade}")
        else:
            print(f"{self.env.now}: Fila vazia!")

def processo(env, fila):
    while True:
        tipo = random.choice(["CORAÇÃO", "CÓRNEA", "MEDULA"])
        idade = random.randint(20, 80)
        paciente = Paciente(env, tipo, idade)
        print(f"{env.now}: Paciente adicionado: Tipo: {paciente.tipo}, Idade: {paciente.idade}")
        fila.adicionar(paciente)
        
        # Simula um intervalo aleatório entre as inserções
        yield env.timeout(random.randint(1, 3))
        
        # Simula a remoção de um paciente aleatório da fila
        fila.remover()
        yield env.timeout(random.randint(1, 3))

# Configurando o ambiente
env = simpy.Environment()
fila = FilaTransplante(env)
env.process(processo(env, fila))

# Executando a simulação por um período de tempo
env.run(until=20)
