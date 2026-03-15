// ---------- CONSTANTS ----------

#define GREEN_PIN (12)
#define YELLOW_PIN (8)
#define RED_PIN (7)

#define BUTTON_PIN (2)

#define GREEN_TIMEOUT (5000)
#define YELLOW_TIMEOUT (1000)
#define RED_TIMEOUT (3000)

#define BUTTON_TIMEOUT ((RED_TIMEOUT) + (YELLOW_TIMEOUT) + (2000))

#define TIMEOUT_TOLERANCE (500)


// ---------- STATE VARIABLES ----------

bool pressed;
unsigned long long last_pressed = 0;

uint8_t pin_on = -1;
unsigned long long last_transition = 0;


// ---------- PROGRAM ----------

void turn_on(uint8_t);
void turn_off(uint8_t);
void check_and_switch(uint8_t, uint8_t, uint16_t);

void setup() {
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  turn_on(GREEN_PIN);
}

void loop(){
  pressed = !digitalRead(BUTTON_PIN);
 
  if (pressed && millis() - last_pressed >= BUTTON_TIMEOUT && pin_on == GREEN_PIN) {

    // Debounce delay
    while (!digitalRead(BUTTON_PIN));

    last_pressed = millis();
    turn_off(GREEN_PIN);
   
    turn_on(YELLOW_PIN);
  }

  check_and_switch(GREEN_PIN, YELLOW_PIN, GREEN_TIMEOUT);

  check_and_switch(YELLOW_PIN, RED_PIN, YELLOW_TIMEOUT);

  check_and_switch(RED_PIN, GREEN_PIN, RED_TIMEOUT);
}


// ---------- HELPER FUNCTIONS ----------

void turn_on(uint8_t led_pin) {
  last_transition = millis();
 
  digitalWrite(led_pin, HIGH);
  pin_on = led_pin;
 
  delay(100);
}

void turn_off(uint8_t led_pin) {
  digitalWrite(led_pin, LOW);
  pin_on = -1;
 
  delay(100);
}

void check_and_switch(uint8_t pin_reff, uint8_t next_pin, uint16_t timeout_reff) {
    if (pin_on == pin_reff && millis() - last_transition >= timeout_reff) {
      turn_off(pin_reff);
      turn_on(next_pin);
  }
}
