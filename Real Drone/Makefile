OBJ:=objs
CC:=gcc
CPP:=g++
LD:=ld
AS:=as
NASM:=nasm

OBJ_DIR:=./
C_OBJ_FILES := $(patsubst ./%.c,$(OBJ_DIR)/%.o,$(wildcard ./*.c))	\
			$(patsubst ./SPI/%.c,./SPI/%.o,$(wildcard ./SPI/*.c))
CPP_OBJ_FILES := $(patsubst ./%.cpp, $(OBJ_DIR)/%.o,$(wildcard ./*.cpp)) \
			$(patsubst ./SPI/%.cpp,./SPI/%.o,$(wildcard ./SPI/*.cpp)) 
obj = $(CPP_OBJ_FILES) $(C_OBJ_FILES)
#csrc = $(wildcard ./*.c) \
       $(wildcard ./SPI/*.c)
#cppsrc = $(wildcard ./*.cpp) \
       $(wildcard ./SPI/*.cpp)
#obj = $(csrc:.c=.o) $(ccsrc:.cpp=.o)

MAIN:=ControlServer.o
OUTPUT:=ControlServer

OBJS:= *.o
INCLUDED:=	#-I$(LIBRARY) -I$(SOURCE)

CXXFLAGS:= -w -lstdc++ -O2 -std=gnu++11 -Wall -Wextra -g -D_GLIBCXX_RELEASE $(INCLUDED)
LDFLAGS+=-lutil -lpthread
all: clean build clean 

brun: all run

build: $(obj)
	$(CXX) -o $(OUTPUT) $^ $(LDFLAGS)

build-main:	$(MAIN)
	$(CXX) -o $(OUTPUT) $^ $(LDFLAGS)
	chmod +x $(OUTPUT)

run:
	./$(OUTPUT)

clean:
	rm -f build-crt0 *.o */*.o */*/*.o
	rm -rfv objs

%.o: %.c
	$(CC) -c $< -o $@ $(CXXFLAGS)

%.o: %.cpp
	$(CPP) -c $< -o $@ $(CXXFLAGS)
