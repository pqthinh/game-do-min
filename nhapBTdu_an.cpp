#include<iostream>
#include<conio.h>
#include<windows.h>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include<fstream>

#define MAX 100
using namespace std;

int he=15,wi=20;
int SoMin=50 ;
float ThoiGian=0;
int Bang[MAX][MAX];
int BangHien[MAX][MAX];
int SoLuong[MAX][MAX];
int BangLap[MAX][MAX] ={0};

int X = 10, Y=5;
int flag =0; // danh dau o nguoi choi cam co

/*
    DEFINE : -2 : o chua min
           : -1 : o rong
           : -10 : chua min
    +) canh mep tren 5 o   +) mep trai 10 o

*/
 /* tao button */
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */


void txtColor(int);
void gotoxy(int ,int ) ;
void level(int ,int) ;
void RaiMin();
void KhoiTao ();
void DemSoLuongMin(int Bang[][MAX],int SoLuong[][MAX]) ;
void Loang(int BangHien[][MAX],int SoLuong[][MAX],int row,int col) ;
void Khung();
void VeKhung();
void DieuKhien() ;
void XuLyChon();
bool ChonDung(int ,int);
void VeOMin(int SoLuong[][MAX],int ,int );
void Xuat(int ,int);
void XuatBanDo(int BangHien [][MAX],int SoLuong[][MAX],int row,int col);
bool Thang(int BangHien[][MAX]);
void XuatKhoiDong(int ,int );
void GioiThieu();
void PlayGame();
void ChonMucDo(int);
void clearScreen() ;
void DocFileHuongDan(string path);

/*int row =Y-5;
int col=X-10;*/

int main() {
    SetConsoleTitle(" minesweeper! ");
    for(int i=21;i>0;i--) {
        txtColor(i%14+1);
        clearScreen();
        XuatKhoiDong(23,i);
        Sleep(100);
    }
   // ChonMucDo(3);

    GioiThieu();
    return 0;
}

void PlayGame() {
    clearScreen();
    Khung();
    VeKhung();
    RaiMin();
    KhoiTao();
    DemSoLuongMin(Bang,SoLuong);

    while(true) {
        DieuKhien();
        if(Thang(BangHien)) {
            gotoxy(10,5+he+3);
            cout << "You Win !!! \n";
            ::MessageBox(hwnd,"Ban da thang :))  !!!", "you win !!",MB_OK);
            break;
        }
    }
}

void txtColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

void gotoxy(int x,int y) {
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void RaiMin() {
    srand(time(NULL));
    for(int i=0;i<he;i++)
        for(int j=0;j<wi;j++)
            Bang[i][j]=-1;

    int i=0;
    while(i<SoMin) {
        int r= rand() % he;
        int c= rand() % wi;
        if(Bang[r][c] != -2) {
            Bang[r][c] = -2;
            i++;
        }
    }
}

void KhoiTao() {
    RaiMin();

    for(int i=0;i<he;i++)

        for(int j=0;j<wi;j++) {
            BangHien[i][j] = -1;
            SoLuong[i][j] =0;
            if( Bang[i][j]==-2) {
                BangHien[i][j] =-10;
                SoLuong[i][j] =-10;
            }
        }

}

void DemSoLuongMin(int Bang[][MAX],int SoLuong[][MAX]) {
    for(int i=0;i<he;i++) {
        for(int j=0;j<wi;j++) {
            //if(Bang[i][j]=='M') SoLuong[i][j] =-1;
            if(Bang[i-1][j]==-2 && Bang[i][j]!=-2 && i>0) SoLuong[i][j]++;
            if(Bang[i-1][j-1]== -2 && Bang[i][j]!= -2 && i>0 && j>0) SoLuong[i][j]++;
            if(Bang[i-1][j+1]== -2 && Bang[i][j]!= -2 && i>0) SoLuong[i][j]++;
            if(Bang[i][j+1]== -2 && Bang[i][j]!= -2 && j< wi-1) SoLuong[i][j]++;
            if(Bang[i+1][j+1]== -2 && Bang[i][j]!= -2 && j<wi-1 && i<he-1) SoLuong[i][j]++;
            if(Bang[i+1][j]== -2 && Bang[i][j]!= -2 && i<he-1) SoLuong[i][j]++;
            if(Bang[i+1][j-1]== -2 && Bang[i][j]!= -2 && i<he-1 && j>0) SoLuong[i][j]++;
            if(Bang[i][j-1]== -2 && Bang[i][j]!= -2 && j>0) SoLuong[i][j]++;
        }
    }
}

void Loang(int BangHien[][MAX],int SoLuong[][MAX],int row,int col)  {
    BangHien[row][col]=1;
    if(SoLuong[row][col]==0) {
        for(int i=-1;i<2;i++) {
            for(int j=-1;j<2;j++) {
                if(i!=0 || j!=0) {
                    if(row+i > -1 && row +i <= he && col+j > -1 && col +j <= wi) {
                        if(BangHien[row+i][col+j]==-1)
                            Loang(BangHien,SoLuong,row+i,col+j);
                    }
                }
            }
        }
    }
}

void Khung() {
    txtColor(14);

    for(int i=0;i<wi+2;i++) { // tinh ca 2 mep khung
        gotoxy(i+9,4);
        cout << char(220);
        gotoxy(9+i,4+he+1);
        cout << char(223);
    }
    for(int i=0;i<he;i++ ) {
        gotoxy(9,5+i);
        cout << char(219);
        gotoxy(10+wi,5+i);
        cout << char(219);
    }
    for(int i=0;i<he+10-2; i++ ) {

        gotoxy(10+wi+10,2+i);
        cout << '|';
    }
    for(int i=0;i<wi+2;i++) {
        gotoxy(10+wi+10+i+1,(he+10)/2);
        cout << '_';
    }
}

void VeKhung() {
    for(int j=5; j<5+he ;j++){
        for(int i=10 ;i<10+wi ;i++){
            if(i%2==0){
                if(j%2==0){
                    gotoxy(i,j);
                    txtColor(0);
                    cout << char(219);
                }
                else{
                    gotoxy(i,j);
                    txtColor(7);
                    cout << char(219);
                }
            }
            else{
                if(j%2==0){
                    gotoxy(i,j);
                    txtColor(7);
                    cout << char(219);
                }
                else{
                    gotoxy(i,j);
                    txtColor(0);
                    cout << char(219);
                }
            }
        }
    }

    txtColor(12);
    gotoxy(10,10+he);
    cout << "* do min *";
    gotoxy(10,13+he);
    cout << " ver 1.3 ";
    gotoxy(10,8+he); cout << "Thoat game an esc !";
    gotoxy(20+wi+5,5); txtColor(42); cout << "So Min: " << SoMin << "  "; txtColor(7);
    //gotoxy(20+wi+5,5+he/2); txtColor(42); cout << "Thoi Gian: " << fixed << setprecision(0) << ThoiGian << "  (s)"; txtColor(7);
}

void VeOMin(int SoLuong[][MAX],int i,int j) {

        if(SoLuong[i][j] ==0) {
            txtColor(136); cout << SoLuong[i][j];txtColor(7);
        }
        if(SoLuong[i][j] ==1) {
            txtColor(129); cout << SoLuong[i][j];txtColor(7);
        }
        if(SoLuong[i][j] ==2) {
            txtColor(137); cout << SoLuong[i][j];txtColor(7);
        }
        if(SoLuong[i][j] ==3) {
            txtColor(139); cout << SoLuong[i][j];txtColor(7);
        }

        if(SoLuong[i][j] ==4) {
            txtColor(132); cout << SoLuong[i][j];txtColor(7);
        }
        if(SoLuong[i][j] ==5) {
            txtColor(130); cout << SoLuong[i][j];txtColor(7);
        }
        if(SoLuong[i][j] ==6) {
            txtColor(134); cout << SoLuong[i][j];txtColor(7);
        }
        if(SoLuong[i][j] ==7) {
            txtColor(140); cout << SoLuong[i][j];txtColor(7);
        }
        if(SoLuong[i][j] ==8) {
            txtColor(128); cout << SoLuong[i][j];txtColor(7);
        }
        if(SoLuong[i][j]==-10) {
            txtColor(128); cout << char(235);txtColor(7);
        }

}

bool ChonDung(int row,int col) {
    if(Bang[row][col]!=-2|| BangHien[row][col]!=-10)  return 1;
    return 0;
}

void Xuat(int row,int col) {
    for(int i=0;i<he;i++) {
        for(int j=0;j<wi;j++) {

            if(ChonDung(row,col)) {
                gotoxy(10+j,5+i);
                if(BangHien[i][j]==-1 || BangHien[i][j]==-10 ) ;
                if(BangHien[i][j]==-2) {
                    VeOMin(SoLuong,i,j);
                }
                if(BangHien[i][j]!=-1 && BangHien[i][j]!=-2 && BangHien[i][j]!=-10)
                    VeOMin(SoLuong,i,j);
            }
            else{
                gotoxy(10+j,5+i);
                if(BangHien[i][j]==-10 || BangHien[i][j]==-2  ) VeOMin(SoLuong,i,j);
                //else VeOMin(SoLuong,i,j);;
            }

        }
    }
}

void XuatBanDo(int BangHien[][MAX],int SoLuong[][MAX],int row,int col) {
    Loang(BangHien,SoLuong,row,col);
    for(int i=0;i<he;i++)
        for(int j=0;j<wi;j++)
            if(BangHien[i][j]==1) BangHien[i][j]=SoLuong[i][j];
    Xuat(row,col);
}

void DieuKhien() {
    ThoiGian += 0.1;
    gotoxy(20+wi+5,4+he/2); txtColor(42); cout << "Thoi Gian: " << fixed << setprecision(0) << ThoiGian << "  (s)"; txtColor(7);
    if(_kbhit() ) {
        char key = getch();

        if(key== 'a' || key == char(75) || key== char(4+'0')) {
            if(X<11) X =10+wi;
            X--;
        }

        if(key== 'd' || key == char(77) || key== char(6+'0')) {
            if(X>=9+wi) X =9;
            X++;
        }

        if(key== 'w' || key == char(72) || key== char(8+'0')) {
            if(Y<6) Y =4+he;
            Y--;
        }

        if(key== 's' || key == char(80) || key== char(2+'0')) {
            if(Y>=4+he) Y =4;
            Y++;
        }

        if(key == 13 || key == char(5+'0')) { //enter // chon o
            int row =Y-5;
            int col=X-10;
            gotoxy(20+wi+2, 2); txtColor(12);cout << "Chon :"; txtColor(7);
            gotoxy(20+wi+2, 3);cout << X << " " << Y << " ";
            if(BangHien[row][col]%2==0) SoMin++;
            if(ChonDung(row,col)) XuatBanDo(BangHien,SoLuong,row,col);
            if(!ChonDung(row,col)) {
                Xuat(row,col);
                gotoxy(10,5+he+3); cout << "You loss !";

                ::MessageBox(hwnd,"Ban da thua :((  !!!","Game over !",MB_OK);

                exit(1);
            }
            gotoxy(20+wi+5,5); txtColor(42); cout << "So Min: " << SoMin << "  "; txtColor(7);
        }

        if(key == 32) {  //space // cam co vao o
            if(SoMin<0) return;
            int row =Y-5;
            int col=X-10;

            BangLap[row][col]++;
            if(BangLap[row][col]%2==1) {
                //BangHien[row][col]=-3;
                SoMin--;
                gotoxy(20+wi+10, 2); txtColor(12);cout << "Gan co:"; txtColor(7);
                gotoxy(20+wi+10, 3); cout << X << " " << Y << " " ;
                gotoxy(X,Y);
                txtColor(12); cout << char(35); txtColor(7);
                gotoxy(20+wi+5,5); txtColor(42); cout << "So Min: " << SoMin << "  "; txtColor(7);
            }
            else { // Huy bo o danh dau co
                SoMin++;
                gotoxy(20+wi+2, 2); txtColor(12);cout << "Chon :"; txtColor(7);
                gotoxy(20+wi+2, 3); cout << X << " " << Y << " " ;
                gotoxy(X,Y);
                txtColor(12); cout << " "; txtColor(7);
                gotoxy(20+wi+5,5); txtColor(42); cout << "So Min: " << SoMin << "  "; txtColor(7);
            }
           // else BangHien[row][col]=-1;
        }

        if(key == 27) {
            gotoxy(2,0);
            cout << "Ban chac chan muon thoat ? ( c / k)\n";
            char c;
            cin >> c;
            if(c=='c'|| c== 'C') exit(0);
            else {
                gotoxy(2,0);
                // xoa chu vua hien ra
                cout << "                                      \n";
                cout << "                                      \n";
            }
        }


    }
    gotoxy(X,Y);
    Sleep(100);
}

bool Thang(int BangHien[][MAX]) {
    for(int i=0;i<he;i++)
        for(int j=0;j<wi;j++)
            if(BangHien[i][j]==-1) return 0;
    return 1;
}


void XuatKhoiDong(int i,int j) {

    gotoxy(i,j) ;  cout << "#    #  #  #    #  ####   ####   #    #  ####  ####  ####   ####  ###\n";
    gotoxy(i,j+1) ;cout << "##  ##  #  ##   #  #     #       #    #  #     #     #   #  #     #  #\n";
    gotoxy(i,j+2) ;cout << "# ## #  #  # #  #  ####   ####   #    #  ####  ####  #   #  ####  #  #\n";
    gotoxy(i,j+3) ;cout << "#    #  #  #  # #  #          #  #    #  #     #     ####   #     ###\n";
    gotoxy(i,j+4) ;cout << "#    #  #  #   ##  #          #  # ## #  #     #     #      #     #  #\n";
    gotoxy(i,j+5) ;cout << "#    #  #  #    #  ####   ####   #    #  ####  ####  #      ####  #   #\n\n\n\n";

}


void GioiThieu() {
    txtColor(2);
    XuatKhoiDong(23,1);

    gotoxy(23,12); cout << "1. PLAY";
    gotoxy(23,15); cout << "2. LEVEL";
   // gotoxy(23,18); cout << "3. HIGHSCORE";
    gotoxy(23,18); cout << "3. INTRODUCTS";
    gotoxy(23,21); cout << "4. EXIT\n\n\n\n";
    gotoxy(8,23); cout << "Chon cac so 1/2/3/4 tu ban phim de chon cac muc !";
    txtColor(7);
    //Sleep(1000);
    char key= _getch();
    switch(key) {
    case '1' :
        PlayGame();
        break;
    case '2' :
        ChonMucDo(2);
        break;
    case '4' :
        exit(1);
        break;
    case '3' :
        string path = "HuongdanDomin.txt";
        DocFileHuongDan(path);
        break;
    }
}

void ChonMucDo(int i) {
    clearScreen();
    txtColor(2);
    gotoxy(23,6); cout << " MUC DO. \n\n";

    gotoxy(23,12); cout << "1. DE";
    gotoxy(23,15); cout << "2. THUONG";
    gotoxy(23,18); cout << "3. KHO";
    gotoxy(23,21); cout << "4. RAT KHO\n\n\n";

    gotoxy(8,23); cout << "Chon cac so 1/2/3/4 tu ban phim de chon cac muc !";
    char M = _getch();

    if(M=='1') {
        switch(i) {
        case 1:
            he = 6; wi = 10; SoMin =9;
            break;
        case 2:
            he = 8; wi = 14; SoMin =12;
            break;
        case 3:
            he = 10; wi = 15; SoMin =15;
            break;
        }
    } else if (M=='2') {
        switch(i) {
        case 1:
            he = 10; wi = 15; SoMin =25;
            break;
        case 2:
            he = 18; wi = 28; SoMin =84;
            break;
        case 3:
            he = 25; wi = 35; SoMin =140;
            break;
        }
    }
    else if (M=='3'){
        switch(i) {
        case 1:
            he = 10; wi = 15; SoMin =38;
            break;
        case 2:
            he = 18; wi = 28; SoMin =126;
            break;
        case 3:
            he = 25; wi = 35; SoMin =210;
            break;
        }
    }else {
        switch(i) {
        case 1:
            he = 10; wi = 15; SoMin =75;
            break;
        case 2:
            he = 18; wi = 28; SoMin =252;
            break;
        case 3:
            he = 25; wi = 35; SoMin =430;
            break;
        }
    }
    printf("\n\n\tBAM ENTER DE CHOI \n\tBAM ESC DE THOAT LUON");
    char tmp = getch();
    if(tmp == 13){
        PlayGame();
    }
    if(tmp == 27){
        clearScreen();
        GioiThieu();
    }
    txtColor(7);
}

void clearScreen() {
    system("cls");
}

void DocFileHuongDan(string path) {
    clearScreen();
    ifstream file(path);
    if(file.is_open()) {
        string line;
        int yy =5;
        while(!file.eof()) {
            getline(file,line);
            gotoxy(8,yy); txtColor(12);
            cout << line << endl;
            yy+=2;
        }
    }
    else {
        gotoxy(8,5); txtColor(12);
        cout << "Loi khi mo file :(";

    }
    file.close();
    printf("\n\n\tBAM ENTER DE TRO LAI \n\tBAM ESC DE THOAT LUON");
    char tmp ;
    do {
        tmp = getch();
        if(tmp == 13){
            clearScreen();
            GioiThieu();
        }
        if(tmp == 27){
            clearScreen();
            GioiThieu();
            exit(1);
        }
    }while(tmp!=27 ||tmp!=13);
    txtColor(7);
}
