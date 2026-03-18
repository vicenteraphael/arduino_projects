// ---------- CONSTANTS ----------

#define RED_PIN (2)
#define BLUE_PIN (4)
#define POT_PIN (A5)
#define MIN_DELAY (100)
#define MAX_DELAY (1000)


// ---------- STATE VARIABLES ----------

uint16_t pot_result;
uint16_t delay_time;
uint8_t pin;


// ---------- PROGRAM ----------

void flash(uint8_t pin, bool mode);
  
void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  pin = (pin == RED_PIN) ? BLUE_PIN : RED_PIN;
  
  pot_result = analogRead(POT_PIN);
  delay_time = map(pot_result, 0, 1023, MAX_DELAY, MIN_DELAY);
  
  flash(pin, HIGH);
  flash(pin, LOW);
}


// ---------- HELPER FUNCTIONS ----------

void flash(uint8_t pin, bool mode) {
  digitalWrite(pin, mode);
  delay(delay_time);
}