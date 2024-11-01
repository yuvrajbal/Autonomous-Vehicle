#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>
extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);
int hello_world_main(int argc, char *argv[]){
    for(int i = 0; i < 5; i++){
        PX4_INFO("Hello World %d", i);
        px4_sleep(1);
    }
    return 0;
}
