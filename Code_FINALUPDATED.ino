
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD   address to 0x27 for a 16 chars and 2 line display

Servo myservo;
int pos=0; // position of servo motor
const byte rows=4;
const byte cols=3;
 
char key[rows][cols]={
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};

byte rowPins[rows]={5,4,3,2};
byte colPins[cols]={6,7,8};

Keypad keypad= Keypad(makeKeymap(key),rowPins,colPins,rows,cols);
char* password="2345";
int currentposition=0;
 
int red = 13;
int green = 12; 

void setup()
{
 
displayscreen();
Serial.begin(9600);

  //START SENDING MSG OF DOOR UNLOCKING
  Serial.println("AT+CMGF=1"); // set SMS mode to text
  delay(200);
  Serial.println("AT+CNMI=2,2,0,0,0"); // set module to send SMS data to serial out upon receipt 
  delay(1000); 

  Serial.println("AT+CMGF=1");
  delay(500);
  String str1 = "AT+CMGS=\"+923375907978\"\r" ;  
  delay(500);
  Serial.println(str1);
  delay(500);
  Serial.println("DOOR UNLOCKED");
  delay(500);
  delay(1000);
  Serial.println((char)26);// ASCII code of CTRL+Z
  delay(500);
  //END MSG OF DOOR UNLOCKING
  
myservo.attach(10); //Servo motor connection
pinMode(red,OUTPUT);
pinMode(green,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(A0,INPUT_PULLUP);


lcd.begin(16,2);

lcd.setCursor(0,0);
lcd.print("Asslam-o-alikum ");
lcd.setCursor(0,1);
lcd.print("Welcome to FYP");
delay(200);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Made by Ahsan");
lcd.setCursor(0,1);
lcd.print("Usama & Abdullah");
delay(200);
lcd.clear();
}
 
void loop()
{
int s = analogRead(A0);
Serial.println(s);

if( currentposition==0)
{
displayscreen();
 
}
int l ;
char code=keypad.getKey();
if(code!=NO_KEY)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("PASSWORD:");
lcd.setCursor(7,1);
lcd.print(" ");
lcd.setCursor(7,1);
for(l=0;l<=currentposition;++l)
{
 
lcd.print("*");
//keypress();
}
 
if (code==password[currentposition] )
{
++currentposition;
if(currentposition==4)
{
 
unlockdoor();
currentposition=0;
 
}
 
}

 
else
{
incorrect();
currentposition=0;
 
}
}
}
 
//------------------ Function 1- OPEN THE DOOR--------------//
 
void unlockdoor()
{
delay(90);
 
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(1,0);
lcd.print("Access Granted");
lcd.setCursor(4,1);
lcd.println("WELCOME!!");
delay(100);
lcd.clear();
lcd.setCursor(0,0);
lcd.println("Sending Message");
lcd.setCursor(0,1);
lcd.println("03001234567");

for(pos = 180; pos>=0; pos-=5) // open the door
{
myservo.write(pos); 
delay(5); 
}
digitalWrite(green,HIGH);
delay(200);
digitalWrite(green,LOW);
delay(200);

 

delay(100);
counterbeep();
 
delay(100);//delay after door opening.
 
for(pos = 0; pos <= 180; pos +=5) // close the door
{ // in steps of 1 degree
myservo.write(pos); 
delay(5); 
}
delay(100);
lcd.clear();
lcd.setCursor(4,0);
lcd.print("LOCKED!");
digitalWrite(red,HIGH);
delay(500);
digitalWrite(red,LOW);
delay(500);
currentposition=0;
 
lcd.clear();
displayscreen();
}
 
//--------------------Function 2- Wrong code--------------//
 
void incorrect()
{

lcd.clear();
lcd.setCursor(1,0);
lcd.print("CODE");
lcd.setCursor(6,0);
lcd.print("INCORRECT");

digitalWrite(11,HIGH);

lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(4,1);
lcd.println("TRY AGAIN !!!");
delay(500);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Sending SMS To");
lcd.setCursor(0,1);
lcd.print("03001234567");
delay(500);

digitalWrite(11,LOW);
 
displayscreen();
}
//-------Function 3 - CLEAR THE SCREEN--------------------/
void clearscreen()
{
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(0,1);
lcd.println(" ");
lcd.setCursor(0,2);
lcd.println(" ");
lcd.setCursor(0,3);
lcd.println(" ");
}

//------------Function 4 - DISPLAY FUNCTION--------------------//
void displayscreen()
{
 
lcd.setCursor(0,0);
lcd.println("*ENTER THE CODE*");
lcd.setCursor(1 ,1);
 
lcd.println("TO OPEN DOOR..");
}


 
//--------------Function 5 - Count down------------------//
void counterbeep()
{
delay(1200);
 
 
lcd.clear();
 
lcd.setCursor(2,15);
lcd.println(" ");
lcd.setCursor(2,14);
lcd.println(" ");
lcd.setCursor(2,0);
delay(20);
lcd.println("GET IN WITHIN:::");
 

lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); 
lcd.print("3");
delay(10);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(10);

lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); 
lcd.print("2");
delay(10);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(10);

lcd.setCursor(4,1);
lcd.print("1");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN::");

delay(10);

lcd.clear();
lcd.setCursor(2,0);
lcd.print("RE-LOCKING");
delay(500);
lcd.setCursor(12,0);
lcd.print(".");
lcd.setCursor(14,0);
lcd.print(".");



}
