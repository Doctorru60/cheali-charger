/*
    cheali-charger - open source firmware for a variety of LiPo chargers
    Copyright (C) 2013  Paweł Stawicki. All right reserved.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <Arduino.h>

#include "GTPowerA6-10-pins.h"
#include "GTPowerA6-10.h"
#include "adc.h"

void hardware::initialize()
{
    pinMode(BACKLIGHT_PIN, OUTPUT);
    pinMode(OUTPUT_DISABLE_PIN, OUTPUT);
    pinMode(FAN_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    pinMode(BALANCER1_LOAD_PIN, OUTPUT);
    pinMode(BALANCER2_LOAD_PIN, OUTPUT);
    pinMode(BALANCER3_LOAD_PIN, OUTPUT);
    pinMode(BALANCER4_LOAD_PIN, OUTPUT);
    pinMode(BALANCER5_LOAD_PIN, OUTPUT);
    pinMode(BALANCER6_LOAD_PIN, OUTPUT);


    pinMode(SMPS_VALUE_PIN, OUTPUT);
    pinMode(SMPS_DISABLE_PIN, OUTPUT);
    pinMode(DISCHARGE_VALUE_PIN, OUTPUT);
    pinMode(DISCHARGE_DISABLE_PIN, OUTPUT);

    setBatteryOutput(false);
    setFan(false);
    setBuzzer(0);
    setBalancer(0);

    lcd.begin(LCD_COLUMNS, LCD_LINES);
    Timer1.initialize(TIMER1_PERIOD_MICROSECONDS);         // initialize timer1, and set a 1/2 second period
    adc::initialize();
}

void hardware::setLCDBacklight(uint8_t val)
{
    uint32_t v1,v2;
    v1  = LCD_BACKLIGHT_MAX;
    v1 *= val;
    v2  = LCD_BACKLIGHT_MIN;
    v2 *= 100 - val;
    v1+=v2;
    v1/=100;
    Timer1.pwm(BACKLIGHT_PIN, v1);
}

void hardware::setFan(bool enable)
{
    digitalWrite(FAN_PIN, enable);
}
void hardware::setBuzzer(uint8_t val)
{
    //TODO: this should be rewritten, sorry for that :D
    //Timer2 is now used by the Timer.cpp implementation
    digitalWrite(BUZZER_PIN, !(val&1));
}

void hardware::setBatteryOutput(bool enable)
{
    digitalWrite(OUTPUT_DISABLE_PIN, !enable);
}
void hardware::setChargerOutput(bool enable)
{
    digitalWrite(SMPS_DISABLE_PIN, !enable);
}
void hardware::setDischargerOutput(bool enable)
{
    digitalWrite(DISCHARGE_DISABLE_PIN, !enable);
}

void hardware::setChargerValue(uint16_t value)
{
    Timer1.pwm(SMPS_VALUE_PIN, value);
}
void hardware::setDischargerValue(uint16_t value)
{
    Timer1.pwm(DISCHARGE_VALUE_PIN, value);
}

void hardware::setBalancer(uint8_t v)
{
    digitalWrite(BALANCER1_LOAD_PIN, v&1);
    digitalWrite(BALANCER2_LOAD_PIN, v&2);
    digitalWrite(BALANCER3_LOAD_PIN, v&4);
    digitalWrite(BALANCER4_LOAD_PIN, v&8);
    digitalWrite(BALANCER5_LOAD_PIN, v&16);
    digitalWrite(BALANCER6_LOAD_PIN, v&32);
}

void hardware::setBalancerOutput(bool enable)
{
}

LiquidCrystal lcd;

