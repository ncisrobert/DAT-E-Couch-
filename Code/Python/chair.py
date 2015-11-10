import serial, mosquitto, random
import pygame
"""http://www.hivemq.com/demos/websocket-client/"""
"""port = serial.Serial("/dev/tty.usbmodem1451",9600,timeout=2)"""#mac
port = serial.Serial('/dev/ttyACM0',9600)# pi
#port = serial.Serial("COM6",9600,timeout=2)# put ardunio com number
pygame.mixer.init()

def messageReceived(broker, obj, msg):
        print("Message " + msg.topic + " containing: " + msg.payload)
        if (msg.payload == 'mad') :
            port.write("2")
            pygame.mixer.music.load("mad.ogg")
            pygame.mixer.music.set_volume(1.0) 
            pygame.mixer.music.play()
            pygame.mixer.music.set_volume(1.0)
        elif (msg.payload == 'happy') :
            port.write("3")
            pygame.mixer.music.load("happy.ogg")
            pygame.mixer.music.set_volume(1.0) 
            pygame.mixer.music.play()
            pygame.mixer.music.set_volume(1.0)     
        elif (msg.payload == 'middle') :
            port.write("4")     
            pygame.mixer.music.load("middle.ogg")
            pygame.mixer.music.set_volume(1.0) 
            pygame.mixer.music.play()
             

#   Create a client wrapper
client = mosquitto.Mosquitto()

#    Connect to the broker (in this case the local one)
client.connect("broker.i-dat.org", 80)

client.subscribe("vibration")
client.on_message = messageReceived


while (client != None): client.loop()




while True:
    command = raw_input("insert command: ")
    if (command == '1') :
        port.write("1")
    
    elif (command == '0') :
        port.write("0")
