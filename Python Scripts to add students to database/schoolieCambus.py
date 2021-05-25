import serial
import requests
import os

def saveFileinDir(whereToSave):
    savePath='C:\\Users\\SHREEVALLABHA\\Desktop\\'+whereToSave+'\\'
    Dir=os.path.join(savePath)
    if not os.path.exists(Dir):
        os.mkdir(Dir)
    return Dir
        
    

URL="http://vallabh.000webhostapp.com/weather/insert.php?"
comPort=input("Specify the COM-PORT connected to: ")
ser=serial.Serial(comPort.upper())
while ser.is_open:
    print("place the id-card on the rfid scanner")
    rfid=ser.readline()
    rfid=rfid.decode('utf-8')
    if(rfid):
        #print(rfid)
        name=input("enter the name of the student: ")
        usn=input("enter the student USN: ")
        bus_no=input("enter the bus number: ")
        PARAMS={'temp':usn,'hum':rfid}
        request=requests.get(url=URL,params=PARAMS)
        response=request.json()
        isOk=response['success']
        Directory=saveFileinDir(bus_no)
        rfid=rfid.replace(":","")
        os.chdir(Directory)
        print(os.getcwd())
        file=open(usn+".txt","w")
        file.write(rfid)
        #print("successfully saved at this location "+Directory)
        file.close()
        if isOk:
            print("successfully sent to the server")
        
    else:
        print("place the card again")
    

