class Led {
  private:
    int pino;

  public:
    Led(int pino) {
      this->pino = pino;
      pinMode(pino, OUTPUT);
    }

    void acender() {
      digitalWrite(pino, HIGH);
    }

    void apagar() {
      digitalWrite(pino, LOW);
    }
};

class Semaforo {
  private:
    Led *vermelho;
    Led *amarelo;
    Led *verde;
    unsigned long tempoVermelho;
    unsigned long tempoAmarelo;
    unsigned long tempoVerde;

  public:
    Semaforo(Led *vermelho, Led *amarelo, Led *verde,
             unsigned long tempoVermelho,
             unsigned long tempoAmarelo,
             unsigned long tempoVerde) {
      this->vermelho = vermelho;
      this->amarelo = amarelo;
      this->verde = verde;
      this->tempoVermelho = tempoVermelho;
      this->tempoAmarelo = tempoAmarelo;
      this->tempoVerde = tempoVerde;
    }

    void ciclo() {
      vermelho->acender();
      delay(tempoVermelho);
      vermelho->apagar();

      verde->acender();
      delay(tempoVerde);
      verde->apagar();

      amarelo->acender();
      delay(tempoAmarelo);
      amarelo->apagar();
    }
};

const int pinoVermelho = 8;
const int pinoVerde = 9;
const int pinoAmarelo = 7;

Led *ledVermelho;
Led *ledVerde;
Led *ledAmarelo;
Semaforo *semaforo;

void setup() {
  ledVermelho = new Led(pinoVermelho);
  ledVerde = new Led(pinoVerde);
  ledAmarelo = new Led(pinoAmarelo);

  semaforo = new Semaforo(ledVermelho, ledAmarelo, ledVerde,
                          6000, 2000, 4000);
}

void loop() {
  semaforo->ciclo();
}
