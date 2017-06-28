#define         MQ2                 2
#define         MQ3                 3
#define         MQ4                 4
#define         MQ5                 5
#define         MQ6                 6
#define         MQ7                 7
#define         MQ8                 8
#define         MQ9                 9
#define         MQ135               135

#define         RL_VALUE_MQ2                  1           //define the load resistance connected to the gas sensor on the board, in kilo ohms
#define         RO_CLEAN_AIR_FACTOR_MQ2       9.577       //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO, which is extracted from the graph in datasheet

#define         RL_VALUE_MQ3                  12   
#define         RO_CLEAN_AIR_FACTOR_MQ3       60.314

#define         RL_VALUE_MQ4                  13  
#define         RO_CLEAN_AIR_FACTOR_MQ4       4.434

#define         RL_VALUE_MQ5                  14   
#define         RO_CLEAN_AIR_FACTOR_MQ5       6.455

#define         RL_VALUE_MQ6                  15    
#define         RO_CLEAN_AIR_FACTOR_MQ6       9.94

#define         RL_VALUE_MQ7                  16      
#define         RO_CLEAN_AIR_FACTOR_MQ7       26.09

#define         RL_VALUE_MQ8                  17     
#define         RO_CLEAN_AIR_FACTOR_MQ8       1

#define         RL_VALUE_MQ9                  18      
#define         RO_CLEAN_AIR_FACTOR_MQ9       9.799

#define         RL_VALUE_MQ135                19       
#define         RO_CLEAN_AIR_FACTOR_MQ135     3.59

#define         MQ2PIN                       (2)   //define which analog input channel you are going to use
#define         MQ3PIN                       (3)
#define         MQ4PIN                       (4)
#define         MQ5PIN                       (5)
#define         MQ6PIN                       (6)
#define         MQ7PIN                       (7)
#define         MQ8PIN                       (8)
#define         MQ9PIN                       (9)
#define         MQ135PIN                     (13)

#define         CALIBARAION_SAMPLE_TIMES     (50)    //define how many samples you are going to take in the calibration phase
#define         CALIBRATION_SAMPLE_INTERVAL  (50)     //define the time interal(in milisecond) between each samples in the cablibration phase

float               Ro = 0;                    //Ro is initialized to 0 kilo ohms
float               RL_VALUE, RO_CLEAN_AIR_FACTOR;

void setup() {
  Serial.begin(9600);                                   //UART setup, baudrate = 9600bps
  

  int Ro2 = MQCalibration(MQ2PIN,MQ2);                       //Calibrating the sensor. Please make sure the sensor is in clean air
                                                        //when you perform the calibration
  int Ro3 = MQCalibration(MQ3PIN,MQ3);

  int Ro4 = MQCalibration(MQ4PIN,MQ4);

  int Ro5 = MQCalibration(MQ5PIN,MQ5);

  int Ro6 = MQCalibration(MQ6PIN,MQ6);

  int Ro7 = MQCalibration(MQ7PIN,MQ7);

  int Ro8 = MQCalibration(MQ8PIN,MQ8);
 
  int Ro9 = MQCalibration(MQ9PIN,MQ9);

  int Ro135 = MQCalibration(MQ135PIN,MQ135);
}

void loop() {
  int Ro2 = MQCalibration(MQ2PIN,MQ2);                       //Calibrating the sensor. Please make sure the sensor is in clean air
                                                        //when you perform the calibration
  int Ro3 = MQCalibration(MQ3PIN,MQ3);

  int Ro4 = MQCalibration(MQ4PIN,MQ4);

  int Ro5 = MQCalibration(MQ5PIN,MQ5);

  int Ro6 = MQCalibration(MQ6PIN,MQ6);

  int Ro7 = MQCalibration(MQ7PIN,MQ7);

  int Ro8 = MQCalibration(MQ8PIN,MQ8);
 
  int Ro9 = MQCalibration(MQ9PIN,MQ9);

  int Ro135 = MQCalibration(MQ135PIN,MQ135);
}

  /****************** MQResistanceCalculation ****************************************
  Input:   raw_adc - raw value read from adc, which represents the voltage
  Output:  the calculated sensor resistance
  Remarks: The sensor and the load resistor forms a voltage divider. Given the voltage
         across the load resistor and its resistance, the resistance of the sensor
         could be derived.
************************************************************************************/
float MQResistanceCalculation(int raw_adc)
{
  return ( ((float)RL_VALUE * (1023 - raw_adc) / raw_adc));
  
}

/***************************** MQCalibration ****************************************
  Input:   mq_pin - analog channel
  Output:  Ro of the sensor
  Remarks: This function assumes that the sensor is in clean air. It uses
         MQResistanceCalculation to calculates the sensor resistance in clean air
         and then divides it with RO_CLEAN_AIR_FACTOR. RO_CLEAN_AIR_FACTOR is about
         9.577 for MQ2 sensor and differs slightly between different sensors.
************************************************************************************/
float MQCalibration(int mq_pin, int type)
{
  int i;
  float RS_AIR_val = 0, r0;

 switch (type) {
    case MQ2:
      {
        //mqgases = {0,1,2,3,4,5,6};
        RL_VALUE = RL_VALUE_MQ2;
        RO_CLEAN_AIR_FACTOR = RO_CLEAN_AIR_FACTOR_MQ2;
      }
      break;
    case MQ3:
      { RL_VALUE = RL_VALUE_MQ3;
        RO_CLEAN_AIR_FACTOR = RO_CLEAN_AIR_FACTOR_MQ3;
      }
      break;
    case MQ4:
      { RL_VALUE = RL_VALUE_MQ4;
        RO_CLEAN_AIR_FACTOR = RO_CLEAN_AIR_FACTOR_MQ4;
      }
      break;
    case MQ5:
      { RL_VALUE = RL_VALUE_MQ5;
        RO_CLEAN_AIR_FACTOR = RO_CLEAN_AIR_FACTOR_MQ5;
      }
      break;
    case MQ6:
      { RL_VALUE = RL_VALUE_MQ6;
        RO_CLEAN_AIR_FACTOR = RO_CLEAN_AIR_FACTOR_MQ6;
      }
      break;
    case MQ7:
      { RL_VALUE = RL_VALUE_MQ7;
        RO_CLEAN_AIR_FACTOR = RO_CLEAN_AIR_FACTOR_MQ7;
      }
      break;
    case MQ8:
      { RL_VALUE = RL_VALUE_MQ8;
        RO_CLEAN_AIR_FACTOR = RO_CLEAN_AIR_FACTOR_MQ8;
      }
      break;
    case MQ9:
      { RL_VALUE = RL_VALUE_MQ9;
        RO_CLEAN_AIR_FACTOR = RO_CLEAN_AIR_FACTOR_MQ9;
      }
      break;
    case MQ135:
      { RL_VALUE = RL_VALUE_MQ135;
        RO_CLEAN_AIR_FACTOR = RO_CLEAN_AIR_FACTOR_MQ135;
      }
      break;
      //default:
      //break;
  }
  
  Serial.println("Calibrating MQ sensor...");
  
  for (i = 0; i < CALIBARAION_SAMPLE_TIMES; i++) {              //take multiple samples
    RS_AIR_val += MQResistanceCalculation(analogRead(mq_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  
  RS_AIR_val = RS_AIR_val / CALIBARAION_SAMPLE_TIMES;           //calculate the average value

  r0 = RS_AIR_val / RO_CLEAN_AIR_FACTOR;                        //RS_AIR_val divided by RO_CLEAN_AIR_FACTOR yields the Ro
                                                                //according to the chart in the datasheet
  Serial.println("Calibration is done");
  Serial.print("Ro value for MQ");
  Serial.print(type);
  Serial.print(" sensor is ");  
  Serial.print(r0);
  Serial.println("kohm\n");
  //Serial.print(F("r0 value"));
  //Serial.println(r0);

  return r0;
}

