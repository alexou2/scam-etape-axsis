// C++ code
//
#include <Servo.h>

int position = 0;
int arr[5] = {1,10, 30, 50, 55};
Servo servo_9;
int overshift = 0;
bool in_motion = false;
int timer = 0
void setup()
{
  servo_9.attach(9, 500, 2500);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(10, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(11, INPUT_PULLUP);
  
}

void loop()
{
  
  int idx = arr[position];
  servo_9.write(idx+overshift);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.println(overshift);
 // overshift = 0;
  if (digitalRead(11) == HIGH && position<5) {
    actuate_servo(10);
  //  overshift = 100;
  }
  if (digitalRead(10) == HIGH && position>0) {
   // position -= 1;
    actuate_servo(-10);

  //  overshift = -100;
  }
  if (digitalRead(10) == HIGH && digitalRead(11) == HIGH){
   //overshift=0; 
  }

//  servo_9.write(idx+overshift);
  delay(500);
  
 if (timer >0){
  in_motion=true;
 }
}


void actuate_servo(int new_pos){
  int current_pos = servo_9.read();
  Serial.println(current_pos);
  if (in_motion){
    position += new_pos;
  }
  
}
