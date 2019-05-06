COMPONENT=AntiTheftAppC

CFLAGS += -DTOSH_DATA_LENGTH=114
CFLAGS += -DPRINTF_BUFFER_SIZE=1500L 
CFLAGS += -DCC2420_DEF_CHANNEL=18

CFLAGS += -DPRINTF_BUFFER_SIZE=1500L
CFLAGS += -I$(TOSDIR)/lib/net \
          -I$(TOSDIR)/lib/net/drip \
          -I$(TOSDIR)/lib/net/4bitle \
					-I$(TOSDIR)/lib/printf \
          -I../libs/ctp #-DNO_DEBUG

TFLAGS += -I$(TOSDIR)/../apps/tests/TestDissemination \
          -I$(TOSDIR)/../support/sdk/c \
          -I$(TOSDIR)/types \
          -I.
#CFLAGS += -DTINYSDM
LIBMOTE = $(TOSDIR)/../support/sdk/c/libmote.a
#BUILD_EXTRA_DEPS += tn-injector #tn-listener
LISTEN_OBJS = collection_msg.o test_network_msg.o tn-listener.o $(LIBMOTE)
INJECT_OBJS = set_rate_msg.o tn-injector.o collection_debug_msg.o $(LIBMOTE)

#CFLAGS += -DJMP_TBL_START=0x3500

include $(MAKERULES)
