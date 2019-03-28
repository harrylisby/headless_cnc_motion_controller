String gcode[n_lines] = {
  "M25",
  "G1 X1920 Y4002 Z340 A0 B1 C2",
  "M15",
  "M26",
  "G0 X9999 Y9999 Z123 A1 B2 C3",
  "G94 F6000",
  "M27",
  "G0 X0001 Y0001 Z333 A1 B2 C5",
  "M16",
  "M28",
  "G94 F8000",
  "G70"
};

long gcode_line_buffer[6];
char c_axis[6] = {'X','Y','Z','A','B','C'};

//handle when only a single axis is send

void gcode_read(unsigned int line){
  if(gcode[line].substring(0,2)=="G0"){
    int n_axis=0; //number of axis in the scan
    while(n_axis<axis_to_read){
      unsigned long line_length = gcode[line].length(); //used to not run forever
      unsigned long s_pos = 0;
      unsigned long f_pos = 0;
      while(gcode[line].charAt(s_pos)!=c_axis[n_axis]){ //look for axis name in string
        s_pos++;
      }
      f_pos=s_pos; //set final pos to start from s_pos found
      while(gcode[line].charAt(f_pos)!=' '){//look for whitespace after X
        f_pos++;
        if(f_pos==line_length){ //stop if line length has been reached
          f_pos=line_length;
          break;
        }
      }

      gcode_line_buffer[n_axis]=atol(gcode[line].substring(s_pos+1,f_pos).c_str()); //save to vector buffer
      n_axis++; //next time read another axis
    }

      x_axis.setMaxSpeed(parameter_feedrate);
      x_axis.setAcceleration(parameter_max_acceleration);
      x_axis.moveTo(gcode_line_buffer[0]);

      y_axis.setMaxSpeed(parameter_feedrate);
      y_axis.setAcceleration(parameter_max_acceleration);
      y_axis.moveTo(gcode_line_buffer[1]);

      // z_axis.setMaxSpeed(parameter_feedrate);
      // z_axis.setAcceleration(parameter_acceleration);
      // z_axis.moveTo(gcode_line_buffer[2]);
      //
      // a_axis.setMaxSpeed(parameter_feedrate);
      // a_axis.setAcceleration(parameter_acceleration);
      // a_axis.moveTo(gcode_line_buffer[3]);
      //
      // b_axis.setMaxSpeed(parameter_feedrate);
      // b_axis.setAcceleration(parameter_acceleration);
      // b_axis.moveTo(gcode_line_buffer[4]);
      //
      // c_axis.setMaxSpeed(parameter_feedrate);
      // c_axis.setAcceleration(parameter_acceleration);
      // c_axis.moveTo(gcode_line_buffer[5]);

  }else if(gcode[line].substring(0,2)=="G1"){
    int n_axis=0; //number of axis in the scan
    while(n_axis<axis_to_read){
      unsigned long line_length = gcode[line].length(); //used to not run forever
      unsigned long s_pos = 0;
      unsigned long f_pos = 0;
      while(gcode[line].charAt(s_pos)!=c_axis[n_axis]){ //look for axis name in string
        s_pos++;
      }
      f_pos=s_pos; //set final pos to start from s_pos found
      while(gcode[line].charAt(f_pos)!=' '){//look for whitespace after X
        f_pos++;
        if(f_pos==line_length){ //stop if line length has been reached
          f_pos=line_length;
          break;
        }
      }

      gcode_line_buffer[n_axis]=atol(gcode[line].substring(s_pos+1,f_pos).c_str()); //save to vector buffer
      n_axis++; //next time read another axis
    }

      x_axis.setMaxSpeed(parameter_feedrate); //G1 runs at constant feedrate
      x_axis.setAcceleration(parameter_acceleration);
      x_axis.moveTo(gcode_line_buffer[0]);

      y_axis.setMaxSpeed(parameter_feedrate); //G1 runs at constant feedrate
      y_axis.setAcceleration(parameter_acceleration);
      y_axis.moveTo(gcode_line_buffer[1]);

      // z_axis.setMaxSpeed(parameter_feedrate);
      // z_axis.setAcceleration(parameter_acceleration);
      // z_axis.moveTo(gcode_line_buffer[2]);
      //
      // a_axis.setMaxSpeed(parameter_feedrate);
      // a_axis.setAcceleration(parameter_acceleration);
      // a_axis.moveTo(gcode_line_buffer[3]);
      //
      // b_axis.setMaxSpeed(parameter_feedrate);
      // b_axis.setAcceleration(parameter_acceleration);
      // b_axis.moveTo(gcode_line_buffer[4]);
      //
      // c_axis.setMaxSpeed(parameter_feedrate);
      // c_axis.setAcceleration(parameter_acceleration);
      // c_axis.moveTo(gcode_line_buffer[5]);


  }else if(gcode[line].substring(0,3)=="G70"){
    current_line=0;
    prevent_skip=true;
    line=0;


  }else if(gcode[line].substring(0,3)=="G94"){
    parameter_feedrate=atol(gcode[line].substring(5,gcode[line].length()).c_str());


  }else if(gcode[line].substring(0,3)=="M15"){
    output_state_relay1=!output_state_relay1;
    digitalWrite(output_relay1,output_state_relay1);


  }else if(gcode[line].substring(0,3)=="M16"){
    output_state_relay2=!output_state_relay2;
    digitalWrite(output_relay2,output_state_relay2);


  }else if(gcode[line].substring(0,3)=="M17"){
    output_state_relay3=!output_state_relay3;
    digitalWrite(output_relay3,output_state_relay3);


  }else if(gcode[line].substring(0,3)=="M18"){
    output_state_relay4=!output_state_relay4;
    digitalWrite(output_relay4,output_state_relay4);


  }else if(gcode[line].substring(0,3)=="M19"){
    output_state_relay5=!output_state_relay5;
    digitalWrite(output_relay5,output_state_relay5);


  }else if(gcode[line].substring(0,3)=="M25"){
    output_state_mosfet1=!output_state_mosfet1;
    digitalWrite(output_mosfet1,output_state_mosfet1);


  }else if(gcode[line].substring(0,3)=="M26"){
    output_state_mosfet2=!output_state_mosfet2;
    digitalWrite(output_mosfet2,output_state_mosfet2);


  }else if(gcode[line].substring(0,3)=="M27"){
    output_state_mosfet3=!output_state_mosfet3;
    digitalWrite(output_mosfet3,output_state_mosfet3);


  }else if(gcode[line].substring(0,3)=="M28"){
    output_state_mosfet4=!output_state_mosfet4;
    digitalWrite(output_mosfet4,output_state_mosfet4);


  }
}
