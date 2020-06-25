#pragma once
#include "HangSo.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "mylib.h"

using namespace std;

//Diem thi
struct ChonDA
{
	int id;
	int daChon;
};
struct DiemThi
{
	int n;
	float diem;
	ChonDA DSCHDTL[MAXCHDTL];
};
struct NodeDiemThi
{
	string maMH;
	DiemThi diemThi;
	struct NodeDiemThi* next;
};
typedef NodeDiemThi* NodeDT;

void InsertFirstDT(NodeDT& First, string maMH, DiemThi diemThi);
void InsertDT(NodeDT& First, string maMH, DiemThi diemThi);
void ClearDT(NodeDT& First);
void SapXepDT(NodeDT& First);
int DemSLBODT(NodeDT First);
NodeDT SearchDT(NodeDT First, string maMH);

//Mon hoc
struct MonHoc
{
	string maMH;
	string tenMH;
};
typedef struct
{
	int n;
	MonHoc* dsNodeMH[MAXMH];
} DanhSachMonHoc;

int InsertDSMH(DanhSachMonHoc& ds, MonHoc mh);
int UpdateDSMH(DanhSachMonHoc& ds, MonHoc mh);
int DeleteDSMH(DanhSachMonHoc& ds, string maMH);
int  SearchMH(DanhSachMonHoc& ds, string maMH);

//Sinh vien
struct SinhVien
{
	string maSV;
	string ho;
	string ten;
	int phai;
	string password;
	NodeDT DT = NULL;
};
struct NodeSinhVien
{
	SinhVien sv;
	struct NodeSinhVien* next;
};
typedef NodeSinhVien* NodeSV;

struct DanhSachSinhVien
{
	NodeSV First;
};

void KhoiTaoDSSV(DanhSachSinhVien& DSDT);
int InsertSV(NodeSV& First, SinhVien sv);
NodeSV SearchSV(NodeSV First, string maSV);
bool UpdateSV(NodeSV& First, SinhVien sv);
bool DeleteSV(NodeSV& First, SinhVien sv);
void ClearDSSV(NodeSV& First);
void DuyetDSSV(NodeSV First);
void SapXepDSSV(NodeSV& First);
int DemSLSV(NodeSV First);
string PhaiSV(int phai);
int DemSLSVDaThiMonHoc(NodeSV First, string maMH);
NodeSV SearchSVSTT(NodeSV First, int stt);

//Lop
struct Lop
{
	string maLop;
	string tenLop;
	NodeSV dssv = NULL;
};
struct DSLOP
{
	int n;
	Lop LopArr[MAXLOP];
};
int InsertLop(DSLOP& dsLop, Lop lop);
int UpdateLop(DSLOP& dsLop, Lop lop);
int DeleteLop(DSLOP& dsLop, Lop lop);
int SearchLop(DSLOP dsLop, string maLop);

//Cau hoi
struct CauHoi
{
	int id;
	string maMH;
	string noiDung;
	string A;
	string B;
	string C;
	string D;
	int dapAn;
};
struct NodeCauHoi
{
	CauHoi cauHoi;
	int bf;
	struct NodeCauHoi* left, * right;
};
typedef struct NodeCauHoi* NodeCH;

NodeCH RotateLeftCH(NodeCH root);
NodeCH RotateRightCH(NodeCH ya);
void InsertCauHoi(NodeCH& pavltree, CauHoi cauHoi);
NodeCH SearchCH(NodeCH root, int x);
void DemCH(NodeCH root, int& dem);
void UpdateCauHoi(NodeCH& rootCH, CauHoi ch);

//danh sach cau hoi theo mon hoc
struct DSCHTMH
{
	int n;
	CauHoi dsch[MAXCH];
};
int InsertCHVaoDSCHTMH(DSCHTMH& ds, CauHoi cauHoi);
void BienDoiThanhNodeCHTheoMonHoc(NodeCH rootCH, string maMH, DSCHTMH& dsch);
int LayCauHoiThi(NodeCH rootCH, string maMH, int soCauHoi, DSCHTMH& deThi);