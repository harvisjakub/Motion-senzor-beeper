/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-motion-sensor
 */

const int PIN_TO_SENSOR = 13; // GIOP13 pin connected to OUTPUT pin of sensor
int pinStateCurrent   = LOW;  // current state of pin
int pinStatePrevious  = LOW;  // previous state of pin

int freq = 200;
int channel = 0;
int resolution = 8;

void setup() {
  Serial.begin(9600);            // initialize serial
  pinMode(PIN_TO_SENSOR, INPUT); // set ESP32 pin to input mode to read value from OUTPUT pin of sensor

  ledcSetup(channel, freq, resolution); //Funkce beeperu
  ledcAttachPin(18, channel); //Nastavení pinu beeperu
  
}

void loop() {
  pinStatePrevious = pinStateCurrent; // store old state
  pinStateCurrent = digitalRead(PIN_TO_SENSOR);   // read new state
// Pokud projde někdo kolem, spustí se podmínka zapnutí senzoru
  if (pinStatePrevious == LOW && pinStateCurrent == HIGH) {   // pin state change: LOW -> HIGH
    Serial.println("Motion detected!");
      beep();
    // TODO: turn on alarm, light or activate a device ... here
  }
  // Pokud delší dobu není zaznamenán pohyb, spustí se podmínka vypnutí senzoru
  else
  if (pinStatePrevious == HIGH && pinStateCurrent == LOW) {   // pin state change: HIGH -> LOW
    Serial.println("Motion stopped!");
       beepoff();
    // TODO: turn off alarm, light or deactivate a device ... here
  }
}
// Funkce po aktivaci motion senzoru pro beeper
void beep() {
  ledcWriteTone(channel, 5);
  
  for (int dutyCycle = 5; dutyCycle <= 750; dutyCycle=dutyCycle+100){
  
    Serial.println(dutyCycle);
  
    ledcWrite(channel, dutyCycle);
   
  }
}
// Funkce po deaktivaci motion senzoru pro beeper
void beepoff() {
  ledcWriteTone(channel, 10);
  
  for (int dutyCycle = 0; dutyCycle <= 5; dutyCycle=dutyCycle+10){
  
    Serial.println(dutyCycle);
  
    ledcWrite(channel, dutyCycle);
   
  }
}
