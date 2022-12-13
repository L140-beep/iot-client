#define LED_PIN 0

int led_get_value(){
  int data = analogRead(LED_PIN);
  Serial.println(data);

  return data;
}