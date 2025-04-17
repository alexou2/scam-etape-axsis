#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(10, 9); // CE, CSN


enum Signals {
  NONE,
  GEAR_UP,
  GEAR_DOWN,
  SET_GEAR,
  TRIM_UP,
  TRIM_DOWN,
};
//int indexing[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int indexing[8] = {0, 13, 26, 39, 52, 65, 78, 90};
int current_gear = 0;
int temp_gear_offset = 0; // used when setting a gear in the setup process
Servo servo_9;
int overshift = 0;


const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);

servo_9.attach(8, 500, 2500);

  // optimizations
  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(2, 2);
  radio.disableDynamicPayloads();
  radio.setAutoAck(true);
  // optimizations end


  radio.startListening();
}

void loop() {
  overshift = 0;
  if (radio.available()) {
    Signals command = NONE;
    radio.read(&command, sizeof(command));
    Serial.println(command);
    
    switch (command) {
      case GEAR_UP:
      if(current_gear<7){
        current_gear += 1;
        overshift  = 3;
      }
//        move_servo(indexing[current_gear]);
        break;
      case GEAR_DOWN:
      if(current_gear>0){
        current_gear -= 1;
        overshift = -3;
      }
//        move_servo(indexing[current_gear]);
        break;
      case SET_GEAR:
        // save the gear position ot storage
        if (current_gear < 7 && indexing[current_gear + 1] < indexing[current_gear]) {
          indexing[current_gear + 1] = indexing[current_gear];
          Serial.println("set");
        } else {
          Serial.println(current_gear);
          Serial.println(indexing[current_gear + 1]);
        }
        temp_gear_offset = 0;
        break;
      case TRIM_UP:
        indexing[current_gear] += 2;
        Serial.print("trim:");
        Serial.println(indexing[current_gear]);
        break;
      case TRIM_DOWN:
        indexing[current_gear] -= 2;
        Serial.print("trim:");
        Serial.println(indexing[current_gear]);
        break;
      default:;
    }
    

   
     print_details();
     

  }
   delay(100);
//  sleep_low_power(6);
 servo_9.write(indexing[current_gear] + overshift);

}

void print_details(){
  Serial.print("GEAR: ");
  Serial.print(current_gear);
  Serial.print("  : ");
  Serial.println( indexing[current_gear]);
  
}

void move_servo(float value) {
  Serial.print("GEAR: ");
  Serial.print(current_gear);
  Serial.print('[');
  for (int i = 0; i < 8; i++) {
    Serial.print(indexing[i]);
    Serial.print(", ");
  }
  Serial.println("]/n");
}

void sleep_low_power(int time) {
  radio.stopListening();
  radio.powerDown();

  // Sleep the receiver for a while to save power (simulate low-power operation)
  delay(time/2); // Adjust as needed for your use case

  // Wake up and listen again
  radio.powerUp();
  radio.startListening();
  delay(time/2);
}
