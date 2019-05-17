#include <AccelStepper.h>
#include <LiquidCrystal_I2C.h>
#include <RipppleEncoder.h>
#include "parameters.h"
#include <SPI.h>
#include "SdFat.h"

LiquidCrystal_I2C lcd(0x27,16,2);

SdFat SD;
File myFile;
String buffer;

const byte ENC_PIN_A = PB12;
const byte ENC_PIN_B = PB13;
const byte ENC_BUTTON = PB14;

const byte output_relay1 = PB15;
const byte output_relay2 = PA8;
const byte output_relay3 = PA9;
const byte output_relay4 = PA10;
const byte output_relay5 = PA11;

const byte output_mosfet1 = PB8;
const byte output_mosfet2 = PB9;
const byte output_mosfet3 = PA0;
const byte output_mosfet4 = PA1;

bool output_state_relay1,output_state_relay2,output_state_relay3,output_state_relay4,output_state_relay5;
bool output_state_mosfet1,output_state_mosfet2,output_state_mosfet3,output_state_mosfet4;
unsigned long current_line = 0;
bool flag_execution = true;
bool prevent_skip;
int alarm = 0;
int contador = 0;

uint32_t encoder_position = 0;

RipppleEncoder knob(ENC_PIN_A,ENC_PIN_B,ENC_BUTTON);

AccelStepper x_axis(AccelStepper::DRIVER, PB12, PB13);
AccelStepper y_axis(AccelStepper::DRIVER, PB14, PB15);
// AccelStepper z_axis(AccelStepper::DRIVER, PA6, PA7);
// AccelStepper a_axis(AccelStepper::DRIVER, PA6, PA7);
// AccelStepper b_axis(AccelStepper::DRIVER, PA6, PA7);
// AccelStepper c_axis(AccelStepper::DRIVER, PA6, PA7);


void ENC_ISR(){
  knob.encoderRead();
}

void setup(){
  attachInterrupt(digitalPinToInterrupt(ENC_PIN_A),ENC_ISR,CHANGE);

  lcd.init();
  lcd.backlight();

  pinMode(PA4,OUTPUT_OPEN_DRAIN);
  pinMode(PA5,OUTPUT_OPEN_DRAIN);
  pinMode(PA6,OUTPUT);
  pinMode(PA7,OUTPUT);
  pinMode(output_relay1,OUTPUT);
  pinMode(output_relay2,OUTPUT);
  pinMode(output_relay3,OUTPUT);
  pinMode(output_relay4,OUTPUT);
  pinMode(output_relay5,OUTPUT);
  pinMode(output_mosfet1,OUTPUT);
  pinMode(output_mosfet2,OUTPUT);
  pinMode(output_mosfet3,OUTPUT);
  pinMode(output_mosfet4,OUTPUT);

  x_axis.setMaxSpeed(10000.0);
  x_axis.setAcceleration(5000.0);
  //x_axis.moveTo(1920);
  x_axis.setPinsInverted(true,true,false);
  x_axis.setMinPulseWidth(5);

  y_axis.setMaxSpeed(10000.0);
  y_axis.setAcceleration(5000.0);
  //y_axis.moveTo(4002);
  y_axis.setPinsInverted(true,true,false);
  y_axis.setMinPulseWidth(5);

  Serial.begin(115200);

  //pin CS del adaptador microSD conectado al puerto PA3 del bluepill
  if (!SD.begin(SD_PIN)) {
    alarm = 2;
    menuHandler();
    return;
  }
  //Abre el archivo para leer
  myFile = SD.open("test.txt");
}

unsigned long cTime, lastTime_screen, time_of_button_update, prev_button_update, lastTime_enc;
bool enc_button_tracker,enc_button_shortpress, enc_button_longpress;
unsigned long enc_update_rate = 20; //hz

void encoderHandler(){
  encoder_position=knob.encoderCount();

  if(!digitalRead(ENC_BUTTON)){
    enc_button_tracker=true;
    time_of_button_update=cTime;
    if(enc_button_tracker&&!enc_button_shortpress&&(time_of_button_update-prev_button_update>250)){
      enc_button_shortpress=true;
      prev_button_update=time_of_button_update;
    }else if(enc_button_tracker&&(time_of_button_update-prev_button_update>750)){
      enc_button_longpress=true;
      prev_button_update=time_of_button_update;
    }else{
      //enc_button_shortpress=false;
    }
  }else{
    enc_button_tracker=false;
    enc_button_shortpress=false;
    enc_button_longpress=false;
  }
}

void menuHandler(){
  lcd_main_menu(500,cTime);
}

void loop(){

  if (myFile) {
    //mientras haya información en el archivo a leer
    while (myFile.available()) {
      cTime=millis();
      //lea la línea y envíela a ser interpretada
      if(!y_axis.isRunning() && !x_axis.isRunning() && alarm == 0){ //cambiar por steps left
        contador = current_line;
        buffer = myFile.readStringUntil('\n');
        gcode_read(buffer);
      }
      if(cTime-lastTime_enc>(1/enc_update_rate))encoderHandler();
      menuHandler();
      x_axis.run();
      y_axis.run();
      if (alarm != 0){
        x_axis.stop();
        y_axis.stop();
        myFile.close();
      }
      if(prevent_skip){
        Serial.println("entró");
        myFile.seek(0);
        prevent_skip = false;
      }
    }
    cTime=millis();

    menuHandler();
    //cierra el archivo y reinicia el contador
    myFile.close();
  }
}