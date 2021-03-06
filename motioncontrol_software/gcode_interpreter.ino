float gcode_line_buffer[6];
char c_axis[7] = {'X','Y','Z','A','B','C','.'};

void setAxisParameters(AccelStepper &axis, long direction, int type = 0){
  switch (type) {
  case 1:
  	axis.setMaxSpeed(parameter_feedrate);
    axis.setAcceleration(parameter_max_acceleration);
    break;
  case 2:
    axis.setMaxSpeed(parameter_max_feedrate);
    axis.setAcceleration(parameter_acceleration);
    break;
  default:
  	axis.setMaxSpeed(parameter_feedrate);
  	axis.setAcceleration(parameter_acceleration);
  	break;
  }
  axis.moveTo(direction);
}

void gcode_read(String line){
	Serial.println(line);
	if(!checkLine(line)){
		Serial.println("Error");
		Serial.println(line);
		alarm = 1;
		return;
	};
	if(line.substring(0,2)=="G0"){
	    int n_axis=0; //number of axis in the scan
	    while(n_axis<axis_to_read){
	    	unsigned long line_length = line.length(); //used to not run forever
	        unsigned long s_pos = 0;
	        unsigned long f_pos = 0;
	        while(line.charAt(s_pos)!=c_axis[n_axis]){ //look for axis name in string
	        	s_pos++;
	        }
	        f_pos=s_pos+1; //set final pos to start from s_pos found
	        while(line.charAt(f_pos)!=' ' && isDigit(line.charAt(f_pos))){//look for whitespace after X
	        	f_pos++;
	        	if(f_pos==line_length){ //stop if line length has been reached
	          		f_pos=line_length;
	          		break;
	        	}
	        	if(line.charAt(f_pos) == '.'){ f_pos++; }
	        }
	        gcode_line_buffer[n_axis]=atof(line.substring(s_pos+1,f_pos).c_str()); //save to vector buffer
	        n_axis++; //next time read another axis
	    }

	    setAxisParameters(x_axis, gcode_line_buffer[0], 1);
    	setAxisParameters(y_axis, gcode_line_buffer[1], 1);

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
	}else if(line.substring(0,2)=="G1"){
	    int n_axis=0; //number of axis in the scan
	    while(n_axis<axis_to_read){
	      	unsigned long line_length = line.length(); //used to not run forever
	      	unsigned long s_pos = 0;
	      	unsigned long f_pos = 0;
	      	while(line.charAt(s_pos)!=c_axis[n_axis]){ //look for axis name in string
	        	s_pos++;	
	      	}

	      	f_pos=s_pos+1; //set final pos to start from s_pos found
	        while(line.charAt(f_pos)!=' ' && isDigit(line.charAt(f_pos))){//look for whitespace after X
	        	f_pos++;
	        	if(f_pos==line_length){ //stop if line length has been reached
	          		f_pos=line_length;
	          		break;
	        	}
	        	if(line.charAt(f_pos) == '.'){ f_pos++; }
	        }
	        gcode_line_buffer[n_axis]=atof(line.substring(s_pos+1,f_pos).c_str()); //save to vector buffer
	        n_axis++; //next time read another axis
	    }

	    setAxisParameters(x_axis, gcode_line_buffer[0]);
	    setAxisParameters(y_axis, gcode_line_buffer[1]);

	    //setAxisParameters(z_axis, gcode_line_buffer[2]);
		// z_axis.setMaxSpeed(parameter_feedrate);
		// z_axis.setAcceleration(parameter_acceleration);
		// z_axis.moveTo(gcode_line_buffer[2]);

		// setAxisParameters(a_axis, gcode_line_buffer[3]);
		// a_axis.setMaxSpeed(parameter_feedrate);
		// a_axis.setAcceleration(parameter_acceleration);
		// a_axis.moveTo(gcode_line_buffer[3]);
		//
		// setAxisParameters(b_axis, gcode_line_buffer[4]);
		// b_axis.setAcceleration(parameter_acceleration);
		// b_axis.moveTo(gcode_line_buffer[4]);
		//
		// setAxisParameters(c_axis, gcode_line_buffer[5]);
		// c_axis.setAcceleration(parameter_acceleration);
		// c_axis.moveTo(gcode_line_buffer[5]);


	}else if(line.substring(0,3)=="G70"){
	    current_line=0;
		prevent_skip=true;

  	}else if(line.substring(0,3)=="G94"){
	  	int val = 4;
	  	if(isSpace(line.charAt(4))){
	  		val++;
	  	}
	    parameter_feedrate=atol(line.substring(val,line.length()).c_str());

  	}else if(line.substring(0,3)=="M15"){
	    output_state_relay1=!output_state_relay1;
	    digitalWrite(output_relay1,output_state_relay1);

  	}else if(line.substring(0,3)=="M16"){
	    output_state_relay2=!output_state_relay2;
	    digitalWrite(output_relay2,output_state_relay2);

  	}else if(line.substring(0,3)=="M17"){
	    output_state_relay3=!output_state_relay3;
	    digitalWrite(output_relay3,output_state_relay3);

  	}else if(line.substring(0,3)=="M18"){
	    output_state_relay4=!output_state_relay4;
	    digitalWrite(output_relay4,output_state_relay4);

  	}else if(line.substring(0,3)=="M19"){
	    output_state_relay5=!output_state_relay5;
	    digitalWrite(output_relay5,output_state_relay5);

  	}else if(line.substring(0,3)=="M25"){
	    output_state_mosfet1=!output_state_mosfet1;
	    digitalWrite(output_mosfet1,output_state_mosfet1);

	}else if(line.substring(0,3)=="M26"){
	    output_state_mosfet2=!output_state_mosfet2;
	    digitalWrite(output_mosfet2,output_state_mosfet2);

  	}else if(line.substring(0,3)=="M27"){
	    output_state_mosfet3=!output_state_mosfet3;
	    digitalWrite(output_mosfet3,output_state_mosfet3);

  	}else if(line.substring(0,3)=="M28"){
	    output_state_mosfet4=!output_state_mosfet4;
	    digitalWrite(output_mosfet4,output_state_mosfet4);
	}
}

bool checkLine(String line){
	char c = line.charAt(0);;
	int len = line.length() - 1;

	if(c != 'G' && c != 'M'){ return false; }

	for(int i = 1; i < len; i++){
		c = line.charAt(i);
		if(!isDigit(c)){
			if(isSpace(c)){
				i++;
				c = line.charAt(i);
			}
			if(checkInArray(c)){
				i++;
				c = line.charAt(i);
				if(!isDigit(c)){ return false; }
			}
			else{ return false; }
		}	
	}
	return true;
}

bool checkInArray(char c){
	bool exist = false;
	for(int i = 0; i < 7; i++){ if(c == c_axis[i]){ exist = true; } }
	return exist;
}