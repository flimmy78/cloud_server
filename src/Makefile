TARGET = server
PWD = $(shell pwd)
			
			
CC = gcc
CPP = g++
CFLAGS  := -Wall -O0
PWD := $(shell pwd)

# add by au 2017/11/06
CFLAGS += -I $(PWD)/sync 
CFLAGS += -I$(PWD)/sync/include/dbmanager 
CFLAGS += -I$(PWD)/sync/include/json 
CFLAGS += -I$(PWD)/sync/include/osa  -DOSA_MODULE_NAME='"DBM"' 
CFLAGS += -I$(PWD)/sync/include/base64
CFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0




SRCS  += $(wildcard $(PWD)/net/*.c)  #####  TCP sever ############
SRCS  += $(wildcard $(PWD)/monitor/*.c) #####  TCP sever monitor ############
SRCS  += $(wildcard $(PWD)/*.c)   #####  main ############
# add by au 2017/11/06
SRCS  += $(wildcard $(PWD)/sync/*.c)   #####  sync #####

OBJS := $(SRCS:.c=.o)
THDPOOL_PATH := ./threadpool/

INCLUDE_PATH := -I ./threadpool  \
				-I $(PWD)/include \
				-I $(PWD)/../include
				
LIB_PATH  := -L$(PWD)/$(THDPOOL_PATH)
# add by au 2017/11/06
LIB_PATH  += -L$(PWD)/sync/lib -L/usr/local/lib/sac
				

DEPEND_LIB = -lthreadpool -lpthread -lboost_thread  -lboost_system ##./threadpool/libthreadpool.a
# add by au 2017/11/06
DEPEND_LIB += -ldbmanager -lmysqlclient -losa -ljansson -lstdc++


all :clean thdpool  $(TARGET)

%.o : %.c
	$(CPP) $(CFLAGS) -c $< -o $@ $(LIB_PATH) $(INCLUDE_PATH) 
	
$(TARGET) : $(OBJS)
	rm -f $@
	#$(CPP) -o $@ $(OBJS)  $(LIB_PATH) $(DEPEND_LIB)
	$(CC) -o $@ $(OBJS)  $(LIB_PATH) $(DEPEND_LIB)
	rm -f $(OBJS)
	
thdpool:
	make -C ./threadpool/

tags :
	ctags -R *

clean:
	rm -f $(OBJS) $(TARGET)
	make -C  $(THDPOOL_PATH) clean


install:
	sudo cp $(PWD)/sync/lib/*  /usr/local/lib/sac
	sudo cp $(PWD)/server /usr/local/bin/sac
	sudo cp $(PWD)/server.sh /usr/local/bin/sac/

start: 
	/usr/local/bin/sac/server.sh start &

stop:
	/usr/local/bin/sac/server.sh stop &

	
