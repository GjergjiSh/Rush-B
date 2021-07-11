PRJ_PATH = -I./subscriber/video \
           -I./publisher/serializer \
		   -I/usr/include/gstreamer-1.0 \
		   -I/usr/include/glib-2.0 \
		   -I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
           -I../protobuf \
           -I./subscriber \
           -I./publisher \
		   -I./device \
           -I.

OBJ_PATH = ./obj

BUILD_PATH = ./build

POST_BUILD = @mv

OBJ_PRJ = $(OBJ_PATH)/Keyboard.o $(OBJ_PATH)/Controller.o $(OBJ_PATH)/VideoPipeline.o $(OBJ_PATH)/Publisher.o $(OBJ_PATH)/Subscriber.o $(OBJ_PATH)/ControlCenter.o $(OBJ_PATH)/Main.o $(OBJ_PATH)/PBDriverWish.o

CC = g++ -std=c++17 -static-libgcc -static-libstdc++ -fPIC $(PRJ_PATH) -m64 -msse2 -Wall -O2 -Wno-comment -Wno-deprecated-declarations -pthread -c

LD = g++ -static-libgcc -static-libstdc++ -m64 -Wall -Wl,--copy-dt-needed-entries

LIB_PRJ = -lzmq -lprotobuf -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 -lgstapp-1.0 -ldl -lpthread

all: $(OBJ_PATH) $(BUILD_PATH)  ControlCenter $(POST_BUILD)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

$(POST_BUILD):
	$(POST_BUILD) ControlCenter $(BUILD_PATH)

ControlCenter: $(OBJ_PRJ)
	$(LD) $(OBJ_PRJ) $(LIB_PRJ) -o ControlCenter

$(OBJ_PATH)/Main.o: ./Main.cpp
	$(CC) -o $@ $?

$(OBJ_PATH)/Keyboard.o: ./device/Keyboard.cpp
	$(CC) -o $@ $?

$(OBJ_PATH)/Controller.o: ./device/Controller.cpp
	$(CC) -o $@ $?

$(OBJ_PATH)/VideoPipeline.o: ./subscriber/video/VideoPipeline.cpp
	$(CC) -o $@ $?

$(OBJ_PATH)/Publisher.o: ./publisher/Publisher.cpp
	$(CC) -o $@ $?

$(OBJ_PATH)/Subscriber.o: ./subscriber/Subscriber.cpp
	$(CC) -o $@ $?

$(OBJ_PATH)/ControlCenter.o: ./ControlCenter.cpp
	$(CC) -o $@ $?

$(OBJ_PATH)/PBDriverWish.o: ../protobuf/PBDriverWish.pb.cc
	$(CC) -o $@ $?

clean:
	rm -f -v -R $(OBJ_PATH)
	rm -f -v -R $(BUILD_PATH)
