NAME := anti_theft

$(NAME)_SOURCES := anti_theft.c

GLOBAL_DEFINES += AOS_NO_WIFI

$(NAME)_COMPONENTS := yloop cli sensor
