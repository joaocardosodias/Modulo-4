# Explicação Técnica do Código RC do Arduino

## 1️ Controle do Circuito RC
- O circuito é formado por um **resistor (R)** e um **capacitor (C) em série**.
- O Arduino controla o carregamento do capacitor pelo pino digital `pinResistor`:
  - `HIGH` → aplica 5 V ao resistor, fazendo o capacitor **carregar**.
  - `LOW` → desconecta a tensão, permitindo que o capacitor **descarregue**.
- A constante de tempo do circuito é:
\[
\tau = R \cdot C
\]  
Ela determina a rapidez com que o capacitor carrega ou descarrega.

## 2️ Leitura da Tensão
- O pino analógico `pinCapacitor` lê a tensão no capacitor usando `analogRead()`.  
- O valor lido é de 0 a 1023 (resolução de 10 bits do Arduino).  
- Conversão para tensão real:
\[
V_C = \frac{\text{leitura}}{1023} \cdot V_{ref}
\]  
- A tensão no resistor é calculada por diferença:
\[
V_R = V_{ref} - V_C
\]  
Isso segue a **Lei de Kirchhoff**, onde a tensão da fonte se divide entre resistor e capacitor.

## 3️ Registro no Tempo
- `millis()` mede o tempo desde o início do carregamento.  
- Cada leitura é registrada com:
  - Tempo em milissegundos
  - Tensão do capacitor \(V_C\)
  - Tensão no resistor \(V_R\)
- `delay(400)` faz a medição a cada 0,4 s, gerando uma série temporal de dados.
## 4️ Ciclo de Carregamento e Descarregamento
- Após 5 s:
  1. `pinResistor = LOW` → inicia o **descarregamento**.
  2. `delay(2000)` → aguarda 2 s para descarregar quase totalmente.
  3. `pinResistor = HIGH` → reinicia o **novo ciclo de carregamento**.
- `startTime` é resetado para calcular o tempo do novo ciclo.

## 5️ Resultado Prático
- O Serial Monitor exibe uma tabela de **tempo x tensão**, permitindo:
  - Plotar gráficos \(V_C(t)\) e \(V_R(t)\)
  - Observar o crescimento exponencial da tensão no capacitor durante o carregamento:
\[
V_C(t) = V_{ref} \left(1 - e^{-t/RC}\right)
\]  
  - Observar a queda exponencial durante o descarregamento:
\[
V_C(t) = V_{ref} \, e^{-t/RC}
\]  
- Isso permite **determinar experimentalmente a constante de tempo \(\tau\)** do circuito.
