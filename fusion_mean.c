// 节点间频率偏差和秒脉冲的偏差都先用int32，均值计算，纯C实现
#include <stdio.h>
#include <stdint.h>

// 这里的输入需要改为直接接受，不能用这种命令行形式
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

    int64_t freq_sum = 0, pulse_sum = 0;
    for (int i = 0; i < N; ++i) {
        freq_sum += freq_deviation[i];
        pulse_sum += pulse_deviation[i];
    }

    double freq_avg = (double)freq_sum / N;
    double pulse_avg = (double)pulse_sum / N;

    printf("频率偏差均值: %f\n", freq_avg);
    printf("秒脉冲偏差均值: %f\n", pulse_avg);
    return 0;
}