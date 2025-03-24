#include <iostream>
using namespace std;

enum CPU_Rank {CP1 = 1, CP2, CP3, CP4, CP5, CP6, CP7};
enum TYPE {DDR1 = 1, DDR2, DDR3, DDR4, DDR5};
enum INTERFACE {SATA = 1, USB};
enum MODE {external = 1, build_in};

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
class RAM {
	private:

		TYPE rank;
		int capacity;
		float frequency;

	public:

		RAM(TYPE r, int c, float f): rank(r), capacity(c), frequency(f) {
			cout << "构建了一个RAM" << endl;
		}
		~RAM() {
			cout << "析构了一个RAM" << endl;
		}

		void run() {
			cout << "RAM is running ." << endl;
		}
		void stop() {
			cout << "RAM is stop running ." << endl;
		}
};
class CDROM {
	private:

		INTERFACE rank;
		int capacity;
		MODE mode;

	public:

		CDROM(INTERFACE r, int c, MODE m): rank(r), capacity(c), mode(m) {
			cout << "构建了一个CDROM" << endl;
		}
		~CDROM() {
			cout << "析构了一个CDROM" << endl;
		}

		void run() {
			cout << "CDROM is running ." << endl;
		}
		void stop() {
			cout << "CDROM is stop running ." << endl;
		}
};
class Computer {
	private:

		CPU cpu;
		RAM ram;
		CDROM cdrom;

	public:
		Computer(CPU_Rank r1, int f1, float v1, TYPE r2, int f2, float v2, INTERFACE r3, int f3, MODE v3): cpu(r1, f1, v1),
			ram(r2, f2, v2), cdrom(r3, f3, v3) {
			cout << "构建了一个COMPUTER" << endl;
		}
		~Computer() {
			cout << "析构了一个COMPUTER" << endl;
		}
		void run();
		void stop();
};

void Computer::run() {
	cpu.run();
	ram.run();
	cdrom.run();
	cout << "Computer is running ." << endl;
}

void Computer::stop() {
	cpu.stop();
	ram.stop();
	cdrom.stop();
	cout << "Computer is stop running ." << endl;
}

int main() {
	Computer rog(CP1, 1, 1.0f, DDR1, 1, 1.0f, SATA, 1, external);
	rog.run();
	rog.stop();
	return 0;
}