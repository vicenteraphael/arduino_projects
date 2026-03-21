/*
I need to cleanify the code and add
the increasing velocity logic.
Also, I want to remove the necessity to 
wait for the LED to turn off to press another
button
*/

// ------------- CONSTANTS -------------

#include <LiquidCrystal.h>

#define C4 (261)
#define E4 (329)
#define G4 (391)
#define C5 (523)

const uint8_t LED_PIN[] = {11, 9, 7, 5};
const uint8_t BUT_PIN[] = {12, 10, 8, 6};
const uint16_t FREQ[] = {C4, E4, G4, C5};

#define PINS_SIZE (sizeof(LED_PIN) / sizeof(LED_PIN[0]))
#define PIEZO_PIN (2)
#define DELAY_TIME (400)
#define SEQ_SIZE (5)


// ------------- STATE VARIABLES -------------

LiquidCrystal lcd(4, 3, A2, A3, A4, A5);

uint8_t SEQ[SEQ_SIZE];
int8_t seq_ptr = -1;

uint8_t led_idx;
uint8_t player_ptr = 0;
uint8_t score = 0;

bool pressed;

// ------------- PROGRAM -------------

void flash(uint8_t, uint8_t, uint16_t);

void game_win();

void game_over();

void play_sequence();

int read_player();

void setup(){
  for (uint8_t i = 0; i < PINS_SIZE; ++i) {
    pinMode(LED_PIN[i], OUTPUT);
    pinMode(BUT_PIN[i], INPUT_PULLUP);

  }
  pinMode(PIEZO_PIN, OUTPUT);
  randomSeed(analogRead(A0));
  
  lcd.begin(16, 2);
  
  game_win();
}

void loop(){

  if (seq_ptr + 1 >= SEQ_SIZE) game_win();

  play_sequence();

  player_ptr = 0;
  while (player_ptr <= seq_ptr) {
    if (read_player()) {
      game_over();
      return;
    }
  }
  
  increase_score();
  delay(DELAY_TIME * 2);
}


// ------------- HELPER FUNCTIONS -------------

void flash(uint8_t led_pin, uint16_t freq, uint16_t delay_time) {
  digitalWrite(led_pin, HIGH);
  tone(PIEZO_PIN, freq, delay_time);
  delay(delay_time);
  digitalWrite(led_pin, LOW);
}


// Animation

void game_win() {
  
  if (score > 0) {
  	lcd.clear();
    lcd.print("YOU WIN");
  }
  else {
    lcd.clear();
    lcd.print("GAME START");
  }

  for (uint8_t i = 0; i < 5; ++i)
    for (uint8_t j = 0; j < PINS_SIZE; ++j)
      flash(LED_PIN[j], FREQ[j], 50);
      
  for (uint8_t j = 0; j < PINS_SIZE; ++j) {
      digitalWrite(LED_PIN[j], HIGH);
      tone(PIEZO_PIN, FREQ[j], 300);
  }
  
  delay(500);
  for (uint8_t j = 0; j < PINS_SIZE; ++j)
      digitalWrite(LED_PIN[j], LOW);
  delay(500);

  seq_ptr = -1;

  lcd.clear();
  
  score = 0;
}

void game_over() {
  tone(PIEZO_PIN, 100, DELAY_TIME * 2);

  lcd.clear();
  lcd.print("YOU LOOSE");
  
  for (uint8_t i = 0; i < PINS_SIZE; ++i)
    digitalWrite(LED_PIN[i], HIGH);

  delay(DELAY_TIME * 2);
  for (uint8_t i = 0; i < PINS_SIZE; ++i)
    digitalWrite(LED_PIN[i], LOW);

  seq_ptr = -1;
  delay(DELAY_TIME * 2);

  lcd.clear();
  
  score = 0;
}


void increase_score(){
  ++score;
  lcd.clear();
  if (score < 10) lcd.print(score);
  else lcd.print(score);
}

// Interaction

void play_sequence(){
  SEQ[++seq_ptr] = random(PINS_SIZE);

  for (uint8_t i = 0; i <= seq_ptr; ++i) {
    led_idx = SEQ[i];
    
    flash(LED_PIN[led_idx], FREQ[led_idx], DELAY_TIME);
    
    delay(DELAY_TIME);
  }

}

int read_player() {
  for (uint8_t i = 0; i < PINS_SIZE; ++i) {  
    pressed = !digitalRead(BUT_PIN[i]); //(!) for input_pullup
    
    if (pressed){
      // Debounce delay
      while(!digitalRead(BUT_PIN[i]));
      
      flash(LED_PIN[i], FREQ[i], DELAY_TIME);

      if (i != SEQ[player_ptr]) return 1;
      
      ++player_ptr;
      
      return 0;

    }
  }
  return 0;
}