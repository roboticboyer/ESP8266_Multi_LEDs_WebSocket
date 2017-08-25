/*
 * ESP8266 Web server with Web Socket to control an LED.
 *
 * The web server keeps all clients' LED status up to date and any client may
 * turn the LED on or off.
 *
 * References:
 * https://github.com/Links2004/arduinoWebSockets
 *
 */

//#include <Arduino.h>

#include <ESP8266WiFi.h>
//#include <ESP8266WiFiMulti.h>
#include <WebSocketsServer.h>
#include <Hash.h>
#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>


const char* ssid = "Rete";
const char* password = "pippo2017";


//MDNSResponder mdns;
void Wifi_STA_Connect();
void Wifi_AP_Connect();
void handleRoot();
void handleNotFound();
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
static void writeLED(int);

IPAddress myIP;
IPAddress staticIP(192,168,1,220);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

//ESP8266WiFiMulti WiFiMulti;

ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

//-----------------------------------------------------------------------

// LED PIN
//static const int LEDPIN = 2; //GPIO 2
//static const int LEDPIN = 0; //GPIO 0
const int LEDPIN[4]={LED_BUILTIN,2,0,5};

// Current LED status
bool LED1_status=0;
bool LED2_status=0;
bool LED3_status=0;
bool LED4_status=0;

//*********************************************************************************************
//ATTENZIONE
//LED2,3,4 SONO DISABILITATI NEL CODICE
//**********************************************************************************************


