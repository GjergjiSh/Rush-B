PRJ_PATH = -I./bus/arduino-link/ \
           -I./bus/video/ \
		   -I./bus/zmq/ \
		   -I./bus/ \
		   -I/usr/include/gstreamer-1.0 \
		   -I/usr/include/glib-2.0 \
		   -I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
           -I../protobuf \
           -I. \
			-I/usr/lib64/glib-2.0/include\
			-I/usr/lib/arm-linux-gnueabihf/glib-2.0/include/ \
			-I/usr/local/include/zmqpp \


OBJ_PATH = ./obj

BUILD_PATH = ./build

POST_BUILD = @mv

OBJ_PRJ = $(OBJ_PATH)/Bus.o $(OBJ_PATH)/ZMQPipeline.o $(OBJ_PATH)/VideoPipeline.o $(OBJ_PATH)/RushB.o $(OBJ_PATH)/Main.o $(OBJ_PATH)/PBDriverWish.o $(OBJ_PATH)/ArduinoLink.o

CC = g++ -std=c++17 -static-libgcc -static-libstdc++ -fPIC $(PRJ_PATH) -Wall -O2 -Wno-comment -Wno-deprecated-declarations -pthread -c

LD = g++ -static-libgcc -static-libstdc++ -Wall -Wl,--copy-dt-needed-entries

LIB_PRJ = -lzmq -lprotobuf -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 -lgstapp-1.0 -ldl -lpthread -lCppLinuxSerial

all: $(OBJ_PATH) $(BUILD_PATH)  RushB $(POST_BUILD)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

$(POST_BUILD):
	$(POST_BUILD) RushB $(BUILD_PATH)

RushB: $(OBJ_PRJ)
	$(LD) $(OBJ_PRJ) $(LIB_PRJ) -o RushB

$(OBJ_PATH)/Main.o: ./Main.cpp
	$(CC) -o $@ $?

$(OBJ_PATH)/Bus.o: ./bus/RBus.cpp
	$(CC) -o $@ $?

$(OBJ_PATH)/ZMQPipeline.o: ./bus/zmq/RZMQPipeline.cpp
	$(CC) -o $@ $?

$(OBJ_PATH)/VideoPipeline.o: ./bus/video/RVideoPipeline.cpp
	$(CC) -o $@ $?

$(OBJ_PATH)/ArduinoLink.o: ./bus/arduino-link/ArduinoLink.cpp
	$(CC) -o $@ $?

$(OBJ_PATH)/RushB.o: ./RushB.cpp
	$(CC) -o $@ $?

$(OBJ_PATH)/PBDriverWish.o: ../protobuf/PBDriverWish.pb.cc
	$(CC) -o $@ $?



clean:
	rm -f -v -R $(OBJ_PATH)
	rm -f -v -R $(BUILD_PATH)
