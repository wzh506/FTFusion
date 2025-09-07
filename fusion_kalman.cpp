// 节点间频率偏差和秒脉冲的偏差都先用int32
#include <iostream>
#include <vector>
#include <cstdint>

// 简单一维卡尔曼滤波器
class KalmanFilter {
public:
    KalmanFilter(double init_x, double init_p, double q, double r)
        : x(init_x), p(init_p), Q(q), R(r) {}

    double update(double z) {
        // 预测
        // x = x; // 状态转移为常数
        p = p + Q;

        // 更新
        double k = p / (p + R);
        x = x + k * (z - x);
        p = (1 - k) * p;
        return x;
    }

private:
    double x; // 状态估计
    double p; // 估计协方差
    double Q; // 过程噪声
    double R; // 测量噪声
};

int main() {
    int N;
    std::cout << "请输入节点数N: ";
    std::cin >> N;
    std::vector<int32_t> freq_deviation(N);
    std::vector<int32_t> pulse_deviation(N);
    std::cout << "请输入每个节点的频率偏差（int32）: ";
    for (int i = 0; i < N; ++i) {
        std::cin >> freq_deviation[i];
    }
    std::cout << "请输入每个节点的秒脉冲偏差（int32）: ";
    for (int i = 0; i < N; ++i) {
        std::cin >> pulse_deviation[i];
    }

    // 初始化卡尔曼滤波器参数
    double init_x_freq = freq_deviation[0];
    double init_x_pulse = pulse_deviation[0];
    double init_p = 1.0;
    double Q = 1e-3; // 过程噪声
    double R = 1.0;  // 测量噪声

    KalmanFilter kf_freq(init_x_freq, init_p, Q, R);
    KalmanFilter kf_pulse(init_x_pulse, init_p, Q, R);

    double freq_kalman = init_x_freq;
    double pulse_kalman = init_x_pulse;
    for (int i = 0; i < N; ++i) {
        freq_kalman = kf_freq.update(freq_deviation[i]);
        pulse_kalman = kf_pulse.update(pulse_deviation[i]);
    }

    std::cout << "频率偏差卡尔曼滤波估计值: " << freq_kalman << std::endl;
    std::cout << "秒脉冲偏差卡尔曼滤波估计值: " << pulse_kalman << std::endl;
    return 0;
}