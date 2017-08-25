/*
 * ESP8266 Web server with Web Socket to control an LED.
 *
*/

//-----------------------------------------------------------------------
static void writeLED(int pin)
{
  // Note inverted logic for ESP-01 board
  if (LED1_status) {
    digitalWrite(LEDPIN[pin], 1);
  }
  else {
    digitalWrite(LEDPIN[pin], 0);
  }

}
