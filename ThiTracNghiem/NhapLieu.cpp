#include "NhapLieu.h"

string Trim(string str)
{
	int n = str.length();
	for (int i = 0; i < n; i++)
	{
		if ((str[i] != ' ') && (str[i] != '	'))
		{
			str.erase(0, i);
			n = str.length();
			break;
		}
	}
	for (int i = n - 1; i >= 0; i--)
	{
		if (str[i] != ' ' && (str[i] != '	'))
		{
			str.erase(i + 1, n - i - 1);
			break;
		}
	}
	return str;
}
string CheckMa(string str)
{
	int n = str.length();
	for (int i = 0; i < n; i++)
	{
		if (str[i] == ' ' || str[i] == '	')
		{
			str.erase(i, 1);
			n = str.length();
			i--;
		}
	}
	return str;
}
string HoanThienChuoi(string str)
{
	str = Trim(str);
	int n = str.length();
	if (str[0] >= 'a' && str[0] <= 'z')
	{
		str[0] = str[0] - 32;
	}
	for (int i = 0; i < n; i++)
	{
		if (str[i] == ' ' || str[i] == '	')
		{
			if (str[i + 1] == ' ' || str[i + 1] == '	')
			{
				str.erase(i, 1);
				n = str.length();
				i--;
			}
			if (str[i + 1] >= 'a' && str[i + 1] <= 'z')
			{
				str[i + 1] = str[i + 1] - 32;
			}
		}
	}
	return str;
}

string HoanThienNoiDungCauHoi(string str)
{
	str = Trim(str);
	if (str[0] >= 'a' && str[0] <= 'z')
	{
		str[0] = str[0] - 32;
	}
	if (str[str.length()] == '?') return str;
	return str += '?';
}

int NhapDuLieu(int x, int y, int maxLength, string& data, int inHoa)
{
	Nocursortype(1);
	if (data.length() > 0)
	{
		gotoxy(x, y);
		cout << data;
		gotoxy(x + data.length(), y);
	}
	else gotoxy(x, y);
	char key;
	string input = data;
	while (1)
	{
		key = _getch();
		if (key == 0) key = _getch();
		if (key < 0)
		{
			_getch();
			continue;
		}
		switch (key)
		{
		case ESC:
		{
			Nocursortype(0);
			return 0;
		}
		case ENTER:
		{
			data = input;
			Nocursortype(0);
			return 1;
		}
		case BACKSPACE:
			if (input.length() != 0)
			{
				input.erase(input.length() - 1, 1);
				gotoxy(x + input.length(), y);
				cout << " ";
				gotoxy(x + input.length(), y);
			}
			break;
		default:
			if (input.length() < maxLength)
			{
				if ((int(key) >= 48 && int(key) <= 57) || (int(key) >= 65 && int(key) <= 90) || (int(key) >= 97 && int(key) <= 122) || (int(key) == SPACE))
				{
					if (inHoa && key >= 'a' && key <= 'z')
						key = key - 32;
					input += key;
					gotoxy(x + input.length() - 1, y);
					cout << key;
				}
			}
			break;
		}
	}
}
int NhapSo(int x, int y, int maxLength, int& slch)
{
	Nocursortype(1);
	string input;
	if (slch > 0)
	{
		gotoxy(x + to_string(slch).length(), y);
		input = to_string(slch);
	}
	else gotoxy(x, y);
	char key;

	while (1)
	{
		key = _getch();
		if (key == 0) key = _getch();
		if (key < 0)
		{
			_getch();
			continue;
		}
		switch (key)
		{
		case ESC:
		{
			Nocursortype(0);
			return 0;
		}
		case ENTER:
		{
			if (!input.length())
			{
				ThongBaoLoi(106, 18, "Vui long khong bo trong!!!");
				if (slch > 0)
				{
					gotoxy(x + to_string(slch).length(), y);
					input = to_string(slch);
				}
				else gotoxy(x, y);
				break;
			}
			slch = stoi(input);
			Nocursortype(0);
			return 1;
		}
		case BACKSPACE:
			if (input.length() != 0)
			{
				input.erase(input.length() - 1, 1);
				gotoxy(x + input.length(), y);
				cout << " ";
				gotoxy(x + input.length(), y);
			}
			break;
		default:
			if (input.length() < maxLength)
			{
				if ((int(key) >= 48 && int(key) <= 57))
				{
					input += key;
					gotoxy(x + input.length() - 1, y);
					cout << key;
				}
			}
			break;
		}
	}
}
int NhapTaiKhoan(int x, int y, int maxLength, string& data)
{
	Nocursortype(1);
	if (data.length() > 0)
	{
		gotoxy(x + data.length(), y);
	}
	else gotoxy(x, y);
	char key;
	string input = data;
	while (1)
	{
		key = _getch();
		if (key == 0) key = _getch();
		if (key == UP || key == LEFT || key == RIGHT)
		{
			_getch();
			continue;
		}
		switch (key)
		{
		case DOWN:
		case TAB:
		{
			data = input;
			Nocursortype(0);
			return 1;
		}
		case ENTER:
		{
			data = input;
			Nocursortype(0);
			return 2;
		}
		case BACKSPACE:
			if (input.length() != 0)
			{
				input.erase(input.length() - 1, 1);
				gotoxy(x + input.length(), y);
				cout << " ";
				gotoxy(x + input.length(), y);
			}
			break;
		default:
			if (input.length() < maxLength)
			{
				if ((int(key) >= 48 && int(key) <= 57) || (int(key) >= 65 && int(key) <= 90) || (int(key) >= 97 && int(key) <= 122))
				{
					if (key >= 'a' && key <= 'z')
						key = key - 32;
					input += key;
					gotoxy(x + input.length() - 1, y);
					cout << key;
				}
			}
			break;
		}
	}
}
int NhapPassword(int x, int y, int maxLength, string& data)
{
	Nocursortype(1);
	if (data.length() > 0)
	{
		gotoxy(x + data.length(), y);
	}
	else gotoxy(x, y);
	char key;
	string input = data;
	while (1)
	{
		key = _getch();
		if (key == 0) key = _getch();
		if (key == DOWN || key == LEFT || key == RIGHT)
		{
			_getch();
			continue;
		}
		switch (key)
		{
		case UP:
		case TAB:
		{
			data = input;
			Nocursortype(0);
			return 1;
		}
		case ENTER:
		{
			data = input;
			Nocursortype(0);
			return 2;
		}
		case BACKSPACE:
			if (input.length() != 0)
			{
				input.erase(input.length() - 1, 1);
				gotoxy(x + input.length(), y);
				cout << " ";
				gotoxy(x + input.length(), y);
			}
			break;
		default:
			if (input.length() < maxLength)
			{
				if (int(key) > 0)
				{
					input += key;
					gotoxy(x + input.length() - 1, y);
					cout << '*';
				}
			}
			break;
		}
	}

}
//NHAP LOP
int NhapDuLieuLop(DSLOP& dsLop)
{
	int x = 113, y = 12;
	Lop lop;
	VeHCN(98, 10, 50, 7, BLUE);
	SetMauChuXY(100, 12, WHITE, "Nhap ma lop: ");
	SetMauChuXY(100, 14, WHITE, "Nhap ten lop: ");
	XoaHuongDan();
	HuongDan(32, 40, BLUE, " ||| ENTER: XAC NHAN CHUOI | UP,DOWN: DE LEN XUONG | F2: LUU (Luu y la phai xac nhan chuoi moi duoc luu!) | ESC: THOAT");
	int flag = NhapDuLieu(x, y, 20, lop.maLop, 1);
	if (flag == 0)
	{
		XoaNhapVaThongbao();
		XoaHuongDan();
		HuongDanLop();
		return -1;
	}
	char key;
	int viTri = 0;
	while (true)
	{
		key = _getch();
		if (key == 0) key = _getch();
		switch (key)
		{
		case UP:
		{
			if (viTri == 1)
			{
				viTri = 0;
				flag = NhapDuLieu(x, y, 20, lop.maLop, 1);
			}
		}
		break;
		case DOWN:
		{
			if (viTri == 0)
			{
				viTri = 1;
				flag = NhapDuLieu(x + 1, y + 2, 30, lop.tenLop, 0);
			}
		}
		break;
		case ENTER:
		{
			if (viTri == 1) flag = NhapDuLieu(x + 1, y + 2, 30, lop.tenLop, 0);
			if (viTri == 0) flag = NhapDuLieu(x, y, 20, lop.maLop, 1);
		}
		break;
		case F2:
		{
			if (lop.maLop.length() == 0)
			{
				viTri = 0;
				ThongBaoLoi(102, 18, "Ma lop khong duoc de trong!!!");
				NormalBlue();
				flag = NhapDuLieu(x, y, 20, lop.maLop, 1);
				break;
			}
			if (lop.tenLop.length() == 0)
			{
				viTri = 1;
				ThongBaoLoi(102, 18, "Ten lop khong duoc de trong!!!");
				NormalBlue();
				flag = NhapDuLieu(x + 1, y + 2, 30, lop.tenLop, 0);
				break;
			}
			lop.maLop = CheckMa(lop.maLop);
			lop.tenLop = HoanThienChuoi(lop.tenLop);
			int a = InsertLop(dsLop, lop);
			if (a == -1)
			{
				ThongBaoLoi(105, 18, "DANH SACH LOP DA DAY!!!");
				continue;
			}
			if (a == -2)
			{
				ThongBaoLoi(98, 18, "Ma lop bi trung! Vui long nhap ma lop khac!");
				NormalBlue();
				flag = NhapDuLieu(x, y, 20, lop.maLop, 1);
				break;
			}
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			ThongBaoThanhCong(105, 18, "THEM LOP HOC THANH CONG!!!");
			return a;
		}
		case ESC:
		{
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			return -1;
		}
		}
		if (flag == 0)
		{
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			return -1;
		}
	}
}

void NhapLieuSuaLop(DSLOP& dsLop, int luaChon)
{
	int x = 114, y = 12;
	VeHCN(98, 10, 50, 5, BLUE);
	SetMauChuXY(100, 12, WHITE, "SUA TEN LOP: ");
	XoaHuongDan();
	HuongDan(56, 40, BLUE, " ||| ENTER: XAC NHAN CHUOI | F2: LUU (Luu y la phai xac nhan chuoi moi duoc luu!) | ESC: THOAT");
	int flag = NhapDuLieu(x, y, 30, dsLop.LopArr[luaChon].tenLop, 0);
	if (flag == 0)
	{
		XoaNhapVaThongbao();
		XoaHuongDan();
		HuongDanLop();
		return;
	}
	char key;
	int viTri = 0;
	while (true)
	{
		key = _getch();
		if (key == 0) key = _getch();
		switch (key)
		{
		case ENTER:
		{

			flag = NhapDuLieu(x, y, 30, dsLop.LopArr[luaChon].tenLop, 0);
		}
		break;
		case F2:
		{
			if (dsLop.LopArr[luaChon].tenLop.length() == 0)
			{
				viTri = 1;
				ThongBaoLoi(102, 18, "Ten lop khong duoc de trong!!!");
				NormalBlue();
				flag = NhapDuLieu(x + 1, y + 2, 30, dsLop.LopArr[luaChon].tenLop, 0);
				break;
			}
			dsLop.LopArr[luaChon].tenLop = HoanThienChuoi(dsLop.LopArr[luaChon].tenLop);
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			ThongBaoThanhCong(105, 18, "SUA TEN LOP HOC THANH CONG!!!");
			return;
		}
		case ESC:
		{
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			return;
		}
		}
		if (flag == 0)
		{
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			return;
		}
	}
}

//Sinh vien
int GioiTinh(string phai)
{
	if (phai == "Nam")
	{
		return 1;
	}
	else if (phai == "Nu")
	{
		return 2;
	}
	else
	{
		return 0;
	}
}
int NhapDuLieuSinhVien(NodeSV& First, DSLOP dsLop)
{
	int x = 98, y = 10;
	char key;
	int viTri = 0;
	SinhVien  sv;
	string phai;
	VeHCN(x, y - 1, 50, 9, BLUE);
	SetMauChuXY(x + 2, y, WHITE, "Nhap ma sinh vien: ");
	SetMauChuXY(x + 2, y + 2, WHITE, "Nhap ho: ");
	SetMauChuXY(x + 2, y + 4, WHITE, "Nhap ten: ");
	SetMauChuXY(x + 2, y + 6, WHITE, "Gioi tinh: ");
	XoaHuongDan();
	HuongDan(32, 40, BLUE, " ||| ENTER: XAC NHAN CHUOI | UP,DOWN: DE LEN XUONG | F2: LUU (Luu y la phai xac nhan chuoi moi duoc luu!) | ESC: THOAT");
	int flag = NhapDuLieu(x + 21, y, 20, sv.maSV, 1);
	if (flag == 0)
	{
		XoaNhapVaThongbao();
		XoaHuongDan();
		HuongDanLop();
		return -1;
	}
	while (true)
	{
		key = _getch();
		if (key == 0) key = _getch();
		switch (key)
		{
		case UP:
		{
			if (viTri > 0)
			{
				viTri--;
				if (viTri == 0)
				{
					flag = NhapDuLieu(x + 21, y, 20, sv.maSV, 1);
				}
				if (viTri == 1)
				{
					flag = NhapDuLieu(x + 11, y + 2, 20, sv.ho, 0);
				}
				if (viTri == 2)
				{
					flag = NhapDuLieu(x + 12, y + 4, 10, sv.ten, 0);
				}

			}
		}
		break;
		case DOWN:
		{
			if (viTri < 3)
			{
				viTri++;
				if (viTri == 1)
				{
					flag = NhapDuLieu(x + 11, y + 2, 20, sv.ho, 0);
				}
				if (viTri == 2)
				{
					flag = NhapDuLieu(x + 12, y + 4, 10, sv.ten, 0);
				}
				if (viTri == 3)
				{
					flag = NhapDuLieu(x + 13, y + 6, 3, phai, 0);
				}
			}
		}
		break;
		case ENTER:
		{
			if (viTri == 0) flag = NhapDuLieu(x + 21, y, 20, sv.maSV, 1);
			if (viTri == 1) flag = NhapDuLieu(x + 11, y + 2, 20, sv.ho, 0);
			if (viTri == 2) flag = NhapDuLieu(x + 12, y + 4, 10, sv.ten, 0);
			if (viTri == 3) flag = NhapDuLieu(x + 13, y + 6, 3, phai, 0);
		}
		break;
		case F2:
		{
			if (sv.maSV.length() == 0)
			{
				viTri = 0;
				ThongBaoLoi(102, 18, "Ma sinh vien khong duoc de trong!!!");
				NormalBlue();
				flag = NhapDuLieu(x + 21, y, 20, sv.maSV, 1);
				break;
			}
			if (sv.ho.length() == 0)
			{
				viTri = 1;
				ThongBaoLoi(102, 18, "Ho sinh vien khong duoc de trong!!!");
				NormalBlue();
				flag = NhapDuLieu(x + 11, y + 2, 20, sv.ho, 0);
				break;
			}
			if (sv.ten.length() == 0)
			{
				viTri = 2;
				ThongBaoLoi(102, 18, "Ten sinh vien khong duoc de trong!!!");
				NormalBlue();
				flag = NhapDuLieu(x + 12, y + 4, 10, sv.ten, 0);
				break;
			}
			if (phai.length() == 0)
			{
				viTri = 3;
				ThongBaoLoi(102, 18, "Ten sinh vien khong duoc de trong!!!");
				NormalBlue();
				flag = NhapDuLieu(x + 13, y + 6, 3, phai, 0);
				break;
			}
			if (GioiTinh(HoanThienChuoi(phai)) == 0)
			{
				ThongBaoLoi(95, 20, "Ban nhap sai phai! Vui long nhap \"Nam\" hoac \"Nu\"!!!");
				NormalBlue();
				flag = NhapDuLieu(x + 13, y + 6, 3, phai, 0);
				break;
			}
			sv.maSV = CheckMa(sv.maSV);
			int checkTrung = 0;
			for (int j = 0; j < dsLop.n; j++)
			{
				if (SearchSV(dsLop.LopArr[j].dssv, sv.maSV) != NULL)
				{
					checkTrung = 1;
					break;
				}
			}
			if (checkTrung == 1)
			{
				XoaThongBao();
				ThongBaoLoi(110, 20, "Ma sinh vien bi trung!!!");
				NormalBlue();
				flag = NhapDuLieu(x + 21, y, 20, sv.maSV, 1);
				break;
			}
			sv.ho = HoanThienChuoi(sv.ho);
			sv.ten = HoanThienChuoi(sv.ten);
			sv.phai = GioiTinh(HoanThienChuoi(phai));
			sv.password = "123";
			int a = InsertSV(First, sv);
			if (a == 0)
			{
				ThongBaoLoi(98, 18, "Them sinh vien bi loi!!!");
				NormalBlue();
				flag = NhapDuLieu(x + 21, y, 20, sv.maSV, 1);
				break;
			}
			int i = 0;
			for (NodeSV p = First; p != NULL; p = p->next)
			{
				if (p->sv.maSV == sv.maSV) break;
				i++;
			}
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			ThongBaoThanhCong(105, 18, "THEM SINH VIEN THANH CONG!!!");
			return i;
		}
		case ESC:
		{
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			return -1;
		}
		}
		if (flag == 0)
		{
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			return -1;
		}
	}
}

void NhapDuLieuSuaSinhVien(NodeSV& First, int luaChon)
{
	int x = 98, y = 10;
	char key;
	int viTri = 0;
	NodeSV nodeSV = SearchSVSTT(First, luaChon);
	string phai = nodeSV->sv.phai == 1 ? "Nam" : "Nu";
	VeHCN(x, y - 1, 50, 9, BLUE);
	SetMauChuXY(x + 2, y, WHITE, "Nhap ho: ");
	SetMauChuXY(x + 2, y + 2, WHITE, "Nhap ten: ");
	SetMauChuXY(x + 2, y + 4, WHITE, "Gioi tinh: ");
	SetMauChuXY(x + 12, y + 2, BLUE, nodeSV->sv.ten);
	SetMauChuXY(x + 13, y + 4, BLUE, phai);
	XoaHuongDan();
	HuongDan(32, 40, BLUE, " ||| ENTER: XAC NHAN CHUOI | UP,DOWN: DE LEN XUONG | F2: LUU (Luu y la phai xac nhan chuoi moi duoc luu!) | ESC: THOAT");
	int flag = NhapDuLieu(x + 11, y, 20, nodeSV->sv.ho, 0);
	if (flag == 0)
	{
		XoaNhapVaThongbao();
		XoaHuongDan();
		HuongDanLop();
		return;
	}
	while (true)
	{
		key = _getch();
		if (key == 0) key = _getch();
		switch (key)
		{
		case UP:
		{
			if (viTri > 0)
			{
				viTri--;
				if (viTri == 0)
				{
					flag = NhapDuLieu(x + 11, y, 20, nodeSV->sv.ho, 0);
				}
				if (viTri == 1)
				{
					flag = NhapDuLieu(x + 12, y + 2, 10, nodeSV->sv.ten, 0);
				}

			}
		}
		break;
		case DOWN:
		{
			if (viTri < 2)
			{
				viTri++;
				if (viTri == 1)
				{
					flag = NhapDuLieu(x + 12, y + 2, 10, nodeSV->sv.ten, 0);
				}
				if (viTri == 2)
				{
					flag = NhapDuLieu(x + 13, y + 4, 3, phai, 0);
				}
			}
		}
		break;
		case ENTER:
		{
			if (viTri == 0) flag = NhapDuLieu(x + 11, y, 20, nodeSV->sv.ho, 0);
			if (viTri == 1) flag = NhapDuLieu(x + 12, y + 2, 10, nodeSV->sv.ten, 0);
			if (viTri == 2) flag = NhapDuLieu(x + 13, y + 4, 3, phai, 0);
		}
		break;
		case F2:
		{
			if (nodeSV->sv.ho.length() == 0)
			{
				viTri = 0;
				ThongBaoLoi(102, 18, "Ho sinh vien khong duoc de trong!!!");
				NormalBlue();
				flag = NhapDuLieu(x + 11, y + 2, 20, nodeSV->sv.ho, 0);
				break;
			}
			if (nodeSV->sv.ten.length() == 0)
			{
				viTri = 1;
				ThongBaoLoi(102, 18, "Ten sinh vien khong duoc de trong!!!");
				NormalBlue();
				flag = NhapDuLieu(x + 12, y + 4, 10, nodeSV->sv.ten, 0);
				break;
			}
			if (phai.length() == 0)
			{
				viTri = 2;
				ThongBaoLoi(102, 18, "Ten sinh vien khong duoc de trong!!!");
				NormalBlue();
				flag = NhapDuLieu(x + 13, y + 6, 3, phai, 0);
				break;
			}
			if (GioiTinh(HoanThienChuoi(phai)) == 0)
			{
				ThongBaoLoi(95, 20, "Ban nhap sai phai! Vui long nhap \"Nam\" hoac \"Nu\"!!!");
				NormalBlue();
				flag = NhapDuLieu(x + 13, y + 4, 3, phai, 0);
				break;
			}
			nodeSV->sv.ho = HoanThienChuoi(nodeSV->sv.ho);
			nodeSV->sv.ten = HoanThienChuoi(nodeSV->sv.ten);
			nodeSV->sv.phai = GioiTinh(HoanThienChuoi(phai));
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			ThongBaoThanhCong(105, 18, "SUA SINH VIEN THANH CONG!!!");
			return;
		}
		case ESC:
		{
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			return;
		}
		}
		if (flag == 0)
		{
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			return;
		}
	}
}


//Mon Hoc
int NhapDuLieuMonHoc(DanhSachMonHoc& dsmh)
{
	int x = 116, y = 12;
	MonHoc mh;
	VeHCN(97, 10, 51, 7, BLUE);
	SetMauChuXY(99, 12, WHITE, "Nhap ma mon hoc: ");
	SetMauChuXY(99, 14, WHITE, "Nhap ten mon hoc: ");
	XoaHuongDan();
	HuongDan(32, 40, BLUE, " ||| ENTER: XAC NHAN CHUOI | UP,DOWN: DE LEN XUONG | F2: LUU (Luu y la phai xac nhan chuoi moi duoc luu!) | ESC: THOAT");
	int flag = NhapDuLieu(x, y, 20, mh.maMH, 1);
	if (flag == 0)
	{
		XoaNhapVaThongbao();
		XoaHuongDan();
		HuongDanLop();
		return -1;
	}
	char key;
	int viTri = 0;
	while (true)
	{
		key = _getch();
		if (key == 0) key = _getch();
		switch (key)
		{
		case UP:
		{
			if (viTri == 1)
			{
				viTri = 0;
				flag = NhapDuLieu(x, y, 20, mh.maMH, 1);
			}
		}
		break;
		case DOWN:
		{
			if (viTri == 0)
			{
				viTri = 1;
				flag = NhapDuLieu(x + 1, y + 2, 30, mh.tenMH, 0);
			}
		}
		break;
		case ENTER:
		{
			if (viTri == 1) flag = NhapDuLieu(x + 1, y + 2, 30, mh.tenMH, 0);
			if (viTri == 0) flag = NhapDuLieu(x, y, 20, mh.maMH, 1);
		}
		break;
		case F2:
		{
			if (mh.maMH.length() == 0)
			{
				viTri = 0;
				ThongBaoLoi(102, 18, "Ma mon hoc khong duoc de trong!!!");
				NormalBlue();
				flag = NhapDuLieu(x, y, 20, mh.maMH, 1);
				break;
			}
			if (mh.tenMH.length() == 0)
			{
				viTri = 1;
				ThongBaoLoi(102, 18, "Ten mon hoc khong duoc de trong!!!");
				NormalBlue();
				flag = NhapDuLieu(x + 1, y + 2, 30, mh.tenMH, 0);
				break;
			}
			mh.maMH = CheckMa(mh.maMH);
			mh.tenMH = HoanThienChuoi(mh.tenMH);
			int a = InsertDSMH(dsmh, mh);
			if (a == -1)
			{
				ThongBaoLoi(105, 18, "DANH SACH LOP DA DAY!!!");
				continue;
			}
			if (a == -2)
			{
				ThongBaoLoi(98, 18, "Ma lop bi trung! Vui long nhap ma lop khac!");
				NormalBlue();
				flag = NhapDuLieu(x, y, 20, mh.maMH, 1);
				break;
			}
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			ThongBaoThanhCong(105, 18, "THEM LOP HOC THANH CONG!!!");
			return a;
		}
		case ESC:
		{
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			return -1;
		}
		}
		if (flag == 0)
		{
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			return -1;
		}
	}
}

void NhapLieuSuaMonHoc(DanhSachMonHoc& dsmh, int luaChon)
{
	int x = 116, y = 12;
	VeHCN(97, 10, 51, 7, BLUE);
	SetMauChuXY(99, 12, WHITE, "SUA TEN MON HOC: ");
	XoaHuongDan();
	HuongDan(56, 40, BLUE, " ||| ENTER: XAC NHAN CHUOI | F2: LUU (Luu y la phai xac nhan chuoi moi duoc luu!) | ESC: THOAT");
	int flag = NhapDuLieu(x, y, 30, dsmh.dsNodeMH[luaChon]->tenMH, 0);
	if (flag == 0)
	{
		XoaNhapVaThongbao();
		XoaHuongDan();
		HuongDanLop();
		return;
	}
	char key;
	int viTri = 0;
	while (true)
	{
		key = _getch();
		if (key == 0) key = _getch();
		switch (key)
		{
		case ENTER:
		{

			flag = NhapDuLieu(x, y, 30, dsmh.dsNodeMH[luaChon]->tenMH, 0);
		}
		break;
		case F2:
		{
			if (dsmh.dsNodeMH[luaChon]->tenMH.length() == 0)
			{
				viTri = 1;
				ThongBaoLoi(102, 18, "Ten lop khong duoc de trong!!!");
				NormalBlue();
				flag = NhapDuLieu(x + 1, y + 2, 30, dsmh.dsNodeMH[luaChon]->tenMH, 0);
				break;
			}
			dsmh.dsNodeMH[luaChon]->tenMH = HoanThienChuoi(dsmh.dsNodeMH[luaChon]->tenMH);
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			ThongBaoThanhCong(105, 18, "SUA TEN MON HOC THANH CONG!!!");
			return;
		}
		case ESC:
		{
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			return;
		}
		}
		if (flag == 0)
		{
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			return;
		}
	}
}
//Cau hoi
void InNoiDungCH(int x, int y, string str)
{
	int i = 0, start, count;
	while (true)
	{
		gotoxy(x, i + y);
		start = 53 * i;
		count = 53 < str.length() - start ? 53 : str.length() - start;
		cout << str.substr(start, count);
		if (count < 53) break;
		i++;
	}
}
int XuLiNhapNoiDungCH(int x, int y, int maxLength, string& data)
{
	Nocursortype(1);
	char key;
	string input = data;
	int i = data.length() / 53; int z = data.length() % 53;
	gotoxy(x, y);
	NormalWhite();
	InNoiDungCH(x, y, input);
	while (1)
	{
		key = _getch();
		if (key == 0) key = _getch();
		if (key < 0)
		{
			_getch();
			continue;
		}
		switch (key)
		{
		case ESC:
		{
			Nocursortype(0);
			return 0;
		}
		case ENTER:
		{
			data = input;
			Nocursortype(0);
			return 1;
		}
		case BACKSPACE:
			if (input.length() != 0)
			{
				if (z == 0)
				{
					i--;
					z = 53;
				}
				input.erase(input.length() - 1, 1);
				z--;
				gotoxy(x + z, y + i);
				cout << " ";
				gotoxy(x + z, y + i);

			}
			break;
		default:
			if (input.length() < maxLength)
			{
				if ((int(key) >= 48 && int(key) <= 57) || (int(key) >= 65 && int(key) <= 90) || (int(key) >= 97 && int(key) <= 122) || (int(key) == SPACE))
				{
					input += key;
					gotoxy(x + z++, y + i);
					cout << key;
					if (z == 53)
					{
						i++;
						z = 0;
					}
				}
			}
			break;
		}
	}
}

int XulyDapAn2(string a)
{
	if (a == "A") return 1;
	if (a == "B") return 2;
	if (a == "C") return 3;
	if (a == "D") return 4;
	return -1;
}

int NhapDuLieuCauHoi(NodeCH& rootCH, DSCHTMH& dsch, string maMH)
{
	int x = 94, y = 8, viTri = 0;
	char key;
	CauHoi ch;
	string dapAn;
	VeHCN(x, y, 55, 18, BLUE);
	SetMauChuXY(x + 1, y + 1, BLUE, "NHAP NOI DUNG: ");
	SetMauChuXY(x + 1, y + 8, BLUE, "A: ");
	SetMauChuXY(x + 1, y + 10, BLUE, "B: ");
	SetMauChuXY(x + 1, y + 12, BLUE, "C: ");
	SetMauChuXY(x + 1, y + 14, BLUE, "D: ");
	SetMauChuXY(x + 1, y + 16, BLUE, "DAP AN: ");
	XoaHuongDan();
	HuongDan(32, 40, BLUE, " ||| ENTER: XAC NHAN CHUOI | UP,DOWN: DE LEN XUONG | F2: LUU (Luu y la phai xac nhan chuoi moi duoc luu!) | ESC: THOAT");
	int flag = XuLiNhapNoiDungCH(x + 1, y + 2, 265, ch.noiDung);
	if (flag == 0)
	{
		XoaNhapVaThongbao();
		XoaHuongDan();
		HuongDanLop();
		return -1;
	}
	while (true)
	{
		key = _getch();
		if (key == 0) key = _getch();
		switch (key)
		{
		case UP:
		{
			if (viTri > 0)
			{
				viTri--;
				if (viTri == 0)
				{
					flag = XuLiNhapNoiDungCH(x + 1, y + 2, 265, ch.noiDung);
				}
				if (viTri == 1)
				{
					flag = NhapDuLieu(x + 4, y + 8, 20, ch.A, 0);
				}
				if (viTri == 2)
				{
					flag = NhapDuLieu(x + 4, y + 10, 20, ch.B, 0);
				}
				if (viTri == 3)
				{
					flag = NhapDuLieu(x + 4, y + 12, 20, ch.C, 0);
				}
				if (viTri == 4)
				{
					flag = NhapDuLieu(x + 4, y + 14, 20, ch.D, 0);
				}

			}
		}
		break;
		case DOWN:
		{
			if (viTri < 5)
			{
				viTri++;
				if (viTri == 1)
				{
					flag = NhapDuLieu(x + 4, y + 8, 20, ch.A, 0);
				}
				if (viTri == 2)
				{
					flag = NhapDuLieu(x + 4, y + 10, 20, ch.B, 0);
				}
				if (viTri == 3)
				{
					flag = NhapDuLieu(x + 4, y + 12, 20, ch.C, 0);
				}
				if (viTri == 4)
				{
					flag = NhapDuLieu(x + 4, y + 14, 20, ch.D, 0);
				}
				if (viTri == 5)
				{
					flag = NhapDuLieu(x + 9, y + 16, 1, dapAn, 1);
				}
			}
		}
		break;
		case ENTER:
		{
			if (viTri == 0) flag = XuLiNhapNoiDungCH(x + 1, y + 2, 265, ch.noiDung);
			if (viTri == 1) flag = NhapDuLieu(x + 4, y + 8, 20, ch.A, 0);
			if (viTri == 2) flag = NhapDuLieu(x + 4, y + 10, 20, ch.B, 0);
			if (viTri == 3) flag = NhapDuLieu(x + 4, y + 12, 20, ch.C, 0);
			if (viTri == 4) flag = NhapDuLieu(x + 4, y + 14, 20, ch.D, 0);
			if (viTri == 5) flag = NhapDuLieu(x + 9, y + 16, 1, dapAn, 1);
		}
		break;
		case F2:
		{
			if (ch.noiDung.length() == 0)
			{
				viTri = 0;
				XoaThongBaoNhapCauHoi();
				ThongBaoLoi(105, 27, "Noi dung khong duoc de trong!!!");
				NormalWhite();
				flag = XuLiNhapNoiDungCH(x + 1, y + 2, 265, ch.noiDung);
				break;
			}
			if (ch.A.length() == 0)
			{
				viTri = 1;
				XoaThongBaoNhapCauHoi();
				ThongBaoLoi(105, 27, "Dap an A khong duoc de trong!!!");
				NormalWhite();
				flag = NhapDuLieu(x + 4, y + 8, 20, ch.A, 0);
				break;
			}
			if (ch.B.length() == 0)
			{
				viTri = 2;
				XoaThongBaoNhapCauHoi();
				ThongBaoLoi(105, 27, "Dap an B khong duoc de trong!!!");
				NormalWhite();
				flag = NhapDuLieu(x + 4, y + 10, 20, ch.B, 0);
				break;
			}
			if (ch.C.length() == 0)
			{
				viTri = 3;
				XoaThongBaoNhapCauHoi();
				ThongBaoLoi(105, 27, "Dap an C khong duoc de trong!!!");
				NormalWhite();
				flag = NhapDuLieu(x + 4, y + 12, 20, ch.C, 0);
				break;
			}
			if (ch.D.length() == 0)
			{
				viTri = 4;
				XoaThongBaoNhapCauHoi();
				ThongBaoLoi(105, 27, "Dap an D khong duoc de trong!!!");
				NormalWhite();
				flag = NhapDuLieu(x + 4, y + 14, 20, ch.D, 0);
				break;
			}
			if (dapAn.length() == 0)
			{
				viTri = 5;
				XoaThongBaoNhapCauHoi();
				ThongBaoLoi(102, 27, "Dap an dung khong duoc de trong!!!");
				NormalWhite();
				flag = NhapDuLieu(x + 9, y + 16, 1, dapAn, 1);
				break;
			}
			if (dapAn != "A" && dapAn != "B" && dapAn != "C" && dapAn != "D")
			{
				viTri = 5;
				XoaThongBaoNhapCauHoi();
				ThongBaoLoi(105, 27, "Dap an phai la A, B, C hoac D!!!");
				NormalWhite();
				flag = NhapDuLieu(x + 9, y + 16, 1, dapAn, 1);
				break;
			}
			ch.dapAn = XulyDapAn2(dapAn);
			ch.maMH = maMH;
			ch.noiDung = HoanThienNoiDungCauHoi(ch.noiDung);
			int ID[MAXCH];
			ReadIDCH(ID);
			ch.id = ID[0];
			int i;
			for (i = 0; i < dsch.n; i++)
			{
				if (dsch.dsch[i].id > ch.id)
				{
					for (int j = dsch.n; j > i; j--)
					{
						dsch.dsch[j] = dsch.dsch[j - 1];
					}
					dsch.dsch[i] = ch;
					break;
				}
			}
			InsertCauHoi(rootCH, ch);
			for (int i = 0; i < 1000; i++)
			{
				if (ID[i] < 0 || i == 999) break;
				ID[i] = ID[i + 1];
			}
			WriteIDCH(ID);
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			ThongBaoThanhCong(105, 18, "THEM CAU HOI THANH CONG!!!");
			return i;
		}
		case ESC:
		{
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			return -1;
		}
		}
		if (flag == 0)
		{
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			return -1;
		}
	}
}

void NhapDuLieuSuaCauHoi(NodeCH& rootCH, DSCHTMH& dsch, int luaChon)
{
	int x = 94, y = 8, viTri = 0;
	char key;
	string dapAn = XuLyDapAn(dsch.dsch[luaChon].dapAn);
	VeHCN(x, y, 55, 18, BLUE);
	SetMauChuXY(x + 1, y + 1, BLUE, "NHAP NOI DUNG: ");
	SetMauChuXY(x + 1, y + 8, BLUE, "A: ");
	SetMauChuXY(x + 4, y + 8, WHITE, dsch.dsch[luaChon].A);
	SetMauChuXY(x + 1, y + 10, BLUE, "B: ");
	SetMauChuXY(x + 4, y + 10, WHITE, dsch.dsch[luaChon].B);
	SetMauChuXY(x + 1, y + 12, BLUE, "C: ");
	SetMauChuXY(x + 4, y + 12, WHITE, dsch.dsch[luaChon].C);
	SetMauChuXY(x + 1, y + 14, BLUE, "D: ");
	SetMauChuXY(x + 4, y + 14, WHITE, dsch.dsch[luaChon].D);
	SetMauChuXY(x + 1, y + 16, BLUE, "DAP AN: ");
	SetMauChuXY(x + 9, y + 16, WHITE, dapAn);
	XoaHuongDan();
	HuongDan(32, 40, BLUE, " ||| ENTER: XAC NHAN CHUOI | UP,DOWN: DE LEN XUONG | F2: LUU (Luu y la phai xac nhan chuoi moi duoc luu!) | ESC: THOAT");
	int flag = XuLiNhapNoiDungCH(x + 1, y + 2, 265, dsch.dsch[luaChon].noiDung);
	if (flag == 0)
	{
		XoaNhapVaThongbao();
		XoaHuongDan();
		HuongDanLop();
		return;
	}
	while (true)
	{
		key = _getch();
		if (key == 0) key = _getch();
		switch (key)
		{
		case UP:
		{
			if (viTri > 0)
			{
				viTri--;
				if (viTri == 0)
				{
					flag = XuLiNhapNoiDungCH(x + 1, y + 2, 265, dsch.dsch[luaChon].noiDung);
				}
				if (viTri == 1)
				{
					flag = NhapDuLieu(x + 4, y + 8, 20, dsch.dsch[luaChon].A, 0);
				}
				if (viTri == 2)
				{
					flag = NhapDuLieu(x + 4, y + 10, 20, dsch.dsch[luaChon].B, 0);
				}
				if (viTri == 3)
				{
					flag = NhapDuLieu(x + 4, y + 12, 20, dsch.dsch[luaChon].C, 0);
				}
				if (viTri == 4)
				{
					flag = NhapDuLieu(x + 4, y + 14, 20, dsch.dsch[luaChon].D, 0);
				}

			}
		}
		break;
		case DOWN:
		{
			if (viTri < 5)
			{
				viTri++;
				if (viTri == 1)
				{
					flag = NhapDuLieu(x + 4, y + 8, 20, dsch.dsch[luaChon].A, 0);
				}
				if (viTri == 2)
				{
					flag = NhapDuLieu(x + 4, y + 10, 20, dsch.dsch[luaChon].B, 0);
				}
				if (viTri == 3)
				{
					flag = NhapDuLieu(x + 4, y + 12, 20, dsch.dsch[luaChon].C, 0);
				}
				if (viTri == 4)
				{
					flag = NhapDuLieu(x + 4, y + 14, 20, dsch.dsch[luaChon].D, 0);
				}
				if (viTri == 5)
				{
					flag = NhapDuLieu(x + 9, y + 16, 1, dapAn, 1);
				}
			}
		}
		break;
		case ENTER:
		{
			if (viTri == 0) flag = XuLiNhapNoiDungCH(x + 1, y + 2, 265, dsch.dsch[luaChon].noiDung);
			if (viTri == 1) flag = NhapDuLieu(x + 4, y + 8, 20, dsch.dsch[luaChon].A, 0);
			if (viTri == 2) flag = NhapDuLieu(x + 4, y + 10, 20, dsch.dsch[luaChon].B, 0);
			if (viTri == 3) flag = NhapDuLieu(x + 4, y + 12, 20, dsch.dsch[luaChon].C, 0);
			if (viTri == 4) flag = NhapDuLieu(x + 4, y + 14, 20, dsch.dsch[luaChon].D, 0);
			if (viTri == 5) flag = NhapDuLieu(x + 9, y + 16, 1, dapAn, 1);
		}
		break;
		case F2:
		{
			if (dsch.dsch[luaChon].noiDung.length() == 0)
			{
				viTri = 0;
				XoaThongBaoNhapCauHoi();
				ThongBaoLoi(105, 27, "Noi dung khong duoc de trong!!!");
				NormalWhite();
				flag = XuLiNhapNoiDungCH(x + 1, y + 2, 265, dsch.dsch[luaChon].noiDung);
				break;
			}
			if (dsch.dsch[luaChon].A.length() == 0)
			{
				viTri = 1;
				XoaThongBaoNhapCauHoi();
				ThongBaoLoi(105, 27, "Dap an A khong duoc de trong!!!");
				NormalWhite();
				flag = NhapDuLieu(x + 4, y + 8, 20, dsch.dsch[luaChon].A, 0);
				break;
			}
			if (dsch.dsch[luaChon].B.length() == 0)
			{
				viTri = 2;
				XoaThongBaoNhapCauHoi();
				ThongBaoLoi(105, 27, "Dap an B khong duoc de trong!!!");
				NormalWhite();
				flag = NhapDuLieu(x + 4, y + 10, 20, dsch.dsch[luaChon].B, 0);
				break;
			}
			if (dsch.dsch[luaChon].C.length() == 0)
			{
				viTri = 3;
				XoaThongBaoNhapCauHoi();
				ThongBaoLoi(105, 27, "Dap an C khong duoc de trong!!!");
				NormalWhite();
				flag = NhapDuLieu(x + 4, y + 12, 20, dsch.dsch[luaChon].C, 0);
				break;
			}
			if (dsch.dsch[luaChon].D.length() == 0)
			{
				viTri = 4;
				XoaThongBaoNhapCauHoi();
				ThongBaoLoi(105, 27, "Dap an D khong duoc de trong!!!");
				NormalWhite();
				flag = NhapDuLieu(x + 4, y + 14, 20, dsch.dsch[luaChon].D, 0);
				break;
			}
			if (dapAn.length() == 0)
			{
				viTri = 5;
				XoaThongBaoNhapCauHoi();
				ThongBaoLoi(102, 27, "Dap an dung khong duoc de trong!!!");
				NormalWhite();
				flag = NhapDuLieu(x + 9, y + 16, 1, dapAn, 1);
				break;
			}
			if (dapAn != "A" && dapAn != "B" && dapAn != "C" && dapAn != "D")
			{
				viTri = 5;
				XoaThongBaoNhapCauHoi();
				ThongBaoLoi(105, 27, "Dap an phai la A, B, C hoac D!!!");
				NormalWhite();
				flag = NhapDuLieu(x + 9, y + 16, 1, dapAn, 1);
				break;
			}
			dsch.dsch[luaChon].dapAn = XulyDapAn2(dapAn);
			UpdateCauHoi(rootCH, dsch.dsch[luaChon]);
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			ThongBaoThanhCong(105, 18, "SUA CAU HOI THANH CONG!!!");
			return;
		}
		case ESC:
		{
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			return;
		}
		}
		if (flag == 0)
		{
			XoaNhapVaThongbao();
			XoaHuongDan();
			HuongDanLop();
			return;
		}
	}
	return;
}

//Thi
int NhapSoCauHoi(int& slch)
{
	XoaNhapVaThongbao();
	VeHCN(106, 11, 31, 3, BLUE);
	SetMauChuXY(109, 12, WHITE, "Nhap so luong cau hoi: ");
NhapSoCH:	if (NhapSo(132, 12, 2, slch) == 0)
{
	XoaNhapVaThongbao();
	return 0;
}
else
{
	if (slch > 40 || slch < 1)
	{
		ThongBaoLoi(95, 15, "So luong cau hoi phai lon hon 0 va nho hon 40!!!");
		goto NhapSoCH;
	}
	XoaNhapVaThongbao();
	return 1;
}
}
int NhapSoPhutThi(int& soPhut)
{
	XoaNhapVaThongbao();
	VeHCN(108, 11, 25, 3, BLUE);
	SetMauChuXY(110, 12, WHITE, "Nhap so phut thi: ");
NhapSoCH:	if (NhapSo(128, 12, 3, soPhut) == 0)
{
	XoaNhapVaThongbao();
	return 0;
}
else
{
	if (soPhut > 180 || soPhut < 0)
	{
		ThongBaoLoi(100, 15, "So thi phai lon hon 0 va nho hon 180!!!");
		goto NhapSoCH;
	}
	XoaNhapVaThongbao();
	return 1;
}
}