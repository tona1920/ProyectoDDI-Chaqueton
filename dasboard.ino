#include <TFT_eSPI.h>
#include <SPI.h>
#include <WiFi.h>
#include <time.h>
#include <PubSubClient.h>

#define TFT_GREY 0x5AEB
TFT_eSPI tft = TFT_eSPI();

#define LOOP_PERIOD 35 // Display updates every 35 ms

float ltx = 0;    // Saved x coord of bottom of needle
uint16_t osx = 120, osy = 120; // Saved x & y coords
uint32_t updateTime = 0;       // time for next update

int old_analog =  -999; // Value last displayed
int old_digital = -999; // Value last displayed

int value[6] = {0, 0, 0, 0, 0, 0};
int old_value[6] = { -1, -1, -1, -1, -1, -1};
int d = 0;

//Configuracion de la red
const char* ssid = "George";
const char* password = "zsns6298";
//Configuracion de MQTT
const char* mqtt_server = "192.168.235.43";
const char* mqtt_topic = "sensor/temperatura";
const char* mqtt_topic2 = "sensor/cardio";

WiFiClient espClient;
PubSubClient client(espClient);

uint32_t targetTime = 0;
bool showCode = true;

static uint8_t conv2d(const char* p);
uint8_t hh = conv2d(__TIME__), mm = conv2d(__TIME__ + 3), ss = conv2d(__TIME__ + 6);
byte omm = 99, oss = 99;
byte xcolon = 0, xsecs = 0;
unsigned int colour = 0;

void setup() {
  Serial.begin(115200);
   tft.init(); tft.setRotation(3); tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1); tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  
  setupWiFi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

void loop() {
    if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  if (targetTime < millis()) {
    targetTime = millis() + 1000;
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
      hh = timeinfo.tm_hour; mm = timeinfo.tm_min; ss = timeinfo.tm_sec;
      int xpos = 20, ypos = 160, ysecs = ypos + 14;
      if (omm != mm) {
        omm = mm; xpos += tft.drawNumber(hh, xpos, ypos, 6);
        xcolon = xpos; xpos += tft.drawChar(':', xpos, ypos - 8, 6);
        xpos += tft.drawNumber(mm, xpos, ypos, 6); xsecs = xpos;
      }
      if (oss != ss) {
        oss = ss; xpos = xsecs;
        if (ss % 2) { tft.setTextColor(0x39C4, TFT_BLACK);
          xpos += tft.drawChar(':', xcolon, ypos - 8, 6);
          xpos += tft.drawChar(':', xsecs, ysecs, 4);
          tft.setTextColor(TFT_YELLOW, TFT_BLACK);
        } else {
          xpos += tft.drawChar(':', xcolon, ypos - 8, 6);
          xpos += tft.drawChar(':', xsecs, ysecs, 4);
        }
        if (ss < 10) xpos += tft.drawChar('0', xpos, ysecs, 4);
        tft.drawNumber(ss, xpos, ysecs, 4);
      }
    }
  }

}

void setupWiFi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a WiFi");
  configTime(-6 * 3600, 0, "pool.ntp.org");
  targetTime = millis() + 1000;
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.println("Conectando a MQTT...");
    if (client.connect("ESP32Client"))
    {
      Serial.println("Conectado a MQTT");
      client.subscribe(mqtt_topic);
      client.subscribe(mqtt_topic2);
    }
    else
    {
      Serial.print("Fallo en la conexion, rc=");
      Serial.println(client.state());
      delay(2000);
    }
  }
}
void callback(char *topic, byte *payload, unsigned int length) {
  // Convierte el payload a una cadena
  char payloadStr[length + 1];
  memcpy(payloadStr, payload, length);
  payloadStr[length] = '\0';

  // Convierte el payload a un entero
  int valorMQTT = atoi(payloadStr);

  // Verifica el tópico MQTT
  if (strcmp(topic, mqtt_topic) == 0) {
    // Llama a la función para actualizar la pantalla digital para topic1
    updateAnalogMeter(valorMQTT);
  } else if (strcmp(topic, mqtt_topic2) == 0) {
    // Llama a la función para actualizar la pantalla digital para topic2}
    byte d = 50;
    plotLinear("IPM", 5 * d, 60,valorMQTT);
  }
}

void updateAnalogMeter(int value)
{
  // Meter outline
  tft.fillRect(0, 0, 239, 126, TFT_GREY);
  tft.fillRect(5, 3, 230, 119, TFT_WHITE);

  tft.setTextColor(TFT_BLACK);  // Text colour

  // Draw ticks every 5 degrees from -50 to +50 degrees (100 deg. FSD swing)
  for (int i = -50; i < 51; i += 5) {
    // Long scale tick length
    int tl = 15;

    // Coodinates of tick to draw
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (100 + tl) + 120;
    uint16_t y0 = sy * (100 + tl) + 140;
    uint16_t x1 = sx * 100 + 120;
    uint16_t y1 = sy * 100 + 140;

    // Coordinates of next tick for zone fill
    float sx2 = cos((i + 5 - 90) * 0.0174532925);
    float sy2 = sin((i + 5 - 90) * 0.0174532925);
    int x2 = sx2 * (100 + tl) + 120;
    int y2 = sy2 * (100 + tl) + 140;
    int x3 = sx2 * 100 + 120;
    int y3 = sy2 * 100 + 140;

    // Green zone limits
    if (i >= -50 && i < 0) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_GREEN);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREEN);
    }

    // Yellow zone limits
    if (i >= -25 && i < 0) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_YELLOW);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_YELLOW);
    }

    // Orange zone limits
    if (i >= 0 && i < 25) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_ORANGE);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_ORANGE);
    }

    // Orange zone limits
    if (i >= 25 && i < 50) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_RED);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_RED);
    }
    
    // Short scale tick length
    if (i % 25 != 0) tl = 8;

    // Recalculate coords incase tick lenght changed
    x0 = sx * (100 + tl) + 120;
    y0 = sy * (100 + tl) + 140;
    x1 = sx * 100 + 120;
    y1 = sy * 100 + 140;

    // Draw tick
    tft.drawLine(x0, y0, x1, y1, TFT_BLACK);

    // Check if labels should be drawn, with position tweaks
    if (i % 25 == 0) {
      // Calculate label positions
      x0 = sx * (100 + tl + 10) + 120;
      y0 = sy * (100 + tl + 10) + 140;
      switch (i / 25) {
        case -2: tft.drawCentreString("0", x0, y0 - 12, 2); break;
        case -1: tft.drawCentreString("25", x0, y0 - 9, 2); break;
        case 0: tft.drawCentreString("50", x0, y0 - 6, 2); break;
        case 1: tft.drawCentreString("75", x0, y0 - 9, 2); break;
        case 2: tft.drawCentreString("100", x0, y0 - 12, 2); break;
      }
    }

    // Now draw the arc of the scale
    sx = cos((i + 5 - 90) * 0.0174532925);
    sy = sin((i + 5 - 90) * 0.0174532925);
    x0 = sx * 100 + 120;
    y0 = sy * 100 + 140;
    // Draw scale arc, don't draw the last part
    if (i < 50) tft.drawLine(x0, y0, x1, y1, TFT_BLACK);
  }

  tft.drawString("Temperatura", 5 + 230 - 100, 119 - 20, 2); // Units at bottom right
  if(value > 100){
    value = value/10;
  }
  char buf[8]; dtostrf(value, 4, 0, buf);
  tft.drawCentreString(strcat(buf, "%"), 120, 70, 4); // Comment out to avoid font 4
  tft.drawRect(5, 3, 230, 119, TFT_BLACK); // Draw bezel line
  
  plotNeedle(value, 0); // Put meter needle at 0
  
}

void plotNeedle(int value, byte ms_delay)
{
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  char buf[8]; dtostrf(value, 4, 0, buf);
  tft.drawRightString(buf, 40, 119 - 20, 2);

  if (value < -10) value = -10; // Limit value to emulate needle end stops
  if (value > 110) value = 110;

  // Move the needle util new value reached
  while (!(value == old_analog)) {

    if (ms_delay == 0) old_analog = value; // Update immediately id delay is 0

    float sdeg = map(old_analog, -10, 110, -150, -30); // Map value to angle
    // Calcualte tip of needle coords
    float sx = cos(sdeg * 0.0174532925);
    float sy = sin(sdeg * 0.0174532925);

    // Calculate x delta of needle start (does not start at pivot point)
    float tx = tan((sdeg + 90) * 0.0174532925);

    // Erase old needle image
    tft.drawLine(120 + 20 * ltx - 1, 140 - 20, osx - 1, osy, TFT_WHITE);
    tft.drawLine(120 + 20 * ltx, 140 - 20, osx, osy, TFT_WHITE);
    tft.drawLine(120 + 20 * ltx + 1, 140 - 20, osx + 1, osy, TFT_WHITE);

    // Re-plot text under needle
    tft.setTextColor(TFT_BLACK);
    tft.drawCentreString("", 120, 70, 4); // // Comment out to avoid font 4

    // Store new needle end coords for next erase
    ltx = tx;
    osx = sx * 98 + 120;
    osy = sy * 98 + 140;

    // Draw the needle in the new postion, magenta makes needle a bit bolder
    // draws 3 lines to thicken needle
    tft.drawLine(120 + 20 * ltx - 1, 140 - 20, osx - 1, osy, TFT_RED);
    tft.drawLine(120 + 20 * ltx, 140 - 20, osx, osy, TFT_MAGENTA);
    tft.drawLine(120 + 20 * ltx + 1, 140 - 20, osx + 1, osy, TFT_RED);

    // Slow needle down slightly as it approaches new postion
    if (abs(old_analog - value) < 10) ms_delay += ms_delay / 5;

    // Wait before next update
    delay(ms_delay);
  }
}

void plotLinear(char *label, int x, int y, int valueM)
{
  int w = 36;
  tft.drawRect(x, y, w, 155, TFT_GREY);
  tft.fillRect(x + 2, y + 19, w - 3, 155 - 38, TFT_WHITE);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.drawCentreString(label, x + w / 2, y + 2, 2);

  for (int i = 0; i < 110; i += 10)
  {
    tft.drawFastHLine(x + 20, y + 27 + i, 6, TFT_BLACK);
  }

  for (int i = 0; i < 110; i += 50)
  {
    tft.drawFastHLine(x + 20, y + 27 + i, 9, TFT_BLACK);
  }



  tft.drawCentreString("---", x + w / 2, y + 155 - 18, 2);
  //Serial.println(valueM);
  plotPointer(valueM);
}

// #########################################################################
//  Adjust  linear meter pointer positions
// #########################################################################
void plotPointer(int valorM)
{
  int dy = 187;
  byte pw = 16;

  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  // Move the 6 pointers one pixel towards new value
  for (int i = 0; i < 1; i++)
  {
    Serial.println( i);
    char buf[8]; dtostrf(valorM, 4, 0, buf);
    tft.drawRightString(buf, 240 + 36 - 5, 87 - 27 + 155 - 18, 2);

    int dx = 3 + 50 * 5;
    if (valorM < 0) valorM = 0; // Limit value to emulate needle end stops
    if (valorM > 100) valorM = 100;

    while (!(valorM == old_value[i])) {
      dy = 67 + 100 - old_value[i];
      if (old_value[i] > valorM)
      {
        tft.drawLine(dx, dy - 5, dx + pw, dy, TFT_WHITE);
        old_value[i]--;
        tft.drawLine(dx, dy + 6, dx + pw, dy + 1, TFT_RED);
      }
      else
      {
        tft.drawLine(dx, dy + 5, dx + pw, dy, TFT_WHITE);
        old_value[i]++;
        tft.drawLine(dx, dy - 6, dx + pw, dy - 1, TFT_RED);
      }
    }
  }
}


static uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9') v = *p - '0';
  return 10 * v + *++p - '0';
}
