# Prediction (24-25)

## Structure

```tree
./src
├── CalibrationMain.cpp
├── Camera
│   ├── Calibration
│   │   ├── Calibration.cpp
│   │   ├── Calibration.hpp
│   │   └── CMakeLists.txt
│   ├── Capture
│   │   ├── CMakeLists.txt
│   │   ├── README.md
│   │   ├── VideoCapture.cpp
│   │   └── VideoCapture.hpp
│   └── CMakeLists.txt
├── CMakeLists.txt
├── Communication
│   ├── CMakeLists.txt
│   ├── SerialPort.cpp
│   └── SerialPort.hpp
├── Detection
│   └── CMakeLists.txt
├── Filter
│   ├── CMakeLists.txt
│   ├── include
│   │   ├── ExtendedKalmanFilter.hpp
│   │   ├── KalmanFilterBase.hpp
│   │   ├── LinearizedMeasurementModel.hpp
│   │   ├── LinearizedSystemModel.hpp
│   │   ├── Matrix.hpp
│   │   ├── MeasurementModel.hpp
│   │   ├── SquareRootBase.hpp
│   │   ├── SquareRootExtendedKalmanFilter.hpp
│   │   ├── SquareRootFilterBase.hpp
│   │   ├── SquareRootUnscentedKalmanFilter.hpp
│   │   ├── StandardBase.hpp
│   │   ├── StandardFilterBase.hpp
│   │   ├── SystemModel.hpp
│   │   ├── Tracker.hpp
│   │   ├── Types.hpp
│   │   ├── UnscentedKalmanFilterBase.hpp
│   │   └── UnscentedKalmanFilter.hpp
│   ├── Predictor.cpp
│   └── Predictor.hpp
├── GetCalibImgs.cpp
├── Main.cpp
├── Pose
│   ├── CMakeLists.txt
│   ├── Pose.cpp
│   ├── Pose.hpp
│   ├── PoseSolver.cpp
│   └── PoseSolver.hpp
├── Settings
│   ├── CMakeLists.txt
│   ├── Config.cpp
│   └── Config.hpp
└── Test.cpp
```

## Dependencies

1. `spdlog`
   + 可以直接通过 `apt` 进行安装：`sudo apt install libspdlog-dev`
2. `ros-<distro>-tf2`
3. `Eigen3`
4. `OpenCV`
   + 可以直接通过 `apt` 进行安装：`sudo apt install libopencv-dev`
5. `MVS Driver`
   + 需要同时安装 SDK（库文件） 和客户端（头文件）

## 编译方法

1. 先 clone 这个 repo：`git clone https://github.com/ArcaLunar/rm-prediction-2425.git`
2. 建立 `cmake-build` 子文件夹用于保存 CMakeCache：`mkdir cmake-build && cd cmake-build`
3. `cmake ..`
4. 编译项目：`cmake --build .`
