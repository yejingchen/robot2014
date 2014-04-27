/*
 * coreutils.h
 * robot2014 项目的核心函数
 */

void motor (int side, int dir, int speed);
void LED_flash (void);
void motor_test (void);
void collect_IR_data (void);

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

boolean LED_on = true;

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

unsigned int IR_sensor_below_1;	// 在 collect_IR_data () 中被使用
unsigned int IR_sensor_below_2;

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
