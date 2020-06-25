#include "GiaoDienVaDieuKhien.h"

int main() {
	resizeConsole();
	DSLOP dsLop;
	dsLop.n = 0;
	DanhSachMonHoc dsmh;
	dsmh.n = 0;
	NodeCH root = NULL;
	BatDau(dsLop, root, dsmh);
	system("pause");
	return 0;
}