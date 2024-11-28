#include <SPI.h>
#include <SD.h>
#include <string.h>
#include <Keyboard.h>
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <IRremote.hpp>
#ifdef __AVR__
#include <avr/power.h> 
#endif
#define LED_PIN     11
#define LED_COUNT  1
#define BRIGHTNESS 50
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);


#define irReceiverPin 7


File myFile;
String DEFAULT_FILE_NAME = "dstike.txt";


void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
strip.begin(); 
strip.show(); 
strip.setBrightness(BRIGHTNESS);
  
  pinMode(6, INPUT_PULLUP);
  IrReceiver.begin(irReceiverPin, ENABLE_LED_FEEDBACK); 
 

 
      if (!SD.begin(4)) {
    
     colorWipe(strip.Color(255,   0,   0)     , 50);
     return;
     }else{
       colorWipe(strip.Color(  0, 255,   0)     , 50); 
     }
     

}

void readSD(String txtName){
    myFile = SD.open(txtName);
    if (myFile) {
    Keyboard.begin();
    
    String line = "";
    while (myFile.available()) {
      char m = myFile.read();
      if (m == '\n'){
        Line(line);
        line = "";
        }
        else if((int) m != 13)
        {
          line += m;
        }
    }
    Line(line);
    
    myFile.close();
  } else {
  }
  Keyboard.end();
  
}
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
void Line(String l)
{
  int space_1 = l.indexOf(" ");
  if (space_1 == -1)
  {
    Press(l);
  }
  else if (l.substring(0,space_1) == "STRING")
  {
    Keyboard.print(l.substring(space_1 + 1));
  }
  else if (l.substring(0,space_1) == "DELAY")
  {
    int delaytime = l.substring(space_1 + 1).toInt();
    delay(delaytime);
  }
  else if(l.substring(0,space_1) == "REM"){}
  else
  {
      String remain = l;

      while(remain.length() > 0)
      {
        int latest_space = remain.indexOf(" ");
        if (latest_space == -1)
        {
          Press(remain);
          remain = "";
        }
        else
        {
          Press(remain.substring(0, latest_space));
          remain = remain.substring(latest_space + 1);
        }
        delay(5);
      }
  }

  Keyboard.releaseAll();
}
void Press(String b)
{
  if(b.length() == 1)
  {
    char c = b[0];
    Keyboard.press(c);
  }
  else if (b.equals("ENTER"))
  {
    Keyboard.press(KEY_RETURN);
  }
  else if (b.equals("CTRL"))
  {
    Keyboard.press(KEY_LEFT_CTRL);
  }
    else if (b.equals("SHIFT"))
  {
    Keyboard.press(KEY_LEFT_SHIFT);
  }
    else if (b.equals("ALT"))
  {
    Keyboard.press(KEY_LEFT_ALT);
  }
    else if (b.equals("GUI"))
  {
    Keyboard.press(KEY_LEFT_GUI);
  }
    else if (b.equals("UP") || b.equals("UPARROW"))
  {
    Keyboard.press(KEY_UP_ARROW);
  }
    else if (b.equals("DOWN") || b.equals("DOWNARROW"))
  {
    Keyboard.press(KEY_DOWN_ARROW);
  }
    else if (b.equals("LEFT") || b.equals("LEFTARROW"))
  {
    Keyboard.press(KEY_LEFT_ARROW);
  }
    else if (b.equals("RIGHT") || b.equals("RIGHTARROW"))
  {
    Keyboard.press(KEY_RIGHT_ARROW);
  }
    else if (b.equals("DELETE"))
  {
    Keyboard.press(KEY_DELETE);
  }
    else if (b.equals("PAGEUP"))
  {
    Keyboard.press(KEY_PAGE_UP);
  }
    else if (b.equals("PAGEDOWN"))
  {
    Keyboard.press(KEY_PAGE_DOWN);
  }
    else if (b.equals("HOME"))
  {
    Keyboard.press(KEY_HOME);
  }
    else if (b.equals("ESC"))
  {
    Keyboard.press(KEY_ESC);
  }
    else if (b.equals("INSERT"))


    
  {
    Keyboard.press(KEY_INSERT);
  }
    else if (b.equals("TAB"))
  {
    Keyboard.press(KEY_TAB);
  }
    else if (b.equals("END"))
  {
    Keyboard.press(KEY_END);
  }
    else if (b.equals("CAPSLOCK"))
  {
    Keyboard.press(KEY_CAPS_LOCK);
  }
    else if (b.equals("F1"))
  {
    Keyboard.press(KEY_F1);
  }
    else if (b.equals("F2"))
  {
    Keyboard.press(KEY_F2);
  }
    else if (b.equals("F3"))
  {
    Keyboard.press(KEY_F3);
  }
    else if (b.equals("F4"))
  {
    Keyboard.press(KEY_F4);
  }
    else if (b.equals("F5"))
  {
    Keyboard.press(KEY_F5);
  }
    else if (b.equals("F6"))
  {
    Keyboard.press(KEY_F6);
  }
    else if (b.equals("F7"))
  {
    Keyboard.press(KEY_F7);
  }
    else if (b.equals("F8"))
  {
    Keyboard.press(KEY_F8);
  }
    else if (b.equals("F9"))
  {
    Keyboard.press(KEY_F9);
  }
    else if (b.equals("F10"))
  {
    Keyboard.press(KEY_F10);
  }

  
    else if (b.equals("F11"))
  {
    Keyboard.press(KEY_F11);
  }
    else if (b.equals("F12"))
  {
    Keyboard.press(KEY_F12);
  }
}


void loop() {
 
  if (IrReceiver.decode()) {   

 // Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
 // IrReceiver.printIRResultShort(&Serial);
 // IrReceiver.printIRSendUsage(&Serial);
  
  if (IrReceiver.decodedIRData.decodedRawData==0xBA45FF00){
    
DEFAULT_FILE_NAME = "CHMINUS.txt";  }else if (IrReceiver.decodedIRData.decodedRawData==0xB946FF00){
DEFAULT_FILE_NAME = "CH.txt"; }else if (IrReceiver.decodedIRData.decodedRawData==0xB847FF00){  
DEFAULT_FILE_NAME = "CHPLUS.txt"; }else if (IrReceiver.decodedIRData.decodedRawData==0xBB44FF00){ 
DEFAULT_FILE_NAME = "PREV.txt"; }else if (IrReceiver.decodedIRData.decodedRawData==0xBF40FF00){ 
DEFAULT_FILE_NAME = "NEXT.txt"; }else if (IrReceiver.decodedIRData.decodedRawData==0xBC43FF00){ 
DEFAULT_FILE_NAME = "PLAY.txt"; }else if (IrReceiver.decodedIRData.decodedRawData==0xF807FF00){ 
DEFAULT_FILE_NAME = "VOLMINUS.txt"; }else if (IrReceiver.decodedIRData.decodedRawData==0xEA15FF00){ 
DEFAULT_FILE_NAME = "VOLPLUS.txt";}else if (IrReceiver.decodedIRData.decodedRawData==0xF609FF00){ 
DEFAULT_FILE_NAME = "EQ.txt"; }else if (IrReceiver.decodedIRData.decodedRawData==0xE916FF00){ 
DEFAULT_FILE_NAME = "0.txt"; }else if (IrReceiver.decodedIRData.decodedRawData==0xE619FF00){ 
DEFAULT_FILE_NAME = "100.txt"; }else if (IrReceiver.decodedIRData.decodedRawData==0xF20DFF00){ 
DEFAULT_FILE_NAME = "200.txt"; }else if (IrReceiver.decodedIRData.decodedRawData==0xF30CFF00){ 
DEFAULT_FILE_NAME = "1.txt"; }else if (IrReceiver.decodedIRData.decodedRawData==0xE718FF00){ 
DEFAULT_FILE_NAME = "2.txt"; }else if (IrReceiver.decodedIRData.decodedRawData==0xA15EFF00){ 
DEFAULT_FILE_NAME = "3.txt"; }else if (IrReceiver.decodedIRData.decodedRawData==0xF708FF00){ 
DEFAULT_FILE_NAME = "4.txt"; }else if (IrReceiver.decodedIRData.decodedRawData==0xE31CFF00){ 
DEFAULT_FILE_NAME = "5.txt"; }else if (IrReceiver.decodedIRData.decodedRawData==0xA55AFF00){ 
DEFAULT_FILE_NAME = "6.txt"; }else if (IrReceiver.decodedIRData.decodedRawData==0xBD42FF00){ 
DEFAULT_FILE_NAME = "7.txt"; }else if (IrReceiver.decodedIRData.decodedRawData==0xAD52FF00){ 
DEFAULT_FILE_NAME = "8.txt"; }else if (IrReceiver.decodedIRData.decodedRawData==0xB54AFF00){   
DEFAULT_FILE_NAME = "9.txt"; } 
}    

  IrReceiver.resume(); 
   delay(600);
   readSD(DEFAULT_FILE_NAME);
   DEFAULT_FILE_NAME = "dstike.txt";
   

}
