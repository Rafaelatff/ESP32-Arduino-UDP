# ESP32-Arduino-UDP
Repositorie created to aid my ESP32 with Arduino studies. This repositorie shall perform similar results as the one created during idf.py studies [Socket, UDP and broadcast messages](https://github.com/Rafaelatff/ESP32-STA-UDP-Socket).

## Sending UDP Messages

It is easy to send UDP messages. After the WiFi connection is made to an AP, just call the `udp.broadcast` function.

```cpp
void setup(){

  // WiFi Configuration (STA mode, connection to an AP)
  // Check: https://github.com/Rafaelatff/ESP32-Arduino-Network-scan

  // Connect to PORT 2000
  if(udp.listen(2000)) {
    Serial.print("UDP Listening on IP: ");
    Serial.print(WiFi.localIP());
    Serial.println(" and Port 2000.");
    /*
  }
}

void loop(){
  // put your main code here, to run repeatedly:

  //Send broadcast
  udp.broadcast("Messagem from Green ESP32");
  delay(1000);
}
```

Using the UDP Sender / Receiver app (Android), we can check the UDP broadcaps messages send from the ESP32:

<img src="https://github.com/Rafaelatff/ESP32-Arduino-UDP/assets/58916022/0abd6dfa-2613-4824-b55f-ca7d6394d061" alt="Descrição da imagem" width="358" height="800">

## Receiving UDP Messages

Inside then `setup(){` -> `if(udp.listen(2000)){`, we call the `udp.onPacket(){`. 
This function is used to register a "callback" that will be called when a UDP packet is received.

PAREI AQUI

```cpp

```


## Bibliography

* [UDP Texting](https://community.appinventor.mit.edu/t/esp32-with-udp-send-receive-text-chat-mobile-mobile-udp-testing-extension-udp-by-ullis-ulrich-bien/72664/2).
