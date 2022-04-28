import pyrebase
import serial
import time
ser = serial.Serial('/dev/ttyACM1')
 
# variables
data = ''
sensor = 0.0
name = 'Empty'
temperature = 0.0
days = 0
 
config = {
    'apiKey': 'apiKey',
    'authDomain': 'fridgehound.firebaseapp.com',
    'databaseURL': 'https://fridgehound.firebaseio.com/',
    'storageBucket': 'fridgehound.appspot.com'
}
 
firebase = pyrebase.initialize_app(config)
 
db = firebase.database()
 
print('firebase setup complete')
 
 
print('running main program')
while 0<1:
    ser = serial.Serial('/dev/ttyACM1')
    print('executed1')
    time.sleep(1)
    print('executed2')
 
    data = ser.read(14)
    print('executed3')
    print(data)
    if data == '':
        print('no data was read. trying again')
        continue
    parsedData = data.split()
    foodData = parsedData[0].decode('utf-8')
    sensorData = parsedData[1].decode('utf-8')
    temperatureData = parsedData[2].decode('utf-8')
    daysData = parsedData[3].decode('utf-8')
 
    print('Food: ' + foodData)
    print('Sensor: ' + sensorData)
    print('Temp: ' + temperatureData)
    print('Days: ' + daysData)
 
 
    print(parsedData)
 
    dataToPush = {
        'Food': foodData,
        'Sensor': sensorData,
        'Temperature': temperatureData,
        'Days': daysData
    }
 
    db.child('foods').set(dataToPush)