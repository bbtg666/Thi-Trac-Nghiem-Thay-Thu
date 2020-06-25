#pragma once
#include "DocGhiFile.h"
#include "NhapLieu.h"

// dung chung
void BatDau(DSLOP& dsLop, NodeCH& rootCH, DanhSachMonHoc& dsmh);
void VeHCN(int x, int y, int width, int height, int color);
void VeKhungChung();
void NormalBlue();
void NormalWhite();
string DongHoDemNguoc(clock_t begin, int soPhut);
bool HetGio(clock_t batdau, int soPhut);

//Tieu de
void VeTieuDe();
void VeTieuDeGiaoVien();

//Dang nhap
void ManHinhDangNhap();
void DangNhap(DSLOP& dsLop, NodeCH& rootCH, DanhSachMonHoc& dsmh);
void SetMauChuXY(int x, int y, int color, string noidung);
//Giao vien
void GiaoVien(DSLOP& dsLop, NodeCH& rootCH, DanhSachMonHoc& dsmh);
int MenuGiaoVien(DSLOP& dsLop);

//Thi
void Thi(DSLOP& dsLop, NodeCH rootCH, DanhSachMonHoc dsmh, string maSV);

//Lop
string KiemTraNoiDungCauHoi(string ndch);
string XuLyDapAn(int da);
string XuLyHienThiCauHoi(string noiDung, int length);
void VeDSCauHoi(DSCHTMH dsch, int page);
void VeDSMonHoc(DanhSachMonHoc& dsmh, int page);
string XuLyDiemThi(NodeDT dt);
void VeNoiDungCauHoi(CauHoi cauHoi);
void VeGiaoDienLop(int n);
void VeDSLop(DSLOP dsLop, int page);
void ShowLop(DSLOP& dsLop);
void ShowMonHoc(DanhSachMonHoc& dsmh, NodeCH& rootCH);
void ShowCauHoi(NodeCH& rootCH, string maMH, string tenMH, int n);
void ShowMHBangDiem(DSLOP dsLop, DanhSachMonHoc dsmh, NodeCH rootCH);
void VeGiaoDienLopBangDiem(int n, string maMH, string tenMH);
void VeGiaoDienSVBangDiem(int n, string maLop, string tenLop, string maMH, string tenMH);
//Huong dan
void HuongDanGiaoVien();
void HuongDanLop();
void HuongDanSV();
void HuongDan(int x, int y, int color, string noiDung);
void HuongDanBangDiem();
//xoa
void XoaNhapVaThongbao();
void XoaThongBaoDangNhap(int x, int y);
void XoaGiaoDien();
void XoaFull();
void XoaNoiDung();
void XoaHuongDan();
void XoaThongBao();
void XoaNoiDungDanhSach();
void XoaNoiDungCauHoi();
void XoaHoiThoat();
void XoaThongBaoNhapCauHoi();

//thong bao
void ThongBaoLoi(int x, int y, string noiDung);
void ThongBaoThanhCong(int x, int y, string noiDung);

//Hoi co chac chan ko
int HoiXoa(int x, int y, string noiDung, int z);
void XacNhan(int x, int y, string noiDung, int z);