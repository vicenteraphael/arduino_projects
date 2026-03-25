#include <Keypad.h>
#include <LiquidCrystal.h>

// ------------- CONSTANTS -------------

#define ROWS (4)
#define COLUMNS (4)

#define PIEZO_PIN (A5)
#define G5 (440)
#define NOTE_DURATION (250)

#define PASSWORD_SIZE (28)
#define WARNING_DELAY (2000)


// ------------- INSTANCES -------------

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


// Alter it to your liking
char password[PASSWORD_SIZE] = "1234";

char key;
char input[PASSWORD_SIZE];
uint8_t input_ptr = 0;

static unsigned long last_pressed = 0;


// ------------- PROGRAM -------------

// Input operations

bool read_key(char[], uint8_t*, const char[]);

bool print_key(char, char[], uint8_t*, const char[]);

bool verify_input();

void check_unlocked(char[], uint8_t*, const char[]);


// Warning

void warning(const char[], const char[]);


// Cursor

void reset_cursor();

void increase_cursor();

void decrease_cursor();


// Functions

void new_password();

void enter(char[], uint8_t*);

void new_password();

void clear(char[], uint8_t*, const char[]);

void _delete(char[], uint8_t*);

void update_input(char[], uint8_t*);

// Main

void setup(){
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.blink();
  lcd.print("P:");
}

void loop(){
  if (read_key(input, &input_ptr, "P:"))
    check_unlocked(input, &input_ptr, "P:");
}


// ------------- HELPER FUNCTIONS -------------

// INPUT OPERATIONS

bool read_key(char string[], uint8_t *ptr, const char text[]){
  key = keypad.getKey();
  if (key) {
    last_pressed = millis();
    noTone(PIEZO_PIN);
    delay(10);
    tone(PIEZO_PIN, G5, NOTE_DURATION);
    if (print_key(key, string, ptr, text))
      return true;
  }
  if (millis() - last_pressed >= NOTE_DURATION) noTone(PIEZO_PIN);
  return false;
}

bool print_key(char key, char string[], uint8_t *ptr, const char text[]){
  
  switch (key) {
    case 'A': enter(string, ptr); return true; break;
    case 'B':  new_password(); break;
    case 'D': if (*ptr > 0) _delete(string, ptr); break;
    case 'C': clear(string, ptr, text); break;
    default: if (*ptr < PASSWORD_SIZE - 1) update_input(string, ptr);
  }

  return false;
}

bool verify_input(){
	return strcmp(input, password) == 0;
}

void check_unlocked(char string[], uint8_t *ptr, const char text[]) {
  lcd.clear();
  
  if (verify_input()) warning("UNLOCKED", "");
  else warning("INCORRECT", "");
  
  clear(string, ptr, text);
}


// WARNING

void warning(const char line1[], const char line2[]){
  lcd.clear();
  lcd.noBlink();

  lcd.setCursor((16 - strlen(line1)) / 2, 0);
  lcd.print(line1);

  lcd.setCursor((16 - strlen(line2)) / 2, 1);
  lcd.print(line2);

  delay(WARNING_DELAY);
  lcd.blink();
}


// CURSOR

void reset_cursor(){
  y = 2;
  x = 0;

  last_y = 2;
  last_x = 0;
}

void increase_cursor(){
  last_y = y;
  last_x = x;
  
  if (y < 15) ++y;
  else if (x == 0){
    y = 2; ++x;
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


// FUNCTIONS

void enter(char string[], uint8_t *ptr){
  string[*ptr] = '\0';
}

void new_password(){

  // Current password
  warning("ENTER CURRENT", "PASSWORD");
  clear(input, &input_ptr, "C:");
  while (true) {
    if (read_key(input, &input_ptr, "C:")) {
      if (verify_input())
        break;
      else {
        warning("INCORRECT", "");
        clear(input, &input_ptr, "P:");
        return;
      }
    }
  }

  // New password
  warning("INFORM NEW", "PASSWORD");
  char new_password1[PASSWORD_SIZE];
  uint8_t new_password1_ptr = 0;
  
  lcd.clear();
  lcd.print("N:");

  while (true) {
    if (read_key(new_password1, &new_password1_ptr, "N:")) {
      break;
    }
  }

  // Confirm new password
  warning("CONFIRM NEW", "PASSWORD");
  char new_password2[PASSWORD_SIZE];
  uint8_t new_password2_ptr = 0;

  lcd.clear();
  lcd.print("N:");

  while (true) {
    if (read_key(new_password2, &new_password2_ptr, "N:")) {
      if (strcmp(new_password1, new_password2) == 0) {
        strcpy(password, new_password2);
        warning("SUCCESS", "");
      }
      else
        warning("PASSWORDS", "DON'T MATCH");
      break;
    }
  }
  clear(input, &input_ptr, "P:");
}

void clear(char string[], uint8_t *ptr, const char text[]){
  lcd.clear();
  lcd.print(text);

  string[0] = '\0';
  *ptr = 0;

  reset_cursor();
}

void _delete(char string[], uint8_t *ptr){  
  string[--(*ptr)] = '\0';
  lcd.setCursor(last_y, last_x);
  
  decrease_cursor();
  lcd.print(' ');
  
  lcd.setCursor(y, x);
}

void update_input(char string[], uint8_t *ptr){
  string[(*ptr)++] = key;
  lcd.print(key);

  increase_cursor();
}