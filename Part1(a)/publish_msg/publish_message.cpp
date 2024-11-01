#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>

#include <drivers/drv_hrt.h>
#include <uORB/Publication.hpp>
#include <uORB/topics/test_motor.h>
#include <uORB/topics/rc_channels.h>

#define DC_MOTOR 0
#define SERVO_MOTOR 1


extern "C" __EXPORT int publish_msg_main(int argc, char *argv[]);

int publish_msg_main(int argc, char *argv[])
{
	test_motor_s test_motor;
	test_motor_s servo_motor;
	double motor_value = 0; // a number between 0 to 1
	double servo_value = 0.008; // a number between 0 to 1

	uORB::Publication<test_motor_s> dc_motor_pub(ORB_ID(test_motor));
	uORB::Publication<test_motor_s> servo_motor_pub(ORB_ID(test_motor));

	while(1)
 	{	
	 	PX4_INFO("Enter speed value and servo angle (0 to 1). If you enter a value outside the range,the motor will be stopped and the application will be terminated.");
		scanf("%lf", &motor_value);
		scanf("%lf", &servo_value);
		if(motor_value > 1.0 || motor_value < 0)
			break;
		if(servo_value > 1.0 || servo_value < 0)
			break;


		PX4_INFO("Motor speed is %f, Servo angle is %f", motor_value, servo_value);
			
		test_motor.timestamp = hrt_absolute_time();
		test_motor.motor_number = DC_MOTOR;
		test_motor.value = (float)motor_value;
		test_motor.action = test_motor_s::ACTION_RUN;
		test_motor.driver_instance = 0;
		test_motor.timeout_ms = 0;
		
		servo_motor.timestamp = hrt_absolute_time();
		servo_motor.motor_number = SERVO_MOTOR;
		servo_motor.value = (float)servo_value;
		servo_motor.action = test_motor_s::ACTION_RUN;
		servo_motor.driver_instance = 0;
		servo_motor.timeout_ms = 0;

		dc_motor_pub.publish(test_motor);
		servo_motor_pub.publish(servo_motor);

	}

	PX4_INFO("The motor will be stopped");
	test_motor.timestamp = hrt_absolute_time();
	test_motor.motor_number = DC_MOTOR;
	test_motor.value = 0.5;
	test_motor.driver_instance = 0;
	test_motor.timeout_ms = 0;
	
	PX4_INFO("The servo will reset");
	servo_motor.timestamp = hrt_absolute_time();
	servo_motor.motor_number = SERVO_MOTOR;
	servo_motor.value = 0.5;
	servo_motor.driver_instance = 0;
	servo_motor.timeout_ms = 0;

	dc_motor_pub.publish(test_motor);
	servo_motor_pub.publish(servo_motor);

	return 0;
 }
