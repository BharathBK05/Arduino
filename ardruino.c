/*
   Switch Batteries based on the voltage
*/
#include <LiquidCrystal.h>
// the setup function runs once when you press reset or power the board

int relayOne = 11;
int relayTwo = 12;
float factor = 5.128;   //reduction factor of voltage sensor shield
float vCC = 5.00;       // Arduino input voltage
int maximumVoltage = 12;  //Maximum Voltage of the Battery
float vIn;
float vOut;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {  // initialize digital pin as an output.
   pinMode(relayOne, OUTPUT);
   pinMode(relayTwo, OUTPUT);
   Serial.begin(9600); //begin the serial monitor at 9600 baud
   lcd.begin(16,2);
   
}

// the loop function runs over and over again forever

void loop() {
   int dataOne = analogRead(A0);
   int dataTwo = analogRead(A1);

   int voltOne = voltageCalculate(dataOne);
   int voltTwo = voltageCalculate(dataTwo);

   // Print battery percentage in LCD
   //Battery 1
   lcd.setCursor(0,1);
   lcd.backlight();
   lcd.print("BATTERY_1 = ");
   lcd.print(voltOne);
   lcd.print("%");

   // Battery 2
   lcd.setCursor(0,2);
   lcd.backlight();
   lcd.print("BATTERY_2 = ");
   lcd.print(voltTwo);
   lcd.print("%");


   if (voltOne > 99)
   {
     digitalWrite(relayOne, HIGH);
     digitalWrite(relayTwo, HIGH);
     Serial.print("Active battery - 1")
     Serial.print("Charging battery - 2")

   }
   
   else if(voltTwo > 99)
   {
     digitalWrite(relayOne, LOW);
     digitalWrite(relayTwo, LOW);
     Serial.print("Active battery - 2")
     Serial.print("Charging battery - 1")
   }

   else if (voltTwo < 30) 
   {
     digitalWrite(relayOne, HIGH);
     digitalWrite(relayTwo, HIGH);
     Serial.print("Active battery - 1")
     Serial.print("Charging battery - 2")
   }

   else if(voltOne < 30)
   {
     digitalWrite(relayOne, LOW);
     digitalWrite(relayTwo, LOW);
     Serial.print("Active battery - 2")
     Serial.print("Charging battery - 1")
   }

   else
   {
    Serial.print('Continuing the same state....')
   }

   delay(3000);
   lcd.clear();

}

int voltageCalculate(int value)
{
    // calculate the voltage
    vOut = (value/1024) * vCC;
    vIn = vOut * factor;

    int VoltagePercent = floor((vIn / maximumVoltage) * 100);  //convert voltage to percentage
    return VoltagePercent;

}