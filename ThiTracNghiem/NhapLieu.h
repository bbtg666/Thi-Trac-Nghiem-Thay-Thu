#pragma once
#include "GiaoDienVaDieuKhien.h"
#include "DanhSach.h"

string Trim(string str);
string HoanThienChuoi(string str);
string CheckMa(string str);
int NhapDuLieu(int x, int y, int maxLength, string& data, int inHoa);
int NhapTaiKhoan(int x, int y, int maxLength, string& data);
int NhapPassword(int x, int y, int maxLength, string& data);
int NhapDuLieuLop(DSLOP& dsLop);
int NhapDuLieuSinhVien(NodeSV& First, DSLOP dsLop);
void NhapLieuSuaLop(DSLOP& dsLop, int luaChon);
void NhapDuLieuSuaSinhVien(NodeSV& First, int luaChon);
void NhapLieuSuaMonHoc(DanhSachMonHoc& dsmh, int luaChon);
int NhapDuLieuMonHoc(DanhSachMonHoc& dsmh);
int NhapDuLieuCauHoi(NodeCH& rootCH, DSCHTMH& dsch, string maMH);
void NhapDuLieuSuaCauHoi(NodeCH& rootCH, DSCHTMH& dsch, int luaChon);
int NhapSoCauHoi(int& slch);
int NhapSoPhutThi(int& soPhut);