import serial
import pymysql
from time import localtime, strftime
T=serial.Serial('COM11',9600)

def timeAverage():
    time=strftime("%Y-%m-%d %H:%M:%S", localtime())

    temp=T.readline()
    print(temp)
    temp=temp[:-2]
    print(temp)
    if(temp != b'1'):
        return(time, 0)
    temp=eval(temp)
    print(temp)

    return(time, temp)

while True:
    data = timeAverage()
    fTime = data[0]
    fTemp = "%.1f\n" % data[1]

    
    db = pymysql.connect(host='localhost', user='root', passwd='swordart1',db='bowling')

    with db :
        cur=db.cursor()

        cur.execute("INSERT INTO warn(warn_data,time) VALUES (%s,%s)",(fTemp,fTime))
        db.commit()
