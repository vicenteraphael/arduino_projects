#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <Arduino.h>
#include "Song.h"

void playSong(const Song song, const uint8_t bpm, const uint8_t pin);

#endif