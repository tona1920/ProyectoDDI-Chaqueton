from machine import Pin
from time import sleep
from hcsr04 import HCSR04
import machine
import time
from umqtt.simple import MQTTClient
import network

#HAcemos las configuraciones de MQTT
MQTT_BROKER = "192.168.235.43"
MQTT_USER = ""
MQTT_PASSWORD = ""
MQTT_CLIENT_ID = ""
MQTT_PORT = 1883

# Configuración del sensor de ultrasonido HC-SR04
pir_pin = Pin(2, Pin.IN)
sensor = HCSR04(trigger_pin=4, echo_pin=5)

# Configuración del sensor de pulso
ppg_pin = machine.Pin(13, machine.Pin.IN)

# Pin donde está conectado el sensor LM35
lm35_pin = machine.ADC(machine.Pin(34))

# #Funcion para conectar a la Red Wifi
def wifi_connect():
    print ("Conectando...", end = "")

    sta_if = network.WLAN(network.STA_IF)
    sta_if.active(True)
    sta_if.connect('George','zsns6298')

    while not sta_if.isconnected():
        print(".", end="")
        sleep(0.3)
    print("Wifi Conectado!")

# Funcion de Publicador de MQTT
def publish (topico, estado):
    client = MQTTClient(MQTT_CLIENT_ID, MQTT_BROKER, port=MQTT_PORT, user=MQTT_USER, password=MQTT_PASSWORD, keepalive=30)
    client.connect()
    print("[OK]")
    client.publish(topico, str(estado))
    print("Publicando estado: ", estado,"   ",topico)

  
wifi_connect()


#Funcion para calcular el ritmo cardiaco
def calcular_pulso(ppg_values):
    return sum(ppg_values)

# Función de detección de movimiento
def deteccion_movimiento():
    distancia = sensor.distance_cm()
    if pir_pin.value() == 1:
        if 1 < distancia <= 150:
            #print("¡Movimiento detectado a {:.2f} cm!".format(distancia))
            return distancia;
    else:
        #print("Sin Movimiento")
        return ;


def read_lm35_temperature():
    # Lee el valor analógico del sensor LM35
    raw_value = lm35_pin.read()
    # Convierte el valor analógico a temperatura en grados Celsius
    temperature_c = (raw_value / 4095) * 330.0
    return temperature_c

try:
    while True:
        #Verifica el movimiento
        movimiento = deteccion_movimiento();
        #print(deteccion_movimiento())
        if(movimiento):
            publish("sensor/ultrasonico",movimiento)
        
        sleep(1)
        
        ppg_values = []

        # Lee valores PPG durante un período de tiempo
        start_time = time.ticks_ms()
        while time.ticks_diff(time.ticks_ms(), start_time) < 3000:  # Lee durante 3 segundos
            ppg_values.append(ppg_pin.value())
            time.sleep_ms(5)  # Frecuencia de muestreo de 200 Hz

        # Calcula el pulso a partir de los valores PPG
        pulso = calcular_pulso(ppg_values)
        if 50 < pulso < 150:
            print("Pulso: {}".format(pulso))
            publish("sensor/cardio",pulso)
        sleep(1)
        
        #Lee valores de la temperatura
        temperature = read_lm35_temperature()
        if (temperature > 35 and temperature < 39):
            publish("sensor/temperatura",temperature)
            print("Temperatura: {:.2f} °C".format(temperature))
        sleep(1)

        
except KeyboardInterrupt:
    pass

