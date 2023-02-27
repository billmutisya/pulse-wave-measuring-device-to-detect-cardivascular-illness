#include <LiquidCrystal.h>

LiquidCrystal lcd(9,8,5,4,3,2);
char message[20];

int value, lowminus,lowplus;
int threshold(500);
int count(0);
int flag(0);
unsigned long currenttime;

void setup() {
Serial.begin(9600);
pinMode( 10, INPUT);
pinMode(11, INPUT);

}

void loop() {
value= analogRead (A0);
lowminus = digitalRead(10);
lowplus = digitalRead(11);
if (lowminus ==1 || lowplus ==1)
{
  Serial.println("!");
}
 else
{
if( value > 500 )
{
flag = 1;
}
  else { if( flag == 1 ) 
  { 
    count = count + 1; 
    flag = 0; 
    //Serial.println( count ); 
    
  }
}
if( millis() - currenttime > 10000 ) 
{ 
  currenttime = millis(); 
  float bpm= count*6.0;
  Serial.println(bpm); 
  count = 0; 
  
   //PWV
   delay( 20 );
    // //velocity is frequency*wavelength
    //Wavelength is 660nm oxygenated and 940 deoxygenated blood. Av is 800nm
    
{
    //convert BPM to freq then multiply it by wavelength
    float count;
   // Serial.print("BPM:");
    // Serial.print (count*6);
   // Serial.println("," );
    //convert BPM to freq then multiply it by wavelength
    float PWV;
   float ECGwavelength = 6.50;
    Serial.print("PWV(nm/s):");
    //V=f*W
    PWV = (((bpm * 2.0) / 120.0) * (ECGwavelength ));
    Serial.print( PWV );
    //wavelength*0000001 or 1e-7
    //Pwv **0000001 
    Serial.println("," );
    //transit time if we know distance is 0.9 and PW(velocity) we can get time
    float timeB;
    float ECGdistance = 0.63;//average distance in m from heart to ankle
    Serial.print("dist =80cm ");
    Serial.print( "transittime(s):" );
    timeB = ECGdistance / PWV;
    Serial.print( timeB );
    Serial.println("," );
    //
}
  }
  
 //Serial.println( count*6);
}
delay( 20 );
 
}
