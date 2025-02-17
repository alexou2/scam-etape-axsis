// C++ code
//
#include <Servo.h>

Servo servo_9;
// indexing
int idx = 0; // current position of the gear in teh array
int arr[13] = {0, 15, 30, 45, 60, 75, 90, 105, 120, 135, 150, 165, 180}; // servo position for shifting

// shifting. the values are changed when shifting and are then returned to default
int overshift = 0; // the ammount to overshift. 0 means that the shift is completed
bool in_motion = false; // tells if the shift is completed
float timer = 0; // timer until the shift is completed

void setup()
{
  Serial.begin(9600);
  Serial.println("Start");
  servo_9.attach(9, 500, 2500);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);

}

void loop()
{
  String command = Serial.readStringUntil('\n');

  // pulling the shift cable
  if (command == "up" && idx < 12) {
    actuate_servo(1, 10);
  }
  // releasing the shift cable
  if (command == "down" && idx > 0) {
    actuate_servo(-1, -10);
  }

// for adjusting the position of the servo for each gear
  if (command == "+")
    arr[idx] ++;
  if (command == "-")
    arr[idx] --;

// checking if the servo is in the process of shifting
if (timer > 0) {
    in_motion = true;
    timer --;
  }
  else {
    // resets temporary shifting info
    in_motion = false;
    overshift = 0;
    timer = 0;
    digitalWrite(LED_BUILTIN, LOW);
  }

  // updates the position the servo is supposed to be at
  // changes the servo position
  int position = arr[idx];
  servo_9.write(position + overshift);
  Serial.println(position + overshift);
  delay(50);
}

// changes the gear position
// param 1: the number of gears to shift
// param 2: the ammount of overshifting
void actuate_servo(int new_pos, int over) {

  if (!in_motion) {
    timer = 3;
    digitalWrite(LED_BUILTIN, HIGH);
    overshift = over;
    idx += new_pos;
  }

}
