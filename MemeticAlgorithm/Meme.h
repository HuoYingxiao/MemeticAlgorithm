#pragma once
class Meme
{
	
public:
	Meme(int option, int numberOfStates);
	int getMemeOption();
	bool setMemeOption(int option);
	int getNumberOfOption();
private:
	int option;
	int maxNumber;
	
};

