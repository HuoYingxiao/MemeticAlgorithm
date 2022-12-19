#pragma once
class Item
{
public:
	Item(int index);
	void setValue(double value);
	void setWeight(double weight);
	double getValue();
	double getWeight();
	Item* clone();
private:
	int index;
	double Value;
	double Weight; 
};

