/////////////////////////////////////////////////////////////////////////////
//				GROUP 18
//				AUTHOR - YB ZW
//////////////////////////////////////////////////////////////////////////////


// project part 2

#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>
#include <drivers/drv_hrt.h>

#include <uORB/Publication.hpp>
#include <uORB/topics/test_motor.h>
#include <uORB/topics/rc_channels.h>
#include <uORB/topics/sensor_combined.h>

#include <uORB/topics/led_control.h>
#include <uORB/topics/debug_value.h>

#define DC_MOTOR 0
#define SERVO_MOTOR 1

extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);


int hello_world_main(int argc, char *argv[]){
	test_motor_s test_motor;
	test_motor_s test_servo;

	double motor_value = 0.1; //has to be a number between 0 and 1
	double servo_value = 0;

	px4_sleep(2);

	int debug_handle;
	debug_value_s mavlink_data;
	debug_handle = orb_subscribe(ORB_ID(debug_value));

	orb_set_interval(debug_handle, 200);

	uORB::Publication<test_motor_s> test_motor_pub(ORB_ID(test_motor));

	while(1){

		if (mavlink_data.value < 25){
			motor_value = 0.5;
		}
		else if (mavlink_data.value < 70 && mavlink_data.value >= 25){
			motor_value = 0.62;
		}
		else{
			motor_value = 0.8;
		}

		if (mavlink_data.ind == 0){ // LEFT
			servo_value = 0;
		}
		else if (mavlink_data.ind == 1){ // FORWARD
			servo_value = 0.5;
		}
		else{ // RIGHT
			servo_value = 1.0;
		}

		orb_copy(ORB_ID(debug_value), debug_handle, &mavlink_data);

		//PX4_INFO("Motor speed is %f", motor_value);
		test_motor.timestamp = hrt_absolute_time();
		test_motor.motor_number = DC_MOTOR;
		test_motor.value = (float)motor_value;
		test_motor.action = test_motor_s::ACTION_RUN;
		test_motor.driver_instance = 0;
		test_motor.timeout_ms = 0;

		test_motor_pub.publish(test_motor);

		//PX4_INFO("Servo speed is %f", servo_value);
		test_servo.timestamp = hrt_absolute_time();
		test_servo.motor_number = SERVO_MOTOR;
		test_servo.value = (float)servo_value;
		test_servo.action = test_motor_s::ACTION_RUN;
		test_servo.driver_instance = 0;
		test_servo.timeout_ms = 0;

		test_motor_pub.publish(test_servo);

		px4_usleep(200000);

 		}
	return 0;
}


////////////////////////////////////////////////////////////////////////////////
// PART 1 A
////////////////////////////////////////////////////////////////////////////////////////
/*
#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>

#include <drivers/drv_hrt.h>
#include <uORB/Publication.hpp>
#include <uORB/topics/test_motor.h>
#include <uORB/topics/rc_channels.h>

#define DC_MOTOR 0
#define SERVO_MOTOR 1

extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);

int hello_world_main(int argc, char *argv[])
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
			test_motor.value = (float)motor_value-(float)0.2;
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
*/

////////////////////////////////////////////////////////////////////////////////
// PART 1 B
////////////////////////////////////////////////////////////////////////////////////////
/*
#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>

#include <drivers/drv_hrt.h>
#include <uORB/Publication.hpp>
#include <uORB/topics/test_motor.h>
#include <uORB/topics/rc_channels.h>

#define DC_MOTOR 0
#define SERVO_MOTOR 1

extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);

int hello_world_main(int argc, char *argv[])
{
	test_motor_s test_motor;
		test_motor_s servo_motor;
		double motor_value = 1; // a number between 0 to 1
		double servo_value = 0.008; // a number between 0 to 1

		int rc_handle;
		rc_channels_s rc_data;
		rc_handle = orb_subscribe(ORB_ID(rc_channels));
		orb_set_interval(rc_handle, 200);

		uORB::Publication<test_motor_s> dc_motor_pub(ORB_ID(test_motor));
		uORB::Publication<test_motor_s> servo_motor_pub(ORB_ID(test_motor));

		while(1)
	 	{
	//	 	PX4_INFO("Enter speed value and servo angle (0 to 1). If you enter a value outside the range,the motor will be stopped and the application will be terminated.");
	//		scanf("%lf", &motor_value);
	//		scanf("%lf", &servo_value);
	//		if(motor_value > 1.0 || motor_value < 0)
	//			break;
	//		if(servo_value > 1.0 || servo_value < 0)
	//			break;

			orb_copy(ORB_ID(rc_channels), rc_handle, &rc_data);
//			 motor accepts 0 -1 , rc values from -1 to 1
			motor_value = (((double)rc_data.channels[2]+1)/2);
			servo_value = (((double)rc_data.channels[0]+1)/2);

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
*/
////////////////////////////////////////////////////////////////////////////////
//EXPERIMENTS
////////////////////////////////////////////////////////////////////////////////////////


//#include <px4_platform_common/px4_config.h>
//#include <px4_platform_common/log.h>
//#include <uORB/topics/sensor_combined.h>
//
//#include <drivers/drv_hrt.h>
//#include <uORB/Publication.hpp>
//#include <uORB/topics/test_motor.h>
//
//#include <uORB/topics/rc_channels.h>
//


//
//extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);
//
//
//int hello_world_main(int argc, char *argv[])
//{
//	for(int i = 0; i < 5; i++)
//	{
//		PX4_INFO("Hello World %d", i);
//		px4_sleep(1);
//	}
//	return 0;
//}
//


/*
extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);

int hello_world_main(int argc, char *argv[])
{
	int sensor_combined_handle;
	sensor_combined_s sensor_data;
	sensor_combined_handle = orb_subscribe(ORB_ID(sensor_combined));
	orb_set_interval(sensor_combined_handle, 200);
	while(1)
	{
		orb_copy(ORB_ID(sensor_combined), sensor_combined_handle, &sensor_data);
		PX4_INFO("X = %f, Y = %f, Z = %f", (double)sensor_data.accelerometer_m_s2[0],
		(double)sensor_data.accelerometer_m_s2[1],
		(double)sensor_data.accelerometer_m_s2[2]);
		px4_usleep(200000);
	}
	return 0;
}
*/

/*
extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);

int hello_world_main(int argc, char *argv[])
{
	int channels_handle;
	rc_channels_s channels;
	channels_handle = orb_subscribe(ORB_ID(rc_channels));
	orb_set_interval(channels_handle, 200);
	while(1)
	{
		orb_copy(ORB_ID(rc_channels), channels_handle, &channels);
		PX4_INFO("Channel_1 = %f, "
				"Channel_2 = %f, "
				"Channel_3s = %f, "
				"Channel_4s = %f",
				(double)channels.channels[0],
				(double)channels.channels[1],
				(double)channels.channels[2],
				(double)channels.channels[3]
		);
		px4_usleep(200000);
	}
	return 0;
}
*/


//#include <px4_platform_common/px4_config.h>
//#include <px4_platform_common/log.h>
//#include <uORB/Publication.hpp>
//#include <uORB/topics/led_control.h>
//#include <uORB/topics/debug_value.h>
//extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);
//int hello_world_main(int argc, char *argv[])
//{
//	px4_sleep(2);
//	debug_value_s debug_data;
//	int debug_handle = orb_subscribe(ORB_ID(debug_value));
//	orb_set_interval(debug_handle, 500);
//	led_control_s led_control;
//	uORB::Publication<led_control_s> led_control_pub(ORB_ID(led_control));
//	while(1)
//	{
//		orb_copy(ORB_ID(debug_value), debug_handle, &debug_data);
//		led_control.timestamp = hrt_absolute_time();
//		led_control.color = led_control_s::COLOR_GREEN;
//		led_control.priority = led_control_s::MAX_PRIORITY;
//		led_control.led_mask = 0xff;
//		if(debug_data.ind == 1)
//			led_control.mode = led_control_s::MODE_ON;
//		else
//			led_control.mode = led_control_s::MODE_OFF;
//
//		led_control_pub.publish(led_control);
//		px4_usleep(500000);
//	}
//	return 0;
//}
//
