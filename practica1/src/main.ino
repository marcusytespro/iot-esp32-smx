// Definir el pin LED
const int LED_PIN = 17;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // LED apagado inicialmente

  Serial.begin(115200);

  delay(1000);
  Serial.println("Sistema listo. Escribe ON u OFF para controlar el LED");
}

void loop() {
  if (Serial.available()) {
    String linea = Serial.readStringUntil('\n');
    linea.trim();

    Serial.print("Recibido: ");
    Serial.println(linea);

    if (linea.equalsIgnoreCase("ON")) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ENCENDIDO");
    }
    else if (linea.equalsIgnoreCase("OFF")) {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED APAGADO");
    }
    else if (linea.length() > 0) {
      Serial.println("Comando desconocido");
    }
  }
}
