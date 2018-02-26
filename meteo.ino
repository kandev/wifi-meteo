#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "FS.h"
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266httpUpdate.h>
#include <Ticker.h>
#include <Adafruit_Sensor.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
ADC_MODE(ADC_VCC);                //read supply voltage by ESP.getVcc()

//Main configuration
#define _RED_LED 12
#define _GRN_LED 13
#define _BLU_LED 14
#define _DHTPIN 4
#define _VERSION F("0.193")
#define _PRODUCT F("Meteo-Chupa")
#define _UPDATE_SERVER F("chupa.kandev.com")
#define _UPDATE_PORT 80
#define _UPDATE_URL "/"
#define update_path "/update"
#define update_username "chupa"
#define update_password "apuhc"
#define _DEEPSLEEP_INTERVAL 900   // in seconds, 0 for disable deep sleep
#define _WATCHDOG_TIMEOUT 600     // in seconds
#define _PIN_RESET 0
#define _DHTTYPE DHT22
#define _CONFIG F("/config.json")

String _HOSTNAME = "";

String _SSID;
String _PASS;
String _ADMIN_PASS = "";
bool _CLIENT = false;               // are we client or AP?
bool allow_sleep = true;
unsigned long reset_hold = 0;
volatile int watchdog_counter = 0;
unsigned long switch_hold_time = 0;
unsigned long switch_moment = 0;
unsigned long last_wifi_connect_attempt = 0;
unsigned long blink_millis = 0;
Ticker secondTick;
Ticker wifiReconnectTimer;
Ticker MeteoCheck;                  //dht sensor check
Ticker deep_sleep_countdown;        //delayed deepsleep
ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;
bool off_countdown = false;
WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
DHT dht(_DHTPIN, _DHTTYPE);
float t = 0;
float h = 0;
bool time_moment = true;            //da izmeri li dannite
byte _RED = LOW;
byte _GRN = LOW;
byte _BLU = LOW;
#include "web_static.h"

void watchdog() {
  watchdog_counter++;
  if (watchdog_counter >= _WATCHDOG_TIMEOUT) {
    Serial.println(F("Watchdog kick in!"));
    ESP.restart();
  }
}

String getMacAddress() {
  char mac[12];
  String s = "";
  uint8_t MAC_array[6];
  WiFi.macAddress(MAC_array);
  for (int i = 0; i < sizeof(MAC_array); ++i)
    s += String(MAC_array[i], HEX);
  return s;
}

void send_msg(String s) {
  HTTPClient http;
  String srv = "http://" + String(_UPDATE_SERVER) + "/msg/";
  String payload = "hostname=" + _HOSTNAME + "&mac=" + getMacAddress() + "&msg=" + s;
  http.begin(srv);
  http.addHeader(F("Content-Type"), F("application/x-www-form-urlencoded"));
  int c = http.POST(payload);
  if (c > 0) {
    Serial.print(F(" MSG result code: "));
    Serial.println(c);
  } else {
    Serial.println(F(" MSG sent!"));
  }
}

void send_data() {
  HTTPClient http;
  String srv = "http://" + String(_UPDATE_SERVER) + "/data/";
  String payload = "hostname=" + _HOSTNAME + "&mac=" + getMacAddress() + "&h=" + h + "&t=" + t + "&vcc=" + String(float(ESP.getVcc() / 1000.0)) + "&rssi=" + String(WiFi.RSSI());
  http.begin(srv);
  http.addHeader(F("Content-Type"), F("application/x-www-form-urlencoded"));
  int c = http.POST(payload);
  Serial.print(F("Payload: "));
  Serial.println(payload);
  if (c > 0) {
    Serial.print(F(" Data result code: "));
    Serial.println(c);
  } else {
    Serial.println(F(" Data sent!"));
  }
}

void get_dht() {
  time_moment = true;
}

void go_to_sleep() {
  Serial.print(F("Entering sleep mode for "));
  Serial.print(_DEEPSLEEP_INTERVAL);
  Serial.println(F(" seconds."));
  ESP.deepSleep(_DEEPSLEEP_INTERVAL * 1000000);
}

bool openFS() {
  if (!SPIFFS.begin()) {
    Serial.println(F("[ERR] Не може да бъде монтирана файловат система. Ще бъде направен опит за форматиране."));
    if (!SPIFFS.format())
      Serial.println(F("[ERR] Файловата система не може да бъде форматирана."));
    else
      Serial.println(F("[OK] Файловата система е форматирана успешно."));
    return false;
  }
  return true;
}

void closeFS() {
  SPIFFS.end();
}

void scan_data() {
  if ((!server.authenticate("admin", _ADMIN_PASS.c_str())) && (_CLIENT))
    server.requestAuthentication();
  int w = WiFi.scanNetworks();
  String wifis = "{";
  byte i;
  for (i = 0; i < w; i++) {
    wifis += "\"" + WiFi.SSID(i) + "\":\"" + WiFi.RSSI(i) + "\"";
    if (i < w - 1) wifis += ", ";
  }
  wifis += "}";
  server.send ( 200, F("application/json"), "{ \"ssid\":\"" + String(_SSID) + "\", \
    \"wifis\":" + wifis + " }");
}

void html_root() {
  if ((!server.authenticate("admin", _ADMIN_PASS.c_str())) && (_CLIENT))
    server.requestAuthentication();
  server.send(200, F("text/html"), PAGE_root);
}

void html_favicon() {
  server.send(200, F("image/svg+xml"), PAGE_favicon);
}

void handle_deleteconfig() {
  if (!server.authenticate("admin", _ADMIN_PASS.c_str()))
    server.requestAuthentication();
  if (!SPIFFS.format())
    Serial.println(F("[ERR] Unable to format flash."));
  else
    Serial.println(F("[OK] Flash formatted."));
  Serial.println(F("Restarting..."));
  ESP.restart();
}

void handle_reboot() {
  if (!server.authenticate("admin", _ADMIN_PASS.c_str()))
    server.requestAuthentication();
  Serial.println(F("Restarting..."));
  server.send(200, F("text/html"), F("<meta http-equiv=\"refresh\" content=\"5; url=/\" />[OK] Restarting..."));
  ESP.restart();
}

void checkforupdate() {
  Serial.println(F("Checking for update..."));
  auto ret = ESPhttpUpdate.update(_UPDATE_SERVER, _UPDATE_PORT, _UPDATE_URL, _VERSION);
}

void wifi_connect() {
  if (_SSID == "") _SSID = _HOSTNAME;
  WiFi.hostname(_HOSTNAME);
  if (!_CLIENT) {
    wifiReconnectTimer.detach();
    Serial.printf("SSID: %s\r\n", _SSID.c_str());
    if (_PASS != "") Serial.printf("Password: %s\r\n", _PASS.c_str());
    WiFi.mode(WIFI_AP);
    //    WiFi.setOutputPower(1);
    WiFi.softAP(_SSID.c_str(), _PASS.c_str(), random(1, 13));
    //WiFi.softAPConfig(_IP, _GATE, _MASK);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print(F("To configure the device, please connect to the wifi network and open http://"));
    Serial.println(myIP.toString().c_str());
  } else {
    wifiReconnectTimer.detach();
    Serial.print(F("Connecting to "));
    Serial.println(_SSID.c_str());
    last_wifi_connect_attempt = millis();
    WiFi.mode(WIFI_STA);
    WiFi.begin(_SSID.c_str(), _PASS.c_str());
    while ((WiFi.status() != WL_CONNECTED) && ((millis() - last_wifi_connect_attempt) < 20000)) {
      delay(100);
      Serial.print(".");
      yield();
      if (digitalRead(_PIN_RESET) == 0) return;
    }
    Serial.println();
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println(F("[OK] Connected."));
    } else {
      Serial.println(F("[ERR] Will try again in a minute."));
    }
  }
}

void onWifiConnect(const WiFiEventStationModeGotIP& event) {
  Serial.println(F("Connected to Wi-Fi."));
  _RED = LOW;
  _GRN = HIGH;
  _BLU = LOW;
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
  Serial.println(F("Disconnected from Wi-Fi"));
  wifiReconnectTimer.attach(10, wifi_connect);
  _RED = LOW;
  _GRN = LOW;
  _BLU = HIGH;
}

void setup()
{
  //watchdog init
  secondTick.attach(1, watchdog);
  pinMode(_RED_LED, OUTPUT);
  pinMode(_GRN_LED, OUTPUT);
  pinMode(_BLU_LED, OUTPUT);
  pinMode(_PIN_RESET, INPUT_PULLUP);  //factory reset

  digitalWrite(_RED_LED, HIGH);
  digitalWrite(_GRN_LED, LOW);
  digitalWrite(_BLU_LED, LOW);
  Serial.begin(115200); Serial.println();
  Serial.print(_PRODUCT);
  Serial.print(F(", "));
  Serial.println(_VERSION);
  dht.begin();
  get_dht();
  MeteoCheck.attach(300, get_dht);
  _CLIENT = loadConfig();
  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
  wifi_connect();
  server.on("/configure", handle_configure);
  server.on("/config.json", handle_showconfig);
  server.on("/data", get_data);
  server.on("/scan", scan_data);
  server.on("/reboot", handle_reboot);
  server.on("/", html_root);
  server.on("/favicon.svg", html_favicon);
  server.begin();
  if (_CLIENT) {
    httpUpdater.setup(&server, update_path, update_username, update_password);
    Serial.print(F("Име: "));
    Serial.println(_HOSTNAME);
    Serial.print(F("Получен ИП адрес: "));
    Serial.println(WiFi.localIP().toString().c_str());
  } else {
    _BLU = HIGH;
  }
}

void loop() {
  server.handleClient();

  // FACTORY RESET
  if ((digitalRead(_PIN_RESET) == 0) and (switch_hold_time >= 10000)) {
    switch_hold_time = 0;
    digitalWrite(_RED_LED, HIGH);
    digitalWrite(_GRN_LED, LOW);
    digitalWrite(_BLU_LED, LOW);
    Serial.println(F("Factory reset initiated!"));
    send_msg(F("Factory reset initiated!"));
    delay(1000);
    handle_deleteconfig();
  }

  // Handle button press
  if ((digitalRead(_PIN_RESET) != 0) and (switch_hold_time >= 100)) {
    allow_sleep = !allow_sleep;
    if (allow_sleep) {
      Serial.println(F("Sleep enabled!"));
      deep_sleep_countdown.attach(3, go_to_sleep);
      _RED = LOW;
      _GRN = HIGH;
      _BLU = LOW;
    } else {
      Serial.println(F("Sleep disabled!"));
      deep_sleep_countdown.detach();
      _RED = HIGH;
      _GRN = HIGH;
      _BLU = LOW;
    }
    switch_hold_time = 0;
  }

  //handle blinking frequency
  if (millis() - blink_millis >= 500) {
    digitalWrite(_RED_LED, _RED);
    digitalWrite(_GRN_LED, _GRN);
    digitalWrite(_BLU_LED, _BLU);
    delay(2);
    digitalWrite(_RED_LED, LOW);
    digitalWrite(_GRN_LED, LOW);
    digitalWrite(_BLU_LED, LOW);
    blink_millis = millis();
  }

  if (time_moment) {
    h = dht.readHumidity();
    t = dht.readTemperature();
    Serial.print(F("Temperature: "));
    Serial.print(t);
    Serial.print(F(", Humidity: "));
    Serial.println(h);
    if (isnan(h) || isnan(t) ) {
      Serial.println(F(" Failed to read from DHT sensor!"));
      digitalWrite(_RED_LED, HIGH);
      digitalWrite(_GRN_LED, LOW);
      digitalWrite(_BLU_LED, LOW);
      delay(100);
      digitalWrite(_RED_LED, LOW);
      digitalWrite(_GRN_LED, LOW);
      digitalWrite(_BLU_LED, LOW);
    }
    if (_CLIENT) {
      send_data();
      checkforupdate();
      if (_DEEPSLEEP_INTERVAL > 0) {
        if (allow_sleep)
          deep_sleep_countdown.attach(3, go_to_sleep);
      }
    }
    time_moment = false;
  }
  //switch management
  if (digitalRead(_PIN_RESET) == 0) {
    if (switch_moment == 0) switch_moment = millis();
    switch_hold_time = millis() - switch_moment;
    digitalWrite(_RED_LED, HIGH);
    digitalWrite(_GRN_LED, LOW);
    digitalWrite(_BLU_LED, HIGH);
  } else {
    switch_hold_time = 0;
    switch_moment = 0;
    digitalWrite(_RED_LED, LOW);
    digitalWrite(_GRN_LED, LOW);
    digitalWrite(_BLU_LED, LOW);
  }
  watchdog_counter = 0;
  yield();
}

