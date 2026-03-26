const int pinLDR = 2; 

void setup() {
  // Inicialitzem la comunicació sèrie a 115200 baudios
  Serial.begin(115200);
  delay(1000);
  Serial.println("Llegint dades del sensor LDR...");
}

void loop() {
  // Llegim el valor analògic (de 0 a 4095)
  int valor = analogRead(pinLDR);

  // Mostrem el valor pel Monitor Sèrie
  Serial.print("Llum detectada: ");
  Serial.println(valor);

  // Esperem 500ms per no col·lapsar la pantalla
  delay(500);
}
