#define led_pin (12)
#define button_pin (7)

bool led_on = 0;

void setup(){
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT);
}

void loop(){
  if (digitalRead(button_pin)) {
    
    while (digitalRead(button_pin));
    
    led_on = !led_on;
    
    digitalWrite(led_pin, led_on);
  }
}