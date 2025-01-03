#define ldr A0
#define ledPin D6
#define pir D5
#define relay D7

unsigned long previousPIR_Millis = 0; //save time-millis after executing the currentMillis
const long intervalPIR = 2.5*60000; //time for the lamp in ON state
int pirState = LOW; //State of PIR for the first time
int ledState = LOW; //State of LED for the first time
int relayValue = LOW; //Value for executing relay
bool BlinkTime = false; 

void setup() {
  Serial.begin(9600); //begin the serial
  pinMode(pir, INPUT); //declare sensor as input
  pinMode(ledPin, OUTPUT); //declare LED as output
  pinMode(relay, OUTPUT); //declare relay as output
}

void loop() {
  int valueLDR = analogRead(ldr); //Reading the illumination value from LDR
  long state = digitalRead(pir); //Reading the illumination value from PIR
  pirState = state; //Stating the PIR to monitor in the serial
  Serial.println(state);
  unsigned long currentMillis = millis();
  
  //The Blink Time will be activated and put the LED and lamp (via relay) to HIGH
  //after the object is detected and LDR value >620
  if(digitalRead(pir) && valueLDR >= 620){
    BlinkTime = true;
    previousPIR_Millis = millis();
    digitalWrite(ledPin, HIGH);
    digitalWrite(relay, HIGH);
  }
  
  //The Blink Time will be removed and put the LED and lamp (via relay) to LOW
  if(BlinkTime && millis()-previousPIR_Millis >= intervalPIR){
    BlinkTime = false;
    digitalWrite(ledPin, LOW);
    digitalWrite(relay,LOW);
  }
}
