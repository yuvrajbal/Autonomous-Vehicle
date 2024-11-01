#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>
#include <uORB/topics/sensor_combined.h>
extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);
int hello_world_main(int argc, char *argv[]){
	int sensor_combined_handle;
	sensor_combined_s sensor_data;
	sensor_combined_handle = orb_subscribe(ORB_ID(sensor_combined));
	orb_set_interval(sensor_combined_handle, 200);
	while(1){
		orb_copy(ORB_ID(sensor_combined), sensor_combined_handle, &sensor_data);
		PX4_INFO("X = %f, Y = %f, Z = %f", (double)sensor_data.accelerometer_m_s2[0],
		(double)sensor_data.accelerometer_m_s2[1],
		(double)sensor_data.accelerometer_m_s2[2]);
		px4_usleep(200000);
	}
	return 0;
}

