#include <PS2Keyboard.h>

const int DATA_PIN = 2;
const int CLK_PIN =  3;

PS2Keyboard keyboard;

void setup()
{
  delay(1000);
  keyboard.begin(DATA_PIN, CLK_PIN);
  Serial.begin(9600);
  Serial.println("[ PS2 Piano ]");
}

void loop()
{
  if (keyboard.available()) 
  {
    char c = keyboard.read();

    switch(c)
    {
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
