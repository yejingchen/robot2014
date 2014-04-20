/*
   本程序适用于 ATmega8 Arduino 控制版，可以完成创意机器人大赛的要求功能。
   程序包含多个模式，根据需要设置不同的 MODE，即可完成不同的工作。
   部分 #define 语句以后会保存到单独的文件中，请留意常量名。
*/

#define WAI_HUAN 1
#define NEI_HUAN 2
#define CHAO_CHE 3
#define XUAN_YA_LE_MA 4
#define FU_JIA_TI 5
// 设置模式：可用值有	WAI_HUAN	NEI_HUAN	CHAO_CHE
//			（外环）	（内环）	（超车）
//			XUAN_YA_LE_MA	FU_JIA_TI
//			（悬崖勒马）	（附加题）
// 各功能尚在开发中
#define MODE WAI_HUAN

#define LED 13

// 左轮和右轮
#define ML_DIR 7	// 左轮方向
#define MR_DIR 8	// 右轮方向
#define ML_SPEED 9	// 左轮速度
#define MR_SPEED 10	// 右轮速度

// 6 个方向的红外 LED、光电三极管
#define IR_OUT_BELOW_LEFT 2
#define IR_SENSOR_BELOW_LEFT 5
/*
未确定安装在哪个管脚
#define IR_OUT_BELOW_RIGHT
#define IR_SENSOR_BELOW_RIGHT

#define IR_OUT_FRONT
#define IR_OUT_BACK
#define IR_OUT_LEFT
#define IR_OUT_RIGHT
*/

#define SENSOR IR_SENSOR_BELOW_LEFT // 用于 collect_IR_data ()

#define FORWARD 1	// 车轮方向，在 motor () 中被使用
#define BACK 0
#define LEFT 1	// 左右轮，用于 motor ()
#define RIGHT 2
#define NORMAL_SPEED 250
#define HALF_SPEED 125

#define IR_BELOW_MAX 600	// <<< 需要测试！
// #define IR_FRONT_CLOSE	// <<< 需要测试！
// #define IR_LEFT_CLOSE	// <<< 需要测试！
// #define IR_LEFT_FAR	// <<< 需要测试！

unsigned int IR_sensor_below_1;	// 在 collect_IR_data 中被使用
unsigned int IR_sensor_below_2;

boolean LED_on = true;

void motor (int side, int dir, int speed)
{
	// 控制车轮转动
	// 注意！小心车轮的导线颜色，不要接反。可以用电池测试出哪根是正极
	if (side == LEFT)
	{
		digitalWrite (ML_DIR, dir);
  		analogWrite (ML_SPEED, speed);
	}

	else if (side == RIGHT)
	{
		digitalWrite (MR_DIR, dir);
  		analogWrite (MR_SPEED, speed);
	}
}

void LED_flash (void)
{
	// LED 闪烁，用于 debug
	if (LED_on = true)
	{
		digitalWrite (LED, LOW);
		LED_on = false;
	}
	else
	{
		digitalWrite (LED, HIGH);
		LED_on = true;
	}
}

void collect_IR_data (void)
{
	// 收集环境光
	IR_sensor_below_1 = analogRead (SENSOR);
	Serial.println ("===================================================");
	Serial.print ("environment light:\t");
	Serial.println (IR_sensor_below_1);

	digitalWrite (IR_OUT_BELOW_LEFT, HIGH); // 打开红外发射管，准备收集数据
	delay (10);
	IR_sensor_below_2 = analogRead (SENSOR);
	Serial.print ("env + IR light:\t\t");
	Serial.println (IR_sensor_below_2);

	Serial.print ("IR light:\t\t");
	Serial.println (IR_sensor_below_2 - IR_sensor_below_1); // 发送红外数据

	delay (300);
}

void motor_test (void)
{
	// 检查电机是否工作正常
	for (int i = 1; i <= 2; i++)
	{
		motor (LEFT, FORWARD, NORMAL_SPEED);
		delay (800);
		motor (LEFT, FORWARD, 0);
		delay (100);
		motor (LEFT, BACK, NORMAL_SPEED);
		delay (400);
		motor (LEFT, BACK, 0);
		delay (100);

		motor (RIGHT, FORWARD, NORMAL_SPEED);
		delay (800);
		motor (RIGHT, FORWARD, 0);
		delay (100);
		motor (RIGHT, BACK, NORMAL_SPEED);
		delay (400);
		motor (RIGHT, BACK, 0);
		delay (100);

	}
}

void xuan_ya_le_ma (void)
{
	// 悬崖勒马模式，施工中
	if (analogRead (SENSOR) < IR_BELOW_MAX)
	{
		motor (LEFT, FORWARD, NORMAL_SPEED);
		motor (RIGHT, FORWARD, NORMAL_SPEED);
	}
	else 
	{
		motor (LEFT, FORWARD, 0);
		motor (RIGHT, FORWARD, 0);
	}
}

///// 以下为外环模式内容
//
// 外环状态机状态
#ifdef MODE == WAI_HUAN
#define S_FORWARD 1
#define S_STOP 2
#define S_TURN_LEFT 3
#define S_TURN_RIGHT 4
#endif

int state;

int wai_huan_detect_state (void)	// 检测当前状态
{
	if (analogRead (IR_SENSOR_FRONT) < IR_FRONT_CLOSE)
		// 前方障碍物，或遇到红灯
		return = S_STOP;
	else if (analogRead (IR_SENSOR_LEFT) < IR_LEFT_CLOSE)
		// 离左挡板太近
		return = S_TURN_RIGHT;
	else if (analogRead (IR_SENSOR_LEFT) > IR_LEFT_FAR)
		// 离左挡板太远
		return = S_TURN_LEFT;
	else return = S_FORWARD;
}

void wai_huan (void)
{
	// 用于外环赛道的模式，功能包括遇障停车、红灯停以及沿左车道行驶
	// 简陋的状态机版本
	state = wai_huan_detect_state ();

	switch (state)
	{
		case S_FORWARD:
			motor (LEFT, FORWARD, NORMAL_SPEED);	// 控制电机直行
			motor (RIGHT, FORWARD, NORMAL_SPEED);
			break;
		case S_STOP:
			motor (LEFT, FORWARD, 0);	// 停车
			motor (RIGHT, FORWARD, 0);
			break;
		case S_TURN_LEFT:
			motor (LEFT, FORWARD, HALF_SPEED);	// 掉转车头向左
			motor (RIGHT, FORWARD, NORMAL_SPEED);
			delay (618);	// 需要测试！
			state = S_FORWARD;
			break;
		case  S_TURN_RIGHT:
			motor (LEFT, FORWARD, NORMAL_SPEED);	// 掉转车头向右
			motor (RIGHT, FORWARD, HALF_SPEED);
			delay (618);	// 需要测试！
			state = S_FORWARD;
			break;
		default:
			break;
}
//
///// 以上为外环模式内容

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

void loop (void)
{
	LED_flash ();

	delay (200);
}
