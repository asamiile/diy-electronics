// degital write
int frequency = 4000; //Buzzer frequency
int cycle = 1000000/frequency; //one time period in microseconds (1s=1000000us)

void setup() {

  // analog write
  // pinMode(WIO_BUZZER, OUTPUT);

  // degital write
  Serial.begin(9600);
  pinMode(WIO_BUZZER,OUTPUT);
}
 
void loop() {

  // analog write
  // analogWrite(WIO_BUZZER, 150);
  // delay(1000);
  // analogWrite(WIO_BUZZER, 0);
  // delay(1000);

  // degital write
  digitalWrite(WIO_BUZZER,HIGH);
  delayMicroseconds(cycle/2);
  digitalWrite(WIO_BUZZER,LOW);
  delayMicroseconds(cycle/2);
}