#include "ListOfGoods.h"
#include "Goods.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;


	list<Goods*>& ListOfGoods::getList() { return ListGoods; }

	bool ListOfGoods::empty() {
		return ListGoods.empty();
	}
	
	bool ListOfGoods::soTen(Goods* a, Goods* b) {
		return a->getTenHangHoa() < b->getTenHangHoa();
	}

	bool ListOfGoods::soSoLuong(Goods* a, Goods* b) {
		return a->getSoLuongTonKho() < b->getSoLuongTonKho();
	}

	void ListOfGoods::themMatHang( const Goods& hang ) {
		Goods* newHang = new Goods(hang);
		ListGoods.push_back(newHang);
	}

	void ListOfGoods::xoaMatHang(string key, bool searchByName = false) {
		try
		{
			auto it = std::find_if(ListGoods.begin(), ListGoods.end(),
				[key, searchByName](Goods* hang) {
					if (searchByName) {
						return hang->getTenHangHoa() == key;
					}
					else {
						return hang->getMaHangHoa() == stoi(key); //stoi: string to int, chuyen doi chuoi ki tu thanh so nguyen
					}
				});
			if (it != ListGoods.end()) {
				delete* it;
				ListGoods.erase(it);
				cout << "Da xoa mat hang khoi he thong\n";
			}
			else {
				cout << "Khong tim thay mat hang\n";
			}
		}
		catch (const invalid_argument) // loi neu khong dung duoc stoi
		{
			cout << "Ma hang hoa khong hop le !\n";
		}
	}

	void ListOfGoods::hienThiMatHang(string key, bool searchByName = false) {
		cout << left
			<< setw(15) << "Ma hang hoa"
			<< setw(20) << "Ten hang hoa"
			<< setw(20) << "Danh muc"
			<< setw(15) << "Gia ban"
			<< setw(20) << "So luong ton kho" << "\n";
		cout << string(90, '-') << "\n";

		for (const auto& newHang : ListGoods) {
			if (!searchByName) {
				if (newHang->getMaHangHoa() == stoi(key)) {
					cout << *newHang << "\n";
				}
			}
			else {
				if (newHang->getTenHangHoa() == key) {
					cout << *newHang << "\n";
				}
			}
		}
	}

	void ListOfGoods::suaThongTinMatHang(string key, bool searchByName = false) {
		auto it = std::find_if(ListGoods.begin(), ListGoods.end(),
			[key, searchByName](Goods* hang) {
				if (searchByName) {
					return hang->getTenHangHoa() == key;
				}
				else {
					return hang->getMaHangHoa() == stoi(key); 
				}
			});
		if (it != ListGoods.end()) {
			int ma, gia, soluong;
			string muc, ten;
			cout << "Nhap ma hang hoa: "; cin >> ma; cin.ignore();
			cout << "Nhap ten hang hoa: "; getline(cin, ten);
			cout << "Nhap danh muc: "; getline(cin, muc);
			cout << "Nhap gia ban: "; cin >> gia;
			cout << "Nhap so luong ton kho: "; cin >> soluong;
			(*it)->setThongTin(ma, ten, muc, gia, soluong);
			cout << "Da cap nhat thong tin mat hang\n";
		}
		else {
			cout << "Khong the tim thay mat hang";
		}
	}

	void ListOfGoods::timKiemMatHang(string key, bool searchByName = false) {
		try
		{
			auto it = std::find_if(ListGoods.begin(), ListGoods.end(),
				[key, searchByName](Goods* hang) {
					if (searchByName) {
						return hang->getTenHangHoa() == key;
					}
					else {
						return hang->getMaHangHoa() == stoi(key); //stoi: string to int, chuyen doi chuoi ki tu thanh so nguyen
					}
				});
			if (it != ListGoods.end()) {
				cout << "Da tim thay hang hoa\n";
				cout << string(90, '-') << "\n";
				cout << **it << "\n";
			}
			else {
				cout << "Khong tim thay mat hang\n";
			}
		}
		catch (const invalid_argument) // loi neu khong dung duoc stoi
		{
			cout << "Ma hang hoa khong hop le !\n";
		}
	}

	void ListOfGoods::hienThiDanhSach() {
		cout << left
			<< setw(15) << "Ma hang hoa"
			<< setw(20) << "Ten hang hoa"
			<< setw(20) << "Danh muc"
			<< setw(15) << "Gia ban"
			<< setw(20) << "So luong ton kho" << "\n";
		cout << string(90, '-') << "\n";

		for (const auto& newHang : ListGoods) {
			cout << *newHang << "\n";
		}
	}

	void ListOfGoods::sapXepHangHoa(int choice) {
		switch (choice) {
		case 1: {
			ListGoods.sort([](Goods* a, Goods* b) {
				return *a < *b;
				});
			break;
		}
		case 2: {
			ListGoods.sort([](Goods* a, Goods* b) {
				return a->getTenHangHoa() < b->getTenHangHoa();
				});
			break;
		}
		case 3: {
			ListGoods.sort([](Goods* a, Goods* b) {
				return a->getSoLuongTonKho() < b->getSoLuongTonKho();
				});
			break;
		}
		}
	}