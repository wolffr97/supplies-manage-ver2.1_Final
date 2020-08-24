#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <iomanip>
#define true 1
#define false 0
#include "draw.h"
#define max 500
#define maxCTHD 20



using namespace std;

enum Colors {
	black,          //  0 text color - multiply by 16, for background colors
	dark_blue,      //  1
	dark_green,     //  2
	dark_cyan,      //  3
	dark_red,       //  4
	dark_magenta,   //  5
	dark_yellow,    //  6
	light_gray,     //  7
	dark_gray,      //  8
	light_blue,     //  9
	light_green,    // 10
	light_cyan,     // 11
	light_red,      // 12
	light_magenta,  // 13
	light_yellow,   // 14
	white           // 15
};

void color_set() {
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int k = 0; k <= 255; k++) {
		SetConsoleTextAttribute(hConsoleColor, 245);
		// cout << k << " - Change color!  ";
		if (k % 3 == 0) cout << endl;
	}
}
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
bool Check_ASCII_words(char word) {
	return(word >= 32 && word <= 127);
}
bool Check_Number(string a ){
	for(int i=0;i< a.size();i++)
		{
			if((a[i] > '9') || (a[i] < '0') || a.empty() == true)
			{
				return false;
			}
		}
	return true;	
}
string Cut_enter(string &s){
	
	if (s.back() == '\n')
	s.pop_back();
	if (s.front() == '\n')
	s = s.erase(0,1);
	return s;
	
}
void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetBGColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Cau truc dl 
// khai bao du lieu cua 1 phan tu cua mang
struct NgayThang {
	string ngay, thang, nam;

};
struct ngaylap{
	int ngay,thang,nam;
};
// khai bao du lieu cua 1 phan tu cua mang
struct CT_HOADON_DATA {
	string MAVT;
	int Soluong;
	float Dongia;
	float VAT;
	int Trangthai;// 1:mua 0:da tra
};
typedef struct CT_HOADON_DATA CTHD_DATA;

//day da la list hoadon
struct CT_HOADON {
	CTHD_DATA hd_data[maxCTHD];//da thay.
	int n = 0;//so luong phan tu trong list
};
typedef struct CT_HOADON CTHD;

// du lieu cua 1 NOde
struct HOADON_DATA {
	string SoHD;
	ngaylap NgaylapHD;
	string Loai;
	CTHD cthd;// 
};
typedef struct HOADON_DATA HOADON;

// 1 node trong list
struct Node_HOADON {// nut
	HOADON hd;
	Node_HOADON* pNext;//con tro toi node tt// p=lk(next)
};
typedef struct Node_HOADON* DSHD;

// data cua 1 nhan vien
struct NHANVIEN_DATA {
	int MANV;
	string HO;
	string TEN;
	string PHAI;
	string CMND;// chuoi //
	DSHD first_hd = NULL;//con tro toi ds hoa don // thuc chat la node dau //first_HD //=null/da
};
typedef struct NHANVIEN_DATA NVDT;

// list nhan vien
struct DS_NHANVIEN {
	NVDT* nvdt[max];
	int n = 0;
};

// vat tu data
struct VATTU_DATA {
	string MAVT;
	string TenVT;
	string DVT;
	float SLT;
};
typedef struct VATTU_DATA VTDT;

// CAY NHI PHAN
struct TREE_VATTU {
	VTDT vtdt;
	TREE_VATTU* pLeft;
	TREE_VATTU* pRight;
};
typedef TREE_VATTU* TREE;

struct position {
	int x, y;
};


string Cut_Space(string &s){
	int i,n,j;
	int dem = 0;
	
	n=s.size();
	
		for(i=0;i<n;i++)
		{
			if((s[i]==' ')&&(s[i+1]==' '))
			{
				dem++;
				for(j=i;j<n;j++)
				{
					s[j]=s[j+1];
				}
				n--;	//so ki tu cua chuoi giam xuong
				i--;	//sau buoc nay thi i se tang (vong for) nen giam no xuong
			}
		}
		
	for (i=0;i<dem;i++){
		s.pop_back();
	}
	if (s.back() == ' ')
	s.pop_back();
	if (s.front() == ' ')
	s = s.erase(0,1);
	return s;
	
}
////////////////////////////////////////////////////////////////////////////////////
// BIEN TOAN CUC TEST

DS_NHANVIEN nv;
NVDT nvdt;
VTDT vtdt;
position vitricase5 = {0,0};
position vitricase3 = {0,0};
TREE T;
int SoVatTu_Auto;
int SoHoaDon_Auto;
string Tenvattu_fix ;
string Donvitinh_VT_Fix;
long long tong ;
ofstream fileout;
ifstream filein;
int lcnhapxuat ;

///////////////////////////////////////////////////////////////////////////////////
// TAO THONG TIN 1 NHAN VIEN DATA
int Insert_list_CTHD (CTHD &list_CTHD,int i , CTHD_DATA INFO){
	
	
	if ( i<0 || i > list_CTHD.n || list_CTHD.n == 0)
	return 0;
	//if (i == 0) i=1;
	for (int j = list_CTHD.n ; j >=i; j--)
	
	 list_CTHD.hd_data[j+1] = list_CTHD.hd_data[j];
	 list_CTHD.hd_data[i] = INFO;
	 //list_CTHD.sizeHD ++;
	 
	return 1;
}
int Count_amount_Hoadon(DS_NHANVIEN NhanVien){
	DSHD q;
		int SoHoaDon = 0;
		for ( int i = 0; i < NhanVien.n;i++){
			q = NhanVien.nvdt[i]->first_hd;
				for (q; q != NULL ; q = q->pNext){
					SoHoaDon++;			
				}
		}	
					   	
	return SoHoaDon;
	
}
void Write_File_HD_CTHD(ofstream &fileout,DS_NHANVIEN NhanVien){
	fileout.open("HD3.TXT",ios::out|ios::trunc);
	if (fileout.fail() == true)
	cout << "file nl";
	else {
			fileout << Count_amount_Hoadon(NhanVien) << "\t";
			fileout << SoHoaDon_Auto << "\n";
	for ( int i = 0; i < NhanVien.n;i++){
		DSHD q = NhanVien.nvdt[i]->first_hd;
		NVDT *p = NhanVien.nvdt[i];
			for (q; q != NULL ; q = q->pNext){
				fileout <<p->MANV << "\n";
				fileout << q->pNext->hd.SoHD << "	";
				fileout << q->pNext->hd.Loai << "	";
				fileout << q->pNext->hd.NgaylapHD.ngay << "	";
				fileout << q->pNext->hd.NgaylapHD.thang << "	";
				fileout << q->pNext->hd.NgaylapHD.nam << "\n";
				fileout << q->hd.cthd.n << "\n";
				for (int j = 0;j < q->hd.cthd.n;j++){
			
					fileout << q->hd.cthd.hd_data[j].MAVT <<"	";
					fileout << q->hd.cthd.hd_data[j].Soluong <<"	";
					fileout << q->hd.cthd.hd_data[j].Dongia <<"\n";
								}
							}	
						}
	}
	fileout.close();
}
void Write_File_List_NV(ofstream &fileout,DS_NHANVIEN NhanVien){
		
	
	fileout.open("NhanVien.TXT",ios::out|ios::trunc);
	
	for (int i = 0; i <NhanVien.n; i++){
		
		fileout << NhanVien.nvdt[i]->MANV << "	" ;
		fileout << NhanVien.nvdt[i]->HO << "	" ;
		fileout << NhanVien.nvdt[i]->TEN << "	";
		fileout << NhanVien.nvdt[i]->PHAI << "\n";
	}
	fileout.close();
}
NVDT Create_NhanVienDT(NVDT nvdt) {
	gotoxy(110, 6);
	cin >> nvdt.MANV;
	cin.ignore();
	gotoxy(102, 9);
	getline(cin, nvdt.HO);
	gotoxy(120, 9);
	getline(cin, nvdt.TEN);
	gotoxy(103, 12);
	cin >> nvdt.PHAI;
	gotoxy(103, 15);
	cin >> nvdt.CMND;
	return nvdt;
}
CTHD_DATA Creat_CTHD(CTHD_DATA cthd,int i){
	gotoxy(52,10+i);// nhap ma vt
	cin>>cthd.MAVT;
	gotoxy(64,10+i);
	cin>>cthd.Soluong;
	gotoxy(80,10+i);
	cin>>cthd.Dongia;
//	gotoxy(85,10);
//	cout<<"Nhap % thue: ";
//	cin>>cthd.VAT;
//	gotoxy(95,10);
//	cout<<"Trang thai: ";
//	cin>>cthd.Trangthai;
	return cthd;
	
}
DSHD Creat_Node_Dshd(HOADON DATA_HD1){
	
	DSHD p = new Node_HOADON ; /// cap phat vung nho cho NODE p
	//p->hd.cthd = new CTHD ;
	p->hd = DATA_HD1;
	p->pNext = NULL;
	return p;
}
DS_NHANVIEN Add_NhanVien(DS_NHANVIEN nv, NVDT nvdt) {
	if (nv.n >= 500) {
		cout << "Danh sach day\n";
	}
	else {
		nv.nvdt[nv.n] = new NVDT();
		nv.nvdt[nv.n]->MANV = nvdt.MANV;
		nv.nvdt[nv.n]->HO = nvdt.HO;
		nv.nvdt[nv.n]->TEN = nvdt.TEN;
		nv.nvdt[nv.n]->PHAI = nvdt.PHAI;
		nv.nvdt[nv.n]->CMND = nvdt.CMND;
		nv.nvdt[nv.n]->first_hd = NULL;
		nv.n++;
	}
	return nv;
}
int Find_Node_Tree(TREE T,string s)
{

		 if (T == NULL)
	 {
	 	
		return 0;
		}
     
     if (Cut_enter(T->vtdt.MAVT ) > s) {
     	if (Find_Node_Tree(T->pLeft,s) == 1)
     		return 1;
     	else return 0;	
     	
	 }
     else if (Cut_enter(T->vtdt.MAVT ) < s){
    	if (Find_Node_Tree(T->pRight,s) == 1)
     		return 1;
     	else return 0;      	
	 }
	
	 else{
	  
		gotoxy(30,10+vitricase5.y);
    	cout << T->vtdt.TenVT;
     	return 1;
	 }
	
     
      
    
}
int Find_Print_VT_case5(TREE root,string s,int i){
	if (T == NULL)
	 {
	 	
		return 0;
		}
     
     if (Cut_enter(root->vtdt.MAVT ) > s) {
        if(Find_Print_VT_case5(root->pLeft,s,i) == 1)
			return 1;
		else return 0;	
	 }
     else if (Cut_enter(root->vtdt.MAVT ) < s){
        if(Find_Print_VT_case5(root->pRight,s,i) == 1)
			return 1;
		else return 0;
      	
	 }
	
	 else{
	  
			gotoxy(85,10+vitricase5.y);
	  		cout << "/" << root->vtdt.DVT;
			if( lcnhapxuat == 1){
				if(root->vtdt.SLT < i){
				gotoxy(90,6);
				cout << root->vtdt.TenVT<< " con " << root->vtdt.SLT << " " << root->vtdt.DVT;
				
				getch();
				
				gotoxy(90,6);
				cout << "                       ";
			//	cin.ignore();
				return 0;					
				}
				else {
					root->vtdt.SLT = root->vtdt.SLT - i;
					return 1;
				}
		
     			return 1;
			}
			else if( lcnhapxuat == 0){
				root->vtdt.SLT = root->vtdt.SLT + i;
				return 1;
			}
     	
	 }
	
      
     
     }
int Find_ViTriNV(DS_NHANVIEN nv, int manv) {
	for (int i = 0; i < nv.n; i++) {
		if (nv.nvdt[i]->MANV == manv)
			return i;
	}
	return -1;// 0 thi mang bd =0
}
int Search_Mavt(CTHD list_CTHD,string Mavt){
	for (int vitri =0; vitri < list_CTHD.n; vitri ++)
	if (list_CTHD.hd_data[vitri].MAVT == Mavt )
	return vitri;
	return -1;
}
void Print_Number_With_point (int s){
	char Num[50];
	itoa(s,Num,10);
	string xuoi = string(Num);
	Cut_Space(xuoi);
	string nguoc;
	int dem = 0;
	for (int i = Cut_Space(xuoi).size(); i >= 0; i-- ){
		
	//	cout << xuoi[i];
		nguoc += xuoi[i];
		if(dem % 3 == 0 && dem != xuoi.size() && dem != 0){
	//	cout << ",";
		nguoc += ",";	
		}
		
		dem++;
	}
	 
	for (int i = nguoc.size(); i >= 0 ; i--  ){
		cout << nguoc[i];	
	}
	cout << "VND";
}
int DEL_ITEM_CTHD(CTHD &list_CTHD, int i){
	
	int j;
	if (i < 0 || i > list_CTHD.n || list_CTHD.n == 0 )
	return 0;
	if (i == 0) i=1;
	for ( j = i; j < list_CTHD.n; j++)
	list_CTHD.hd_data[j-1] = list_CTHD.hd_data [j];
	list_CTHD.n--;
	return 1;
		
}
int Fix_VT_Xuat(TREE &root,string s,int i)
{
	if (root == NULL)
	 {
	 	
		return 0;
	}
	else {

     
     if (Cut_enter(root->vtdt.MAVT ) > s) {

		if (Fix_VT_Xuat(root->pLeft,s,i) == 1) 
		return 1;
     	else return 0;
	 }
     else if (Cut_enter(root->vtdt.MAVT) < s){
		if (Fix_VT_Xuat(root->pRight,s,i) == 1) 
		return 1;
     	else return 0;      	

	 }
	
	 else{
	  
	//	cout << T->DATA.TenVatTu <<"\n";
	//	cout << T->DATA.TenVatTu <<"\n";
	//	cout << T->DATA.SoLuongTon <<"\n";
	//	cout << i <<"\n";
		root->vtdt.SLT = root->vtdt.SLT+ i;
	//	cout << T->DATA.SoLuongTon <<"\n";
     	return 1;
	 }
	
      	
	}
}
int Fix_VT_Nhap(TREE &root,string s,int i)
{
	if (root == NULL)
	 {
	 	
		return 0;
	}
	else {

     
     if (Cut_enter(root->vtdt.MAVT ) > s) {

		if (Fix_VT_Nhap(root->pLeft,s,i) == 1) 
		return 1;
     	else return 0;
	 }
     else if (Cut_enter(root->vtdt.MAVT ) < s){
		if (Fix_VT_Nhap(root->pRight,s,i) == 1) 
		return 1;
     	else return 0;      	

	 }
	
	 else{
	  
	//	cout << T->DATA.TenVatTu <<"\n";
	//	cout << i;
		root->vtdt.SLT = root->vtdt.SLT - i;
     	return 1;
	 }
	
      	
	}
}
int DEL_ITEM_NHANVIEN(DS_NHANVIEN& NhanVien, int i) {// i la vt

	int j;
	if (i < 0 || i > NhanVien.n || NhanVien.n == 0) {
		return 0;
	}
	//	if (i == 0) i=1;
	for (j = i; j < NhanVien.n; j++) {
		NhanVien.nvdt[j] = NhanVien.nvdt[j + 1];
	}
	NhanVien.n--;
	return 1;
}
int Is_NhanVien_Have_HD(DS_NHANVIEN NhanVien, int manv) {
	for (int i = 0; i < NhanVien.n; i++) {
		if (NhanVien.nvdt[i]->MANV == manv) {
			if (NhanVien.nvdt[i] != NULL) {
				return 1;
			}
		}
	}
	return 0;
}

DS_NHANVIEN Edit_NhanVien(DS_NHANVIEN nv, NVDT nvdt, int manv) {
	nv.nvdt[Find_ViTriNV(nv, manv)]->MANV = nvdt.MANV;
	nv.nvdt[Find_ViTriNV(nv, manv)]->HO = nvdt.HO;
	nv.nvdt[Find_ViTriNV(nv, manv)]->TEN = nvdt.TEN;
	nv.nvdt[Find_ViTriNV(nv, manv)]->PHAI = nvdt.PHAI;
	nv.nvdt[Find_ViTriNV(nv, manv)]->CMND = nvdt.CMND;
}
void Duyet_NhanVien_case3(DS_NHANVIEN nv, int n) {
	// khong phan trang duoc 
	for (int i = 0; i < 20; i++) {
		gotoxy(10, 5 + i);
		cout << "        ";
		gotoxy(25, 5 + i);
		cout << "                               ";
		gotoxy(60, 5 + i);
		cout << "         ";
		gotoxy(68, 5 + i);
		cout << "	         ";
		
	}
	NVDT Data;

	for (int i = 0; i < nv.n; i++) {//buble sort
		for (int j = 0; j < nv.n; j++) {
			if (strcmp(nv.nvdt[i]->TEN.c_str(), nv.nvdt[j]->TEN.c_str()) < 0) {

				Data.MANV = nv.nvdt[j]->MANV;
				Data.HO = nv.nvdt[j]->HO;
				Data.TEN = nv.nvdt[j]->TEN;
				Data.PHAI = nv.nvdt[j]->PHAI;
				Data.CMND = nv.nvdt[j]->CMND;

				nv.nvdt[j]->MANV = nv.nvdt[i]->MANV;
				nv.nvdt[j]->HO = nv.nvdt[i]->HO;
				nv.nvdt[j]->TEN = nv.nvdt[i]->TEN;
				nv.nvdt[j]->PHAI = nv.nvdt[i]->PHAI;
				nv.nvdt[j]->CMND = nv.nvdt[i]->CMND;

				nv.nvdt[i]->MANV = Data.MANV;
				nv.nvdt[i]->HO = Data.HO;
				nv.nvdt[i]->TEN = Data.TEN;
				nv.nvdt[i]->PHAI = Data.PHAI;
				nv.nvdt[i]->CMND = Data.CMND;

			}
			else if (strcmp(nv.nvdt[i]->TEN.c_str(), nv.nvdt[j]->TEN.c_str()) == 0) {
				if (strcmp(nv.nvdt[i]->HO.c_str(), nv.nvdt[j]->HO.c_str()) < 0) {
					Data.MANV = nv.nvdt[j]->MANV;
					Data.HO = nv.nvdt[j]->HO;
					Data.TEN = nv.nvdt[j]->TEN;
					Data.PHAI = nv.nvdt[j]->PHAI;
					Data.CMND = nv.nvdt[j]->CMND;

					nv.nvdt[j]->MANV = nv.nvdt[i]->MANV;
					nv.nvdt[j]->HO = nv.nvdt[i]->HO;
					nv.nvdt[j]->TEN = nv.nvdt[i]->TEN;
					nv.nvdt[j]->PHAI = nv.nvdt[i]->PHAI;
					nv.nvdt[j]->CMND = nv.nvdt[i]->CMND;

					nv.nvdt[i]->MANV = Data.MANV;
					nv.nvdt[i]->HO = Data.HO;
					nv.nvdt[i]->TEN = Data.TEN;
					nv.nvdt[i]->PHAI = Data.PHAI;
					nv.nvdt[i]->CMND = Data.CMND;
				}
			}

		}

	}
	int i = 0;
	int j = n - 20;
	if (nv.n == 0)
		cout << " danh sach rong ";
	gotoxy(10, 5);
	for (j; j < n; j++) {
		if(j==nv.n){
			break;
		}
		if(nv.n+20<n){
			break ;
		}
		gotoxy(10, 5 + i);
		cout << nv.nvdt[j]->MANV << endl;
		gotoxy(25, 5 + i);
		cout << nv.nvdt[j]->HO << " " << nv.nvdt[j]->TEN << endl;
		gotoxy(60, 5 + i);
		cout << nv.nvdt[j]->PHAI << endl;
		gotoxy(72, 5 + i);
		cout << nv.nvdt[j]->CMND << endl;
		i++;
	}
}
void Duyet_NhanVienDT(DS_NHANVIEN nv, int n) {
	// khong phan trang duoc 
	for (int i = 0; i < 20; i++) {
		gotoxy(33, 5 + i);
		cout << "        ";
		gotoxy(50, 5 + i);
		cout << "                               ";
		gotoxy(85, 5 + i);
		cout << "         ";
		gotoxy(90, 5 + i);
		cout << "	         ";
	}
	NVDT Data;
	
	for (int i = 0; i < nv.n; i++) {//buble sort
		for (int j = 0; j < nv.n; j++) {
			if (strcmp(nv.nvdt[i]->TEN.c_str(), nv.nvdt[j]->TEN.c_str()) < 0) {

				Data.MANV = nv.nvdt[j]->MANV;
				Data.HO = nv.nvdt[j]->HO;
				Data.TEN = nv.nvdt[j]->TEN;
				Data.PHAI = nv.nvdt[j]->PHAI;
				Data.CMND = nv.nvdt[j]->CMND;

				nv.nvdt[j]->MANV = nv.nvdt[i]->MANV;
				nv.nvdt[j]->HO = nv.nvdt[i]->HO;
				nv.nvdt[j]->TEN = nv.nvdt[i]->TEN;
				nv.nvdt[j]->PHAI = nv.nvdt[i]->PHAI;
				nv.nvdt[j]->CMND = nv.nvdt[i]->CMND;

				nv.nvdt[i]->MANV = Data.MANV;
				nv.nvdt[i]->HO = Data.HO;
				nv.nvdt[i]->TEN = Data.TEN;
				nv.nvdt[i]->PHAI = Data.PHAI;
				nv.nvdt[i]->CMND = Data.CMND;

			}
			else if (strcmp(nv.nvdt[i]->TEN.c_str(), nv.nvdt[j]->TEN.c_str()) == 0) {
				if (strcmp(nv.nvdt[i]->HO.c_str(), nv.nvdt[j]->HO.c_str()) < 0) {
					Data.MANV = nv.nvdt[j]->MANV;
					Data.HO = nv.nvdt[j]->HO;
					Data.TEN = nv.nvdt[j]->TEN;
					Data.PHAI = nv.nvdt[j]->PHAI;
					Data.CMND = nv.nvdt[j]->CMND;

					nv.nvdt[j]->MANV = nv.nvdt[i]->MANV;
					nv.nvdt[j]->HO = nv.nvdt[i]->HO;
					nv.nvdt[j]->TEN = nv.nvdt[i]->TEN;
					nv.nvdt[j]->PHAI = nv.nvdt[i]->PHAI;
					nv.nvdt[j]->CMND = nv.nvdt[i]->CMND;

					nv.nvdt[i]->MANV = Data.MANV;
					nv.nvdt[i]->HO = Data.HO;
					nv.nvdt[i]->TEN = Data.TEN;
					nv.nvdt[i]->PHAI = Data.PHAI;
					nv.nvdt[i]->CMND = Data.CMND;
				}
			}

		}

	}
	int i = 0;
	int j = n - 20;
	if (nv.n == 0)
		cout << " danh sach rong ";
	gotoxy(10, 5);
	for (j; j < n; j++) {
		if(j==nv.n){
			break;
		}
		if(nv.n+20<n){
			break ;
		}
		gotoxy(33, 5 + i);
		cout << nv.nvdt[j]->MANV << endl;
		gotoxy(50, 5 + i);
		cout << nv.nvdt[j]->HO << " " << nv.nvdt[j]->TEN << endl;
		gotoxy(85, 5 + i);
		cout << nv.nvdt[j]->PHAI << endl;
		gotoxy(96, 5 + i);
		cout << nv.nvdt[j]->CMND << endl;

		i++;


	}
	
}
/////////////////////////////////////////////////////////////////////////////////
void Creat_Data_Tree(VTDT &Data){
	gotoxy(103,6);
	
	Data.MAVT = to_string(SoVatTu_Auto);
	cout << Data.MAVT;
	while (Data.TenVT.empty()){
	gotoxy(103,9);
	cout << "                   ";
	gotoxy(103,9);
//	cin.ignore();
	getline(cin,Data.TenVT);
	Data.TenVT= Cut_Space(Data.TenVT);
	}
	while (Data.DVT.empty()){
	gotoxy(103,12);
	cout << "                   ";
	
	gotoxy(103,12);
//	cin.ignore();
	getline(cin,Data.DVT);
	Data.DVT= Cut_Space(Data.DVT);
	}
	while ( true){
		gotoxy(103,15);
		cout <<"        ";
		gotoxy(103,15);
		string s ;
		cin >> s;
		if (Check_Number(s ) == true){
		Data.SLT= atoi(s.c_str());
		break;
		}
	}
	
}
void Creat_Tree(TREE &T){
	
	T = NULL;
	
}
void Add_Node_Tree(TREE &VT,VATTU_DATA vtdt){
	if (VT == NULL){
			TREE_VATTU *p = new TREE_VATTU;
			p->vtdt = vtdt;
			p->pLeft = NULL;
			p->pRight = NULL;
			VT = p;
	}
	else {
		
		if (VT->vtdt.MAVT > vtdt.MAVT) {
			
			Add_Node_Tree(VT->pLeft,vtdt);
		}
		else if ( VT->vtdt.MAVT < vtdt.MAVT){
			
			Add_Node_Tree(VT->pRight,vtdt);
		}
		
	}
	
}
void Read_Tree(ifstream &filein,TREE &T){
	filein.open("Tree.txt",ios_base::in);
	if (filein.fail()== true){	
		cout << "FILE D TON TAI";	
	}else {		
		VTDT Data;
		int sovattu;
		filein >>  sovattu;
		filein >>  SoVatTu_Auto;
		string s;
		getline(filein,s);
		for ( int i = 0; i < sovattu; i++ ){
			getline(filein ,Data.MAVT,'	');
			getline(filein , Data.TenVT,'	');
			getline(filein , Data.DVT,'	');
			filein >> Data.SLT;
			getline(filein,s);
		//	getline(cin,s);
			Add_Node_Tree(T,Data);
		}
	}
	filein.close();	
}
void Add_Node_Tree_case2(TREE &T,VTDT Data){
	if (T == NULL){
			TREE_VATTU *p = new TREE_VATTU ;
			p->vtdt= Data;
			p->pLeft = NULL;
			p->pRight = NULL;
			T = p;
	}
	else {
		
		if (strcmp(T->vtdt.TenVT.c_str(),Data.TenVT.c_str()) > 0 ) {
			
			Add_Node_Tree_case2(T->pLeft,Data);
		}
		else if (  strcmp(T->vtdt.TenVT.c_str(),Data.TenVT.c_str()) < 0 ){
			
			Add_Node_Tree_case2(T->pRight,Data);
		}
		
	}
}
void Read_Tree_case2(ifstream &filein,TREE &T){
	filein.open("Tree.txt",ios_base::in);
	if (filein.fail()== true){	
		cout << "FILE D TON TAI";	
	}else {
		VTDT Data;
		int sovattu;
		filein >>  sovattu;
		string s;
		getline(filein,s);
		for ( int i = 0; i < sovattu; i++ ){
			getline(filein ,Data.MAVT,'	');
			getline(filein , Data.TenVT,'	');
			getline(filein , Data.DVT,'	');
			filein >> Data.SLT;
		//	getline(cin,s);
			Add_Node_Tree_case2(T,Data);
		}
	}
	filein.close();	
}
int Count_Node_Tree( TREE root){
	int count = 0;
	TREE_VATTU *p;
	while( root ){
		if( root->pLeft == NULL ){
			count = count + 1;
			root = root->pRight;
		}
		else{
			p = root->pLeft;
			while(p->pRight && p->pRight != root ){
				p = p->pRight;
			}
			if( p->pRight == NULL ){
				p->pRight = root;
				count = count + 1;
				root = root->pLeft;
			}
			else{
				p->pRight = NULL;
			//	cout<< root->data << " ";
				root = root->pRight;
			}
		}
	}
	
	
	 return count;
}

void Write_Tree (ofstream &fileout,TREE root){
	
	fileout.open("Tree.txt",ios::out|ios::trunc);
	fileout << Count_Node_Tree(root) << " \t";
	fileout << SoVatTu_Auto << "\n";
	TREE_VATTU *p;
	while( root ){
		if( root->pLeft == NULL ){
			fileout << root->vtdt.MAVT << "	";
			fileout << root->vtdt.TenVT << "	";
			fileout << root->vtdt.DVT << "	";		
			fileout << root->vtdt.SLT << "\n";
			root = root->pRight;
		}
		else{
			p = root->pLeft;
			while(p->pRight && p->pRight != root ){
				p = p->pRight;
			}
			if( p->pRight == NULL ){
				p->pRight = root;
					fileout << root->vtdt.MAVT << "	";
					fileout << root->vtdt.TenVT << "	";
					fileout << root->vtdt.DVT << "	";		
					fileout << root->vtdt.SLT << "\n";
				root = root->pLeft;
			}
			else{
				p->pRight = NULL;
			//	cout<< root->data << " ";
				root = root->pRight;
			}
		}
	}
	fileout.close();
}

int  Find_Node_Case1(TREE root,string s){
	if (root == NULL){
		return 0;
	}
    if (Cut_enter(root->vtdt.MAVT) > s) {
     	if (Find_Node_Case1(root->pLeft,s) == 1)
	 		return 1;
	 	else return 0;	
	}else if (Cut_enter(root->vtdt.MAVT) < s){
     	if (Find_Node_Case1(root->pRight,s) == 1)
	 		return 1;
	 	else return 0;
      	
	}else{
	 		gotoxy(103,6);
	 		cout << root->vtdt.MAVT;
			gotoxy(103,9);
			cout << root->vtdt.TenVT;
			gotoxy(103,12);
			cout << root->vtdt.DVT;
			Tenvattu_fix = root->vtdt.TenVT;
			Donvitinh_VT_Fix = root->vtdt.DVT; 	  				
			return 1;
	}	
}
int Find_Node_Tree_case1(TREE T,string s){
	if (T == NULL){
		return 0;
	}
    if (Cut_enter(T->vtdt.MAVT) > s) {
     	if (Find_Node_Tree_case1(T->pLeft,s) == 1)
     		return 1;
     	else return 0;	
    }else if (Cut_enter(T->vtdt.MAVT) < s){
    	if (Find_Node_Tree_case1(T->pRight,s) == 1)
     		return 1;
     	else return 0;      	
	}else{
	  return 1;
	}    
}
void Find_Node_Delete(TREE &X, TREE &Y){
	if (Y->pLeft != NULL){
		Find_Node_Delete(X,Y->pLeft);
	}else {
		X->vtdt = Y->vtdt;
		X = Y;
		Y = Y->pRight;	
	}
}

int Delete_Node_Tree(TREE &root, string s ){
	if ( root == NULL){
		return 0;
	}else {
		if ( s < root->vtdt.MAVT){
			 if (Delete_Node_Tree(root->pLeft,s ) == 1)
			 return 1;
			 else return 0;
		}else if ( s > root->vtdt.MAVT){
			 if (Delete_Node_Tree(root->pRight,s ) == 1)
			 return 1;
			 else return 0;
		}else {
			TREE_VATTU *X = new TREE_VATTU ;
			X = root;
			if ( root->pLeft == NULL){
				root = root->pRight;
			}
			else if ( root->pRight == NULL){
				root = root->pLeft;
			}
			else {
				TREE_VATTU *Y = new TREE_VATTU;
				Y = root->pRight;
				Find_Node_Delete(X,Y);
			}
			delete X;	
			return 1;
		}
		 		 
	}
	
} 
//int traverse_Case_7(struct NHANVIEN NhanVien,struct ngaylap NgayDau,struct ngaylap NgayCuoi,int t){
//
//	//////////////////////////Xuat Thong Tin Vao Case 7/////////////////////////////
//	for (int t = 0; t < 20; t++){
//		gotoxy(22,10+t);
//		cout << "         ";
//		gotoxy(35,10+t);
//		cout <<	"            ";
//		gotoxy(52,10+t);
//		cout << "       ";
//		gotoxy(63,10+t);
//		cout << "                            ";
//		gotoxy(100,10+t);
//		cout << "                ";
//		
//	}
//	int dong = 0;
//	int HoaDonDaIN = 0;
//
//		for ( int i = 0; i < Pos_Empty_NV(NhanVien);i++){
//			struct HOADON *q = NhanVien.NV[i]->HD;
//			struct DATA_NHANVIEN *p = NhanVien.NV[i];
//			for (q ; q != NULL ; q = q->pNext){
//				
//				if ((Compare_Date(q->DATA_HD.ngaylap, NgayDau) == 1 || Compare_Date(q->DATA_HD.ngaylap, NgayDau) == 0) && (Compare_Date(q->DATA_HD.ngaylap, NgayCuoi) == -1 || Compare_Date(q->DATA_HD.ngaylap, NgayDau) == 0)){
//					if (HoaDonDaIN >= t-20 && HoaDonDaIN < t){
//					
//					gotoxy(22,10+dong);
//					cout << 	q->DATA_HD.SoHD;
//					gotoxy(35,10+dong);
//					cout <<		q->DATA_HD.ngaylap.ngay <<"/"<< q->DATA_HD.ngaylap.thang <<"/"<<q->DATA_HD.ngaylap.nam;
//					gotoxy(52,10+dong);
//					cout << q->DATA_HD.loai;
//					gotoxy(63,10+dong);
//					cout << p->HO << " " << p->TEN;
//					gotoxy(100,10+dong);
//					int tong = 0;
//					for (int j = 0; j < Pos_Empty_CTHD(q->DATA_HD.CT_HD); j++){
//						
//						tong += (q->DATA_HD.CT_HD->INFO[j].SoLuong)*(q->DATA_HD.CT_HD->INFO[j].DonGia);						
//					}
//					//cout << fixed << setprecision(0) << tong ;
//					Print_Number_With_point (tong);
//					dong ++;
//					}
//					HoaDonDaIN ++;
//				}   
//			}	
//		}
//	
//	
//	return HoaDonDaIN;
//}
void Clear_list_CTHD( CTHD list_CTHD){
	
	for (int i =0; i < list_CTHD.n; i ++){
		list_CTHD.hd_data[i].MAVT ="";
		list_CTHD.hd_data[i].Soluong = 0;
		list_CTHD.hd_data[i].Dongia = 0;
	}
	

	}
int Search_Ma_HD(DS_NHANVIEN NhanVien, string MaHD){
 	struct Node_HOADON* q;
	for ( int i = 0; i < NhanVien.n;i++){
		q=NhanVien.nvdt[i]->first_hd;
		for (q ; q != NULL ; q = q->pNext){ 
			if(q->hd.SoHD==MaHD)
			return i;
		}
	}
	return -1;
}
void Traverse_Tree_case_6 (TREE root,string s,int i){
	TREE_VATTU *p;
	while( root ){
		if( root->pLeft == NULL ){
			if(atoi(root->vtdt.MAVT.c_str()) == atoi(s.c_str())){
			cout <<root->vtdt.TenVT;
			gotoxy(85,10+i);
			cout << "/" << root->vtdt.DVT;
			
			}			
			root = root->pRight;
		}
		else{
			p = root->pLeft;
			while(p->pRight && p->pRight != root ){
				p = p->pRight;
			}
			if( p->pRight == NULL ){
				p->pRight = root;
			if(atoi(root->vtdt.MAVT.c_str()) == atoi(s.c_str())){
			cout <<root->vtdt.TenVT;
			gotoxy(85,10+i);
			cout << "/" << root->vtdt.DVT;
			}
			root = root->pLeft;
			}
			else{
				p->pRight = NULL;
			//	cout<< root->data << " ";
				root = root->pRight;
			}
		}
	}
}
void Traverse_Tree_case_7 (TREE root,string s,int i,int j){
	TREE_VATTU *p;
	while( root ){
		if( root->pLeft == NULL ){
			if(atoi(root->vtdt.MAVT.c_str()) == atoi(s.c_str())){
			cout <<root->vtdt.TenVT;
			gotoxy(85,10+i+j);
			cout << "/" << root->vtdt.DVT;
			
			}			
			root = root->pRight;
		}
		else{
			p = root->pLeft;
			while(p->pRight && p->pRight != root ){
				p = p->pRight;
			}
			if( p->pRight == NULL ){
				p->pRight = root;
			if(atoi(root->vtdt.MAVT.c_str()) == atoi(s.c_str())){
			cout <<root->vtdt.TenVT;
			gotoxy(85,10+i+j);
			cout << "/" << root->vtdt.DVT;
			}
			root = root->pLeft;
			}
			else{
				p->pRight = NULL;
			//	cout<< root->data << " ";
				root = root->pRight;
			}
		}
	}
}
void Traverse_Case_6(DS_NHANVIEN NhanVien){
	for (int t = 0; t < 17;t++){
	gotoxy(19,10+t);
	cout << "   ";
	gotoxy(29,10+t);
	cout << "                 ";
	gotoxy(55,10+t);
	cout << "     ";
	gotoxy(67,10+t);
	cout << "        ";
	gotoxy(78,10+t);
	cout << "            ";
	gotoxy(95,10+t);
	cout << "                 ";
	}
	gotoxy(95,28);
	cout << "                  ";
	char input;
	while(input != 27){
		gotoxy(68,2);
		cout << "                        ";
		gotoxy(72,3);
		cout << "                        ";
		gotoxy(72,4);
		cout << "                        ";		
		gotoxy(72,5);
		cout << "                        ";
		string MaHD;
		gotoxy(72,2);
		cin >> MaHD;
	if (Search_Ma_HD(NhanVien, MaHD) == -1){
		gotoxy(68,2);
		cout << " khong tim thay hoa don";
		input = getch();
	}
	else {
		for ( int i = 0; i < NhanVien.n;i++){
			 DSHD q = NhanVien.nvdt[i]->first_hd;
			 NVDT *p = NhanVien.nvdt[i];
		for (q; q != NULL ; q = q->pNext){ 
			if (q->hd.SoHD == MaHD)
			{	
				int Tong = 0;
				gotoxy(72,2);
				cout << q->hd.SoHD;
				gotoxy(72,3);
				cout << q->hd.Loai;
				gotoxy(72,4);
				cout << p->HO << " " << p->TEN;
				gotoxy(72,5);
				cout <<q->hd.NgaylapHD.ngay<< " / " << q->hd.NgaylapHD.thang << " / " << q->hd.NgaylapHD.nam;
				for (int j = 0; j < q->hd.cthd.n ; j++){
					gotoxy(19,10+j);
					cout << j+1;
					gotoxy(29,10+j);
					Traverse_Tree_case_6 (T,q->hd.cthd.hd_data[j].MAVT,j);
					gotoxy(55,10+j);
					cout << q->hd.cthd.hd_data[j].MAVT;
					gotoxy(67,10+j);
					cout <<q->hd.cthd.hd_data[j].Soluong;
					gotoxy(78,10+j);
					cout << fixed << setprecision(0) << q->hd.cthd.hd_data[j].Dongia;
					gotoxy(95,10+j);
				//	cout << fixed << setprecision(0) <<(NhanVien.NV[i].HD->DATA_HD.CT_HD->INFO[j].SoLuong)*(NhanVien.NV[i].HD->DATA_HD.CT_HD->INFO[j].DonGia);
					Print_Number_With_point ((q->hd.cthd.hd_data[j].Soluong)*(q->hd.cthd.hd_data[j].Dongia));
					Tong +=	(q->hd.cthd.hd_data[j].Soluong)*(q->hd.cthd.hd_data[j].Dongia);
					
				}
					gotoxy(95,28);
				//	cout << fixed << setprecision(0) << Tong << "  VND";
					Print_Number_With_point(Tong);
				break;
			}

		}
	}
		
		break;
		
		}
	}
	
	input = getch();
	}
	

int Find_Print_Deleta_case5(TREE root,string s,int i){
	if (root == NULL)
	 {
		return 0;
		}
     
     if (Cut_enter(root->vtdt.MAVT ) > s) {
     	Find_Print_Deleta_case5(root->pLeft,s,i);
	 }
     else if (Cut_enter(root->vtdt.MAVT) < s){
      	Find_Print_Deleta_case5(root->pRight,s,i);
      	
	 }
	
	 else{
	  		gotoxy(30,10+i);
			cout <<root->vtdt.TenVT;
			gotoxy(85,10+i);
			cout << "/" << root->vtdt.DVT;			
			return 1;
	 }
	
      
     return 0;
	
	
}
int  Fix_Node_Case1(TREE &root,string s){
	if (root == NULL){
		return 0;
	}
    if (Cut_enter(root->vtdt.MAVT ) > s) {
     	if (Fix_Node_Case1(root->pLeft,s) == 1)
	 		return 1;
	 	else return 0;	
	 }
     else if (Cut_enter(root->vtdt.MAVT ) < s){
     	if (Fix_Node_Case1(root->pRight,s) == 1)
	 		return 1;
	 	else return 0;
      	
	 }else{
			root->vtdt.TenVT=  Cut_Space(Tenvattu_fix);
			root->vtdt.DVT= Cut_Space(Donvitinh_VT_Fix); 	  				
			return 1;
	 }	
}

void Trasever_case_2(TREE root){
	
	int j = 0;
	int i = 0;
	////

	TREE_VATTU *p;
	while( root ){
		if( root->pLeft == NULL ){
				if(i<20){
				
				gotoxy(30,5+j);
				cout << atoi(root->vtdt.TenVT.c_str());
				gotoxy(47,5+j);
				cout << root->vtdt.TenVT;
				gotoxy(85,5+j);
				cout << root->vtdt.DVT;
				gotoxy(97,5+j);
				cout << root->vtdt.SLT;
				j++;
				}
				i++;
			root = root->pRight;
		}
		else{
			p = root->pLeft;
			while(p->pRight && p->pRight != root ){
				p = p->pRight;
			}
			if( p->pRight == NULL ){
				p->pRight = root;
			//	cout<< root->data << " ";
				root = root->pLeft;
			}
			else{
				p->pRight = NULL;
				if(i<20){
				
				gotoxy(30,5+j);
				cout << atoi(root->vtdt.MAVT.c_str());
				gotoxy(47,5+j);
				cout << root->vtdt.TenVT;
				gotoxy(85,5+j);
				cout << root->vtdt.DVT ;
				gotoxy(97,5+j);
				cout << root->vtdt.SLT;
				j++;
				}
				i++;
				root = root->pRight;
			}
		}
	}
	
}
	
void Duyet_List_Case_1(TREE root, int i){
	for (int j = 0 ; j < 20;j++){
						
	gotoxy(10,5+j);
	cout << "      " ;
	gotoxy(30,5+j);
	cout << "                        ";
	gotoxy(60,5+j);
	cout << "        ";
	gotoxy(77,5+j);
	cout << "      ";
	}
	int j = 0;
	int n = 0;
	TREE_VATTU *p;
	while( root ){
		if( root->pLeft == NULL ){
				if(n<i && n >= i - 20){
				
				gotoxy(10,5+j);
				cout << atoi(root->vtdt.MAVT.c_str());
				gotoxy(30,5+j);
				cout << root->vtdt.TenVT;
				gotoxy(60,5+j);
				cout << root->vtdt.DVT;
				gotoxy(77,5+j);
				cout << root->vtdt.SLT;
				j++;
				}
				n++;
				root = root->pRight;
				
		}
		else{
			p = root->pLeft;
			while(p->pRight && p->pRight != root ){
				p = p->pRight;
			}
			if( p->pRight == NULL ){
				p->pRight = root;
				if(n<i && n >= i - 20){
				
				gotoxy(10,5+j);
				cout << atoi(root->vtdt.MAVT.c_str());
				gotoxy(30,5+j);
				cout << root->vtdt.TenVT;
				gotoxy(60,5+j);
				cout << root->vtdt.DVT ;
				gotoxy(77,5+j);
				cout << root->vtdt.SLT;
				j++;
				}
				n++;
				root = root->pLeft;
				
			}
			else{
				p->pRight = NULL;
			//	cout<< root->data << " ";
				root = root->pRight;
			}
		}
	}
	
}

void Duyet_List_Case_2(TREE root, int i){
	for (int i=0;i < 20;i++){
	
	gotoxy(30,5+i);
	cout << "     "; 
	gotoxy(47,5+i);
	cout << "               ";
	gotoxy(85,5+i);
	cout << "       ";
	gotoxy(97,5+i);
	cout << "         ";
		}
	int j = 0;
	int n = 0;
	//////
		TREE_VATTU *p;
	while( root ){
		if( root->pLeft == NULL ){
				if(n<i && n >= i - 20){
				
				gotoxy(30,5+j);
				cout << atoi(root->vtdt.MAVT.c_str());
				gotoxy(47,5+j);
				cout << root->vtdt.TenVT;
				gotoxy(85,5+j);
				cout << root->vtdt.DVT ;
				gotoxy(97,5+j);
				cout << root->vtdt.SLT;
				j++;
				}
				n++;
			root = root->pRight;
		}
		else{
			p = root->pLeft;
			while(p->pRight && p->pRight != root ){
				p = p->pRight;
			}
			if( p->pRight == NULL ){
				p->pRight = root;
			//	cout<< root->data << " ";
				root = root->pLeft;
			}
			else{
				p->pRight = NULL;
				if(n<i && n >= i - 20){
				
				gotoxy(30,5+j);
				cout << atoi(root->vtdt.MAVT.c_str());
				gotoxy(47,5+j);
				cout << root->vtdt.TenVT;
				gotoxy(85,5+j);
				cout << root->vtdt.DVT ;
				gotoxy(97,5+j);
				cout << root->vtdt.SLT;
				j++;
				}
				n++;
				root = root->pRight;
			}
		}
	}
	/////
	
}
void Duyet_Case_6(DS_NHANVIEN NhanVien){
	for (int t = 0; t < 17;t++){
	
	gotoxy(19,10+t);
	cout << "   ";
	gotoxy(29,10+t);
	cout << "                 ";
	gotoxy(55,10+t);
	cout << "     ";
	gotoxy(67,10+t);
	cout << "        ";
	gotoxy(78,10+t);
	cout << "            ";
	gotoxy(95,10+t);
	cout << "                 ";
	}
	gotoxy(95,28);
	cout << "                  ";
	char input;
	while(input != 27){
		gotoxy(68,2);
		cout << "                        ";
		gotoxy(72,3);
		cout << "                        ";
		gotoxy(72,4);
		cout << "                        ";		
		gotoxy(72,5);
		cout << "                        ";
		string MaHD;
		gotoxy(72,2);
		cin >> MaHD;
	if (Search_Ma_HD(NhanVien, MaHD) == -1){
		gotoxy(68,2);
		cout << " khong tim thay hoa don";
		input = getch();
	}
	else {
		for ( int i = 0; i < NhanVien.n;i++){
			DSHD q = NhanVien.nvdt[i]->first_hd;
			NVDT *p = NhanVien.nvdt[i];
		for (q; q != NULL ; q = q->pNext){ 
			if (q->hd.SoHD == MaHD)
			{	
				int Tong = 0;
				gotoxy(72,2);
				cout << q->hd.SoHD;
				gotoxy(72,3);
				cout << q->hd.Loai;
				gotoxy(72,4);
			//	cout << NhanVien.nvdt[i].HO << " " <<NhanVien.nvdt[i].TEN ;
				gotoxy(72,5);
				cout <<q->hd.NgaylapHD.ngay << " / " << q->hd.NgaylapHD.thang << " / " << q->hd.NgaylapHD.nam;
				for (int j = 0; j<q->hd.cthd.n;j++){
					gotoxy(19,10+j);
					cout << j+1;
					gotoxy(29,10+j);
					Traverse_Tree_case_6 (T,q->hd.cthd.hd_data[j].MAVT,j);
					gotoxy(55,10+j);
					cout << q->hd.cthd.hd_data[j].MAVT;
					gotoxy(67,10+j);
					cout <<q->hd.cthd.hd_data[j].Soluong;
					gotoxy(78,10+j);
					cout << fixed << setprecision(0) << q->hd.cthd.hd_data[j].Dongia;
					gotoxy(95,10+j);
				//	cout << fixed << setprecision(0) <<(NhanVien.NV[i].HD->DATA_HD.CT_HD->INFO[j].SoLuong)*(NhanVien.NV[i].HD->DATA_HD.CT_HD->INFO[j].DonGia);
					Print_Number_With_point ((q->hd.cthd.hd_data[j].Soluong)*(q->hd.cthd.hd_data[j].Dongia));
					Tong +=	(q->hd.cthd.hd_data[j].Soluong)*(q->hd.cthd.hd_data[j].Dongia);
					
				}
					gotoxy(95,28);
				//	cout << fixed << setprecision(0) << Tong << "  VND";
					Print_Number_With_point(Tong);
				break;
			}

		}
	}
		
		break;
		
		}
	}
	
	input = getch();
	}
//////////////////////////////////////////////////////////////////////////////////////////
void Creat_node_CTHD(CTHD_DATA &INFO ){
		
//		while(Find_Node_Tree(T,INFO.MAVT) == 0){
		do {
				
			gotoxy(30,10+vitricase5.y);
			cout << "                   ";
			gotoxy(52,10+vitricase5.y);
			cout << "       ";
					
			//vi tri So Luong vat tu
			gotoxy(68,10+vitricase5.y);
			cout << "        ";
			// vi tri don gia vat tu
			gotoxy(78,10+vitricase5.y);
			cout << "            ";	
			while ( true){
				gotoxy(52,10+vitricase5.y);
				cout <<"         ";
				gotoxy(52,10+vitricase5.y);
				string s ;
				cin >> s;
				if (Check_Number(s ) == true){
					INFO.MAVT = s;
					break;
				}
			}
		}
		while (Find_Node_Tree(T,INFO.MAVT) != 1);
			
		//vi tri So Luong vat tu
		do {
		
			while ( true){
				gotoxy(68,10+vitricase5.y);
				cout <<"         ";
				gotoxy(68,10+vitricase5.y);
				string s ;
				cin >> s;
				if (Check_Number(s ) == true){
					INFO.Soluong = atoi(s.c_str());
					break;
				}
			}
		}
		while (Find_Print_VT_case5(T,INFO.MAVT,INFO.Soluong) != 1);	
			
		
			// vi tri don gia vat tu
	//	Find_Print_VT_case5(T,INFO.MAVT,INFO.SoLuong);
			while ( true){
				gotoxy(78,10+vitricase5.y);
				cout <<"       ";
				gotoxy(78,10+vitricase5.y);
				string s ;
				cin >> s;
				if (Check_Number(s ) == true){
					INFO.Dongia = atoi(s.c_str());
					break;
				}
			}	

	
}
//////////////////////////////////////////////////////////////////////////////////////////
void Input_Case_7(struct ngaylap &NgayDau,struct ngaylap &NgayCuoi){
	for (int t = 0; t < 20; t++){
		gotoxy(22,10+t);
		cout << "         ";
		gotoxy(35,10+t);
		cout <<	"            ";
		gotoxy(52,10+t);
		cout << "       ";
		gotoxy(63,10+t);
		cout << "                            ";
		gotoxy(100,10+t);
		cout << "              ";
		
	}

	while (true){
	gotoxy(58,4);
	cout <<"  ";
	gotoxy(61,4);
	cout << "  ";
	gotoxy(64,4);
	cout << "    ";		
	gotoxy(82,4);
	cout << "  ";
	gotoxy(85,4);
	cout << "  ";
	gotoxy(88,4);
	cout << "    ";
	gotoxy(50,5);
	cout << "                                                           ";		
	while (true){
	gotoxy(58,4);
	cout <<"  ";
	gotoxy(61,4);
	cout << "  ";
	gotoxy(64,4);
	cout << "    ";

	gotoxy(50,5);
	cout << "                                                           ";

	
	while ( true){
		gotoxy(58,4);
		cout <<"  ";
		gotoxy(58,4);
		string s ;
		cin >> s;
		if (Check_Number(s ) == true){
		NgayDau.ngay = atoi(s.c_str());
		break;
		}
	}
	while ( true){
		gotoxy(61,4);
		cout <<"  ";
		gotoxy(61,4);
		string s ;
		cin >> s;
		if (Check_Number(s ) == true){
		NgayDau.thang = atoi(s.c_str());
		break;
		}
	}
	while ( true){
		gotoxy(64,4);
		cout <<"    ";
		gotoxy(64,4);
		string s ;
		cin >> s;
		if (Check_Number(s ) == true){
		NgayDau.nam = atoi(s.c_str());
		break;
		}
	}


	// chuan hoa du lieu ngay dau
	if (NgayDau.nam % 4 == 0){
		if(NgayDau.thang < 1 || NgayDau.thang > 12){
			gotoxy(50,5);
			cout << "Nhap thang  Dau sai hay nhap lai";
			}
		else if (NgayDau.thang == 2){
			
				if (NgayDau.ngay < 1 || NgayDau.ngay > 29 )
				{
					gotoxy(50,5);
					cout << " Nhap ngay Dau sai hay nhap lai!";
				}
				else break;
			}
		else if (NgayDau.thang == 1 || NgayDau.thang == 3 || NgayDau.thang == 3 || NgayDau.thang == 5 || NgayDau.thang == 7 ||NgayDau.thang == 8 || NgayDau.thang == 10 || NgayDau.thang == 12)
			 {
				if (NgayDau.ngay <1 || NgayDau.ngay > 31)
				{
					gotoxy(50,5);
					cout << "Nhap Ngay Dau sai hay nhap lai";
				}
				else break;
				
			}
		else {
				if (NgayDau.ngay <1 || NgayDau.ngay > 30){
					gotoxy(50,5);
					cout << " Nhap Ngay Dau sai hay nhap lai";
				}
				else break;
			}
		getch();
		}
	
	else {
		if(NgayDau.thang < 1 || NgayDau.thang > 12){
			gotoxy(50,5);
			cout << "Nhap thang Dau sai hay nhap lai";
			}
		else if (NgayDau.thang == 2){
			
				if (NgayDau.ngay < 1 || NgayDau.ngay > 28 )
				{
					gotoxy(50,5);
					cout << " Nhap ngay Dau sai hay nhap lai!";
				}
				else break;
			}
		else if (NgayDau.thang == 1 || NgayDau.thang == 3 || NgayDau.thang == 3 || NgayDau.thang == 5 || NgayDau.thang == 7 ||NgayDau.thang == 8 || NgayDau.thang == 10 || NgayDau.thang == 12)
			 {
				if (NgayDau.ngay <1 || NgayDau.ngay > 31)
				{
					gotoxy(50,5);
					cout << "Nhap Ngay Dau sai hay nhap lai";
				}
				else break;
				
			}
		else {
				if (NgayDau.ngay <1 || NgayDau.ngay > 30){
					gotoxy(50,5);
					cout << " Nhap Ngay Dau sai hay nhap lai";
				}
				else break;
			}
		getch();
	}	
}
	//////////////////////////// chuan hoa du lieu ngay cuoi ///////////////////////////
	while (true){
	gotoxy(82,4);
	cout << "  ";
	gotoxy(85,4);
	cout << "  ";
	gotoxy(88,4);
	cout << "    ";
	gotoxy(50,5);
	cout << "                                                           ";	
	while ( true){
		gotoxy(82,4);
		cout <<"  ";
		gotoxy(82,4);
		string s ;
		cin >> s;
		if (Check_Number(s ) == true){
		NgayCuoi.ngay = atoi(s.c_str());
		break;
		}
	}
	while ( true){
		gotoxy(85,4);
		cout <<"  ";
		gotoxy(85,4);
		string s ;
		cin >> s;
		if (Check_Number(s ) == true){
		NgayCuoi.thang = atoi(s.c_str());
		break;
		}
	}
	while ( true){
		gotoxy(88,4);
		cout <<"    ";
		gotoxy(88,4);
		string s ;
		cin>> s;
		if (Check_Number(s ) == true){
		NgayCuoi.nam = atoi(s.c_str());
		break;
		}
	}
		if (NgayCuoi.nam % 4 == 0){
		if(NgayCuoi.thang < 1 || NgayCuoi.thang > 12){
			gotoxy(50,5);
			cout << "Nhap thang cuoi sai hay nhap lai";
			}
		else if (NgayCuoi.thang == 2){
			
				if (NgayCuoi.ngay < 1 || NgayCuoi.ngay > 29 )
				{
					gotoxy(50,5);
					cout << " Nhap ngay cuoi sai hay nhap lai!";
				}
				else break;
			}
		else if (NgayCuoi.thang == 1 || NgayCuoi.thang == 3 || NgayCuoi.thang == 3 || NgayCuoi.thang == 5 || NgayCuoi.thang == 7 ||NgayCuoi.thang == 8 || NgayCuoi.thang == 10 || NgayCuoi.thang == 12)
			 {
				if (NgayCuoi.ngay <1 || NgayCuoi.ngay > 31)
				{
					gotoxy(50,5);
					cout << "Nhap Ngay cuoi sai hay nhap lai";
				}
				else break;
				
			}
		else {
				if (NgayCuoi.ngay <1 || NgayCuoi.ngay > 30){
					gotoxy(50,5);
					cout << " Nhap Ngay cuoi sai hay nhap lai";
				}
				else break;
			}
		getch();	
		}
	
	else {
		if(NgayCuoi.thang < 1 || NgayCuoi.thang > 12){
			gotoxy(50,5);
			cout << "Nhap thang cuoi sai hay nhap lai";
			}
		else if (NgayCuoi.thang == 2){
			
				if (NgayCuoi.ngay < 1 || NgayCuoi.ngay > 28 )
				{
					gotoxy(50,5);
					cout << " Nhap ngay cuoi sai hay nhap lai!";
				}
				else break;
			}
		else if (NgayCuoi.thang == 1 || NgayCuoi.thang == 3 || NgayCuoi.thang == 3 || NgayCuoi.thang == 5 || NgayCuoi.thang == 7 ||NgayCuoi.thang == 8 || NgayCuoi.thang == 10 || NgayCuoi.thang == 12)
			 {
				if (NgayCuoi.ngay <1 || NgayCuoi.ngay > 31)
				{
					gotoxy(50,5);
					cout << "Nhap Ngay cuoi sai hay nhap lai";
				}
				else break;
				
			}
		else {
				if (NgayCuoi.ngay <1 || NgayCuoi.ngay > 30){
					gotoxy(50,5);
					cout << " Nhap Ngay cuoi sai hay nhap lai";
				}
				else break;
			}
		getch();
	}
}
	//////////////Chuan hoa du lieu ngay dau va ngay cuoi///////////////


	if (NgayDau.nam > NgayCuoi.nam){
		gotoxy(50,5);
		cout << " Nam ngay dau ko the lon hon nam ngay cuoi";
	}
	else if (NgayDau.nam == NgayCuoi.nam){
	
	 	if (NgayDau.thang > NgayCuoi.thang){
		gotoxy(50,5);
		cout << " thang ngay dau ko the lon hon thang ngay cuoi";
		}
	
		else if (NgayDau.thang == NgayCuoi.thang){
			if (NgayDau.ngay > NgayCuoi.ngay){
				gotoxy(50,5);
				cout << "  ngay dau ko the lon hon ngay cuoi";
			}
			else break;
		}
	
	}
	else break;
	getch();
	}
	
}
int Compare_Date(struct ngaylap a, struct ngaylap b){
	
	if (a.nam > b.nam){
		return 1;
	}
	else if(a.nam == b.nam){
		if (a.thang == b.thang){
			if (a.ngay == b.ngay)
			return 0;
			else if (a.ngay > b.ngay)
			return 1;
			else 
			return -1;
		}
		else if (a.thang < b.thang)
		return -1;
		else return 1;

	}
	else return -1;
}
CTHD ADD_CTHD(CTHD ct,CTHD_DATA cthd){
	if(ct.n>=20){
		cout<<"Khong duoc vuot qua 20 vat tu!";
	}else{
		ct.hd_data[ct.n]=cthd;
		ct.n++;
	}
	return ct;
}
void Add_Node_Head(DS_NHANVIEN &NhanVien, DSHD p,int i){
	
	if (NhanVien.nvdt[i]->first_hd == NULL){
		NhanVien.nvdt[i]->first_hd  = p; // node dau cx la node cuoi la p
		
	}
	else {
		p->pNext = NhanVien.nvdt[i]->first_hd; // cho con tro node can them lien ket voi node dau pHead
		NhanVien.nvdt[i]->first_hd = p;  // cap nhat lai pHead la node p
		
	}
}
void Add_CTHD_To_HD(DSHD &hoadon, CTHD list_CTHD){
	
//	DSHD hd1=new Node_HOADON;
	for (int i = 0; i < list_CTHD.n;i++ ){
		
	hoadon->hd.cthd.hd_data[i] = list_CTHD.hd_data[i];
		
	}
	//hoadon=hd1;
}
//int Is_VT_Have_CTHD(DS_NHANVIEN NhanVien,string s){
//		DSHD *q;
//	for ( int i = 0; i < NhanVien.n;i++){
//		q = NhanVien.nvdt[i]->first_hd;
//		for (q; q != NULL ; q = q->pNext){
//				for (int j = 0;j <q.hd.cthd.n;j++){
//					if (atoi(s.c_str()) == atoi(q->hd.cthd->hd_data[j].c_str())){
//						return 1;
//					}
//					
//				}
//		}
//	}
//	return 0;
//}

int Is_SLT_Eq_0(TREE T,string s)
{
	if (T == NULL)
	 {
	 	
		return 0;
	}
	else {

     
     if (Cut_enter(T->vtdt.MAVT) > s) {
		if (Is_SLT_Eq_0(T->pLeft,s) == 1) 
		return 1;
     	else return 0;
	 }
     else if (Cut_enter(T->vtdt.MAVT ) < s){
		if (Is_SLT_Eq_0(T->pRight,s) == 1) 
		return 1;
     	else return 0;      	

	 }
	
	 else{
	  
		if (T->vtdt.SLT == 0)
     	return 1;
     	else return 0;
	 }
	
      	
	}
}

void Output_Case5(CTHD list_CTHD){
	long tong = 0;
	gotoxy(95,10+vitricase5.y-1);
//	cout << fixed << setprecision(0) <<(list_CTHD.INFO[vitricase5.y-1].SoLuong)*(list_CTHD.INFO[vitricase5.y-1].DonGia); 
	Print_Number_With_point ((list_CTHD.hd_data[vitricase5.y-1].Soluong)*(list_CTHD.hd_data[vitricase5.y-1].Dongia));
	
	tong += (list_CTHD.hd_data[vitricase5.y-1].Soluong)*(list_CTHD.hd_data[vitricase5.y-1].Dongia);
	
	gotoxy(95,28);
//	cout << fixed << setprecision(0) << tong << "   VND";
 	Print_Number_With_point (tong);
}


void Add_HoaDon_To_NV(DS_NHANVIEN &nv,DSHD p,int i){
	
	nv.nvdt[i]->first_hd = p;
	nv.n++;
	
}
void Creat_HD(HOADON &hd,int m,CTHD ct){
	int n;
	if( m == 1 ){
		hd.Loai = "X";
	}
	else if ( m == 0){
		hd.Loai = "N";
	}
	else if(m == 2){
		
	}
	gotoxy(70,6);
	//cout<<"Nhap so hoa don: ";
	cin>>hd.SoHD;
	gotoxy(67,5);
	//cout<<"Ngay lap: ";
	cin>>hd.NgaylapHD.ngay;
	gotoxy(73,5);
	//cout<<"Thang: ";
	cin>>hd.NgaylapHD.thang;
	gotoxy(78,5);
	//cout<<"Nam: ";
	cin>>hd.NgaylapHD.nam;
	hd.cthd=ct;
	
}

/////////////////////////////////////////////////////////////////////////////////////////
// doc file hoa don va chi tiet hoa don vao danh sach nhan vien

//
void Read_File_HD_Add_NV(ifstream &filein1,DS_NHANVIEN &NhanVien ){
	HOADON hoadon ;
	CTHD cthd;
	DSHD node_hd = new Node_HOADON;
	filein1.open("HD3.txt", ios_base::in);
	
	if (filein1.fail()== true)
	{
		cout << "FILE K TON TAI";
		
	}
	else{
	int Sohoadon;
	filein1 >> Sohoadon;
	filein1 >> SoHoaDon_Auto;
	string enter;
	getline(filein1,enter);
		

	for (int i = 0; i < Sohoadon; i++){

	// nhap thong tin vao HD
	string Manv;
	getline(filein1,Manv);
	getline(filein1,hoadon.SoHD,'	');
	getline(filein1, hoadon.Loai,'	');
	filein1 >> hoadon.NgaylapHD.ngay;
	filein1 >> hoadon.NgaylapHD.thang;
	filein1 >> hoadon.NgaylapHD.nam;
	string line;
	getline(filein1,line);
	// nhap thong tin vao CTHD
	int sovattu;
	filein1 >> sovattu;
	getline(filein1,line);
	for (int j = 0 ; j < sovattu; j++){
		
		filein1 >>cthd.hd_data[j].MAVT;
		filein1 >>cthd.hd_data[j].Soluong ;
		filein1 >>cthd.hd_data[j].Dongia;
		getline(filein1,line);
	
	}
	
	//Creat_HD(hoadon,2,cthd);
	hoadon.cthd = cthd;
	hoadon.cthd.n = sovattu;
	//Add_CTHD_To_HD(hoadon,cthd);
	//hoadon = Creat_Node_Dshd(DATA_HD2);
//	Clear_list_CTHD(cthd);
	//Add_Node_Head(NhanVien, hoadon ,Find_ViTriNV(NhanVien,atoi(Manv.c_str())) );
	//them CTHD vao Hoa Don
	node_hd = Creat_Node_Dshd(hoadon);
	Add_Node_Head(nv, node_hd ,Find_ViTriNV(NhanVien,atoi(Manv.c_str())));	
	
	}
	
		}
		
	filein1.close();	
}				

/////////////////////////////////////////////////////////////////////////////////////////
// doc file vao sach sach tuyen tinh nhan vien
void Read_File_List_NV(ifstream& filein, DS_NHANVIEN& NhanVien) {
	filein.open("NhanVien.txt", ios_base::in);
		if (filein.fail()== true){	
			cout << "FILE D TON TAI";
		}	
	int i = 0;
	while (filein.eof() == false) {
		
		NhanVien.nvdt[i]=new NVDT;
		string manv;
		getline(filein, manv,'	');
		NhanVien.nvdt[i]->MANV=atoi(manv.c_str());
		//filein>>NhanVien.nvdt[i]->MANV;
		getline(filein, NhanVien.nvdt[i]->HO,'	');
		getline(filein, NhanVien.nvdt[i]->TEN,'	');
		getline(filein, NhanVien.nvdt[i]->PHAI,'	');
		getline(filein, NhanVien.nvdt[i]->CMND);
		NhanVien.n++;
		i++;
	}
	filein.close();
}

void cap_phat(DS_NHANVIEN& NhanVien) {
	for (int i = 0; i < NhanVien.n; i++) {
		NhanVien.nvdt[i] = new NVDT();
	}

}

////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////

void draw_case1() {
	color_set();
	system("cls");
	SetBGColor(0);
	gotoxy(5, 2);
	cout << string(80, char(219));
	for (int i = 3; i < 25; i++) {
		gotoxy(5, i);
		cout << char(219);

	}
	gotoxy(5, 25);
	cout << string(80, char(219)) << endl;
	for (int i = 2; i <= 25; i++) {
		gotoxy(85, i);
		cout << char(219);
	}
	gotoxy(6, 3);
	SetBGColor(15);
	cout << " MA VAT TU |        	 TEN VAT TU 	      | DON VI TINH | SO LUONG TON  ";
	gotoxy(6, 4);
	cout << "------------------------------------------------------------------------------";
	gotoxy(55, 28);
	cout << "*NHAN ESC DE TRO VE MENU\n";
	gotoxy(54, 29);
	cout << "*NHAN ENTER DE CHON CHUC NANG\n";
	gotoxy(53, 30);
	cout << "*SU DUNG PHIM MUI TEN DE LUA CHON\n";
	gotoxy(87, 2);
	cout << string(41, char(219)) << endl;
	for (int i = 2; i <= 25; i++) {
		gotoxy(87, i);
		cout << char(219);
	}
	gotoxy(87, 25);
	cout << string(41, char(219)) << endl;
	for (int i = 2; i <= 25; i++) {
		gotoxy(128, i);
		cout << char(219);
	}
	gotoxy(100, 3);
	cout << "BANG HIEU CHINH";
	gotoxy(88, 4);
	cout << "----------------------------------------";
	gotoxy(17, 4);
	for (int i = 3; i < 25; i++) {
		gotoxy(17, i);
		cout << "|";
	}
	gotoxy(54, 4);
	for (int i = 3; i < 25; i++) {
		gotoxy(54, i);
		cout << "|";
	}
	gotoxy(68, 4);
	for (int i = 3; i < 25; i++) {
		gotoxy(68, i);
		cout << "|";
	}
	gotoxy(90, 6);
	cout << "MA VT      [                         ]";
	gotoxy(90, 9);
	cout << "TEN VT     [                         ]";
	gotoxy(90, 12);
	cout << "DVI TINH   [                         ]";
	gotoxy(90, 15);
	cout << "SLUONG TON [                         ]";
	
		Duyet_List_Case_1(T, 20);

		 //////chon trang /////
	 int trang;
	trang = Count_Node_Tree(T) / 20; // 20 so dong toi da cua bang 
	gotoxy(56,26);
	cout << "Trang ";
	gotoxy(64,26);
	for (int i = -1; i < trang; i++){
	
	cout << "[" <<i+2 << "]" << " ";
	}
	gotoxy(64,26);
	SetBGColor(light_cyan);
	cout << "[" << "1" << "]";
	SetBGColor(15);
	 /////////////////////
	
	
	 int luachon1 = 1;
	position luachon_case1[3];
	string case1[5]={"[them vat tu]","[ xoa vat tu]","[  cap nhat ]"};
	for (int i= 0;i < 3;i++){
		luachon_case1[i].x=101;
		luachon_case1[i].y=20+i;
		gotoxy(luachon_case1[i].x,luachon_case1[i].y);
		cout << case1[i];
		}
	gotoxy (luachon_case1[0].x,luachon_case1[0].y);
	cout<< case1[0];
	
while (true){
	 if(kbhit){
		 char input = getch();
		 if (input == -32){
		 	input = getch();
		 	switch (input){
		 		case 80 : {gotoxy(luachon_case1[luachon1].x,luachon_case1[luachon1].y);
		 			 SetBGColor(15);
					 cout <<case1[luachon1];
                     luachon1++;
                     if(luachon1 > 3){
                     	luachon1 = 0;
					 }
					 gotoxy(luachon_case1[luachon1].x,luachon_case1[luachon1].y);
					 SetBGColor(light_cyan);   //light_cyan
					 cout <<case1[luachon1]; 
					 
					break;
				 } 
				case 72: {
					gotoxy(luachon_case1[luachon1].x,luachon_case1[luachon1].y);
		 			 SetBGColor(15);
					 cout <<case1[luachon1];
                     luachon1--;
                     if(luachon1 < 0){
                     	luachon1 = 3;
					 }
					 gotoxy(luachon_case1[luachon1].x,luachon_case1[luachon1].y);
					 SetBGColor(light_cyan);
					 cout <<case1[luachon1]; 
					break;
				}
		 		}
}
else if(input == 13)
				{
					switch (luachon1) {
						case 0 : {// thuc hien them vat tu
					
						ShowConsoleCursor(true);
						SetBGColor(15);
						gotoxy(90,15);
						cout << "SLUONG TON [                         ]";
						gotoxy(103,6);
	
						cout << "               ";
						
						gotoxy(103,9);
//						cin.ignore();
						cout<<"                       ";
						gotoxy(103,12);
//						cin.ignore();
						cout <<"                     ";
						gotoxy(103,15);
						cout << "                    ";
						VTDT Data;
						Creat_Data_Tree(Data);
						Add_Node_Tree(T,Data);
						SoVatTu_Auto ++;
						Duyet_List_Case_1(T, 20);
					//	Write_Tree (fileout,T);
						sleep(2);
						gotoxy(103,6);
	
						cout << "               ";
						
						gotoxy(103,9);
//						cin.ignore();
						cout<<"                       ";
						gotoxy(103,12);
//						cin.ignore();
						cout <<"                     ";
						gotoxy(103,15);
						cout << "                    ";
						gotoxy(97,18);
						cout <<" Them Vat Tu Thanh Cong";
						getch();
						gotoxy(97,18);
						cout <<"                        ";
							break;
						}
						case 1 :{ // thuc hien xoa vat tu
						ShowConsoleCursor(true);
						gotoxy(101,24);
						cout << luachon1;
						SetBGColor(15);
						gotoxy(90,15);
						cout << "TIM KIEM   [                         ]";						
						gotoxy(103,6);
						cout <<"                      ";
						gotoxy(103,9);
						cout <<"                ";
						gotoxy(120,9);
						cout << "       ";
						gotoxy(103,12);
						cout <<"                      ";
				//		gotoxy(101,24);
				//		cout << luachon1;
    					gotoxy(92,17);
    					cout << "                                 ";						
						gotoxy(103,15);
						
						string Mavattu;
						cin >> Mavattu;
    					gotoxy(92,17);
    					cout << "                                  ";
//    					if (Is_VT_Have_CTHD(NhanVien,Mavattu) == 1){
//    						gotoxy(92,17);
//    						cout << "Vat Tu da co trong hoa don ko xoa";
//    						gotoxy(103,15);
//						    cout <<"                       ";
//    						break;
//						}
						if (Is_SLT_Eq_0(T,Mavattu) == 0 ){
							gotoxy(92,17);
    						cout << "Vat Tu con hang trong kho ko xoa";
    						gotoxy(103,15);
						    cout <<"                       ";
    						break;
							
						}
						if ( Find_Node_Tree_case1(T,Mavattu) == 0)  //return == 0 neu ko tim thay
    					{
    						gotoxy(92,17);
    						cout << "khong tim thay vat tu can xoa";
    						gotoxy(103,15);
						    cout <<"                       ";
							
							break;
							
						}
						else if ( Find_Node_Tree_case1(T,Mavattu) == 1){
							Find_Node_Case1(T,Mavattu);
							gotoxy(94,17);
    						cout << "Ban co thuc su muon xoa VT ko? ";
    						gotoxy(97,18);
    						cout << " y: yes | n: no ";
						
						while (true){
						
						
						if (kbhit){
						char input3;
							input3 = getch();
						if (input3 == 121){
							gotoxy(103,6);
							cout <<"                      ";
							gotoxy(103,9);
							cout <<"                ";
							gotoxy(120,9);
							cout << "       ";
							gotoxy(103,12);
							cout <<"                      ";
    						gotoxy(92,17);
    						cout << "                                ";					   
    						gotoxy(97,18);
    						cout << "                     ";							
							Delete_Node_Tree(T,Mavattu);

				//			Trasever_List_Case_1(T, 20);
				//			DEL_ITEM_NHANVIEN(NhanVien, Search_list_NV(NhanVien, Data_NV)+1);
							//ofstream fileout1;
				//			Write_Tree (fileout,T);
							Duyet_List_Case_1(T, 20);
				//			Write_File_List_NV(fileout, NhanVien);
							sleep (1);
							gotoxy(94,17);
							cout << "Xoa Vat Tu Thanh Cong";
							sleep(2);
							gotoxy(94,17);
    						cout << "                                ";
    						gotoxy(97,18);
    						cout << "                     ";
							
				//       		Traverse_list_NV_case3(NhanVien,Pos_Empty_NV(NhanVien));
				       		
				       		break;
				       		
					   }
					   else if (input3 == 110) {
					   
						gotoxy(103,6);
						cout <<"                      ";
						gotoxy(103,9);
						cout <<"                ";
						gotoxy(120,9);
						cout << "       ";
						gotoxy(103,12);
						cout <<"                      ";
    					gotoxy(92,17);
    					cout << "                                ";					   
    					gotoxy(97,18);
    					cout << "                     ";					   
					   
					   break;
						}
					   //else if (input3 == 27)
					   
					   }
				}
						gotoxy(103,15);
						cout << "             ";
						gotoxy(94,17);
    					cout << "                                 ";
    					gotoxy(97,18);
    					cout << "                     ";
						
							
						
					}	
								
							break;	
							
						}
						case 2 : {// thuc hien cap nhat
						ShowConsoleCursor(true);
						SetBGColor(15);
						gotoxy(90,15);
						cout << "TIM KIEM   [                         ]";								
						gotoxy(103,6);
						cout <<"                      ";
						gotoxy(103,9);
						cout <<"                ";
						gotoxy(120,9);
						cout << "       ";
						gotoxy(103,12);
						cout <<"                      ";
    					gotoxy(92,17);
    					cout << "                                  ";						
						SetBGColor(15);
						gotoxy(103,15);
						string Mavattu;
						cin >> Mavattu;
    					gotoxy(92,17);
    					cout << "                                    ";
    					
						if ( Find_Node_Tree_case1(T,Mavattu) == 0)  //return == 0 neu ko tim thay
    					{
    						gotoxy(92,17);
    						cout << "khong tim thay vat tu can sua";
    						gotoxy(103,15);
						    cout <<"                       ";
							
							break;
							
						}
						else if ( Find_Node_Tree_case1(T,Mavattu) == 1){
							gotoxy(94,17);
    						cout << "Ban co thuc su muon sua VT ko? ";
    						gotoxy(97,18);
    						cout << " y: yes | n: no ";					
						while (true){
						
						
						if (kbhit){
						char input3;
							input3 = getch();
						if (input3 == 121){
						
				//			DEL_ITEM_NHANVIEN(NhanVien, Search_list_NV(NhanVien, Data_NV)+1);
							//ofstream fileout1;
							Find_Node_Case1(T,Mavattu);
							
				
				//			Write_File_List_NV(fileout, NhanVien);
						//////////////////// sua ten VT //////////////////
							char Ten;
							while (true) {
							gotoxy(94,17);
    						cout << "                                ";
    						gotoxy(97,18);
    						cout << "                     ";								
							gotoxy(103 + Tenvattu_fix.size(),9);	
							Ten = getch();
							if (Ten == 8){
								
								gotoxy(103 + Tenvattu_fix.size() - 1,9);
								cout <<" ";
								Tenvattu_fix.pop_back();
							}
						
							else if (Ten >= 'a' && Ten <= 'z' || Ten == 32 || Ten >= 'A' && Ten <= 'Z' || Ten >= '0' && Ten <= '9'){
								Tenvattu_fix += Ten;
								gotoxy(103,9);
								cout << Tenvattu_fix;
								}
							if(Ten == 13)
							break;
							if (Tenvattu_fix.empty())
							Tenvattu_fix = " ";
							}
							////////////// sua don vi tinh VT ////////////////
							char Donvitinh;
							while (true) {
							gotoxy(94,17);
    						cout << "                                ";
    						gotoxy(97,18);
    						cout << "                     ";								
							gotoxy(103 + Donvitinh_VT_Fix.size(),12);	
							Donvitinh = getch();
							if (Donvitinh == 8){
								
								gotoxy(103 + Donvitinh_VT_Fix.size() - 1,12);
								cout <<" ";
								Donvitinh_VT_Fix.pop_back();
							}
						
							else if (Donvitinh >= 'a' && Donvitinh <= 'z' || Donvitinh == 32 || Donvitinh >= 'A' && Donvitinh <= 'Z'|| Donvitinh >= '0' && Donvitinh <= '9'){
								Donvitinh_VT_Fix += Donvitinh;
								gotoxy(103,12);
								cout << Donvitinh_VT_Fix;
								}
							if(Donvitinh == 13)
							break;
							if (Donvitinh_VT_Fix.empty())
							Donvitinh_VT_Fix = " ";	
							}
							Fix_Node_Case1(T,Mavattu);
							Duyet_List_Case_1(T,20);
							//Write_Tree (fileout,T);
							gotoxy(92,17);
							cout << "	Sua Vat Tu Thanh Cong ";
							sleep (2);
							gotoxy(103,6);
							cout <<"                      ";
							gotoxy(103,9);
							cout <<"                ";
							gotoxy(120,9);
							cout << "       ";
							gotoxy(103,12);
							cout <<"                      ";
    						gotoxy(92,17);
    						cout << "                                  ";														
    						gotoxy(97,18);
    						cout << "                     ";
							
				//       		Traverse_list_NV_case3(NhanVien,Pos_Empty_NV(NhanVien));
				       		
				       		break;
				       		
					   }
					   else if (input3 == 110) 
					   
					   
					   break;
					   
					   //else if (input3 == 27)
					   
					   }
				}
						gotoxy(103,15);
						cout << "             ";
						gotoxy(94,17);
    					cout << "                                 ";
    					gotoxy(97,18);
    					cout << "                     ";
														
								}
							break;
						}	
					}
					
}
else if(input == 27){
	
	color_set();
	system("cls");
	SetBGColor(15);
	//SetBGColor(0);
	menu();
}
switch (input){
	    	case 50: {
	    		gotoxy(64,26);
	    		cout << "                                          ";
				
				SetBGColor(15);
				gotoxy(56,26);
				cout << "Trang ";
				gotoxy(64,26);
				for (int i = -1; i < trang; i++){
				cout << "[" <<i+2 << "]" << " ";
				}
				gotoxy(68,26);
				SetBGColor(light_cyan);
				cout << "[" << "2" << "]";
				SetBGColor(15);
				Duyet_List_Case_1(T, 40);
				break;
			}
			case 49:{
				gotoxy(64,26);
	    		cout << "                                          ";
				SetBGColor(15);
				gotoxy(56,26);
				cout << "Trang ";
				gotoxy(64,26);
				for (int i = -1; i < trang; i++){
				cout << "[" <<i+2 << "]" << " ";
				}
				gotoxy(64,26);
				SetBGColor(light_cyan);
				cout << "[" << "1" << "]"<<" ";
				
				SetBGColor(15);
				Duyet_List_Case_1(T, 20);
				
				break;
			}
			case 51:{
				gotoxy(64,26);
	    		cout << "                                          ";
				SetBGColor(15);
				gotoxy(56,26);
				cout << "Trang ";
				gotoxy(64,26);
				for (int i = -1; i < trang; i++){
				cout << "[" <<i+2 << "]" << " ";
				}
				gotoxy(72,26);
				SetBGColor(light_cyan);
				cout << "[" << "3" <<"]";
				SetBGColor(15);
				Duyet_List_Case_1(T, 60);
				break;
			}
	    	case 52:{
				gotoxy(64,26);
	    		cout << "                                          ";
				SetBGColor(15);
				gotoxy(56,26);
				cout << "Trang ";
				gotoxy(64,26);
				for (int i = -1; i < trang; i++){
				cout << "[" <<i+2 << "]" << " ";
				}
				gotoxy(76,26);
				SetBGColor(light_cyan);
				cout << "[" << "4" <<"]";
				SetBGColor(15);
				Duyet_List_Case_1(T, 80);
				break;
			}
	    	case 53:{
				gotoxy(64,26);
	    		cout << "                                          ";
				SetBGColor(15);
				gotoxy(56,26);
				cout << "Trang ";
				gotoxy(64,26);
				for (int i = -1; i < trang; i++){
				cout << "[" <<i+2 << "]" << " ";
				}
				gotoxy(80,26);
				SetBGColor(light_cyan);
				cout << "[" << "5" <<"]";
				SetBGColor(15);
				Duyet_List_Case_1(T, 100);
				break;
			}
	    	
				}
}
}

	}


void draw_case2() {
	color_set();
	system("cls");
	SetBGColor(15);
	gotoxy(27, 2);
	cout << string(80, char(219));
	for (int i = 3; i < 25; i++) {
		gotoxy(27, i);
		cout << char(219);

	}
	gotoxy(27, 25);
	cout << string(80, char(219)) << endl;
	for (int i = 2; i <= 25; i++) {
		gotoxy(107, i);
		cout << char(219);
	}
	gotoxy(28, 3);
	cout << " MA VAT TU |        	 TEN VAT TU 	      | DON VI TINH | SO LUONG TON ";
	gotoxy(28, 4);
	cout << "------------------------------------------------------------------------------";

	gotoxy(55, 28);
	cout << "*NHAN ESC DE TRO VE MENU\n";
	gotoxy(53, 29);
	cout << "*SU DUNG PHIM SO DE LUA CHON TRANG\n";
	gotoxy(39, 4);
	for (int i = 3; i < 25; i++) {
		gotoxy(39, i);
		cout << "|";
	}
	gotoxy(78, 4);
	for (int i = 3; i < 25; i++) {
		gotoxy(78, i);
		cout << "|";
	}
	gotoxy(92, 4);
	for (int i = 3; i < 25; i++) {
		gotoxy(92, i);
		cout << "|";
	}

	//TREE T;
	//Creat_Tree(T);
	//Read_Tree_case2(filein,V);	
	Trasever_case_2(T);	
	
			 //////chon trang /////
	int trang;
	trang = Count_Node_Tree(T) / 20; // 20 so dong toi da cua bang 
	gotoxy(56,26);
	cout << "Trang ";
	gotoxy(64,26);
	for (int i = -1; i < trang; i++){
	
	cout << "[" <<i+2 << "]" << " ";
	}
	gotoxy(64,26);
	SetBGColor(light_cyan);
	cout << "[" << "1" << "]";
	SetBGColor(15);
	 /////////////////////	
		
	while (true){
		if (kbhit){
		char input1 = getch();
		if (input1 == 27)
		{
		system("cls");	
		menu();
		break;
	    }
	    switch (input1){
	    	case 50: {
	    		gotoxy(64,26);
	    		cout << "                                          ";
				
				SetBGColor(15);
				gotoxy(56,26);
				cout << "Trang ";
				gotoxy(64,26);
				for (int i = -1; i < trang; i++){
				cout << "[" <<i+2 << "]" << " ";
				}
				gotoxy(68,26);
				SetBGColor(light_cyan);
				cout << "[" << "2" << "]";
				SetBGColor(15);
	//			Traverse_list_NV_case4(NhanVien,40);
				Duyet_List_Case_2(T, 40);
				
				break;
			}
			case 49:{
				gotoxy(64,26);
	    		cout << "                                          ";
				SetBGColor(15);
				gotoxy(56,26);
				cout << "Trang ";
				gotoxy(64,26);
				for (int i = -1; i < trang; i++){
				cout << "[" <<i+2 << "]" << " ";
				}
				gotoxy(64,26);
				SetBGColor(light_cyan);
				cout << "[" << "1" << "]"<<" ";
				
				SetBGColor(15);
	//			Traverse_list_NV_case4(NhanVien,20);
				Duyet_List_Case_2(T, 20);
				
				break;
			}
			case 51:{
				gotoxy(64,26);
	    		cout << "                                          ";
				SetBGColor(15);
				gotoxy(56,26);
				cout << "Trang ";
				gotoxy(64,26);
				for (int i = -1; i < trang; i++){
				cout << "[" <<i+2 << "]" << " ";
				}
				gotoxy(72,26);
				SetBGColor(light_cyan);
				cout << "[" << "3" <<"]";
				SetBGColor(15);
				Duyet_List_Case_2(T,60);
				break;
			}
	    	case 52:{
				gotoxy(64,26);
	    		cout << "                                          ";
				SetBGColor(15);
				gotoxy(56,26);
				cout << "Trang ";
				gotoxy(64,26);
				for (int i = -1; i < trang; i++){
				cout << "[" <<i+2 << "]" << " ";
				}
				gotoxy(76,26);
				SetBGColor(light_cyan);
				cout << "[" << "4" <<"]";
				SetBGColor(15);
				Duyet_List_Case_2(T,80);
				break;
			}
	    	case 53:{
				gotoxy(64,26);
	    		cout << "                                          ";
				SetBGColor(15);
				gotoxy(56,26);
				cout << "Trang ";
				gotoxy(64,26);
				for (int i = -1; i < trang; i++){
				cout << "[" <<i+2 << "]" << " ";
				}
				gotoxy(80,26);
				SetBGColor(light_cyan);
				cout << "[" << "5" <<"]";
				SetBGColor(15);
				Duyet_List_Case_2(T,100);
				break;
			}
	    	
				}
	  
	
				  }	
	}
		
}
void draw_case3() {
	ShowConsoleCursor(true);
	color_set();
	system("cls");
	SetBGColor(0);
	gotoxy(5, 2);
	cout << string(80, char(219));
	for (int i = 3; i < 25; i++) {
		gotoxy(5, i);
		cout << char(219);
	}
	gotoxy(5, 25);
	cout << string(80, char(219)) << endl;
	for (int i = 2; i <= 25; i++) {
		gotoxy(85, i);
		cout << char(219);
	}
	gotoxy(6, 3);
	SetBGColor(15);
	cout << " MA NHAN VIEN |        	  TEN NHAN VIEN           | GIOI TINH |  CMND     ";
	gotoxy(6, 4);
	cout << "------------------------------------------------------------------------------";
	gotoxy(55, 28);
	cout << "*NHAN ESC DE TRO VE MENU\n";
	gotoxy(54, 29);
	cout << "*NHAN --> DE HIEU CHINH NHAN VIEN\n";
	gotoxy(53, 30);
	cout << "*SU DUNG PHIM MUI TEN DE LUA CHON\n";
	gotoxy(87, 2);
	cout << string(41, char(219)) << endl;
	for (int i = 2; i <= 25; i++) {
		gotoxy(87, i);
		cout << char(219);
	}
	gotoxy(87, 25);
	cout << string(41, char(219)) << endl;
	for (int i = 2; i <= 25; i++) {
		gotoxy(128, i);
		cout << char(219);
	}
	gotoxy(100, 3);
	cout << "BANG HIEU CHINH";
	gotoxy(88, 4);
	cout << "----------------------------------------";
	gotoxy(20, 4);
	for (int i = 3; i < 25; i++) {
		gotoxy(20, i);
		cout << "|";
	}
	gotoxy(58, 4);
	for (int i = 3; i < 25; i++) {
		gotoxy(58, i);
		cout << "|";
	}
	gotoxy(70, 4);
	for (int i = 3; i < 25; i++) {
		gotoxy(70, i);
		cout << "|";
	}

	Duyet_NhanVien_case3(nv, 20);
	/////////////////////////////////////////////
	int trang;
	trang = nv.n / 20; // 20 so dong toi da cua bang 
	gotoxy(56, 26);
	cout << "Trang ";
	gotoxy(64, 26);
	for (int i = -1; i < trang; i++) {

		cout << "[" << i + 2 << "]" << " ";
	}
	gotoxy(64, 26);
	SetBGColor(light_cyan);
	cout << "[" << "1" << "]";
	SetBGColor(15);
	gotoxy(90, 6);
	cout << "MA NV      [                         ]";
	gotoxy(90, 9);
	cout << "TEN NV     [                 |       ]";
	gotoxy(90, 12);
	cout << "GIOI TINH  [                         ]";
	gotoxy(90, 15);
	cout << "CMND	     [                         ]";
	gotoxy(90, 18);
	cout << "TIM KIEM   [                    ]";


	int luachon = 1;
	position luachon_case1[3];
	string case1[5] = { "[Them nhan vien]","[ Xoa nhan vien]","[   Cap nhat   ]" };
	for (int i = 0; i < 3; i++) {
		luachon_case1[i].x = 101;
		luachon_case1[i].y = 20 + i;
		gotoxy(luachon_case1[i].x, luachon_case1[i].y);
		cout << case1[i];
	}
	gotoxy(luachon_case1[0].x, luachon_case1[0].y);
	cout << case1[0];
	while (true) {
		if (kbhit) {
			char input = getch();
			if (input == -32) {
				input = getch();
				switch (input) {
				case 80: {gotoxy(luachon_case1[luachon].x, luachon_case1[luachon].y);
					SetBGColor(15);
					cout << case1[luachon];
					luachon++;
					if (luachon > 3) {
						luachon = 0;
					}
					gotoxy(luachon_case1[luachon].x, luachon_case1[luachon].y);
					SetBGColor(light_cyan);   //light_cyan
					cout << case1[luachon];

					break;
				}
				case 72: {
					gotoxy(luachon_case1[luachon].x, luachon_case1[luachon].y);
					SetBGColor(15);
					cout << case1[luachon];
					luachon--;
					if (luachon < 0) {
						luachon = 3;
					}
					gotoxy(luachon_case1[luachon].x, luachon_case1[luachon].y);
					SetBGColor(light_cyan);
					cout << case1[luachon];
					break;
				}
				}
			}
			else if (input == 13)
			{
				NVDT Data_NV;
				switch (luachon) {
				case 0: {// thuc hien them nhan vien

					SetBGColor(15);
					gotoxy(103, 6);
					cout << "                      ";
					gotoxy(102, 9);
					cout << "                ";
					gotoxy(120, 9);
					cout << "    ";
					gotoxy(115, 12);
					cout << "       ";
					gotoxy(103, 15);
					cout << "                      ";
					SetBGColor(15);
					gotoxy(92, 17);
					cout << "                                  ";

					Duyet_NhanVien_case3(nv, nv.n - 1);
					char input3;
					while (true) {
						if (kbhit) {

							nvdt = Create_NhanVienDT(nvdt);
							nv = Add_NhanVien(nv, nvdt);

							//ofstream fileout;
						//	Write_File_List_NV(fileout, NhanVien);
							Duyet_NhanVien_case3(nv, nv.n - 1);
							gotoxy(94, 17);
							cout << "                                  ";
							gotoxy(94, 17);
							cout << "Them Nhan Vien Thanh Cong!";
							sleep(2);
							gotoxy(94, 17);
							cout << "                                  ";
							gotoxy(101, 9);
							cout<<"			";
							gotoxy(117, 9);
							cout<<"		";
							gotoxy(103, 12);
							cout << "    ";
							break;


						}
					}
					gotoxy(103, 6);
					cout << "                      ";
					gotoxy(102, 9);
					cout << "                ";
					gotoxy(120, 9);
					cout << "    ";
					gotoxy(115, 12);
					cout << "       ";
					gotoxy(103, 15);
					cout << "                      ";
					SetBGColor(15);
					break;
				}
				case 1: { // thuc hien xoa nhan vien
					SetBGColor(15);
					gotoxy(103, 6);
					cout << "                      ";
					gotoxy(103, 9);
					cout << "                ";
					gotoxy(115, 12);
					cout << "       ";
					gotoxy(103, 15);
					cout << "                      ";
					//	gotoxy(101,24);
					//	cout << luachon;
					gotoxy(92, 17);
					cout << "                                ";
					gotoxy(103, 18);
					int manv;
					cin >> manv;

					gotoxy(92, 17);
					cout << "                                  ";
					if (Is_NhanVien_Have_HD(nv, manv) == 0) {
						gotoxy(92, 17);
						cout << "nhan vien da lap hoa don ko xoa";
						gotoxy(103, 15);
						cout << "                       ";
						break;
					}
					if (Find_ViTriNV(nv, manv) == -1)  //return ==-1
					{
						gotoxy(92, 17);
						cout << "khong tim thay nhan vien can xoa";
						gotoxy(103, 15);
						cout << "                       ";

						break;

					}
					else {
						gotoxy(94, 17);
						cout << "                               ";
						gotoxy(90, 18);
						cout << "                    ";
						gotoxy(103, 6);
						cout << nv.nvdt[Find_ViTriNV(nv, manv)]->MANV;
						gotoxy(103, 9);
						cout << nv.nvdt[Find_ViTriNV(nv, manv)]->HO << nv.nvdt[Find_ViTriNV(nv, manv)]->TEN;
						gotoxy(115, 12);
						cout << nv.nvdt[Find_ViTriNV(nv, manv)]->PHAI;
						gotoxy(103, 15);
						cout << nv.nvdt[Find_ViTriNV(nv, manv)]->CMND;
						gotoxy(94, 17);
						cout << "Ban co thuc su muon xoa ko? ";
						gotoxy(89, 18);
						cout<<"                      ";
						gotoxy(90, 18);
						cout << " y: yes | n: no ";

						while (true) {
							if (kbhit) {
								char input3;
								input3 = getch();
								if (input3 == 121) {

									DEL_ITEM_NHANVIEN(nv, +1);
									//ofstream fileout1;

								//	Write_File_List_NV(fileout, NhanVien);

									gotoxy(103, 6);
									cout << "                      ";
									gotoxy(103, 9);
									cout << "                ";
									gotoxy(115, 12);
									cout << "       ";
									gotoxy(103, 15);
									cout << "                      ";
									gotoxy(94, 17);
									cout << "                                ";
									gotoxy(105, 18);
									cout << "                      ";
									gotoxy(94, 17);
									cout << " Xoa Nhan Vien Thanh Cong";
									gotoxy(90, 18);
									cout << "TIM KIEM   [                    ]";
									sleep(2);
									gotoxy(94, 17);
									cout << "                                 ";
									gotoxy(105, 18);
									cout << "                      ";

									Duyet_NhanVien_case3(nv, nv.n);

									break;

								}
								else if (input3 == 110){
									gotoxy(90, 18);
									cout << "TIM KIEM   [                    ]";
										break;
								}


								

								//else if (input3 == 27)

							}
						}
						gotoxy(103, 15);
						cout << "             ";
						gotoxy(94, 17);
						cout << "                                ";
						gotoxy(105, 18);
						cout << "                     ";



					}
					break;
				}

				case 2: {// thuc hien cap nhat
					SetBGColor(15);
					gotoxy(103, 6);
					cout << "                      ";
					gotoxy(103, 9);
					cout << "                ";
					gotoxy(115, 12);
					cout << "       ";
					gotoxy(103, 15);
					cout << "                      ";
					gotoxy(92, 17);
					cout << "                                ";
					SetBGColor(15);
					gotoxy(103, 18);
					int manv;
					cin >> manv;

					gotoxy(92, 17);
					cout << "                                   ";

					if (Find_ViTriNV(nv, manv) == -1)  //return == -1
					{
						gotoxy(92, 17);
						cout << "khong tim thay nhan vien can sua";
						gotoxy(103, 15);
						cout << "                       ";

						break;

					}
					else {
						gotoxy(94, 17);
						cout << "Ban co thuc su muon xoa ko? ";
						gotoxy(89, 18);
						cout<<"                      ";
						gotoxy(90, 18);
						cout << " y: yes | n: no ";
						while (true) {


							if (kbhit) {
								char input3;
								input3 = getch();
								if (input3 == 121) {
									gotoxy(94, 17);
									cout << "                               ";
									gotoxy(105, 18);
									cout << "                    ";
									gotoxy(103, 6);
									cout << nv.nvdt[Find_ViTriNV(nv, manv)]->MANV;
									gotoxy(103, 9);
									cout << nv.nvdt[Find_ViTriNV(nv, manv)]->HO;
									gotoxy(120, 9);
									cout << nv.nvdt[Find_ViTriNV(nv, manv)]->TEN;
									gotoxy(103, 12);
									cout << nv.nvdt[Find_ViTriNV(nv, manv)]->PHAI;
									gotoxy(103, 15);
									cout << nv.nvdt[Find_ViTriNV(nv, manv)]->CMND;
									gotoxy(103 + nv.nvdt[Find_ViTriNV(nv, manv)]->MANV, 9);
									/// sua Ho Nhan Vien
									while (true) {
										if (kbhit) {
											gotoxy(103 + nv.nvdt[Find_ViTriNV(nv, manv)]->HO.size(), 9);
											char Ho = getch();
											if (Ho == 8) {
												if (nv.nvdt[Find_ViTriNV(nv, manv)]->HO.empty())
													nv.nvdt[Find_ViTriNV(nv, manv)]->HO = ' ';
												gotoxy(103 + nv.nvdt[Find_ViTriNV(nv, manv)]->HO.size() - 1, 9);
												cout << " ";
												nv.nvdt[Find_ViTriNV(nv, manv)]->HO.pop_back();

											}
											else if (Ho == 13 || Ho == 27)
												break;

											else if (Ho >= 'a' && Ho <= 'z' || Ho == 32 || Ho >= 'A' && Ho <= 'Z' || Ho >= '0' && Ho <= '9') {

												gotoxy(103 + nv.nvdt[Find_ViTriNV(nv, manv)]->HO.size(), 9);
												nv.nvdt[Find_ViTriNV(nv, manv)]->HO = nv.nvdt[Find_ViTriNV(nv, manv)]->HO + Ho;

											}

											gotoxy(103, 9);
											cout << nv.nvdt[Find_ViTriNV(nv, manv)]->HO;
										}
									}
									// Sua Ten Nhan Vien
									while (true) {
										gotoxy(120 + nv.nvdt[Find_ViTriNV(nv, manv)]->TEN.size(), 9);
										char Ten = getch();
										if (Ten == 8) {
											if (nv.nvdt[Find_ViTriNV(nv, manv)]->TEN.empty())
												nv.nvdt[Find_ViTriNV(nv, manv)]->TEN = ' ';
											gotoxy(120 + nv.nvdt[Find_ViTriNV(nv, manv)]->TEN.size() - 1, 9);
											cout << " ";
											nv.nvdt[Find_ViTriNV(nv, manv)]->TEN.pop_back();

										}
										else if (Ten == 13 || Ten == 27)
											break;
										else if (Ten >= 'a' && Ten <= 'z' || Ten == 32 || Ten >= 'A' && Ten <= 'Z' || Ten >= '0' && Ten <= '9') {

											gotoxy(121 + nv.nvdt[Find_ViTriNV(nv, manv)]->TEN.size() - 1, 9);

											nv.nvdt[Find_ViTriNV(nv, manv)]->TEN = nv.nvdt[Find_ViTriNV(nv, manv)]->TEN + Ten;


										}
										gotoxy(120, 9);
										nv.nvdt[Find_ViTriNV(nv, manv)]->TEN;

										// Sua Phai Nhan Vien	
									}
									while (true) {
										gotoxy(103 + nv.nvdt[Find_ViTriNV(nv, manv)]->PHAI.size(), 12);
										char Phai = getch();
										if (Phai == 8) {
											gotoxy(103, 12);
											cout << "       ";
											nv.nvdt[Find_ViTriNV(nv, manv)]->PHAI.clear();
											gotoxy(103, 12);
											//cin.ignore();
											getline(cin, nv.nvdt[Find_ViTriNV(nv, manv)]->PHAI);
											while (true) {
												if (nv.nvdt[Find_ViTriNV(nv, manv)]->PHAI == "NAM" || nv.nvdt[Find_ViTriNV(nv, manv)]->PHAI == "NU" || nv.nvdt[Find_ViTriNV(nv, manv)]->PHAI == "Nam" || nv.nvdt[Find_ViTriNV(nv, manv)]->PHAI == "Nu" || nv.nvdt[Find_ViTriNV(nv, manv)]->PHAI == "nam" || nv.nvdt[Find_ViTriNV(nv, manv)]->PHAI == "nu") {
													break;
												}
												else
													gotoxy(103, 12);
												cout << "                     ";
												gotoxy(103, 12);
												cin.ignore();
												cin >> nv.nvdt[Find_ViTriNV(nv, manv)]->PHAI;
											}

										}
										else if (Phai == 13 || Phai == 27)
											break;




									}

									//ofstream fileout1;
								//	Write_File_List_NV(fileout, NhanVien);

									// xoa man hinh
									gotoxy(94, 17);
									cout << "                               ";
									gotoxy(94, 17);
									cout << "Cap Nhat Nhan Vien Thanh Cong";
									sleep(2);
									gotoxy(103, 6);
									cout << "                      ";
									gotoxy(103, 9);
									cout << "                ";
									gotoxy(120, 9);
									cout << "       ";
									gotoxy(103, 12);
									cout << "                      ";
									gotoxy(94, 17);
									cout << "                               ";
									gotoxy(105, 18);
									cout << "                     ";
									gotoxy(103, 15);
									cout << "                ";
									Duyet_NhanVien_case3(nv, nv.n);

									break;

								}
								else if (input3 == 110)
									gotoxy(94, 17);
								cout << "                               ";
								gotoxy(105, 18);
								cout << "                     ";
								gotoxy(103, 15);
								cout << "                ";

								break;

								//else if (input3 == 27)

							}
						}






						break;
					}
				}

				}
			}
			else if (input == 27) {

				color_set();
				system("cls");
				SetBGColor(15);
				//SetBGColor(0);
				menu();
			}
			switch (input) {
			case 50: {
				SetBGColor(15);
				gotoxy(64, 26);
				cout << "                                          ";

				SetBGColor(15);
				gotoxy(56, 26);
				cout << "Trang ";
				gotoxy(64, 26);
				for (int i = -1; i < trang; i++) {
					cout << "[" << i + 2 << "]" << " ";
				}
				gotoxy(68, 26);
				SetBGColor(light_cyan);
				cout << "[" << "2" << "]";
				SetBGColor(15);
				Duyet_NhanVien_case3(nv, 40);
				break;
			}
			case 49: {
				SetBGColor(15);
				gotoxy(64, 26);
				cout << "                                          ";

				gotoxy(56, 26);
				cout << "Trang ";
				gotoxy(64, 26);
				for (int i = -1; i < trang; i++) {
					cout << "[" << i + 2 << "]" << " ";
				}
				gotoxy(64, 26);
				SetBGColor(light_cyan);
				cout << "[" << "1" << "]" << " ";

				SetBGColor(15);
				Duyet_NhanVien_case3(nv, 20);

				break;
			}
			case 51: {
				SetBGColor(15);
				gotoxy(64, 26);
				cout << "                                          ";
				SetBGColor(15);
				gotoxy(56, 26);
				cout << "Trang ";
				gotoxy(64, 26);
				for (int i = -1; i < trang; i++) {
					cout << "[" << i + 2 << "]" << " ";
				}
				gotoxy(72, 26);
				SetBGColor(light_cyan);
				cout << "[" << "3" << "]";
				SetBGColor(15);
				Duyet_NhanVien_case3(nv, 60);
				break;
			}
			case 52: {
				SetBGColor(15);
				gotoxy(64, 26);
				cout << "                                          ";
				SetBGColor(15);
				gotoxy(56, 26);
				cout << "Trang ";
				gotoxy(64, 26);
				for (int i = -1; i < trang; i++) {
					cout << "[" << i + 2 << "]" << " ";
				}
				gotoxy(76, 26);
				SetBGColor(light_cyan);
				cout << "[" << "4" << "]";
				SetBGColor(15);
				Duyet_NhanVien_case3(nv, 80);
				break;
			}
			case 53: {
				SetBGColor(15);
				gotoxy(64, 26);
				cout << "                                          ";
				SetBGColor(15);
				gotoxy(56, 26);
				cout << "Trang ";
				gotoxy(64, 26);
				for (int i = -1; i < trang; i++) {
					cout << "[" << i + 2 << "]" << " ";
				}
				gotoxy(80, 26);
				SetBGColor(light_cyan);
				cout << "[" << "5" << "]";
				SetBGColor(15);
				Duyet_NhanVien_case3(nv, 100);
				break;
			}

			}



		}

	}
}
void draw_case4() {
	//	Read_File_HD_Add_NV(filein1,NhanVien1);
	//	Write_File_HD_CTHD(fileout1,NhanVien);	
	color_set();
	system("cls");
	SetBGColor(15);
	gotoxy(27, 2);
	cout << string(80, char(219));
	for (int i = 3; i < 25; i++) {
		gotoxy(27, i);
		cout << char(219);

	}
	gotoxy(27, 25);
	cout << string(80, char(219)) << endl;
	for (int i = 2; i <= 25; i++) {
		gotoxy(107, i);
		cout << char(219);
	}
	gotoxy(28, 3);
	cout << " MA NHAN VIEN |        	  TEN NHAN VIEN           | GIOI TINH |  CMND     ";
	gotoxy(28, 4);
	cout << "------------------------------------------------------------------------------";
	gotoxy(55, 28);
	cout << "*NHAN ESC DE TRO VE MENU\n";
	gotoxy(53, 29);
	cout << "*SU DUNG PHIM SO DE LUA CHON TRANG\n";
	gotoxy(42, 4);
	for (int i = 3; i < 25; i++) {
		gotoxy(42, i);
		cout << "|";
	}
	gotoxy(82, 4);
	for (int i = 3; i < 25; i++) {
		gotoxy(82, i);
		cout << "|";
	}
	gotoxy(94, 4);
	for (int i = 3; i < 25; i++) {
		gotoxy(94, i);
		cout << "|";
	}

	Duyet_NhanVienDT(nv, 20);
	/////////////////////////////////////////////
	int trang;
	trang = nv.n / 20; // 20 so dong toi da cua bang 
	gotoxy(56, 26);
	cout << "Trang ";
	gotoxy(64, 26);
	for (int i = -1; i < trang; i++) {

		cout << "[" << i + 2 << "]" << " ";
	}
	gotoxy(64, 26);
	SetBGColor(light_cyan);
	cout << "[" << "1" << "]";
	SetBGColor(15);
	///////////////////////////////////////////////
//	nvdt=Create_NhanVienDT(nvdt);
//	nv = Add_NhanVien(nv,nvdt);

// 	ifstream filein;
//	ofstream fileout;
//
// 	cap_phat(nv);
// 	Read_File_List_NV(filein,nv);
 //	Duyet_NhanVienDT(nv);
	while (true) {
		if (kbhit) {
			ShowConsoleCursor(true);
			char input1 = getch();
			if (input1 == 27)
			{
				system("cls");
				menu();
				break;
			}
			switch (input1) {
			case 50: {
				gotoxy(64, 26);
				cout << "                                          ";

				SetBGColor(15);
				gotoxy(56, 26);
				cout << "Trang ";
				gotoxy(64, 26);
				for (int i = -1; i < trang; i++) {
					cout << "[" << i + 2 << "]" << " ";
				}
				gotoxy(68, 26);
				SetBGColor(light_cyan);
				cout << "[" << "2" << "]";
				SetBGColor(15);
				Duyet_NhanVienDT(nv, 40);
				break;
			}
			case 49: {
				gotoxy(64, 26);
				cout << "                                          ";
				SetBGColor(15);
				gotoxy(56, 26);
				cout << "Trang ";
				gotoxy(64, 26);
				for (int i = -1; i < trang; i++) {
					cout << "[" << i + 2 << "]" << " ";
				}
				gotoxy(64, 26);
				SetBGColor(light_cyan);
				cout << "[" << "1" << "]" << " ";

				SetBGColor(15);
				Duyet_NhanVienDT(nv, 20);
				break;
			}
			case 51: {
				gotoxy(64, 26);
				cout << "                                          ";
				SetBGColor(15);
				gotoxy(56, 26);
				cout << "Trang ";
				gotoxy(64, 26);
				for (int i = -1; i < trang; i++) {
					cout << "[" << i + 2 << "]" << " ";
				}
				gotoxy(72, 26);
				SetBGColor(light_cyan);
				cout << "[" << "3" << "]";
				SetBGColor(15);
				Duyet_NhanVienDT(nv, 60);
				break;
			}
			case 52: {
				gotoxy(64, 26);
				cout << "                                          ";
				SetBGColor(15);
				gotoxy(56, 26);
				cout << "Trang ";
				gotoxy(64, 26);
				for (int i = -1; i < trang; i++) {
					cout << "[" << i + 2 << "]" << " ";
				}
				gotoxy(76, 26);
				SetBGColor(light_cyan);
				cout << "[" << "4" << "]";
				SetBGColor(15);
				Duyet_NhanVienDT(nv, 80);
				break;
			}
			case 53: {
				gotoxy(64, 26);
				cout << "                                          ";
				SetBGColor(15);
				gotoxy(56, 26);
				cout << "Trang ";
				gotoxy(64, 26);
				for (int i = -1; i < trang; i++) {
					cout << "[" << i + 2 << "]" << " ";
				}
				gotoxy(80, 26);
				SetBGColor(light_cyan);
				cout << "[" << "5" << "]";
				SetBGColor(15);
				Duyet_NhanVienDT(nv, 100);
				break;
			}

			}
		}
		///////////////////////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////////////////////
	}
}
void draw_case5() {
	 NVDT nvdt;
	 CTHD_DATA cthd;
	 CTHD list1_CTHD;
	color_set();
	system("cls");
	SetBGColor(15);
	gotoxy(17, 7);
	cout << string(100, char(219));
	for (int i = 7; i < 30; i++) {
		gotoxy(17, i);
		cout << char(219);

	}
	gotoxy(17, 30);
	cout << string(100, char(219)) << endl;
	for (int i = 7; i <= 30; i++) {
		gotoxy(117, i);
		cout << char(219);
	}

	gotoxy(18, 8);
	cout << " stt	|   	Ten Vat Tu	  |   Ma VT   |   So Luong   |   Don Gia  |	Thanh Tien	 ";
	gotoxy(18, 9);
	cout << "--------------------------------------------------------------------------------------------------";
	gotoxy(57, 1);
	cout << " HOA DON BAN HANG";
	gotoxy(40, 4);
	cout << "Loai phieu (xuat/nhap):  [         /        ]";
	gotoxy(40, 3);
	cout << "Ma Nhan Vien Lap Phieu:  [                  ]  [                             ]";
	gotoxy(40, 5);
	cout << "Ngay Lap :               [     /     /      ]  [                             ]";
	gotoxy(40, 6);
	cout << "So Hoa Don:              [                  ]  [                             ]";
	gotoxy(18, 27);
	cout << "--------------------------------------------------------------------------------------------------";
	gotoxy(79, 28);
	cout << "Tong Tien :   ";

	for (int i = 10; i < 27; i++) {
		gotoxy(24, i);
		cout << "|";
	}
	for (int i = 10; i < 27; i++) {
		gotoxy(50, i);
		cout << "|";
	}
	for (int i = 10; i < 27; i++) {
		gotoxy(62, i);
		cout << "|";
	}
	for (int i = 10; i < 27; i++) {
		gotoxy(77, i);
		cout << "|";
	}
	for (int i = 10; i < 27; i++) {
		gotoxy(90, i);
		cout << "|";
	}
	gotoxy(52, 10);
	gotoxy(55, 31);
	cout << "*NHAN ESC DE LUU HOA DON\n";
	gotoxy(55, 32);
	cout << "*NHAN PHIM X DE XOA VAT TU\n";
	gotoxy(50, 33);
	cout << "* Dung Phim Mui Ten De Lua Chon Nhap/Xuat ";
///////////////////////////////////////////////////////////////////
	int manv;
	char input;
	while (true){
	//struct DATA_NHANVIEN Data_NV;
	ShowConsoleCursor(true);
	gotoxy(72,3);
//	DeLete_Node_NV(Data_NV);
	
	cin>>manv;
	gotoxy(89,3);
    cout << "                        ";
	if ( Find_ViTriNV(nv,manv)== -1){  //return == -1
    
		gotoxy(72,3);
		cout << "         ";				
    	gotoxy(89,3);
    	cout << "khong tim thay nhan vien ";					
		}
	else {
		gotoxy(89,3);
		cout << nv.nvdt[Find_ViTriNV(nv,manv)]->HO << " " <<nv.nvdt[Find_ViTriNV(nv,manv)]->TEN;
        break;
		}
	
	input = getch();
	if (input == 27 )
	{
	system("cls");
	menu();
	}
}	
	//////////////////////////////////////////////////////////////////////////////////	
	////ham nhap xuat hoa don
	int lcnhapxuat ;
	char input1,input2;
	string NX[3]={"NHAP","XUAT"};	
	gotoxy(69,4);
	cout << NX[0];
	gotoxy(77,4);
	cout << NX[1];
	
	while (true){
			
		ShowConsoleCursor(false);
	 	if(kbhit){
		  input1 = getch();
		 
		if (input1 == 13){
		break;	
		}
		else if (input1 == 75){
			while(true){
			
			gotoxy(69,4);
			SetBGColor(light_cyan);
			cout << NX[0];
			SetBGColor(15);
			gotoxy(77,4);
			cout << NX[1];
			lcnhapxuat = 0;
			ShowConsoleCursor(false);
			break;	
		}
			
			
		}
		else if (input1 == 77){
			while(true){
				ShowConsoleCursor(false);
				gotoxy(77,4);
				SetBGColor(light_cyan);
				cout << NX[1];
				SetBGColor(15);
				gotoxy(69,4);
				cout << NX[0];
				lcnhapxuat = 1;//1 N 0 X
				ShowConsoleCursor(false);
				break;
			}
		}		 
		else if(input1 == 27){
	
			color_set();
			system("cls");
			SetBGColor(15);
			//SetBGColor(0);
			gotoxy(45, 5);
			cout << "---------------------------\n";
			gotoxy(45, 6);
			cout << "| BAN CO MUON LUU HAY KO? |\n";
			gotoxy(45, 7);
			cout << "|            |            |\n"; 
			gotoxy(45, 8);
			cout << "|  Y : yes   |   N : NO   |\n";
			gotoxy(45, 9);
			cout << "|            |            |\n";
			gotoxy(45, 10);
			cout << "---------------------------\n";
			input1 = getch();
			 if (input1 == 121){
				
				color_set();
				system("cls");
				SetBGColor(15);
				menu();
				break;
			}
			else if (input1 == 110)
			{
				//color_set();
				
				system("cls");
				//SetBGColor(15);
				draw_case5();
			}
			
		
			}
				 
				 
}

	vitricase5 ={0,0};			

}
HOADON hoadon;

while (true){
	if (kbhit){
		input1 = getch();
		if(input1 == 13){
				while(input1 != 27){ 
			
		 	ShowConsoleCursor(true);
		 	gotoxy(20,10+vitricase5.y);
			cout << vitricase5.x+1;
			gotoxy(90,6);
			cout     << "                         ";
		 		//input1 = getch();
		 		if (input1 == 13){
				 gotoxy(21,10+vitricase5.y);
				 //cout << vitricase5.y + 1;
				 CTHD_DATA INFO;
				 //Creat_CTHD(INFO,vitricase5.y);
				 Creat_node_CTHD(INFO);
				list1_CTHD.n++;
				 //list1_CTHD =ADD_CTHD(list1_CTHD ,INFO);
				 Insert_list_CTHD (list1_CTHD, vitricase5.y ,INFO);
				 //gotoxy(68,10+vitricase5.y);
				 //cout << vitricase5.y;
		 		
				 if (vitricase5.y == 16 ){ //vitri cuoi bang
				 vitricase5.x = 0;
				 vitricase5.y = 0;
				 //break;
				 }
				 else {
				 vitricase5.x++;
		 		 vitricase5.y++;
		 		 //break;
				 }
				 
				 }
				  
		 		break;
		 		}
		 		Output_Case5(list1_CTHD);
				 }
				 
			else if (input1 == 88 || input1 == 120) // chu X hoac x
				{
					gotoxy(90,6);
					cout     << "                         ";
					gotoxy(90,6);
					string Mavt;
					cout << "Ma Vat Tu can xoa: ";
					cin >> Mavt;
					if (Search_Mavt(list1_CTHD,Mavt) == -1){
						gotoxy(90,6);
						cout << "khong thay VT can xoa";
					}
					else {
						gotoxy (90,6);
						cout << "ban that su muon xoa ko?";
						

						gotoxy (90,6);
						cout << "                        ";
						if (lcnhapxuat == 1){
				
							
							Fix_VT_Xuat(T,list1_CTHD.hd_data[Search_Mavt(list1_CTHD,Mavt)].MAVT,list1_CTHD.hd_data[Search_Mavt(list1_CTHD,Mavt)].Soluong);
						
						}
						else if (lcnhapxuat == 0) {
							
							Fix_VT_Nhap(T,list1_CTHD.hd_data[Search_Mavt(list1_CTHD,Mavt)+1].MAVT,list1_CTHD.hd_data[Search_Mavt(list1_CTHD,Mavt)+1].Soluong);
												
					
						}							
					DEL_ITEM_CTHD(list1_CTHD, Search_Mavt(list1_CTHD,Mavt)+1);
						vitricase5.y = vitricase5.y-1;
						vitricase5.x = vitricase5.x-1;
					for (int j = 0; j < 16 ;j++){
						gotoxy(30,10+j);
						cout << "                   ";					
						gotoxy(52,10+j);
						cout << "         ";
						gotoxy(68,10+j);
						cout << "         ";
						gotoxy(78,10+j);
						cout << "            ";
						gotoxy(95,10+j);
						cout << "                 ";
						gotoxy(95,28);
						cout << "                ";
						}
						tong = 0;
					for (int i = 0; i < list1_CTHD.n;i++){
	//				
						
						gotoxy(52,10+i);
						cout << list1_CTHD.hd_data[i].MAVT;

					
						gotoxy(30,10+i);
					
						Find_Print_Deleta_case5(T,Cut_enter(list1_CTHD.hd_data[i].MAVT),i);
						gotoxy(68,10+i);
						cout << list1_CTHD.hd_data[i].Soluong;
						
						gotoxy(78,10+i);
						cout << list1_CTHD.hd_data[i].Dongia;
	
						gotoxy(95,10+i);
				
						Print_Number_With_point (list1_CTHD.hd_data[i].Soluong * list1_CTHD.hd_data[i].Dongia);
						tong = tong + (list1_CTHD.hd_data[i].Soluong)*(list1_CTHD.hd_data[i].Dongia);
						gotoxy(95,28);
						cout << "                ";
						gotoxy(95,28);
				
						Print_Number_With_point(tong);
					
					}
				
				}
				 }	
			else if(input1 == 27  ){
			Creat_HD(hoadon,lcnhapxuat,list1_CTHD);
			//Add_HoaDon_To_NV(NhanVien,hoadon,Search_list_NV(NhanVien,Data_NV));
			color_set();
			system("cls");
			SetBGColor(15);
			//SetBGColor(0);
			while ( true){
			gotoxy(45, 5);
			cout << "---------------------------\n";
			gotoxy(45, 6);
			cout << "| BAN CO MUON LUU HAY KO? |\n";
			gotoxy(45, 7);
			cout << "|            |            |\n"; 
			gotoxy(45, 8);
			cout << "|  Y : yes   |   N : NO   |\n";
			gotoxy(45, 9);
			cout << "|            |            |\n";
			gotoxy(45, 10);
			cout << "---------------------------\n";
			char input2 = getch();
			 if (input2 == 121){
			 	DSHD node_hd = new Node_HOADON;
				node_hd= Creat_Node_Dshd(hoadon);
			//	Add_CTHD_To_HD(node_hd,list1_CTHD);
				Add_Node_Head(nv, node_hd , Find_ViTriNV(nv,manv));
				
				SoHoaDon_Auto ++;
			//	Write_File_HD_CTHD(fileout1,NhanVien);
				
	
		//		Write_Tree (fileout,T);
	//			}
				tong = 0; // sau nay lap hoa don tong tri gia tro lai  = 0 //
				color_set();
				system("cls");
				SetBGColor(15);
				draw_case5();
				break;
			}
			else if (input2 == 110)
			{
				//color_set();
				if (lcnhapxuat == 1){
				
				for (int i = 0; i < list1_CTHD.n;i++){
				//	Fix_VT_Xuat(T,list1_CTHD.INFO[i].MAVT,list1_CTHD.INFO[i].SoLuong);
					
				}	
			//	system("pause");
				}
				else if (lcnhapxuat == 0) {
				for (int i = 0; i < list1_CTHD.n;i++){
				//	Fix_VT_Nhap(T,list1_CTHD.INFO[i].MAVT,list1_CTHD.INFO[i].SoLuong);
				}					
					
				}			
				system("cls");
				draw_case5();
			}
			
						}
			}	 
				 
		}
	}
////////////////////////////////////////////////////////////////////

}
void draw_case6() {

	//	Write_File_HD_CTHD(fileout1,NhanVien);	
	color_set();
	system("cls");
	SetBGColor(15);
	gotoxy(17, 7);
	cout << string(100, char(219));
	for (int i = 7; i < 30; i++) {
		gotoxy(17, i);
		cout << char(219);

	}
	gotoxy(17, 30);
	cout << string(100, char(219)) << endl;
	for (int i = 7; i <= 30; i++) {
		gotoxy(117, i);
		cout << char(219);
	}

	gotoxy(18, 8);
	cout << " stt	|   	Ten Vat Tu	  |   Ma VT   |   So Luong   |   Don Gia  |	Thanh Tien	 ";
	gotoxy(18, 9);
	cout << "--------------------------------------------------------------------------------------------------";
	gotoxy(57, 1);
	cout << " HOA DON BAN HANG";
	gotoxy(40, 3);
	cout << "Loai phieu (xuat/nhap):  [                              ]";
	gotoxy(40, 4);
	cout << "Ten Nhan Vien Lap Phieu: [                              ]";
	gotoxy(40, 5);
	cout << "Ngay Lap :               [                              ]";
	gotoxy(18, 27);
	cout << "--------------------------------------------------------------------------------------------------";
	gotoxy(79, 28);
	cout << "Tong Tien :   ";
	gotoxy(40, 2);
	cout << "Ma Hoa Don:              [                              ]";
	gotoxy(55, 32);
	cout << "*NHAN ESC DE TRO VE MENU\n";

	for (int i = 10; i < 27; i++) {
		gotoxy(24, i);
		cout << "|";
	}
	for (int i = 10; i < 27; i++) {
		gotoxy(50, i);
		cout << "|";
	}
	for (int i = 10; i < 27; i++) {
		gotoxy(62, i);
		cout << "|";
	}
	for (int i = 10; i < 27; i++) {
		gotoxy(77, i);
		cout << "|";
	}
	for (int i = 10; i < 27; i++) {
		gotoxy(90, i);
		cout << "|";
	}

	while (true){
		if (kbhit){
		ShowConsoleCursor(true);	
		Traverse_Case_6(nv);
		char input1 = getch();
		if (input1 == 27)
		{
		system("cls");	
		menu();
		break;
	    }
				  }	
	}	


}
void draw_case7() {
	ShowConsoleCursor(true);
	//	Write_File_HD_CTHD(fileout1,NhanVien);	
	color_set();
	system("cls");
	SetBGColor(15);
	
	gotoxy(44, 2);
	cout << "   BANG LIET KE CAC HOA DON TRONG KHOANG THOI GIAN";
	gotoxy(54, 3);
	cout << "MA NHAN VIEN: ";
	gotoxy(48, 4);
	cout << "TU NGAY:|   /  /   ";
	gotoxy(68, 4);
	cout << "| DEN NGAY: |   /  /   ";
	gotoxy(92, 4);
	cout << "|";

	while (true) {
		
		if (kbhit) {
			ShowConsoleCursor(true);
			system("cls");
			gotoxy(68, 3);
			cout << "            ";
			gotoxy(44, 2);
			cout << "   BANG LIET KE CAC HOA DON TRONG KHOANG THOI GIAN";
			gotoxy(54, 3);
			cout << "MA NHAN VIEN: ";
			gotoxy(48, 4);
			cout << "TU NGAY:|   /  /   ";
			gotoxy(68, 4);
			cout << "| DEN NGAY: |   /  /   ";
			gotoxy(92, 4);
			cout << "|";
			char input1 = getch();
			if (input1 == 27)
			{
				system("cls");
				menu();
				break;
			}else{

		int MaNV;
		gotoxy(68, 3);
		cin >> MaNV;
	if (Find_ViTriNV(nv, MaNV) == -1){
		gotoxy(68,3);
		cout << " khong tim thay NV";
		sleep(2);
		draw_case7();
	}
	else{
		struct ngaylap NgayDau;
		struct ngaylap NgayCuoi;
		Input_Case_7(NgayDau,NgayCuoi);
		int vitri=0;

			DSHD q = nv.nvdt[Find_ViTriNV(nv, MaNV)]->first_hd;
			for (q ; q != NULL ; q = q->pNext){
				int Tong=0;
				if ((Compare_Date(q->hd.NgaylapHD, NgayDau) == 1 || Compare_Date(q->hd.NgaylapHD, NgayDau) == 0) && (Compare_Date(q->hd.NgaylapHD, NgayCuoi) == -1 || Compare_Date(q->hd.NgaylapHD, NgayDau) == 0)){
						gotoxy(18, 6+vitri);
						cout << "  SO HD :|" <<q->hd.SoHD<<"|	NGAY LAP:|"<<q->hd.NgaylapHD.ngay<<"/"<<q->hd.NgaylapHD.thang<<"/"<<q->hd.NgaylapHD.nam<<" | LOAI HD:|"<<q->hd.Loai<<"|";
						gotoxy(18, 7+vitri);
						cout << "--------------------------------------------------------------------------------------------------";
						gotoxy(18, 8+vitri);
						cout << " stt	|   	Ten Vat Tu	  |   Ma VT   |   So Luong   |   Don Gia  |	Thanh Tien	 ";
						gotoxy(18, 9+vitri);
						cout << "--------------------------------------------------------------------------------------------------";
						
						for (int j = 0; j < q->hd.cthd.n ; j++){
							gotoxy(19,10+j+vitri);
							cout << j+1;
							gotoxy(29,10+j+vitri);
							Traverse_Tree_case_7 (T,q->hd.cthd.hd_data[j].MAVT,j,vitri);
							gotoxy(55,10+j+vitri);
							cout << q->hd.cthd.hd_data[j].MAVT;
							gotoxy(67,10+j+vitri);
							cout <<q->hd.cthd.hd_data[j].Soluong;
							gotoxy(78,10+j+vitri);
							cout << fixed << setprecision(0) << q->hd.cthd.hd_data[j].Dongia;
							gotoxy(95,10+j+vitri);
						//	cout << fixed << setprecision(0) <<(NhanVien.NV[i].HD->DATA_HD.CT_HD->INFO[j].SoLuong)*(NhanVien.NV[i].HD->DATA_HD.CT_HD->INFO[j].DonGia);
							Print_Number_With_point ((q->hd.cthd.hd_data[j].Soluong)*(q->hd.cthd.hd_data[j].Dongia));
							Tong +=	(q->hd.cthd.hd_data[j].Soluong)*(q->hd.cthd.hd_data[j].Dongia);
					
					}
					
					vitri+=(4+q->hd.cthd.n);
						gotoxy(18, 5+vitri);
						cout << "--------------------------------------------------------------------------------------------------";
					vitri++;
				}   
			}
			gotoxy(55, 8+vitri);
			cout << "*NHAN ESC DE TRO VE MENU\n";	
			char input1 = getch();
	}
			
				
			}
		}
	}
}
void draw_case8() {
	ShowConsoleCursor(true);
	//	Write_File_HD_CTHD(fileout1,NhanVien);	
	color_set();
	system("cls");
	SetBGColor(15);
	gotoxy(17, 7);
	cout << string(100, char(219));
	for (int i = 7; i < 30; i++) {
		gotoxy(17, i);
		cout << char(219);

	}
	gotoxy(17, 30);
	cout << string(100, char(219)) << endl;
	for (int i = 7; i <= 30; i++) {
		gotoxy(117, i);
		cout << char(219);
	}
	gotoxy(44, 3);
	cout << "BANG LIET KE 10 HOA DON CO DOANH THU CAO NHAT ";
	gotoxy(48, 4);
	//	cout <<"TU NGAY:|   /   /  ";

	gotoxy(68, 4);
	//	cout <<"| DEN NGAY: |   /   /  ";
	gotoxy(92, 4);
	//	cout <<"|";
	gotoxy(18, 8);
	cout << "  SO HD	 |	NGAY LAP | LOAI HD |		HO TEN NV LAP   	| TRI GIA HOA DON";
	gotoxy(18, 9);
	cout << "--------------------------------------------------------------------------------------------------";


	gotoxy(55, 32);
	cout << "*NHAN ESC DE TRO VE MENU\n";
	gotoxy(33, 4);
	for (int i = 8; i < 30; i++) {
		gotoxy(33, i);
		cout << "|";
	}
	gotoxy(49, 4);
	for (int i = 8; i < 30; i++) {
		gotoxy(49, i);
		cout << "|";
	}
	gotoxy(59, 4);
	for (int i = 8; i < 30; i++) {
		gotoxy(59, i);
		cout << "|";
	}
	gotoxy(96, 4);
	for (int i = 8; i < 30; i++) {
		gotoxy(96, i);
		cout << "|";
	}
	gotoxy(48, 4);
	cout << "TU NGAY:|   /  /   ";

	gotoxy(68, 4);
	cout << "| DEN NGAY: |   /  /    ";
	while (true) {
		if (kbhit) {
			ShowConsoleCursor(true);
			char input1 = getch();
			if (input1 == 27)
			{
				system("cls");
				menu();
				break;
			}
		}
	}
}
void draw_case9() {

	ShowConsoleCursor(true);
	//	Write_File_HD_CTHD(fileout1,NhanVien);	
	color_set();
	system("cls");
	SetBGColor(15);
	gotoxy(17, 7);
	cout << string(100, char(219));
	for (int i = 7; i < 30; i++) {
		gotoxy(17, i);
		cout << char(219);

	}
	gotoxy(17, 30);
	cout << string(100, char(219)) << endl;
	for (int i = 7; i <= 30; i++) {
		gotoxy(117, i);
		cout << char(219);
	}
	gotoxy(44, 3);
	cout << "   BANG LIET KE 10 VAT TU CO DOANH THU CAO NHAT ";
	gotoxy(48, 4);
	//	cout <<"TU NGAY:|   /   /  ";

	gotoxy(68, 4);
	//	cout <<"| DEN NGAY: |   /   /  ";
	gotoxy(92, 4);
	//	cout <<"|";
	gotoxy(18, 8);
	cout << "  MA VT	 |	DVI TINH | SL  TON |		 TEN VAT TU     	| TRI GIA VAT TU  ";
	gotoxy(18, 9);
	cout << "--------------------------------------------------------------------------------------------------";


	gotoxy(55, 32);
	cout << "*NHAN ESC DE TRO VE MENU\n";
	gotoxy(33, 4);
	for (int i = 8; i < 30; i++) {
		gotoxy(33, i);
		cout << "|";
	}
	gotoxy(49, 4);
	for (int i = 8; i < 30; i++) {
		gotoxy(49, i);
		cout << "|";
	}
	gotoxy(59, 4);
	for (int i = 8; i < 30; i++) {
		gotoxy(59, i);
		cout << "|";
	}
	gotoxy(96, 4);
	for (int i = 8; i < 30; i++) {
		gotoxy(96, i);
		cout << "|";
	}
	gotoxy(48, 4);
	cout << "TU NGAY:|   /  /   ";

	gotoxy(68, 4);
	cout << "| DEN NGAY: |   /  /    ";

	while (true) {
		if (kbhit) {
			ShowConsoleCursor(true);
			char input1 = getch();
			if (input1 == 27)
			{
				system("cls");
				menu();
				break;
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
void  menu() {
	ShowConsoleCursor(false);
	int x = 40, y = 5;
	int FieldSelect = 0;
	string Menu[9] = { "1. NHAP VAT TU","2. IN DANH SACH VAT TU TON KHO","3. NHAP NHAN VIEN","4. IN DANH SACH NHAN VIEN","5. LAP HOA DON NHAP, XUAT","6. IN HOA DON THEO SO HOA DON","7. THONG KE HOA DON THEO KHOANG THOI GIAN ","8. IN 10 HOA DON CO DOANH THU CAO NHAT","9. IN 10 VAT TU VO DOANH THU CAO NHAT" };
	position vitri[9];
	gotoxy(x + 14, y - 2);
	cout << "MENU";
	gotoxy(x + 5, y + 20);
	cout << "*NHAN ENTER DE CHON CHUC NANG\n";
	gotoxy(x + 4, y + 21);
	cout << "*NHAN ESC DE THOAT CHUONG TRINH\n";
	gotoxy(x + 3, y + 22);
	cout << "*SU DUNG PHIM MUI TEN DE LUA CHON\n";

	for (int i = 0; i < 9; i++) {
		vitri[i].x = x;
		vitri[i].y = y + i;
		gotoxy(vitri[i].x, vitri[i].y);
		cout << Menu[i];
	}

	gotoxy(vitri[0].x, vitri[0].y);
	cout << Menu[0];
	while (true) {
		if (kbhit) {
			char input = getch();
			if (input == -32) {
				input = getch();
				switch (input) {
				case 80: {
					gotoxy(vitri[FieldSelect].x, vitri[FieldSelect].y);
					SetBGColor(15);
					cout << Menu[FieldSelect];
					FieldSelect++;
					if (FieldSelect > 8) {
						FieldSelect = 0;
					}
					gotoxy(vitri[FieldSelect].x, vitri[FieldSelect].y);
					SetBGColor(light_cyan);   //light_cyan
					cout << Menu[FieldSelect];

					break;
				}
				case 72: {
					gotoxy(vitri[FieldSelect].x, vitri[FieldSelect].y);
					SetBGColor(15);
					cout << Menu[FieldSelect];
					FieldSelect--;
					if (FieldSelect < 0) {
						FieldSelect = 8;
					}
					gotoxy(vitri[FieldSelect].x, vitri[FieldSelect].y);
					SetBGColor(light_cyan);
					cout << Menu[FieldSelect];
					break;
				}

				case 77: {
					break;
				}
				}
			}
			else if (input == 13) {


				break;

			}
			else if (input == 27)
			{
				SetBGColor(light_cyan);
				system("cls");
				//SetBGColor(light_cyan); 
				//color_set();

				gotoxy(45, 5);
				cout << " Product of Nhom20 Student of PTIT";
				gotoxy(51, 6);
				cout << "supplies manage ver1.0";
				string thanks[30] = { "THANKS","FOR","USING","MY","PROGRAM" };
				string GoodBye[20] = { "G","O","O","D",".",".","B","Y","E"," ","!","!" };
				gotoxy(47, 9);
				for (int i; i <= 16; i++) {
					cout << thanks[i] << "  ";
					Sleep(100);
				}
				gotoxy(56, 11);
				for (int i = 0; i <= 16; i++) {
					cout << GoodBye[i];
					Sleep(100);
				}

				while (true) {
				}
			}
		}
	}

	switch (FieldSelect) {
	case 0: {
		gotoxy(x + 5, y + 10);
		gotoxy(x + 5, y + 10); "ban chon chuc nang 1";		// noi thuc hien chuc nang 1
		draw_case1();


		break;
	}
	case 1: {
		gotoxy(x + 5, y + 11);
		cout << "ban chon chuc nang 2";		// noi thuc hien chuc nang 2
		draw_case2();

		break;
	}
	case 2: {
		gotoxy(x + 5, y + 12);
		cout << "ban chon chuc nang 3";		// noi thuc hien chuc nang 3
		draw_case3();

		break;
	}
	case 3: {
		gotoxy(x + 5, y + 13);
		cout << "ban chon chuc nang 4";		// noi thuc hien chuc nang 4
		draw_case4();

		break;
	}
	case 4: {
		gotoxy(x + 5, y + 14);
		cout << "ban chon chuc nang 5";		// noi thuc hien chuc nang 5
		draw_case5();
		break;
	}
	case 5: {
		gotoxy(x + 5, y + 15);
		cout << "ban chon chuc nang 6";		// noi thuc hien chuc nang 6
		system("cls");
	//	Read_File_HD_Add_NV(filein,nv);
		draw_case6();
	//	Read_File_HD_Add_NV(filein,nv);
		break;

	}
	case 6: {
		gotoxy(x + 5, y + 16);
		cout << "ban chon chuc nang 7";		// noi thuc hien chuc nang 7
		draw_case7();

		break;
	}
	case 7: {
		gotoxy(x + 5, y + 17);
		//	cout << "ban chon chuc nang 8";		// noi thuc hien chuc nang 8
		draw_case8();
		/*(	system("cls");
		for ( int i = 0; i < Pos_Empty_NV(NhanVien);i++){
			cout << "---------------------------------------------------------------------------------------------------------------\n";

			cout << NhanVien.NV[i].MANV << " "<< NhanVien.NV[i].HO << " "<< NhanVien.NV[i].TEN << " "<< NhanVien.NV[i].PHAI << "\n";
			cout << "--------------------------------------------------------------------------------------------------------------\n";
			for (NhanVien.NV[i].HD; NhanVien.NV[i].HD != NULL ; NhanVien.NV[i].HD = NhanVien.NV[i].HD->pNext){
				cout << NhanVien.NV[i].HD->DATA_HD.loai << " " <<NhanVien.NV[i].HD->DATA_HD.SoHD << " "<<NhanVien.NV[i].HD->DATA_HD.ngaylap.ngay << "/" <<NhanVien.NV[i].HD->DATA_HD.ngaylap.thang<< "/" << NhanVien.NV[i].HD->DATA_HD.ngaylap.nam<< "\n";
				for (int j = 0;j < Pos_Empty_CTHD(NhanVien.NV[i].HD->DATA_HD.CT_HD);j++){
					cout << NhanVien.NV[i].HD->DATA_HD.CT_HD->INFO[j].MAVT << " " <<NhanVien.NV[i].HD->DATA_HD.CT_HD->INFO[j].SoLuong<< " "<<NhanVien.NV[i].HD->DATA_HD.CT_HD->INFO[j].DonGia << "\n";
				}
			}
		}
//		int i = 0;
//		int j = 0;
//		cout << NhanVien.NV[i].HD->DATA_HD.CT_HD->INFO[j].MAVT << " " <<NhanVien.NV[i].HD->DATA_HD.CT_HD->INFO[j].SoLuong<< " "<<NhanVien.NV[i].HD->DATA_HD.CT_HD->INFO[j].DonGia << "\n";
*/
		break;
	}
	case 8: {
		draw_case9(); // chuc nang 9
		break;
	}

	}
}

int main() {
	SetBGColor(15);
	system("cls");
	color_set();
	
	Read_File_List_NV(filein,nv);
	//Write_File_List_NV(fileout,nv);
   	Read_Tree(filein,T);
	Read_File_HD_Add_NV(filein,nv);
	menu();

	return 0;
}



