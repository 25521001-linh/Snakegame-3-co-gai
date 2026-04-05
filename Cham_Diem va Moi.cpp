#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <ctime>

#include <algorithm> 


using namespace std;

#define MAP_WIDTH 40
#define MAP_HEIGHT 20


float tocDo = 150.0f;
int diem = 0;
int bestScore = 0;


void gotoxy(int column, int line) {
    COORD coord = {(SHORT)column, (SHORT)line};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


struct Point { int x, y; };

struct ConMoi {
    Point vitri;
    clock_t timeXuatHien;
    bool conHieuLuc;
    int thoiGianTon; // Thời gian tồn tại (giây)

};

class CONRAN {
public:

    vector<Point> A;
    Point tail_old;

    CONRAN() {
        A.push_back({10, 10});
        A.push_back({11, 10});
        A.push_back({12, 10});
    }

    void Ve() {
        for (int i = 0; i < (int)A.size(); i++) {

            gotoxy(A[i].x, A[i].y);
            cout << "X";
        }
    }

    void XoaDuoi() {
        gotoxy(tail_old.x, tail_old.y);
        cout << " ";
    }


    void DiChuyen(int Huong, const vector<Point> &tuong) {
        tail_old = A.back();
        Point dauMoi = A[0];

        if (Huong == 0) dauMoi.x++;
        else if (Huong == 1) dauMoi.y++;
        else if (Huong == 2) dauMoi.x--;
        else if (Huong == 3) dauMoi.y--;


        if (dauMoi.x >= MAP_WIDTH) dauMoi.x = 0;
        else if (dauMoi.x < 0) dauMoi.x = MAP_WIDTH - 1;
        if (dauMoi.y >= MAP_HEIGHT) dauMoi.y = 0;
        else if (dauMoi.y < 0) dauMoi.y = MAP_HEIGHT - 1;


        for (auto &p : tuong) {
            if (dauMoi.x == p.x && dauMoi.y == p.y) return;
        }

        for (int i = (int)A.size() - 1; i > 0; i--) A[i] = A[i - 1];

        A[0] = dauMoi;
    }
};


vector<Point> ToaDoChuongNgaiVatL() {
    vector<Point> tuong;
    for (int i = 15; i <= 25; i++) {
        tuong.push_back({i, 9});
        tuong.push_back({i, 11});

    }
    return tuong;
}


class QuanLyGame {
public:
    ConMoi moiThuong, moiDB;

    QuanLyGame() {
        moiThuong.conHieuLuc = false;
        moiThuong.thoiGianTon = 15; // Mồi thường tồn tại 15s
        moiDB.conHieuLuc = false;
        moiDB.thoiGianTon = 10;    // Mồi đặc biệt tồn tại 10s
    }


    void xuatHienMoiThuong(CONRAN &r) {
        bool hopLe;
        do {
            hopLe = true;
            moiThuong.vitri.x = rand() % MAP_WIDTH;
            moiThuong.vitri.y = rand() % MAP_HEIGHT;

            for (auto &p : r.A) {
                if (moiThuong.vitri.x == p.x && moiThuong.vitri.y == p.y) {
                    hopLe = false; break;
                }
            }
            // Không mọc mồi trong vùng chướng ngại vật L
            if (moiThuong.vitri.x >= 15 && moiThuong.vitri.x <= 25 && 
                moiThuong.vitri.y >= 9 && moiThuong.vitri.y <= 11) hopLe = false;
        } while (!hopLe);

        moiThuong.conHieuLuc = true;
        moiThuong.timeXuatHien = clock();

        gotoxy(moiThuong.vitri.x, moiThuong.vitri.y); cout << "P";
    }

    void xuatHienMoiDB() {
        moiDB.vitri = {20, 10};

        moiDB.conHieuLuc = true;
        moiDB.timeXuatHien = clock();
        
        // Vẽ chướng ngại vật L
        vector<Point> tuong = ToaDoChuongNgaiVatL();
        for (auto &p : tuong) { gotoxy(p.x, p.y); cout << "*"; }
        gotoxy(moiDB.vitri.x, moiDB.vitri.y); cout << "$";

    }

    void XoaTuongL() {
        vector<Point> tuong = ToaDoChuongNgaiVatL();

        for (auto &p : tuong) { gotoxy(p.x, p.y); cout << " "; }
        gotoxy(20, 10); cout << " ";
        moiDB.conHieuLuc = false;
    }

    void KiemTraTimeout(CONRAN &r) {
        // Nếu mồi thường hết hạn -> đổi chỗ
        if (moiThuong.conHieuLuc && (clock() - moiThuong.timeXuatHien) / CLOCKS_PER_SEC >= moiThuong.thoiGianTon) {
            gotoxy(moiThuong.vitri.x, moiThuong.vitri.y); cout << " ";
            xuatHienMoiThuong(r);
        }
        // Nếu mồi đặc biệt hết hạn -> biến mất cùng tường
        if (moiDB.conHieuLuc && (clock() - moiDB.timeXuatHien) / CLOCKS_PER_SEC >= moiDB.thoiGianTon) {
            XoaTuongL();
        }
    }

    void tinhdiem(CONRAN &r) {
        // Ăn mồi thường
        if (moiThuong.conHieuLuc && r.A[0].x == moiThuong.vitri.x && r.A[0].y == moiThuong.vitri.y) {
            diem++;
            if (diem > bestScore) bestScore = diem;
            r.A.push_back(r.tail_old); // Tăng độ dài
            if (tocDo > 50) tocDo -= 2.0f; // Tăng tốc độ game
            xuatHienMoiThuong(r);
            if (diem % 5 == 0) xuatHienMoiDB();
        }
        // Ăn mồi đặc biệt
        if (moiDB.conHieuLuc && r.A[0].x == 20 && r.A[0].y == 10) {
            diem += 5;
            if (diem > bestScore) bestScore = diem;
            for(int i=0; i<3; i++) r.A.push_back(r.tail_old);
            XoaTuongL();
        }
    }

    bool KiemTraThua(CONRAN &r) {
        for (int i = 1; i < (int)r.A.size(); i++) {
            if (r.A[0].x == r.A[i].x && r.A[0].y == r.A[i].y) return true;
        }
        return false;
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

        vector<Point> tuongHienTai = ql.moiDB.conHieuLuc ? ToaDoChuongNgaiVatL() : vector<Point>();

        r.DiChuyen(Huong, tuongHienTai);

        if (ql.KiemTraThua(r)) break;

        ql.tinhdiem(r);

        ql.KiemTraTimeout(r);
        r.Ve();

        gotoxy(0, MAP_HEIGHT + 1);
        cout << "Diem: " << diem << " | Best: " << bestScore << " | Speed: " << (int)tocDo << "ms   ";

        Sleep((int)tocDo);
    }
    
    system("cls");
    cout << "GAME OVER! Diem: " << diem << " | Ky luc: " << bestScore << endl;
    return 0;
}

