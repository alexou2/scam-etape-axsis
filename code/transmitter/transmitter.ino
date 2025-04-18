#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(10, 9); // CE, CSN

const byte address[6] = "00001";

enum Signals {
  NONE,
  GEAR_UP,
  GEAR_DOWN,
  SET_GEAR,
  TRIM_UP,
  TRIM_DOWN,
};
bool in_debug_mode = false;


void setup() {
  radio.begin();
  Serial.begin(9600);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);

  // optimizations
  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(2, 2);
  radio.disableDynamicPayloads();
  radio.setAutoAck(true);
  // optimizations end


  radio.stopListening();

  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);

  //  pinMode(11, INPUT_PULLUP);
}

void loop() {
  //  Serial.println("ss");

  int buttonState = digitalRead(7);
  int button2State = digitalRead(8);
  int debug_button_state = digitalRead(2);

  Signals command = NONE;
  //  if (buttonState == LOW && button2State == LOW) {
  //    String prompt = Serial.readStringUntil('\n');

  //    if (prompt == "setup") {
  if (debug_button_state == LOW && !in_debug_mode ) {
    Serial.println("setup");
    in_debug_mode = true;
    delay(1000);
    return;
  }
  //    if ( prompt == "set") {
  if (debug_button_state == LOW && in_debug_mode ) {
    command = SET_GEAR;
    Serial.println("set");
    in_debug_mode = false;
    delay(1000);

    buttonState = HIGH;
    button2State = HIGH;
  }
  //  }


  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW) {
    if (in_debug_mode) {
      command = TRIM_UP;
    } else {
      command = GEAR_UP;
    }

    // turn LED on:
  }
  if (button2State == LOW) {
    if (in_debug_mode) {
      command = TRIM_DOWN;
    } else {
      command = GEAR_DOWN;
    }
    // turn LED on:
  }
  if (command != NONE) {
    // enabling and disabling the radio to save power
    //    radio.powerUp();
    int status = radio.write(&command, sizeof(command));
    Serial.println(command);
    //    radio.powerDown();

  }


  //  Serial.println(command);
  delay(120);
}
