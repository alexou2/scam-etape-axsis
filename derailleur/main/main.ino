// C++ code
//
#include <Servo.h>
#include <EEPROM.h>

int position = 0;
int arr[13] = {-1, 15, 30, 45, 60, 75, 90, 105, 120, 135, 150, 165, 180};
Servo servo_9;
int overshift = 0;
bool in_motion = false;
float timer = 0;

int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;

void setup() {
  servo_9.attach(9, 500, 2500);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(10, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(11, INPUT_PULLUP);

  // dipswitch
  pinMode(7, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
}

void loop() {
  actuate_switch();
  int idx = arr[position];

  if (s4) {
    overshift = 0;
  }

  servo_9.write(idx + overshift);

  if (digitalRead(11) == LOW && position < 12) {
    actuate_servo(1, 10);
  }
  if (digitalRead(10) == LOW && position > 0) {

    actuate_servo(-1, -10);
  }
  if (s3) {
    Serial.println("no cooldown");
    in_motion = false;
    timer = 0;
  }

  if (timer > 0) {
    in_motion = true;

    timer--;
  } else {
    in_motion = false;
    overshift = 0;
    timer = 0;
    digitalWrite(LED_BUILTIN, LOW);
  }
  int s1_time = s1 * 25;
  int s2_time = s2 * 50;
  int sleep_time = s1_time + s2_time + 50;
  Serial.println(sleep_time);
  delay(sleep_time);
}

void actuate_switch() {
  s1 = digitalRead(7);
  s2 = digitalRead(6);
  s3 = digitalRead(5);
  s4 = digitalRead(4);
}

void actuate_servo(int new_pos, int over) {

  // Serial.println(new_pos);
  if (!in_motion) {
    timer = 3;
    digitalWrite(LED_BUILTIN, HIGH);
    overshift = over;
    position += new_pos;
  }
}
