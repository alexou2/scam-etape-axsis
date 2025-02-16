// C++ code
//
#include <Servo.h>

int position = 0;
int arr[13] = {0,15,30, 45,60, 75, 90, 105, 120, 135, 150, 165, 180};
Servo servo_9;
int overshift = 0;
bool in_motion = false;
float timer = 0;




void setup()
{
  Serial.begin(9600);
  Serial.println("Start");
  servo_9.attach(9, 500, 2500);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(10, INPUT_PULLUP);
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(11, INPUT_PULLUP);
  
}

void loop()
{

  int idx = arr[position];
  
 String command = Serial.readStringUntil('\n');
 
  servo_9.write(idx+overshift);


  if (command == "up" && position<12) {
    actuate_servo(1, 10);

  }
  if (command == "down" && position>0) {

    actuate_servo(-1, -10);

  }
  
  
  
 if (timer >0){
  in_motion=true;
   
   timer --;
 }
  else {
    in_motion = false;
    overshift = 0;
    timer = 0;
    digitalWrite(LED_BUILTIN, LOW);
  }
  Serial.println(idx+overshift);
  delay(50);
}

void actuate_servo(int new_pos, int over){
  
  
  if (!in_motion){
    timer = 3;
    digitalWrite(LED_BUILTIN, HIGH);
    overshift = over;
    position += new_pos;
  }
  
}
