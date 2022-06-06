import thingspeak
import time
import Adafruit_DHT
 
channel_id = 1724961 # PUT CHANNEL ID HERE
write_key  = 'SWZVYWRW1WRV9CQ0' # PUT YOUR WRITE KEY HERE
read_key   = 'YZA0C5U86AI79WB0' # PUT YOUR READ KEY HERE
pin = 4
sensor = Adafruit_DHT.DHT11

def measure(channel):
    try:
        humidity, temperature = Adafruit_DHT.read(sensor, pin)
        # write
        
        response = channel.update({'field1': temperature, 'field2': humidity})
        
        
    except:
        print("connection failed")
 
 
if __name__ == "__main__":
    channel = thingspeak.Channel(id=channel_id, api_key=write_key)
    while True:
        measure(channel)
        # free account has an api limit of 15sec
        time.sleep(15)