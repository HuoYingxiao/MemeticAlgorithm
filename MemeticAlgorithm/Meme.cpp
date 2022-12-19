#include "Meme.h"


Meme::Meme(int option, int numberOfStates) 
	:option(option)
	,maxNumber(numberOfStates){

}

int Meme::getMemeOption(){
	return this->option;
}

bool Meme::setMemeOption(int option) {
	if (option < this->maxNumber)
		this->option = option;
	return option < this->maxNumber;
}

int Meme::getNumberOfOption() {
	return this->maxNumber;
}