/*
 * wai_huan.h
 * robot2014 项目的外环模式，功能包括遇障停车、红灯停以及沿左车道行驶
 * 简陋的状态机版本
 */

#define S_FORWARD 1
#define S_STOP 2
#define S_TURN_LEFT 3
#define S_TURN_RIGHT 4

int state;

int wai_huan_detect_state (void)	// 检测当前状态
{
	if (analogRead (IR_SENSOR_FRONT) < IR_FRONT_CLOSE)
		// 前方障碍物，或遇到红灯
		return S_STOP;
	else if (analogRead (IR_SENSOR_LEFT) < IR_LEFT_CLOSE)
		// 离左挡板太近
		return S_TURN_RIGHT;
	else if (analogRead (IR_SENSOR_LEFT) > IR_LEFT_FAR)
		// 离左挡板太远
		return S_TURN_LEFT;
	else return S_FORWARD;
}

void wai_huan (void)
{
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
		case S_TURN_RIGHT:
			motor (LEFT, FORWARD, NORMAL_SPEED);	// 掉转车头向右
			motor (RIGHT, FORWARD, HALF_SPEED);
			delay (618);	// 需要测试！
			state = S_FORWARD;
			break;
		default:
			break;
	}
}
