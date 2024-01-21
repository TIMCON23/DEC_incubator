/*
//файл персональних даних не загружати на gitHub
//-прописуються усі налаштування мереж і назв
//-індивідуальні кліматичні карти інкубації різних птахів
//-шляхи для використання штучного інтелекту у
//відповідях і шифрування, ключі API тощо

*/

#include <Arduino.h>


 char* ssid = "timCon";
 char* password = "nheafy3211971";
 //конфігурація для ідентифікації власника
String phoneNumber= "+380979504647";//діючий телефон для тривожних по
String Email = "timcon2023@gmail.com";//пошта
String Pass_Email = "nheafy3211971";//пароль від електронної скриньки для відправки пошти і даних
String encryption ="тундрик";//слово-пароль для ідентифікації власника
String timcon_login ="timco"; //логін для входу на сервер TIMCON
String timcon_password = "nheafy3211971";//пароль для входу на сервер TIMCON
String id_code =""; //записане числф секунд з NTP для шифрування даних
 

//#define BOT_TOKEN "6743045291:AAFdjuMdZZ6-GyxCDN8ow2UwxJ-0jitYccM" // унікальний номер бота TIMCON_incubator
//#define BOT_TOKEN "6743045291:AAGjjPoynlvWhlecsv2rDwiK4vg2QWG71kA" // перевипущений токет..
//#define BOT_TOKEN "6743045291:AAFdjuMdZZ6-GyxCDN8ow2UwxJ-0jitYccM" // унікальний номер бота
//#define CHAT_ID "5055498216" // код чату отримується//https://api.telegram.org/bot6743045291:AAFdjuMdZZ6-GyxCDN8ow2UwxJ-0jitYccM/getUpdates,(вставляємо токен після слова bоt



#define BOT_TOKEN "5480410299:AAHBogE79UdNZMVSyQob2_Jh6BVcXkNIZQ0" // унікальний номер бота
#define CHAT_ID "5055498216" //код чату

//дані шифрувань та інка конфіденційна інформація
