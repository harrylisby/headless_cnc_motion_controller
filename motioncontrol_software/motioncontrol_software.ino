#include <AccelStepper.h>
#include <LiquidCrystal_I2C.h>
#include <RipppleEncoder.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define n_lines 3
#define axis_to_read 2

const byte ENC_PIN_A = PB12;
const byte ENC_PIN_B = PB13;
const byte ENC_BUTTON = PB14;

float parameter_feedrate = 10000.00;
float parameter_acceleration = 500.00;
unsigned long current_line = 0;
bool flag_execution = true;

uint32_t encoder_position = 0;

RipppleEncoder knob(ENC_PIN_A,ENC_PIN_B,ENC_BUTTON);

AccelStepper x_axis(AccelStepper::DRIVER, PA4, PA5);
AccelStepper y_axis(AccelStepper::DRIVER, PA6, PA7);
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
  cTime=millis();

  // if((cTime-lastTime_screen>250)&&flag_execution){
  //   lastTime_screen=cTime;
  //   if(current_line<n_lines){
  //     gcode_read(current_line);
  //     flag_execution=true;
  //   }
  //   if(n_lines==current_line){
  //     flag_execution=false;
  //   }
  //   current_line++;
  // }

  if(!y_axis.isRunning() && !x_axis.isRunning()){ //cambiar por steps left
    gcode_read(current_line);
    current_line++;
  }

    if(cTime-lastTime_enc>(1/enc_update_rate))encoderHandler();
    menuHandler();
    x_axis.run();
    y_axis.run();





}
