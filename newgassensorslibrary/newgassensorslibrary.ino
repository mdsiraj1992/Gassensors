#include "Gassensors.h"

#define         MQ2PIN                       (0)   //define which analog input channel you are going to use
//#define         MQ3PIN                       (1)
#define         MQ4PIN                       (4)
//#define         MQ5PIN                       (3)
//#define         MQ6PIN                       (3)
//#define         MQ7PIN                       (5)
//#define         MQ8PIN                       (0)
//#define         MQ9PIN                       (1)
#define         MQ135PIN                     (2)

/*//#define         Gassensor_type2                 2   //define which sensor you are going to use
//#define         Gassensor_type3                3   //a mazimum of 6 sensors can be used at a time
//#define         Gassensor_type4                4
//#define         Gassensor_type5               5
//#define         Gassensor_type6               6
//#define         Gassensor_type7               7
//#define         Gassensor_type8               8
//#define         Gassensor_type9               9
//#define         Gassensor_type135               35*/

//#define             Gas_Name                   GAS_HYDROGEN                  
//#define           Gas_Name                   GAS_LPG                      
//#define           Gas_Name                   GAS_METHANE                  
#define           Gas_Name                   GAS_CARBON_MONOXIDE          
//#define           Gas_Name                   GAS_ALCOHOL                  
//#define           Gas_Name                   GAS_SMOKE                    
//#define           Gas_Name                   GAS_PROPANE         

int Gassensor_type[] = {2,3,4,5,6,7,8,9,135};
/*int mq2gases[] = {0,1,2,3,4,5,6};
//int mq3gases[] = {4,7,2,8,1,3};
int mq4gases[] = {1,2,0,3,4,5};
//int mq5gases[] = {0,1,2,3,4};
//int mq6gases[] = {1,0,2,3,4};
//int mq7gases[] = {3,0,1,2,4};
//int mq8gases[] = {0,4,3,2};
//int mq9gases[] = {1,3,2};
//int mq135gases[] = {9,3,10,11,12,13};
//int mq135gases[] = {91,3,101,121,12,143};*/
float               Ro = 0;                    //Ro is initialized to 0 kilo ohms

//Gassensors gs2(MQ2PIN,Gassensor_type[0], Gas_Name);
//Gassensors gs3(MQ3PIN,Gassensor_type[1], Gas_Name);
Gassensors gs4(MQ4PIN,Gassensor_type[2], Gas_Name);
//Gassensors gs5(MQ5PIN,Gassensor_type[3], Gas_Name);
//Gassensors gs6(MQ6PIN,Gassensor_type[4], Gas_Name);
//Gassensors gs7(MQ7PIN,Gassensor_type[5], Gas_Name);
//Gassensors gs8(MQ8PIN,Gassensor_type[6], Gas_Name);
//Gassensors gs9(MQ9PIN,Gassensor_type[7], Gas_Name);
//Gassensors gs135(MQ135PIN,Gassensor_type[8], Gas_Name);

void setup() {
  Serial.begin(9600);                               //UART setup, baudrate = 9600bps
 /* Serial.print("Calibrating...\n");
  Ro = gs2.MQCalibration(MQ2PIN);                       //Calibrating the sensor. Please make sure the sensor is in clean air
                                                     //when you perform the calibration
  Serial.print("Calibration is done...\n");
  Serial.print("Ro2=");
  Serial.print(Ro);
  Serial.print("kohm");
  Serial.print("\n");
    Serial.print("Calibrating...\n");
  Ro = gs4.MQCalibration(MQ4PIN);                       //Calibrating the sensor. Please make sure the sensor is in clean air
                                                     //when you perform the calibration
  Serial.print("Calibration is done...\n");
  Serial.print("Ro4=");
  Serial.print(Ro);
  Serial.print("kohm");
  Serial.print("\n");*/
  Serial.print("Calibrating...\n");
//  Ro = gs135.MQCalibration(MQ135PIN);                       //Calibrating the sensor. Please make sure the sensor is in clean air
                                                     //when you perform the calibration
  Serial.print("Calibration is done...\n");
  Serial.print("Ro135=");
  Serial.print(Ro);
  Serial.print("kohm");
  Serial.print("\n");

}

void loop() {
  /* Serial.print("adc reading pin4: ");
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
// Serial.print(Gas_Name);
// delay(5000);

// gs2.printallgases(Gassensor_type[0]);
  delay(200);
  gs4.printallgases(Gassensor_type[2]);
  delay(200);
//  gs135.printallgases(Gassensor_type[8]);
  delay(200);
}
