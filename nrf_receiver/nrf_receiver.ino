// most important 
//==========================//
//always connect NRF24L01 module with 3.3V Not with 5v
//and use a 10uF capasitor between NRF24L01 module's Vcc and ground

#include <Servo.h>

//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";
Servo myServo;
int data = 0;

void setup()
{
  while (!Serial);
    Serial.begin(9600);

  if (!radio.begin()) {
    Serial.println("NRF24L01 not responding!");
    while (1);
  }

  radio.setAutoAck(false);
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_LOW);

  Serial.println("NRF24L01 initialized successfully!");
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();
  myServo.attach(3);
  //myServo.write(0);
  //delay(15);
}

void loop()
{
  //Read the data if available in buffer
  if (radio.available())
  {
   //char text[32] = {0};

    
    radio.read(&data, sizeof(data));
    Serial.println(data);
    //radio.stopListening();
    myServo.write(data);
    //delay(15);
    radio.startListening();
  }

  
}