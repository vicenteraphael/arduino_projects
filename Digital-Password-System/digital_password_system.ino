#include <Keypad.h>
#include <LiquidCrystal.h>

// ------------- INSTANCES -------------

#define ROWS (4)
#define COLUMNS (4)

byte row_pin[ROWS] = {12, 11, 10, 9};
byte column_pin[COLUMNS] = {8, 7, 6, 5};

char keys[ROWS][COLUMNS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

Keypad keypad = Keypad(makeKeymap(keys), row_pin, column_pin, ROWS, COLUMNS);

LiquidCrystal lcd(4, 3, A0, A1, A2, A3);


// ------------- VARIABLES -------------

uint8_t y = 2;
uint8_t x = 0;

uint8_t last_y = 2;
uint8_t last_x = 0;

const char password[] = "53C50#";

char key;
char string[32];
uint8_t str_ptr = 0;


// ------------- PROGRAM -------------

bool verify_string();

void check_unlocked();

void unlocked_animation();

void incorrect_animation();

void update_cursor();

void decrease_cursor();

bool print_key();

void setup(){
  lcd.begin(16, 2);
  lcd.setCursor(y, x);
  lcd.setCursor(0, 0);
  lcd.print("P:");
}

void loop(){
  key = keypad.getKey();
  if (key)
    if (print_key(key))
      check_unlocked();
}


// ------------- HELPER FUNCTIONS -------------

bool verify_string(){
	return strcmp(string, password) == 0;
}

void check_unlocked() {
  lcd.clear();
  
  if (verify_string()) unlocked_animation();
  else incorrect_animation();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("P:");
}

void unlocked_animation(){
  lcd.print("                UNLOCKED");
  for (uint8_t i; i < 50; ++i) {
    lcd.scrollDisplayLeft();
    delay(50);
  }
  lcd.clear();
}

void incorrect_animation(){
	lcd.print("INCORRECT");
    delay(2000);
}

bool print_key(char key){
  if (key == 'A') {
  	string[str_ptr] = '\0';
    return true;
  }
  else if (key == 'D') {
    if (str_ptr <= 0) return false;
    
    string[--str_ptr] = '\0';
    lcd.setCursor(last_y, last_x);
    
    decrease_cursor();
    lcd.print(' ');
    
    lcd.setCursor(y, x);
  }
  else {
    string[str_ptr++] = key;
    lcd.print(key);
  
  	increase_cursor();
  }
  return false;
}

void increase_cursor(){
  last_y = y;
  last_x = x;
  
  if (y < 16) ++y;
  else if (x < 1){
    y = 2;
    ++x;
    lcd.setCursor(y, x);
  }
}

void decrease_cursor(){
  if (x == 1 && y == 2) {
    x = 0; y = 15;
    last_x = 0; last_y = 14;
    lcd.setCursor(y, x);
  }
  else if (y > 2) {
    --y; last_y = y - 1;
  }
}