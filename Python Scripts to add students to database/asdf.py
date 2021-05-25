import serial
locations=['com0','com1','com2', 'com3', 'com4', 'com5', 'com6', 'com7', 'com8', 'com9', 'com10', 'com11', 'com12', 'com13', 'com14', 'com15', 'com16', 'com17', 'com18', 'com19', 'com20', 'com21', 'end']
for device in locations:
    try:
        serialport=serial.Serial(device,9600,timeout=0)
        break
    except:
        if device=='end':
            print ("unable to find serial port")
            exit()

