/* перевірка посилок з телеграмбота
*/
#include <cstring>
#include "mane.h"
#include "settings.cpp"

void handleNewMessages(int numNewMessages){

  for (int i = 0; i < numNewMessages; i++) 
      {
    if (bot.messages[i].chat_id == CHAT_ID) 
      {
        String command = bot.messages[i].text;
        Serial.println("отримано команду: " + command);

        if (command.startsWith("/maxTemp:")) {
          maxTemp = command.substring(9).toFloat();
          bot.sendMessage(bot.messages[i].chat_id, "Максимальна температура контролю: " + String(maxTemp), "");
        
        // вписати перевірку чи таке значення в пам'яті, якщо інше - то записуємо
          saveFloatValueToEEPROM(maxTemp, maxTempAddress);
           } 
          else if (command.startsWith("/minTemp:")) {
          minTemp = command.substring(9).toFloat();
          bot.sendMessage(bot.messages[i].chat_id, "Мінімальна температура контролю: " + String(minTemp), "");
        
          saveFloatValueToEEPROM(minTemp, minTempAddress);
          }
          else if (command.startsWith("/maxHum:")) {
          maxHum = command.substring(8).toFloat();
          bot.sendMessage(bot.messages[i].chat_id, "Максимальна вологість контролю: " + String(maxHum), "");

          saveFloatValueToEEPROM(maxHum, maxHumAddress);
          }
          else if (command.startsWith("/minHum:")) {
          minHum = command.substring(8).toFloat();
          bot.sendMessage(bot.messages[i].chat_id, "Мінімальна вологість контролю: " + String(minHum), "");
          saveFloatValueToEEPROM(minHum, minHumAddress);
          }
          else if (command.startsWith("/maxEgg:")) {
          maxEgg = command.substring(8).toFloat();
          bot.sendMessage(bot.messages[i].chat_id, "Максимальна температура яйця: " + String(maxEgg), "");

          saveFloatValueToEEPROM( maxEgg, maxEggAddress);
          } 
          else if (command.startsWith("/minEgg:")) {
          minEgg = command.substring(8).toFloat();
          bot.sendMessage(bot.messages[i].chat_id, "Мінімальна температура яйця: " + String(minEgg), "");

          saveFloatValueToEEPROM(minEgg, minEggAddress);
          }
          else if (command.startsWith("/maxMethane:")) {
          maxMethane = command.substring(12).toInt();
          bot.sendMessage(bot.messages[i].chat_id, "Максимальний рівень Метану: " + String(maxMethane), "");

          saveIntValueToEEPROM(maxMethane, maxMethaneAddress);
          }
          else if (command.startsWith("/maxSmoke:")) {
          maxsmoke = command.substring(10).toInt();
          bot.sendMessage(bot.messages[i].chat_id, "Максимальний рівень диму: " + String(maxsmoke), "");

          saveIntValueToEEPROM( maxsmoke, maxSmokeAddress);
          }
          else if (command.startsWith("/phoneNumber:")) {
          String newPhoneNumber = command.substring(13); // Отримуємо новий номер телефону, починаючи з 13-го символу
            int phoneNumberSize = newPhoneNumber.length(); // Визначаємо розмір нового номера телефону
               Serial.print("символів у новому телефоні: ");
                Serial.println(phoneNumberSize);
              if(phoneNumberSize==13)
                {bot.sendMessage(bot.messages[i].chat_id, "Внесено телефон: " + newPhoneNumber, "");
                  saveStringValueToEEPROM(newPhoneNumber, loginTIMCONAddress, phoneNumberSize);
                  phoneNumber=newPhoneNumber;
                }
               else {bot.sendMessage(bot.messages[i].chat_id, "помилка телефона: " + newPhoneNumber, "");
            }
         } 
          
          
          
          
          //зміна string 
          
          
          else if (command.startsWith("/login_TIMCON:")) {
            String newLoginTIMCON = command.substring(14); // Отримуємо новий логін TIMCON, починаючи з 14-го символу
              int loginTIMCONSize = newLoginTIMCON.length(); // Визначаємо розмір нового логіна TIMCON
              saveStringValueToEEPROM(newLoginTIMCON, loginTIMCONAddress, loginTIMCONSize);
              bot.sendMessage(bot.messages[i].chat_id, "Внесено логін сервера TIMCON: " + newLoginTIMCON, "");
              timcon_login=newLoginTIMCON;
            }
          else if (command.startsWith("/email:")) {
            String newEmail = command.substring(7); // Отримуємо нову адресу електронної пошти, починаючи з 7-го символу
            int emailSize = newEmail.length(); // Визначаємо розмір нової адреси електронної пошти
             saveStringValueToEEPROM(newEmail, emailAddress, emailSize);
             bot.sendMessage(bot.messages[i].chat_id, "Внесено адресу електронної пошти: " + newEmail, "");
             Email=newEmail;
} 

          else if (command.startsWith("/ssid:")) {
                  String newSsid = command.substring(6);

                        size_t ssidSize = newSsid.length() + 1;  // +1 для завершального символу '\0'
                      char* newSsidPtr = new char[ssidSize];
                       strncpy(newSsidPtr, newSsid.c_str(), ssidSize - 1);
                       newSsidPtr[ssidSize - 1] = '\0';

                       delete ssid;  // Видалення попереднього значення в змінній ssid                       ssid = newSsidPtr;

                   bot.sendMessage(bot.messages[i].chat_id, "SSID оновлено: " + String(ssid[0]), "");
                }
          
          else if (command.startsWith("/pass:")) {
                        String newPass = command.substring(6); // Виправлення індексу зміщення

                        size_t passSize = newPass.length() + 1;  // +1 для завершального символу '\0'
                        char* newPassPtr = new char[passSize];
                        strncpy(newPassPtr, newPass.c_str(), passSize - 1);
                        newPassPtr[passSize - 1] = '\0';

                        delete password;  // Видалення попереднього виділеного блоку пам'яті
                        password = newPassPtr;

                        bot.sendMessage(bot.messages[i].chat_id, "password 1 оновлено: " + String(password[0]), "");
                        }
       
          else if (command == "/reset") {
             String alarm = "Проводиться перезавантаження!\n";
             bot.sendMessage(CHAT_ID, alarm, "");
             Serial.println("перезавантаження модуля");
             delay(500);
             shouldRestart = true;
            
          }
          else if (command == "/operatorBot") {
          String person = "Дані про власника:\n";
            person += "Логін: " + timcon_login + "\n";
            person += "Телефон: " + phoneNumber + "\n";
            person += "Електронна пошта: " + Email + "\n";
            bot.sendMessage(CHAT_ID, person, "");
          }
          else if (command == "/climate"){
      
          String str = "клімат в інкубаторі:\n";
          str+="Температура: " + String(temperature_air)+" °C;\n";
          str+="Вологість: " + String(humidity_inc)+" %HR;\n";
          str+="Атм.тиск: " + String(pressure_inc)+" мм.рт.cт;\n";
          if (temperature_egg != DEVICE_DISCONNECTED_C) {
              str+="Темп_яйця: " + String(temperature_egg)+" °C;\n";
          }else {
              str+="Темп_яйця: non °C;\n";
          }
          str+="Метан: " + String(dust_1)+" ppm;\n";
          str+="Дим: " + String( dust_2)+" ppm\n";
          str+="Швидкість вентилятора: " + String(windSpeed)+" м.с;\n";
          str+="Яскравість: " + String(lighting)+" люкс;\n";
        //якщо включений режим контролю
        if(incubatorControl==true){
          str+="включено режим подвійного контролю \n";
              if (digitalRead(relay1) == HIGH) {
          str+="світло включено. \n"; 
              } else {str+="світло виключено.\n"; 
              }
        if (digitalRead(relay2) == HIGH) {
          str+="камеру включено. \n"; 
              } else {str+="камеру виключено.\n";
              }
           }
        bot.sendMessage(CHAT_ID, str, "");
      }
          else if (command == "/incubatorControl") {
          digitalWrite(LED_BUILTIN, LOW);  // включаємо на платі світлодіод, що означає включено подвійний контроль
          incubatorControl = true;// піднімаємо флаг що здійснюється подвійний контроль параметрів
          bot.sendMessage(CHAT_ID, "встановлено подвійний контроль параметрів інкубатора \n");
        }
          else if (command == "/stopControl") {
          digitalWrite(LED_BUILTIN, HIGH);  // виключаємо на платі світлодіод, що означає виключено подвійний контроль
          incubatorControl = false;// піднімаємо флаг що припинено віддправка тривожних повідомлень в телеграм(подвійний контроль параметрів не здійснюється)
          bot.sendMessage(CHAT_ID, "віддалений контроль параметрів інкубатора припинено \n");
        }
          else if (command == "/settings"){
     String setting = "утримуйте 1 сек. відповідну команду.Двокрапка і параметри\n";
          setting += "/maxTemp: - максимальна температура інкубатора\n";
          setting += "/minTemp: - мінімальна температура інкубатора\n";
          setting += "/maxHum: - максимальна вологість інкубатора\n";
          setting += "/minHum: - мінімальна вологість інкубатора\n";
          setting += "/maxEgg: - максимальна температура яйця\n";
          setting += "/minEgg: -  мінімальна температура яйця\n";
          setting += "/maxMethane: - максимальна рівень Метану\n";
          setting += "/maxsmoke: - максимальна рівень диму\n";
          setting += "/phoneNumber: - номер телефону власника\n";
          setting += "/email: - адреса електронної пошти\n";
          setting += "/login_TIMCON: - логін з сайту TIMCON\n";
          
             
     bot.sendMessage(CHAT_ID, setting, "");
          }
          else if (command == "/parameters") {
             String str = "параметри контролю в інкубаторі:\n";
          str+="максимальна температура: " + String(maxTemp)+" °C;\n";
          str+="мінімальна температура: " + String(minTemp)+" °C;\n";
          str+="максимальна вологість: " + String(maxHum)+" %HR;\n";
          str+="мінімальна вологість: " + String(minHum)+" %HR;\n";
          str+="максимальна температура яйця: " + String(maxEgg)+" °C;\n";
          str+="мінімальна температура яйця: " + String(minEgg)+" °C;\n";
          str+="максимальний рівень Метану: " + String(maxMethane)+" ppm;\n";
          str+="максимальний рівень Диму: " + String(maxsmoke)+" ppm;\n";
             bot.sendMessage(CHAT_ID, str, "");
        }
          else if (command == "/cameraOn") {
          digitalWrite(relay1, HIGH);
          relay1status = HIGH;
           bot.sendMessage(CHAT_ID, "камера включена");
      }
          else if (command == "/cameraOff") {
          digitalWrite(relay1, LOW);
          relay1status = LOW;
           bot.sendMessage(CHAT_ID, "камера виключена");
      }
          else if (command == "/lightOn") {
          digitalWrite(relay2, HIGH);
          relay2status = HIGH;
           bot.sendMessage(CHAT_ID, "світло включено");
         }
          else if (command == "/lightOff") {
          digitalWrite(relay2, LOW);
          relay2status = LOW;
           bot.sendMessage(CHAT_ID, "світло виключено");
         }
          else if (command == "/welcome"){
      
        String welcome = "Привіт, я інкубатор TIMCON.\n";
        welcome += "Ось команди які я знаю:\n";
        welcome += "/operatorBot - надам дані про власника бота\n";
        welcome += "/settings - встановимо ваші параметри\n";
        welcome += "/incubatorControl - запущу подвійний контроль інкубатора\n";
        welcome += "/stopControl - відключу подвійний контроль інкубатора\n";
        welcome += "/climate - відпишу клімат в інкубаторі\n";
        welcome += "/parameters - відпишу встановлені параметри клімату\n";
        welcome += "/cameraOn - включу камеру\n";
        welcome += "/cameraOff - виключу камеру\n";
        welcome += "/lightOn - включу світло\n";
        welcome += "/lightOff - виключу світло\n";
        welcome += "/reset: - перезавантаження модуля\n";
        welcome +="мій власник:\n";
        welcome +="Логін: " + timcon_login + "\n";
        welcome +="Телефон: " + phoneNumber + "\n";
        welcome +="Електронна пошта: " + Email + "\n";
        welcome +=(F(" https://teplopar.jimdofree.com \n"));
        bot.sendMessage(CHAT_ID, welcome, "");
      }
          
    }
        else {
          bot.sendMessage(bot.messages[i].chat_id, "помилка команди!", "");
        }
  }
}