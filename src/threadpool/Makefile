TARGET = threadpool
PWD = $(shell pwd)
CC = gcc
CPP = g++
CFLAGS  := -Wall -O0

SRCS_CPP  += $(wildcard $(PWD)/*.cpp) 
OBJS_CPP += $(SRCS_CPP:.cpp=.o) 


DEPEND_LIB = -lpthread -lboost_thread


all : a
	ar crv libthreadpool.a  $(OBJS_CPP)
	#$(CPP) -shared -fPIC -o libthreadpool.so $(OBJS_CPP)
	rm -f $(OBJS_CPP)

a:
	$(CPP) $(CFLAGS) -c  -fPIC $(SRCS_CPP) $(INCLUDE_PATH) $(LIB_PATH) $(DEPEND_LIB)
	

	

tags :
	ctags -R *
clean:
	-rm -f $(OBJS) lib$(TARGET).a



