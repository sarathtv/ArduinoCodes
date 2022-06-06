# Import standard python modules.
import random
import sys
import time
import Adafruit_DHT

 
DHT_SENSOR = Adafruit_DHT.DHT11
DHT_PIN = 4
# Import Adafruit IO MQTT client.
from Adafruit_IO import MQTTClient

# Set to your Adafruit IO key.
# Remember, your key is a secret,
# so make sure not to publish it when you publish this code!
ADAFRUIT_IO_KEY = '19ae9c82ee78444aa4aea146cffe5eae'

# Set to your Adafruit IO username.
# (go to https://accounts.adafruit.com to find your username)
ADAFRUIT_IO_USERNAME = 'tvsarath89'


# Define callback functions which will be called when certain events happen.
def connected(client):
    # Connected function will be called when the client is connected to Adafruit IO.
    # This is a good place to subscribe to feed changes.  The client parameter
    # passed to this function is the Adafruit IO MQTT client so you can make
    # calls against it easily.
    print('Connected to Adafruit IO!  Listening for DemoFeed changes...')
    # Subscribe to changes on a feed named DemoFeed.
    client.subscribe('DemoFeed')

def disconnected(client):
    # Disconnected function will be called when the client disconnects.
    print('Disconnected from Adafruit IO!')
    sys.exit(1)

def message(client, feed_id, payload):
    # Message function will be called when a subscribed feed has a new value.
    # The feed_id parameter identifies the feed, and the payload parameter has
    # the new value.
    print('Feed {0} received new value: {1}'.format(feed_id, payload))


# Create an MQTT client instance.
client = MQTTClient(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

# Setup the callback functions defined above.
client.on_connect    = connected
client.on_disconnect = disconnected
client.on_message    = message

# Connect to the Adafruit IO server.
client.connect()
client.subscribe("slider_rpi")
client.loop_background()
# Now send new values every 10 seconds.
print('Publishing a new message every 10 seconds (press Ctrl-C to quit)...')
while True:
    
    
    humidity, temperature = Adafruit_DHT.read(DHT_SENSOR, DHT_PIN)
    if humidity is not None and temperature is not None:
        print("Temp={0:0.1f}C Humidity={1:0.1f}%".format(temperature, humidity))
        print('Publishing {0} to temperature feed.'.format(temperature))
        client.publish('temperature_rpi', temperature)
    else:
        print("Sensor failure. Check wiring.");
    
    time.sleep(10)
        



