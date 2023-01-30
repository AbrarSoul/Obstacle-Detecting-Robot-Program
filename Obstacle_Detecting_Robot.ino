 
#define trigPin  A0         // Assign PIN A0 as trigPin (Connect ARDUINO UNO "A0" pin with Ultrasonic Sonar Sensor "TRIG" Pin) 
#define echoPin  A1         // Assign PIN A1 as echoPin (Connect ARDUINO UNO "A1" pin with Ultrasonic Sonar Sensor "ECHO" Pin) 

#define MotorA_IN1  3       // Assign PIN 3 as MotorA_IN1 (Connect ARDUINO UNO "4" pin with L293D Motor Driver "IN1" Pin) 
#define MotorA_IN2  4       // Assign PIN 4 as MotorA_IN2 (Connect ARDUINO UNO "3" pin with L293D Motor Driver "IN2" Pin)

#define MotorB_IN3  5       // Assign PIN 5 as MotorB_IN3 (Connect ARDUINO UNO "7" pin with L293D Motor Driver "IN3" Pin)
#define MotorB_IN4  6       // Assign PIN 6 as MotorB_IN4 (Connect ARDUINO UNO "8" pin with L293D Motor Driver "IN4" Pin)

#define MotorA_PWM  9       // Assign PIN 9 as MOTORA_PWM (Connect ARDUINO UNO "5" pin with L293D Motor Driver "ENA" Pin) 
#define MotorB_PWM  10      // Assign PIN 10 as MOTORB_PWM (Connect ARDUINO UNO "6" pin with L293D Motor Driver "ENB" Pin)


void setup()
  {
  	pinMode(MotorA_IN1, OUTPUT);       // Declare "MotorB_IN1" as "Output Pin".
  	pinMode(MotorA_IN2, OUTPUT);       // Declare "MotorB_IN2" as "Output Pin".
  
  	pinMode(MotorB_IN3, OUTPUT);       // Declare "MotorB_IN3" as "Output Pin".
  	pinMode(MotorB_IN4, OUTPUT);       // Declare "MotorB_IN4" as "Output Pin".
  	
  	pinMode(MotorA_PWM, OUTPUT);       // Declare "MotorA_PWM" as "Output Pin".
  	pinMode(MotorB_PWM, OUTPUT);       // Declare "MotorB_PWM" as "Output Pin". 
  
    pinMode(trigPin, OUTPUT);          // Declare "trigPin" as "Output Pin". 
    pinMode(echoPin, INPUT);           // Declare "echoPin" as "Input Pin". 
  
  }



float search(void)
  {
    float duration = 0.00;                // Float type variable declaration 
    float CM = 0.00;
      
      
      digitalWrite(trigPin, LOW);        // Trig_pin output as OV (Logic Low-Level) 
      delayMicroseconds(2);              // Delay for 2 us
    
      //Send 10us High Pulse to Ultra-Sonic Sonar Sensor "trigPin" 
      digitalWrite(trigPin, HIGH);       // Trig_pin output as 5V (Logic High-Level)
      delayMicroseconds(10);             // Delay for 10 us 
    
      digitalWrite(trigPin, LOW);        // Trig_pin output as OV (Logic Low-Level)
  
    
    duration = pulseIn(echoPin, HIGH); // Start counting time, upto again "echoPin" back to Logical "High-Level" and puting the "time" into a variable called "duration" 
   
    CM = (duration / 58.82); //Convert distance into CM. 
    
   return CM;
  }


void RobotForward()
  {
	digitalWrite(MotorA_IN1, HIGH);
	digitalWrite(MotorA_IN2, LOW);
	digitalWrite(MotorB_IN3, HIGH);
	digitalWrite(MotorB_IN4, LOW);
  }

void RobotBackward()
  {
	digitalWrite(MotorA_IN1, LOW);
	digitalWrite(MotorA_IN2, HIGH);
	digitalWrite(MotorB_IN3, LOW);
	digitalWrite(MotorB_IN4, HIGH);
  }

void RobotLeft()
  {
	digitalWrite(MotorA_IN1, LOW);
	digitalWrite(MotorA_IN2, HIGH);
	digitalWrite(MotorB_IN3, HIGH);
	digitalWrite(MotorB_IN4, LOW);	
  }

void RobotRight()
  {
	digitalWrite(MotorA_IN1, HIGH);
	digitalWrite(MotorA_IN2, LOW);
	digitalWrite(MotorB_IN3, LOW);
	digitalWrite(MotorB_IN4, HIGH);	
  }

void RobotStop()
  {
	digitalWrite(MotorA_IN1, LOW);
	digitalWrite(MotorA_IN2, LOW);
	digitalWrite(MotorB_IN3, LOW);
	digitalWrite(MotorB_IN4, LOW);
  }
  
  
  


void loop()
  {
     float distance = 0.00;
     float RobotSpeed = 0.00;
 
    
    // Measuring the distance in CM
    distance = search();
    
    
    if((distance < 40)) // If obstracle found in 40 CM.
      {
        RobotSpeed = 100; // Speed Down 
        
            analogWrite(MotorA_PWM, RobotSpeed); // Update speed in MOTORA Output Terminal
            analogWrite(MotorB_PWM, RobotSpeed); // Update speed in MOTORB Output Terminal 
        
        RobotStop(); //Robot Stop
        delay(10);
        
        RobotBackward(); //Robot Run Backward Direction 
        delay(400);
        
        
        RobotStop(); //Robot Stop
        delay(10);
       
        
      distance = search(); // Check obstracle again 
       
         int a = 250;
         int b = 250;
         
                   if(distance<30)
                     {
                         RobotRight(); //Robot Turn into Right Direction 
                         a = a+50;     
                         delay(a);
                       
                         distance = search(); // Check obstracle again
                     }
                   
                   else
                     {   
                         b = b+50;    
                         RobotLeft(); //Robot Turn into Left Direction 
                         delay(b);
                      
                         distance = search(); // Check obstracle again
                     }
      }
      
   else if((distance >= 40) && (distance <= 70))
     {
      RobotSpeed = 150; // Speed increase slightly 
      
            analogWrite(MotorA_PWM, RobotSpeed); // Update speed in MOTORA Output Terminal
            analogWrite(MotorB_PWM, RobotSpeed); // Update speed in MOTORB Output Terminal
            
      RobotForward();
     }
    
   else
     {
          RobotSpeed = 255; // Speed increase to full speed 
        
            analogWrite(MotorA_PWM, RobotSpeed); // Update speed in MOTORA Output Terminal
            analogWrite(MotorB_PWM, RobotSpeed); // Update speed in MOTORB Output Terminal
        
        RobotForward(); //Robot Move to Forward Direction
     }
   
    
  }
  
  


