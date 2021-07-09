# Rush-B

Source for the Rush-B Remote Controlled Robot.

The goal of the project is divided into 4 phases.

- Phase 1: Build a 2 wheeled robot which can be remote controlled from a standalone binary and transmit video data
- Phase 2: Implement simple image recognition - The robot is able to detect faces and react when a face is detected
- Phase 3: Implement SLAM - The robot is able to detect faces and determine its position relative to the detected face
- Phase 4: Autonomous mode - The robot can follow the detected faces around autonomously

# Dependencies

1. ZeroMQ
2. Google Protobuf
3. GStreamer
4. OpenCV
5. gcc/g+
6. Make
7. Arduino ServoLib ?

**Note**: Please install [Drawio]() to view the .drawio design diagrams in the docs directory

# Software components

1. Control Center (Linux): Sends movement commands to the robot and displays a live stream of the robots camera
2. Rush-B: (RasPi): Streams the webcamera of the robot and sends the received movement commands from the control center to the arduino
3. Rush-B.ino (Arduino): Receives the commands from the Rush-B (RasPi) component and controls the servos of the robot


# Hardware components

1. Arduino UNO
2. Rasberry Pi
3. Servomotors (3x)
4. Generic Webcamera
5. Generic Keyboard
6. xBox 360 controller
7. Custom 3d printed parts (Models can be found [here](3d-parts-design))

# Build

1. Control Center - cd src/control-center && make
2. Rush-B (RasPi) - cd src/rush-b && make

# Configure

1. Control Center -
2. Rush-B (RasPi) -

# Run

1. Control Center - cd build && ./control-center
2. Rush-B (RasPi) - cd build && ./rush-b

**Note**: The input mappings can be found [here]()

# Current State of the project

**Phase 1**

The project is still in its design phase. The Control Center is suggested as a starting point as the component has no hardware dependencies (Arduino/raspi etc)

# Changelog
The changelog can be found [here]()