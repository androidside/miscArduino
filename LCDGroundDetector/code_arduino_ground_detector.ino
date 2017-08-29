
//https://www.amazon.com/DFRobot-DFR0009-LCD-Shield-Arduino/dp/B006D903KE/ref=sr_1_7?ie=UTF8&qid=1501181609&sr=8-7&keywords=lcd+shield
#include <LiquidCrystal.h>

const int buzzer = 13; //buzzer to arduino pin 13

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);          


int lcd_key     = 0;
int adc_key_in  = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int val = 0;           // variable to store the value read
int val2 = 0;   
float voltage = 0;
float voltage2 = 0;
float r_probe = 840; 
float r_given = 773;
float v_drop_r2;
float v_drop_r1;

void setup(){
   Serial.begin(9600);
   lcd.begin(16, 2);               // start the library
   lcd.setCursor(0,0);             // set the LCD cursor   position 
   lcd.print("Resistance");  // print a simple message on the LCD
   pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
   
}
 
void loop(){
   delay(400);
   val = analogRead(A1);    // read the input pin
   voltage = val * (5.0 / 1023.0);
   val2 = analogRead(A5);    // read the input pin
   voltage2 = val2 * (5.0 / 1023.0);
//   Serial.println(voltage);             // debug value
   r_probe = (5*r_given/(5-voltage))-r_given;
   v_drop_r2 = r_probe*5/(r_given+r_probe);
   v_drop_r1 = r_given*5/(r_given+r_probe);
   if (r_probe < 0.1)
   {
    tone(buzzer, 4000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec
   }
   
   Serial.println(voltage);             // debug value
   lcd.setCursor(11,0); 
   lcd.print(r_probe);       // display seconds elapsed since power-up
   lcd.setCursor(9,1);             // move cursor to second line "1" and 9 spaces over
   lcd.print(voltage2);       // display seconds elapsed since power-up
   lcd.setCursor(0,1);             // move to the begining of the second line
   lcd.print("Voltage ");

}
