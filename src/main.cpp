/*telegramBot для контроллю параметрів
*/
#include "mane.h"
#include "telegram_bot.h">"
#include "settings.cpp"

void setup() {
  Serial.begin(115200);
  lightMeter.begin();
  delay(100);
  mq2.calibrate();
  Wire.begin(); // ds18b20
  Serial.begin(9600);
  delay(100);
  sensors.begin();
  delay(100);
  bme.begin(0x76);  
  delay(100); 
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(13, INPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
  
  
  configTime(0, 0, "pool.ntp.org");
  secured_client.setTrustAnchors(&cert);
  Serial.print("Connecting to WiFi SSID ");
  MultyWiFiBegin();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);
  bot.sendMessage(CHAT_ID, "Привіт! Я інкубатор TIMCON!\n напиши мені:/старт", "");

read_sensors();

}

void loop() {
  if(millis() - bot_lasttime > BOT_MTBS)
  {
 read_sensors();
    
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while(numNewMessages)
    {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_lasttime = millis();

    criticalParametrs();
  }

}




