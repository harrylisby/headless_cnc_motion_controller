String gcode[n_lines] = {
  "G0 X1920 Y4002 Z0 A0",
  "G0 X24400 Y3223 Z0 A0",
  "G0 X55500 Y5532 Z0 A0"
};

long gcode_line_buffer[6];

//char c_axis; //current axis in the scan
char c_axis[6] = {'X','Y','Z','A','B','C'};

void gcode_read(String line){
  if(line.substring(0,2)=="G0"){
    int n_axis=0; //number of axis in the scan
    while(n_axis<axis_to_read){
      unsigned int line_length = line.length(); //used to not run forever
      unsigned int s_pos = 0;
      unsigned int f_pos = 0;
      while(line.charAt(s_pos)!=c_axis[n_axis]){ //look for axis name in string
        s_pos++;
      }
      f_pos=s_pos; //set final pos to start from s_pos found
      while(line.charAt(f_pos)!=' '){//look for whitespace after X
        f_pos++;
        if(f_pos==line_length){ //stop if line length has been reached
          f_pos=line_length;
          break;
        }
      }

      gcode_line_buffer[n_axis]=atol(line.substring(s_pos+1,f_pos).c_str()); //save to vector buffer
      n_axis++; //next time read another axis
    }

      // x_axis.setMaxSpeed(parameter_feedrate);
      // x_axis.setAcceleration(parameter_acceleration);
      x_axis.moveTo(gcode_line_buffer[0]);

      // y_axis.setMaxSpeed(parameter_feedrate);
      // y_axis.setAcceleration(parameter_acceleration);
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
  }
}
