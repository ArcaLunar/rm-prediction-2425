# Prediction (24-25)

## Structure

```tree
.
├── bin
│   └── auto_aim
├── CMakeLists.txt
├── compile_commands.json -> /home/arca/Documents/codebases/Prediction2425/build/compile_commands.json
├── config
│   └── mono_calib_data
├── logs
├── README.md
└── src
    ├── CalibrationMain.cpp
    ├── Camera
    │   ├── Calibration
    │   │   ├── Calibration.cpp
    │   │   ├── Calibration.hpp
    │   │   └── CMakeLists.txt
    │   ├── Capture
    │   │   ├── CMakeLists.txt
    │   │   ├── VideoCapture.cpp
    │   │   └── VideoCapture.hpp
    │   └── CMakeLists.txt
    ├── CMakeLists.txt
    ├── Communication
    │   ├── CMakeLists.txt
    │   ├── SerialPort.cpp
    │   └── SerialPort.hpp
    ├── Filter
    │   ├── CMakeLists.txt
    │   ├── KalmanFilter.cpp
    │   ├── KalmanFilter.hpp
    │   ├── UnscentedKalmanFilter.cpp
    │   └── UnscentedKalmanFilter.hpp
    ├── Main.cpp
    ├── Pose
    │   ├── CMakeLists.txt
    │   ├── Pose.cpp
    │   ├── Pose.hpp
    │   ├── PoseSolver.cpp
    │   └── PoseSolver.hpp
    ├── Settings
    │   ├── CMakeLists.txt
    │   ├── Constants.cpp
    │   └── Constants.hpp
    └── Test.cpp
```

## Dependencies

1. `spdlog`
2. `ros-<distro>-tf2`
3. `Eigen3`
4. `OpenCV`
5. `MVS Driver`
