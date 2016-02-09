int EN1 = 6;
int EN2 = 5;  //Roboduino Motor shield uses Pin 9
int IN1 = 7;
int IN2 = 4; //Latest version use pin 4 instead of pin 8

void Motor1(int pwm, boolean reverse)
{
  analogWrite(EN1, pwm); //set pwm control, 0 for stop, and 255 for maximum speed
  if (reverse)
  {
    digitalWrite(IN1, HIGH);
  }
  else
  {
    digitalWrite(IN1, LOW);
  }
}

void Motor2(int pwm, boolean reverse)
{
  analogWrite(EN2, pwm);
  if (reverse)
  {
    digitalWrite(IN2, HIGH);
  }
  else
  {
    digitalWrite(IN2, LOW);
  }
}

void setup()
{
  // for(int i=6;i<=9;i++) //For Roboduino Motor Shield
  //   pinMode(i, OUTPUT);  //set pin 6,7,8,9 to output mode

  for (int i = 4; i <= 7; i++) //For Arduino Motor Shield
    pinMode(i, OUTPUT);  //set pin 4,5,6,7 to output mode

  Serial.begin(9600);
}

void loop()
{
  char val;
  int speedL, speedR;
  boolean reverseL, reverseR;
  const int SPEED_RATIO = 2;
  char data[4];

  while (true) {
    for (int i = 0; i < 2; ) {
      if (Serial.available() > 0) {
        char temp = (char)Serial.read();
        if (temp == '[') {
          i++;
        }
      }
    }

    for (int i = 0; i < sizeof(data); ) {
      if (Serial.available() > 0) {
        data[i] = (char)Serial.read();
        if (data[i] == '[') {
          return;
        }
        i++;
      }
    }

    reverseL = data[0] == '0' ? true : false;
    if(data[1] != '0') {
      speedL = data[1] * SPEED_RATIO;
    } else {
      speedL = 0;
    }
    
    reverseR = data[2] == '1' ? true : false;
    if(data[3] != '0') {
      speedR = data[3] * SPEED_RATIO;
    } else {
      speedR = 0;
    }

    Motor1(speedL, reverseL);
    Motor2(speedR, reverseR);
    char buffer[256];
    sprintf(buffer, "Motor L: Direction %d Speed %d\n", reverseL, speedL);
    Serial.print(buffer);
    sprintf(buffer, "Motor R: Direction %d Speed %d\n", reverseR, speedR);
    Serial.print(buffer);
  }
}


