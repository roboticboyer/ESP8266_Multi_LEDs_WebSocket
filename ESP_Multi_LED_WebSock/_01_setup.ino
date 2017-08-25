/*
 * ESP8266 Web server with Web Socket to control an LED.
 *
*/


//-----------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.setDebugOutput(true);



  for(uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] BOOT WAIT %d...\r\n", t);
    //Serial.flush();
    delay(1000);
  }

// Connection to WIFI
	Wifi_STA_Connect();
 
//Set LED1
  pinMode(LEDPIN[0], OUTPUT);
  writeLED(0);

/*  
//Set LED2
    pinMode(LEDPIN[1], OUTPUT);
  writeLED(0);
//set LED3
    pinMode(LEDPIN[2], OUTPUT);
  writeLED(0);
//set LED4
    pinMode(LEDPIN[3], OUTPUT);
  writeLED(0);
*/

/*
//--- MDNS
  if (mdns.begin("espWebSock", WiFi.localIP())) {
    Serial.println("MDNS responder started");
    mdns.addService("http", "tcp", 80);
    mdns.addService("ws", "tcp", 81);
  }
  else {
    Serial.println("MDNS.begin failed");
  }

  
  Serial.print("Connect to http://espWebSock.local");
*/

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.begin();

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

