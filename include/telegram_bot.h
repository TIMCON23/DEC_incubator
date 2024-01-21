#pragma once
const unsigned long BOT_MTBS = 3000;
unsigned long bot_lasttime;
int maxMethane=350;
int maxTemp = 39;
int maxsmoke = 250;
int maxHum = 70;
float maxTemp_egg = 35.2;
bool relay1status = 0;
bool relay2status = 0;

const unsigned long TEMP_MTBS = 3000000; // 5 хв.затримка приходу тривожного повідомлення
unsigned long tame_lasttime;

int relay1= 14; // D5 (digital_PWM-GPIO14) реле для світла
int relay2= 12; // D6 (digital_PWM-GPIO12) реле для камери
