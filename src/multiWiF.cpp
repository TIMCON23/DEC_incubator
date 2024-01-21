#include <mane.h>


int ssid_count=0; // лічильник пар доступних пар (логін-пароль)
const char* ssid[] = {"timCon","OLAX_4G_D101", "Galaxy A22 5Ga1e6"}; // масив назв доступних мереж WiFi
const char* password[] = {"nheafy3211971","63613254","rgca9534"}; //масив паролів доступних мереж WiFi



void MultyWiFiBegin() {
  // Підключаємось платою до пари wifi-password
  int ssid_count = 0;
  int ssid_mas_size = sizeof(ssid) / sizeof(ssid[0]);
   WiFi.mode(WIFI_STA);
  do {
    Serial.println("Trying to connect to wi-fi " + String(ssid[ssid_count]));
    WiFi.begin(ssid[ssid_count], password[ssid_count]);   
    int WiFi_timeout_count = 0;
    while (WiFi.status() != WL_CONNECTED && WiFi_timeout_count < 10) { // Чекаємо 10 секунд
      delay(1000); // Затримка в 1 секунду
      Serial.print(".");
      ++WiFi_timeout_count;
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Connected");
     
      break; // Вихід з циклу, якщо підключення вдале
    } else {
      Serial.println("Connection failed!");
    }
    ++ssid_count;
  } while (ssid_count < ssid_mas_size && WiFi.status() != WL_CONNECTED);
}