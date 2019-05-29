#include <util/delay.h>
#define pulse 2000

void setup() {
    pinMode(5,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(4,OUTPUT);
    //digitalWrite(5,1);
    digitalWrite(9,0);
    //TCCR1A=0x43;// fast pwm mode 43=on->03=off
    TCCR1B=0x19;// no prescaler and WGM02 is 1
    OCR1AH=0;
    OCR1AL=199;//40kHz  
}
void loop() {
  
  TCCR1A=0x43;
  PORTD =B01110000;//76543210
  delayMicroseconds(10);
  PORTD =B01000000;//76543210
  delayMicroseconds(pulse);
  TCCR1A=0x03;
//  PORTD =B0000000;//76543210
//  PORTD =B01110000;//76543210
//  delay(500);
//  PORTD =B01000000;//76543210
    _delay_ms(200);
}
