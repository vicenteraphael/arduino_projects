#ifndef NOTES_H
#define NOTES_H

#include <Arduino.h>

// ---------- NOTES' FREQUENCIES ----------

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

// ---------- NOTES' LENGTHS ----------

#define WHOLE (1)
#define HALF (2)
#define QUARTER (4)
#define EIGHTH (8)

// ---------- NOTE STRUCTURE ----------

typedef struct note {
  uint16_t pitch;
  uint8_t value;
} Note;

#endif