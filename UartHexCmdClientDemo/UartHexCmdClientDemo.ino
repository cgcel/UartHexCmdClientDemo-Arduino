/**
    @file: UartHexCmdClientDemo
    @author: guncung
    @date: 2021-06-05
    @brief: Send a hex cmd via serial, and Arduino returns you a responce data.
*/

#include "SoftwareSerial.h"

/* define recv_cmd and resp_data by yourself */
uint8_t recv_cmd[] = {0x01, 0x04, 0x00, 0x00, 0x00, 0x08, 0xf1, 0xcc};
uint8_t resp_data[] = {0x01, 0x04, 0x10, 0x03, 0x34, 0x03, 0x32, 0x03, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9b, 0x83};

uint8_t recv_data[sizeof(recv_cmd)] = {}; // store incoming serial byte
int index = 0;
bool flag = false;

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(20);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (mySerial.available()) {
    uint8_t b = mySerial.read();
    recv_data[index] = b; // store the incoming byte to recv_data
    index++;
  }

  // compare recv_data with recv_cmd
  if (index == sizeof(recv_cmd)) {
    for (int i = 0; i < sizeof(recv_data); i++) {
      flag = true;
      if (recv_data[i] != recv_cmd[i]) {
        flag = false;
        break;
      }
    }
    if (flag) {
      mySerial.write(resp_data, sizeof(resp_data));
      Serial.write(resp_data, sizeof(resp_data));
    }
  }

  delay(50); // necessary delay
  memset(recv_data, 0, sizeof(recv_data)); // reset the array
  index = 0; // reset index
}
