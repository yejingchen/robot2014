/*
 * nei_huan.h
 * robot2014 项目的内环模式，功能包括遇障停车、红灯停、沿右车道行驶
 * 以及倒车入库
 * 伪状态机版本
 */

#define S_FORWARD 1
#define S_STOP 2
#define S_TURN_LEFT 3
#define S_TURN_RIGHT 4
#define S_GARAGE 5
#define S_BACK 6

#define LIMIT_DELTA 100	// <<< 需要测试！

int state;
int tempRightData;
bool in_garage = false;

int nei_huan_detect_state (void)	// 检测当前状态
{
	
	if (!in_garage)
	{
		if (analogRead (IR_SENSOR_FRONT) < IR_FRONT_CLOSE)
			// 前方障碍物，或遇到红灯
			return S_STOP;
		else if (analogRead (IR_SENSOR_RIGHT) < IR_RIGHT_CLOSE)
			// 离右挡板太近
			return S_TURN_LEFT;
		else if (analogRead (IR_SENSOR_RIGHT) > IR_RIGHT_FAR)
			// 离右挡板太远，或者已到达车库
		{
			if (analogRead (IR_SENSOR_RIGHT) - tempRightData < LIMIT_DELTA)
				// 前后两次检测变化不大，即视为偏离车道，调整车头
				return S_TURN_RIGHT;
			else 
				// 否则，即是已到达车库，准备倒车入库
				return S_GARAGE;
		}
		else return S_FORWARD;
	}
	
	else if (analogRead (IR_SENSOR_BACK) < IR_BACK_CLOSE)
		// 车后方有障碍/已到车库尽头
		return S_STOP;
	else
		// 在车库（in_garage），但是后方还没到尽头
		// 倒车
		return S_BACK; 
}

void nei_huan (void)
{
	state = nei_huan_detect_state ();

	switch (state)
	{
		case S_FORWARD:
			motor (LEFT, FORWARD, NORMAL_SPEED);	// 控制车直行
			motor (RIGHT, FORWARD, NORMAL_SPEED);
			break;
		case S_STOP:
			motor (LEFT, FORWARD, 0);	// 停车
			motor (RIGHT, FORWARD, 0);
			break;
		case S_TURN_LEFT:
			motor (LEFT, FORWARD, HALF_SPEED);	// 掉转车头向左
			motor (RIGHT, FORWARD, NORMAL_SPEED);
			delay (618);	// <<< 需要测试！
			state = S_FORWARD;
			break;
		case S_TURN_RIGHT:
			motor (LEFT, FORWARD, NORMAL_SPEED);	// 掉转车头向右
			motor (RIGHT, FORWARD, HALF_SPEED);
			delay (618);	// <<< 需要测试！
			state = S_FORWARD;
			break;
		case S_GARAGE:
			delay (600);	// 准备入库，掉转车头
			motor (LEFT, BACK, NORMAL_SPEED);
			motor (RIGHT, FORWARD, NORMAL_SPEED);
			delay (400);	// <<< 旋转时间，需要测试！
			in_garage = true;
			break;
		case S_BACK:
			motor (LEFT, BACK, NORMAL_SPEED);	// 控制车后退
			motor (RIGHT, BACK, NORMAL_SPEED);
			break;
		default:
			break;
	}

	tempRightData = analogRead (IR_SENSOR_RIGHT);
}
