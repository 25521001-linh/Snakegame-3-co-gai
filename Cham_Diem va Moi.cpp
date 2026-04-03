
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include<ctime>
using namespace std;

int diem = 0 ;
int tocDo = 300;
int huongTuongL;
int maxDiem = 0;
vector<int> lichsuDiem;

void gotoxy( int column, int line );
struct Point{
    int x,y;
};
class CONRAN{
public:
    struct Point A[100];
    int DoDai;
    CONRAN(){
        DoDai = 3;
        A[0].x = 10; A[0].y = 10;
        A[1].x = 11; A[1].y = 10;
        A[2].x = 12; A[2].y = 10;
    }
    void Ve(){
        for (int i = 0; i < DoDai; i++){
            gotoxy(A[i].x,A[i].y);
            cout<<"X";
        }
    }
    void DiChuyen(int Huong){
        for (int i = DoDai-1; i>0;i--)
            A[i] = A[i-1];
        if (Huong==0) A[0].x = A[0].x + 1;
        if (Huong==1) A[0].y = A[0].y + 1;
        if (Huong==2) A[0].x = A[0].x - 1;
        if (Huong==3) A[0].y = A[0].y - 1;

    }
};
vector<Point> ToaDoChuongNgaiVatL ( int huong)
{    vector<Point> tuong;
    if ( huong == 0) {
        for ( int i = 18; i <= 21; i++ ){ 
            tuong.push_back({i,19}); }
            tuong.push_back({21,20});
        }
    
    else if ( huong == 1){
        for ( int i = 18; i <= 21; i++ ){
            tuong.push_back({21,i});}
            tuong.push_back({20,21});
    }
    else if ( huong == 2){
        for ( int i = 19; i <= 22; i++ ){
            tuong.push_back({i,21}); }
            tuong.push_back({19,20});
    }
    else {
        for ( int i = 19; i <= 22; i++ ){
            tuong.push_back({19,i});}
            tuong.push_back({20,19});
    }
    return tuong;
}
// Tao con moi
struct ConMoi {
    Point vitri;
    clock_t TimeXuathien;
    bool ChuaBiAn;
    int loai;
};
class QuanLyMoi {
public:
    ConMoi moiThuong;
    ConMoi moiDB;
    int huongTuongL;
QuanLyMoi() {
        moiThuong.ChuaBiAn = false;
        moiDB.ChuaBiAn = false;
        huongTuongL = 0;
}
    void xuatHienMoiThuong(CONRAN &r) {
        bool hopLe = false;
    while ( !hopLe){
        hopLe = true;
        moiThuong.vitri.x = rand() % 40;
        moiThuong.vitri.y = rand() % 40;
        // tranh trung ran
        for (int i = 0; i < r.DoDai; i++) {
                if (moiThuong.vitri.x == r.A[i].x && moiThuong.vitri.y == r.A[i].y) {
                    hopLe = false;
                    break; 
                }
            }
    
        //tranh vung moi DB
        if (XuathienMoiDB == true){
        if ( moiThuong.vitri.x >= 18 && moiThuong.vitri.x <= 22 && moiThuong.vitri.y >= 18 && moiThuong.vitri.y <= 22){
        hopLe = false;}
        }}
        moiThuong.TimeXuathien = clock();
        moiThuong.ChuaBiAn = true;
    }
    void xuatHienMoiDB() {
        moiDB.ChuaBiAn = true;
        moiDB.TimeXuathien= clock();
    }
        
    void Ve_MoiDB_ChuongNgaiVat_L(){
        if (moiDB.ChuaBiAn == true){
            gotoxy(19, 19); cout << "@"; gotoxy (20, 19); cout << "@"; 
            gotoxy(19, 20); cout << "@"; gotoxy ( 20,20); cout << "@"; 
        
        vector<Point> tuong = ToaDoChuongNgaiVatL(huongTuongL);
        for ( int i = 0; i < tuong.size(); i++)
        { gotoxy (tuong[i].x, tuong[i].y); cout << "X";}
    }}

    void ve_MoiThuong (){
        if (moiThuong.ChuaBiAn) {
        gotoxy(moiThuong.vitri.x, moiThuong.vitri.y);
        cout << "O";}}

    void xoaMoiThuong() {
        if ( moiThuong.ChuaBiAn){
        gotoxy(moiThuong.vitri.x, moiThuong.vitri.y);
        cout << " ";
        moiThuong.ChuaBiAn = false;}
    }
    void XoaTuongL_MoiDB() {
    //xoa tuong ngai vat
    vector<Point> tuong = ToaDoChuongNgaiVatL(huongTuongL);
    for (int i = 0; i < tuong.size(); i++) {
        gotoxy(tuong[i].x, tuong[i].y);
        cout << " "; }
    // xoay 90 độ
    moiDB.ChuaBiAn = false;
    huongTuongL = (huongTuongL + 1) % 4; 

    gotoxy(19, 19); cout << "  "; 
    gotoxy(19, 20); cout << "  ";
}
bool KiemTraThua(CONRAN &r) {
    if (r.A[0].x < 0 || r.A[0].x >= 40 || r.A[0].y < 0 || r.A[0].y >= 40) return true;

    for (int i = 1; i < r.DoDai; i++) {
        if (r.A[0].x == r.A[i].x && r.A[0].y == r.A[i].y) return true;
    }
    if (ChamTuongL(r.A[0])) return true;

    return false;
}
bool ChamTuongL (Point dau){
    if ( moiDB.ChuaBiAn == false) return false;

    vector<Point> tuong = ToaDoChuongNgaiVatL(huongTuongL);
    for ( int i = 0; i < tuong.size(); i++){
        if ( dau.x == tuong[i].x && dau.y == tuong[i].y) return true;
    }
    return false;
}
void tinhdiem(CONRAN &r) {
        // Ăn mồi thường
        if (r.A[0].x == moiThuong.vitri.x && r.A[0].y == moiThuong.vitri.y) {
            diem += 1;
            r.DoDai += 1;
            
            xuatHienMoiThuong(r);
        }
        // Ăn mồi đặc biệt
        if (moiDB.ChuaBiAn && (r.A[0].x == 19 || r.A[0].x == 20) && (r.A[0].y == 19 || r.A[0].y == 20)) {
            diem += 5;
            r.DoDai += 5;
            XoaTuongL_MoiDB();
        }
    }
    void kiemTraThoiGian(CONRAN &r) {
        if (moiThuong.ChuaBiAn && (clock() - moiThuong.TimeXuathien) / CLOCKS_PER_SEC >= 15) {
            xoaMoiThuong();
            xuatHienMoiThuong(r);
        }
        if (moiDB.ChuaBiAn && (clock() - moiDB.TimeXuathien) / CLOCKS_PER_SEC >= 25) {
            XoaTuongL_MoiDB();
        }
    }};

int main()
{
    CONRAN r;
    int Huong = 0;
    char t;

    srand((unsigned int) time (NULL));
    diem = 0;
    tocDo = 300;
    moiDB.ChuaBiAn = false;
    XuathienMoiDB = false;
    QuanLyMoi qlm;
    qlm.xuatHienMoiThuong(r);
        
     
    while (1){
        if (kbhit()){
            t = getch();
            if (t=='a') Huong = 2;
            if (t=='w') Huong = 3;
            if (t=='d') Huong = 0;
            if (t=='x') Huong = 1;
        }
        system("cls");
        if (diem > 0 && diem % 5 == 0 && !qlm.moiDB.ChuaBiAn && !XuathienMoiDB) {
            qlm.xuatHienMoiDB();
            XuathienMoiDB = true;
        }
        if (diem % 5 != 0) XuathienMoiDB = false;
        qlm.kiemTraThoiGian(r);        
        if ( qlm.KiemTraThua(r)) {break;};
        qlm.tinhdiem(r);        
        qlm.ve_MoiThuong();
        qlm.Ve_MoiDB_ChuongNgaiVat_L();
        r.Ve();
        r.DiChuyen(Huong);
        Sleep(300);
    }

    return 0;
}


void gotoxy( int column, int line )
  {
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
    );
  }
