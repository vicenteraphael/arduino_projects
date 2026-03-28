#ifndef SONG_H
#define SONG_H

#include <Arduino.h>
#include "Notes.h"

// ---------- MUSICAL STRUCTURE ----------

typedef struct song {
  const Note *score;
  const uint8_t size;
} Song;

#endif