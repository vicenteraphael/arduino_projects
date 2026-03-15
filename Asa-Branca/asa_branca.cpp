/*
Song: Asa Branca
Composer: Luiz Gonzaga

Scale: C Major
Time signature: 4/4
Tempo: 97 bpm

Tribute to: https://musescore.com/user/190926/scores/181370
*/

#include <avr/pgmspace.h>

// ---------- FREQUENCIES ----------

#define SLNC (0)
#define E3 (329)
#define F3 (349)
#define G3 (391)
#define A3 (440)
#define B3 (493)
#define C4 (523)
#define D4 (587)
#define E4 (659)
#define F4 (698)


// ---------- NOTES LENGTHS ----------

// tempo
#define BPM (97)

#define WHOLE (1)
#define HALF (2)
#define QUARTER (4)
#define EIGHTH (8)

// BUZZER' DIGITAL PIN
#define PIEZO_PIN (12)


// ---------- MUSICAL STRUCTURE ----------

typedef struct note {
  uint16_t pitch;
  uint8_t value;
} Note;

const Note SCORE[] PROGMEM = {
  {SLNC, HALF},
  {SLNC, QUARTER},
  {G3, EIGHTH},
  {A3, EIGHTH},
    
  {B3, QUARTER},
  {D4, QUARTER},
  {D4, QUARTER},
  {B3, QUARTER},
    
  {C4, QUARTER},
  {C4, HALF},
  {G3, EIGHTH},
  {A3, EIGHTH},
    
  {B3, QUARTER},
  {D4, QUARTER},
  {D4, QUARTER},
  {C4, QUARTER},
    
  {B3, HALF},
  {SLNC, EIGHTH},
  {G3, EIGHTH},
  {G3, EIGHTH},
  {A3, EIGHTH},
  
  {B3, QUARTER},
  {D4, QUARTER},
  {SLNC, EIGHTH},
  {D4, EIGHTH},
  {C4, EIGHTH},
  {B3, EIGHTH},
    
  {G3, QUARTER},
  {C4, QUARTER},
  {SLNC, EIGHTH},
  {C4, EIGHTH},
  {B3, EIGHTH},
  {A3, EIGHTH},
  
  {A3, QUARTER},
  {B3, QUARTER},
  {SLNC, EIGHTH},
  {B3, EIGHTH},
  {A3, EIGHTH},
  {G3, EIGHTH},
  
  {G3, HALF},
  {SLNC, EIGHTH},
  {G3, EIGHTH},
  {G3, EIGHTH},
  {A3, EIGHTH},
  
  {B3, QUARTER},
  {D4, QUARTER},
  {SLNC, EIGHTH},
  {D4, EIGHTH},
  {C4, EIGHTH},
  {B3, EIGHTH},
  
  {G3, QUARTER},
  {C4, QUARTER},
  {SLNC, EIGHTH},
  {C4, EIGHTH},
  {B3, EIGHTH},
  {A3, EIGHTH},

  {A3, QUARTER},
  {B3, QUARTER},
  {SLNC, EIGHTH},
  {B3, EIGHTH},
  {A3, EIGHTH},
  {G3, EIGHTH},
 
  {G3, QUARTER},
  {F4, EIGHTH},
  {D4, EIGHTH},
  {E4, EIGHTH},
  {C4, EIGHTH},
  {D4, EIGHTH},
  {B3, EIGHTH},
  
  {C4, EIGHTH},
  {A3, EIGHTH},
  {B3, EIGHTH},
  {G3, EIGHTH},
  {A3, EIGHTH},
  {G3, EIGHTH},
  {E3, EIGHTH},
  {G3, EIGHTH},
  
  {G3, QUARTER},
  {F4, EIGHTH},
  {D4, EIGHTH},
  {E4, EIGHTH},
  {C4, EIGHTH},
  {D4, EIGHTH},
  {B3, EIGHTH},
  
  {C4, EIGHTH},
  {A3, EIGHTH},
  {B3, EIGHTH},
  {G3, EIGHTH},
  {A3, EIGHTH},
  {G3, EIGHTH},
  {E3, EIGHTH},
  {G3, EIGHTH},
  
  {G3, HALF}
};

// ---------- VARIABLES ----------

#define QNT_NOTES ((sizeof(SCORE)) / (sizeof(SCORE[0])))

#define BEAT (60000 / BPM)

uint16_t duration;

size_t i;

Note note;

//HELPER FUNCTION
void play_note(uint16_t, uint8_t);


// ---------- PROGRAM ----------

void setup(){
  pinMode(PIEZO_PIN, OUTPUT);
}

void loop(){
  for (i = 0; i < QNT_NOTES; ++i) {
    memcpy_P(&note, &SCORE[i], sizeof(Note));
    play_note(note.pitch, note.value);
  }
}


// ---------- HELPER FUNCTIONS ----------

void play_note(uint16_t pitch, uint8_t value) {
  duration = (BEAT * 4) / value;
  if (pitch != SLNC){
    tone(PIEZO_PIN, pitch, duration);
    delay(duration * 1.025);
    noTone(PIEZO_PIN);
  }
  else delay(duration);
}