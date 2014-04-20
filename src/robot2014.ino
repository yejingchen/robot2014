#define LED 13

#define ML_DIR 7	// left motor direction pin
#define MR_DIR 8	// right motor direction pin
#define ML_SPEED 9	// left motor speed pin
#define MR_SPEED 10	// right morot speed pin

#define IR_OUT_BELOW 2		// IR out below pin
#define IR_SENSOR_BELOW 5	// IR sensor below pin

#define FORWARD 1	// used in motor ()
#define BACK 0

#define LEFT 1
#define RIGHT 2

#define NORMAL_SPEED 250

#define IR_BELOW_MAX 600

int IR_sensor_below_1;
int IR_sensor_below_2;

boolean LED_on = true;

void motor (int side, int dir, int speed)
{
	if (side == LEFT)
	{
		if (dir == FORWARD)
		{
			digitalWrite (ML_DIR, 1);
  			analogWrite (ML_SPEED, speed);
		}
		else if (dir == BACK)
		{ 
			digitalWrite (ML_DIR, 0); 
			analogWrite (ML_SPEED, speed);
		}
	}

	else if (side == RIGHT)
	{
		if (dir == FORWARD)
		{
			digitalWrite (MR_DIR, 1);
  			analogWrite (MR_SPEED, speed);
		}
		else if (dir == BACK)
		{ 
			digitalWrite (MR_DIR, 0); 
			analogWrite (MR_SPEED, speed);
		}
	}
}

void LED_flash (void)
{
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
	IR_sensor_below_1 = analogRead (IR_SENSOR_BELOW);
	Serial.println ("=====================================================");
	Serial.print ("environment light: ");
	Serial.println (IR_sensor_below_1);

	digitalWrite (IR_OUT_BELOW, HIGH); // turn on IRout to get ready to collect IR data
	delay (10);
	IR_sensor_below_2 = analogRead (IR_SENSOR_BELOW);
	Serial.print ("env + IR light: ");
	Serial.println (IR_sensor_below_2);

	Serial.print ("IR light: ");
	Serial.println (IR_sensor_below_2 - IR_sensor_below_1); // send the IR light data

	delay (300);
}

void setup ()
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
	pinMode (IR_SENSOR_BELOW, INPUT);

	// IR out
	pinMode (IR_OUT_BELOW, OUTPUT);
	digitalWrite(IR_OUT_BELOW, LOW); // disable the IR first to collect env data

	// Serial
	Serial.begin (9600);
	Serial.println ("Arduino initialized!");

	// DEBUG!!!
	//
	// IR debug
	for (int i = 1; i <= 3; i++)
		collect_IR_data ();

	// motor debug
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

void loop ()
{
	LED_flash ();

	if (analogRead (IR_SENSOR_BELOW) < IR_BELOW_MAX)
	{
		motor (LEFT, FORWARD, NORMAL_SPEED);
		motor (RIGHT, FORWARD, NORMAL_SPEED);
	}
	else 
	{
		motor (LEFT, FORWARD, 0);
		motor (RIGHT, FORWARD, 0);
	}

	delay (200);
}
