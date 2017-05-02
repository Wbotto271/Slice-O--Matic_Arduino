
#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3,POSITIVE);

long diameter = 0;
long slices = 0;
long Length = 0;
long Width = 0;
long areacut = 0;
long SlicesSic = 0;
double total = 0;
double cir = 0;
double area = 0;
double aslice = 0;
double angle = 0;
double arc = 0;
double R = 0;
double acut = 0;
//double sector = 0;


char customKey;
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9,8,7,6}; //Rows 0 to 3
byte colPins[COLS]= {5,4,3,2}; //Columns 0 to 3

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); 

void setup()
{
    lcd.begin(20,4);
    lcd.backlight();
    for(int i = 0; i< 40; i++)
  {  
    lcd.setCursor(3,1);
    lcd.print("Slice O' Matic");
    lcd.setCursor(2,2);
    lcd.print("Handheld Edition");
    lcd.setCursor(3,3);
    lcd.print("By: Will Botto");
    lcd.setCursor(0,3);
    delayMicroseconds(50000);
  }


  delayMicroseconds(50000);
}

void loop()
{

  start();

}

void start()
{
  lcd.clear();
  while( 1 )
  {
    
  diameter = 0;
  slices = 0;
  Length = 0;
  Width = 0;
  areacut = 0;
  SlicesSic = 0;
  
  //customKey = customKeypad.getKey();
  lcd.setCursor(3,0);
  lcd.print("Slice O' Matic");
  lcd.setCursor(1,1);
  lcd.print("Select your Pizza:");
  lcd.setCursor(4,2);
  lcd.print("Standard (A)");
  lcd.setCursor(4,3);
  lcd.print("Sicilian (B)");
  //lcd.setCursor(0,3);
  //lcd.print("Selection: ");
  customKey = customKeypad.getKey();
  //delayMicroseconds(200);
  
  if (customKey == 'A')
    {
      Standard();
      customKey = '0';
    }
  if(customKey == 'B')
    {
      Sicilian();
      customKey = '0';
    }
  if(customKey == '*')
  {
      lcd.clear();
      Easter();
      customKey = '0';
  }
      
  }
}

void Easter()
{
  
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Easter Egg Found!");
  lcd.setCursor(0,1);
  lcd.print("Thank you Frank,");
  lcd.setCursor(0,2);
  lcd.print("for making ");
  lcd.setCursor(0,3);
  lcd.print("'D' to cont.");
  while( 1 )
    {
      customKey = customKeypad.getKey();
      if(customKey >= '0' && customKey <= '9')
      {
        diameter = diameter * 10 + (customKey - '0');
      
     }

    
    if(customKey == 'D') 
    {
    lcd.setCursor(0,1);
    lcd.print("programming fun");
    lcd.setCursor(0,2);
    lcd.print("again.    ");
    lcd.setCursor(0,3);
    lcd.print("'C' to exit.");
    }
    if(customKey == 'C')  
    {  
      lcd.clear();
      restart();

    }
    }
}
     



void Standard()
{
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Standard Pizza");
    lcd.setCursor(0,1);
    lcd.print("Size: ");

    lcd.setCursor(0,3);
    lcd.print("'D' to cont.");
    while( 1 )
    {
      customKey = customKeypad.getKey();
      if(customKey >= '0' && customKey <= '9')
      {
        diameter = diameter * 10 + (customKey - '0');
        lcd.setCursor(6,1);
        lcd.print(diameter);
      
     }

      if(customKey == 'D') 
      {
      lcd.setCursor(0,2);
      lcd.print("Slices: ");
      slices = SliceNumber();
      break;
      }
    }
     
    diameter = 0, slices = 0, R = 0, area = 0, angle = 0, cir = 0, arc = 0; // reset values back to zero for next use

}

void Sicilian()
{
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sicilian Pizza");
    lcd.setCursor(0,1);
    lcd.print("Slices: ");

    lcd.setCursor(0,3);
    lcd.print("'D' to cont.");
    while( 1 )
    {
      customKey = customKeypad.getKey();
      if(customKey >= '0' && customKey <= '9')
      {
        SlicesSic = SlicesSic * 10 + (customKey - '0');
       lcd.setCursor(8,1);
        lcd.print(SlicesSic);
      
     }

      if(customKey == 'D') 
      {
      lcd.setCursor(0,1);
      lcd.print("Length:             ");
      Length = LengthNumber();
      break; 
      }
    }
     
    Length = 0, Width = 0, SlicesSic = 0; // reset values back to zero for next use
   
}

long SliceNumber()
{
  while( 1 )
  {
    
    customKey = customKeypad.getKey();
    if(customKey >= '0' && customKey <= '9')
    {
      slices = slices * 10 + (customKey - '0');
      lcd.setCursor(8,2);
      lcd.print(slices);
    }

    if(customKey == 'D') 
    {
        lcd.clear();
        R = diameter/2; //converts the pizza size (Diameter) to the radius of the circle
        cir = round((2*3.14159*R)); //calculates the circumference of the users pizza
        angle = 360/slices; //determines the internal angle of the sector, the sector is the slice of pizza
        area = round((3.14159*pow(R,2))); //calculates the area of the circle
        arc = round(cir*(angle/360)); //calculates the arc length of the pizza
        
        
        delayMicroseconds(50);
        
        
        lcd.setCursor(0,0);
        lcd.print("Cir: ");
        lcd.setCursor(5,0);
        lcd.print(cir);
        lcd.setCursor(0,1);
        lcd.print("Area: ");
        lcd.setCursor(6,1);
        lcd.print(area);
        lcd.setCursor(0,2);
        lcd.print("Arc: ");
        lcd.setCursor(5,2);
        lcd.print(arc);
        lcd.setCursor(0,3);
        lcd.print("'C' to restart");
    }
    if(customKey == 'C')  
    {  
    restart();
    break;
    }
  }
 return slices;
}

long LengthNumber()
{
  while( 1 )
  {
    customKey = customKeypad.getKey();
    if(customKey >= '0' && customKey <= '9')
    {
      Length = Length * 10 + (customKey - '0');
      lcd.setCursor(8,1);
      lcd.print(Length);
      //Length = LengthNumber();
    }

    if(customKey == 'D') 
    {
      lcd.setCursor(0,2);
      lcd.print("Width: ");
      //lcd.clear();
      Width = WidthNumber();
    }
  }
 return Length;
}

long WidthNumber()
{
  //lcd.setCursor(0,2);
  //lcd.print("Width: ");
  while( 1 )
  {

    customKey = customKeypad.getKey();
    if(customKey >= '0' && customKey <= '9')
    {
      Width = Width * 10 + (customKey - '0');
      lcd.setCursor(7,2);
      lcd.print(Width);
    }

    if(customKey == 'D') 
    {
      area = round((Length*Width)); //calculates the area of the rectangle
      areacut = round((area/SlicesSic));
      
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Area: ");
      lcd.setCursor(6,1);
      lcd.print(area);
      lcd.setCursor(0,2);
      lcd.print("Slice Area: ");
      lcd.setCursor(12,2);
      lcd.print(areacut);
      lcd.setCursor(0,3);
      lcd.print("'C' to restart");
    }
    if(customKey == 'C')  
    {  
      lcd.clear();
      restart();
    break;
    }
  }
 return Width;
}

void restart()
{
   loop();

   
}




