/*
 * ESP8266 Web server with Web Socket to control an LED.
*/


//-----------------------------------------------------------------------
const char INDEX_HTML[] = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <title>ESP LEDs Websocket Example</title>
    <script>
var LED1_stato=0;
function start() {
	
	//Avvia Websocket
  websock = new WebSocket('ws://' + window.location.hostname + ':81/');
  
  //Callbacks di Websocket 
  websock.onopen = function(evt) {
    console.log('websock open');};
  
  websock.onclose = function(evt) { console.log('websock close'); };
  
  websock.onerror = function(evt) { console.log(evt); };
  
  websock.onmessage = function(evt) {
	//Riceve stato LEDs da ESP
    console.log('websocket message from ESP: ',evt.data);
	var payload = evt.data;
	//Processa JSON
	if (payload != null) {
 
		//LED1
		if (payload === "11"){
			document.getElementById("led_1").innerHTML = "led1 accesso";
			LED1_stato = 1;}
		else if(payload === "10"){
			document.getElementById("led_1").innerHTML = "led1 spento";
			LED1_stato = 0;}
      
    //LED2
    else if (payload === "21"){
      document.getElementById("led_2").innerHTML = "led2 accesso";
      LED2_stato = 1;}  
    else if(payload === "20"){
      document.getElementById("led_2").innerHTML = "led2 spento";
      LED2_stato = 0;}
      
    //LED3
         else if (payload === "31"){
      document.getElementById("led_3").innerHTML = "led3 accesso";
      LED3_stato = 1;}  
    else if(payload === "30"){
      document.getElementById("led_3").innerHTML = "led3 spento";
      LED3_stato = 0;}
      
    //LED4
    else if (payload === "41"){
      document.getElementById("led_4").innerHTML = "led4 accesso";
      LED4_stato = 1;}  
    else if(payload === "40"){
      document.getElementById("led_4").innerHTML = "led4 spento";
      LED4_stato = 0;}

      
		else { //nessun comando valido
			console.log('unknown event', evt.data);}    
	};
  }
} //end start


//---------------------------
//Gestione Bottoni
//---------------------------
function LED_1(){
	if (LED1_stato === 0) {
		LED1_stato = 1;
		payload = "11";}
	else { 
		LED1_stato = 0;
		payload = "10";}
      websock.send(payload); //invia id del bottone premuto
  console.log('websocket message from botton: ',payload);
  }

function LED_2(){
  if (LED2_stato === 0) {
    LED2_stato = 1;
    payload = "21";}
  else { 
    LED2_stato = 0;
    payload = "20";}
      websock.send(payload); //invia id del bottone premuto
  console.log('websocket message from botton: ',payload);
  }

function LED_3(){
  if (LED3_stato === 0) {
    LED3_stato = 1;
    payload = "31";}
  else { 
    LED3_stato = 0;
    payload = "30";}
      websock.send(payload); //invia id del bottone premuto
  console.log('websocket message from botton: ',payload);
  }

function LED_4(){
  if (LED4_stato === 0) {
    LED4_stato = 1;
    payload = "41";}
  else { 
    LED4_stato = 0;
    payload = "40";}


	websock.send(payload); //invia id del bottone premuto
	console.log('websocket message from botton: ',payload);
	}
 </script>
    <style>
      .Ing_box {
        background-color:yellow;
        float: left;
        margin: 10px 0px 10px 20px;
        border: 10px solid red;
        padding: 6px 2px 6px 10px;
        width: 130px;
        color: blue;
      }
      p.form,button {  /* */  
        border-radius: 50px;    
        font-size: 100%;
				height: 70px;
        width: 200px;
        margin: 4px 0px 5px 0px;
        padding: 1px 0px 5px 0px;
     		background-color:cyan;
        color: blue;
      }
    </style>
  </head>
  <body onload="start()">
    <br>
    <h2>SLIP, Gruppo Arduino</h2>
    <table border='1px'>
      <tr style="background-color:sienna">
        <td>  
          <div class="Ing_box">
            Prove con un LED
          </div>  
        </td>
      </tr>
      <tr style="background-color:peru">  
        <td><div>
            <button type="button" id="led_1" onclick="LED_1();">led1 spento</button>
          </div></td>
        <td><div>
            <button type="button" id="led_2" onclick="LED_2();">led2 spento</button>
        </div></td>
        <td><div>
            <button type="button" id="led_3" onclick="LED_3();">led3 spento</button>
        </div></td>
        <td><div>
            <button type="button" id="led_4" onclick="LED_4();">led4 spento</button>
        </div></td>
    </tr>      
  </body>
</html>
)rawliteral";
