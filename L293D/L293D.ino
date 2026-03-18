/*
add:
void readInputs();
void updateSpeed();
void updateDirection();

maybe, this can become a lib!
*/

struct Wheel {
  const uint8_t FORWARD_PIN;
  const uint8_t BACKWARD_PIN;

  const uint8_t FORWARD_SWITCH_PIN;
  const uint8_t BACKWARD_SWITCH_PIN;

  const uint8_t SPEED_PIN;
  const uint8_t POT_PIN;

  Wheel(
    uint8_t fwd, uint8_t back,
    uint8_t fwd_sw, uint8_t back_sw,
    uint8_t speed_pin, uint8_t pot_pin
  ):
  FORWARD_PIN(fwd),
  BACKWARD_PIN(back),
  FORWARD_SWITCH_PIN(fwd_sw),
  BACKWARD_SWITCH_PIN(back_sw),
  SPEED_PIN(speed_pin),
  POT_PIN(pot_pin) {}

  bool forward_switch_on;
  bool backward_switch_on;

  uint16_t pot_result;
  uint8_t speed;

  void move(){
    forward_switch_on = digitalRead(FORWARD_SWITCH_PIN);
    backward_switch_on = digitalRead(BACKWARD_SWITCH_PIN);

    pot_result = analogRead(POT_PIN);
    speed = map(pot_result, 0, 1023, 0, 255);
    analogWrite(SPEED_PIN, speed);

    if (forward_switch_on && !backward_switch_on){
      digitalWrite(FORWARD_PIN, HIGH);
      digitalWrite(BACKWARD_PIN, LOW);
    }
    else if (!forward_switch_on && backward_switch_on){
      digitalWrite(BACKWARD_PIN, HIGH);
      digitalWrite(FORWARD_PIN, LOW);
    }
    else{
      digitalWrite(BACKWARD_PIN, LOW);
      digitalWrite(FORWARD_PIN, LOW);
    }
  }  
};

Wheel wheel1(12, 11, 2, 7, 10, A5);
Wheel wheel2(4, 5, 8, 9, 3, A4);

void setup(){
  // Wheel 1
  pinMode(wheel1.FORWARD_PIN, OUTPUT);
  pinMode(wheel1.BACKWARD_PIN, OUTPUT);
  pinMode(wheel1.FORWARD_SWITCH_PIN, INPUT);
  pinMode(wheel1.BACKWARD_SWITCH_PIN, INPUT);

  // Wheel 2
  pinMode(wheel2.FORWARD_PIN, OUTPUT);
  pinMode(wheel2.BACKWARD_PIN, OUTPUT);
  pinMode(wheel2.FORWARD_SWITCH_PIN, INPUT);
  pinMode(wheel2.BACKWARD_SWITCH_PIN, INPUT);
}

void loop(){
  wheel1.move();
  wheel2.move();
}