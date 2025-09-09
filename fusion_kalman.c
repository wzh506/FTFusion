// 节点间频率偏差和秒脉冲的偏差都先用int32，卡尔曼滤波，纯C实现
#include <stdio.h>
#include <stdint.h>

// 简单一维卡尔曼滤波器结构体
typedef struct {
    double x; // 状态估计
    double p; // 估计协方差
    double Q; // 过程噪声
    double R; // 测量噪声
} KalmanFilter;

// 初始化卡尔曼滤波器
void KalmanFilter_init(KalmanFilter* kf, double init_x, double init_p, double q, double r) {
    kf->x = init_x;
    kf->p = init_p;
    kf->Q = q;
    kf->R = r;
}

// 更新卡尔曼滤波器
double KalmanFilter_update(KalmanFilter* kf, double z) {
    // 预测
    kf->p = kf->p + kf->Q;

    // 更新
    double k = kf->p / (kf->p + kf->R);
    kf->x = kf->x + k * (z - kf->x);
    kf->p = (1 - k) * kf->p;
    return kf->x;
}

int main() {
    int N;
    printf("请输入节点数N: ");
    scanf("%d", &N);

    int32_t freq_deviation[N];
    int32_t pulse_deviation[N];

    printf("请输入每个节点的频率偏差（int32）: ");
    for (int i = 0; i < N; ++i) {
        scanf("%d", &freq_deviation[i]);
    }
    printf("请输入每个节点的秒脉冲偏差（int32）: ");
    for (int i = 0; i < N; ++i) {
        scanf("%d", &pulse_deviation[i]);
    }

    // 初始化卡尔曼滤波器参数
    double init_x_freq = freq_deviation[0];
    double init_x_pulse = pulse_deviation[0];
    double init_p = 1.0;
    double Q = 1e-3;
    double R = 1.0;

    KalmanFilter kf_freq, kf_pulse;
    KalmanFilter_init(&kf_freq, init_x_freq, init_p, Q, R);
    KalmanFilter_init(&kf_pulse, init_x_pulse, init_p, Q, R);

    double freq_kalman = init_x_freq;
    double pulse_kalman = init_x_pulse;
    for (int i = 0; i < N; ++i) {
        freq_kalman = KalmanFilter_update(&kf_freq, freq_deviation[i]);
        pulse_kalman = KalmanFilter_update(&kf_pulse, pulse_deviation[i]);
    }

    printf("频率偏差卡尔曼滤波估计值: %f\n", freq_kalman);
    printf("秒脉冲偏差卡尔曼滤波估计值: %f\n", pulse_kalman);
    return 0;
}