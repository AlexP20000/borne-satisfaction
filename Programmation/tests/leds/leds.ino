#define PIN_LED_VERTE 4
#define PIN_LED_JAUNE 12
#define PIN_LED_ROUGE 14


void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(PIN_LED_VERTE, OUTPUT);
  pinMode(PIN_LED_JAUNE, OUTPUT);
  pinMode(PIN_LED_ROUGE, OUTPUT);

  Serial.println("LEDs pin inititilisés");
}

void loop() {
  // test de la led verte
  Serial.println("Allumage de la led verte");
  digitalWrite(PIN_LED_VERTE, HIGH);
  delay(1000);
  digitalWrite(PIN_LED_VERTE, LOW);

  // test de la led jaune
  Serial.println("Allumage de la led jaune");
  digitalWrite(PIN_LED_JAUNE, HIGH);
  delay(1000);
  digitalWrite(PIN_LED_JAUNE, LOW);

  // test de la led rouge
  Serial.println("Allumage de la led rouge");
  digitalWrite(PIN_LED_ROUGE, HIGH);
  delay(1000);
  digitalWrite(PIN_LED_ROUGE, LOW);
}
