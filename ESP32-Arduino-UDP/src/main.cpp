#include <Arduino.h>
#include <WiFi.h>
#include <AsyncUDP.h> 

// put function declarations here:
// IO
const byte blueLED = 2;  // GPIO2

//WiFI
const char* ssid = "Skynet";
const char* senha = "xxxx";

//UDO
AsyncUDP udp;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(blueLED,OUTPUT);

  WiFi.mode(WIFI_STA); // Station mode
  Serial.print("\r\n"); // new line, new carriage return
  Serial.print("Connecting to the network ");
  Serial.print(ssid);
  WiFi.begin(ssid, senha);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
  }
  Serial.println(" ");
  Serial.println("WiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  if(udp.listen(2000)) {
    Serial.print("UDP Listening on IP: ");
    Serial.print(WiFi.localIP());
    Serial.println(" and Port 2000.");
    
    udp.onPacket([](AsyncUDPPacket packet){
      
      // malloc() -> memory allocation -> function that allows C to **allocate memory** dynamically from the heap
      char* tmpStr = (char*) malloc(packet.length() + 1); // pointer named "temporary string", receives the address (typecasted to char), with size of packet.length +1 
      // memcpy (destination, source, size)
      memcpy(tmpStr, packet.data(), packet.length()); 
      tmpStr[packet.length()] = '\0'; // ensure null termination        
      
      // String  menssage = (char*)(packet.data());      
      String message = String(tmpStr);
      free(tmpStr); // Free our memory
      Serial.println(message); // Print our message
      if(message == "on"){
        digitalWrite(blueLED, HIGH); // Turn on blueLED
        packet.print("Received: on");
      }
      if(message == "off"){
        digitalWrite(blueLED, LOW); // Turn off blueLED
        packet.print("Received: off");
      }
      if(message == "consulta"){
        if(digitalRead(blueLED == HIGH)){packet.print("Now blueLED is HIGH");} // not working now
        if(digitalRead(blueLED == LOW)) {packet.print("Now blueLED is LOW");}
      }

      // Reply to the client
      Serial.print("Got ");
      Serial.print(packet.length());
      Serial.println(" bytes of data");
    });
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  //Send broadcast
  udp.broadcast("Message from Green ESP32");
  delay(1000);

    if (WiFi.status() == WL_CONNECTED) {
    // Obtenha o RSSI da conexão WiFi
    int rssi = WiFi.RSSI();
    Serial.print("RSSI: ");
    Serial.println(rssi);

    // Envie uma mensagem UDP para o servidor
    //udp.beginPacket(serverIP, serverPort);
    //udp.printf("RSSI: %d", rssi);
    //udp.endPacket();

  } else {
    Serial.println("WiFi connection lost");
    // Reconnect or handle accordingly
  }
}
