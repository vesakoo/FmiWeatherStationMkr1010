#include <LiquidCrystal.h>
#include <DHT.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include "SSID.h"

#define DHTPIN 9     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   
// initialize the library with the numbers of the MKR Pin: ( From D0 to D5 )
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);
DHT dht(DHTPIN, DHTTYPE);

byte Heart[8] = {
0b00000,
0b01010,
0b11111,
0b11111,
0b01110,
0b00100,
0b00000,
0b00000
};

char server[] = "robo.sukelluspaikka.fi";
WiFiClient cli;
HttpClient client = HttpClient(cli,server,80);
int status = WL_IDLE_STATUS;

void setupWifi(){
  while (status != WL_CONNECTED) {
    status = WiFi.begin(SECRET_SSID, SECRET_PASS);
    delay(10000);
  }
  client.setTimeout(3000);
  printWiFiStatus();
}

void printWiFiStatus() {

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void log(String s){
  Serial.println(s);
}

void setup() {
// setup the LCD’s number of columns and rows:
lcd.begin(16, 2); // If you have 20×4 LCD user (20,4)
lcd.createChar(0, Heart);
 setupWifi();
dht.begin();
}

void loop() {
  
  //delay(2000);
  WiFi.noLowPowerMode();
  client.get("/images/forecast.txt");
  String responce = client.responseBody();
  responce.trim();
  String times = responce.substring(0,15);
  //times.trim();
  String temps = responce.substring(16,16+16);
  //temps.trim();
  String t_outdoors =  responce.substring(16+16+1);
  t_outdoors.trim();
  WiFi.lowPowerMode();
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  int t_int = round(t);
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float f = dht.readTemperature(true);
  float hic = dht.computeHeatIndex(t, h, false);
  lcd.clear();
  lcd.setCursor(0, 0); // Lcd first row is 0
  //lcd.write(byte(0));
  //lcd.print('FOO');
  //lcd.setCursor(2,0);
  lcd.print(String(t_int));
  lcd.print("'C ");
  lcd.print(t_outdoors);
  //lcd.print("'C");
  //lcd.print()
  lcd.setCursor(0, 1);// Lcd second row is 1
  lcd.print("Kosteus:");
  lcd.print(String(h));
  lcd.print("%");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print(times);
  lcd.setCursor(0, 1);
  lcd.print(temps);
   delay(5000);
}