// to use only one core
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static const int led_pin  = 2;

void ledtoggle(void *parameter){
  while(true){
    digitalWrite(led_pin, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(800 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, HIGH);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);

  xTaskCreatePinnedToCore(
    ledtoggle,
    "Toggle LED",
    1024,
    NULL,
    1,
    NULL,
    app_cpu);
}

void loop() {
  // put your main code here, to run repeatedly:

}
