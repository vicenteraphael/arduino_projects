// --------- CONSTANTS AND VARIBALES ---------

#define G4 (783)

#define GREEN_LED_PIN (12)
#define YELLOW_LED_PIN (11)
#define RED_LED_PIN (10)

#define PIEZO_PIN (A0)

#define GREEN_DELAY (800)
#define YELLOW_DELAY (500)
#define RED_DELAY (250)

#define BEEP_DURATION (300)

#define TRIGGER_PIN (A5)
#define ECHO_PIN (A4)

#define GREEN_DIST (215)
#define YELLOW_DIST (130)

#define MAX_DIST (336)

uint16_t dist_cm = 0;

unsigned long long lastBeep;

// --------- PROGRAM ---------

long readUltrasonicDistance();

void beep(uint16_t);

void setup(){
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop(){
  // Measure the ping time in cm
  dist_cm = 0.01723 * readUltrasonicDistance();
 
  Serial.print(dist_cm);
  Serial.println("cm");
	
  // Classify the distances
  if (dist_cm >= GREEN_DIST && dist_cm < MAX_DIST) {
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    
    beep(GREEN_DELAY);
  }
  else if (dist_cm >= YELLOW_DIST && dist_cm < MAX_DIST) {
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    
    beep(YELLOW_DELAY);
  }
  else {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    
    beep(RED_DELAY);
  }
 
  delay(100);
}


// --------- HELPER FUNCTIONS ---------

long readUltrasonicDistance(){
  pinMode(TRIGGER_PIN, OUTPUT);  // Clear the trigger
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
 
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
 
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(ECHO_PIN, HIGH);
}

void beep(uint16_t delayBetweenBeeps){
  if (millis() - lastBeep >= delayBetweenBeeps) {
	tone(PIEZO_PIN, G4, BEEP_DURATION);
    lastBeep = millis();
  }
}