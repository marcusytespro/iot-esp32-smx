const int pinLM35 = 34; // He puesto el 34 que es el que sale en tu imagen

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Iniciando lectura LM35...");
}

void loop() {
  // Leemos el valor del pin
  int valor = analogRead(pinLM35);

  // Aplicamos la fórmula de tu imagen:
  // Temperatura = (analogRead * 5.0 / 4095) * 100
  // Nota: Si ves que la temperatura es muy alta, cambia el 5.0 por 3.3
  float temperatura = (valor * 5.0 / 4095.0) * 100.0;

  // Mostramos el resultado
  Serial.print("Valor ADC: ");
  Serial.print(valor);
  Serial.print(" -> Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  delay(500);
}
