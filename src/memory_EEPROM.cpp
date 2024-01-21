#include"mane.h"


void saveFloatValueToEEPROM(float value, int address) {
  EEPROM.begin(512);
  float storedValue;
  EEPROM.get(address, storedValue);
  
  if (value != storedValue) {
    EEPROM.put(address, value);
    EEPROM.commit();
  }
  
  EEPROM.end();
}

void saveIntValueToEEPROM(int value, int address) {
  EEPROM.begin(512);
  int storedValue;
  EEPROM.get(address, storedValue);
  
  if (value != storedValue) {
    EEPROM.put(address, value);
    EEPROM.commit();
  }
  
  EEPROM.end();
}
void saveStringValueToEEPROM(String value, int address, int size) {
  EEPROM.begin(512);
  String storedValue;
  storedValue.reserve(size);
  
  for (int i = 0; i < size; i++) {
    storedValue += char(EEPROM.read(address + i));
  }
  
  if (value != storedValue) {
    for (int i = 0; i < size; i++) {
      EEPROM.write(address + i, value[i]);
    }
    EEPROM.commit();
  }
  
  EEPROM.end();
}
void readValuesFromMemory() { // зчитування ручних налаштувань контролю
  
  EEPROM.get(maxTempAddress, maxTemp);
  if (maxTemp < 20.0 || maxTemp > 40.0) {
    // Значення не в межах допустимого діапазону, встановлюємо значення за замовчуванням
    maxTemp = 35.0;
    EEPROM.put(maxTempAddress, maxTemp);
    EEPROM.commit(); // Збереження змін до EEPROM
    }
   
  EEPROM.get(minTempAddress, minTemp);
  if (minTemp < 20.0 || minTemp > 40.0) {
    // Значення не в межах допустимого діапазону, встановлюємо значення за замовчуванням
    maxTemp = 35.0;
    EEPROM.put(minTempAddress, minTemp);
    EEPROM.commit(); // Збереження змін до EEPROM
    }
  EEPROM.get(maxHumAddress, maxHum);
 if (maxHum < 40.0 || maxHum > 90.0) {
    // Значення не в межах допустимого діапазону, встановлюємо значення за замовчуванням
    maxHum = 75.0;
    EEPROM.put(maxHumAddress, maxHum);
    EEPROM.commit(); // Збереження змін до EEPROM
    }
  EEPROM.get(minHumAddress, minHum);
  if (minHum < 40.0 || minHum > 90.0) {
    // Значення не в межах допустимого діапазону, встановлюємо значення за замовчуванням
    minHum = 45.0;
    EEPROM.put(minHumAddress, minHum);
    EEPROM.commit(); // Збереження змін до EEPROM
    }
  EEPROM.get(maxEggAddress, maxEgg);
  if (maxEgg < 30.0 || maxEgg > 40.0) {
    // Значення не в межах допустимого діапазону, встановлюємо значення за замовчуванням
    maxEgg = 38.8;
    EEPROM.put(maxEggAddress, maxEgg);
    EEPROM.commit(); // Збереження змін до EEPROM
    }
  
  EEPROM.get(minEggAddress, minEgg);
  if (minEgg < 30.0 || minEgg > 40.0) {
    // Значення не в межах допустимого діапазону, встановлюємо значення за замовчуванням
    minEgg = 38.8;
    EEPROM.put(minEggAddress, minEgg);
    EEPROM.commit(); // Збереження змін до EEPROM
  }
  maxMethane = EEPROM.read(maxMethaneAddress);
  if (maxMethane < 100 || maxMethane > 500) {
    // Значення не в межах допустимого діапазону, встановлюємо значення за замовчуванням
    maxMethane = 350;
    EEPROM.put(maxMethaneAddress, maxMethane);
    EEPROM.commit(); // Збереження змін до EEPROM
  }
  maxsmoke = EEPROM.read(maxSmokeAddress);
if (maxsmoke < 100 || maxsmoke > 500) {
    // Значення не в межах допустимого діапазону, встановлюємо значення за замовчуванням
    maxsmoke = 350;
    EEPROM.put(maxSmokeAddress, maxsmoke);
    EEPROM.commit(); // Збереження змін до EEPROM
  }

  Serial.print("Max Temperature: ");
  Serial.println(maxTemp);
  Serial.print("Min Temperature: ");
  Serial.println(minTemp);
  Serial.print("Max Humidity: ");
  Serial.println(maxHum);
  Serial.print("Min Humidity: ");
  Serial.println(minHum);
  Serial.print("Max Egg: ");
  Serial.println(maxEgg);
  Serial.print("Min Egg: ");
  Serial.println(minEgg);
  Serial.print("Max Methane: ");
  Serial.println(maxMethane);
  Serial.print("Max Smoke: ");
  Serial.println(maxsmoke);
  Serial.println();

}
/*void readValuesFromMemory() {
  value.reserve(size);
  for (int i = 0; i < size; i++) {
    value += char(EEPROM.read(address + i));
  }
}

void saveNumberPhoneToEEPROM(String value, int address, int size) {
  EEPROM.begin(512);
  String storedValue; // читаємо що є в пам'яті
  storedValue.reserve(size); //Цей рядок резервує пам'ять для змінної storedValue, щоб уникнути надмірного використання пам'яті.
  
  for (int i = 0; i < size; i++) {
    storedValue += char(EEPROM.read(address + i));
  }
  int characterCount = countCharacters(value);
  
  
  if ((value != storedValue)&&(characterCount==13))
    {
    for (int i = 0; i < size; i++) {
      EEPROM.write(address + i, value[i]);
    }
    EEPROM.commit();
       
    }
    else {
    Serial.print("Телефон не записаний. Кількість символів у рядку: ");
    Serial.println(characterCount);
       }
  EEPROM.end();
}


int countCharacters(const String& str) {
  int count = 0;
  
  for (int i = 0; i < str.length(); i++) {
    if (str.charAt(i) != '\0') {
      count++;
    }
  }
  
  return count;
}

*/

//функція зчитування даних з пам'яті