/*
 * ESP8266 Web server with Web Socket to control an LED.
 *
*/

//-----------------------------------------------------------------------
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
  static uint32_t lastMillis = 0;
  
  Serial.printf("webSocketEvent(%d, %d, ...)\r\n", num, type);
  switch(type) {
	  
	  
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\r\n", num);
      break;
      
      
    case WStype_CONNECTED:
	{
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\r\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        // Send the current LED status to the new connected client

		if (LED1_status==0){ webSocket.sendTXT(num,"10", 2);}
		if (LED1_status==1){ webSocket.sendTXT(num,"11", 2);}
		if (LED2_status==0){ webSocket.sendTXT(num,"20", 2);}
		if (LED2_status==1){ webSocket.sendTXT(num,"21", 2);}
		if (LED3_status==0){ webSocket.sendTXT(num,"30", 2);}
		if (LED3_status==1){ webSocket.sendTXT(num,"31", 2);}
		if (LED4_status==0){ webSocket.sendTXT(num,"40", 2);}
		if (LED4_status==1){ webSocket.sendTXT(num,"41", 2);}
	}
	break;
      
      
    case WStype_TEXT:
      // Processa il messaggio ricevuto da un client
      Serial.printf("[%u] [%u ms] get Text: %s\r", num, millis()-lastMillis, payload);
      lastMillis = millis();

//LED1
      if ((length == 2) && (memcmp("10", payload, 2) == 0)){
		LED1_status=0;
		writeLED(0);}
      else if ((length == 2) && (memcmp("11", payload, 2) == 0)) {
		LED1_status=1;
		writeLED(0);}
   
//LED2
      else if ((length == 2) && (memcmp("20", payload, 2) == 0)){
    LED2_status=0;
    //writeLED(1);
    }
      else if ((length == 2) && (memcmp("21", payload, 2) == 0)) {
    LED2_status=1;
    //writeLED(1);
    }
    
//LED3
      else if ((length == 2) && (memcmp("30", payload, 2) == 0)){
    LED3_status=0;
    //writeLED(2);
    }
      else if ((length == 2) && (memcmp("31", payload, 2) == 0)) {
    LED3_status=1;
    //writeLED(2);
    }
    
//LED4
      else if ((length == 2) && (memcmp("40", payload, 2) == 0)){
    LED4_status=0;
    //writeLED(3);
    }
      else if ((length == 2) && (memcmp("41", payload, 2) == 0)) {
    LED4_status=1;
    //writeLED(3);
    }
   
      else {
        Serial.println("Unknown command");
      }
      
      // send updated status to all connected clients => manda aggiornamento a tutti client connessi
      webSocket.broadcastTXT(payload, length);
      break;
      
      
    case WStype_BIN:
      Serial.printf("[%u] get binary length: %u\r\n", num, length);
      /*hexdump(payload, length);

      // echo data back to browser
      webSocket.sendBIN(num, payload, length);*/
      break;
      
      
    default:
      Serial.printf("Invalid WStype [%d]\r\n", type);
      break;
  }
}

