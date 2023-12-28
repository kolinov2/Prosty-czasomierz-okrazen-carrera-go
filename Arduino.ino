const int trigPin = 9;    // Pin Trig do sensora ultradźwiękowego
const int echoPin = 10;   // Pin Echo do sensora ultradźwiękowego
unsigned long previousMillis = 0;  // Zmienna przechowująca czas poprzedniego wykrycia
const long interval = 1000;  // Interwał pomiaru w milisekundach (tutaj 1000ms = 1s)

void setup() {
  Serial.begin(9600);  // Inicjalizacja komunikacji szeregowej

  pinMode(trigPin, OUTPUT);  // Ustawienie pinu Trig jako wyjście
  pinMode(echoPin, INPUT);   // Ustawienie pinu Echo jako wejście
}

void loop() {
  unsigned long currentMillis = millis();  // Pobranie aktualnego czasu

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH);  // Odczyt czasu trwania impulsu z pinu Echo
  float distance = ((float)duration * 0.034) / 2.0;  // Konwersja czasu na odległość w cm z dokładnością do 2 miejsc po przecinku

  if (distance >= 0 && distance <= 7) {  // Jeśli wykryto ruch w obrębie 0-7 cm
    unsigned long timeElapsed = (currentMillis - previousMillis) / 1000;  // Czas w sekundach
    if (timeElapsed > 0) {
      Serial.print("Czas od ostatniego wykrycia: ");
      Serial.print(distance, 2);  // Wyświetlenie odległości z dokładnością do 2 miejsc po przecinku
      Serial.println("s");
      delay(1000);
    }
    previousMillis = currentMillis;  // Zapisanie aktualnego czasu jako poprzedni
  } else {
    Serial.println("Oczekiwanie na ruch...");
  }

  // Opóźnienie między pomiarami
  while (millis() - currentMillis < interval) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    unsigned long newDuration = pulseIn(echoPin, HIGH);  // Odczyt z sensora w trakcie oczekiwania
    float newDistance = ((float)newDuration * 0.034) / 2.0;  // Konwersja czasu na odległość w cm z dokładnością do 2 miejsc po przecinku

    if (newDistance >= 0 && newDistance <= 7) {
      break;  // Jeśli wykryto ruch, przerwij oczekiwanie
    }
  }
}
