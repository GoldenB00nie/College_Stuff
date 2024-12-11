import pandas as pd
import matplotlib.pyplot as plt

dados = {'CountLista': {'Action': 2643, 'Adventure': 2195, 'RPG': 1537, 'Indie': 2718, 'Early Access': 474, 'Simulation': 1551, 'Sports': 156, 'Casual': 974, 'Racing': 134, 'Massively Multiplayer': 181, 'Strategy': 1414, 'Free To Play': 215, 'Animation & Modeling': 2, 'Audio Production': 3, 'Design & Illustration': 1, 'Utilities': 14}}

df = pd.DataFrame(dados)
df = df.apply(pd.to_numeric, errors='coerce')

