#pragma once
#include "DanhSach.h"

// Mon hoc
void ReadDSMH(DanhSachMonHoc& dsmh);
void WriteDSMH(DanhSachMonHoc dsmh);
//Diem thi
void ReadDT(NodeDT& DSDT, ifstream& file);
void WriteDT(string maMH, DiemThi DT, ofstream& file);
//SV
void ReadSV(NodeSV& dssv, ifstream& file);
void WriteSV(SinhVien sv, ofstream& file);
//Lop
void ReadLop(DSLOP& dsLOP);
void WriteLop(DSLOP dsLOP);
//Cau hoi
void ReadCH(NodeCH& root);
void WriteCH(NodeCH root);

void ReadIDCH(int mangID[MAXCH]);
void WriteIDCH(int mangID[MAXCH]);