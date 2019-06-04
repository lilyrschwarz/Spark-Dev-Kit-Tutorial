
void blinky(){
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(200);              // wait for a second
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
}

void joinOk(){
  Serial.println("Join Accepted");
  digitalWrite(13, HIGH);   
  delay(1500);              
  digitalWrite(13, LOW);    
  delay(500);              
  digitalWrite(13, HIGH);   
  delay(1500);              
  digitalWrite(13, LOW);    
}

void print_to_console(String message){
  Serial.println(message);
}

void read_data_from_LoRa_Mod(){
  if (Serial1.available()) {
    String inByte = Serial1.readString();
    Serial.println(inByte);
  }
}

void send_LoRa_Command(String cmd){
  print_to_console("Now sending: " + cmd);
  Serial1.print(cmd+"\r");
}

void sparkStart(long baudrate){
  Serial.begin(baudrate);
  Serial1.begin(baudrate);
  delay(1000);
  print_to_console("Serial initialised");
  delay(1000);

  pinMode(13, OUTPUT); // Initialize LED port
  pinMode(9, INPUT);
  pinMode(7, INPUT_PULLUP);
  blinky();
  digitalWrite(13, LOW);

  pinMode(6, OUTPUT);      //Enable power to the Murata
  digitalWrite(6, HIGH);
  print_to_console("Murata Powered up");
  delay(1000);
 
  pinMode(5, OUTPUT);   //Disable reset pin
  digitalWrite(5, HIGH);
  delay(1000);
  read_data_from_LoRa_Mod();
  delay(1000);

  /***
  send_LoRa_Command("AT+VER?");   //Firmware Version
  delay(500);
  read_data_from_LoRa_Mod();
  ***/
  send_LoRa_Command("AT+MODE=1"); //Begin configuring LoRaWAN Parameters
  delay(500);
  read_data_from_LoRa_Mod();

  send_LoRa_Command("AT+DEVEUI=" + set_deveui);
  delay(250);
  read_data_from_LoRa_Mod();

  send_LoRa_Command("AT+APPKEY=" + set_appkey);
  delay(250);
  read_data_from_LoRa_Mod();

  send_LoRa_Command("AT+APPEUI=" + set_appeui);
  delay(250);
  read_data_from_LoRa_Mod();

  send_LoRa_Command("AT+DFORMAT=1");//Message formatting  
  delay(500);
  read_data_from_LoRa_Mod();

  send_LoRa_Command("AT+BAND=8");   //Set band to US915
  delay(500);
  read_data_from_LoRa_Mod();
  
  digitalWrite(13, HIGH);
}

void mQjoin(){
  send_LoRa_Command("AT+JOIN");   //Join network
  delay(10000);
  read_data_from_LoRa_Mod();
  delay(1000);
}

void mQsend(int pSize, String rawdata){
  send_LoRa_Command("AT+UTX " + String(pSize));
  send_LoRa_Command(rawdata);
  blinky();
}

//Temperature Sensor
float sparkTemp(int tempSensorPin)
{
    const int B = 4275;               // B value of the thermistor
    const int R0 = 100000;            // R0 = 100k
    int a = 0;

    a = analogRead(tempSensorPin);
    float R = 1023.0/a-1.0;
    R = R0*R;
    float temp = 1.0/(log(R/R0)/B+1/298.15)-273.15; // convert to temperature via datasheet

   return temp;
}

//Sound Sensor
long sparkSound(int soundSensorPin)
{
  long sum = 0;
    for(int i=0; i<32; i++){
        sum += analogRead(soundSensorPin);
    }
    sum >>= 5;
    return sum;
}


//Distance Sensor
Ultrasonic ultrasonic(A0);

long sparkUltrasonic(int ultrasonicSensorPin)
{

  long RangeInCentimeters;
  RangeInCentimeters = ultrasonic.MeasureInCentimeters();
  delay(150);

  return RangeInCentimeters;
}
