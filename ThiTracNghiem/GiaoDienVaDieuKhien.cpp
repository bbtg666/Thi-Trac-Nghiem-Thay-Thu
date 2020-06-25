#include "GiaoDienVaDieuKhien.h"

void BatDau(DSLOP& dsLop, NodeCH& rootCH, DanhSachMonHoc& dsmh)
{
	ReadLop(dsLop);
	ReadCH(rootCH);
	ReadDSMH(dsmh);
	DangNhap(dsLop, rootCH, dsmh);
}
//Tieu de
void VeTieuDe()
{
	ifstream file("TIEUDE.txt");
	string temp;
	int line = 7;
	SetColor(YELLOW);
	while (!file.eof())
	{
		gotoxy(22, line++);
		getline(file, temp);
		cout << temp << endl;
	}
	SetColor(WHITE);
	file.close();
}
void VeTieuDeGiaoVien()
{
	ifstream file("TieuDeGiaoVien.txt");
	string temp;
	int line = 3;
	SetColor(YELLOW);
	while (!file.eof())
	{
		gotoxy(40, line++);
		getline(file, temp);
		cout << temp << endl;
	}
	SetColor(WHITE);
	file.close();
}

// Dung chung
void NormalBlue() {
	SetColor(BLUE);
	SetBGColor(BLACK);
}
void NormalWhite()
{
	SetColor(WHITE);
	SetBGColor(BLACK);
}
void HighLight() {
	SetColor(BLACK);
	SetBGColor(WHITE);
}
void VeKhungChung()
{
	VeHCN(0, 0, 152, 39, BLUE);
	VeHCN(0, 39, 152, 3, BLUE);
}
void VeHCN(int x, int y, int width, int height, int color)
{

	SetColor(color);
	gotoxy(x, y);
	cout << (char)(201);
	for (int i = x; i < x + width - 2; i++)
	{
		gotoxy(i + 1, y);
		cout << (char)(205);
		gotoxy(i + 1, y + height - 1);
		cout << (char)(205);
	}
	gotoxy(x + width - 1, y);
	cout << (char)(187) << endl;
	for (int i = y; i < y + height - 1; i++)
	{
		gotoxy(x, i + 1);
		cout << (char)(186);
		gotoxy(x + width - 1, i + 1);
		cout << (char)(186) << endl;
	}
	gotoxy(x, y + height - 1);
	cout << (char)(200);
	gotoxy(x + width - 1, y + height - 1);
	cout << (char)(188);
	SetColor(WHITE);
}
void SetMauChuXY(int x, int y, int color, string noidung)
{
	SetColor(color);
	gotoxy(x, y);
	cout << noidung;
	SetColor(WHITE);
}
int CapNhatMuiTen(int x, int y, int luaChon, int key)
{
	if (key == 72) {
		SetMauChuXY(x, y + (luaChon % 20), BLACK, "    ");
		luaChon--;
	}
	else {
		SetMauChuXY(x, y + (luaChon % 20), BLACK, "    ");
		luaChon++;
	}
	return luaChon;
}

float TinhDiem(DSCHTMH deThi, DiemThi dt)
{
	float soCauDung = 0;
	for (int i = 0; i < dt.n; i++)
	{
		if (dt.DSCHDTL[i].id == deThi.dsch[i].id)
		{
			if (dt.DSCHDTL[i].daChon == deThi.dsch[i].dapAn)
			{
				soCauDung++;
			}
		}
	}
	return (soCauDung / dt.n) * 10;
}

// Dong Ho dem nguoc
string DongHoDemNguoc(clock_t batdau, int soPhut)
{
	int conLai = soPhut * 60 - ((clock() - batdau) / CLOCKS_PER_SEC);
	int phut = conLai / 60;
	int giay = conLai % 60;
	string s_phut = to_string(phut);
	if (s_phut.length() == 1) s_phut = "0" + s_phut;
	string s_giay = to_string(giay);
	if (s_giay.length() == 1) s_giay = "0" + s_giay;
	return s_phut + ":" + s_giay;
}
bool HetGio(clock_t batdau, int soPhut)
{
	int daChayDuoc = (clock() - batdau) / CLOCKS_PER_SEC;
	if (daChayDuoc > (soPhut * 60)) return false;
	else return true;
}

// Dang nhap
void ManHinhDangNhap()
{
	VeTieuDe();
	VeHCN(0, 0, 148, 41, WHITE);
	VeHCN(46, 16, 48, 15, YELLOW);
	SetMauChuXY(63, 16, YELLOW, "  DANG NHAP  ");
	VeHCN(65, 27, 9, 3, BLUE);
	SetMauChuXY(67, 28, BLUE, "ENTER");
	VeHCN(52, 20, 37, 3, YELLOW);
	SetMauChuXY(52, 19, GREEN, "Tai Khoan:");
	VeHCN(52, 24, 37, 3, YELLOW);
	SetMauChuXY(52, 23, GREEN, "Mat Khau:");
}
int KiemTraUser(string taiKhoan, string matKhau, DSLOP dsLop)
{
	if (taiKhoan == "GV")
	{
		if (matKhau == "gv")
		{
			return 2;
		}
		else return 0;
	}
	for (int i = 0; i < dsLop.n; i++)
	{
		if (dsLop.LopArr[i].dssv == NULL) continue;
		NodeSV SV = SearchSV(dsLop.LopArr[i].dssv, taiKhoan);
		if (SV != NULL)
		{
			if (SV->sv.password == matKhau)	return 1;
		}
	}
	return 0;
}
void DangNhap(DSLOP& dsLop, NodeCH& rootCH, DanhSachMonHoc& dsmh)
{
	clrscr();
	int x = 54, y = 21;
	ManHinhDangNhap();
	char kytu;
	int flag, vitri = 0, checkUser;
	string taiKhoan, matKhau;
TaiKhoan:
	flag = NhapTaiKhoan(x, y, 20, taiKhoan);
	if (flag == 1)
	{
		vitri = 1;
		goto Password;
	}
	else if (taiKhoan.length() == 0)
	{
		checkUser = -2;
		goto DangNhap;
	}
	else if (matKhau.length() == 0)
	{
		vitri = 1;
		checkUser = -1;
		goto DangNhap;
	}
	else
	{
		checkUser = KiemTraUser(taiKhoan, matKhau, dsLop);
		goto DangNhap;
	}
Password:
	flag = NhapPassword(x, y + 4, 20, matKhau);
	if (flag == 1)
	{
		vitri = 0;
		goto TaiKhoan;
	}
	else if (taiKhoan.length() == 0)
	{
		vitri = 0;
		checkUser = -2;
		goto DangNhap;
	}
	else if (matKhau.length() == 0)
	{
		checkUser = -1;
		goto DangNhap;
	}
	else
	{
		checkUser = KiemTraUser(taiKhoan, matKhau, dsLop);
	}
DangNhap:
	if (checkUser == -2)
	{
		XoaThongBaoDangNhap(48, 32);
		ThongBaoLoi(53, 32, "Tai khoan khong duoc bo trong!!");
		goto TaiKhoan;
	}
	if (checkUser == -1)
	{
		XoaThongBaoDangNhap(48, 32);
		ThongBaoLoi(53, 32, "Mat khau khong duoc bo trong!!!");
		goto Password;
	}
	if (checkUser == 0)
	{
		XoaThongBaoDangNhap(48, 32);
		ThongBaoLoi(48, 32, "Tai khoan hoac mat khau khong ton tai!!!");
		if (vitri == 0)
		{
			goto TaiKhoan;
		}
		if (vitri == 1)
		{
			goto Password;
		}
	}
	if (checkUser == 1)
	{
		Thi(dsLop, rootCH, dsmh, taiKhoan);
	}
	if (checkUser == 2)
	{
		GiaoVien(dsLop, rootCH, dsmh);
	}
}

//THI
int VeNoiDungCauHoiThiVaChonCauTraLoi(CauHoi& cauHoi, clock_t batDauTimer, int soPhut, DiemThi& dt, int viTri)
{
	XoaNhapVaThongbao();
	int x = 96, y = 10;
	char kytu;
	int luaChon = 0, page = 1;
	VeHCN(x - 2, y - 2, 55, 26, BLUE);
	if (cauHoi.noiDung.length() <= 51) SetMauChuXY(x, y, WHITE, cauHoi.noiDung);
	else
	{
		int  dau = 0;
		cauHoi.noiDung += " ";
		for (int i = 0; i < cauHoi.noiDung.length() / 51 + 1; i++)
		{
			SetMauChuXY(x, y + i, WHITE, KiemTraNoiDungCauHoi(cauHoi.noiDung.substr(dau, 52)));
			dau += KiemTraNoiDungCauHoi(cauHoi.noiDung.substr(dau, 52)).length();
		}
	}
	x++;
	y += cauHoi.noiDung.length() / 51 + 2;
	string dapan[4] = { "A. " + cauHoi.A, "B. " + cauHoi.B, "C. " + cauHoi.C, "D. " + cauHoi.D };
	for (int i = 0; i < 4; i++)
	{
		SetMauChuXY(x, y + i, WHITE, dapan[i]);
	}
	HighLight();
	SetMauChuXY(x, y, BLACK, dapan[0]);
	NormalWhite();
	while (HetGio(batDauTimer, soPhut))
	{
		SetMauChuXY(136, 5, RED, DongHoDemNguoc(batDauTimer, soPhut));
		if (_kbhit())
		{
			kytu = _getch();
			if (kytu == 0) kytu = _getch();
			switch (kytu)
			{
			case UP:if (luaChon > 0)
			{
				NormalBlue();
				SetMauChuXY(x, y + luaChon, WHITE, dapan[luaChon]);
				luaChon--;
				HighLight();
				SetMauChuXY(x, y + luaChon, BLACK, dapan[luaChon]);
				NormalWhite();
			}
				   break;
			case DOWN:if (luaChon < 3)
			{
				NormalBlue();
				SetMauChuXY(x, y + luaChon, WHITE, dapan[luaChon]);
				luaChon++;
				HighLight();
				SetMauChuXY(x, y + luaChon, BLACK, dapan[luaChon]);
				NormalWhite();
			}
					 break;
			case ENTER:
			{
				dt.DSCHDTL[viTri].daChon = luaChon + 1;
				XoaNoiDungCauHoi();
				return 0;
			}
			case F2:
			{
				XoaNhapVaThongbao();
				if (HoiXoa(102, 17, "Ban co chac chan muon nop bai khong???", 11))
				{
					VeHCN(94, 8, 55, 26, BLUE);
					return 1;
				}

			}
			case ESC:
			{
				XoaNoiDungCauHoi();
				return 0;
			}
			}
		}
	}
	XoaNhapVaThongbao();
	XacNhan(108, 17, "Da het gio lam bai!!!", 8);
	return 1;
}
void VeDSMonHocThi(DanhSachMonHoc& dsmh, int page, NodeDT nodeDT)
{
	int y = 0;
	if (dsmh.n <= 0)
	{
		gotoxy(8, 12);
		cout << "Danh sach mon hoc trong!";
		return;
	}
	for (int i = MAXPAGE * (page - 1); i < page * MAXPAGE && i < dsmh.n; i++)
	{
		string diem = XuLyDiemThi(SearchDT(nodeDT, dsmh.dsNodeMH[i]->maMH));
		SetMauChuXY(10, 12 + y, WHITE, dsmh.dsNodeMH[i]->maMH + string(20 - dsmh.dsNodeMH[i]->maMH.length(), ' '));
		SetMauChuXY(33, 12 + y, WHITE, dsmh.dsNodeMH[i]->tenMH + string(30 - dsmh.dsNodeMH[i]->tenMH.length(), ' '));
		SetMauChuXY(75, 12 + y, WHITE, diem + string(8 - diem.length(), ' '));
		y++;
	}
	for (int i = y; i < MAXPAGE; i++)
	{
		SetMauChuXY(10, 12 + i, BLACK, string(20, ' '));
		SetMauChuXY(33, 12 + i, BLACK, string(30, ' '));
		SetMauChuXY(75, 12 + i, BLACK, string(8, ' '));
	}
	if (dsmh.n % MAXPAGE != 0)
	{
		gotoxy(72, 34); cout << "Trang: " << page << "/" << dsmh.n / MAXPAGE + 1;
	}
	else
	{
		gotoxy(72, 34); cout << "Trang: " << page << "/" << dsmh.n / MAXPAGE;
	}
}
void VeGiaoDienChonMonHocThi(string maLop, string tenLop, string ho, string ten, string maSV)
{
	XoaNoiDung();
	VeKhungChung();
	HuongDan(2, 40, BLUE, "UP,DOWN: LEN, XUONG | RIGHT, LEFT: SANG TRANG, LUI TRANG | ENTER: CHON MON HOC THI | ESC: DANG XUAT");
	VeHCN(3, 8, 87, 26, BLUE);
	SetMauChuXY(52, 2, YELLOW, "####### CHON MON HOC THI #######");
	SetMauChuXY(8, 5, GREEN, "MA LOP: " + maLop);
	SetMauChuXY(8, 6, GREEN, "TEN LOP: " + tenLop);
	SetMauChuXY(35, 5, GREEN, "MA SV: " + maSV);
	SetMauChuXY(35, 6, GREEN, "TEN SV: " + ho + " " + ten);
	SetMauChuXY(10, 10, WHITE, "MA MON HOC");
	SetMauChuXY(30, 10, WHITE, "||  TEN MON HOC");
	SetMauChuXY(73, 10, WHITE, "|| DIEM");
}
void LayThongTin(DSLOP dsLop, string maSV, int& viTriLop, NodeSV& nodeSV)
{
	for (int i = 0; i < dsLop.n; i++)
	{
		if (dsLop.LopArr[i].dssv == NULL) continue;
		NodeSV nodeSV1 = SearchSV(dsLop.LopArr[i].dssv, maSV);
		if (nodeSV1 != NULL)
		{
			viTriLop = i;
			nodeSV = nodeSV1;
			return;
		}
	}
}

void VeGiaoDienThi(string maMH, int soCau, int soPhut)
{
	XoaNoiDungDanhSach();
	XoaNhapVaThongbao();
	HuongDan(2, 40, BLUE, "UP,DOWN: LEN, XUONG | RIGHT, LEFT: SANG TRANG, LUI TRANG | ENTER: CHON CAU HOI DE TRA LOI | F2: NOP BAI | ESC: THOAT");
	SetMauChuXY(52, 2, BLACK, "####### CHON MON HOC THI #######");
	SetMauChuXY(65, 2, YELLOW, "####### BAT DAU THI #######");
	SetMauChuXY(8, 4, GREEN, "MA MON HOC: " + maMH);
	SetMauChuXY(72, 34, BLACK, "              ");
	SetMauChuXY(96, 5, GREEN, "SO CAU: " + to_string(soCau));
	SetMauChuXY(107, 5, GREEN, "THOI GIAN: " + to_string(soPhut) + " PHUT");
	SetMauChuXY(10, 10, WHITE, "NOI DUNG");
	SetMauChuXY(79, 10, WHITE, "|| CHON");
	VeHCN(94, 3, 35, 5, BLUE);
	VeHCN(94, 8, 55, 26, BLUE);
	VeHCN(129, 3, 20, 5, BLUE);
}

void VeDSCauHoiThi(DSCHTMH dsch, int page, DiemThi dt)
{
	int y = 0;
	if (dsch.n <= 0)
	{
		gotoxy(8, 12);
		cout << "Danh sach cau hoi trong!";
		return;
	}
	for (int i = MAXPAGE * (page - 1); i < page * MAXPAGE && i < dsch.n; i++)
	{
		SetMauChuXY(8, 12 + y, WHITE,
			"Cau " + to_string(i + 1) + ": "
			+ XuLyHienThiCauHoi(dsch.dsch[i].noiDung, 64)
			+ string(72 - to_string(i + 1).length() - 6 - XuLyHienThiCauHoi(dsch.dsch[i].noiDung, 64).length(), ' ')
			);
		SetMauChuXY(83, 12 + y, WHITE, XuLyDapAn(dt.DSCHDTL[i].daChon));
		y++;
	}
	for (int i = y; i < MAXPAGE; i++)
	{
		SetMauChuXY(8, 12 + i, BLACK, string(72, ' '));
		SetMauChuXY(83, 12 + i, WHITE, string(1, ' '));
	}
	if (dsch.n % MAXPAGE != 0)
	{
		gotoxy(72, 34); cout << "Trang: " << page << "/" << dsch.n / MAXPAGE + 1;
	}
	else
	{
		gotoxy(72, 34); cout << "Trang: " << page << "/" << dsch.n / MAXPAGE;
	}
}
void BatDauThi(NodeSV& SV, DSCHTMH deThi, string maMH, int soPhut, Lop lop)
{
	VeGiaoDienThi(maMH, deThi.n, soPhut);
	clock_t batDauTimer = clock();
	int page = 1, x = 4, y = 12, luaChon = 0;
	int flag = 0;
	char kytu;
	DiemThi dt;
	dt.n = 0;
	for (int i = 0; i < deThi.n; i++)
	{
		dt.DSCHDTL[i].id = deThi.dsch[i].id;
		dt.DSCHDTL[i].daChon = -1;
		dt.n++;
	}
	while (HetGio(batDauTimer, soPhut))
	{
		SetMauChuXY(136, 5, RED, DongHoDemNguoc(batDauTimer, soPhut));
		if (deThi.n > 0)
		{
			HighLight();
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, " -> ");
			NormalWhite();
		}
		VeDSCauHoiThi(deThi, page, dt);
		if (_kbhit())
		{
			kytu = _getch();
			if (kytu == 0) kytu = _getch();
			switch (kytu)
			{
			case UP:if (luaChon > 0 && luaChon > (page - 1) * MAXPAGE) luaChon = CapNhatMuiTen(x, y, luaChon, UP);
				break;
			case DOWN:if (luaChon + 1 < deThi.n && luaChon < (page * MAXPAGE) - 1) luaChon = CapNhatMuiTen(x, y, luaChon, DOWN);
				break;
			case LEFT: if (page > 1) {
				page--;
				SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
				luaChon = (page - 1) * MAXPAGE;
			}
					 break;
			case RIGHT: if (page * MAXPAGE < deThi.n)
			{
				page++;
				SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
				luaChon = (page - 1) * MAXPAGE;
			}
					  break;
			case ENTER:
			{
				flag = VeNoiDungCauHoiThiVaChonCauTraLoi(deThi.dsch[luaChon], batDauTimer, soPhut, dt, luaChon);
			}
			break;
			case F2:
			{
				XoaNhapVaThongbao();
				if (HoiXoa(102, 17, "Ban co chac chan muon nop bai khong???", 11))
				{
					VeHCN(94, 8, 55, 26, BLUE);
					break;
				}
				flag = 1;
			}
			break;
			case ESC:
			{
				XoaNhapVaThongbao();
				if (HoiXoa(105, 17, "Ban co chac chan thoat khong?", 8))
				{
					VeHCN(94, 8, 55, 26, BLUE);
					break;
				}
				for (int i = 0; i < dt.n; i++)
				{
					dt.DSCHDTL[i].daChon = -1;
				}
				dt.diem = 0.0;
				InsertDT(SV->sv.DT, maMH, dt);
				VeGiaoDienChonMonHocThi(lop.maLop, lop.tenLop, SV->sv.ho, SV->sv.ten, SV->sv.maSV);
				return;
			}
			}
			if (flag)
			{
				dt.diem = TinhDiem(deThi, dt);
				XoaNhapVaThongbao();
				XacNhan(108, 17, "DIEM CUA BAN LA: " + (dt.diem == 10 ? "10" : to_string(dt.diem).substr(0, 3)), 8);
				InsertDT(SV->sv.DT, maMH, dt);
				VeGiaoDienChonMonHocThi(lop.maLop, lop.tenLop, SV->sv.ho, SV->sv.ten, SV->sv.maSV);
				return;
			}
		}
	}
	dt.diem = TinhDiem(deThi, dt);
	XoaNhapVaThongbao();
	XacNhan(108, 17, "Da het gio lam bai!!!", 8);
	XoaNhapVaThongbao();
	XacNhan(108, 17, "DIEM CUA BAN LA: " + (dt.diem == 10 ? "10" : to_string(dt.diem).substr(0, 3)), 8);
	InsertDT(SV->sv.DT, maMH, dt);
	VeGiaoDienChonMonHocThi(lop.maLop, lop.tenLop, SV->sv.ho, SV->sv.ten, SV->sv.maSV);
}

void ChuanBiThi(NodeSV& SV, NodeCH rootCH, string maMH, Lop lop)
{
	int slch;
	int soPhut;
	DSCHTMH deThi;
	deThi.n = 0;
	if (!NhapSoCauHoi(slch)) return;
	else
	{
		if (!NhapSoPhutThi(soPhut)) return;
		int check = LayCauHoiThi(rootCH, maMH, slch, deThi);
		if (check == -1)
		{
			XoaNhapVaThongbao();
			ThongBaoLoi(98, 13, "Ngan hang cau thi khong du de thi mon nay!!!");
		}
		if (check == 0)
		{
			XoaNhapVaThongbao();
			ThongBaoLoi(95, 13, "Ngan hang cau hoi khong co cau hoi cho mon nay!!!");
		}
		if (check == 1)
		{
			BatDauThi(SV, deThi, maMH, soPhut, lop);
		}
	}
}

void Thi(DSLOP& dsLop, NodeCH rootCH, DanhSachMonHoc dsmh, string maSV)
{
	XoaFull();
	NodeSV nodeSV;
	int viTriLop;
	LayThongTin(dsLop, maSV, viTriLop, nodeSV);
	VeGiaoDienChonMonHocThi(dsLop.LopArr[viTriLop].maLop, dsLop.LopArr[viTriLop].tenLop, nodeSV->sv.ho, nodeSV->sv.ten, nodeSV->sv.maSV);
	int page = 1, x = 6, y = 12, luaChon = 0;
	char kytu;
	while (true)
	{
		if (dsmh.n > 0)
		{
			HighLight();
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, " -> ");
			NormalWhite();
		}
		VeDSMonHocThi(dsmh, page, nodeSV->sv.DT);
		kytu = _getch();
		if (kytu == 0) kytu = _getch();
		switch (kytu)
		{
		case UP:if (luaChon > 0 && luaChon > (page - 1) * MAXPAGE) luaChon = CapNhatMuiTen(x, y, luaChon, UP);
			break;
		case DOWN:if (luaChon + 1 < dsmh.n && luaChon < (page * MAXPAGE) - 1) luaChon = CapNhatMuiTen(x, y, luaChon, DOWN);
			break;
		case LEFT: if (page > 1) {
			page--;
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
			luaChon = (page - 1) * MAXPAGE;
		}
				 break;
		case RIGHT: if (page * MAXPAGE < dsmh.n)
		{
			page++;
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
			luaChon = (page - 1) * MAXPAGE;
		}
				  break;
		case ENTER:
		{
			if (dsmh.n == 0) continue;
			XoaNhapVaThongbao();
			if (SearchDT(nodeSV->sv.DT, dsmh.dsNodeMH[luaChon]->maMH) != NULL)
			{
				ThongBaoLoi(97, 14, "Ban da thi mon nay roi. Khong the thi tiep!!!");
				break;
			}
			if (HoiXoa(105, 14, "Ban co chac chan thi mon nay???", 8)) break;
			ChuanBiThi(nodeSV, rootCH, dsmh.dsNodeMH[luaChon]->maMH, dsLop.LopArr[viTriLop]);
		}
		break;
		case ESC:
		{
			XoaNhapVaThongbao();
			if (HoiXoa(105, 15, "Ban co that su mun thoat khong???", 8)) break;
			WriteLop(dsLop);
			BatDau(dsLop, rootCH, dsmh);
			DangNhap(dsLop, rootCH, dsmh);
		}
		}
	}
}

//Giao vien
int MenuGiaoVien(DSLOP& dsLop)
{
	XoaFull();
	VeTieuDeGiaoVien();
	HuongDanGiaoVien();
	string menu[3] = { "     LOP     ", "   MON HOC   ","  BANG DIEM  " };
	for (int i = 0; i < 3; i++)
	{
		SetMauChuXY(66, 22 + i * 5, BLUE, menu[i]);
	}
	VeKhungChung();
	VeHCN(65, 21, 15, 3, BLUE);
	VeHCN(65, 26, 15, 3, BLUE);
	VeHCN(65, 31, 15, 3, BLUE);
	Nocursortype(0);
	HighLight();
	SetMauChuXY(66, 22, BLACK, menu[0]);
	NormalBlue();
	int luaChon = 0;
	char kytu;
	while (true)
	{
		kytu = _getch();
		if (kytu == 224) kytu = _getch();
		switch (kytu)
		{
		case UP:if (luaChon > 0)
		{
			NormalBlue();
			SetMauChuXY(66, 22 + luaChon * 5, BLUE, menu[luaChon]);
			luaChon--;
			HighLight();
			SetMauChuXY(66, 22 + luaChon * 5, BLACK, menu[luaChon]);
			NormalBlue();
		}
			   break;
		case DOWN:if (luaChon < 2)
		{
			NormalBlue();
			SetMauChuXY(66, 22 + luaChon * 5, BLUE, menu[luaChon]);
			luaChon++;
			HighLight();
			SetMauChuXY(66, 22 + luaChon * 5, BLACK, menu[luaChon]);
			NormalBlue();
		}
				 break;
		case ESC: return -1;
		case ENTER: return luaChon;
		}
	}
}
void GiaoVien(DSLOP& dsLop, NodeCH& rootCH, DanhSachMonHoc& dsmh)
{
	while (true)
	{
		switch (MenuGiaoVien(dsLop))
		{
		case 0:
		{
			ShowLop(dsLop);
			WriteLop(dsLop);
			break;
		}
		case 1:
		{
			ShowMonHoc(dsmh, rootCH);
			WriteDSMH(dsmh);
			WriteCH(rootCH);
			break;
		}
		case 2:
		{
			ShowMHBangDiem(dsLop, dsmh, rootCH);
			break;
		}
		case -1:
		{
			XoaHoiThoat();
			if (HoiXoa(55, 20, "Ban co that su mun thoat khong???", 8))	break;
			BatDau(dsLop, rootCH, dsmh);
			DangNhap(dsLop, rootCH, dsmh);
		}
		}
	}
}

//Sinh vien
void VeGiaoDienSV(int n, string maLop, string tenLop)
{
	XoaNoiDung();
	HuongDanSV();
	VeHCN(3, 8, 87, 26, BLUE);
	SetMauChuXY(55, 2, YELLOW, "####### DANH SACH SINH VIEN #######");
	SetMauChuXY(8, 4, GREEN, "MA LOP: " + maLop);
	SetMauChuXY(8, 5, GREEN, "TEN LOP: " + tenLop);
	SetMauChuXY(8, 6, GREEN, "SI SO: " + to_string(n));
	SetMauChuXY(8, 10, WHITE, "Ma sinh vien");
	SetMauChuXY(30, 10, WHITE, "|| Ho");
	SetMauChuXY(55, 10, WHITE, "|| Ten");
	SetMauChuXY(73, 10, WHITE, "|| Phai");
}
void VeDSSinhVien(Lop lop, int slsv, int page)
{
	int y = 0;
	if (slsv <= 0)
	{
		gotoxy(8, 12);
		cout << "Danh sach sinh vien trong!" + string(55, ' ');
		gotoxy(72, 34); cout << "Trang: " << 0 << "/" << 0;
		return;
	}
	int dau = (page - 1) * MAXPAGE, cuoi = page * MAXPAGE - 1, i = 0;
	for (NodeSV p = lop.dssv; p != NULL; p = p->next)
	{

		if (i >= dau)
		{
			SetMauChuXY(8, 12 + y, WHITE, p->sv.maSV + string(20 - p->sv.maSV.length(), ' '));
			SetMauChuXY(33, 12 + y, WHITE, p->sv.ho + string(25 - p->sv.ho.length(), ' '));
			SetMauChuXY(58, 12 + y, WHITE, p->sv.ten + string(10 - p->sv.ten.length(), ' '));
			SetMauChuXY(76, 12 + y, WHITE, PhaiSV(p->sv.phai) + string(3 - PhaiSV(p->sv.phai).length(), ' '));
			y++;
		}
		if (i == cuoi || i == slsv - 1) break;;
		i++;
	}
	for (int i = y; i < MAXPAGE; i++)
	{
		SetMauChuXY(8, 12 + i, BLACK, string(20, ' '));
		SetMauChuXY(33, 12 + i, BLACK, string(25, ' '));
		SetMauChuXY(58, 12 + i, BLACK, string(10, ' '));
		SetMauChuXY(76, 12 + i, BLACK, string(3, ' '));
	}
	if (slsv % MAXPAGE != 0)
	{
		gotoxy(72, 34); cout << "Trang: " << page << "/" << slsv / MAXPAGE + 1;
	}
	else
	{
		gotoxy(72, 34); cout << "Trang: " << page << "/" << slsv / MAXPAGE;
	}
}
void ShowSinhVien(Lop& lop, DSLOP dsLop)
{
	XoaNoiDung();
	int slsv = DemSLSV(lop.dssv);
	VeGiaoDienSV(slsv, lop.maLop, lop.tenLop);
	int page = 1, x = 4, y = 12, luaChon = 0;
	char kytu;
	while (true)
	{
		slsv = DemSLSV(lop.dssv);
		if (slsv > 0)
		{
			HighLight();
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, " -> ");
			NormalWhite();
		}
		VeDSSinhVien(lop, slsv, page);
		kytu = _getch();
		if (kytu == 0) kytu = _getch();
		switch (kytu) {
		case UP:if (luaChon > 0 && luaChon > (page - 1) * MAXPAGE) luaChon = CapNhatMuiTen(x, y, luaChon, UP);
			break;
		case DOWN:if (luaChon + 1 < slsv && luaChon < (page * MAXPAGE) - 1) luaChon = CapNhatMuiTen(x, y, luaChon, DOWN);
			break;
		case LEFT: if (page > 1) {
			page--;
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
			luaChon = (page - 1) * MAXPAGE;
		}
				 break;
		case RIGHT: if (page * MAXPAGE < slsv)
		{
			page++;
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
			luaChon = (page - 1) * MAXPAGE;

		}
				  break;
		case ESC:
		{
			XoaNoiDung();
			VeGiaoDienLop(dsLop.n);
			return;
		}
		case INSERT:
		{
			XoaNhapVaThongbao();
			int a = NhapDuLieuSinhVien(lop.dssv, dsLop);
			if (a == -1) break;
			if (slsv == 0)
			{
				SetMauChuXY(4, 12, BLACK, string(40, ' '));
			}
			page = a / MAXPAGE + 1;
			SetMauChuXY(x, 12 + (luaChon % MAXPAGE), BLACK, "     ");
			luaChon = a;
		}
		break;
		case F2:
		{
			XoaNhapVaThongbao();
			NhapDuLieuSuaSinhVien(lop.dssv, luaChon);
		}
		break;
		case DEL:
		{
			if (DemSLSV(lop.dssv) == 0) break;
			XoaNhapVaThongbao();
			NodeSV nodeSV = SearchSVSTT(lop.dssv, luaChon);
			string tenSV = nodeSV->sv.ho + " " + nodeSV->sv.ten;
			if (HoiXoa(92, 18, "Ban co chac chan muon xoa " + tenSV + " khong???", 14)) break;
			int kt = DeleteSV(lop.dssv, nodeSV->sv);
			if (kt == 0)
			{
				XoaNhapVaThongbao();
				ThongBaoLoi(105, 18, "Khong con sinh vien de xoa!!");
			}
			if (kt == 1)
			{
				XoaNhapVaThongbao();
				ThongBaoThanhCong(100, 18, "Da xoa " + tenSV + " thanh cong!!");
				SetMauChuXY(x, 12 + (luaChon % MAXPAGE), BLACK, "    ");
				if (luaChon % MAXPAGE == 0 && luaChon / MAXPAGE == 0)
					break;
				luaChon--;
			}
		}
		break;
		}
	}
}

// ve lop
void VeDSLop(DSLOP dsLop, int page)
{
	int y = 0;
	if (dsLop.n <= 0)
	{
		gotoxy(8, 12);
		cout << "Danh sach lop hoc trong!";
		return;
	}
	for (int i = MAXPAGE * (page - 1); i < page * MAXPAGE && i < dsLop.n; i++)
	{
		SetMauChuXY(8, 12 + y, WHITE, dsLop.LopArr[i].maLop + string(20 - dsLop.LopArr[i].maLop.length(), ' '));
		SetMauChuXY(35, 12 + y, WHITE, dsLop.LopArr[i].tenLop + string(30 - dsLop.LopArr[i].tenLop.length(), ' '));
		SetMauChuXY(75, 12 + y, WHITE, to_string(DemSLSV(dsLop.LopArr[i].dssv)) + string(3 - to_string(DemSLSV(dsLop.LopArr[i].dssv)).length(), ' '));
		y++;
	}

	for (int i = y; i < MAXPAGE; i++)
	{
		SetMauChuXY(8, 12 + i, BLACK, string(20, ' '));
		SetMauChuXY(35, 12 + i, BLACK, string(30, ' '));
		SetMauChuXY(75, 12 + i, BLACK, string(3, ' '));
	}
	if (dsLop.n % MAXPAGE != 0)
	{
		gotoxy(72, 34); cout << "Trang: " << page << "/" << dsLop.n / MAXPAGE + 1;
	}
	else
	{
		gotoxy(72, 34); cout << "Trang: " << page << "/" << dsLop.n / MAXPAGE;
	}
}

void VeGiaoDienLop(int n)
{
	VeKhungChung();
	HuongDanLop();
	VeHCN(3, 8, 87, 26, BLUE);
	SetMauChuXY(55, 2, YELLOW, "####### DANH SACH CAC LOP #######");
	SetMauChuXY(8, 10, WHITE, "MA LOP");
	SetMauChuXY(32, 10, WHITE, "|| TEN LOP");
	SetMauChuXY(64, 10, WHITE, "|| SO LUONG SINH VIEN");
	SetMauChuXY(8, 6, GREEN, "SO LUONG LOP: " + to_string(n));
}

void ShowLop(DSLOP& dsLop)
{
	XoaFull();
	VeGiaoDienLop(dsLop.n);
	int page = 1, x = 4, y = 12, luaChon = 0;
	char kytu;
	while (true)
	{
		if (dsLop.n > 0)
		{
			HighLight();
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, " -> ");
			NormalWhite();
		}
		VeDSLop(dsLop, page);
		kytu = _getch();
		if (kytu == 0) kytu = _getch();
		switch (kytu) {
		case UP:if (luaChon > 0 && luaChon > (page - 1) * MAXPAGE) luaChon = CapNhatMuiTen(x, y, luaChon, UP);
			break;
		case DOWN:if (luaChon + 1 < dsLop.n && luaChon < (page * MAXPAGE) - 1) luaChon = CapNhatMuiTen(x, y, luaChon, DOWN);
			break;
		case LEFT: if (page > 1) {
			page--;
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
			luaChon = (page - 1) * MAXPAGE;
		}
				 break;
		case RIGHT: if (page * MAXPAGE < dsLop.n)
		{
			page++;
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
			luaChon = (page - 1) * MAXPAGE;

		}
				  break;
		case ESC:
		{
			return;
		}
		case F2:
		{
			XoaNhapVaThongbao();
			NhapLieuSuaLop(dsLop, luaChon);
		}
		break;
		case ENTER:
		{
			if (dsLop.n == 0)
			{
				continue;
			}
			ShowSinhVien(dsLop.LopArr[luaChon], dsLop);
			break;
		}
		case INSERT:
		{
			XoaNhapVaThongbao();
			int a = NhapDuLieuLop(dsLop);
			if (a == -1) break;
			page = a / MAXPAGE + 1;
			SetMauChuXY(x, 12 + (luaChon % MAXPAGE), BLACK, "     ");
			luaChon = a;
		}
		break;
		case DEL:
		{
			if (dsLop.n == 0) break;
			XoaNhapVaThongbao();
			string maLop = dsLop.LopArr[luaChon].maLop;
			if (HoiXoa(95, 18, "Ban co chac chan muon xoa " + maLop + " khong???", 14)) continue;
			int kt = DeleteLop(dsLop, dsLop.LopArr[luaChon]);
			if (kt == -1)
			{
				XoaNhapVaThongbao();
				ThongBaoLoi(105, 18, "Khong con lop de xoa!!");
			}
			if (kt == -2)
			{
				XoaNhapVaThongbao();
				ThongBaoLoi(98, 18, "Khong the xoa vi co sinh vien trong lop!!");
			}
			if (kt == 0)
			{
				XoaNhapVaThongbao();
				ThongBaoLoi(105, 18, "Lop khong ton tai!!!");
			}
			if (kt == 1)
			{
				XoaNhapVaThongbao();
				ThongBaoThanhCong(105, 18, "Da xoa " + maLop + " thanh cong!!");
				SetMauChuXY(x, 12 + (luaChon % MAXPAGE), BLACK, "    ");
				if (luaChon % MAXPAGE == 0 && luaChon / MAXPAGE == 0)
					break;
				luaChon--;
			}
		}
		break;
		}
	}
}

// Ve Mon hoc
void VeDSMonHoc(DanhSachMonHoc& dsmh, int page)
{
	int y = 0;
	if (dsmh.n <= 0)
	{
		gotoxy(8, 12);
		cout << "Danh sach mon hoc trong!";
		return;
	}
	for (int i = MAXPAGE * (page - 1); i < page * MAXPAGE && i < dsmh.n; i++)
	{
		SetMauChuXY(10, 12 + y, WHITE, dsmh.dsNodeMH[i]->maMH + string(20 - dsmh.dsNodeMH[i]->maMH.length(), ' '));
		SetMauChuXY(45, 12 + y, WHITE, dsmh.dsNodeMH[i]->tenMH + string(30 - dsmh.dsNodeMH[i]->tenMH.length(), ' '));
		y++;
	}
	for (int i = y; i < MAXPAGE; i++)
	{
		SetMauChuXY(10, 12 + i, BLACK, string(20, ' '));
		SetMauChuXY(45, 12 + i, BLACK, string(30, ' '));
	}
	if (dsmh.n % MAXPAGE != 0)
	{
		gotoxy(72, 34); cout << "Trang: " << page << "/" << dsmh.n / MAXPAGE + 1;
	}
	else
	{
		gotoxy(72, 34); cout << "Trang: " << page << "/" << dsmh.n / MAXPAGE;
	}
}
void VeGiaoDienMonHoc(int n)
{
	VeKhungChung();
	VeHCN(3, 8, 87, 26, BLUE);
	SetMauChuXY(52, 2, YELLOW, "####### DANH SACH CAC MON HOC #######");
	SetMauChuXY(8, 6, GREEN, "SO LUONG MON HOC: " + to_string(n));
	SetMauChuXY(10, 10, WHITE, "Ma mon hoc");
	SetMauChuXY(40, 10, WHITE, "||      Ten mon hoc");

}
void ShowMonHoc(DanhSachMonHoc& dsmh, NodeCH& rootCH)
{
	XoaFull();
	VeGiaoDienMonHoc(dsmh.n);
	HuongDanLop();
	int page = 1, x = 6, y = 12, luaChon = 0;
	char kytu;
	while (true)
	{
		if (dsmh.n > 0)
		{
			HighLight();
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, " -> ");
			NormalWhite();
		}
		VeDSMonHoc(dsmh, page);
		kytu = _getch();
		if (kytu == 0) kytu = _getch();
		switch (kytu)
		{
		case UP:if (luaChon > 0 && luaChon > (page - 1) * MAXPAGE) luaChon = CapNhatMuiTen(x, y, luaChon, UP);
			break;
		case DOWN:if (luaChon + 1 < dsmh.n && luaChon < (page * MAXPAGE) - 1) luaChon = CapNhatMuiTen(x, y, luaChon, DOWN);
			break;
		case LEFT: if (page > 1) {
			page--;
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
			luaChon = (page - 1) * MAXPAGE;
		}
				 break;
		case RIGHT: if (page * MAXPAGE < dsmh.n)
		{
			page++;
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
			luaChon = (page - 1) * MAXPAGE;
		}
				  break;
		case INSERT:
		{
			XoaNhapVaThongbao();
			int a = NhapDuLieuMonHoc(dsmh);
			if (a == -1) break;
			page = a / MAXPAGE + 1;
			SetMauChuXY(x, 12 + (luaChon % MAXPAGE), BLACK, "     ");
			luaChon = a;
		}
		break;
		case ESC:
		{
			return;
		}
		case F2:
		{
			XoaNhapVaThongbao();
			NhapLieuSuaMonHoc(dsmh, luaChon);
		}
		break;
		case ENTER:
		{
			if (dsmh.n == 0)
			{
				continue;
			}
			ShowCauHoi(rootCH, dsmh.dsNodeMH[luaChon]->maMH, dsmh.dsNodeMH[luaChon]->tenMH, dsmh.n);
			break;
		}
		case DEL:
		{
			XoaNhapVaThongbao();
			string maMH = dsmh.dsNodeMH[luaChon]->maMH;
			if (HoiXoa(95, 18, "Ban co chac chan muon xoa " + maMH + " khong???", 14)) continue;
			int kt = DeleteDSMH(dsmh, maMH);
			if (kt == -1)
			{
				XoaNhapVaThongbao();
				ThongBaoLoi(105, 18, "Khong con lop de xoa!!");
			}
			if (kt == -2)
			{
				XoaNhapVaThongbao();
				ThongBaoLoi(98, 18, "Khong the xoa vi co sinh vien trong lop!!");
			}
			if (kt == 0)
			{
				XoaNhapVaThongbao();
				ThongBaoLoi(105, 18, "Lop khong ton tai!!!");
			}
			if (kt == 1)
			{
				XoaNhapVaThongbao();
				ThongBaoThanhCong(105, 18, "Da xoa " + maMH + " thanh cong!!");
				SetMauChuXY(x, 12 + (luaChon % MAXPAGE), BLACK, "    ");
				if (dsmh.n == 0)
				{
					SetMauChuXY(4, 12, BLACK, string(40, ' '));
				}
				if (luaChon % MAXPAGE == 0 && luaChon / MAXPAGE == 0)
					break;
				luaChon--;
			}
		}
		}
	}
}

// cau hoi
string XuLyHienThiCauHoi(string noiDung, int length)
{
	if (noiDung.length() <= length)	return noiDung;
	else
	{
		length -= 3;
		return noiDung.substr(0, length) + "...";
	}
}
string XuLyDapAn(int da)
{
	if (da == 1)
		return "A";
	if (da == 2)
		return "B";
	if (da == 3)
		return "C";
	if (da == 4)
		return "D";
	else
		return "?";
}
void VeGiaoDienCauHoi(string maMH, string tenMH, int n)
{
	XoaNoiDung();
	VeKhungChung();
	HuongDanLop();
	VeHCN(3, 8, 87, 26, BLUE);
	SetMauChuXY(55, 2, YELLOW, "####### DANH SACH CAU HOI #######");
	SetMauChuXY(8, 4, GREEN, "MA MON HOC: " + maMH);
	SetMauChuXY(8, 5, GREEN, "TEN MON HOC: " + tenMH);
	SetMauChuXY(8, 6, GREEN, "SO LUONG CAU HOI: " + to_string(n));
	SetMauChuXY(8, 10, WHITE, "ID");
	SetMauChuXY(12, 10, WHITE, "|| NOI DUNG");
	SetMauChuXY(78, 10, WHITE, "|| DAP AN");
}
void VeDSCauHoi(DSCHTMH dsch, int page)
{
	int y = 0;
	if (dsch.n <= 0)
	{
		gotoxy(8, 12);
		NormalWhite();
		cout << "Danh sach cau hoi trong!";
		return;
	}
	for (int i = MAXPAGE * (page - 1); i < page * MAXPAGE && i < dsch.n; i++)
	{
		SetMauChuXY(8, 12 + y, WHITE, to_string(dsch.dsch[i].id) + string(3 - to_string(dsch.dsch[i].id).length(), ' '));
		SetMauChuXY(15, 12 + y, WHITE, XuLyHienThiCauHoi(dsch.dsch[i].noiDung, 64) + string(64 - XuLyHienThiCauHoi(dsch.dsch[i].noiDung, 64).length(), ' '));
		SetMauChuXY(83, 12 + y, WHITE, XuLyDapAn(dsch.dsch[i].dapAn));
		y++;
	}
	for (int i = y; i < MAXPAGE; i++)
	{
		SetMauChuXY(8, 12 + i, BLACK, string(3, ' '));
		SetMauChuXY(15, 12 + i, BLACK, string(64, ' '));
		SetMauChuXY(83, 12 + i, WHITE, string(1, ' '));
	}
	if (dsch.n % MAXPAGE != 0)
	{
		gotoxy(72, 34); cout << "Trang: " << page << "/" << dsch.n / MAXPAGE + 1;
	}
	else
	{
		gotoxy(72, 34); cout << "Trang: " << page << "/" << dsch.n / MAXPAGE;
	}
}
string KiemTraNoiDungCauHoi(string ndch)
{
	if (ndch[0] == ' ') ndch.erase(0, 1);
	int n = ndch.length();
	if (ndch[n - 1] == ' ' || ndch[n - 2] == ' ') return ndch.erase(n - 1, 1);
	else
	{
		for (int i = n; i > 0; i--)
		{
			if (ndch[i] == ' ')
			{
				ndch.erase(i + 1, n - i);
				break;
			}
		}
		return ndch;
	}
}
void VeNoiDungCauHoi(CauHoi cauHoi)
{
	XoaNhapVaThongbao();
	int x = 96, y = 10;
	VeHCN(x - 2, y - 2, 55, 26, BLUE);
	if (cauHoi.noiDung.length() <= 51) SetMauChuXY(x, y, WHITE, cauHoi.noiDung);
	else
	{
		int  dau = 0;
		cauHoi.noiDung += " ";
		for (int i = 0; i < cauHoi.noiDung.length() / 51 + 1; i++)
		{
			SetMauChuXY(x, y + i, WHITE, KiemTraNoiDungCauHoi(cauHoi.noiDung.substr(dau, 52)));
			dau += KiemTraNoiDungCauHoi(cauHoi.noiDung.substr(dau, 52)).length();
		}
	}
	y += cauHoi.noiDung.length() / 51 + 1;
	string dapan[4] = { "A. " + cauHoi.A, "B. " + cauHoi.B, "C. " + cauHoi.C, "D. " + cauHoi.D };
	for (int i = 1; i <= 4; i++)
	{
		if (i == cauHoi.dapAn) SetMauChuXY(x + 1, y + i, BLUE, dapan[i - 1]);
		else SetMauChuXY(x + 1, y + i, WHITE, dapan[i - 1]);
	}
}
void ShowCauHoi(NodeCH& rootCH, string maMH, string tenMH, int n)
{
	XoaNoiDung();
	DSCHTMH dsch;
	dsch.n = 0;
	BienDoiThanhNodeCHTheoMonHoc(rootCH, maMH, dsch);
	VeGiaoDienCauHoi(maMH, tenMH, dsch.n);
	int page = 1, x = 4, y = 12, luaChon = 0;
	char kytu;
	while (true)
	{
		if (dsch.n > 0)
		{
			HighLight();
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, " -> ");
			NormalWhite();
		}
		VeDSCauHoi(dsch, page);
		kytu = _getch();
		if (kytu == 0) kytu = _getch();
		switch (kytu)
		{
		case UP:if (luaChon > 0 && luaChon > (page - 1) * MAXPAGE) luaChon = CapNhatMuiTen(x, y, luaChon, UP);
			break;
		case DOWN:if (luaChon + 1 < dsch.n && luaChon < (page * MAXPAGE) - 1) luaChon = CapNhatMuiTen(x, y, luaChon, DOWN);
			break;
		case LEFT: if (page > 1) {
			page--;
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
			luaChon = (page - 1) * MAXPAGE;
		}
				 break;
		case RIGHT: if (page * MAXPAGE < dsch.n)
		{
			page++;
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
			luaChon = (page - 1) * MAXPAGE;
		}
				  break;
		case ENTER:
		{
			if (dsch.n <= 0) break;
			VeNoiDungCauHoi(dsch.dsch[luaChon]);

		}
		break;
		case F2:
		{
			XoaNhapVaThongbao();
			NhapDuLieuSuaCauHoi(rootCH, dsch, luaChon);
		}
		break;
		case DEL:
		{

		}
		break;
		case INSERT:
		{
			XoaNhapVaThongbao();
			int a = NhapDuLieuCauHoi(rootCH, dsch, maMH);
			if (a == -1) break;
			if (dsch.n == 0)
			{
				SetMauChuXY(4, 12, BLACK, string(40, ' '));
				NormalWhite();
			}
			dsch.n++;
			page = a / MAXPAGE + 1;
			SetMauChuXY(x, 12 + (luaChon % MAXPAGE), BLACK, "     ");
			luaChon = a;
		}
		break;
		case ESC:
		{
			XoaNoiDung();
			VeGiaoDienMonHoc(n);
			NormalWhite();
			return;
		}
		}
	}
}

// Bang diem
void VeNoiDungCauHoiThiBangDiem(CauHoi cauHoi, int daChon)
{
	XoaNhapVaThongbao();
	int x = 96, y = 10;
	VeHCN(x - 2, y - 2, 55, 26, BLUE);
	if (cauHoi.noiDung.length() <= 51) SetMauChuXY(x, y, WHITE, cauHoi.noiDung);
	else
	{
		int  dau = 0;
		cauHoi.noiDung += " ";
		for (int i = 0; i < cauHoi.noiDung.length() / 51 + 1; i++)
		{
			SetMauChuXY(x, y + i, WHITE, KiemTraNoiDungCauHoi(cauHoi.noiDung.substr(dau, 52)));
			dau += KiemTraNoiDungCauHoi(cauHoi.noiDung.substr(dau, 52)).length();
		}
	}
	y += cauHoi.noiDung.length() / 51 + 1;

	string dapan[4] = { "A. " + cauHoi.A, "B. " + cauHoi.B, "C. " + cauHoi.C, "D. " + cauHoi.D };
	for (int i = 1; i <= 4; i++)
	{
		string Chon = "";
		if (daChon == i) Chon += "   X";
		if (i == cauHoi.dapAn) SetMauChuXY(x + 1, y + i, BLUE, dapan[i - 1] + Chon);
		else SetMauChuXY(x + 1, y + i, WHITE, dapan[i - 1] + Chon);
	}
}
string DungSai(int dapAn, int daChon)
{
	if (dapAn == daChon) return "Dung";
	else return "Sai";
}
void VeDSCauHoiDaThi(NodeCH rootCH, NodeDT nodeDT, int page)
{
	int y = 0;
	if (nodeDT == NULL || nodeDT->diemThi.n <= 0)
	{
		gotoxy(8, 12);
		cout << "Danh sach cau hoi da thi trong!";
		return;
	}
	DiemThi dt = nodeDT->diemThi;
	for (int i = MAXPAGE * (page - 1); i < page * MAXPAGE && i < dt.n; i++)
	{
		SetMauChuXY(8, 12 + y, WHITE, to_string(i + 1) + string(3 - to_string(i + 1).length(), ' '));
		NodeCH ch = SearchCH(rootCH, dt.DSCHDTL[i].id);
		SetMauChuXY(14, 12 + y, WHITE, XuLyHienThiCauHoi(ch->cauHoi.noiDung, 55) + string(55 - XuLyHienThiCauHoi(ch->cauHoi.noiDung, 55).length(), ' '));
		SetMauChuXY(74, 12 + y, WHITE, XuLyDapAn(dt.DSCHDTL[i].daChon));
		SetMauChuXY(81, 12 + y, WHITE, DungSai(ch->cauHoi.dapAn, dt.DSCHDTL[i].daChon) + string(4 - DungSai(ch->cauHoi.dapAn, dt.DSCHDTL[i].daChon).length(), ' '));
		y++;
	}
	for (int i = y; i < MAXPAGE; i++)
	{
		SetMauChuXY(8, 12 + i, BLACK, string(3, ' '));
		SetMauChuXY(14, 12 + i, BLACK, string(55, ' '));
		SetMauChuXY(74, 12 + i, WHITE, string(1, ' '));
		SetMauChuXY(81, 12 + i, WHITE, string(4, ' '));
	}
	if (dt.n % MAXPAGE != 0)
	{
		gotoxy(72, 34); cout << "Trang: " << page << "/" << dt.n / MAXPAGE + 1;
	}
	else
	{
		gotoxy(72, 34); cout << "Trang: " << page << "/" << dt.n / MAXPAGE;
	}
}
void VeGiaoDienCauHoiDaThi(SinhVien sv, NodeDT node, string maMH, string tenMH, string maLop, string tenLop)
{
	XoaNoiDung();
	HuongDanBangDiem();
	int n;
	if (sv.DT == NULL) n = 0;
	else n = sv.DT->diemThi.n;
	VeHCN(3, 8, 87, 26, BLUE);
	SetMauChuXY(50, 2, YELLOW, "####### DANH SACH CAU HOI DA THI #######");
	SetMauChuXY(8, 3, GREEN, "MA MON HOC: " + maMH);
	SetMauChuXY(8, 4, GREEN, "TEN MON HOC: " + tenMH);
	SetMauChuXY(8, 5, GREEN, "MA LOP: " + maLop);
	SetMauChuXY(35, 5, GREEN, "TEN LOP: " + tenLop);
	SetMauChuXY(8, 6, GREEN, "MA SV: " + sv.maSV);
	SetMauChuXY(35, 6, GREEN, "TEN SV: " + sv.ho + " " + sv.ten);
	SetMauChuXY(8, 7, GREEN, "SO CAU HOI: " + to_string(n));
	SetMauChuXY(35, 7, GREEN, "DIEM: " + XuLyDiemThi(node));
	SetMauChuXY(8, 10, WHITE, "STT");
	SetMauChuXY(12, 10, WHITE, "|| NOI DUNG");
	SetMauChuXY(70, 10, WHITE, "|| CHON");
	SetMauChuXY(79, 10, WHITE, "|| KQ");
}
void ShowCauHoiDaThi(NodeCH rootCH, SinhVien sv, string maMH, string tenMH, Lop lop, int n)
{
	NodeDT node = SearchDT(sv.DT, maMH);
	VeGiaoDienCauHoiDaThi(sv, node, maMH, tenMH, lop.maLop, lop.tenLop);
	int page = 1, x = 4, y = 12, luaChon = 0;
	char kytu;
	while (true)
	{
		if (node != NULL && node->diemThi.n > 0)
		{
			HighLight();
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, " -> ");
			NormalWhite();
		}
		VeDSCauHoiDaThi(rootCH, node, page);
		kytu = _getch();
		if (kytu == 0) kytu = _getch();
		switch (kytu) {
		case UP:if (luaChon > 0 && luaChon > (page - 1) * MAXPAGE) luaChon = CapNhatMuiTen(x, y, luaChon, UP);
			break;
		case DOWN:if (luaChon + 1 < node->diemThi.n && luaChon < (page * MAXPAGE) - 1) luaChon = CapNhatMuiTen(x, y, luaChon, DOWN);
			break;
		case LEFT: if (page > 1) {
			page--;
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
			luaChon = (page - 1) * MAXPAGE;
		}
				 break;
		case RIGHT: if (page * MAXPAGE < node->diemThi.n)
		{
			page++;
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
			luaChon = (page - 1) * MAXPAGE;
		}
				  break;
		case ESC:
		{
			XoaNoiDung();
			VeGiaoDienSVBangDiem(n, lop.maLop, lop.tenLop, maMH, tenMH);
			return;
		}
		case ENTER:
		{
			if (node == NULL || node->diemThi.n <= 0) break;
			VeNoiDungCauHoiThiBangDiem(SearchCH(rootCH, node->diemThi.DSCHDTL[luaChon].id)->cauHoi, node->diemThi.DSCHDTL[luaChon].daChon);
		}
		break;
		}
	}
}
void VeGiaoDienSVBangDiem(int n, string maLop, string tenLop, string maMH, string tenMH)
{
	XoaNoiDung();
	HuongDanBangDiem();
	VeHCN(3, 8, 87, 26, BLUE);
	SetMauChuXY(55, 2, YELLOW, "####### DANH SACH SINH VIEN #######");
	SetMauChuXY(8, 3, GREEN, "MA MON HOC: " + maMH);
	SetMauChuXY(8, 4, GREEN, "TEN MON HOC: " + tenMH);
	SetMauChuXY(8, 5, GREEN, "MA LOP: " + maLop);
	SetMauChuXY(8, 6, GREEN, "TEN LOP: " + tenLop);
	SetMauChuXY(8, 7, GREEN, "SI SO: " + to_string(n));
	SetMauChuXY(8, 10, WHITE, "MA SINH VIEN");
	SetMauChuXY(30, 10, WHITE, "|| HO VA TEN");
	SetMauChuXY(73, 10, WHITE, "|| DIEM");
}
string XuLyDiemThi(NodeDT dt)
{
	if (dt == NULL) return "Chua thi";
	else if (dt->diemThi.diem == 10) return to_string(dt->diemThi.diem).substr(0, 2);
	else return to_string(dt->diemThi.diem).substr(0, 3);
}
void VeDSSinhVienBangDiem(Lop lop, int slsv, int page, string maMH)
{
	int y = 0;
	if (slsv <= 0)
	{
		gotoxy(8, 12);
		cout << "Danh sach sinh vien trong!";
		gotoxy(72, 34); cout << "Trang: " << 0 << "/" << 0;
		return;
	}
	int dau = (page - 1) * MAXPAGE, cuoi = page * MAXPAGE - 1, i = 0;
	for (NodeSV p = lop.dssv; p != NULL; p = p->next)
	{

		if (i >= dau)
		{
			NodeDT dt = SearchDT(p->sv.DT, maMH);
			string diem = XuLyDiemThi(dt);
			SetMauChuXY(8, 12 + y, WHITE, p->sv.maSV + string(20 - p->sv.maSV.length(), ' '));
			SetMauChuXY(33, 12 + y, WHITE, p->sv.ho + " " + p->sv.ten + string(30 - p->sv.ho.length() - p->sv.ten.length() - 1, ' '));
			SetMauChuXY(76, 12 + y, WHITE, diem + string(8 - diem.length(), ' '));
			y++;
		}
		if (i == cuoi || i == slsv - 1) break;;
		i++;
	}
	for (int i = y; i < MAXPAGE; i++)
	{
		SetMauChuXY(8, 12 + i, BLACK, string(20, ' '));
		SetMauChuXY(33, 12 + i, BLACK, string(30, ' '));
		SetMauChuXY(76, 12 + i, BLACK, string(8, ' '));
	}
	if (slsv % MAXPAGE != 0)
	{
		gotoxy(72, 34); cout << "Trang: " << page << "/" << slsv / MAXPAGE + 1;
	}
	else
	{
		gotoxy(72, 34); cout << "Trang: " << page << "/" << slsv / MAXPAGE;
	}
}
void ShowSVBangDiem(DSLOP dsLop, NodeCH rootCH, Lop lop, string maMH, string tenMH)
{
	int slsv = DemSLSV(lop.dssv);
	VeGiaoDienSVBangDiem(slsv, lop.maLop, lop.tenLop, maMH, tenMH);
	int page = 1, x = 4, y = 12, luaChon = 0;
	char kytu;
	while (true)
	{
		slsv = DemSLSV(lop.dssv);
		if (slsv > 0)
		{
			HighLight();
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, " -> ");
			NormalWhite();
		}
		VeDSSinhVienBangDiem(lop, slsv, page, maMH);
		kytu = _getch();
		if (kytu == 0) kytu = _getch();
		switch (kytu) {
		case UP:if (luaChon > 0 && luaChon > (page - 1) * MAXPAGE) luaChon = CapNhatMuiTen(x, y, luaChon, UP);
			break;
		case DOWN:if (luaChon + 1 < slsv && luaChon < (page * MAXPAGE) - 1) luaChon = CapNhatMuiTen(x, y, luaChon, DOWN);
			break;
		case LEFT: if (page > 1) {
			page--;
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
			luaChon = (page - 1) * MAXPAGE;
		}
				 break;
		case RIGHT: if (page * MAXPAGE < slsv)
		{
			page++;
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
			luaChon = (page - 1) * MAXPAGE;
		}
				  break;
		case ENTER:
		{
			if (slsv <= 0) break;
			ShowCauHoiDaThi(rootCH, SearchSVSTT(lop.dssv, luaChon)->sv, maMH, tenMH, lop, slsv);
		}
		break;
		case ESC:
		{
			XoaNoiDung();
			VeGiaoDienLopBangDiem(dsLop.n, maMH, tenMH);
			return;
		}
		}
	}
}
void VeDSLopBangDiem(DSLOP dsLop, int page, string maMH)
{
	int y = 0;
	if (dsLop.n <= 0)
	{
		gotoxy(8, 12);
		cout << "Danh sach lop hoc trong!";
		return;
	}
	for (int i = MAXPAGE * (page - 1); i < page * MAXPAGE && i < dsLop.n; i++)
	{
		int daThi = DemSLSVDaThiMonHoc(dsLop.LopArr[i].dssv, maMH);
		SetMauChuXY(8, 12 + y, WHITE, dsLop.LopArr[i].maLop + string(20 - dsLop.LopArr[i].maLop.length(), ' '));
		SetMauChuXY(35, 12 + y, WHITE, dsLop.LopArr[i].tenLop + string(30 - dsLop.LopArr[i].tenLop.length(), ' '));
		SetMauChuXY(70, 12 + y, WHITE, to_string(DemSLSV(dsLop.LopArr[i].dssv)) + string(3 - to_string(DemSLSV(dsLop.LopArr[i].dssv)).length(), ' '));
		SetMauChuXY(82, 12 + y, WHITE, to_string(daThi) + string(3 - to_string(daThi).length(), ' '));
		y++;
	}

	for (int i = y; i < MAXPAGE; i++)
	{
		SetMauChuXY(8, 12 + i, BLACK, string(20, ' '));
		SetMauChuXY(35, 12 + i, BLACK, string(30, ' '));
		SetMauChuXY(70, 12 + i, BLACK, string(3, ' '));
		SetMauChuXY(82, 12 + i, BLACK, string(3, ' '));
	}
	if (dsLop.n % MAXPAGE != 0)
	{
		gotoxy(72, 34); cout << "Trang: " << page << "/" << dsLop.n / MAXPAGE + 1;
	}
	else
	{
		gotoxy(72, 34); cout << "Trang: " << page << "/" << dsLop.n / MAXPAGE;
	}
}

void VeGiaoDienLopBangDiem(int n, string maMH, string tenMH)
{
	XoaNoiDung();
	VeKhungChung();
	HuongDanBangDiem();
	VeHCN(3, 8, 87, 26, BLUE);
	SetMauChuXY(55, 2, YELLOW, "####### DANH SACH CAC LOP #######");
	SetMauChuXY(8, 4, GREEN, "MA MON HOC: " + maMH);
	SetMauChuXY(8, 5, GREEN, "TEN MON HOC: " + tenMH);
	SetMauChuXY(8, 6, GREEN, "SO LUONG LOP: " + to_string(n));
	SetMauChuXY(8, 10, WHITE, "MA LOP");
	SetMauChuXY(32, 10, WHITE, "|| TEN LOP");
	SetMauChuXY(66, 10, WHITE, "|| SLSV");
	SetMauChuXY(77, 10, WHITE, "|| DA THI");

}
void ShowLopBangDiem(DSLOP dsLop, NodeCH rootCH, int n, MonHoc* mh)
{
	VeGiaoDienLopBangDiem(dsLop.n, mh->maMH, mh->tenMH);
	int page = 1, x = 4, y = 12, luaChon = 0;
	char kytu;
	while (true)
	{
		if (dsLop.n > 0)
		{
			HighLight();
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, " -> ");
			NormalWhite();
		}
		VeDSLopBangDiem(dsLop, page, mh->maMH);
		kytu = _getch();
		if (kytu == 0) kytu = _getch();
		switch (kytu) {
		case UP:if (luaChon > 0 && luaChon > (page - 1) * MAXPAGE) luaChon = CapNhatMuiTen(x, y, luaChon, UP);
			break;
		case DOWN:if (luaChon + 1 < dsLop.n && luaChon < (page * MAXPAGE) - 1) luaChon = CapNhatMuiTen(x, y, luaChon, DOWN);
			break;
		case LEFT: if (page > 1) {
			page--;
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
			luaChon = (page - 1) * MAXPAGE;
		}
				 break;
		case RIGHT: if (page * MAXPAGE < dsLop.n)
		{
			page++;
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
			luaChon = (page - 1) * MAXPAGE;
		}
				  break;
		case ESC:
		{
			XoaNoiDung();
			VeGiaoDienMonHoc(n);
			HuongDanBangDiem();
			return;
		}
		case ENTER:
		{
			if (dsLop.n == 0)
			{
				continue;
			}
			ShowSVBangDiem(dsLop, rootCH, dsLop.LopArr[luaChon], mh->maMH, mh->tenMH);
			break;
		}
		}
	}
}
void ShowMHBangDiem(DSLOP dsLop, DanhSachMonHoc dsmh, NodeCH rootCH)
{
	XoaFull();
	VeGiaoDienMonHoc(dsmh.n);
	HuongDanBangDiem();
	int page = 1, x = 6, y = 12, luaChon = 0;
	char kytu;
	while (true)
	{
		if (dsmh.n > 0)
		{
			HighLight();
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, " -> ");
			NormalWhite();
		}
		VeDSMonHoc(dsmh, page);
		kytu = _getch();
		if (kytu == 0) kytu = _getch();
		switch (kytu)
		{
		case UP:if (luaChon > 0 && luaChon > (page - 1) * MAXPAGE) luaChon = CapNhatMuiTen(x, y, luaChon, UP);
			break;
		case DOWN:if (luaChon + 1 < dsmh.n && luaChon < (page * MAXPAGE) - 1) luaChon = CapNhatMuiTen(x, y, luaChon, DOWN);
			break;
		case LEFT: if (page > 1) {
			page--;
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
			luaChon = (page - 1) * MAXPAGE;
		}
				 break;
		case RIGHT: if (page * MAXPAGE < dsmh.n)
		{
			page++;
			SetMauChuXY(x, y + (luaChon % MAXPAGE), BLACK, "    ");
			luaChon = (page - 1) * MAXPAGE;
		}
				  break;
		case ENTER:
		{
			if (dsmh.n == 0)
			{
				continue;
			}
			ShowLopBangDiem(dsLop, rootCH, dsmh.n, dsmh.dsNodeMH[luaChon]);
			break;
		}
		case ESC:
		{
			return;
		}
		}
	}
}

// Huong dan
void HuongDanGiaoVien()
{
	gotoxy(10, 40);
	SetColor(BLUE);
	cout << "UP,DOWN: LEN XUONG | ENTER: CHON | ESC: DANG XUAT";
}

void HuongDanLop()
{
	gotoxy(2, 40);
	SetColor(BLUE);
	cout << "UP,DOWN: LEN,XUONG | RIGHT,LEFT: SANG TRANG, LUI TRANG | INSERT: THEM | DELETE: XOA | F2: SUA | ENTER: CHON | ESC: THOAT";
}
void HuongDanSV()
{
	gotoxy(2, 40);
	SetColor(BLUE);
	cout << "UP,DOWN: LEN,XUONG | RIGHT,LEFT: SANG TRANG, LUI TRANG | INSERT: THEM | F2: SUA | DELETE: XOA | ESC: THOAT              ";
}

void HuongDanBangDiem()
{
	gotoxy(2, 40);
	SetColor(BLUE);
	cout << "UP,DOWN: LEN,XUONG | RIGHT,LEFT: SANG TRANG, LUI TRANG | ENTER: CHON | ESC: THOAT                             ";
}

void HuongDan(int x, int y, int color, string noiDung)
{
	gotoxy(x, y);
	SetColor(color);
	cout << noiDung;
}

//Xoa giao dien va thong bao
void XoaGiaoDien()
{
	for (int i = 0; i < 37; i++)
	{
		gotoxy(1, 1 + i);
		cout << string(150, ' ');
	}
	gotoxy(1, 40);
	cout << string(150, ' ');
}
void XoaNhapVaThongbao()
{
	int x = 90, y = 8;
	for (int i = 0; i < 26; i++)
	{
		gotoxy(x, y + i);
		cout << string(60, ' ');
	}
}
void XoaThongBao()
{
	int x = 95, y = 20;

	for (int i = 0; i < 5; i++)
	{
		gotoxy(x, y + i);
		cout << string(55, ' ');
	}
}
void XoaThongBaoDangNhap(int x, int y)
{
	for (int i = 0; i < 6; i++)
	{
		gotoxy(x, y + i);
		cout << string(40, ' ');
	}
}
void XoaFull()
{
	for (int i = 0; i < 42; i++)
	{
		gotoxy(0, i);
		cout << string(152, ' ');
	}
}
void XoaNoiDung()
{
	for (int i = 0; i < 7; i++)
	{
		gotoxy(1, 1 + i);
		cout << string(150, ' ');
	}
	XoaNhapVaThongbao();
	for (int i = 0; i < 23; i++)
	{
		gotoxy(4, 10 + i);
		cout << string(84, ' ');
	}
}
void XoaThongBaoNhapCauHoi()
{
	for (int i = 0; i < 5; i++)
	{
		gotoxy(100, 27 + i);
		cout << string(50, ' ');
	}
}
void XoaHuongDan()
{
	gotoxy(1, 40);
	cout << string(150, ' ');
}
void XoaNoiDungDanhSach()
{
	for (int i = 0; i < 23; i++)
	{
		gotoxy(4, 10 + i);
		cout << string(84, ' ');
	}
}

void XoaNoiDungCauHoi()
{
	for (int i = 0; i < 23; i++)
	{
		gotoxy(95, 10 + i);
		cout << string(53, ' ');
	}
}
void XoaHoiThoat()
{
	for (int i = 0; i < 5; i++)
	{
		gotoxy(55, 20 + i);
		cout << string(34, ' ');
	}
}
//Thong bao
void ThongBaoLoi(int x, int y, string noiDung)
{
	VeHCN(x, y, noiDung.length() + 4, 5, RED);
	SetMauChuXY(x + 2, y + 2, RED, noiDung);
}
void ThongBaoThanhCong(int x, int y, string noiDung)
{
	VeHCN(x, y, noiDung.length() + 4, 5, YELLOW);
	SetMauChuXY(x + 2, y + 2, YELLOW, noiDung);
}
//Hoi co chac chan ko
int HoiXoa(int x, int y, string noiDung, int z)
{

	VeHCN(x, y, noiDung.length() + 2, 5, YELLOW);
	SetMauChuXY(x + 1, y + 1, YELLOW, noiDung);
	x += z;
	y += 3;
	string menu[2] = { "Yes", "No" };
	for (int i = 1; i < 2; i++)
	{
		SetMauChuXY(x + i * 15, y, WHITE, menu[i]);
	}
	HighLight();
	SetMauChuXY(x, y, BLACK, menu[0]);
	NormalBlue();
	int luaChon = 0;
	char kytu;
	while (true)
	{
		kytu = _getch();
		if (kytu == 224) kytu = _getch();
		switch (kytu)
		{
		case LEFT:if (luaChon > 0)
		{
			NormalBlue();
			SetMauChuXY(x + luaChon * 15, y, WHITE, menu[luaChon]);
			luaChon--;
			HighLight();
			SetMauChuXY(x + luaChon * 15, y, BLACK, menu[luaChon]);
			NormalBlue();
		}
				 break;
		case RIGHT:if (luaChon < 1)
		{
			NormalBlue();
			SetMauChuXY(x + luaChon * 15, y, WHITE, menu[luaChon]);
			luaChon++;
			HighLight();
			SetMauChuXY(x + luaChon * 15, y, BLACK, menu[luaChon]);
			NormalBlue();
		}
				  break;
		case ENTER:
		{
			XoaNhapVaThongbao();
			return luaChon;
		}
		}
	}
}
void XacNhan(int x, int y, string noiDung, int z)
{
	VeHCN(x, y, noiDung.length() + 2, 5, YELLOW);
	SetMauChuXY(x + 1, y + 1, YELLOW, noiDung);
	x += z;
	y += 3;
	HighLight();
	SetMauChuXY(x, y, BLACK, "ENTER");
	NormalBlue();
	char kytu;
	while (true)
	{
		kytu = _getch();
		if (kytu == 224) kytu = _getch();
		switch (kytu)
		{
		case ENTER:
		{
			XoaNhapVaThongbao();
			return;
		}
		}
	}
}