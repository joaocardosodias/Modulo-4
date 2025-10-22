import pandas as pd
import io
import matplotlib.pyplot as plt
import numpy as np

# Dados fornecidos pelo usuário em formato string
data = """tempo(ms)	Vresistor(V)	Vcapacitor(V)
1	5.00		0.00
402	3.34		1.66
804	2.23		2.77
1207	1.50		3.50
1608	1.00		4.00
2011	0.67		4.33
2413	0.45		4.55
2816	0.30		4.70
3218	0.20		4.80
3619	0.13		4.87
4022	0.09		4.91
4424	0.06		4.94
4827	0.04		4.96
5229	0.03		4.97
0	0.00		5.00"""


df = pd.read_csv(io.StringIO(data), sep=r'\s+', engine='python', skipinitialspace=True)

df = df.sort_values(by='tempo(ms)').reset_index(drop=True)

plt.figure(figsize=(10, 6))


plt.plot(
    df['tempo(ms)'], 
    df['Vresistor(V)'], 
    label='Vresistor (V)', 
    marker='o', 
    markersize=4, 
    linestyle='-'
)

# Plot Vcapacitor
plt.plot(
    df['tempo(ms)'], 
    df['Vcapacitor(V)'], 
    label='Vcapacitor (V)', 
    marker='x', 
    markersize=4, 
    linestyle='-'
)

# Configurações de Títulos e Eixos
plt.title('Carga/Descarga de Componente em Circuito RC', fontsize=16)
plt.xlabel('Tempo (ms)', fontsize=12)
plt.ylabel('Tensão (V)', fontsize=12)
plt.legend(title='Componente')
plt.grid(True, linestyle='--', alpha=0.7)


max_y = df[['Vresistor(V)', 'Vcapacitor(V)']].max().max()
plt.yticks(np.arange(0, max_y + 0.5, 0.5))
plt.xticks(rotation=45)
plt.tight_layout() 


plt.savefig('grafico_rc.png')

