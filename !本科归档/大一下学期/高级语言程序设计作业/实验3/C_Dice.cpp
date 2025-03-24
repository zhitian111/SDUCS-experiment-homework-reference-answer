#include <iostream>
#include <cstdlib>

enum GameStatus {WIN, LOSE, PLAYING};
using namespace std;

class Dice {
	private:
		GameStatus status;
		int sum;
		unsigned int seed;
		int mark_point;
	public:
		Dice() {
			seed = 1;
			sum = 0;
			status = PLAYING;
			mark_point = 0;
		}
		void setseed(unsigned int seeed);
		void roll();
		void check1();
		void play();
};

void Dice::setseed(unsigned int seeed) {
	this->seed = seeed;
	srand(this->seed);
}
void Dice::roll() {
	int die1 = 1 + rand() % 6;
	int die2 = 1 + rand() % 6;
	sum = die1 + die2;
	std::cout << "player rolled " << die1 << "+" << die2 << "=" << sum << std::endl;
}

void Dice::check1() {
	switch (this->sum) {
		case 7:
		case 11:
			this->status = WIN;
			break;
		case 2:
		case 3:
		case 12:
			this->status = LOSE;
			break;
		default:
			this->status = PLAYING;
			this->mark_point = this->sum;
			std::cout << "point is " << this->mark_point << std::endl;
			break;
	}

}

void Dice::play() {
	this->roll();
	this->check1();
	while (this->status == PLAYING) {
		this->roll();
		if (this->sum == this->mark_point) {
			this->status = WIN;
		} else if (this->sum == 7) {
			this->status = LOSE;
		}
	}
	if (this->status == WIN)
		std::cout << "player wins" << std::endl;
	else
		std::cout << "player loses" << std::endl;
}

int main() {
	Dice dice;
	unsigned seed;
	std::cout << "Please enter an unsigned integer:";
	std::cin >> seed;
	dice.setseed(seed);
	dice.play();
	return 0;
}
