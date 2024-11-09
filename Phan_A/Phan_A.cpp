#include <iostream> 
#include <iomanip>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
using namespace std;

class Goods {
private:
    int maHangHoa;
    string tenHangHoa;
    string danhMuc;
    int giaBan;
    int soLuongTonKho;

public:
    Goods() {}
    Goods(int ma, string ten, string muc, int gia, int soluong) 
        : maHangHoa(ma), tenHangHoa(ten), danhMuc(muc), giaBan(gia), soLuongTonKho(soluong) {}

    int getMaHangHoa() const { return maHangHoa; }
    string getTenHangHoa() const { return tenHangHoa; }
    string getDanhMuc() const { return danhMuc; }
    int getSoLuongTonKho() const { return soLuongTonKho; }
    int getGiaBan() const { return giaBan; }

    void setThongTin(int ma, string ten, string muc, int gia, int soluong) {
        maHangHoa = ma;
        tenHangHoa = ten;
        danhMuc = muc;
        giaBan = gia;
        soLuongTonKho = soluong;
    }
    
    friend bool operator<(const Goods& g1, const Goods& g2) {
        return g1.getGiaBan() < g2.getGiaBan();
    }

    friend istream& operator>>(istream& is, Goods& goods) {
        is >> goods.maHangHoa;
        is.ignore();
        getline(is, goods.tenHangHoa);
        getline(is, goods.danhMuc);
        is >> goods.giaBan;
        is >> goods.soLuongTonKho;
        return is;
    }

    friend ostream& operator<<(ostream& os, const Goods& goods) {
        os  << left 
            << setw(15) << goods.maHangHoa
            << setw(20) << goods.tenHangHoa
            << setw(20) << goods.danhMuc
            << setw(15) << goods.giaBan
            << setw(20) << goods.soLuongTonKho;
        return os;
    }
};

class ListOfGoods {
private:
    list<Goods*> ListGoods;

public:
    list<Goods*>& getList() { return ListGoods; }

    bool empty() { return ListGoods.empty(); }

    bool soTen(Goods* a, Goods* b) {
        return a->getTenHangHoa() < b->getTenHangHoa();
    }

    bool soSoLuong(Goods* a, Goods* b) {
        return a->getSoLuongTonKho() < b->getSoLuongTonKho();
    }

    void themMatHang(const Goods& hang) {
        Goods* newHang = new Goods(hang);
        ListGoods.push_back(newHang);
    }

    void xoaMatHang(string key, bool searchByName = false) {
        try {
            auto it = std::find_if(ListGoods.begin(), ListGoods.end(),
                [key, searchByName](Goods* hang) {
                    if (searchByName) {
                        return hang->getTenHangHoa() == key;
                    } else {
                        return hang->getMaHangHoa() == stoi(key);
                    }
                });
            if (it != ListGoods.end()) {
                delete* it;
                ListGoods.erase(it);
                cout << "Da xoa mat hang khoi he thong\n";
            } else {
                cout << "Khong tim thay mat hang\n";
            }
        } catch (const invalid_argument&) {
            cout << "Ma hang hoa khong hop le !\n";
        }
    }

    void hienThiMatHang(string key, bool searchByName = false) {
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
            } else {
                if (newHang->getTenHangHoa() == key) {
                    cout << *newHang << "\n";
                }
            }
        }
    }

    void suaThongTinMatHang(string key, bool searchByName = false) {
        auto it = std::find_if(ListGoods.begin(), ListGoods.end(),
            [key, searchByName](Goods* hang) {
                if (searchByName) {
                    return hang->getTenHangHoa() == key;
                } else {
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
        } else {
            cout << "Khong the tim thay mat hang";
        }
    }

    void timKiemMatHang(string key, bool searchByName = false) {
        try {
            auto it = std::find_if(ListGoods.begin(), ListGoods.end(),
                [key, searchByName](Goods* hang) {
                    if (searchByName) {
                        return hang->getTenHangHoa() == key;
                    } else {
                        return hang->getMaHangHoa() == stoi(key);
                    }
                });
            if (it != ListGoods.end()) {
                cout << "Da tim thay hang hoa\n";
                cout << string(90, '-') << "\n";
                cout << **it << "\n";
            } else {
                cout << "Khong tim thay mat hang\n";
            }
        } catch (const invalid_argument&) {
            cout << "Ma hang hoa khong hop le !\n";
        }
    }

    void hienThiDanhSach() {
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

    void sapXepHangHoa(int choice) {
        switch (choice) {
        case 1: {
            ListGoods.sort([](Goods* a, Goods* b) { return *a < *b; });
            break;
        }
        case 2: {
            ListGoods.sort([](Goods* a, Goods* b) { return a->getTenHangHoa() < b->getTenHangHoa(); });
            break;
        }
        case 3: {
            ListGoods.sort([](Goods* a, Goods* b) { return a->getSoLuongTonKho() < b->getSoLuongTonKho(); });
            break;
        }
        }
    }
};

class App {
    private:
        ListOfGoods ListGoods;
	void disPlayMenu() {
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

	void addGoods() {
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

	void removeGoods() {
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

	void editGoods() {
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

	void disPlayGoods() {
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

	void searchGoods() {
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

	void sortGoods() {
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
    public:
        void run() {
            int choice;
            do {
                disPlayMenu();
                cin >> choice;
                cin.ignore();
                switch (choice) {
                case 1: addGoods(); break;
                case 2: removeGoods(); break;
                case 3: editGoods(); break;
                case 4: disPlayGoods(); break;
                case 5: searchGoods(); break;
                case 6: sortGoods(); break;
                case 0: cout << "Tam Biet!\n"; break;
                default: cout << "Lua chon khong hop le, vui long chon lai.\n"; break;
                }
            } while (choice != 0);
        }
};

int main() {
    App app;
    app.run();
    return 0;
}
