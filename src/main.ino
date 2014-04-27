/*
 * main.ino
 * 2014 年广东省创意机器人大赛适用程序 主程序
 * 适用于 Arduino ATmega8 控制版
 */

#include "defines.h"
#include "coreutils.h"

#include "wai_huan.h"
#include "nei_huan.h"
#include "chao_che.h"
#include "xuan_ya.h"
#include "fu_jia.h"
#include "zi_ge.h"

void setup (void)
{
	// LED flashing
	pinMode (LED, OUTPUT);
	digitalWrite (LED, HIGH);

	// left motor
	pinMode (ML_DIR, OUTPUT);
	pinMode (ML_SPEED, OUTPUT);

	// right motor
	pinMode (MR_DIR, OUTPUT);
	pinMode (MR_SPEED, OUTPUT);

	// IR sensor
	pinMode (IR_SENSOR_BELOW_LEFT, INPUT);
	pinMode (IR_SENSOR_BELOW_RIGHT, INPUT);
	pinMode (IR_SENSOR_LEFT, INPUT);
	pinMode (IR_SENSOR_RIGHT, INPUT);
	pinMode (IR_SENSOR_FRONT, INPUT);
	pinMode (IR_SENSOR_BACK, INPUT);

	// IR out
	pinMode (IR_OUT_BELOW_LEFT, OUTPUT);
	pinMode (IR_OUT_BELOW_RIGHT, OUTPUT);
	pinMode (IR_OUT_BELOW_LEFT, OUTPUT);
	pinMode (IR_OUT_RIGHT, OUTPUT);
	pinMode (IR_OUT_FRONT, OUTPUT);
	pinMode (IR_OUT_BACK, OUTPUT);

	// Serial
	Serial.begin (9600);
	Serial.println ("Arduino initialized!");

	// 检查电机是否工作正常，在正式比赛时需移除
	// motor_test ();
}

// 设置模式：在 loop () 内调用下列函数之一，即可完成相应功能
// chao_che ()		超车
// xuan_yaa ()		悬崖勒马
// wai_huan ()		外环
// nei_huan ()		内环
// fu_jia ()		附加题
// zi_ge ()		资格赛

void loop (void)
{
	LED_flash ();

	delay (200);
}
