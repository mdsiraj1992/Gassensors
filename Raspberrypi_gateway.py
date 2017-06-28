import paho.mqtt.client as mqtt 
import serial
import time
import sys
import glob
import serial

#used to extract name of serial port being used for serial communication
#Code for Serial_ports() function is written by Thomas on stackoverfllow.com
def serial_ports():            
    """ Lists serial port names
        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
    """
    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result

def on_connect(client, userdata, flags, rc):
    m="Connected flags"+str(flags)+"result code "\
    +str(rc)+"client1_id  "+str(client)
    print(m)

def on_message(client1, userdata, message):
    print("message received  "  ,str(message.payload.decode("utf-8")))

#declaring an empty list which stores the name of serial ports that are in use for serial  communication
pyserialport = []               
if __name__ == '__main__':
    ports = serial_ports()
    for port in ports:
        if (('USB' in port) ):
            pyserialport.append(port)
        else:
            pass

data=serial.Serial(pyserialport[0],9600)
name=b''

#Function that decides MQTT topic based on sensorname and publishes data to the topic
def Senddata_nodered(sensorname,data):          
    if sensorname != b'':
        subtopic = data.split(b':')[0]
        if sensorname.startswith(b'MQ'):
            mqtttopic = b"Airqualitymonitoring/Gassensors/" + sensorname + b"/" + subtopic
        else:
            mqtttopic = b"Airqualitymonitoring/Othersensors/" + sensorname + b"/" + subtopic
        try:
            print (mqtttopic)
            client1.publish(mqtttopic.decode(),data,2)
        except:
            print ('in except')
        
broker_address="172.16.27.101"
#broker_address="iot.eclipse.org"
client1 = mqtt.Client("P1")    	#create new instance
client1.on_connect= on_connect  	#attach function to callback
client1.on_message=on_message    	#attach function to callback
time.sleep(1)
client1.connect(broker_address)    	#connect to broker
client1.loop_start()    		#start the loop
time.sleep(1)

while 1:
    Arduinodata = data.readline()          #Reads serial data from arduino
    serialdata_split = Arduinodata.strip().split()
    string_start = serialdata_split[0]
    if string_start == b'MQSENSOR':
        name = b'MQ'+serialdata_split[1]
    elif string_start == b'DHT22':
        name = b'DHT22'
    elif string_start == b'SDS011':
        name = b'SDS011'
    elif string_start == b'BMP':
        name = b'BMP'
    print('sensorname',name)    
    if string_start == name or string_start == b'MQSENSOR':
        continue
    else:  
        for value in serialdata_split:
            if b':' in value:
                Senddata_nodered(name,value)
               # time.sleep(0.5)
client1.disconnect()
client1.loop_stop()
