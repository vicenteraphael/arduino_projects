/*
TO DO:
- add diodes;
- think about sensor noise filtering;
- think about clamping values;
- max motor timeout
*/

#include <LiquidCrystal.h>

// ---------- CONSTANTS ----------

#define SENSOR_PIN (A0)
#define FAN_PIN (11)
#define HEATER_PIN (6)

// IRL, you'll want: (20ºC - 25ºC)
#define MIN_ROOM_TEMP (32)
#define MAX_ROOM_TEMP (52)

// Adjust with data from your sensor
#define MIN_SENSOR_TEMP (-40)
#define MAX_SENSOR_TEMP (125)

#define MIN_SENSOR_SIGNAL (20)
#define MAX_SENSOR_SIGNAL (358)

#define HYSTERESIS (2)


// ---------- STATE VARIABLES ----------

LiquidCrystal lcd(4, 5, A1, A2, A3, A4);

int16_t sensor_result;
int8_t temp;
int8_t last_temp;


uint8_t intensity;


// ---------- PROGRAM ----------

void print_temperature();

void control_temperature();

void turn_heater_on();

void turn_fan_on();

void turn_all_off();

void setup(){
  pinMode(FAN_PIN, OUTPUT);
  pinMode(HEATER_PIN, OUTPUT);
  
  lcd.begin(16, 2);
}

void loop(){
  sensor_result = analogRead(SENSOR_PIN);
  temp = map(sensor_result, MIN_SENSOR_SIGNAL, MAX_SENSOR_SIGNAL, MIN_SENSOR_TEMP, MAX_SENSOR_TEMP);

  if (temp != last_temp) {
    lcd.clear();
    
    print_temperature();
  
  	control_temperature();
    
    last_temp = temp;
  }
	
  // IRL, you'll probably want a delay
  // once temperature doesn't usually
  // abruptly change
}


// ---------- HELPER FUNCTIONS ----------

void print_temperature(){
  lcd.setCursor(0,0);
  lcd.print("      "); lcd.print(temp); lcd.write(178); lcd.print("C      ");
}

void control_temperature(){
  lcd.setCursor(0,1);
  
  if (temp < MIN_ROOM_TEMP - HYSTERESIS){
    turn_heater_on();
    lcd.print("   HEATER ON   ");
  }
  else if (temp > MAX_ROOM_TEMP + HYSTERESIS){
    turn_fan_on();
    lcd.print("     FAN ON     ");
  }
  else {
    turn_all_off();
    lcd.print("     STABLE     ");
  }
  
}

void turn_heater_on(){
  digitalWrite(FAN_PIN, LOW);
    
  intensity = map(temp, MIN_SENSOR_TEMP, MIN_ROOM_TEMP - 1, 255, 1);
  analogWrite(HEATER_PIN, intensity);
}

void turn_fan_on(){
  digitalWrite(HEATER_PIN, LOW);
    
  intensity = map(temp, MAX_ROOM_TEMP, MAX_SENSOR_TEMP, 1, 255);
  analogWrite(FAN_PIN, intensity);
}

void turn_all_off(){
	digitalWrite(FAN_PIN, LOW);
  	digitalWrite(HEATER_PIN, LOW);
}