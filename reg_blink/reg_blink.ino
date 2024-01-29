// Use only one core for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

//Pins
static const int led_pin = 2;

void toggleLED(void *parameter) {
  while(1){
    digitalWrite(led_pin, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);

  xTaskCreatePinnedToCore (
              toggleLED, //Function to be called
              "Toggle LED", //Name of Task
              1024, // Stack size (bytes in ESP32)
              NULL, // Parameter to pass into function
              1, // Task priority, higher the number the higher the priority
              NULL, // Task handle
              app_cpu); // Run on one core for demo
}

void loop() {
  // put your main code here, to run repeatedly:

}
