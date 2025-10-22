
const int pinResistor = 8;   
const int pinCapacitor = A0; 
const float Vref = 5.0;      
const int R = 10000;         
unsigned long startTime;

void setup() {
  Serial.begin(9600);
  pinMode(pinResistor, OUTPUT);
  digitalWrite(pinResistor, HIGH);
  startTime = millis();

  Serial.println("tempo(ms)\tVresistor(V)\tVcapacitor(V)");
}

void loop() {
  unsigned long tempo = millis() - startTime;

  int leitura = analogRead(pinCapacitor);
  float Vc = (leitura / 1023.0) * Vref; 
  float Vr = Vref - Vc;

  Serial.print(tempo);
  Serial.print("\t");
  Serial.print(Vr, 2);
  Serial.print("\t\t");
  Serial.println(Vc, 2);

  delay(400); 

  if (tempo > 5000) {
    digitalWrite(pinResistor, LOW);
    delay(2000);
    digitalWrite(pinResistor, HIGH);
    startTime = millis();
  }
}
