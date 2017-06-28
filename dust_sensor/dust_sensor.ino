unsigned int Pm25 = 0;
unsigned int Pm10 = 0;
void setup() {
  // put your setup code here, to run once:
    Pm25=0;
    Pm10=0;
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
PM_CAL();
Serial.print("PM25:");
  Serial.println(Pm25);
  Serial.print("PM10:");
  Serial.println(Pm10);
  delay(1000);
}

void PM_CAL()
{
  uint8_t mData = 0;
  uint8_t i = 0;
  uint8_t mPkt[10] = {0};
  uint8_t mCheck = 0;
 while (Serial.available() > 0) 
  {  
    // from www.inovafitness.com
    // packet format: AA C0 PM25_Low PM25_High PM10_Low PM10_High 0 0 CRC AB
     mData = Serial.read();     delay(2);//wait until packet is received
    if(mData == 0xAA)//head1 ok
     {
        mPkt[0] =  mData;
        mData = Serial.read();
        if(mData == 0xc0)//head2 ok
        {
          mPkt[1] =  mData;
          mCheck = 0;
          for(i=0;i < 6;i++)//data recv and crc calc
          {
             mPkt[i+2] = Serial.read();
             delay(2);
             mCheck += mPkt[i+2];
          }
          mPkt[8] = Serial.read();
          delay(1);
    mPkt[9] = Serial.read();
          if(mCheck == mPkt[8])//crc ok
          {
            Serial.flush();
            //Serial.write(mPkt,10);
            
            Pm25 = ((uint16_t)mPkt[2] + (uint16_t)(mPkt[3]*256))/10;
            Pm10 = ((uint16_t)mPkt[4] + (uint16_t)(mPkt[5]*256))/10;

            //Pm25 = (uint16_t)mPkt[2] | (uint16_t)(mPkt[3]<<8);
            //Pm10 = (uint16_t)mPkt[4] | (uint16_t)(mPkt[5]<<8);
            
            if(Pm25 > 999)
             Pm25 = 999;
            if(Pm10 > 999)
             Pm10 = 999;            
            //get one good packet
             return;
          }
        }      
     }
   } 
}
