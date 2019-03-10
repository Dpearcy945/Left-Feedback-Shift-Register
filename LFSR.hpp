
#ifndef LFSR_HPP
#define LFSR_HPP

using namespace std;

class LFSR{
public:
	LFSR(string reg, int k);
	int to_int(int element);
	int step();
	int generate(int k);
	friend ostream& operator <<(ostream& out, const LFSR &oLFSR);
private:
	string seed;
	int tap;
	int front;
	int back;
	int longness;
	int gen_num;
};


#endif