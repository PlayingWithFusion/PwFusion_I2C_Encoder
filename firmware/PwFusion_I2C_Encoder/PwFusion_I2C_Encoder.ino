/***************************************************************************
* File Name: PwFusion_I2C_Encoder.ino
* Processor/Platform: ATtiny841-MMHR (tested)
* Development Environment: Arduino 2.1.1
*
* Designed for use with with Playing With Fusion IFB-40001 I2C Encoder
* Copyright � 2023 Playing With Fusion, Inc.
* SOFTWARE LICENSE AGREEMENT: This code is released under the MIT License.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
* **************************************************************************
* REVISION HISTORY:
* Author		    Date		    Comments
* N. Johnson    2023Oct1   Original version
*
* Playing With Fusion, Inc. invests time and resources developing open-source
* code. Please support Playing With Fusion and continued open-source
* development by buying products from Playing With Fusion!
*
* **************************************************************************
* ADDITIONAL NOTES:
* This file contains functions to flash an AtTiny841-MMHR included in
* the Playing with Fusion i2c encoder interface board (IFB-40001).
* Funcionality is as described below:
*   - Read values from the encoder componet
*   - Pack values into a register struct
*   - Send values over the i2c bus when requested
***************************************************************************/

#include <WireS.h>
#include <ezButton.h>

#include <RotaryEncoder.h>


uint8_t primaryAddress = 0x01;
uint8_t secondaryAddress = 0x02;

#define SW 7   // PA7
#define DT 1   // PA1
#define CLK 0  // PA0

#define ADR_SEL 9

int direction = 1;
ezButton button(SW);

RotaryEncoder enc(CLK, DT, RotaryEncoder::LatchMode::TWO03);

struct memoryMap {
  uint8_t sw;
  uint8_t count;
  uint8_t millisBetweenRotations;
  uint8_t rpm;
  uint8_t direction;
};

volatile memoryMap registerMap = {
  .sw                           = 0x00,
  .count                        = 0x01, 
  .millisBetweenRotations       = 0x02,
  .rpm                          = 0x03,
  .direction                    = 0x04,
};

uint8_t *registerPointer = (uint8_t *)&registerMap;
volatile byte registerPosition;

int counter = 0;

int btnState;

void setup() {

  pinMode(ADR_SEL, INPUT);
  startI2C();
 
  pinMode(SW, INPUT);
  pinMode(DT, INPUT);
  pinMode(CLK, INPUT);

  button.setDebounceTime(5);

}

void startI2C() {
  // Select the correct I2C address based on the state of the ADR jumper
  if (digitalRead(ADR_SEL) == LOW) {
    Wire.begin(primaryAddress);
  } else {
    Wire.begin(secondaryAddress);
  }

  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {

  // Encoder Position
  static int pos = 0;
  enc.tick();

  int newPos = enc.getPosition();
  if (pos != newPos) {
    counter = newPos;
    pos = newPos;

  registerMap.direction = (int)enc.getDirection() + 5;

  }
  
  // Encoder Button
  button.loop();
  if(button.isPressed())
    btnState = 1;

  if(button.isReleased())
    btnState = 0;

  // Assign values
  registerMap.count = counter;
  registerMap.sw = btnState;
  registerMap.rpm = enc.getRPM();
  registerMap.millisBetweenRotations = enc.getMillisBetweenRotations();

}
 
// Gets called when the ATtiny receives an i2c request
void requestEvent() {
  Wire.write(*(registerPointer + registerPosition));
}

void receiveEvent(byte howMany) {
  if (howMany < 1) return;

  registerPosition = Wire.read();
  howMany--;
  if(!howMany) return;
  
}