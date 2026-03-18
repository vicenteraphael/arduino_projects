/*
Points of improvement:
- implement PROGMEM;
- modularize better.
*/

// ----------- CONSTANTS -----------

#define DOT (500)
#define DASH (3 * (DOT))
#define SPACE_SIMPLE (DOT)
#define SPACE_LETTER (3 * (DOT))
#define SPACE_WORD (7 * (DOT))

#define LED_PIN (12)
#define PIEZO_PIN (7)
#define PIEZO_PITCH (600)

const char* const alphabet[26] = {
  ".-", "-...", "-.-.", "-..",		//A-D
  ".", "..-.", "--.", "....",		//E-H
  "..", ".---", "-.-", ".-..",		//I-L
  "--", "-.", "---", ".--.",		//M-P
  "--.-", ".-.", "...", "-",		//Q-T
  "..-", "...-", ".--", "-..-",		//U-X
  "-.--", "--.."					//Y-Z
};

const char* const number[10] = {
  "-----", ".----",					//0-1
  "..---", "...--",					//2-3
  "....-", ".....",					//4-5
  "-....", "--...",					//6-7
  "---..", "----.",					//8-9
};

// ----------- STATE VARIABLES -----------

#define MAX_SIZE (256)
char message[MAX_SIZE];
char ch;
size_t message_len;
size_t i;

// ----------- PROGRAM -----------

void transmit_char(char);

void flash(const char*);

void setup(){
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println(F("Ready to start, enter the text:"));
}

void loop(){
  if (!Serial.available()) return;
  
  message_len = Serial.readBytesUntil('\n', message, MAX_SIZE);
  
  message[message_len] = '\0';
  
  Serial.println(message);

  for (i = 0; i < message_len; ++i){
    ch = toupper(message[i]);
	
    transmit_char(ch);
  }
  Serial.println();
}


// ----------- HELPER FUNCTIONS -----------

void transmit_char(char ch){
  // Flash characters
  if (ch >= 'A' && ch <= 'Z')
    flash(alphabet[ch - 'A']);

  else if (ch >= '0' && ch <= '9')
    flash(number[ch - '0']);
  
  // Check if it's the last letter of a word;
  if (i < message_len - 1) {
    if (message[i+1] != ' ') {
      delay(SPACE_LETTER - SPACE_SIMPLE);
      Serial.print(F(" "));
    }
    else {
      delay(SPACE_WORD - SPACE_SIMPLE);
      Serial.print(F("  "));
    }
  }
}

void flash(const char *sequence) {
  for (int i = 0; sequence[i]; ++i) {
    Serial.print(sequence[i]);
    if (sequence[i] == '.') {
      digitalWrite(LED_PIN, HIGH);
      tone(PIEZO_PIN, PIEZO_PITCH, DOT);
      
      delay(DOT);
    }
    else if (sequence[i] == '-') {
      digitalWrite(LED_PIN, HIGH);
      tone(PIEZO_PIN, PIEZO_PITCH, DASH);
      
      delay(DASH);
    }
    
    digitalWrite(LED_PIN, LOW);
    
    delay(SPACE_SIMPLE);
  }
}
