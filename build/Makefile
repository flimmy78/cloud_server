#
#  LIBDSXMLC makefile 
#  Author: Jerry.Deng(denghongjie@hzdusun.com)
#
#
#

TARGET := server
PWD := $(shell pwd)
SRC := $(PWD)/../src
BIN := $(PWD)/../bin





all:
	@echo "Start building $(TARGET) ..."
	make -C $(SRC)
	-mv  $(SRC)/$(TARGET)  $(BIN)/
	
clean:
	make -C  $(SRC) clean
	-rm $(BIN)/$(TARGET)





   
	
	
	
	
	
