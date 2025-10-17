const int ledVermelho=8;
const int ledVerde=10;
const int ledAmarelo=9;
void setup()
{
  pinMode(ledVermelho,OUTPUT);
  pinMode(ledVerde,OUTPUT);
  pinMode(ledAmarelo,OUTPUT);

}

void loop()
{
  digitalWrite(ledVermelho,HIGH);
  delay(6000);
  digitalWrite(ledVermelho,LOW);
  digitalWrite(ledAmarelo,HIGH);
  delay(2000);
  digitalWrite(ledAmarelo,LOW);
  digitalWrite(ledVerde,HIGH);
  delay(2000);
  digitalWrite(ledVerde,LOW);
  digitalWrite(ledVerde,HIGH);
  delay(2000);
  digitalWrite(ledVerde,LOW);
  digitalWrite(ledAmarelo,HIGH);
  delay(2000);
  digitalWrite(ledAmarelo,LOW);
}