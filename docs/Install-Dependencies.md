# Base

1. sudo apt-get install autoconf automake libtool curl make g++ unzip cmake


# Pugixml

1. sudo apt-get install -y libpugixml-dev

# G-Streamer

1. sudo apt-get install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-pulseaudio

# Protobuf

1. git clone https://github.com/protocolbuffers/protobuf.git
2. cd protobuf
3. git submodule update --init --recursive
4. ./autogen.sh
5. ./configure
6. make
7. make check
8. sudo make install
9. sudo ldconfig # refresh shared library cache.


# CppLinuxSerial

1. git clone https://github.com/gbmhunter/CppLinuxSerial.git
2. cd CppLinuxSerial
3. mkdir build
4. cd build
5. cmake ..
6. make
7. sudo make install
8. make run_unit_tests

# ZMQ & ZMQPP

## libsodium
1. sudo apt-get install -y libsodium-dev

## zmq
1. git clone git://github.com/zeromq/libzmq.git
2. cd libzmq
3. ./autogen.sh
4. ./configure –with-libsodium && make
5. sudo make install
6. sudo ldconfig

## zmqpp
1. git clone git://github.com/zeromq/zmqpp.git
2. cd zmqpp
3. make
4. make check
5. sudo make install
6. make installcheck

## cppzmq
1. git clone https://github.com/zeromq/cppzmq.git
2. cd cppzmq
3. mkdir build && cd build
4. cmake ..
5. sudo make -j4 install

# Python Dependencies

1. cd py-modules
2. pip install -r requirements.txt









