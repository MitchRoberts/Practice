#if #CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else  
  static const BaseType_t app_cpu = 1;
#endif

//print sone random string
const char msg[] = "Hello there ho are you today, I hope you are all doing well";


//now create some task handles
static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;

//**************************************************************
//Tasks

void startTask1 (void *parameter){
  // count number of characters in string
  int msg_len = strlen(msg);

  //print string to terminal
  while (true){
    Serial.println();
    for (int i = 0; i < msg_len; i++){
      Serial.print(msg[i]);
    }
    Serial.println();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void startTask2 ( void *parameter){
  while (true){
    Serial.print('*');
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup() {
  // put your setup code here, to run once:
  // configure serial (slow so we can watch the preemption)
  Serial.begin(300);

  //wait a moment to start (so we don't miss serial output)
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("--FreeRTOS Task Demo--");

  // Print seld priority
  Serial.print("Setup and loop task running on core");
  Serial.print(xPortGetCoreID());
  Serial.print("with priority");
  Serial.println(uxTaskPriorityGet(NULL));

  //Task to run forever
  xTaskCreatePinnedToCore(startTask1,
                          "Task1",
                          1024,
                          NULL,
                          1, //priority
                          &task_1, // handle
                          app_cpu);
 

xTaskCreatePinnedToCore(startTask2,
                          "Task1",
                          1024,
                          NULL,
                          2, //priority
                          &task_2, // handle
                          app_cpu);
}
void loop() {
  // put your main code here, to run repeatedly:
  // Suspend the higher priority task for some intervals

  for (int i = 0; i < 3; i++){
    vTaskSuspend(task_2);
    vTaskDelay(2000/portTICK_PERIOD_MS);
    vTaskResume(task_2);
    vTaskDelay(2000/portTICK_PERIOD_MS);
  
// Deleteing the lower priority task
    
  }
  if (task_1 != NULL) {
    vTaskDelete(task_1);
    task_1 = NULL;
  }
}
