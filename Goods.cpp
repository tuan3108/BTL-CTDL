#include "Goods.h"
#include <iomanip>
using namespace std;

Goods::Goods() {}
Goods::Goods(int ma, string ten, string muc, int gia, int soluong) :maHangHoa(ma), tenHangHoa(ten), danhMuc(muc), giaBan(gia), soLuongTonKho(soluong) {}

	int Goods::getMaHangHoa() const { return maHangHoa; }
	string Goods::getTenHangHoa() const { return tenHangHoa; }
	string Goods::getDanhMuc() const { return danhMuc; }
	int Goods::getSoLuongTonKho() const { return soLuongTonKho; }
	int Goods::getGiaBan() const { return giaBan;  }
	

	void Goods::setThongTin(int ma, string ten, string muc, int gia, int soluong) {
		maHangHoa = ma;
		tenHangHoa = ten;
		danhMuc = muc;
		giaBan = gia;
		soLuongTonKho = soluong;
	}


	void Goods::setsoLuongTonKho(int sl) {
		soLuongTonKho = sl;
	}

	bool operator<(const Goods& g1, const Goods& g2) {
		return g1.getGiaBan() < g2.getGiaBan();
	}

	istream& operator>>(istream& is, Goods& goods) {
		is >> goods.maHangHoa;
		is.ignore();
		getline(is, goods.tenHangHoa);
		getline(is, goods.danhMuc);
		is >> goods.giaBan;
		is >> goods.soLuongTonKho;
		return is;
	}


	ostream& operator<<(ostream& os, const Goods& goods) {
		os  << left 
			<< setw(15) << goods.maHangHoa
			<< setw(20) << goods.tenHangHoa
			<< setw(20) << goods.danhMuc
			<< setw(15) << goods.giaBan
			<< setw(20) << goods.soLuongTonKho;
		return os;
	}
	