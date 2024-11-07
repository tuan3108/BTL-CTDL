#pragma once

#include <list>
#include "Goods.h"
using namespace std;

class ListOfGoods {
private:
    list<Goods*> ListGoods;

public:
    list<Goods*>& getList();

    bool empty();
    bool soTen(Goods* a, Goods* b);
    bool soSoLuong(Goods* a, Goods* b);

    void hienThiMatHang(string key, bool searchByName);
    void themMatHang(const Goods& hang);
    void xoaMatHang(string key, bool searchByName);
    void suaThongTinMatHang(string key, bool searchByName);
    void timKiemMatHang(string key, bool searchByName);
    void hienThiDanhSach();
    void sapXepHangHoa(int choice);
};