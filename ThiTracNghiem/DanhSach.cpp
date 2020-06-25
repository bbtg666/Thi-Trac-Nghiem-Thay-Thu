#include "DanhSach.h"

//Cau hoi da tra loi
void InsertFirstDT(NodeDT& First, string maMH, DiemThi diemThi)
{
	NodeDT p;
	p = new NodeDiemThi;
	p->maMH = maMH;
	p->diemThi = diemThi;
	p->next = First;
	First = p;
}
void InsertDT(NodeDT& First, string maMH, DiemThi diemThi)
{
	NodeDT p, s, t = NULL;
	p = new NodeDiemThi;
	p->maMH = maMH;
	p->diemThi = diemThi;
	if (First == NULL)
	{
		InsertFirstDT(First, maMH, diemThi);
		return;
	}
	for (s = First; s != NULL && (s->maMH.compare(maMH) < 0); t = s, s = s->next);
	if (s == First)
	{
		p->next = First;
		First = p;
	}
	else
	{
		p->next = s;
		t->next = p;
	}
}
void ClearDT(NodeDT& First)
{
	NodeDT p;
	while (First != NULL)
	{
		p = First;
		First = First->next;
		delete p;
	}
}
void SapXepDT(NodeDT& First)
{
	NodeDT p, q, pmin;
	string minMH;
	DiemThi minDT;
	for (p = First; p->next != NULL; p = p->next)
	{
		minMH = p->maMH;
		pmin = p;
		for (q = p->next; q != NULL; q = q->next)
			if (q->maMH.compare(minMH) < 0)
			{
				minMH = q->maMH;
				minDT = q->diemThi;
				pmin = q;
			}
		pmin->maMH = p->maMH;
		pmin->diemThi = p->diemThi;
		p->maMH = minMH;
		p->diemThi = minDT;
	}
}
int DemSLBODT(NodeDT First) {
	int count = 0;
	for (NodeDT i = First; i != NULL; i = i->next) {
		count++;
	}
	return count;
}

NodeDT SearchDT(NodeDT First, string maMH)
{
	NodeDT p;
	for (p = First; p != NULL; p = p->next)
		if (p->maMH == maMH) return p;
	return NULL;
}


//Mon hoc
int InsertDSMH(DanhSachMonHoc& ds, MonHoc mh)
{
	if (ds.n >= MAXMH) return -1;
	if (SearchMH(ds, mh.maMH) > -1) return -2;
	for (int i = 0; i < ds.n; i++)
	{
		if (mh.maMH < ds.dsNodeMH[i]->maMH)
		{
			for (int j = ds.n; j > i; j--)
				ds.dsNodeMH[j] = ds.dsNodeMH[j - 1];
			ds.dsNodeMH[i] = new MonHoc;
			*ds.dsNodeMH[i] = mh;
			ds.n++;
			return i;
		}
	}
	ds.dsNodeMH[ds.n] = new MonHoc;
	*ds.dsNodeMH[ds.n] = mh;
	ds.n++;
	return ds.n - 1;
}
int UpdateDSMH(DanhSachMonHoc& ds, MonHoc mh)
{
	if (ds.n == 0) return -1;
	if (SearchMH(ds, mh.maMH) == -1) return 0;
	ds.dsNodeMH[SearchMH(ds, mh.maMH)]->tenMH = mh.tenMH;
	return 1;
}
int DeleteDSMH(DanhSachMonHoc& ds, string maMH)
{
	int i = SearchMH(ds, maMH);
	if (ds.n == 0) return -1;
	if (i == -1) return 0;
	else
	{
		delete  ds.dsNodeMH[i];
		for (int j = i + 1; j < ds.n; j++)
			ds.dsNodeMH[j - 1] = ds.dsNodeMH[j];
		ds.n--;
		return 1;
	}
}
int SearchMH(DanhSachMonHoc& ds, string maMH)
{
	for (int i = 0; i < ds.n; i++)
		if (ds.dsNodeMH[i]->maMH == maMH) return i;
	return  -1;
}

//Sinh vien
string PhaiSV(int phai)
{
	if (phai == 2)
		return "Nu";
	if (phai == 1)
		return "Nam";
}
void InsertFirstSV(NodeSV& First, SinhVien sv)
{
	NodeSV p;
	p = new NodeSinhVien;
	p->sv = sv;
	p->next = First;
	First = p;
}
void KhoiTaoDSSV(DanhSachSinhVien& DSSV)
{
	DSSV.First = NULL;
}
int InsertSV(NodeSV& First, SinhVien sv)
{
	if (sv.maSV.length() == 0) return 0;
	if (SearchSV(First, sv.maSV) != NULL) return -1;
	NodeSV p, t, s;
	t = NULL;
	p = new NodeSinhVien;
	p->sv = sv;
	if (First == NULL)
	{
		InsertFirstSV(First, sv);
		return 1;
	}
	for (s = First; s != NULL && (s->sv.maSV.compare(sv.maSV) < 0); t = s, s = s->next);
	if (s == First)
	{
		p->next = First;
		First = p;
	}
	else
	{
		p->next = s;
		t->next = p;
	}
	return 1;
}
NodeSV SearchSV(NodeSV First, string maSV)
{
	NodeSV p;
	for (p = First; p != NULL; p = p->next)
		if (p->sv.maSV == maSV) return p;
	return NULL;
}
bool UpdateSV(NodeSV& First, SinhVien sv)
{
	return 0;
}
bool DeleteSV(NodeSV& First, SinhVien sv)
{
	NodeSV p = First;
	if (First == NULL) return 0;
	if (First->sv.maSV == sv.maSV)
	{
		p = First;
		First = p->next;
		delete p;
		return 1;
	}
	for (p = First; p->next != NULL && p->next->sv.maSV != sv.maSV; p = p->next);
	if (p->next != NULL)
	{
		NodeSV q = p->next;
		p->next = q->next;
		delete q;
		return 1;
	}
	return 0;
}
void ClearDSSV(NodeSV& First)
{
	NodeSV p;
	while (First != NULL)
	{
		p = First;
		First = First->next;
		delete p;
	}
}
void DuyetDSSV(NodeSV First)
{
	NodeSV p;
	int stt = 0;
	if (First == NULL) return;
	for (p = First; p != NULL; p->next);
}
void SapXepDSSV(NodeSV& First)
{
	NodeSV p, q, pmin;
	SinhVien min;

	for (p = First; p->next != NULL; p = p->next)
	{
		min = p->sv;
		pmin = p;
		for (q = p->next; q != NULL; q = q->next)
			if (q->sv.maSV.compare(min.maSV) < 0)
			{
				min = q->sv;
				pmin = q;
			}

		pmin->sv = p->sv;
		p->sv = min;
	}
}
int DemSLSV(NodeSV First)
{
	int count = 0;
	for (NodeSV i = First; i != NULL; i = i->next) {
		count++;
	}
	return count;
}
int DemSLSVDaThiMonHoc(NodeSV First, string maMH)
{
	int count = 0;
	for (NodeSV p = First; p != NULL; p = p->next) {
		if(SearchDT(p->sv.DT, maMH) != NULL) count++;
	}
	return count;
}
NodeSV SearchSVSTT(NodeSV First, int stt)
{
	int i = 0;
	NodeSV p;
	for (p = First; p != NULL; p = p->next)
	{
		if (i == stt) return p;
		i++;
	}
	return NULL;
}

//Lop
int InsertLop(DSLOP& dsLop, Lop lop)
{
	if (lop.maLop == "") return -3;
	if (dsLop.n >= MAXLOP) return -1;
	if (SearchLop(dsLop, lop.maLop) > -1) return -2;
	for (int i = 0; i < dsLop.n; i++)
	{
		if (lop.maLop < dsLop.LopArr[i].maLop)
		{
			for (int j = dsLop.n; j > i; j--)
				dsLop.LopArr[j] = dsLop.LopArr[j - 1];
			dsLop.LopArr[i] = lop;
			dsLop.n++;
			return i;
		}
	}
	dsLop.LopArr[dsLop.n] = lop;
	dsLop.n++;
	return dsLop.n - 1;
}
int UpdateLop(DSLOP& dsLop, Lop lop)
{
	if (dsLop.n == 0) return -1;
	int i = SearchLop(dsLop, lop.maLop);
	if (i < 0) return 0;
	dsLop.LopArr[i] = lop;
	return 1;
}
int DeleteLop(DSLOP& dsLop, Lop lop)
{
	if (dsLop.n == 0) return -1;
	int i = SearchLop(dsLop, lop.maLop);
	int j;
	if (i < 0 || i >= dsLop.n) return 0;
	if (dsLop.LopArr[i].dssv != NULL) return -2;
	for (j = i + 1; j < dsLop.n; j++)
		dsLop.LopArr[j - 1] = dsLop.LopArr[j];
	dsLop.n--;
	return 1;
}
int SearchLop(DSLOP dsLop, string maLop)
{
	for (int i = 0; i < dsLop.n; i++)
		if (dsLop.LopArr[i].maLop == maLop) return i;
	return -1;
}

//Cau hoi
NodeCH RotateLeftCH(NodeCH root)
{
	NodeCH p = NULL;
	if (root == NULL)
		printf("Khong the xoay trai vi cay bi rong.");
	else
		if (root->right == NULL)
			printf("Khong the xoay trai vi khong co nut con ben phai.");
		else
		{
			p = root->right;
			root->right = p->left;
			p->left = root;
		}
	return p;
}
NodeCH RotateRightCH(NodeCH ya)
{
	NodeCH s = NULL;
	if (ya == NULL)
		printf("Khong the xoay phai vi cay bi rong.");
	else
		if (ya->left == NULL)
			printf("Khong the xoay phai vi khong co nut con ben trai.");
		else
		{
			s = ya->left;
			ya->left = s->right;
			s->right = ya;
		}
	return s;
}
void InsertCauHoi(NodeCH& root, CauHoi cauHoi)
{
	if (root == NULL)
	{
		root = new NodeCauHoi;
		root->cauHoi = cauHoi;
		root->bf = 0;
		root->left = NULL;
		root->right = NULL;
		return;
	}
	NodeCH fp, p, q, fya, ya, s;
	int imbal;
	fp = NULL;   p = root;
	fya = NULL;   ya = p;
	// tim nut fp, ya va fya, nut moi them vao la nut la con cua nut fp
	while (p != NULL)
	{
		if (cauHoi.id == p->cauHoi.id)  // bi trung khoa
			return;
		if (cauHoi.id < p->cauHoi.id)
			q = p->left;
		else      	q = p->right;
		if (q != NULL)
			if (q->bf != 0) // truong hop chi so can bang cua q la 1 hay -1
			{
				fya = p;
				ya = q;
			}
		fp = p;
		p = q;
	}

	q = new NodeCauHoi;
	q->cauHoi = cauHoi;  q->bf = 0;
	q->left = NULL;  q->right = NULL;
	if (cauHoi.id < fp->cauHoi.id)
		fp->left = q;
	else      fp->right = q;

	if (cauHoi.id < ya->cauHoi.id)
		p = ya->left;
	else
		p = ya->right;
	s = p;     // s la con nut ya
	while (p != q)
	{
		if (cauHoi.id < p->cauHoi.id)
		{
			p->bf = 1;
			p = p->left;
		}
		else
		{
			p->bf = -1;
			p = p->right;
		}
	}
	// xac dinh huong lech
	if (cauHoi.id < ya->cauHoi.id)
		imbal = 1;
	else
		imbal = -1;

	if (ya->bf == 0)
	{
		ya->bf = imbal;
		return;
	}
	if (ya->bf != imbal)
	{
		ya->bf = 0;
		return;
	}

	if (s->bf == imbal)   // Truong hop xoay don
	{
		if (imbal == 1)    // xoay phai 
			p = RotateRightCH(ya);
		else              // xoay trai 
			p = RotateLeftCH(ya);
		ya->bf = 0;
		s->bf = 0;
	}
	else                 // Truong hop xoay kep
	{
		if (imbal == 1)    // xoay kep trai-phai 
		{
			ya->left = RotateLeftCH(s);
			p = RotateRightCH(ya);
		}
		else              // xoay kep phai-trai - 
		{
			ya->right = RotateRightCH(s);
			p = RotateLeftCH(ya);
		}
		if (p->bf == 0)    // truong hop p la nut moi them vao
		{
			ya->bf = 0;
			s->bf = 0;
		}
		else
			if (p->bf == imbal)
			{
				ya->bf = -imbal;
				s->bf = 0;
			}
			else
			{
				ya->bf = 0;
				s->bf = imbal;
			}
		p->bf = 0;
	}
	if (fya == NULL)
		root = p;
	else
		if (ya == fya->right)
			fya->right = p;
		else
			fya->left = p;
}

NodeCH SearchCH(NodeCH root, int x)
{
	NodeCH p = root;
	while (p != NULL && x != p->cauHoi.id)
		if (x < p->cauHoi.id)
			p = p->left;
		else
			p = p->right;
	return p;
}

void UpdateCauHoi(NodeCH& rootCH, CauHoi ch)
{
	NodeCH p = SearchCH(rootCH, ch.id);
	if (ch.id == NULL) return;
	if (p == NULL) return;
	p->cauHoi = ch;
}

void DemCH(NodeCH p, int& dem)
{
	if (p == NULL) return;
	dem++;
	if (p != NULL)
	{
		DemCH(p->left, dem);
		DemCH(p->right, dem);
	}
}

void BienDoiThanhNodeCHTheoMonHoc(NodeCH rootCH, string maMH, DSCHTMH& dsch)
{
	if (rootCH == NULL) return;
	NodeCH p = rootCH;
	if (p->cauHoi.maMH == maMH)
	{
		InsertCHVaoDSCHTMH(dsch, p->cauHoi);
	}
	if (p != NULL)
	{
		BienDoiThanhNodeCHTheoMonHoc(p->left, maMH, dsch);
		BienDoiThanhNodeCHTheoMonHoc(p->right, maMH, dsch);
	}
}
int InsertCHVaoDSCHTMH(DSCHTMH& ds, CauHoi cauHoi)
{
	if (ds.n >= MAXMH) return -1;
	if (ds.n == 0)
	{
		ds.dsch[0] = cauHoi;
		ds.n++;
		return 0;
	}
	for (int i = 0; i < ds.n; i++)
	{
		if (cauHoi.id < ds.dsch[i].id)
		{
			for (int j = ds.n; j > i; j--)
				ds.dsch[j] = ds.dsch[j - 1];
			ds.dsch[i] = cauHoi;
			ds.n++;
			return i;
		}
	}
	ds.dsch[ds.n] = cauHoi;
	ds.n++;
	return ds.n - 1;
}
int LayCauHoiThi(NodeCH rootCH, string maMH, int soCauHoi, DSCHTMH& deThi)
{
	DSCHTMH ds;
	ds.n = 0;
	int dem = 0;
	BienDoiThanhNodeCHTheoMonHoc(rootCH, maMH, ds);
	if (ds.n == 0) return 0;
	if (soCauHoi > ds.n) return -1;
	srand(time(NULL));
	while (dem < soCauHoi)
	{
		int viTri = rand() % ds.n;
		if (ds.dsch[viTri].id != -1)
		{
			deThi.dsch[dem] = ds.dsch[viTri];
			ds.dsch[viTri].id = -1;
			deThi.n++;
			dem++;
		}
	}
	return 1;
}