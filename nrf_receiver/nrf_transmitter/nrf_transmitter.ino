// most important 
//==========================//
//always connect NRF24L01 module with 3.3V Not with 5v
//and use a 10uF capasitor between NRF24L01 module's Vcc and ground



//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";
int count = 0;

const int xPin = A5; // X-axis
const int yPin = A4; // Y-axis
const int buttonPin = 7; // Button

void setup()
{
  Serial.begin(9600);
  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_LOW);
  
  //Set module as transmitter
  radio.stopListening();
  pinMode(buttonPin, INPUT_PULLUP); // Enable internal pull-up resistor for the button
}
void loop()
{
 // int xValue = analogRead(xPin); // Read X-axis
  int yValue = analogRead(yPin); // Read Y-axis
  //int buttonState = digitalRead(buttonPin); // Read button state

  // Print values to Serial Monitor
  // Serial.print("X: ");
  // Serial.print(xValue);
  // Serial.print(" | Y: ");
  // Serial.print(yValue);
  // Serial.print(" | Button: ");
  // Serial.println(buttonState == LOW ? "Pressed" : "Released");

  //Send message to receiver
  //const char text[] = "Hello World ";
  int y = map(yValue, 0, 1023, 0, 180);
  bool res =  radio.write(&y, sizeof(y));
  Serial.println(res);
  
  //delay(100); // Small delay to make output readable

}