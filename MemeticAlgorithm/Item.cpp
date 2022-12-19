#include "Item.h"

Item::Item(int index)
	:index(index) 
	,Value(0)
	,Weight(0){

}

void Item::setValue(double Value) {
	this->Value = Value;
}

void Item::setWeight(double Weight) {
	this->Weight = Weight;
}

double Item::getValue() {
	return this->Value;
}

double Item::getWeight() {
	return this->Weight;
}

Item* Item::clone() {
	Item* newItem = new Item(this->index);
	newItem->setValue(this->Value);
	newItem->setWeight(this->Weight);
	return newItem;
}