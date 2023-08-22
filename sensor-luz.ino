// Librerias que se implementaron para la ESP8266 y MQTT
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Credenciales para la conexion con la red wifi y para que se concectara al Brokret
const char* ssid = "George";
const char* password = "zsns6298";
const char* mqtt_server = "192.168.235.43";
// const char* mqtt_server = "192.168.12.29";
const int mqtt_port = 1883;

// Inicializar las instancias deacuerdo alas librerias que declaramos
WiFiClient espClient;
PubSubClient client(espClient);

// Creamos una variable con el pin de Datos
const int analogLightPin = A0; // Pin A0 para el sensor de luz KY-018

// Inicializamos la conexion a internet de la ESP8266
void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }

  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  // Validamos que este conectada a internet
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Medir intensidad de luz
  int rawValue = analogRead(analogLightPin);
  float lightIntensity = 100.0 - ((rawValue / 1023.0) * 100.0);

  // Enviar datos por MQTT
  char intensityStr[6];
  dtostrf(lightIntensity, 4, 2, intensityStr);
  client.publish("sensor/intensidad_luz", intensityStr);

  Serial.printf("Intensidad de Luz: %.2f%%\n", lightIntensity);


  delay(1000); // Espera 1 segundo antes de enviar el próximo dato
}

// Funcion que nos permite la conexion a MQTT una vez que se le haya conecatado la red a la ESP
void reconnect() {
  while (!client.connected()) {
    Serial.println("Conectando al servidor MQTT...");
    if (client.connect("ESP8266Client")) {
      Serial.println("Conectado!");
      // Puedes suscribirte a temas aquí si es necesario
    } else {
      Serial.print("Fallo, rc=");
      Serial.print(client.state());
      Serial.println(" Intentando de nuevo en 5 segundos...");
      delay(5000);
    }
  }
}
