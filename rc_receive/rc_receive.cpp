#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>

#include <drivers/drv_hrt.h>
#include <uORB/Publication.hpp>
#include <uORB/topics/rc_channels.h>

extern "C" __EXPORT int rc_receive_main(int argc, char *argv[]);

int rc_receive_main(int argc, char *argv[])
{

	int rc_msg_handle;
	rc_channels_s rc_data;
	rc_msg_handle = orb_subscribe(ORB_ID(rc_channels));
	orb_set_interval(rc_msg_handle, 200);
	
	while(1)
	{
		orb_copy(ORB_ID(rc_channels), rc_msg_handle, &rc_data);
		PX4_INFO("channels 1 = %f", (double) rc_data.channels[0]);
		PX4_INFO("channels 2 = %f", (double) rc_data.channels[1]);
		PX4_INFO("channels 3 = %f", (double) rc_data.channels[2]);
		PX4_INFO("channels 4 = %f", (double) rc_data.channels[3]);
		PX4_INFO("channels 5 = %f", (double) rc_data.channels[4]);
		px4_usleep(200000);
	}
	return 0;
 }
