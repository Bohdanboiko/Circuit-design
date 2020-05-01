byte n = 3;     
float r = 3.5;   



float r_speed, rev_time;
volatile unsigned long lastflash, flash, lastshow;
unsigned int RPM;
String spaces = "       ";

void setup() {
  Serial.begin(9600);                  
  attachInterrupt(0, sens, RISING);    
  pinMode(3, OUTPUT);                 
  digitalWrite(3, HIGH);               
  lcd.init();                 
  lcd.backlight();            
  lcd.setCursor(0, 0);       
  lcd.print(L"Оберти: ");    
  lcd.setCursor(0, 1);     
  lcd.print(L"Швидкість: ");  
}
void sens() {
  flash = micros() - lastflash;   
  lastflash = micros();           
}

void loop() {
  if (micros() - lastflash > 1000000) { 
    RPM = 0;                            
    r_speed = 0;
  } else {
    rev_time = (float) flash / 1000000 * n;            
    RPM = (float) 60 / rev_time;                        
    r_speed = (float) 2 * 3.1415 * r / 100 / rev_time * 3.6;  
  }
  if (millis() - lastshow > 300) { 
    lcd.setCursor(9, 0);  
    lcd.print(RPM);      
    lcd.print(spaces);    
    lcd.setCursor(10, 1); 
    lcd.print(r_speed);  
    lcd.print(spaces);    
    lastshow = millis();  
  }
}
