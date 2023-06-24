#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
const int LED_PIN = 2;
volatile float cpuTemperature = 0;
TaskHandle_t temperatureTaskHandle = NULL;
float readCpuTemperature() {
 return random(30, 50); 
}
void temperatureTask(void *parameter) {
  (void)parameter;

  TickType_t lastWakeTime = xTaskGetTickCount();

  for (;;) {
    cpuTemperature = readCpuTemperature();
    xTaskNotifyGive(temperatureTaskHandle);
    vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(100));
  }
}
void ledBlinkTask(void *parameter) {
  (void)parameter;

  pinMode(LED_PIN, OUTPUT);

  for (;;) {
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  }
}

void setup() {
  xTaskCreate(temperatureTask, "TemperatureTask", 2048, NULL, 1, &temperatureTaskHandle);
  xTaskCreate(ledBlinkTask, "LEDBlinkTask", 2048, NULL, 2, NULL);
}

void loop() {
}
