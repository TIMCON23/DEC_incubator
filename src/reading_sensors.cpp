#include <mane.h>
#include "readingSens.h"
#include "telegram_bot.h"


void read_sensors(){
    temperature_air= bme.readTemperature();
    temperature_air=constrain(temperature_air,-30,50);
    Serial.println(temperature_air);
    humidity = bme.readHumidity();
    humidity=constrain(humidity,20,90);
     Serial.println(humidity);
    pressure = bme.readPressure() / 100.0F;
    pressure=constrain(pressure,500,1200);
     Serial.print(pressure);
    
    sensors.requestTemperatures(); // Send the command to get temperatures
    Temp_egg = sensors.getTempCByIndex(0);  
    Temp_egg=constrain(Temp_egg,0,40);
    Serial.println(Temp_egg);
          
    
  dust_1= mq2.readMethane();
  dust_1=constrain(dust_1,0,500);
  Serial.println(dust_1);
  dust_2= mq2.readSmoke();
  dust_1=constrain(dust_2,0,700);
  Serial.println(dust_2);
  
  fanSpeed = 5; // обороти міксера
    Serial.println(fanSpeed);
       
  lighting = lightMeter.readLightLevel();//берем показания в люксах
 Serial.println(lighting); 
}