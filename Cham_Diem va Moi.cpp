#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <ctime>

using namespace std;

#define MAP_WIDTH 40
#define MAP_HEIGHT 20

float tocDo = 150.0;
int diem = 0;

void gotoxy(int column, int line) {
    COORD coord = {(SHORT)column, (SHORT)line};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct Point {
    int x, y;
};

class CONRAN {
public:
    struct Point A[100]; 
    int DoDai;
    Point tail_old;     

    CONRAN() {
        DoDai = 3;
        A[0].x = 10; A[0].y = 10;
        A[1].x = 11; A[1].y = 10;
        A[2].x = 12; A[2].y = 10;
    }

    void Ve() {
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            cout << "X";
        }
    }

    void XoaDuoi() {
        gotoxy(tail_old.x, tail_old.y);
        cout << " ";
    }

    
    void DiChuyen(int Huong, const vector<Point> &tuong) {
        
        tail_old = A[DoDai - 1];

        
        Point dauMoi = A[0];
        if (Huong == 0) dauMoi.x++;
        if (Huong == 1) dauMoi.y++;
        if (Huong == 2) dauMoi.x--;
        if (Huong == 3) dauMoi.y--;

        
        if (dauMoi.x >= MAP_WIDTH) dauMoi.x = 0;
        else if (dauMoi.x < 0) dauMoi.x = MAP_WIDTH - 1;
        if (dauMoi.y >= MAP_HEIGHT) dauMoi.y = 0;
        else if (dauMoi.y < 0) dauMoi.y = MAP_HEIGHT - 1;

        
        for (int i = 0; i < (int)tuong.size(); i++) {
            if (dauMoi.x == tuong[i].x && dauMoi.y == tuong[i].y) return;
        }

        
        for (int i = DoDai - 1; i > 0; i--) {
            A[i] = A[i - 1];
        }
        A[0] = dauMoi;
    }
};



vector<Point> ToaDoChuongNgaiVatL() {
    vector<Point> tuong;
    for (int i = 15; i <= 25; i++) {
        Point p1 = {i, 9};  tuong.push_back(p1);
        Point p2 = {i, 11}; tuong.push_back(p2);
    }
    return tuong;
}

struct ConMoi {
    Point vitri;
    clock_t TimeXuathien;
    bool ChuaBiAn;
};

class QuanLyGame {
public:
    ConMoi moiThuong, moiDB;
    QuanLyGame() { moiThuong.ChuaBiAn = false; moiDB.ChuaBiAn = false; }

    void xuatHienMoiThuong(CONRAN &r) {
        bool hopLe;
        do {
            hopLe = true;
            moiThuong.vitri.x = rand() % MAP_WIDTH;
            moiThuong.vitri.y = rand() % MAP_HEIGHT;
            for (int i = 0; i < r.DoDai; i++) {
                if (moiThuong.vitri.x == r.A[i].x && moiThuong.vitri.y == r.A[i].y) {
                    hopLe = false; break;
                }
            }
        } while (!hopLe);
        moiThuong.ChuaBiAn = true;
        gotoxy(moiThuong.vitri.x, moiThuong.vitri.y); cout << "P";
    }

    void xuatHienMoiDB() {
        moiDB.vitri = {20, 10};
        moiDB.ChuaBiAn = true;
    }

    void Ve_MoiDB_ChuongNgaiVat_L() {
        if (moiDB.ChuaBiAn) {
            gotoxy(20, 10); cout << "$";
            vector<Point> tuong = ToaDoChuongNgaiVatL();
            for (int i = 0; i < (int)tuong.size(); i++) {
                gotoxy(tuong[i].x, tuong[i].y); cout << "*";
            }
        }
    }

    void XoaTuongL() {
        vector<Point> tuong = ToaDoChuongNgaiVatL();
        for (int i = 0; i < (int)tuong.size(); i++) {
            gotoxy(tuong[i].x, tuong[i].y); cout << " ";
        }
        gotoxy(20, 10); cout << " ";
        moiDB.ChuaBiAn = false;
    }

    bool KiemTraThua(CONRAN &r) {
        for (int i = 1; i < r.DoDai; i++) {
            if (r.A[0].x == r.A[i].x && r.A[0].y == r.A[i].y) return true;
        }
        return false;
    }

    void tinhdiem(CONRAN &r) {
        if (r.A[0].x == moiThuong.vitri.x && r.A[0].y == moiThuong.vitri.y) {
            diem++;
            if (r.DoDai < 100) r.DoDai++; // Tăng độ dài mảng tĩnh
            xuatHienMoiThuong(r);
            if (diem % 5 == 0) xuatHienMoiDB();
        }
        if (moiDB.ChuaBiAn && r.A[0].x == 20 && r.A[0].y == 10) {
            diem += 5;
            r.DoDai = (r.DoDai + 3 < 100) ? r.DoDai + 3 : 99;
            XoaTuongL();
        }
    }
};

int main() {
    srand((unsigned int)time(NULL));
    CONSOLE_CURSOR_INFO ci = {100, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);

    CONRAN r;
    QuanLyGame ql;
    int Huong = 2; 
    ql.xuatHienMoiThuong(r);

    while (true) {
        if (kbhit()) {
            char t = getch();
            if ((t == 'a' || t == 75) && Huong != 0) Huong = 2;
            else if ((t == 'd' || t == 77) && Huong != 2) Huong = 0;
            else if ((t == 'w' || t == 72) && Huong != 1) Huong = 3;
            else if ((t == 's' || t == 80) && Huong != 3) Huong = 1;
        }

        r.XoaDuoi();
        vector<Point> tuongHienTai = ql.moiDB.ChuaBiAn ? ToaDoChuongNgaiVatL() : vector<Point>();
        r.DiChuyen(Huong, tuongHienTai);

        if (ql.KiemTraThua(r)) break;

        ql.tinhdiem(r);
        ql.Ve_MoiDB_ChuongNgaiVat_L();
        r.Ve();

        gotoxy(0, MAP_HEIGHT + 1);
        cout << "Diem: " << diem << "  ";

        Sleep((int)tocDo);
    }

    
    return 0;
}
