const int sound_pin_0 = 12;
const int sound_pin_1 = 13;

int buttons[] = {2, 3, 4, 5, 6, 7, 8, 9};
int tones[] = {100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850};

void setup() {
  pinMode(sound_pin_0, OUTPUT);
  pinMode(sound_pin_1, OUTPUT);

}

void loop() {
  int pressed_btn = button_check();
  if(pressed_btn != -1){
    sound(sound_pin_0, tones[5]);
    Serial.print(pressed_btn);
  }
}

int button_check(){
  for(int i = 2; i < 11; i++){
    if(i == 11){
      return -1;
    }
    if(digitalRead(i) == LOW){
      return i;
    }else{
      continue;
    }
  }
}

void sound(int pin, int tones){
  tone(pin, tones);
  delay(1000);
  noTone(pin);
}
