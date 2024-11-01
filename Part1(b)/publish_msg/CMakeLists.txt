px4_add_module(
	MODULE examples__publish_msg
	MAIN publish_msg
	COMPILE_FLAGS
	SRCS
		publish_message.cpp
	DEPENDS
	)
