#include <iostream>
#include <string>
#include <vector>
#include "DanhSachLopTinChi.cpp"
#include "DanhSachSinhVien.cpp"
#include "DanhSachMonHoc.cpp"

using namespace std;

void themSV(DanhSachLopTinChi* DSLTC, DanhSachMonHoc* DSMH) {
	string mamh, mssv, tensv;
	
	float score;
	
	cout<<"Nhap ma mon hoc: ";
	getline(cin, mamh);
	
	DanhSachMonHoc* monhoc = TimKiemTheoMAMH(DSMH, mamh);
	
	if(monhoc == nullptr) {
		cout<<"Mon hoc khong ton tai.";
		return;
	}
	
	int hocKy, nhom;
	cout<<"Nhap hoc ky: ";
	cin>>hocKy;
	cout<<"Nhap nhom: ";
	cin>>nhom;
	
	
	LopTinChi* lop = DSLTC->TimLopTinChiTheoMAMH(mamh, hocKy, nhom);
	if(lop == nullptr) {
		cout<<"Khong tim thay lop tin chi!"<<endl;
		return;
	}
	
	cout<<"Nhap ma sinh vien: ";
	getline(cin, mssv);
	cout<<"Nhap ten sinh vien: ";
	cin.ignore();
	getline(cin, tensv);
	cout<<"Nhap diem: ";
	cin>>score;
	
	DangKy* sinhVien(mssv, score);
	
	
	lop->DSDK->timKiem(sinhVien);
	
	cout<<"Da them sinh vien vao lop tin chi!"<<endl;
}

void suaThongTinSinhVien(DanhSachLopTinChi* DSLTC, DanhSachMonHoc* DSMH) {
	string mamh, masv;
	
	cout<<"Nhap ma mon hoc: ";
	cin>>mamh;
	
	DanhSachMonHoc* monhoc = TimKiemTheoMAMH(DSMH, mamh);
	
	if(monhoc == nullptr) {
		cout<<"Mon hoc khong ton tai."<<endl;
		
		return;
	}
	
	int hocKy, nhom;
	
	cout<<"Nhap hoc ky: ";
	cin>>hocKy;
	
	cout<<"Nhap nhom: ";
	cin>>nhom;
	
	LopTinChi* lop = DSLTC->TimLopTinChiTheoMAMH(mamh, hocKy, nhom);
	
	if(lop == nullptr) {
		cout<<"Khong tim thay lop tin chi!"<<endl;
		return;
	}
	
	cout<<"Nhap ma sinh vien can sua: ";
	cin>>masv;
	
	DangKy* sinhVien = lop->DSDK->timKiem(masv);
	
	if(sinhVien == nullptr) {
		cout<<"Khong tim thay sinh vien!"<<endl;
		return;
	}
	
	float newScore;
	
	cout<<"Nhap diem moi: ";
	cin>>newScore;
	
	sinhVien->DIEM = newScore;
	
	cout<<"Da sua diem cho sinh vien!"<<endl;
}


void xoaSinhVienKhoiLop(DanhSachLopTinChi* DSLTC, DanhSachMonHoc* DSMH) {
	string mamh, mssv;
	
	cout<<"Nhap ma mon hoc: ";
	getline(cin, mamh);
	
	DanhSachMonHoc* monhoc = TimKiemTheoMAMH(DSMH, mamh);
	if(monhoc == nullptr) {
		cout<<"Mon hoc khong ton tai."<<endl;
		
		return;
	}
	
	int hocKy, nhom;
	cout<<"Nhap hoc ky: ";
	cin>>hocKy;
	cout<<"Nhap nhom: ";
	
	LopTinChi* lop = DSLTC->TimLopTinChiTheoMAMH(mamh, hocKy, nhom);
	
	if(lop ==nullptr) {
		cout<<"Khong tim thay lop tin chi!"<<endl;
		return;
	}
	
	cout<<"Nhap ma sinh vien can xoa: ";
	getline(cin,mssv);
	
	bool find = false;
	Node* temp = lop->DSDK->head;
	Node* prev = nullptr;
	
	while(temp != nullptr) {
		if(temp->dataDK.MASV == mssv) {
			if(prev == nullptr) {
				lop->DSDK->xoaDau();
			} else {
				prev->next = temp->next;
				delete temp;
			}
			
			find = true;
			break;
		}
		
		prev = temp;
		temp = temp->next;
	}
	
	if(find) {
		cout<<"Da xoa."<<endl;
	} else {
		cout<<"Khong tim thay sinh vien trong lop tin chi!"<<endl;
	}
}
