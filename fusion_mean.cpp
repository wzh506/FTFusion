// 节点间频率偏差和秒脉冲的偏差都先用int32
#include <iostream>
#include <vector>
#include <cstdint>

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
	int64_t freq_sum = 0, pulse_sum = 0;
	for (int i = 0; i < N; ++i) {
		freq_sum += freq_deviation[i];
		pulse_sum += pulse_deviation[i];
	}
	double freq_avg = static_cast<double>(freq_sum) / N;
	double pulse_avg = static_cast<double>(pulse_sum) / N;
	std::cout << "频率偏差均值: " << freq_avg << std::endl;
	std::cout << "秒脉冲偏差均值: " << pulse_avg << std::endl;
	return 0;
}





