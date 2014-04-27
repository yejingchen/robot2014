/*
 * defines.h
 * 定义了 robot2014 项目的宏，定义了各红外三极管、马达安装的管脚，
 * 以及核心函数用到的状态名
 */

#define LED 13

// 左轮和右轮
#define ML_DIR 7	// 左轮方向
#define MR_DIR 8	// 右轮方向
#define ML_SPEED 9	// 左轮速度
#define MR_SPEED 10	// 右轮速度

// 6 个方向的红外 LED、光电三极管
#define IR_OUT_BELOW_LEFT 2
#define IR_SENSOR_BELOW_LEFT 5

// 红外传感器、红外发射管
// <<< 需要实际接线！
  #define IR_SENSOR_BELOW_LEFT 2
  #define IR_SENSOR_BELOW_RIGHT 2
  #define IR_SENSOR_LEFT 2
  #define IR_SENSOR_RIGHT 2
  #define IR_SENSOR_FRONT 2
  #define IR_SENSOR_BACK 2

  #define IR_OUT_BELOW_LEFT 2
  #define IR_OUT_BELOW_RIGHT 2
  #define IR_OUT_LEFT 2
  #define IR_OUT_RIGHT 2
  #define IR_OUT_FRONT 2
  #define IR_OUT_BACK 2

#define SENSOR IR_SENSOR_BELOW_LEFT // 用于 collect_IR_data ()

#define FORWARD 1	// 车轮方向，在 motor () 中被使用
#define BACK 0
#define LEFT 1	// 左右轮，用于 motor ()
#define RIGHT 2
#define NORMAL_SPEED 250
#define HALF_SPEED 125

#define IR_BELOW_MAX	600	// <<< 需要测试！
//test only
#define IR_FRONT_CLOSE	100	// <<< 需要测试！
#define IR_LEFT_CLOSE	100	// <<< 需要测试！
#define IR_LEFT_FAR	100	// <<< 需要测试！
#define IR_RIGHT_FAR	100	// <<< 需要测试！
#define IR_RIGHT_CLOSE	100	// <<< 需要测试!
