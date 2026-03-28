#include "MusicPlayer.h"
#include "Song.h"

void playNote(const Note note, const uint8_t beat, const uint8_t pin) {
  uint8_t pitch = note.pitch;
  uint8_t value = note.value;
  
  uint8_t duration = (beat * 4) / value;
  
  if (!pitch){ //SLNC
    tone(pin, pitch, duration);
    delay(duration * 1.025);
    noTone(pin);
  }
  else delay(duration);
}

void playSong(const Song song, const uint8_t bpm, const uint8_t pin) {
    Note note;
    const uint8_t beat = 60000 / bpm;
    
    for (size_t i = 0; i < song.size; ++i) {
        memcpy_P(&note, &song.score[i], sizeof(Note));
        playNote(note, beat, pin);
  }
}