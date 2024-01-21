// обмін з telegramBot

#include "mane.h"
#include "readingSens.h"


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


int  relay1= 14; // D5 (digital_PWM-GPIO14) реле для світла
int  relay2= 12; // D6 (digital_PWM-GPIO12) реле для камери


void handleNewMessages(int numNewMessages)
{
  for(int i = 0; i < numNewMessages; i++)
  {
    if(bot.messages[i].chat_id == CHAT_ID)
    {
      String text = bot.messages[i].text;
       if(text == "/погода")
      {
          String str = "Клімат в інкубаторі:\n";
        str+="Темп_повітря: " + String(temperature_air)+" C;\n";
        str+="Вологість: " + String(humidity)+" %HR;\n";
        str+="Атм.тиск: " + String(pressure)+" мм.рт.cт;\n";
        str+="Темп_яйця: " + String(Temp_egg)+" C;\n";
        str+="Метан: " + String(dust_1)+" ppm;\n";
        str+="Дим: " + String( dust_2)+" ppm\n";
        str+="Швидкість змішувача: " + String(fanSpeed)+" м.с;\n";
        str+="Яскравість: " + String(lighting)+" люкс;\n";
        
        
        bot.sendMessage(CHAT_ID, str, "");
      }
      if (text == "/включи інкубатор") {
          digitalWrite(relay1, HIGH);
          relay1status = HIGH;
          bot.sendMessage(CHAT_ID, "інкубатор включено");
        }
      if (text == "/виключи інкубатор") {
          digitalWrite(relay1, LOW);
          relay1status = LOW;
           bot.sendMessage(CHAT_ID, "інкубатор виключено");
      }
      if (text == "/включи світло") {
          digitalWrite(relay2, HIGH);
          relay2status = HIGH;
           bot.sendMessage(CHAT_ID, "світло включено");
         }
      if (text == "/виключи світло") {
          digitalWrite(relay2, LOW);
          relay2status = LOW;
           bot.sendMessage(CHAT_ID, "світло виключено");
         }
         
      if(text == "/старт" || text == "/привіт")
      {
        String welcome = "Привіт, я інкубатор TIMCON.\n";
        welcome += "Ось команди які я знаю:\n";
        welcome += "/інкубатор - відпишу клітат в інкубаторі \n";
        welcome += "/включи інкубатор - включу інкубатор\n";
        welcome += "/виключи інкубатор - виключу інкубатор\n";
        welcome += "/включи світло - включу світло\n";
        welcome += "/виключи світло - виключу світло\n";
        bot.sendMessage(CHAT_ID, welcome, "");
      }
    }
  }
}         
void criticalParametrs()
{
  if(millis() - tame_lasttime > TEMP_MTBS)
  {
    if(temperature_air >= maxTemp)
    {
      String str = "критична темп.: " + String(temperature_air)+ " C;\n";
      bot.sendMessage(CHAT_ID, str, "");
    }
    if(humidity >= maxHum)
    {
      String str = "критична вол.: " + String(humidity)+ " %HR;\n";
      bot.sendMessage(CHAT_ID, str, "");
    }
    if( dust_2 >= maxsmoke)
    {
      String str = "ДИМ! : " + String( dust_2) + " ppm;\n";
      bot.sendMessage(CHAT_ID, str, "");
    }
    if( maxMethane >= dust_1)
    {
      String str = "Метан!: " + String(maxMethane) + " ppm;\n";
      bot.sendMessage(CHAT_ID, str, "");
    }
    //if(radiation_background >= maxRadian)
    //{
    //  String str = "Радіація!: " + String(radiation_background) + " rad;\n";
    //  bot.sendMessage(CHAT_ID, str, "");
    //  }
 
    
    tame_lasttime = millis();
  }

}