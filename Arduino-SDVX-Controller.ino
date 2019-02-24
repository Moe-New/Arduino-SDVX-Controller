#include <Keyboard.h>
#include <Mouse.h>
#include <Encoder.h>

typedef struct {
  int pin;
  char keycode;
} LIST;

LIST keylist[] =
{
  //{9, 'q'}, {8, 'w'},
  //{16, 'o'}, {10, 'p'},
  {7, 'd'}, {6, 'f'}, {15, 'j'}, {14, 'k'},
  {5, 'g'}, {18, 'h'},
  {4, 'y'},
};

Encoder encoder1(3, 2);
Encoder encoder2(0, 1);
int o_ec1;
int o_ec2;
int Keys = sizeof(keylist) / sizeof(keylist[0]);

void setup() {
  for (int i = 0; i < Keys; i++) {
    pinMode(keylist[i].pin, INPUT_PULLUP);
  }
  Mouse.begin();
  Keyboard.begin();
  o_ec1 = encoder1.read();
  o_ec2 = encoder2.read();
}

void loop() {
  for (int i = 0; i < Keys; i++) {
    if (digitalRead(keylist[i].pin) == LOW) {
      Keyboard.press(keylist[i].keycode);
    } else {
      Keyboard.release(keylist[i].keycode);
    }
  }
  int ec1 = encoder1.read();
  int ec2 = encoder2.read();
  if (ec1 != o_ec1) {
    Mouse.move(ec1 > o_ec1 ? -5 : 5, 0);
    o_ec1 = ec1;
  }
  if (ec2 != o_ec2) {
    Mouse.move(0, ec2 > o_ec2 ? -5 : 5);
    o_ec2 = ec2;
  }
}
