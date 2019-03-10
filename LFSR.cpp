#include <iostream>
#include <string>
#include "LFSR.hpp"
#include <stdlib.h>
#include <math.h>


//The constructor that is hopefully used
LFSR::LFSR(string reg, int k)
{
	seed = reg;
	longness = seed.length();
	tap = (longness-1)-k;

	front = 0;
	back = longness - 1;
}
int LFSR::step()
{
	char exclusive;
	int ex;

	if(seed.at(front) == seed.at(tap)){
		exclusive = '0';
		ex = 0;	
	}
	if(seed.at(front) != seed.at(tap))
	{	
		exclusive = '1';
		ex = 1;
	}
	//move everything to the right, or rather the reference elements for the front, back, and k
	front += 1;
	back += 1;
	tap += 1;

	if(front >= longness)
		front = 0;
	if(back >= longness)
		back = 0;
	if(tap >= longness)
		tap = 0;
	//puts the Xor'd ting in the back
	seed[back] = exclusive;

	return ex;

}
//for when you want the char to be an integer and don't feel like dealing
//with that long chain to casting to do so
int LFSR::to_int(int element)
{	
	if(seed[element] == '1')
		return 1;
	else
		return 0;
}
int LFSR::generate(int k)
{
	int number = 0;
	//int walk = back; old variable

	//this will get the number by multiplying the number, which 
	// stars at 0, by 2 and performing a step and adding the right
	//most bit to the number. alternating b/w odd and even numbers. 
	for(int i = 1; i <= k; i++)
	{
		number *= 2;
		number += step();
		
	}
	
	
	return number;
}
ostream& operator<< (ostream& out, const LFSR &oLFSR)
{
	int walk = oLFSR.front;
	for(int i = 0 ; i < oLFSR.longness; walk++){
		
		if(walk >= oLFSR.longness)
			walk = 0;

		out << oLFSR.seed[walk];
		i++;
	}

	return out;
}