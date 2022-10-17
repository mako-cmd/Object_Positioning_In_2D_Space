/*
  ******PINOUT*****
  *MIC1 -> GPIO 4 *
  *MIC2 -> GPIO 5 *
  *MIC3 -> GPIO 19*
  *****************
*/


//ISR for mic input triggered on falling edge
void mic_1_ISR();
void mic_2_ISR();
void mic_3_ISR();
//flags to track if ISRs have run
bool mic_1_triggered = false;
bool mic_2_triggered = false;
bool mic_3_triggered = false;
//ticker to track how many ISRs have run
int mics_triggered = 0;

int timer_val = 0;

//timer obj init
hw_timer_t * timer_1 = NULL;
hw_timer_t * timer_2 = NULL;
hw_timer_t * timer_3 = NULL;

//timer value buffers
int mic_1_time = 0;
int mic_2_time = 0;
int mic_3_time = 0;

//flags to check if results for timer have run
bool mic_1_printed = false;
bool mic_2_printed = false;
bool mic_3_printed = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //Setup Timers
  timer_1 = timerBegin(1, 1, true);
  timerStop(timer_1);
  timerWrite(timer_1,0);

  timer_2 = timerBegin(2, 1, true);
  timerStop(timer_2);
  timerWrite(timer_2,0);

  timer_3 = timerBegin(3, 1, true);
  timerStop(timer_3);
  timerWrite(timer_3,0);

  //Blue LED used to debug if ISRs are working
  pinMode(2, OUTPUT);

  //Setup mic input pins and ISRs
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  //setup interrupts
  attachInterrupt(4,mic_1_ISR,FALLING);
  attachInterrupt(5,mic_2_ISR,FALLING);
  attachInterrupt(19,mic_3_ISR,FALLING);
  interrupts();
  
}

void loop() {
  // put your main code here, to run repeatedly:

  //if nothing has been triggered, wait...
  while((!(mic_1_triggered || mic_2_triggered || mic_3_triggered)))
  {
    Serial.println("Waiting...");
  }

  //Print results and Run forever
  while(1)
  {
    //if mic 1 has been triggered and the reuslt has not been triggered
    if(mic_1_triggered && !mic_1_printed)
    {
      Serial.print("Mic 1 triggered @: ");
      Serial.println(mic_1_time);
      mic_1_printed = true;
    }
    //if mic 2 has been triggered and the reuslt has not been triggered
    if(mic_2_triggered && !mic_2_printed)
    {
      Serial.print("Mic 2 triggered @: ");
      Serial.println(mic_2_time);
      mic_2_printed = true;
    }
    //if mic 3 has been triggered and the reuslt has not been triggered
    if(mic_3_triggered && !mic_3_printed)
    {
      Serial.print("Mic 3 triggered @: ");
      Serial.println(mic_3_time);
      mic_3_printed = true;
    }
  }
}

void mic_1_ISR()
{
  //Turn interrupts off: Good practice
  noInterrupts();
  //if Mic 1 has already been triggered do not run again: Debouncing
  if(!mic_1_triggered)
  {
    //Flag to show mic_3_ISR has run
    mic_1_triggered = true;
    
    //Flag blue LED showing interrupt is working
    digitalWrite(2, HIGH); 
    
    //Need to call twice because of bug reported at https://github.com/espressif/arduino-esp32/issues/3434
    mic_1_time = timerReadMicros(timer_1);
    mic_1_time = timerReadMicros(timer_1);
    
    //If other mics have not been triggered then timer has not started, start it now
    if (!(mic_2_triggered || mic_3_triggered))
    {
      timerStart(timer_1);
      //timerStart(timer_1);
      mic_1_time = 0;
    }
    //if other mics have been triggered, stop timer
    if (mics_triggered == 2)
    {
      timerStop(timer_1);
    }
    //ticker to track how many mics have been triggered
    mics_triggered++;
  }
  interrupts();
}
void mic_2_ISR()
{
  //Turn interrupts off: Good practice
  noInterrupts();
  //if Mic 2 has already been triggered do not run again: Debouncing
  if(!mic_2_triggered)
  {
    //Flag to show mic_3_ISR has run
    mic_2_triggered = true;
    
    //Flag blue LED showing interrupt is working
    digitalWrite(2, HIGH); 
    
    //Need to call twice because of bug reported at https://github.com/espressif/arduino-esp32/issues/3434
    mic_2_time = timerReadMicros(timer_1);
    mic_2_time = timerReadMicros(timer_1);
    //If other mics have not been triggered then timer has not started, start it now
    if (!(mic_1_triggered || mic_3_triggered))
    {
      timerStart(timer_1);
      //timerStart(timer_1);
      //mic_2_time = 0;
    }
    //if other mics have been triggered, stop timer
    if (mics_triggered == 2)
    {
      timerStop(timer_1);
    }
    //ticker to track how many mics have been triggered
    mics_triggered++;
  }
  interrupts();
}
void mic_3_ISR()
{
  //Turn interrupts off: Good practice
  noInterrupts();
  //if Mic 3 has already been triggered do not run again: Debouncing
  if (!mic_3_triggered)
  {
    //Flag to show mic_3_ISR has run
    mic_3_triggered = true;
    //Flag blue LED showing interrupt is working
    digitalWrite(2, HIGH);
    //Need to call twice because of bug reported at https://github.com/espressif/arduino-esp32/issues/3434
    mic_3_time = timerReadMicros(timer_1);
    mic_3_time = timerReadMicros(timer_1);
    //If other mics have not been triggered then timer has not started, start it now
    if (!(mic_2_triggered || mic_1_triggered))
    {
      timerStart(timer_1);
      //timerStart(timer_1);
      //mic_3_time = 0;
    }
    //if other mics have been triggered, stop timer
    if (mics_triggered == 2)
    {
      timerStop(timer_1);
      
    }
    //ticker to track how many mics have been triggered
    mics_triggered++;
  }
  interrupts();
}
