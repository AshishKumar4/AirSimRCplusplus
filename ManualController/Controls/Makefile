OBJ:=objs
CC:=gcc
CPP:=g++
LD:=ld
DIRECTCONTROL:=DirectControls

OBJ_DIR:=./
CPP_OBJ_FILES := $(patsubst ./%.cpp, $(OBJ_DIR)/%.o,$(wildcard ./*.cpp)) \
			$(patsubst ./$(DIRECTCONTROL)/%.cpp,./$(DIRECTCONTROL)/%.o,$(wildcard ./$(DIRECTCONTROL)/*.cpp)) 
obj = $(CPP_OBJ_FILES) 
#csrc = $(wildcard ./*.c) \
       $(wildcard ./SPI/*.c)
#cppsrc = $(wildcard ./*.cpp) \
       $(wildcard ./SPI/*.cpp)
#obj = $(csrc:.c=.o) $(ccsrc:.cpp=.o)

MAIN:=RemoteDemo.o
OUTPUT:=RemoteDemo

OBJS:= *.o
INCLUDED:=	#-I$(LIBRARY) -I$(SOURCE)

CXXFLAGS:= -w -lstdc++ -O2 -std=gnu++11 -Wall -Wextra -g -D_GLIBCXX_RELEASE $(INCLUDED)
LDFLAGS+=-lutil -lpthread
all: clean build clean 

build: $(obj)
	$(CXX) -o $(OUTPUT) $^ $(LDFLAGS)
	chmod +x $(OUTPUT)

run:
	./$(OUTPUT)

clean:
	rm -f build-crt0 *.o */*.o */*/*.o
	rm -rfv objs

%.o: %.cpp
	$(CPP) -c $< -o $@ $(CXXFLAGS)
