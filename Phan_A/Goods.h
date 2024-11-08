#pragma once 

#include <string>
#include <iostream>
using namespace std;

class Goods {
private:
	int maHangHoa;
	string tenHangHoa;
	string danhMuc;
	int giaBan;
	int soLuongTonKho;
public:
	Goods();
	Goods(int ma, string ten, string muc, int gia, int soluong);

	int getMaHangHoa() const;
	int getSoLuongTonKho() const;
	string getTenHangHoa() const;
	string getDanhMuc() const;
	int getGiaBan() const;

	void setThongTin(int ma, string ten, string muc, int gia, int soluong);
	void setsoLuongTonKho(int sl);

	friend bool operator<(const Goods& g1, const Goods& g2);
	friend istream& operator>>(istream& is, Goods& goods);
	friend ostream& operator<<(ostream& os, const Goods& goods);
};
