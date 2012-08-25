#include <PS2Keyboard.h>

const int DATA_PIN = 2;
const int CLK_PIN =  3;
const int PIEZO_PIN = 8;

PS2Keyboard keyboard;
int num_keys = 49;
char keymap[] = "zsxdcvgbhnjmq2w3er5t6y7uZSXDCVGBHNJMQ@W#ER%T^Y&UI";
int timehigh[] = {
  7645, 7215, 6810, 6428, 6067, 5727, 5405, 5102, 4816, 4545, 4290, 4050,
  3822, 3608, 3405, 3214, 3034, 2863, 2703, 2551, 2408, 2273, 2145, 2025,
  1911, 1804, 1703, 1607, 1517, 1432, 1351, 1276, 1204, 1136, 1073, 1012,
  956, 902, 851, 804, 758, 716, 676, 638, 602, 568, 536, 506,
  478 
};
int std_freq = 440;
boolean buffer_open = false;
boolean buffer_repeat = false;
int buffer_pos = 0;
int buffer_size = 64;
char buffer[64];
int tempo = 300;


void setup() {
  delay(1000);
  pinMode(PIEZO_PIN, OUTPUT);
  keyboard.begin(DATA_PIN, CLK_PIN);
  Serial.begin(9600);
  Serial.println("[ PS2 Piano ]");
}

void loop() {
  if (keyboard.available())  {
    char c = keyboard.read();
    
    if (c == '|')
      buffer_repeat = !buffer_repeat;
    if (c == '\\') {
      if (buffer_open) {
        for (int i = 0; i < buffer_size; i++)
          buffer[i] = 0;
          
        buffer_open = false;
      }
       else
        buffer_open = true;
    }
    
    else if (c == PS2_ENTER) {
      playMelody(buffer);
      buffer_open = false;
    }
      
    else if (buffer_open)
      buffer[buffer_pos++] = c;
      
    else if (c == ' ')
      delay(tempo);
      
    else
      for (int i = 0; i < num_keys; i++)
        if (c == keymap[i]) 
          playTone(timehigh[i], tempo);
      
     
      

    switch(c) {
      case PS2_ENTER: Serial.println(); break;
      case PS2_TAB: Serial.print("[Tab]"); break;
      case PS2_ESC: Serial.print("[Esc]"); break;
      case PS2_PAGEDOWN: Serial.print("[PgDn]"); break;
      case PS2_PAGEUP: Serial.print("[PgUp]"); break;
      case PS2_LEFTARROW: Serial.print("[Left]"); break;
      case PS2_RIGHTARROW: Serial.print("[Right]"); break;
      case PS2_UPARROW: Serial.print("[Up]"); break;
      case PS2_DOWNARROW: Serial.print("[Down]"); break;
      case PS2_DELETE: Serial.print("[Del]"); break;
      default: Serial.print(c);  break;
    }
  }
}

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(PIEZO_PIN, HIGH);
    delayMicroseconds(tone);
    digitalWrite(PIEZO_PIN, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void playMelody(char melody[]) {
  do {
   for (int i = 0; i < buffer_size; i++)
     if (buffer[i] == ' ')
       delay(tempo);
     else
       for (int j = 0; j < num_keys; j++)
          if (buffer[i] == keymap[j]) 
            playTone(timehigh[j], tempo); 
  } while (buffer_repeat == true);
}

