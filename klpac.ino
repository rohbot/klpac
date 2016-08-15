#define NUM_LIGHTS 6

//Set up pins
int input1 = A0;
int led1 = 3;
int led2 = 5;
int led3 = 6;
int led4 = 9;
int led5 = 10;
int led6 = 11;

unsigned long debounce_time = 500;  //Time between jumps to activate

unsigned long turn_on_time = 1024; // Time to fade on Light
unsigned long turn_off_time = 4864; // Time to fade off light

unsigned long rampUpStep = turn_on_time / 256;
unsigned long rampDownStep = turn_off_time / 256; 

// Arrays for storing 
int lights[NUM_LIGHTS];
int light_vals[NUM_LIGHTS];
int light_rampUp[NUM_LIGHTS];
int light_rampDown[NUM_LIGHTS];
unsigned long time[NUM_LIGHTS];


unsigned long dt;
int reading;

bool serial_debug = true;    

void setup(){
  
  Serial.begin(9600);                   

  lights[0] = led1;
  lights[1] = led2;
  lights[2] = led3;
  lights[3] = led4;
  lights[4] = led5;
  lights[5] = led6;


  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);
  pinMode(led6,OUTPUT);

  
  analogWrite(led1,0);
  analogWrite(led2,0);
  analogWrite(led3,0);
  analogWrite(led4,0);
  analogWrite(led5,0);
  analogWrite(led6,0);

  //Initialise arrays

  for(int i = 0; i < 6; i++){
    light_vals[i] = 0;
    light_rampUp[i] = 0;
    light_rampDown[i] = 1;
    time[i] = millis();

  }

 

}

void loop(){
  
  reading = analogRead(input1);

  if(reading > 400){
    light_rampUp[0]  = 1;

  }else{
    light_rampDown[0]  = 1;

  }
  if(reading > 600){
    light_rampUp[1]  = 1;

  }else{
    light_rampDown[1]  = 1;

  }

  if(reading > 700){
    light_rampUp[2]  = 1;

  }else{
    light_rampDown[2]  = 1;

  }
  if(reading > 800){
    light_rampUp[3]  = 1;

  }else{
    light_rampDown[3]  = 1;

  }

  if(reading > 950){
    light_rampUp[4]  = 1;

  }else{
    light_rampDown[4]  = 1;

  }
  if(reading > 1000){
    light_rampUp[5]  = 1;

  }else{
    light_rampDown[5]  = 1;

  }


  if(serial_debug){
    Serial.print(reading);
    Serial.print("\t");
    Serial.println(millis());
  }

  for(int i=0; i < NUM_LIGHTS; i++){
  
    dt = millis() - time[i];

    if(light_rampUp[i] && dt >= rampUpStep){
        light_vals[i] += 1;
        time[i] = millis();
    }

    if(!light_rampUp[i] && dt >= rampDownStep){
      light_vals[i] -= 2;
      if(light_rampDown[i] == 1){
        light_vals[i] -= 5;
      }
      time[i] = millis();
    }

    if(light_vals[i] > 254){
      light_vals[i] = 255;
      light_rampUp[i] = 0;

    }


    if(light_vals[i] < 1){
      light_vals[i] = 0;
      //light_rampDown[0] = 0;
     
    }

    analogWrite(lights[i], light_vals[i]);  
  }
  

}

   
 
