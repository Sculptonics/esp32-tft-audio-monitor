#include "esp_timer.h"
#include "u8g2_esp32_hal.h"
#include "UI.h"
#include "UI/Waveform.h"
#include "esp_log.h"
#include "UI/GraphicEqualiser.h"
#include "config.h"
static const char *TAG = "UI";


// Task to process samples
void drawing_task(void *param)
{
  UI *ui = reinterpret_cast<UI *>(param);
  const TickType_t xMaxBlockTime = pdMS_TO_TICKS(1000);
  while (true)
  {
    // wait to be told to redraw
    uint32_t ulNotificationValue = ulTaskNotifyTake(pdTRUE, xMaxBlockTime);
    if (ulNotificationValue != 0)
    {
      ui->draw();
    }
  }
}

UI::UI(u8g2_t &display, int window_size) : m_display(display)
{
  ESP_LOGI(TAG,"Display is %d x %d\n", display.width, display.height);
  m_waveform = new Waveform(display, 0, 0, display.width, display.height, window_size);
  m_graphic_equaliser = new GraphicEqualiser(0, 0, display.width, display.height, window_size, BAND_NUM, PART_OF_RANGE);
  // start off with the spectrogram hidden
  m_waveform->visible = true;

  m_graphic_equaliser->visible = true;
  // create a drawing task to update our UI
  xTaskCreatePinnedToCore(drawing_task, "Drawing Task", 4096, this, 1, &m_draw_task_handle, 1);
}

void UI::toggle_display()
{
  bool tmp = m_graphic_equaliser->visible;
  m_graphic_equaliser->visible = m_waveform->visible;
  m_waveform->visible = tmp;
}

void UI::update(float *samples, float *fft)
{
  m_waveform->update(samples);
  m_graphic_equaliser->update(fft);
  xTaskNotify(m_draw_task_handle, 1, eIncrement);
}

unsigned long draw_time = 0;
int draw_count = 0;
void UI::draw()
{
  auto start = esp_timer_get_time()/1000;
  u8g2_ClearBuffer(&m_display);
  m_graphic_equaliser->draw(m_display);
  m_waveform->draw(m_display);
  u8g2_SendBuffer(&m_display);
  auto end = esp_timer_get_time()/1000;
  draw_time += end - start;
  draw_count++;
  if (draw_count == 20)
  {
    ESP_LOGI(TAG, "Drawing time %ld", draw_time / 20);
    draw_count = 0;
    draw_time = 0;
  }
}