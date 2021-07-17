#include <Servo.h>
#define LEFTWHEEL 13
#define RIGHTWHEEL 12
#define CAMERA 11

Servo LeftServo;
Servo RightServo;
Servo TopServo;

//Tagged string sent through serial
String driver_wish;

//Values for the servos extracted from driver wish
String top_servo;
String left_servo;
String right_servo;

void setup()
{
  Serial.begin(460800);
  LeftServo.attach(LEFTWHEEL);
  RightServo.attach(RIGHTWHEEL);
  TopServo.attach(CAMERA);
}

void loop()
{
  if (Serial.available()) {
    read_driver_wish();
    control_servos();
  }
}

void control_servos()
{
  LeftServo.write(left_servo.toInt());
  RightServo.write(right_servo.toInt());
  TopServo.write(top_servo.toInt());
}

void read_driver_wish()
{
  driver_wish = Serial.readStringUntil('\n');
  left_servo = extract(driver_wish, "!", "%");
  right_servo = extract(driver_wish, "%", "#");
  top_servo = extract(driver_wish, "#", "&");
}

void print_driver_wish()
{
  Serial.println("Left Servo: " + left_servo);
  Serial.println("Right Servo: " + right_servo);
  Serial.println("Top Servo: " + top_servo);
}

void test_value()
{
  String test_val = Serial.readStringUntil('n');
  int output = test_val.toInt();

  LeftServo.write(output);
}

String extract(String str, String start, String finish)
{
  int locStart = str.indexOf(start);
  if (locStart == -1)
    return "";
  locStart += start.length();
  int locFinish = str.indexOf(finish, locStart);
  if (locFinish == -1)
    return "";
  return str.substring(locStart, locFinish);
}
