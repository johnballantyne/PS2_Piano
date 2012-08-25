#include <PS2Keyboard.h>

const int DATA_PIN = 2;
const int CLK_PIN =  3;
const int PIEZO_PIN = 8;

PS2Keyboard keyboard;
char keymap[] = "zsxdcvgbhnjmq2w3er5t6y7uZSXDCVGBHNJMQ@W#ER%T6Y&UI";
int low_halftone = -33;
int high_halftone = 15;

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
      case 'z': playNote('c', 300); break;
      case 'x': playNote('d', 300); break;
      case 'c': playNote('e', 300); break;
      case 'v': playNote('f', 300); break;
      case 'b': playNote('g', 300); break;
      case 'n': playNote('a', 300); break;
      case 'm': playNote('b', 300); break;
      case ',': playNote('C', 300); break;
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
