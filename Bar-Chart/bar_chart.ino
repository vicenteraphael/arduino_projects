// --------- CONSTANTS ---------

const uint8_t LED_PINS[] = {12, 11, 10, 9, 8, 7, 6, 5, 4};

#define LED_PINS_LENGTH (sizeof(LED_PINS) / sizeof(LED_PINS[0]))
#define TIME_DELAY (100)
#define POT_PIN (A5)


// --------- STATE VARIABLES ---------

uint16_t pot_result;
uint8_t scale;
size_t i;


// --------- PROGRAM ---------

void setup(){
  for (i = 0; i < LED_PINS_LENGTH; ++i)
  	pinMode(LED_PINS[i], OUTPUT);
}

void loop(){
  pot_result = analogRead(POT_PIN);
  scale = map(pot_result, 0, 1023, 0, LED_PINS_LENGTH);
  
  for (i = 0; i < scale; ++i)
    digitalWrite(LED_PINS[i], HIGH);
  
  for (i = scale; i < LED_PINS_LENGTH; ++i)
    digitalWrite(LED_PINS[i], LOW);
  
  delay(TIME_DELAY);
}