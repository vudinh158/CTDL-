#pragma once
#include <iostream>
#include <string>
#include "DanhSachDangKy.cpp"
#include "DanhSachMonHoc.cpp"

using namespace std;

int MALOP = 0;// khoi tao tam sau cho doc file data

struct LopTinChi
{
	int MALOPTC;
	string MAMH; 
	int NienKhoa; 
	int HocKy; 
	int Nhom;  
	int SoSVMin;
	int SoSVMax; 
	bool HuyLop;
	DanhSachDangKy* DSDK;

	LopTinChi(){}
	LopTinChi(string MAMH, int HocKy, int Nhom)
	{
		this->MALOPTC = 0;
		this->MAMH = MAMH;
		this->HocKy = HocKy;
		this->Nhom = Nhom;
		this->SoSVMin = 10;
		this->SoSVMax = 100;
		DSDK = new DanhSachDangKy;
	}
	LopTinChi(string MAMH,int NienKhoa, int HocKy, int Nhom, int max, int min)
	{
		this->MALOPTC = 0;
		this->MAMH = MAMH;
		this->NienKhoa = NienKhoa;
		this->HocKy = HocKy;
		this->Nhom = Nhom;
		this->SoSVMin = min;
		this->SoSVMax = max;
		DSDK = new DanhSachDangKy;
	}
};

struct DanhSachLopTinChi
{
	LopTinChi* DanhSach[10000]; 
	int SoLuongLop; 
	DanhSachLopTinChi()
	{
		this->SoLuongLop = 0;
	}

	DanhSachLopTinChi(int so)
	{
		this->SoLuongLop = so;
	}

	bool ThemLopTinChi(DanhSachLopTinChi* DSLTC, LopTinChi* lop) 
	{
		if (DSLTC->SoLuongLop >= 10000) 
			return false;

		LopTinChi* lopMoi = new LopTinChi(lop->MAMH,lop->NienKhoa, lop->HocKy, lop->Nhom, lop->SoSVMax, lop->SoSVMin);
		if (lop->MALOPTC != 0) 
			lopMoi->MALOPTC = lop->MALOPTC;
		else 
			lopMoi->MALOPTC = ++MALOP;

		int tmp = DSLTC->SoLuongLop;
		DSLTC->DanhSach[tmp] = lopMoi;

		(DSLTC->SoLuongLop)++;

		return true;
	}

	LopTinChi* TimLopTinChi(int MALOPTC)
	{
    int left = 0, right = SoLuongLop - 1;

    while (left <= right) 
	{
        int mid = (left + right) / 2;

        if (MALOPTC == DanhSach[mid]->MALOPTC) {
            return DanhSach[mid];
        } else if (MALOPTC < DanhSach[mid]->MALOPTC) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return nullptr;
	}	

	LopTinChi* TimLopTinChiTheoMAMH(string MAMH, int HocKy, int Nhom) 
	{
   		for (int i = 0; i < SoLuongLop; ++i) 
		{	
        	if (MAMH == DanhSach[i]->MAMH && HocKy == DanhSach[i]->HocKy && Nhom == DanhSach[i]->Nhom)
        		return DanhSach[i];
    	}
    	return nullptr;
	}

	void inDanhSachLopTinChi(DanhSachMonHoc *root)
	{
		for(int i = 0; i < SoLuongLop; i++)
		{
			cout << DanhSach[i]->MAMH <<" "<< TimKiemTheoMAMH(root,DanhSach[i]->MAMH)->data.TENMH << " " <<DanhSach[i]->Nhom <<" "<< DanhSach[i]->DSDK->soLuong << " "<< DanhSach[i]->SoSVMax - DanhSach[i]->DSDK->soLuong << endl;
		}
		return;
	}

	void xoaLopTinChi(int MALOPTC)
	{
		LopTinChi* lop = TimLopTinChi(MALOPTC);
		if(lop == nullptr)
		{
			cout << "Lop Tin Chi Khong Ton Tai" << endl;
			return;
		}
		else
		{
			bool check = false;
			int left = 0, right = SoLuongLop - 1;

    		while (left <= right) 
			{
        		int mid = (left + right) / 2;
        		if (MALOPTC == DanhSach[mid]->MALOPTC) 
				{	
					delete(DanhSach[mid]->DSDK);
					
					int j = mid;
					while(j < SoLuongLop - 1)
					{
					DanhSach[j] = DanhSach[j+1];
					j++;
					}

					delete(DanhSach[mid]);
					DanhSach[j] = nullptr;

					check = true;
					break;
        		} 
				else if (MALOPTC < DanhSach[mid]->MALOPTC) 
				{
            		right = mid - 1;
        		} 
				else 
				{
            		left = mid + 1;
        		}
			}
			if(check)
				cout << "Xoa Lop Thanh Cong"<< endl;
			SoLuongLop--;
			return;
		}
	}

	void hieuChinhLopTinChi(DanhSachLopTinChi* DSLTC, int malop)
	{
		LopTinChi* lop1 = DSLTC->TimLopTinChi(malop);
        DSLTC->xoaLopTinChi(malop);
        if(lop1 != NULL)
        {
            cout << lop1->MALOPTC << " " << lop1->MAMH << " " << lop1->NienKhoa<< endl;
			cout << "\tBan muon chi gi?\n\t1. Thay doi mon hoc\n\t2. So luong max min\n\t3. Thoat!\n";
			int i; cin >> i;
			switch (i)
			{
				case 1:
				{
					cout <<"Nhap ma mon hoc muon doi: ";
					string mamh; cin.ignore(); getline(cin, mamh);
					lop1->MAMH = mamh;
					DSLTC->ThemLopTinChi(DSLTC, lop1);
					break;
				}
				case 2:
				{
					cout << lop1->SoSVMax << " " << lop1->SoSVMin << endl;
					cout <<"Theo thu tu nhap max min: ";
					int max, min; cin >> max; cin >> min;
					lop1->SoSVMax = max;
					lop1->SoSVMin = min;
					cout << lop1->SoSVMax << " " << lop1->SoSVMin << endl;
					DSLTC->ThemLopTinChi(DSLTC, lop1);
					break;
				}
				case 3:
				{
					DSLTC->ThemLopTinChi(DSLTC, lop1);
					return;
				}
				default:
					break;
			}
        }

		return;
	}

	DanhSachLopTinChi locDanhSach(DanhSachLopTinChi* DS, int NK, int HK)
	{
		DanhSachLopTinChi DStmp(0);
		for(int i = 0; i < DS->SoLuongLop; i++)
		{
			LopTinChi lop = *(DS->DanhSach[i]);
			if(lop.NienKhoa == NK && lop.HocKy == HK)
				DStmp.ThemLopTinChi(&DStmp, &lop);	
			else
				continue;
		}
		return DStmp;
	}
};

