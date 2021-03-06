#define INTERRUPT_PIN 4   // on digital pin 7
int interruptCount;
float rpm = 0;

void initRPM() {
   digitalWrite(7, HIGH);  
   // Interrupt 6 on the micro must be set this way
   EICRB |= (0<<ISC60)|(1<<ISC61); // sets the interrupt type for EICRB (INT6). 
                                   // EICRA sets interrupt type for INT0...3
   /*
   ISCn0  ISCn1  Where n is the interrupt. 0 for 0, etc
     0      0  Triggers on low level
     1      0  Triggers on edge
     0      1  Triggers on falling edge
     1      1  Triggers on rising edge
   */

   EIMSK |= (1<<INT6); // activates the interrupt. 6 for 6, etc
}

ISR(INT6_vect) {
   interruptCount++;
}
  
void calcRPM(){
   static unsigned long lastTime = 0;
   unsigned long currTime = 0;
   unsigned long timeDiff = 0;
   float timeDiffSeconds=0;
   //https://diydrones.com/forum/topics/brushless-motor-rpm-sensor?id=705844%3ATopic%3A86002&page=3#comments
   // Change value to the number of magnets in the motor divided by 2    
   float numpoles = 7;   // guess it takes two magnets to get an edge
                            
   currTime = millis();
   timeDiff = currTime - lastTime;
   timeDiffSeconds = (timeDiff/1000.0);
   rpm = ((interruptCount/numpoles)/timeDiffSeconds)*60.0;
   interruptCount = 0;
   lastTime = currTime;  // store current time for next iteration
}
