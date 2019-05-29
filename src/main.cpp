#include <Arduino.h>
byte now_s;
byte stateD;
byte stateB;
bool found;
//int pTrig[8] = {13, 10, 11, 12, A0, A1, A2, A3};
int pEcho[8] = {2, 3, 4, 5, 6, 7, 8, 9}; //8,9
//long response[8];
//float distance[8];
byte nearest_index{0};
bool old{1};
byte now{0};
int32_t start{0};
bool activated{0};
int32_t response{0};
bool timeout{0};
float nearest_distance{0};
#define PIR 12
#define pTrig 13
#define pTrigAtmega 5
#define pNowAtmega 4
#define TIME_OUT 123694

void setup()
{
    pinMode(PIR, INPUT_PULLUP);
    pinMode(pTrig, OUTPUT);
    for (int i; i < 8; i++)
    {
        pinMode(pEcho[i], INPUT);
    }
    //pinMode(2, INPUT);
    //digitalWrite(8)
    Serial.begin(115200);
    Serial.println("Started");
}

#include <util/delay.h>

void loop()
{

    now = PINB;
    now &= (1 << pNowAtmega);
    // bool done = 0;
    timeout = false;
    if (now < old)
    {
        PORTB |= (1 << pTrigAtmega);
        _delay_us(10);
        PORTB &= ~(1 << pTrigAtmega);
        activated = 1;
    }
    old = now;
    if (activated)
    {
        start = micros();
        while(((PIND & 0b11111100) < 0b11111100) or ((PINB & 0b00000011) < 0b00000011)){
        
        }
        while (((PIND & 0b11111100) >= 0b11111100)  and ((PINB & 0b00000011) >= 0b00000011)  /* (PIND &= 0b00000100) */)
        {   

            if ((micros() - start) > TIME_OUT)
            {
                timeout = true;
                break;
            }
        }
        stateD = PIND & B11111100;
        stateD >>= 2;
        stateB = PINB & B00000011;
        found = false;
        for (int i = 0; i < 6; i++)
        {
            if (stateD % 2)
            {
                stateD >>= 1;
                continue;
            }
            else
            {
                found = 1;
                nearest_index = i;
                break;
            }
        }
        if (!found)
        {
            if (stateB % 2)
            {
                nearest_index = 7;
            }
            else
            {
                nearest_index = 6;
            }
        }
        response = 0.00015 + micros() - start;
        Serial.println(response);
        Serial.println(nearest_index);
        Serial.println();
        if (!timeout)
        {
            //nearest_distance = response / 29.155;
            activated = 0;
        }else{
            Serial.println("timeout");
        }
    }

    // }else if((now!=old)& now){
    //     old = now;
    // }

    // while (now)
    // {
    //     now = PINB;
    //     now &= (1 << pNowAtmega);
    // }
    // PORTB |= (1 << pTrigAtmega);
    // _delay_us(10);
    // PORTB &= ~(1 << pTrigAtmega);
    // while(!now){
    //     now = PINB;
    //     now &= (1 << pNowAtmega);
    // }

    //int32_t start = micros();
    // while (((PIND & 0b11111100) >= 0b11111100) and ((PINB & 0b00000011) >= 0b00000011))
    // {
    //     if ((micros() - start) > TIME_OUT)
    //     {
    //         break;
    //         timeout = true;
    //         Serial.println("timeout");
    //     }
    // }
    // if (!timeout)
    // {
    //     //Serial.println("stop");
    //     // int32_t response = micros() - start;
    //     // Serial.print("response: ");
    //     // Serial.println(response);
    // //     byte stateD = PIND & B11111100;
        // // byte stateB = PINB & B00000011;
    // //     bool found = false;
    // //     for (int i = 0; i < 8; i++)
    // //     {
    // //         if (stateD % 2)
    // //         {
    // //             stateD >>= 1;
    // //             continue;
    // //         }
    // //         else
    // //         {
    // //             found = 1;
    // //             nearest_index = i;
    // //             break;
    // //         }
    // //     }
    // //     if (!found)
    // //     {
    // //         if (stateB % 2)
    // //         {
    // //             nearest_index = 7;
    // //         }
    // //         else
    // //         {
    // //             nearest_index = 6;
    // //         }
    // //     }
    // //     nearest_distance = response / 29.155;
    // //     Serial.print("i:");
    // //     Serial.println(nearest_index);
    // //     Serial.print("d:");
    // //     Serial.println(nearest_distance);
    // // }

    // if (!now)
    // {
    // if (!now)
    // {
    //             done = true;
    // }

    //Serial.println("activated");
    //Serial.println(now);
    // PORTB |= (1 << pTrigAtmega);
    //delayMicroseconds(10);
    // _delay_us(10);
    // PORTB &= ~(1 << pTrigAtmega);

    // int32_t start = micros();
    // //while ((PIND >= 0xFC) and ((PINB & 0b00000011) == 0x03))
    // while (((PIND & 0b11111100) >= 0b11111100) and ((PINB & 0b00000011) >= 0b00000011))
    // {
    //     if ((micros() - start) > TIME_OUT)
    //     {
    //         break;
    //         timeout = true;
    //         Serial.println("timeout");
    //     }
    // }
    // if(!timeout){
    //     Serial.println("stop");
    //     int32_t response = micros() - start;
    //     Serial.print("response: ");
    //     Serial.println(response);
    //     byte stateD = PIND & B11111100;
    //     byte stateB = PINB & B00000011;
    //     bool found = false;
    //     for (int i = 0; i < 8; i++)
    //     {
    //         if (stateD % 2)
    //         {
    //             stateD >>= 1;
    //             continue;
    //         }
    //         else
    //         {
    //             found = 1;
    //             nearest_index = i;
    //             break;
    //         }
    //     }
    //     if (!found)
    //     {
    //         if (stateB % 2)
    //         {
    //             nearest_index = 7;
    //         }
    //         else
    //         {
    //             nearest_index = 6;
    //         }
    //     }
    //     nearest_distance = response / 29.155;
    //     Serial.print("i:");
    //     Serial.println(nearest_index);
    //     Serial.print("d:");
    //     Serial.println(nearest_distance);
    // }
    // }else{
    //     done = 0;
}
