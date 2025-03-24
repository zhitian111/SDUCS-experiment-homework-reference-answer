#include <iostream>
using namespace std;

enum CPU_Rank {P1 = 1, P2, P3, P4, P5, P6, P7};

class CPU {
	private:

		CPU_Rank rank;
		int frequency;
		float voltage;

	public:

		CPU(CPU_Rank r, int f, float v): rank(r), frequency(f), voltage(v) {
			cout << "构建了一个CPU" << endl;
		}
		~CPU() {
			cout << "析构了一个CPU" << endl;
		}

		void run() {
			cout << "CPU is running ." << endl;
		}
		void stop() {
			cout << "CPU is stop running ." << endl;
		}


};


int main() {
	CPU Inter_i9_13980hx(P1, 2200, 1.2);
	Inter_i9_13980hx.run();
	Inter_i9_13980hx.stop();
	return 0;
}