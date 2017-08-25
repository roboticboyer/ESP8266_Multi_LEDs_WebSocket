/*
 * ESP8266 Web server with Web Socket to control an LED.
 *
*/


//----------------------------------------------------------------------- 
// Station Configuration
//-----------------------------------------------------------------------
void Wifi_STA_Connect(){
  WiFi.setAutoConnect(true);
  //WiFi.setAutoConnect (false); //disatttivo autoconnect
  if (!WiFi.config(staticIP, gateway, subnet)){
    Serial.println("Static IP has not been set correctly");
    };
  //WiFi.config(IPAddress(192,168,1,220), IPAddress(192,168,1,1),IPAddress(255,255,255,0));
  if (WiFi.status() != WL_CONNECTED) {
   
  WiFi.persistent(false); // Do not memorise new connections
  WiFi.mode(WIFI_OFF);    //otherwise the module will not reconnect
  delay(100);
  //Connessione alla rete WiFi con IP Statico
  WiFi.mode(WIFI_STA);
  
  //WiFi.config(IPAddress(192,168,1,220), IPAddress(192,168,1,1),IPAddress(255,255,255,0));
  Serial.println("mode is station only");
  Serial.print("Connecting to STA - WIFI router");
  WiFi.begin(ssid, password);

  delay(100);
  Serial.print("\nConnecting to "); Serial.println(ssid);
  uint8_t i = 0;
  const uint8_t i_max = 50;
  while (WiFi.status() != WL_CONNECTED && i++ < i_max){
	   delay(200);
    Serial.print(WiFi.status());
     Serial.print(".");
     Serial.print(i);
     Serial.print(".");
       }
  Serial.println("");
  if(WiFi.status() == WL_CONNECTED){
  Serial.print("IP address is:");
  //IPAddress myIP;
  myIP = WiFi.localIP();
  Serial.println(myIP);
   }

   Serial.print("i=");
   Serial.println(i);
  // Dopo 56 secondi se non si è connesso si ferma l'esecuzione 
  if(i>i_max){
    Serial.println("Could not connect to: "); Serial.println(ssid);
    Serial.println("ESP is activating the Access point...");
    WiFi.disconnect(true); //ferma il tentativo di connessione come STA
    delay(500);
    Wifi_AP_Connect();
  }
  }
  else {
  Serial.print("IP address is:");
  //IPAddress myIP;
  myIP = WiFi.localIP();
  Serial.println(myIP);
   }
   WiFi.printDiag(Serial);

   Serial.println(WiFi.getMode());
}
  
//----------------------------------------------------------------------- 
// Access Point configuration
//-----------------------------------------------------------------------  
 void Wifi_AP_Connect()
{ 
    WiFi.mode(WIFI_AP);      
    Serial.println("mode is Access Point only");

    Serial.println("Configuring access point...");
    // You can remove the password parameter if you want the AP to be open. /
    //WiFi.softAP(ssid, password);
    //WiFi.softAP("esp8266_ap", "");
    WiFi.softAP("esp8266_ap");
    //IPAddress myIP;
    myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
  }      

