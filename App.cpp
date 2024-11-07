#include "App.h"
#include <iostream>
#include <fstream>
#include "ListOfGoods.h"
#include <algorithm>

	void App::run() {
		int choice;
		do {
			disPlayMenu();
			cin >> choice;
			cin.ignore();
			switch (choice) {
			case 1: addGoods(); break;
			case 2: removeGoods(); break;
			case 3: editGoods(); break;
			case 4: disPlayGoods(); ; break;
			case 5: searchGoods(); break;
			case 6: sortGoods(); break;
			case 0: cout << "Tam Biet!\n"; break;
			default: cout << "Lua chon khong hop le, vui long chon lai.\n";
			}
		} while (choice != 0);
	}

	void App::disPlayMenu() {
		cout << "=== QUAN LY HANG HOA===\n";
		cout << "1. Them mat hang\n";
		cout << "2. Xoa mat hang\n";
		cout << "3. Sua thong tin mat hang\n";
		cout << "4. Hien thi danh sach hang hoa\n";
		cout << "5. Tim kiem mat hang\n";
		cout << "6. Sap xep danh sach hang hoa\n";
		cout << "0. Thoat\n";
		cout << "============================\n";
		cout << "Vui long nhap lua chon cua ban : ";
	}

	void App::addGoods() {
		int choice;
		do {
			system("cls");
			cout << "===THEM MAT HANG===\n";
			cout << "1. Nhap thu cong\n";
			cout << "2. Nhap tu file\n";
			cout << "Ban muon nhap thong tin nhu the nao : ";
			cin >> choice;
			cin.ignore();
			switch (choice) {
			case 1: { 
				Goods newGoods;
				cout << "\nBan muon them bao nhieu mat hang: ";
				int a; cin >> a;
				for (int i = 0; i < a; i++)
				{
					cout << "\nNhap thong tin mat hang thu " << i + 1 << ":\n";
					cout << "(Ma, ten, danh muc, gia, soluong)\n";
					cin >> newGoods;
					ListGoods.themMatHang(newGoods);
				}
				choice = 0;
				system("cls");
				break;
			}
			case 2: {
				string tenFile;
				cout << "Nhap ten file: ";
				getline(cin, tenFile);
				ifstream inFile(tenFile);
				if (!inFile.is_open()) {
					cout << "Khong tim thay file\n";
				}
				else {
					int n;
					if (!(inFile >> n)) {
						cout << "Loi khi doc so luong mat hang!\n";
						inFile.close();
						break;
					}
					inFile.ignore();
					for (int i = 0; i < n; i++)
					{
						Goods tempGoods;
						if (!(inFile >> tempGoods)) {
							cout << "Loi khi doc mat hang thu " << i + 1 << endl;
							break;
						}
						ListGoods.themMatHang(tempGoods);
					}
					cout << "Da nhap thong tin thanh cong!\n\n";
					inFile.close();
					choice = 0;
					break;
				}
			}
			default: cout << "Lua chon khong hop le, vui long chon lai.\n";
			}
		} while (choice != 0);
	}

	void App::removeGoods() {
		int choice;
		system("cls");
		cout << "===XOA MAT HANG===\n";
		cout <<"1. Theo ma hang hoa\n2. Theo ten hang hoa \n"<< "Ban muon xoa theo ten hay theo ma hang hoa: ";
		cin >> choice;
		cin.ignore();
		switch (choice)
		{
		case 1: {
			string maHH;
			cout << "Nhap ma hang hoa ban muon xoa: ";
			cin >> maHH;
			ListGoods.hienThiMatHang(maHH, false);
			cin.ignore();
			string choice;
			cout << "\nBan co chac muon xoa mat hang nay khong ? (y/n) ";
			getline(cin, choice);
			if (choice == "y") {
				ListGoods.xoaMatHang(maHH, false); 
			}
			break;
		}
		case 2: {
			string tenHH;
			cout << "Nhap ten hang hoa ban muon xoa:";
			getline(cin, tenHH);
			ListGoods.hienThiMatHang(tenHH, true);
			string choice;
			cout << "Ban co chac muon xoa mat hang nay khong ? (y/n) ";
			getline(cin, choice);
			if (choice == "y") {
				ListGoods.xoaMatHang(tenHH, true);
			}

		}
		default:  "Nhap sai, vui long nhap lai !";
			break;
		}
	}

	void App::editGoods() {
		int choice;
		system("cls");
		cout << "===CHINH SUA THONG TIN HANG HOA===\n";
		cout << "1. Theo ma hang hoa\n2. Theo ten hang hoa \n" << "Ban muon tim kiem hang hoa muon sua bang cach : ";
		cin >> choice;
		cin.ignore();
		switch (choice)
		{
		case 1: {
			string maHH;
			cout << "Nhap ma hang hoa ban muon thay doi: ";
			getline(cin, maHH);
			ListGoods.hienThiMatHang(maHH, false);
			ListGoods.suaThongTinMatHang(maHH, false);
			break;
		}
		case 2: {
			string tenHH;
			cout << "Nhap ten hang hoa ban muon thay doi: ";
			getline(cin, tenHH);
			ListGoods.hienThiMatHang(tenHH, true);
			ListGoods.suaThongTinMatHang(tenHH, true);
		}
		default:  "Nhap sai, vui long nhap lai !";
			break;
		}
	}

	void App::disPlayGoods() {
		if (ListGoods.empty()) {
			system("cls");
			cout << "Danh sach hang hoa rong!\n";
			cout << "Bam bat ki de thoat, bam 0 de quay lai menu: ";
			int a; cin >> a;
			system("cls");
			if (a != 0) {
				cout << "Tam biet!";
				exit(0);
			}
		}
		else {
			system("cls");
			cout << "Danh sach hang hoa la:\n";
			ListGoods.hienThiDanhSach();
			cout << "\n";
		}
	}

	void App::searchGoods() {
		int choice;
		system("cls");
		cout << "=== TIM KIEM HANG HOA ===\n";
		cout << "1. Tim kiem theo ma hang hoa\n";
		cout << "2. Tim kiem theo ten hang hoa\n";
		cout << "Nhap lua chon cua ban: ";
		cin >> choice;
		cin.ignore();

		switch (choice) {
		case 1: {
			string maHH;
			cout << "Nhap ma hang hoa can tim: ";
			getline(cin, maHH);
			ListGoods.timKiemMatHang(maHH, false);
			break;
		}
		case 2: {
			string tenHH;
			cout << "Nhap ten hang hoa can tim: ";
			getline(cin, tenHH);
			ListGoods.timKiemMatHang(tenHH, true);
			break;
		}
		default:
			cout << "Lua chon khong hop le!\n";
		}
	}

	void App::sortGoods() {
		int choice;
		system("cls");
		cout << "=== SAP XEP HANG HOA ===\n";
		cout << "1. Sap xep theo gia\n";
		cout << "2. Sap xep theo ten\n";
		cout << "3. Sap xep theo so luong\n";
		cout << "Nhap lua chon cua ban: ";
		cin >> choice;
		if (choice >= 1 && choice <= 4) {
			ListGoods.sapXepHangHoa(choice);
			cout << "Danh sach da duoc sap xep la\n";
			ListGoods.hienThiDanhSach();
			cout << "\n";
		}
		else {
			cout << "Vui long lua chon lai";
		}
	}
