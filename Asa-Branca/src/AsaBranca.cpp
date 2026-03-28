#include "AsaBranca.h"

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

const uint8_t SIZE  = sizeof(SCORE) / sizeof(SCORE[0]);

const Song AsaBranca = {SCORE, SIZE};