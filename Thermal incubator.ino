const int thermistor1Pin = A1;
const int thermistor2Pin = A2;
const int thermistor3Pin = A3;
const int doorPin = A5;
const int ledPin = 13;
const int alarmPin = 12;
const float hysteresis = 0.1;      // select the pin for the LED

float voltage1 = 0;
float voltage2 = 0;
float voltage3 = 0;
int doorValue = 0;

void read_sensors() {
  voltage1 = analogRead (thermistor1Pin)/1023.*5.0;
  voltage2 = analogRead (thermistor2Pin)/1023.*5.0;
  voltage3 = analogRead (thermistor3Pin)/1023.*5.0;
  doorValue = digitalRead (doorPin);
}

void compare_voltages() {
  if ((doorValue == HIGH) || (voltage1 > 1.2*voltage2) || (voltage2 > 1.2*voltage1)){
  digitalWrite (alarmPin, HIGH);
  digitalWrite (ledPin,LOW);
 } else {
  digitalWrite (alarmPin, LOW);
  if((voltage1 > voltage3 + hysteresis) && (voltage2 > voltage3 + hysteresis)){
  digitalWrite (ledPin,HIGH);
 } else if ((voltage1 < voltage3 - hysteresis) && (voltage2 < voltage3 - hysteresis)){
  digitalWrite (ledPin, LOW);
 } 
}
}

void print_values(){
Serial.print(doorValue);
Serial.print(" ");
Serial.print(voltage1);
Serial.print(" ");
Serial.print(voltage2);
Serial.print(" ");
Serial.println(voltage3);
}

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  pinMode(alarmPin, OUTPUT);
  pinMode(doorPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  read_sensors();

  compare_voltages();

  print_values();

  delay(100);

}
