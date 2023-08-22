#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "George";
const char* password = "zsns6298";
const char* mqtt_server = "192.168.235.43";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

const int analogPin = A0; // Pin A0 para el sensor de Gas

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
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Leer el valor del sensor de gas
  int gasValue = analogRead(analogPin);

  // Enviar datos por MQTT
  char gasValueStr[6];
  sprintf(gasValueStr, "%d", gasValue);
  client.publish("sensor/gas", gasValueStr);

  Serial.printf("Nivel de gas: %d\n", gasValue);

  delay(1000); // Espera 1 segundo antes de enviar el próximo dato
}

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
