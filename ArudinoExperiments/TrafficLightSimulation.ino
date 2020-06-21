// Implemenation of traffic light simulation using finite statemachine logic without delay()
// Bulusu, Ravikiran
// Hardware connections on Arudino Nano
// D12 to 330ohms to yellow led, D11 to 330ohms t0 red led, D10 to 330 ohms to green led, D5 to SPST and common ground
// Output
// Press button to start simulation, yellow led blinks for 3 times
// then switch on the red led, followed by transition state from 
// green led (after yellow led blinks for 3 times), finally turn off.

// button
int pin_button = 5;

// red led
int pin_redLed = 11;
int state_redLed = 0;
unsigned long t_redLed = 0;
unsigned long t_0_redLed = 0;
unsigned long on_delay_redLed = 1000;
unsigned long off_delay_redLed = 500;

// green led
int pin_greenLed = 10;
int state_greenLed = 0;
unsigned long t_greenLed = 0;
unsigned long t_0_greenLed = 0;
unsigned long on_delay_greenLed = 2000;
unsigned long off_delay_greenLed = 500;

// yellow led
int pin_yellowLed = 12;
int state_yellowLed = 0;
unsigned long t_yellowLed = 0;
unsigned long t_0_yellowLed = 0;
unsigned long on_delay_yellowLed = 300;
unsigned long off_delay_yellowLed = 300;
int beep_count_yellowLed = 0;
int beep_number_yellowLed = 3;

// traffic light
int state_current_trafficLight = 0;

void setup(){
  pinMode(pin_button,INPUT_PULLUP);
  pinMode(pin_redLed,OUTPUT);
  pinMode(pin_greenLed,OUTPUT);
  pinMode(pin_yellowLed,OUTPUT);
}

void loop() {
  StateMachine_trafficLightSimulation();
  StateMachine_yellowLed();
  StateMachine_redLed();
  StateMachine_greenLed();
}

void StateMachine_trafficLightSimulation(){
  // switch case to handle traffic light simulation
  switch(state_current_trafficLight){
    case 0: // RESET
      state_current_trafficLight = 1;
      if(state_greenLed == 0)
      {
        state_yellowLed = 0;
        state_redLed = 0;
        state_greenLed = 0;
      }
    break;

    case 1: // Start
      if(!digitalRead(pin_button))
      {
        state_yellowLed = 2;
        state_current_trafficLight = 2;
      }
    break;

    case 2: // Turn on Red led
        if(state_yellowLed == 0)
        {
          state_redLed = 2;
          state_current_trafficLight = 3;
        }
    break;

    case 3: // Transition from red to green through yellow
        if(state_redLed == 0)
        {
          state_yellowLed = 2;
          state_current_trafficLight = 4;
        }
    break;
        
    case 4:  // Turn on Green led
        if(state_yellowLed == 0)
        {
          state_greenLed = 2;
          state_current_trafficLight = 0;
        }
    break;
  }
}

void StateMachine_redLed() {
  //State Machine Section
  switch(state_redLed) {
    case 0: //RESET
      state_redLed = 1;
    break;
    case 1: //WAIT
      //Do nothing.  Only the top level loop can force us out of this state into state 2 "TURN ON"
    break;
    case 2: //TURN ON
      //Start buzzer, record time then proceed to ON, 
      digitalWrite(pin_redLed,HIGH);
      t_0_redLed = millis();
      state_redLed = 3;
    break;
    case 3: //ON
      //Wait for time to elapse, then proceed to TURN OFF
      t_redLed = millis();
      if (t_redLed - t_0_redLed > on_delay_redLed) {state_redLed = 4;}
    break;
    case 4: //TURN OFF
      t_0_redLed = millis();
      digitalWrite(pin_redLed,LOW);
      state_redLed = 5;
    break;
    case 5: //OFF
      t_redLed = millis();
      if (t_redLed - t_0_redLed > off_delay_redLed) {state_redLed = 0;}
      break;
  }
}

void StateMachine_greenLed() {
  //State Machine Section
  switch(state_greenLed) {
    case 0: //RESET
      state_greenLed = 1;
    break;
    case 1: //WAIT
      //Do nothing.  Only the top level loop can force us out of this state into state 2 "TURN ON"
    break;
    case 2: //TURN ON
      //Start buzzer, record time then proceed to ON, 
      digitalWrite(pin_greenLed,HIGH);
      t_0_greenLed = millis();
      state_greenLed = 3;
    break;
    case 3: //ON
      //Wait for time to elapse, then proceed to TURN OFF
      t_greenLed = millis();
      if (t_greenLed - t_0_greenLed > on_delay_greenLed) {state_greenLed = 4;}
    break;
    case 4: //TURN OFF
      t_0_greenLed = millis();
      digitalWrite(pin_greenLed,LOW);
      state_greenLed = 5;
    break;
    case 5: //OFF
      t_greenLed = millis();
      if (t_greenLed - t_0_greenLed > off_delay_greenLed) {state_greenLed = 0;}
    break;
  }
}

void StateMachine_yellowLed() {
  //State Machine Section
  switch(state_yellowLed) {
    case 0: //RESET
      //Set Beep Count to 0 then proceed to WAIT
      beep_count_yellowLed = 0;
      state_yellowLed = 1;
    break;
    case 1: //WAIT
      //Do nothing.  Only the top level loop can force us out of this state into state 2 "TURN ON"
    break;
    case 2: //TURN ON
      //Start buzzer, record time then proceed to ON, 
      digitalWrite(pin_yellowLed,HIGH);
      t_0_yellowLed = millis();
      state_yellowLed = 3;
    break;
    case 3: //ON
      //Wait for time to elapse, then proceed to TURN OFF
      t_yellowLed = millis();
      if (t_yellowLed - t_0_yellowLed > on_delay_yellowLed) {state_yellowLed = 4;}
    break;
    case 4: //TURN OFF
      //Increment the beep counter, turn off buzzer, proceed to OFF
      beep_count_yellowLed++;
      t_0_yellowLed = millis();
      digitalWrite(pin_yellowLed,LOW);
      state_yellowLed = 5;
    break;
    case 5: //OFF
      t_yellowLed = millis();
      if (t_yellowLed - t_0_yellowLed > off_delay_yellowLed) {state_yellowLed = 2;}
      if (beep_count_yellowLed >= beep_number_yellowLed) {state_yellowLed = 0;}
    break;
  }
}
