#include <Keypad.h>

// define the max number of beats the user can create and loop
const int max_beats = 1000;

// speaker output pins
const int sound_pin_0 = 12;
const int sound_pin_1 = 13;

// sound variables
int tones[] = {100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850};

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// array records the current beat saved to the device: 16 bars
char current_beat[max_beats];

// we assign key S16 -> '8' for record functionality, S15 -> 'C' for stop record, S14 -> for playback and S13 -> for delete recording
bool record = false;

// keeps track of how many beats are currently in memory for the current track: must be <= 16
int press_count = 0;

void setup(){
  Serial.begin(9600);
  // declare sound pins as output
  pinMode(sound_pin_0, OUTPUT);
  pinMode(sound_pin_1, OUTPUT);

  // initialise beats
  for(int i = 0; i < max_beats; i++){
    current_beat[i] = 0;
  }
}


void loop(){
  // listen for keydown
  char customKey = customKeypad.getKey();
  
  // act on keydown
  for(int i = 0; i < 4; i++){
    for(int ii = 0; ii < 4; ii++){
      if(customKey == hexaKeys[i][ii]){
        // handle record setting (top - left button: (0,0))
        if(customKey == 'C'){
          record = !record;
        }
        // handle playback (1, 0)
        else if (customKey == '8'){
          playback();
        }
        else{
          // plays note no matter what
          sound(sound_pin_0, tones[i + ii]);
          sound(sound_pin_1, tones[i + ii]);
          // only records not if these conditions are met
          if(record && press_count < max_beats){
            current_beat[press_count] = i + ii;
            press_count++;
          }
        }
      }
    }
  }
}

// sound creation
void sound(int pin, int tones){
  tone(pin, tones);
  delay(200);
  noTone(pin);
}

// creates accurate playback
void playback(){
  int user_beats[press_count];
  for(int i = 0; i < press_count; i++){
    user_beats[i] = current_beat[i];
  }
  for(int i = 0; i < press_count; i++){
    sound(sound_pin_0, tones[user_beats[i]]);
    sound(sound_pin_1, tones[user_beats[i]]);
  }
}
