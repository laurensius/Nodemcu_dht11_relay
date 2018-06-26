#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <dht.h>

#define BAUDRATE 115200

const char* ssid = "863 Studio - Office";
const char* password = "f(x)=2x^2+3x+4";

String server = "http://iot-project.laurensius-dede-suhardiman.com/index.php/api/save_data/";

dht DHT;

int respon_dht11 = 0;
 
void setup () {
  Serial.begin(BAUDRATE);
  WiFi.begin(ssid, password);
  Serial.println("==================================================");
  Serial.println("|| Hello World!                                 ||");
  Serial.println("|| IoT Project - Laurensius Dede Suhardiman!    ||");
  Serial.println("==================================================");
  Serial.println("Setting ESP8266");
  delay(1000);
  inisialisasi_dht11();
  wifiConnecting();
}
 
void loop() {
  if (WiFi.status() == WL_CONNECTED) { 
    String data = ambil_data_dht11();
    String req = server + data;
    HTTPClient http;  
    http.begin(req);  
    int httpCode = http.GET();                                                       
    if (httpCode > 0) { 
      String payload = http.getString();
      Serial.println(payload); 
    }
    http.end();   
  }else
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("ESP8266 tidak terhubung ke Access Point");
    wifiConnecting();
  }
  delay(1000);
}

void wifiConnecting(){
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Menghubungkan ke Access Point");
    for(int c=0;c<3;c++){
      Serial.print(" .");
      delay(1000);  
    }
    Serial.println();
  }
}

void inisialisasi_dht11(){
  respon_dht11 = DHT.read11(1);
  switch (respon_dht11){
    case DHTLIB_OK:  
      Serial.println("Status: OK");
      Serial.println("Setup berhasil!");
      break;
    case DHTLIB_ERROR_CHECKSUM: 
      Serial.println("Status: Checksum error");
      break;
    case DHTLIB_ERROR_TIMEOUT: 
      Serial.println("Status: Time out error");
      break;
    case DHTLIB_ERROR_CONNECT:
      Serial.print("Status: Connect error");
      break;
    case DHTLIB_ERROR_ACK_L:
      Serial.print("Status: Ack Low error");
      break;
    case DHTLIB_ERROR_ACK_H:
      Serial.print("Status: Ack High error");
      break;
    default: 
      Serial.println("Status: Unknown error"); 
      break;
  }
  delay(2000);
}

String ambil_data_dht11(){
  String data;
  Serial.print("Temperatur : ");
  Serial.println(DHT.temperature);
  Serial.print("Kelembaban : ");
  Serial.println(DHT.humidity);
  delay(1000);
  String temperature = String(DHT.temperature);
  String humidity = String(DHT.humidity);
  data = temperature + "/" + humidity + "/ " ;
  return data;
}


