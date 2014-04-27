/*
 * xuan_ya.h
 * robot2014 项目的悬崖勒马模式，在悬崖前刹车。施工中
 */

void xuan_ya (void)
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
