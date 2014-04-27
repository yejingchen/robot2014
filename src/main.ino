/*
 * main.ino
 * 2014 年广东省创意机器人大赛适用程序
 * 本程序适用于 Arduino ATmega8 控制版，可以完成创意机器人大赛的要求功能。
 * 程序包含多个模式，根据需要设置不同的 MODE，即可完成不同的工作。
 */

#include "defines.h"
#include "coreutils.h"

#include "wai_huan.h"
#include "nei_huan.h"
#include "chao_che.h"
#include "xuan_ya_le_ma.h"
#include "fu_jia_ti.h"
#include "zi_ge_sai.h"

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
	// pinMode (IR_SENSOR_BELOW_RIGHT, INPUT);


	// IR out
	pinMode (IR_OUT_BELOW_LEFT, OUTPUT);
	// pinMode (IR_OUT_BELOW_RIGHT, OUTPUT);
	digitalWrite (IR_OUT_BELOW_LEFT, LOW); // 关闭红外以便收集环境光数据
	// digitalWrite (IR_OUT_BELOW_RIGHT, LOW);

	// Serial
	Serial.begin (9600);
	Serial.println ("Arduino initialized!");

	// 检查电机是否工作正常，在正式比赛时需移除
	// motor_test ();
}

// 设置模式：在 loop () 内调用下列函数之一，即可完成相应功能
// chao_che ()		超车
// xuan_ya_le_ma ()	悬崖勒马
// wai_huan ()		外环
// nei_huan ()		内环
// fu_jia_ti ()		附加题

void loop (void)
{
	LED_flash ();

	delay (200);
}
