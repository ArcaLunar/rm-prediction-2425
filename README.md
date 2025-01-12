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

## 后续开发计划

+ `AimBot` 类负责所有自瞄职责，下分三种模式，每种模式有各自的类。
  + `Capture` 模式：捕获图像；根据识别结果（什么兵种）~会考虑优先级策略~进行转发；包含解算、封装为结构体；
  + `WindMill` 模式：大符、小符。
  + `OutPost` 模式：前哨站。
  + `General` 模式：所有其他兵种。
    + `General` 类包含内置的滤波器，流程：
      1. 初始化滤波器，然后等待直到有数据~考虑使用锁等结构实现同一时刻只关心一个目标，或者考虑优先级策略~
      2. 主动获取转发的数据进行滤波过程
      3. 根据滤波出的小车中心、转速、子弹射程等因素，计算击打参数
      4. 将击打参数发送给电控
      5. 一旦失踪时间超过定值，则回到 step 1。
