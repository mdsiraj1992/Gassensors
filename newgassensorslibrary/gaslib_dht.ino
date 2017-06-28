#include "Gassensors.h"
#include "DHT.h"

#define         DHTPIN                       (48)
#define         MQ2PIN                       (2)   //define which analog input channel you are going to use
#define         MQ3PIN                       (3)
#define         MQ4PIN                       (4)
#define         MQ5PIN                       (5)
#define         MQ6PIN                       (6)
#define         MQ7PIN                       (7)
#define         MQ8PIN                       (8)
#define         MQ9PIN                       (9)
#define         MQ135PIN                     (13)

#define         DHTTYPE                      DHT22   // DHT 22  (AM2302)    
int Gassensor_type[] = {MQ2,MQ3,MQ4,MQ5,MQ6,MQ7,MQ8,MQ9,MQ135};
float               Ro = 0, Pm25 = 0, Pm10 = 0;                    //Ro is initialized to 0 kilo ohms

DHT dht(DHTPIN, DHTTYPE);
Gassensors gs2(MQ2PIN,Gassensor_type[0]);
Gassensors gs3(MQ3PIN,Gassensor_type[1]);
Gassensors gs4(MQ4PIN,Gassensor_type[2]);
Gassensors gs5(MQ5PIN,Gassensor_type[3]);
Gassensors gs6(MQ6PIN,Gassensor_type[4]);
Gassensors gs7(MQ7PIN,Gassensor_type[5]);
Gassensors gs8(MQ8PIN,Gassensor_type[6]);
Gassensors gs9(MQ9PIN,Gassensor_type[7]);
Gassensors gs135(MQ135PIN,Gassensor_type[8]);

void setup() {
  Serial.begin(9600);                                   //UART setup, baudrate = 9600bps
  dht.begin();
}

void loop() {
 /* /*  //Serial.println(analogRead(MQ135PIN));
/*Serial.print("mq values");
  Serial.println(Gassensor_type[0]);
  Serial.println(Gassensor_type[1]);
  Serial.println(Gassensor_type[2]);
  Serial.println(Gassensor_type[3]);
   Serial.print("adc reading pin4: ");
  Serial.print(gs4.MQRead(MQ4PIN));
    delay(500);
  //Serial.print(Ro);
  
       Serial.print("rs/ro reading pin4: ");
       //gs4.rs_ro_ratio(MQ4PIN);
  Serial.print(gs4.rs_ro_ratio(MQ4PIN));
   //Serial.print("printed value: ");
    delay(500);
  //Serial.print(Ro);
  
   Serial.print("       adc reading pin2: ");
  Serial.print(gs2.MQRead(MQ2PIN)); 
  delay(500);
  //Serial.print(Ro);


   Serial.print("       rs/ro reading pin2: ");
  Serial.println(gs2.rs_ro_ratio(MQ2PIN)); 
  delay(500);
  //Serial.print(Ro);*/
//Serial.print(Gas_Name);
//delay(5000);

/****************** DHT22 Temperature sensor code ****************************************/

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  float hi = dht.computeHeatIndex(f, h);
  Serial.println(F("DHT22 sensor output "));
  Serial.print(F("Humidity:")); 
  Serial.print(h);
  Serial.print(F(" %\t"));
  Serial.print(F("  Temperature(Deg):")); 
  Serial.print(t);
  Serial.println(F(" *C\t "));

/****************** SDS011 Dust sensor code ****************************************/

  PM_CAL();
  Serial.println(F("SDS011 sensor output "));
  Serial.print(F("PM25:"));
  Serial.print(Pm25);
  Serial.print(F(" ug/m3 "));
  Serial.print(F(" PM10:"));
  Serial.print(Pm10);
  Serial.println(F(" ug/m3 "));
  
/****************** MQ Gas sensors code ****************************************/

 gs2.printallgases(Gassensor_type[0]);
  //delay(200);
  gs3.printallgases(Gassensor_type[1]);
  //delay(200);
  gs4.printallgases(Gassensor_type[2]);
  //delay(200);
  gs5.printallgases(Gassensor_type[3]);
  //delay(200);
  gs6.printallgases(Gassensor_type[4]);
  //delay(200);
  gs7.printallgases(Gassensor_type[5]);
  //delay(200);
  gs8.printallgases(Gassensor_type[6]);
  //delay(200);
  /*gs135.printallgases(Gassensor_type[8]);
  //delay(200);*/
}

void PM_CAL()
{
  uint8_t mData = 0, i = 0,  mCheck = 0;
  float mPkt[10] = {0};
  
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

            Pm25 = (mPkt[2] + (mPkt[3]*256))/10;
            Pm10 = (mPkt[4] + (mPkt[5]*256))/10;
              
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
