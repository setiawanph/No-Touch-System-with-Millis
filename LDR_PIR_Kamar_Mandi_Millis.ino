#define ldr A0
#define ledPin D6
#define pir D5
#define relay D7

unsigned long previousPIR_Millis = 0; 
//unsigned long previousLED_Millis = 0; 
const long intervalPIR = 2.5*60000;
int pirState = LOW;
/*const long intervalMillis = 10000;
int ledState = LOW;
int relayValue = LOW;*/
bool BlinkTime = false;

void setup() {
  Serial.begin(9600);
  pinMode(pir, INPUT);   // declare sensor as input
  pinMode(ledPin, OUTPUT);  // declare LED as output
  pinMode(relay, OUTPUT);
}

void loop() {
  int valueLDR = analogRead(ldr);
  //Serial.print("Cahaya: "+ valueLDR);
  //Serial.println(sensor);
  long state = digitalRead(pir);
  pirState = state;
  Serial.println(state);
  unsigned long currentMillis = millis();

  if(digitalRead(pir) && valueLDR >= 620){
    BlinkTime = true;
    previousPIR_Millis = millis();
    digitalWrite(ledPin, HIGH);
    digitalWrite(relay, HIGH);
  }
  if(BlinkTime && millis()-previousPIR_Millis >= intervalPIR){
    BlinkTime = false;
    digitalWrite(ledPin, LOW);
    digitalWrite(relay,LOW);
  }
}
