    #include <SoftwareSerial.h>
    SoftwareSerial EEBlue(2, 3); // RX | TX\

    int ENA2 = 10;
    int ENA1 = 5;

    int motorDirection11 = 8;
    int motorDirection12 = 9;
    int motorDirection21 = 7;
    int motorDirection22 = 6;
    char like2;
    
    void setup()
    {
     
      Serial.begin(9600);
      EEBlue.begin(9600);  //Default Baud for comm, it may be different for your Module. 
      Serial.println("The bluetooth gates are open.\n Connect to HC-05 from any other bluetooth device with 1234 as pairing key!.");
      pinMode(motorDirection11, OUTPUT);
      pinMode(motorDirection12, OUTPUT);
      pinMode(motorDirection21, OUTPUT);
      pinMode(motorDirection22, OUTPUT);
      pinMode(ENA1, OUTPUT);
      pinMode(ENA2, OUTPUT);

      // Set all direction pins to low to stop all motion
      analogWrite(ENA2, 255);
      analogWrite(ENA1, 255);
      digitalWrite(motorDirection12, LOW);
      digitalWrite(motorDirection11, HIGH);
      digitalWrite(motorDirection22, LOW);
      digitalWrite(motorDirection21, HIGH);
      delay(1000);
      analogWrite(ENA2, 0);
      analogWrite(ENA1, 0);
      digitalWrite(motorDirection12, LOW);
      digitalWrite(motorDirection11, LOW);
      digitalWrite(motorDirection22, LOW);
      digitalWrite(motorDirection21, LOW);

    }
    int hehe = 1;
    void loop()
    {
      
      // Feed any data from bluetooth to Terminal.
      if (EEBlue.available())
        like2 = EEBlue.read();
        if(like2 != ""){
          String like(like2);
        }
        if(hehe == 1){
          String like = String("SS");
        }
        else {
          String like = String(like);
        }

        String like = String(like);
        if(like.indexOf("S") == 0){
          analogWrite(ENA1, 0);
          analogWrite(ENA2, 0);
          digitalWrite(motorDirection12, LOW);
          digitalWrite(motorDirection11, LOW);
          digitalWrite(motorDirection22, LOW);
          digitalWrite(motorDirection21, LOW);
          Serial.print("d");
        }
        if(String(like2).indexOf("R") == 0){
          analogWrite(ENA1, 255);
          analogWrite(ENA2, 255);
          digitalWrite(motorDirection12, HIGH);
          digitalWrite(motorDirection11, LOW);
          digitalWrite(motorDirection21, LOW);
          digitalWrite(motorDirection22, HIGH);
          delay(25);
        }
        if(String(like2).indexOf("K") == 0){
          analogWrite(ENA1, 255);
          analogWrite(ENA2, 255);
          digitalWrite(motorDirection12, HIGH);
          digitalWrite(motorDirection11, LOW);
          digitalWrite(motorDirection21, HIGH);
          digitalWrite(motorDirection22, LOW);
          delay(25);
        }
        if(String(like2).indexOf("J") == 0){
          analogWrite(ENA1, 255);
          analogWrite(ENA2, 255);
          digitalWrite(motorDirection11, HIGH);
          digitalWrite(motorDirection12, LOW);
          digitalWrite(motorDirection22, HIGH);
          digitalWrite(motorDirection21, LOW);
          delay(25);
        }
        if(String(like2).indexOf("F") == 0){
          Serial.print(like.indexOf("FF"));
          analogWrite(ENA2, 255);
          analogWrite(ENA1, 255);
          digitalWrite(motorDirection12, LOW);
          digitalWrite(motorDirection11, HIGH);
          digitalWrite(motorDirection22, LOW);
          digitalWrite(motorDirection21, HIGH);
          delay(25);
        }
        if(String(like2).indexOf("Z") == 0){
          Serial.print(like.indexOf("FF"));
          analogWrite(ENA2, 80);
          analogWrite(ENA1, 255);
          digitalWrite(motorDirection12, LOW);
          digitalWrite(motorDirection11, HIGH);
          digitalWrite(motorDirection22, LOW);
          digitalWrite(motorDirection21, HIGH);
          delay(25);
        }
        if(String(like2).indexOf("X") == 0){
          Serial.print(like.indexOf("FF"));
          analogWrite(ENA2, 255);
          analogWrite(ENA1, 80);
          digitalWrite(motorDirection12, LOW);
          digitalWrite(motorDirection11, HIGH);
          digitalWrite(motorDirection22, LOW);
          digitalWrite(motorDirection21, HIGH);
          delay(25);
        }
        // Serial.print("\n");
        hehe = 0;
        Serial.print(String(like2));
        Serial.print("\n");
        Serial.print(String(like2).indexOf("Z"));
        Serial.print("\n");
        Serial.print("\n");
        
        analogWrite(ENA1, 0);
        analogWrite(ENA2, 0);
        digitalWrite(motorDirection12, LOW);
        digitalWrite(motorDirection11, LOW);
        digitalWrite(motorDirection22, LOW);
        digitalWrite(motorDirection21, LOW);

        // Serial.print("\n");
        // delay(50);
     
      // Feed all data from termial to bluetooth
      if (Serial.available())
        EEBlue.write(Serial.read());
    }