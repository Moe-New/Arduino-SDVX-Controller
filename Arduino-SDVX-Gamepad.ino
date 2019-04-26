#include <Mouse.h>
#include <Joystick.h>
#include <Encoder.h>
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
                   7, 0,                  // Button Count, Hat Switch Count
                   false, false, false,     // X and Y, but no Z Axis
                   false, false, false,   // No Rx, Ry, or Rz
                   false, false,          // No rudder or throttle
                   false, false, false);  // No accelerator, brake, or steering

typedef struct {
  int pin;
  char keycode;
} LIST;

LIST keylist[] =
{
  {7, 'd'}, {6, 'f'}, {15, 'j'}, {14, 'k'},
  {5, 'g'}, {18, 'h'},
  {4, 'y'},
};
const int Keys = sizeof(keylist) / sizeof(keylist[0]);
const int P = 3;
int o_ec1;
int o_ec2;

Encoder encoder1(2, 3);
Encoder encoder2(20, 19);

void setup() {// 初始化
  for (int i = 0; i < Keys; i++) {
    pinMode(keylist[i].pin, INPUT_PULLUP);
  }
  Mouse.begin();
  Joystick.begin();


  o_ec1 = encoder1.read();
  o_ec2 = encoder2.read();
}
int lastButtonState[Keys];//保存 pin 的状态数据（0，1）

void loop() {
  for (int index = 0; index < Keys; index++)//循环检查所有按钮
  {
    int currentButtonState = !digitalRead(keylist[index].pin);
    //读取 pin 的状态并取反；读取 0 为接通，1 为断开；取反后，1 为按下，0 为未按下
    if (currentButtonState != lastButtonState[index])//如果 pin 状态已改变
    {
      switch (index) {
        case 0:
          Joystick.setButton(0, currentButtonState);
          break;
        case 1:
          Joystick.setButton(1, currentButtonState);
          break;
        case 2:
          Joystick.setButton(2, currentButtonState);
          break;
        case 3:
          Joystick.setButton(3, currentButtonState);
          break;
        case 4:
          Joystick.setButton(4, currentButtonState);
          break;
        case 5:
          Joystick.setButton(5, currentButtonState);
          break;
        case 6:
          Joystick.setButton(6, currentButtonState);
          break;
      }
      lastButtonState[index] = currentButtonState;//保存 pin 状态
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
