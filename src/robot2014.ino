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
#define IR_OUT_BELOW_RIGHT
#define IR_SENSOR_BELOW_RIGHT

#define IR_OUT_FRONT
#define IR_OUT_BACK
#define IR_OUT_LEFT
#define IR_OUT_RIGHT
*/

#define SENSOR IR_SENSOR_BELOW_LEFT
#define FORWARD 1	// 在 motor () 中被使用
#define BACK 0

#define LEFT 1
#define RIGHT 2

#define NORMAL_SPEED 250
#define HALF_SPEED 125

#define IR_BELOW_MAX 600 // <<< 需要修正
// #define IR_FRONT_MAX

int IR_sensor_below_1;	// 在 collect_IR_data 中被使用
int IR_sensor_below_2;

boolean LED_on = true;

void motor (int side, int dir, int speed)
{
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
	// collect env light data
	IR_sensor_below_1 = analogRead (SENSOR);
	Serial.println ("=====================================================");
	Serial.print ("environment light:\t");
	Serial.println (IR_sensor_below_1);

	digitalWrite (IR_OUT_BELOW_LEFT, HIGH); // 打开红外发射管，准备收集数据
	delay (10);
	IR_sensor_below_2 = analogRead (SENSOR);
	Serial.print ("env + IR light:\t\t");
	Serial.println (IR_sensor_below_2);

	Serial.print ("IR light:\t\t");
	Serial.println (IR_sensor_below_2 - IR_sensor_below_1); // send the IR light data

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

void nei_huan (void)
{
	// 用于内环赛道的模式，功能包括遇障停车、红灯停以及沿车道行驶
	if (analogRead (IR_SENSOR_FRONT) < IR_FRONT_MAX)
	{
		motor (LEFT, FORWARD, 0);
		motor (RIGHT, FORWARD, 0);
	}

	if (analogRead (IR_SENSOR_RIGHT) > IR_RIGHT_MIN)
	{
		motor (LEFT, FORWARD, NORMAL_SPEED);
		motor (RIGHT, FORWARD, HALF_SPEED);
	}
}		

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
