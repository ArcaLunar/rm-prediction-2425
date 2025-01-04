#ifndef __SERIAL_PORT_HPP__
#define __SERIAL_PORT_HPP__

/**
 * @file SerialPort.hpp
 * @author arca@connect.hku.hk
 * @brief 与串口通信，based on NautilusSerialPort.hpp
 * @version 0.1
 * @date 2025-01-04
 *
 * @copyright Copyright (c) 2025
 *
 */

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LOGGER_TRACE // 设置为输出文件名和行号

#include <spdlog/spdlog.h>

#include <cstdint>

#pragma pack(push, 1)
struct VisionPLCSendMsg {
    uint8_t m_FrameHead = 0xA3;
    float m_Pitch{};
    float m_Yaw{};
    uint8_t m_FlagFound{};       // 找到敌人
    uint8_t m_FlagFire{};        // 开火控制
    uint8_t m_FlagDoneFitting{}; // 是否建模拟合完成
    uint8_t m_FlagPatrolling{};  // 哨兵云台是否进入巡逻模式

    // 在每次发送时都取反（0/1）。电控用来判断该帧消息是否最新
    uint8_t m_FlagUpdated{};

    uint8_t m_FrameTail = 0xAA;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct VisionPLCRecvMsg {
    uint8_t m_FrameHead = 0x3A;
    float m_ImuRoll{};
    float m_ImuPitch{};
    float m_ImuYaw{};
    uint8_t m_MyColor{}; // 0 未知, 1 红, 2 蓝
    uint8_t
        m_VisionMode{}; // 0视觉待机  1自瞄装甲板  2小能量机关  3大能量机关
    struct armor_select_t {
        uint8_t m_Hero : 1;
        uint8_t m_Engineer : 1;
        uint8_t m_Infantry3 : 1;
        uint8_t m_Infantry4 : 1;
        uint8_t m_Infantry5 : 1;
        uint8_t m_Sentry : 1;
        uint8_t m_Outpost : 1;
        uint8_t m_Base : 1;
    } m_ShootDecision{};
    uint8_t m_FrameTail = 0xAA;
};
#pragma pack(pop)

// -----------------------------
// Constants
// -----------------------------
constexpr size_t kSendBufSize = sizeof(VisionPLCSendMsg);
constexpr size_t kRecvMsgSize = sizeof(VisionPLCRecvMsg);
constexpr size_t kRecvBufSize = kRecvMsgSize * 10; // 缓冲区大小
using RawBufRecv = std::array<uint8_t, kRecvBufSize>; // 缓冲区数组

class SerialPort {
  public:
    SerialPort() {}
    ~SerialPort() {}

    bool OpenPort(const std::string &portname, int baudrate, char parity,
                  char databit, char stopbit, char synchronizeflag = 1);

    void ClosePort() {}

    bool Send(const VisionPLCSendMsg &payload);

    // 检查接收帧中下标范围为[begin, end)的部分是否符合MsgType协议
    template <typename MsgType>
    bool VerifyFrame(const RawBufRecv &buf, size_t begin, size_t end);

    void ReadRawBuf();

    void ProcRawBuf();

    void CheckAndReconnect(); // 如果连续timeout
                              // ms没有收到任何消息，尝试连接其他预设的串口
};

#endif