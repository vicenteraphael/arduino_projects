// ---------- CONSTANTS ----------

#define RED_LED_PIN (11)
#define GREEN_LED_PIN (9)
#define BLUE_LED_PIN (10)

#define RED_POT_PIN (A0)
#define GREEN_POT_PIN (A1)
#define BLUE_POT_PIN (A2)


// ---------- STATE VARIABLES ----------

int red_pot_result;
int green_pot_result;
int blue_pot_result;

int red_scale;
int green_scale;
int blue_scale;


// ---------- PROGRAM ----------

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  
  pinMode(RED_POT_PIN, INPUT);
  pinMode(GREEN_POT_PIN, INPUT);
  pinMode(BLUE_POT_PIN, INPUT);
}

void loop() {
  red_pot_result = analogRead(RED_POT_PIN);
  green_pot_result = analogRead(GREEN_POT_PIN);
  blue_pot_result = analogRead(BLUE_POT_PIN);
  
  red_scale = map(red_pot_result, 0, 1023, 0, 255);
  green_scale = map(green_pot_result, 0, 1023, 0, 255);
  blue_scale = map(blue_pot_result, 0, 1023, 0, 255);
  
  analogWrite(RED_LED_PIN, red_scale);
  analogWrite(GREEN_LED_PIN, green_scale);
  analogWrite(BLUE_LED_PIN, blue_scale);
}