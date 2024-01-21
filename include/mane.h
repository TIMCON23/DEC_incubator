//конфігураційний файл
#pragma once
#include <EEPROM.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <UniversalTelegramBot.h>
#include <TroykaMQ.h>
#include <MQ2.h>
#include <Wire.h>
#include <OneWire.h>                   // бібліотека для роботи з протоколом OneWire 
#include <DallasTemperature.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <BH1750.h>

#include "settings.cpp"

#define PIN_MQ2 A0
#define LED D4   
//#define PIN 4                       // світлодіод внутрішній на платі реверсний
#define ONE_WIRE_BUS 15 // D8 ESP8266
#define relay1 14 // D5 (digital_PWM-GPIO14) реле для світла
#define relay2 12 // D6 (digital_PWM-GPIO12) реле для камери

MQ2 mq2(PIN_MQ2);
OneWire oneWire(ONE_WIRE_BUS);  
DallasTemperature sensors(&oneWire);
Adafruit_BME280 bme; // на шині i2C
#define SEALEVELPRESSURE_HPA (1013.25)


BH1750 lightMeter;
WiFiClientSecure secured_client;
//Конфiгурация телеграм

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

//для роботи з пам'яттю
int maxTempAddress = 10;
int minTempAddress = maxTempAddress + sizeof(float);
int maxHumAddress = minTempAddress + sizeof(float);
int minHumAddress = maxHumAddress + sizeof(float);
int maxEggAddress = minHumAddress + sizeof(float);
int minEggAddress = maxEggAddress + sizeof(float);
int maxMethaneAddress = minEggAddress + sizeof(float);
int maxSmokeAddress = maxMethaneAddress + sizeof(int);

//int maxTempAddress = 10; // стартові ячейки для записування даних у пам'ять(4 байти для типу float)
//int minTempAddress = 14; //(4 байти для типу float)
//int maxHumAddress = 18; //(4 байти для типу float)
//int minHumAddress = 22;//(4 байти для типу float)
//int maxEggAddress = 26;//(4 байти для типу float)
//int minEggAddress = 30;//(4 байти для типу float)
//int maxMethaneAddress = 34;//(2 байти для типу int)
//int maxSmokeAddress = 36;//(2 байти для типу int)

// вільні ячейки з 38 по 42

int phoneNumberAddress = 50;//( стартова ячейка для запису телефона (13 байт)
int loginTIMCONAddress = 64;//( тартова ячейка для запису kjusyf для типу String) до 25 символів
int emailAddress = loginTIMCONAddress+sizeof(String);// ( байти для типу String) до 30 символів
//int id_codeAddress = emailAddress + sizeof(String); // Початкова адреса для запису

//параметри максимумів і мінімумів можна вводити з сторінки web через додаток з телеграм каналу через головну плату і її способи
float maxTemp = 35.00;
float minTemp = 33.00;
float maxHum = 85.00;
float minHum = 45.00;
float maxEgg = 38.9;
float minEgg = 38.1;
int maxMethane= 350;
int maxsmoke = 250;
float epsilon = 0.10; // Точність порівняння 0.1
bool relay1status = LOW;
bool relay2status = LOW;
bool incubatorControl=false;
const unsigned long TEMP_MTBS = 150000; // 2,5 хв.між приходом тривожних повідомлення
unsigned long tame_lasttime;
float temperature_air,  temperature_egg, humidity_inc, pressure_inc;
int dust_1, dust_2, windSpeed,lighting;

bool shouldRestart = false;
//функції
void read_sensors();
void handleNewMessages(int numNewMessages);
void criticalParametrs();
void MultyWiFiBegin();
void saveFloatValueToEEPROM(float value, int address);
void saveIntValueToEEPROM(int value, int address);
void saveStringValueToEEPROM(String value, int address, int size);
void readValuesFromMemory();
void readValuesFromMemory();



