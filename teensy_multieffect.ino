
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <ResponsiveAnalogRead.h>
//#include <Adafruit_GFX.h>      
//#include <Adafruit_SSD1306.h>
#include <Bounce.h>
#include <Encoder.h>



// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=194.75,508
AudioEffectBitcrusher    bitcrusher_r;   //xy=495.75,587
AudioEffectBitcrusher    bitcrusher_l;   //xy=500.75,449
AudioMixer4              bitcrusher_drywet_l; //xy=525.75,380
AudioMixer4              bitcrusher_drywet_r; //xy=546.75,527
AudioFilterBiquad        delay_lp_l;     //xy=730.75,223
AudioMixer4              delay_feedback_r; //xy=748.75,636
AudioFilterBiquad        delay_lp_r;     //xy=748.75,730
AudioMixer4              delay_feedback_l; //xy=765.75,333
AudioEffectDelay         delay_r;        //xy=899.75,675
AudioEffectDelay         delay_l;        //xy=919.75,231
AudioMixer4              delay_drywet_l; //xy=1017.75,416
AudioMixer4              delay_drywet_r; //xy=1024.75,564
AudioFilterBiquad        verb_lp_l;      //xy=1035.75,484
AudioFilterBiquad        verb_lp_r;      //xy=1087.75,679
AudioEffectFreeverb      freeverb_r;     //xy=1133.750015258789,875.0000095367432
AudioEffectFreeverb      freeverb_l;     //xy=1136.750015258789,819.0000076293945
AudioMixer4              rev_mix;         //xy=1193.750015258789,289.7500057220459
AudioEffectFreeverbStereo freeverb_st;     //xy=1321.7500190734863,261.75000381469727
AudioMixer4              reverb_drywet_l; //xy=1359.75,431
AudioMixer4              reverb_drywet_r; //xy=1366.75,581
AudioFilterLadder        filter_r;       //xy=1490.75,704
AudioFilterLadder        filter_l;       //xy=1521.75,292
AudioOutputI2S           i2s2;           //xy=1657.75,500
AudioConnection          patchCord1(i2s1, 0, bitcrusher_drywet_l, 0);
AudioConnection          patchCord2(i2s1, 0, bitcrusher_l, 0);
AudioConnection          patchCord3(i2s1, 1, bitcrusher_drywet_r, 0);
AudioConnection          patchCord4(i2s1, 1, bitcrusher_r, 0);
AudioConnection          patchCord5(bitcrusher_r, 0, bitcrusher_drywet_r, 1);
AudioConnection          patchCord6(bitcrusher_l, 0, bitcrusher_drywet_l, 1);
AudioConnection          patchCord7(bitcrusher_drywet_l, 0, delay_feedback_l, 0);
AudioConnection          patchCord8(bitcrusher_drywet_l, 0, delay_drywet_l, 0);
AudioConnection          patchCord9(bitcrusher_drywet_r, 0, delay_feedback_r, 0);
AudioConnection          patchCord10(bitcrusher_drywet_r, 0, delay_drywet_r, 0);
AudioConnection          patchCord11(delay_lp_l, 0, delay_feedback_l, 1);
AudioConnection          patchCord12(delay_feedback_r, delay_r);
AudioConnection          patchCord13(delay_lp_r, 0, delay_feedback_r, 1);
AudioConnection          patchCord14(delay_feedback_l, delay_l);
AudioConnection          patchCord15(delay_r, 0, delay_lp_r, 0);
AudioConnection          patchCord16(delay_r, 0, delay_drywet_r, 1);
AudioConnection          patchCord17(delay_l, 0, delay_lp_l, 0);
AudioConnection          patchCord18(delay_l, 0, delay_drywet_l, 1);
AudioConnection          patchCord19(delay_drywet_l, 0, reverb_drywet_l, 0);
AudioConnection          patchCord20(delay_drywet_l, verb_lp_l);
AudioConnection          patchCord21(delay_drywet_r, 0, reverb_drywet_r, 0);
AudioConnection          patchCord22(delay_drywet_r, verb_lp_r);
AudioConnection          patchCord23(verb_lp_l, 0, rev_mix, 0);
AudioConnection          patchCord24(verb_lp_r, 0, rev_mix, 1);
AudioConnection          patchCord25(rev_mix, freeverb_st);
AudioConnection          patchCord26(freeverb_st, 0, reverb_drywet_l, 1);
AudioConnection          patchCord27(freeverb_st, 1, reverb_drywet_r, 1);
AudioConnection          patchCord28(reverb_drywet_l, 0, filter_l, 0);
AudioConnection          patchCord29(reverb_drywet_r, 0, filter_r, 0);
AudioConnection          patchCord30(filter_r, 0, i2s2, 1);
AudioConnection          patchCord31(filter_l, 0, i2s2, 0);
AudioControlSGTL5000     audioShield;    //xy=1189.75,201
// GUItool: end automatically generated code





// *********** DEBUG LEVELS

// MIDI CC 
//#define DEBUG

// POTS and BUTTONS and ENCODER
#define DEBUG2

// DISPLAY
//#define DEBUG3

// PEAK values
//#define DEBUG4

// *********** OLED STUFF
//Adafruit_SSD1306 display(128, 64, &Wire, -1, 1000000);  // 1MHz I2C clock


// *********** VARIABLES 

// -- CONSTANTS
const int audioChSelect = AUDIO_INPUT_LINEIN;
const int DT_PIN = 4, CLK_PIN = 5;
const int SW_PIN = 3;
const int LED_PIN = 13;

const int LED_HIGH = 255;
const int LED_LOW = 10;

const byte MIDICHANNEL = 1;
const byte DRY = 0;
const byte WET = 1;

const byte UP = 1;
const byte DOWN = 0;


const float MIN_LP = 100;
const float MAX_LP = 20000;
const float MIN_RES = 0;
const float MAX_RES = 18;
const float MAXDELAYTIME = 245;



//-- EFFECT STORED VALUES

byte bitcrush_bits = 16;
int bitcrush_samplerate = 44100;
float bitcrush_wet = 0;

float delay_feedback = 0;
float delay_time = 0;
float delay_wet = 0;

float reverb_roomsize = 0;
float reverb_damp = 0;
float reverb_wet = 0;

float filter_cutoff = MAX_LP;
float filter_res = MIN_RES;

//-- OVERALL VOLUME
float vol = 0.5;

//POTS
ResponsiveAnalogRead pot1(A10, true);
ResponsiveAnalogRead pot2(A11, true);
ResponsiveAnalogRead pot3(A13, true);
ResponsiveAnalogRead pot4(A12, true);
ResponsiveAnalogRead pot5(A8, true);
ResponsiveAnalogRead pot6(A0, true);
ResponsiveAnalogRead pot7(A3, true);
ResponsiveAnalogRead pot8(A2, true);

//BUTTONS
Encoder knob(DT_PIN, CLK_PIN);
Bounce swButton = Bounce(SW_PIN, 10);
byte sw_state = UP;
int previous_pos = 0;
bool bitcrushing = true;


//const byte SW1 = 5;
//const byte SW2 = 4;
//Bounce bounceSW1 = Bounce(SW1, 10);
//Bounce bounceSW2 = Bounce(SW2, 10);
//byte sw_state = 0; //0 middle; 1=up; 2=down

// CC VALUE CONSTANTS
const byte CC_DELAY_DRYW = 102;
const byte CC_DELAY_FEED = 103;
const byte CC_DELAY_TIME = 104;

const byte CC_LOWPASS_CUTOFF = 105;
const byte CC_LOWPASS_RESO = 106;

const byte CC_REVERB_DRYW = 107;
const byte CC_REVERB_ROOM = 100;
const byte CC_REVERB_DAMP = 101;

const byte CC_VOLUME = 108;

const byte CC_BITCRUSH_BITS = 109;
const byte CC_BITCRUSH_RATE = 110;
const byte CC_BITCRUSH_DRYW = 111;

// -----------------------------------------------------------------------------

// PEAK variables
elapsedMillis fps;
uint8_t cnt=0;
//

void setup()
{
    Serial.begin(9600);

    //audio board thingy
    Serial.println("Setting up audio..");

    AudioMemory(200);
    AudioProcessorUsageMaxReset();
        
    audioShield.enable();
    audioShield.inputSelect(audioChSelect);
    audioShield.volume(vol);
    
    

    
    // button pinouts
     pinMode(SW_PIN, INPUT_PULLUP);

  //  pinMode(SW1, INPUT_PULLUP);
  //  pinMode(SW2, INPUT_PULLUP);
  
    // Initiate led for output
      pinMode(LED_PIN, OUTPUT);

    //turn on red led
      analogWrite(LED_PIN, LED_HIGH);

      //*********** OLED display

/*
      #ifdef DEBUG
      Serial.println("Setting up OLED..");
      #endif
      
      display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
      delay(100);
      initOLED();  
*/
      // *************** MIDI
      usbMIDI.setHandleControlChange(handleCC);


      //************* BUTTONS
      //initate buttons and pots
      //initiateButtons();

    /// ************* POTS
    pot1.setActivityThreshold(25);
    pot2.setActivityThreshold(25);
    pot3.setActivityThreshold(25);
    pot4.setActivityThreshold(25);
    pot5.setActivityThreshold(25);
    pot6.setActivityThreshold(25);
    pot7.setActivityThreshold(25);
    pot8.setActivityThreshold(25);

    initEffectValues();
       
}


void loop()
{

    updateButtons();

    updatePots();

    updateEncoder();
  
    usbMIDI.read();

    #ifdef DEBUG4
      if(fps > 24) {
        if (peak_L.available() && peak_R.available()) {
          fps=0;
          uint8_t leftPeak=peak_L.read() * 30.0;
          uint8_t rightPeak=peak_R.read() * 30.0;

          for(cnt=0;cnt<30-leftPeak;cnt++) {
            Serial.print(" ");
          }
          while(cnt++<30) {
            Serial.print("<");
          }
          Serial.print("||");
          for(cnt=0;cnt<rightPeak;cnt++) {
            Serial.print(">");
          }
          while(cnt++<30) {
            Serial.print(" ");
          }
          Serial.print("Left peak:");
          Serial.print(leftPeak);
          Serial.print(", Right peak: ");
          Serial.print(rightPeak);
          Serial.println();
        }
      }
    #endif
}

void initEffectValues() {
    
    //********* INITIAL VALUES FOR EFFECTS *******************

    //-- BITCRUSH

    bitcrusher_drywet_l.gain(DRY,0);
    bitcrusher_drywet_l.gain(WET,1);

    bitcrusher_drywet_r.gain(DRY,0);
    bitcrusher_drywet_r.gain(WET,1);

    bitcrusher_l.bits(bitcrush_bits);
    bitcrusher_l.sampleRate(bitcrush_samplerate);

    bitcrusher_r.bits(bitcrush_bits);
    bitcrusher_r.sampleRate(bitcrush_samplerate);


    //-- DELAY    
   
    delay_drywet_l.gain(DRY,1);
    delay_drywet_l.gain(WET,0);

    delay_drywet_r.gain(DRY,1);
    delay_drywet_r.gain(WET,0);
    
    delay_feedback_l.gain(DRY,1);
    delay_feedback_l.gain(WET,0);

    delay_feedback_r.gain(DRY,1);
    delay_feedback_r.gain(WET,0);

    delay_lp_l.setLowpass(0,6000,0.6);
    delay_lp_r.setLowpass(0,6000,0.6);


    //-- REVERB
    reverb_drywet_l.gain(DRY,1);
    reverb_drywet_l.gain(WET,0);

    reverb_drywet_r.gain(DRY,1);
    reverb_drywet_r.gain(WET,0);
    
    freeverb_l.roomsize(0.5);
    freeverb_l.damping(0);

    freeverb_l.roomsize(0.5);
    freeverb_r.damping(0);

    freeverb_st.roomsize(0.5);
    freeverb_st.damping(0);

    rev_mix.gain(0,1);
    rev_mix.gain(1,1);

    verb_lp_l.setHighpass(0,500,0.3);
    verb_lp_r.setHighpass(0,500,0.3);

    verb_lp_l.setLowpass(0,5000,0.3);
    verb_lp_r.setLowpass(0,5000,0.3); 
        

    //-- LP FILTER
   // filter_l.setLowpass(0,filter_cutoff,filter_res/10); 
   // filter_r.setLowpass(0,filter_cutoff,filter_res/10);
   filter_l.frequency(filter_cutoff);
   filter_l.resonance(filter_res);
   filter_r.frequency(filter_cutoff);
   filter_r.resonance(filter_res);
   
   filter_l.inputDrive(2);
   filter_r.inputDrive(2);


}


void initOLED() {

/*
      display.clearDisplay();
      display.display();


      switch (sw_state) {

        case 1:
          handleCC(1,CC_REVERB_DRYW,pot_read);
        break;
        
        case 0:
           handleCC(1,CC_DELAY_DRYW,pot_read);
        break;

        case 2:
          handleCC(1,CC_BITCRUSH_BITS,pot_read);
        break;
        }

  */


  /*
  
      display.clearDisplay();
      display.display();

      display.setTextSize(1);
      display.setTextColor(1);

      display.setCursor(0,0);
      display.print(r_size);
      display.print("  ");
      display.print(r_damp);
      display.print("  ");
      display.print(r_mix);
      
      display.setCursor(0,8);
      display.print("Size Damp Mix");

      display.setCursor(0,16);
      display.print(d_feedback);
      display.print("  ");
      display.print(d_time);
      display.print("  ");
      display.print(d_mix);

      display.setCursor(0,24);
      display.print("Feed Time Mix");


      display.setCursor(0,40);
      display.print(cutoff);
      display.print("  ");
      display.print(crushBits);
      display.print("  ");
      display.print(sampleRt);

      display.setCursor(0,48);
      display.print("Cutoff Rate Smple");

      display.display();

      */
 
  }



// ***************** OLED DISPLAY FUNCTIONS **************
  

  void refreshOLEDReverb() {

  /*  

      display.setTextColor(WHITE, BLACK);
      display.setCursor(0,0); 
      display.print(String(r_size));
      display.print("  ");
      display.print(r_damp);
      display.print("  ");
      display.print(r_mix);
            
      display.display();
      
       #ifdef DEBUG2
       Serial.println(AudioMemoryUsage());
       #endif
    */   
  }

    void refreshOLEDDelay() {

      /*

      display.setTextColor(WHITE, BLACK);            
      display.setCursor(0,16);
      display.print(d_feedback);
      display.print("  ");
      display.print(d_time);
      display.print("  ");
      display.print(d_mix);

      display.display();
            #ifdef DEBUG2
       Serial.println(AudioMemoryUsage());
       #endif

       */
  }


    void refreshOLEDBitCrush() {

      /*

      display.setTextColor(WHITE, BLACK);            
      display.setCursor(50,40);
      display.print(crushBits);
      display.print("  ");
      display.print(sampleRt);

      display.display();
            #ifdef DEBUG2
       Serial.println(AudioMemoryUsage());
       #endif
       */
  }


      void refreshOLEDCutoff() {

    /*
      display.setTextColor(WHITE, BLACK);            
      display.setCursor(0,40);
      display.print(cutoff);
      
      display.display();
            #ifdef DEBUG2
       Serial.println(AudioMemoryUsage());
       #endif
       */
  }
  
  

//*************** BUTTONS

void initiateButtons() {

/*
    //check which mode we are on
    bounceSW1.update();
    bounceSW2.update();

    int sw1_value = bounceSW1.read();
    int sw2_value = bounceSW2.read();

       #ifdef DEBUG2
        Serial.print("SW1 VALUE:");
        Serial.println(sw1_value);
      #endif  

       #ifdef DEBUG2
        Serial.print("SW2 VALUE:");
        Serial.println(sw2_value);
      #endif  
    
    if (sw1_value == LOW) {
        sw_state = 1;
      }
    else if (sw2_value == LOW) {
        sw_state = 2;
      }
    else 
    {
       sw_state = 0;
      }

       #ifdef DEBUG2
        Serial.print("SW_STATE:");
        Serial.println(sw_state);
      #endif  

   */   
    
  }

void updatePots() {
    
    int pot_read = -1;
    byte current_pot = 0;
    
    pot1.update();
    pot2.update();
    pot3.update();
    pot4.update();
    pot5.update();
    pot6.update();
    pot7.update();
    pot8.update();


    //*****  DRY / WETS *********************************

    // bitcrush
    if(pot5.hasChanged()) {
      current_pot = 5;
      pot_read = (byte)map(pot5.getValue(),0,1023,0,127);      
      if (bitcrushing) {
        handleCC(1,CC_BITCRUSH_BITS,pot_read);
      }      
     }

    // delay
    if(pot6.hasChanged()) {
      current_pot = 6;
      pot_read = (byte)map(pot6.getValue(),0,1023,0,127);      
      handleCC(1,CC_DELAY_DRYW,pot_read);      
     }
    
    // *** DELAY PARAMETERS ************************************

    if(pot2.hasChanged()) {
      current_pot = 2;
      pot_read = (byte)map(pot2.getValue(),0,1023,0,127);
      handleCC(1,CC_DELAY_TIME,pot_read);
      } 

    if(pot3.hasChanged()) {
      current_pot = 3;
      pot_read = (byte)map(pot3.getValue(),0,1023,0,127);
      handleCC(1,CC_DELAY_FEED,pot_read);
      } 

    //**** REVERB *****
      if(pot4.hasChanged()) {
      current_pot = 4;
      pot_read = (byte)map(pot4.getValue(),0,1023,0,127);
      if (sw_state == UP)
        handleCC(1,CC_REVERB_DRYW,pot_read);  
      else 
        handleCC(1,CC_REVERB_ROOM,pot_read);
        //handleCC(1,CC_REVERB_DAMP,pot_read); 
      }


    // **** LOWPASS PARAMETERS *********************************
    if(pot7.hasChanged()) {
      current_pot = 7;
      pot_read = (byte)map(pot7.getValue(),0,1023,0,127);
      handleCC(1,CC_LOWPASS_CUTOFF,pot_read);  
      }

    if(pot8.hasChanged()) {
      current_pot = 8;
      pot_read = (byte)map(pot8.getValue(),0,1023,0,127);     
      handleCC(1,CC_LOWPASS_RESO,pot_read);
      //handleCC(1,CC_REVERB_DRYW,pot_read);            
     }
      


    // **** BITCRUSH PARAMETERS              
    if(pot1.hasChanged()) {
      current_pot = 1;
      pot_read = (byte)map(pot1.getValue(),0,1023,0,127);
      if (bitcrushing) {
        handleCC(1,CC_BITCRUSH_RATE,pot_read);
        }
      }           


    //DEBUG
      #ifdef DEBUG
        if (pot_read > 0) {
          Serial.print("POT ");
          Serial.print(current_pot);
          Serial.print(": ");
          Serial.println(pot_read);
        }
      #endif     
  
  }

void updateButtons() {


      //****** BUTTON LOGIC

    if (swButton.update()) {
      if (swButton.fallingEdge()) {
        sw_state = DOWN;
        #ifdef DEBUG2
          Serial.println("State UP, Button released");
        #endif
        }
      
      if (swButton.risingEdge()) {
         sw_state=UP;
        // toggle bitcusher on and off
        if (bitcrushing){
            bitcrusher_drywet_l.gain(DRY,1);
            bitcrusher_drywet_l.gain(WET,0);
            bitcrusher_drywet_r.gain(DRY,1);
            bitcrusher_drywet_r.gain(WET,0);      
            bitcrushing=false;
          }
        else
        {
            bitcrusher_drywet_l.gain(DRY,0);
            bitcrusher_drywet_l.gain(WET,1);
            bitcrusher_drywet_r.gain(DRY,0);
            bitcrusher_drywet_r.gain(WET,1);             
            bitcrushing=true;
        }
        #ifdef DEBUG2
          Serial.println("State UP, Button released.");
          Serial.print("Bitcrushing is ");
          Serial.println(bitcrushing);
        #endif
        }
      }
  }

void updateEncoder() {

  int pos;
  pos = knob.read();
  if (pos != previous_pos) {
     previous_pos = pos;
    
    if (pos >= 127) {
      previous_pos = 127;
      knob.write(previous_pos);
    }
    
    if (pos <= 0) {
      previous_pos = 0;
      knob.write(previous_pos);
    }

    #ifdef DEBUG2
      Serial.print("Position: ");
      Serial.println(previous_pos);
    #endif
    }

}

// ************** MIDI CALLBACK FUNCTIONS *************************

void handleCC(byte channel, byte control, byte value) {


  #ifdef DEBUG
    Serial.print("CC received:");
    Serial.print("Channel:");
    Serial.print(channel);
    Serial.print(" , control:");
    Serial.print(control);
    Serial.print(" , value:");
    Serial.println(value);
  #endif
  
  
  switch (control) {

   // ************* BITCRUSH ***************************
   
    case CC_BITCRUSH_DRYW: 
     { 
       if (bitcrush_wet != ((float)value / 127)) {

         bitcrush_wet = (float)value / 127;
         bitcrusher_drywet_l.gain(WET,bitcrush_wet);
         bitcrusher_drywet_r.gain(WET,bitcrush_wet);   
        
        #ifdef DEBUG2
         Serial.print("Bitcrush wet : ");
         Serial.print(value);
         Serial.println();
        #endif
       }
     }      
     break; 
      
    case CC_BITCRUSH_BITS: 
     {
      if (bitcrush_bits != (byte)map(value,0,127,4,16)) {
          bitcrush_bits = (byte)map(value,0,127,4,16);
          bitcrusher_l.bits(bitcrush_bits);
          bitcrusher_r.bits(bitcrush_bits);
                  
        #ifdef DEBUG2
         Serial.print("Crushbits: ");
         Serial.print(bitcrush_bits);
         Serial.println();
        #endif
  
        refreshOLEDBitCrush();
        }
      }
      break; 
       
    case CC_BITCRUSH_RATE: 
     {
      if (bitcrush_samplerate != (int)map(value,0,127,1,44100)) {
      bitcrush_samplerate = (int)map(value,0,127,1,44100);
      bitcrusher_l.sampleRate(bitcrush_samplerate);
      bitcrusher_r.sampleRate(bitcrush_samplerate);
                    
      #ifdef DEBUG2
       Serial.print("Samplerate: ");
       Serial.print(bitcrush_samplerate);
       Serial.println();
      #endif
      refreshOLEDBitCrush();
      }
     }
     break; 

     //************** DELAY ************************

    case CC_DELAY_DRYW:
     {
     if (delay_wet != ((float)value / 127)) {
      
       delay_wet = (float)value / 127;
       delay_drywet_l.gain(WET,(float)value / 127);
       delay_drywet_r.gain(WET,(float)value / 127);
              
       #ifdef DEBUG2
          Serial.print("Delay mix: ");
          Serial.println((float)value / 127);
       #endif
        
       refreshOLEDDelay();
        }
      } 
      break;  
    
    case CC_DELAY_FEED: 
      {

       if (delay_feedback != ((float)value / 127)) {
         delay_feedback = (float)value / 127; 
  
          //set delay loopbacl mixers
         delay_feedback_l.gain(WET,delay_feedback);    
         delay_feedback_r.gain(WET,delay_feedback);
        
          // if loopback value is less than 0.1, turn delay off from output
         if (delay_feedback < 0.1)
         {
            delay_feedback_l.gain(WET,0);
            delay_feedback_r.gain(WET,0);
          } 
         
           
            #ifdef DEBUG2
             Serial.print("Delay Feedback: ");
             Serial.print(delay_feedback);
              Serial.println();
           #endif
    
          refreshOLEDDelay();
        }
       }
       break;
                   
    case CC_DELAY_TIME: {

          if (delay_time != (float)map(value,0,127,1,MAXDELAYTIME)) {
          delay_time = (float)map(value,0,127,1,MAXDELAYTIME);  
          delay_l.delay(0, delay_time);
          delay_r.delay(0, delay_time);
        
          #ifdef DEBUG2
            Serial.print("Delay time: ");
            Serial.print(delay_time);
            Serial.println();
          #endif 
  
        refreshOLEDDelay();
        }
      }  
      break;

     // ************* REVERB ***************
     
     case CC_REVERB_DRYW: 
      {
        if (reverb_wet != ((float)value / 127)) {
           reverb_wet = (float)value / 127;
           reverb_drywet_l.gain(WET,reverb_wet);
           reverb_drywet_r.gain(WET,reverb_wet);      
            
          #ifdef DEBUG2
           Serial.print("Reverb Mix : ");
           Serial.print((float)value / 127);
           Serial.println();
          #endif
      
          refreshOLEDReverb();
        }
      }
      break;

    case CC_REVERB_ROOM: {

        if (reverb_roomsize != (float)value / 127) {
          reverb_roomsize = (float)value / 127;
          freeverb_l.roomsize(reverb_roomsize);
          freeverb_r.roomsize(reverb_roomsize);
          freeverb_st.roomsize(reverb_roomsize);
         
          #ifdef DEBUG2
           Serial.print("Roomsize: ");
           Serial.print(reverb_roomsize*127);
           Serial.println();
          #endif
          
         refreshOLEDReverb();
        }
      }
    break;

    //********** REVERB DAMP 
    case CC_REVERB_DAMP: {

       if (reverb_damp != (float)value / 127) {
         reverb_damp = (float)value / 127;
         freeverb_l.damping(reverb_damp);
         freeverb_r.damping(reverb_damp);
         freeverb_st.damping(reverb_damp);
          
        #ifdef DEBUG2
         Serial.print("Damping: ");
         Serial.print(reverb_damp*127);
         Serial.println();
        #endif
  
        refreshOLEDReverb();
       }
      }
    break;
      
      

    // **************** LOWPASS **********************
    case CC_LOWPASS_CUTOFF: {


       int diff = (int)map(value,0,127,MIN_LP,MAX_LP)-filter_cutoff;
       if (diff<0) { 
        diff=diff*-1;
        }
       if (diff>400) { 
        filter_cutoff = (int)map(value,0,127,MIN_LP,MAX_LP); 
        //filter_l.setLowpass(0,filter_cutoff,filter_res/10);
        //filter_r.setLowpass(0,filter_cutoff,filter_res/10);
          filter_l.frequency(filter_cutoff);
          filter_r.frequency(filter_cutoff);
               
        #ifdef DEBUG2
         Serial.print("Lowpass cutoff: ");
         Serial.print(filter_cutoff);
         Serial.println();
        #endif
  
       refreshOLEDCutoff();       
       
       }
      }
      break;
   
    case CC_LOWPASS_RESO: {
  
        if (filter_res != (float)map(value,0,127,MIN_RES,MAX_RES)) {
          filter_res = (float)map(value,0,127,MIN_RES,MAX_RES);        
         // filter_l.setLowpass(0,filter_cutoff,filter_res/10);
         // filter_r.setLowpass(0,filter_cutoff,filter_res/10);
            filter_l.resonance(filter_res/10);
            filter_r.resonance(filter_res/10);
           
          #ifdef DEBUG2
           Serial.print("Lowpass res: ");
           Serial.print(filter_res/10);
           Serial.println();
          #endif
        }
      }
      break;


    //**** VOLUME
      
    case CC_VOLUME: {
      
        vol = (float)value / 127;
        audioShield.volume(vol);
                
      #ifdef DEBUG2
       Serial.print("Volume: ");
       Serial.print(vol);
       Serial.println();
      #endif
      }
    break;

 }
}      
     



 
