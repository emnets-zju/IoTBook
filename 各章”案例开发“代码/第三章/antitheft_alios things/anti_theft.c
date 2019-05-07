#include <aos/aos.h>
#include "hal/hal.h"
#include <hal/soc/soc.h>
#include <stdio.h>
#define GPIO_LED_IO     67
#define SAMPLES_COUNT 20

gpio_dev_t led;         /* 声明LED 设备 */
static int fd_acc  = -1;    /* 声明加速度传感器文件标识符 */
int counter = 0;
float samples[SAMPLES_COUNT];

static int get_acc_data(int32_t *x, int32_t *y, int32_t *z)
{
    accel_data_t data = {0};
    ssize_t size = 0;
    if (fd_acc < 0)
        return 0;
    size = aos_read(fd_acc, &data, sizeof(data));
    if (size != sizeof(data)) {
        printf("aos_read return error.\n");
    }
    *x = data.data[0];
    *y = data.data[1];
    *z = data.data[2];
    return 0;
}

static void sensor_refresh_task(void *arg) {
    static int thiefFlag = 0;
    int32_t acc_x = 0, acc_y = 0, acc_z = 0, i;
    get_acc_data(&acc_x, &acc_y, &acc_z); /* 读取加速度传感器数据*/
    samples[counter % SAMPLES_COUNT] = (float)acc_x * 9.8 / 1024;
    if (counter >= SAMPLES_COUNT) {
        float sum = 0, avg, var = 0, diff;
        for (i = 0; i < SAMPLES_COUNT; i++) {
            sum += samples[i];
        }
        avg = sum / SAMPLES_COUNT;
        for (i = 0; i < SAMPLES_COUNT; i++){
            diff = samples[i] - avg;
            var += diff * diff;
        }
        if (var > SAMPLES_COUNT / 2) {
            hal_gpio_output_toggle(&led); /* 亮LED灯提醒用户有小偷 */
            if (thiefFlag == 0) {
                LOG("Thief!\n");
                thiefFlag = 1;
            }
        } else {
            hal_gpio_output_high(&led);
            thiefFlag = 0;
        }
    }
    counter++;
    aos_post_delayed_action(50, sensor_refresh_task, NULL);
}

void app_init() {
    led.port = GPIO_LED_IO; /* 配置LED 灯的GPIO */
    led.config = OUTPUT_PUSH_PULL; /* 设置为输出模式 */
    hal_gpio_init(&led); /* 初始化LED 灯 */
    int fd = -1;
    fd = aos_open(dev_acc_path, O_RDWR); /* 打开加速度传感器 */
    if (fd < 0) {
        printf("Off-line: aos_open %s fd = %d.\n", dev_acc_path, fd);
    }
    fd_acc = fd;
    /* 创建定时器，每隔1s 执行一次sensor_refresh_task */
    aos_post_delayed_action(50, sensor_refresh_task, NULL);
    // aos_timer_new(&refresh_timer, sensor_refresh_task, NULL, 10, 1);
}

int application_start(int argc, char *argv[])
{
    LOG("Start\n");
    app_init();
    // aos_post_delayed_action(1000, app_trigger_low_action, NULL);
    aos_loop_run();

    return 0;
}
