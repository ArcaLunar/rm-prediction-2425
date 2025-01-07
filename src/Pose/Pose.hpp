#ifndef __POSE_HPP__
#define __POSE_HPP__

struct IMU_Pose {
    double roll;
    double pitch;
    double yaw;

    IMU_Pose(double imu_roll = 0.0, double imu_pitch = 0.0,
             double imu_yaw = 0.0)
        : roll(imu_roll), pitch(imu_pitch), yaw(imu_yaw) {}

    static double GetPitch(double x, double y, double v);
};

#endif