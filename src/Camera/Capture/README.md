# `Capture` 启动流程

## `HikCamera` 海康威视工业相机

1. 使用 `HikCamera` 创建变量后**自动调用构造函数**
2. 在构造函数里：
   1. 先初始化 SDK
   2. 枚举设备、找到海康相机（同时输出信息） `__EnumDevices(), __DebugDevices()`
   3. 为找到的海康相机创建 Handle `__CreateHandle()`
   4. 打开相机 `__OpenCamera()`
   5. 进行相机参数的初始化 `__Setup()`
   6. 初始化图像捕获 `__Init`
3. 然后就完成了初始化相机类
