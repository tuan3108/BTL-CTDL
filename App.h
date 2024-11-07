#pragma once

#include "ListOfGoods.h"

class App {
private:
	ListOfGoods ListGoods;
	void disPlayMenu();
	void addGoods();
	void removeGoods();
	void editGoods();
	void disPlayGoods();
	void searchGoods();
	void sortGoods();
public:
	void run();
};


