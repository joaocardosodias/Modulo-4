
##  Descrição Geral
O projeto tem como objetivo simular o funcionamento de um semáforo de trânsito utilizando LEDs, um Arduino UNO e resistores para limitar a corrente. O sistema acende os LEDs vermelho, amarelo e verde em sequência, representando as fases de parar, atenção e seguir.

A montagem foi realizada em protoboard, o que facilitou as conexões e testes. Os LEDs foram conectados a pinos digitais do Arduino, cada um com um resistor em série, e o GND comum foi ligado ao barramento negativo da protoboard.

##  Montagem e Conexões
- **LED vermelho**: conectado ao pino digital 8 do Arduino, em série com um resistor de 220 Ω até o GND.
- **LED amarelo**: conectado ao pino digital 9, também com resistor de 220 Ω.
- **LED verde**: conectado ao pino digital 10, com resistor de 220 Ω.
- **GND do Arduino**: ligado à linha negativa da protoboard (terra comum para todos os LEDs).
- **A porta USB**: foi usada para alimentar a placa e o circuito com 5V.

O programa foi escrito na IDE do Arduino e utiliza *delays* para controlar o tempo de cada fase do semáforo.

##  Lógica de Funcionamento
O código segue o ciclo:
1. Vermelho acende (parar) por 6 segundos.
2. Amarelo acende (atenção) por 2 segundos.
3. Verde acende (seguir) por 4 segundos.

Depois, o ciclo reinicia, criando o efeito contínuo de um semáforo real.

##  Tabela de Componentes
| Componente            | Quantidade | Especificação / Valor          | Função no Circuito                             |
|-----------------------|------------|--------------------------------|-----------------------------------------------|
| Arduino UNO R3        | 1          | 5V / 16 MHz / 14 pinos digitais | Controle lógico do sistema                   |
| LED Vermelho          | 1          | 2V / 20mA                     | Indica o sinal de "Parar"                     |
| LED Amarelo           | 1          | 2V / 20mA                     | Indica o sinal de "Atenção"                   |
| LED Verde             | 1          | 2V / 20mA                     | Indica o sinal de "Siga"                      |
| Resistores            | 3          | 220 Ω (1/4W)                  | Limita a corrente nos LEDs                    |
| Protoboard            | 1          | 400 pontos (ou mais)          | Facilita a montagem sem solda                 |
| Cabos Jumper          | 8        | Macho-Macho                   | Conexões entre Arduino e protoboard           |
| Cabo USB              | 1          | Tipo A-B                      | Alimentação e programação do Arduino          |