void lcd_main_menu(int update_rate_mainMenu,unsigned long current_time){
  static int lastTime_mainMenu = 0;

  if(current_time-lastTime_mainMenu>update_rate_mainMenu){
    lastTime_mainMenu=current_time;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("X:");
    lcd.print(x_axis.currentPosition());
    lcd.print("  ");
    // lcd.print(x_axis.isRunning());
    // lcd.print(y_axis.isRunning());
    lcd.print(parameter_feedrate);
    lcd.setCursor(0,1);
    lcd.print("Y:");
    lcd.print(y_axis.currentPosition());
    lcd.print("  ");
    lcd.print(current_line);
    lcd.print("  ");
    lcd.print(cTime);
    // lcd.setCursor(9,0);
    // lcd.print("B:");
    // lcd.print(enc_button_shortpress);
    // lcd.print(" L:");
    // lcd.print(enc_button_longpress);
    // lcd.setCursor(9,1);
    // lcd.print("E:");
    // lcd.print(encoder_position);
  }
  if(alarm){
  	lcd.clear();
  	lcd.setCursor(0,0);
  	lcd.print("L. Invalida");
  	lcd.setCursor(0,1);
  	lcd.print("N: ");
  	lcd.print(contador);
  	delay(10000);
  }
}