#include <Arduino.h>
#include "LedBar.h"

#define TIME_DELAY (100)

LedBar ledbar(12, 11, 10, 9, 8, 7, 6, 5, 4);

void setup(){
  ledbar.begin(A0);
}

void loop(){
  ledbar.drawChart();
  
  delay(TIME_DELAY);
}