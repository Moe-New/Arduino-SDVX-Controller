#include <Mouse.h>
#include <Joystick.h>
#include <Encoder.h>
Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
  7, 0,
  false, false, false,
  false, false, false,
  false, false,
  false, false, false
);

const int keylist[] =
{
  7, 6, 15, 14,
  5, 18,
  4,
};
const int Keys = sizeof(keylist) / sizeof(keylist[0]);
const int P = 3;

Encoder encoder1(2, 3);
Encoder encoder2(20, 19);

void setup() {
  for (int i = 0; i < Keys; i++) {
    pinMode(keylist[i], INPUT_PULLUP);
  }
  Mouse.begin();
  Joystick.begin();
}
boolean lastStatus[Keys];
int o_ec1 = encoder1.read();
int o_ec2 = encoder2.read();

void loop() {
  for (int i = 0; i < Keys; i++) {
    boolean Status = !digitalRead(keylist[i]);
    if (Status != lastStatus[i]) {
      Joystick.setButton(i, Status);
      lastStatus[i] = Status;
    }
  }
  int ec1 = encoder1.read();
  int ec2 = encoder2.read();
  if (ec1 != o_ec1) {
    Mouse.move(ec1 < o_ec1 ? -P : P, 0);
    o_ec1 = ec1;
  }
  if (ec2 != o_ec2) {
    Mouse.move(0, ec2 < o_ec2 ? -P : P);
    o_ec2 = ec2;
  }
}
