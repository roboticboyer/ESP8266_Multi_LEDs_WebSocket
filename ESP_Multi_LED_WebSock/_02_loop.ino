/*
 * ESP8266 Web server with Web Socket to control an LED.
 *
*/ 

//-----------------------------------------------------------------------
void loop()
{
  webSocket.loop();
  server.handleClient();
}
