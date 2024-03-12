# ESP32-Arduino-UDP
Repositorie created to aid my ESP32 with Arduino studies. This repositorie shall perform similar results as the one created during idf.py studies [Socket, UDP and broadcast messages](https://github.com/Rafaelatff/ESP32-STA-UDP-Socket).

## Sending UDP Messages

It is easy to send UDP messages. First I include the library `#include "AsyncUDP.h"`. This is a fully asynchronous UDP library. After the WiFi connection is made to an AP ([check here how to do it](https://github.com/Rafaelatff/ESP32-Arduino-Network-scan)), during `setup()` I connect to port 2000 (`udp.listen(2000)`). Then, In the `loop()` I call the `udp.broadcast` function everytime I want to send a broadcast message.

```cpp
void setup(){

  // WiFi Configuration (STA mode, connection to an AP)
  // Check: https://github.com/Rafaelatff/ESP32-Arduino-Network-scan

  // Connect to PORT 2000
  if(udp.listen(2000)) {
    Serial.print("UDP Listening on IP: ");
    Serial.print(WiFi.localIP());
    Serial.println(" and Port 2000.");
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

<img src="https://github.com/Rafaelatff/ESP32-Arduino-UDP/assets/58916022/0abd6dfa-2613-4824-b55f-ca7d6394d061" alt="app image" width="358" height="800">

## Receiving UDP Messages

#### Small Recap on Lambda Functions

From the Udemy course [Qt 5 C++ GUI Development For Beginners : The Fundamentals](https://www.udemy.com/course/qt-c-gui-tutorial-for-complete-beginners/), Lesson 20. C++ Lambda Basics: 

Lambdas are a construct in C++ that allows you to define functions inline. You define them "in place" and you can use them right away. **You can capture variable in the context**, being able of using it withou passing in as parameters. You have as definition:

* The sintax: `[capture list] (parameter list) {function body};`.
* Call the Lambda function directly after definition: `[]() { /* function body */ }();`. This last () makes the call.
* Giving a name to the Lambda function:  `auto func = []() { /* function body */ };`. It doen't call the Lambda function.
* Calling the Lambda function: `func();`;
* Define a Lambda function that takes parameters:  `[](int a, int b) { /* function body */ }(7, 3);`, where `int a, int b` are parameters. `7, 3` are the numbers passed to the Lambda function.
* Define and call a Lambda function that can return value: `[](int a, int b)->int{ return a + b }(7, 3);`, where `->int` defines the type that the Lambda return.
* To assign a variable to capture the return value: `int sum = [](int a, int b)->int{ return a + b }(7, 3);`.
* Capture lists allows to capture the variables that are in the current context, but not declared iniside the Lambda or passed to the Lambda. Example:
```cpp
int a = 7;
int b = 3;
[a, b](){
  count << "a is: " << a << endl;
}();
```
* Capture by value:
```cpp
int c = 42;
auto func = [c](){
  count << "The inner value of c is: " << c << endl;
}; // not calling it
for (int i=1; i <5; i++){
  count << "The outer value of c is: " << c << endl;
  func(); // calling the Lambda function
  c++;
}
```
This returned: 

![image](https://github.com/Rafaelatff/ESP32-Arduino-UDP/assets/58916022/75762bbd-2445-4565-a214-56e7bc7193f5)

* Capturing by reference (pass the address, the pointer, to work in the original value): 
```cpp
int c = 42;
auto func = [&c](){ // address
  count << "The inner value of c is: " << c << endl;
}; // not calling it
for (int i=1; i <5; i++){
  count << "The outer value of c is: " << c << endl;
  func(); // calling the Lambda function
  c++;
}
```
This returned:

![image](https://github.com/Rafaelatff/ESP32-Arduino-UDP/assets/58916022/cf42c93c-b947-457f-8c20-dd3c114cad5d)

* Capturing everything by valuein the context (I can have `a`, `b`, `c`, `d`, `e`, `f`, ...). In this case, inner value always returns 42:

```cpp
int c = 42;
auto func = [=](){ // address
  count << "The inner value of c is: " << c << endl;
}; // not calling it
// same as previous example ...
```

* Capturing by reference (I can have `a`, `b`, `c`, `d`, `e`, `f`, ...). In this case, inner value always returns the same as outer value:

```cpp
int c = 42;
auto func = [&](){ // address
  count << "The inner value of c is: " << c << endl;
}; // not calling it
// same as previous example ...
```

### Now let's return to the ESP code -  Receiving UDP Messages

First I declare the class type `AsyncUDP udp;`. 



Inside then `setup(){` -> `if(udp.listen(2000)){`, we call the `udp.onPacket(){`. 
This function is used to register a "callback" that will be called when a UDP packet is received.

PAREI AQUI

```cpp

```


## Bibliography

* [UDP Texting](https://community.appinventor.mit.edu/t/esp32-with-udp-send-receive-text-chat-mobile-mobile-udp-testing-extension-udp-by-ullis-ulrich-bien/72664/2).
