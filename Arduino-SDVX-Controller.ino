#include <Keyboard.h>
#include <Mouse.h>
#include <Encoder.h>
#define Keys 11
typedef struct {
  int pin;
  char keycode;
} LIST;

LIST keylist[] =
{
  {9, 'q'}, {8, 'w'},
  {0, 'o'}, {1, 'p'},
  {7, 'd'}, {6, 'f'}, {3, 'j'}, {2, 'k'},
  {5, 'g'}, {4, 'h'},
  {10, KEY_RETURN},
};

Encoder encoder1(14, 16);
Encoder encoder2(15, 18);
int old_ec1;
int old_ec2;

void setup() {
  for (int i = 0; i < Keys; i++) {
    pinMode(keylist[i].pin, INPUT_PULLUP);
  }
  Mouse.begin();
  Keyboard.begin();
  old_ec1 = encoder1.read();
  old_ec2 = encoder2.read();
}

void loop() {
  for (int i = 0; i < Keys; i++) {
    if (digitalRead(keylist[i].pin) == LOW) {
      Keyboard.press(keylist[i].keycode);
    } else {
      Keyboard.release(keylist[i].keycode);
    }
    int ec1 = encoder1.read();
    int ec2 = encoder2.read();
    if (ec1 != old_ec1) {
      Mouse.move(ec1 > old_ec1 ? -5 : 5, 0);
      old_ec1 = ec1;
    }
    if (ec2 != old_ec2) {
      Mouse.move(0, ec2 > old_ec2 ? -5 : 5);
      old_ec2 = ec2;
    }
  }
}
