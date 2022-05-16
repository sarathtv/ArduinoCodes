from urllib.request import urlopen, Request
import json,time
#import RPi.GPIO as GPIO

#GPIO.setmode(GPIO.BCM)
#GPIO.setup(4, GPIO.OUT)
while True:
    request = Request('https://api.thingspeak.com/talkbacks/45273/commands/execute?api_key=DS4YLUANDDQ0HC9E')
    response = urlopen(request)
    command = response.read()
    command = command.decode()
    command = command
    print(command)
    if command == 'FAN_ON':
        print("light_on")
        #GPIO.output(4,GPIO.HIGH)
    if command == 'FAN_OFF':
        #GPIO.output(4,GPIO.LOW)
        print("light_off")
    time.sleep(5)