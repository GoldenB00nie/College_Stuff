import time
start = time.time()
print("Começou o tempo.")

import importar_steamspy as imp_spy
import graficos

dados_lista = imp_spy.dados_lista
imp_spy.clear()
print("Dados coletados com sucesso!\n\n")
#print("\n\n\n", dados_lista['Lista']['2024']['Meses']['11']['Dias']['30']['CountDia'])

graficos.definir_tipo("ListaAnos", "2015", "04", "20")
graficos.total_categorias(dados_lista)
graficos.medidas_centralidade(dados_lista)
graficos.variancia_desvio(dados_lista)
graficos.amplitude(dados_lista)
graficos.boxplot(dados_lista)

finish = time.time()
tempo_total = finish - start
print(f"Tempo de atividade em segundos: {tempo_total}")
print(f"Tempo de atividade em minutos: {tempo_total/60}")
print(f"Tempo de atividade em horas: {tempo_total/3600}")

with open("dados coletados(2019-2024).txt", 'w', encoding='utf-8') as file:
    file.write(f"{dados_lista}")
    file.close()