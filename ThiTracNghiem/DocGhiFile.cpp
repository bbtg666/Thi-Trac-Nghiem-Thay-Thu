#include "DocGhiFile.h"

// Mon hoc
void ReadDSMH(DanhSachMonHoc& dsmh)
{
	int slmh;
	ifstream file("DSMH.txt");
	file >> slmh;
	for (int i = 0; i < slmh; i++)
	{
		MonHoc mh;
		string maMH;
		file.ignore();
		getline(file, mh.maMH, '#');
		file.ignore();
		getline(file, mh.tenMH, '#');
		InsertDSMH(dsmh, mh);
	}
	file.close();
}
void WriteDSMH(DanhSachMonHoc dsmh)
{
	ofstream file("DSMH.txt");
	file << dsmh.n << "\n";
	for (int i = 0; i < dsmh.n; i++)
	{
		file << dsmh.dsNodeMH[i]->maMH << "# " << dsmh.dsNodeMH[i]->tenMH << "#\n";
	}
	file.close();
}

// DIEM THI VA CAU HOI DA TRA LOI
void ReadDT(NodeDT& First, ifstream& file)
{
	string maMH;
	DiemThi diemThi;
	file.ignore();
	getline(file, maMH, '#');
	file.ignore();
	file >> diemThi.n;
	file.ignore();
	file >> diemThi.diem;
	for (int i = 0; i < diemThi.n; i++)
	{
		file.ignore();
		file >> diemThi.DSCHDTL[i].id;
		file.ignore();
		file >> diemThi.DSCHDTL[i].daChon;
	}
	InsertDT(First, maMH, diemThi);
}
void WriteDT(string maMH, DiemThi DT, ofstream& file)
{
	file << maMH << "# ";
	file << DT.n << " ";
	file << DT.diem << "\n";
	for (int i = 0; i < DT.n; i++)
	{
		file << DT.DSCHDTL[i].id << " ";
		file << DT.DSCHDTL[i].daChon << "\n";
	}
}

//SINH VIEN
void ReadSV(NodeSV& First, ifstream& file)
{
	SinhVien sv;
	int slmdt;
	file.ignore();
	getline(file, sv.maSV, '#');
	file.ignore();
	getline(file, sv.ho, '#');
	file.ignore();
	getline(file, sv.ten, '#');
	file.ignore();
	file >> sv.phai;
	file.ignore();
	getline(file, sv.password, '#');
	file.ignore();
	file >> slmdt;
	for (int i = 0; i < slmdt; i++)
	{
		ReadDT(sv.DT, file);
	}
	InsertSV(First, sv);
}

void WriteSV(SinhVien sv, ofstream& file)
{
	int slbchdt = DemSLBODT(sv.DT);
	file << sv.maSV << "# ";
	file << sv.ho << "# ";
	file << sv.ten << "# ";
	file << sv.phai << " ";
	file << sv.password << "# ";
	file << slbchdt << "\n";
	NodeDT p;
	if (sv.DT == NULL) return;
	for (p = sv.DT; p != NULL; p = p->next)
	{
		WriteDT(p->maMH, p->diemThi, file);
	}
}

//Lop
void ReadLop(DSLOP& dsLOP)
{
	int sllop;
	ifstream file("DSLOP.txt");
	file >> sllop;
	for (int i = 0; i < sllop; i++)
	{
		Lop lop;
		int slsv;
		file.ignore();
		getline(file, lop.maLop, '#');
		file.ignore();
		getline(file, lop.tenLop, '#');
		file.ignore();
		file >> slsv;
		for (int j = 0; j < slsv; j++)
		{
			ReadSV(lop.dssv, file);
		}
		InsertLop(dsLOP, lop);
	}
	file.close();
}
void WriteLop(DSLOP dsLOP)
{
	ofstream file("DSLOP.txt");
	file << dsLOP.n << "\n";
	for (int i = 0; i < dsLOP.n; i++)
	{
		int slsv = DemSLSV(dsLOP.LopArr[i].dssv);
		file << dsLOP.LopArr[i].maLop << "# ";
		file << dsLOP.LopArr[i].tenLop << "# ";
		file << slsv  << "\n";
		NodeSV p;
		if (dsLOP.LopArr[i].dssv == NULL) continue;
		for (p = dsLOP.LopArr[i].dssv; p != NULL; p = p->next)
		{
			WriteSV(p->sv, file);
		}
	}
	file.close();
}

// Cau hoi
void ReadCH(NodeCH& root)
{
	ifstream file("DSCH.txt");
	int slch;
	file >> slch;
	for (int i = 0; i < slch; i++)
	{
		file.ignore();
		CauHoi cauHoi;
		file >> cauHoi.id;
		file.ignore();
		getline(file, cauHoi.maMH, '#');
		file.ignore();
		getline(file, cauHoi.noiDung, '#');
		file.ignore();
		getline(file, cauHoi.A, '#');
		file.ignore();
		getline(file, cauHoi.B, '#');
		file.ignore();
		getline(file, cauHoi.C, '#');
		file.ignore();
		getline(file, cauHoi.D, '#');
		file.ignore();
		file >> cauHoi.dapAn;
		InsertCauHoi(root, cauHoi);
	}
}
void WriteCTCH(CauHoi cauHoi, ofstream& file)
{
	file << cauHoi.id << " ";
	file << cauHoi.maMH << "# ";
	file << cauHoi.noiDung << "# ";
	file << cauHoi.A << "# ";
	file << cauHoi.B << "# ";
	file << cauHoi.C << "# ";
	file << cauHoi.D << "# ";
	file << cauHoi.dapAn << "\n";
}
void WriteDSCH(NodeCH p, ofstream& file)
{
	if (p != NULL)
	{
		WriteDSCH(p->left, file);
		WriteCTCH(p->cauHoi, file);
		WriteDSCH(p->right, file);
	}
}
void WriteCH(NodeCH root)
{
	ofstream file("DSCH.txt");
	int slch = 0;
	DemCH(root, slch);
	file << slch << "\n";
	WriteDSCH(root, file);
	file.close();
}
// ID cau hoi

void ReadIDCH(int mangID[MAXCH])
{
	ifstream file("IDCH.txt");
	int i = 0;
	while(!file.eof())
	{
		file >> mangID[i];
		file.ignore();
		i++;
	}
}
void WriteIDCH(int mangID[MAXCH])
{
	ofstream file("IDCH.txt");
	int i = 0;
	while (mangID[i] >= 0)
	{
		file << mangID[i] << "\n";
		i++;
	}
	file.close();
}