#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_CCS811.h>

// ===== WIFI =====
const char* ssid = "POCO F7";
const char* password = "12345qwe";

// ===== SENSOR =====
Adafruit_CCS811 ccs;

// ===== SERVIDOR WEB =====
WebServer server(80);

// Variables globales
int eco2 = 0;
int tvoc = 0;
String calidad = "Sin datos";

// ===== PAGINA WEB =====
String paginaHTML() {

  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <meta charset="UTF-8">
    <meta http-equiv="refresh" content="2">
    <title>Calidad del Aire - Aula</title>

    <style>
      body{
        font-family: Arial;
        background:#111;
        color:white;
        text-align:center;
        padding-top:40px;
      }

      .card{
        background:#1e1e1e;
        width:350px;
        margin:auto;
        padding:30px;
        border-radius:20px;
        box-shadow:0 0 20px rgba(0,255,150,0.3);
      }

      h1{
        color:#00ff99;
      }

      .dato{
        font-size:28px;
        margin:20px;
      }

      .estado{
        font-size:32px;
        font-weight:bold;
        color:#00ffaa;
      }
    </style>
  </head>

  <body>

    <div class="card">
      <h1>Calidad del Aire en el Aula</h1>

      <div class="dato">
        eCO2: )rawliteral";

  html += eco2;

  html += R"rawliteral( ppm
      </div>

      <div class="dato">
        TVOC: )rawliteral";

  html += tvoc;

  html += R"rawliteral( ppb
      </div>

      <div class="estado">
        )rawliteral";

  html += calidad;

  html += R"rawliteral(
      </div>

    </div>

  </body>
  </html>
  )rawliteral";

  return html;
}

// ===== PAGINA PRINCIPAL =====
void handleRoot() {
  server.send(200, "text/html", paginaHTML());
}

void setup() {

  Serial.begin(115200);

  // ===== I2C =====
  Wire.begin(21, 22);

  // ===== SENSOR =====
  Serial.println("Iniciando CCS811...");

  if (!ccs.begin()) {
    Serial.println(" Error iniciando CCS811");
    while (1);
  }

  // Modo de medición: 1 lectura por segundo
  ccs.setDriveMode(CCS811_DRIVE_MODE_1SEC);

  // Esperar a que el sensor esté listo
  delay(2000);

  Serial.println(" Sensor listo");

  // ===== WIFI =====
  WiFi.begin(ssid, password);

  Serial.print("Conectando al WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println(" WiFi conectado");
  Serial.print("IP del ESP32: ");
  Serial.println(WiFi.localIP());

  // ===== SERVIDOR =====
  server.on("/", handleRoot);

  server.begin();

  Serial.println(" Servidor web iniciado");
}

void loop() {

  // ===== LEER SENSOR =====
  if (ccs.available()) {

    if (!ccs.readData()) {

      eco2 = ccs.geteCO2();
      tvoc = ccs.getTVOC();

      if (eco2 < 800) {
        calidad = "Excelente";
      }
      else if (eco2 < 1200) {
        calidad = "Buena";
      }
      else if (eco2 < 2000) {
        calidad = "Regular";
      }
      else {
        calidad = "Mala";
      }

      // Monitor serie
      Serial.print("eCO2: ");
      Serial.print(eco2);
      Serial.print(" ppm | TVOC: ");
      Serial.print(tvoc);
      Serial.print(" ppb | Calidad (Aula): ");
      Serial.println(calidad);

    } else {
      Serial.println(" Error leyendo sensor");
    }
  }

  // ===== WEB =====
  server.handleClient();

  delay(1000);
}
