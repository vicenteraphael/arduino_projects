/*
Song: Asa Branca
Composer: Luiz Gonzaga

Scale: C Major
Time signature: 4/4
Tempo: 97 bpm

Tribute to: https://musescore.com/user/190926/scores/181370
*/  

// ---------- LIBRARIES ----------

#include <Arduino.h>
#include "AsaBranca.h"
#include "MusicPlayer.h"

// BUZZER' DIGITAL PIN
#define PIEZO_PIN (12)

// TEMPO
#define BPM (97)
#define BEAT (60000 / BPM)

uint16_t duration;

// ---------- PROGRAM ----------

void setup(){
  pinMode(PIEZO_PIN, OUTPUT);
}

void loop(){
  playSong(AsaBranca, BPM, BEAT);
}


// ---------- HELPER FUNCTIONS ----------