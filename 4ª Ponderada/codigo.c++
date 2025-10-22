
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>


const int VAZAO_PIN   = 34;
const int T_IDA_PIN   = 35;
const int T_RETORNO_PIN = 32;

const int RED_PIN     = 12;
const int GREEN_PIN   = 13;
const int BLUE_PIN    = 14; 
const int BUZZER_PIN  = 27;
const int BUTTON_PIN  = 25;

#define TFT_CS    15
#define TFT_DC    2
#define TFT_RST   4
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);


enum DeviceState {
  NORMAL,
  WARNING,
  ERROR
};


class StatusMonitor {
private:
  DeviceState _currentState;
  unsigned long _lastBlinkTime = 0;
  unsigned long _lastBeepTime = 0;
  bool _ledState = false;
  bool buzzerMuted = false;

  void _setLedColor(int red, int green, int blue) {
    digitalWrite(RED_PIN, red > 0 ? HIGH : LOW);
    digitalWrite(GREEN_PIN, green > 0 ? HIGH : LOW);
    digitalWrite(BLUE_PIN, blue > 0 ? HIGH : LOW);
  }

public:
  StatusMonitor() { _currentState = NORMAL; }

  void begin() {
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.println("HMI Inicializada.");
    updateHMI();
  }

  void setState(DeviceState newState) {
    if (_currentState == newState) return;
    _currentState = newState;
    _lastBlinkTime = 0;
    _lastBeepTime = 0;
    _ledState = false;
    if (_currentState == ERROR || _currentState == WARNING) {
      buzzerMuted = false;
    }
    if (_currentState == NORMAL) { 
      digitalWrite(BUZZER_PIN, LOW);
      buzzerMuted = false;
    }
    Serial.print("HMI Estado: ");
    if (_currentState == NORMAL) Serial.println("NORMAL");
    else if (_currentState == WARNING) Serial.println("ATENCAO");
    else Serial.println("ERRO");
    updateHMI();
  }

  void muteBuzzer() {
    buzzerMuted = true;
    digitalWrite(BUZZER_PIN, LOW);
  }

  DeviceState getState() { return _currentState; }

  void updateHMI() {
    unsigned long currentTime = millis();
    switch (_currentState) {
      case NORMAL:
        _setLedColor(0, 255, 0);
        digitalWrite(BUZZER_PIN, LOW);
        break;
      case WARNING:
        
        if (currentTime - _lastBlinkTime > 500) {
          _lastBlinkTime = currentTime;
          _ledState = !_ledState;
          if (_ledState) _setLedColor(255, 255, 0);
          else _setLedColor(0, 0, 0);
        }
        
        if (!buzzerMuted && (currentTime - _lastBeepTime > 2000)) {
          _lastBeepTime = currentTime;
          tone(BUZZER_PIN, 700, 150); 
        }
        break;
      case ERROR:
        
        _setLedColor(255, 0, 0);
        if (!buzzerMuted) {
          tone(BUZZER_PIN, 500, 450);
        }
        break;
    }
  }
};

StatusMonitor hmiMonitor;


float vazaoLPM = 0.0;
float tempIdaC = 0.0;
float tempRetornoC = 0.0;
float potenciaKW = 0.0;


void readSensors() {
  int rawVazao    = analogRead(VAZAO_PIN);
  int rawTIda     = analogRead(T_IDA_PIN);
  int rawTRetorno = analogRead(T_RETORNO_PIN);
  vazaoLPM        = map(rawVazao,    0, 4095, 0, 100);
  tempIdaC        = map(rawTIda,     0, 4095, 20, 90);
  tempRetornoC    = map(rawTRetorno, 0, 4095, 20, 90);
}

void calculatePower() {
  float deltaT   = tempIdaC - tempRetornoC;
  float vazaoLPS = vazaoLPM / 60.0;

  if (deltaT <= 0 || vazaoLPS < 0) {
    potenciaKW = 0.0;
    hmiMonitor.setState(ERROR);
  } 
  else if (deltaT > 0 && deltaT < 5.0) {
    potenciaKW = vazaoLPS * deltaT * 4.184;
    hmiMonitor.setState(WARNING);
  }
  else {
    potenciaKW = vazaoLPS * deltaT * 4.184;
    hmiMonitor.setState(NORMAL);
  }
}

void updateTFT() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);

  tft.print("Vazao: ");
  tft.print(vazaoLPM, 1);
  tft.println(" L/m");

  tft.print("T_Ida: ");
  tft.print(tempIdaC, 1);
  tft.println(" C");

  tft.print("T_Rtrn:");
  tft.print(tempRetornoC, 1);
  tft.println(" C");
  tft.println("");

  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(3);
  tft.print(potenciaKW, 1);
  tft.println(" kW");
}


void setup() {
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("Inicializando...");
  delay(1000);
  hmiMonitor.begin();
  pinMode(VAZAO_PIN, INPUT);
  pinMode(T_IDA_PIN, INPUT);
  pinMode(T_RETORNO_PIN, INPUT);
}


void loop() {
  
  if (digitalRead(BUTTON_PIN) == LOW) {
    if (hmiMonitor.getState() == ERROR || hmiMonitor.getState() == WARNING) {
      hmiMonitor.muteBuzzer();
    }
  }

  readSensors();
  calculatePower();
  updateTFT();
  hmiMonitor.updateHMI();

  delay(100);
}
