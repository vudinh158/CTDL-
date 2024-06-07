#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "DanhSachLopTinChi.cpp"
#include "DanhSachSinhVien.cpp"
#include "DanhSachMonHoc.cpp"
#include "DanhSachDangKy.cpp"

using namespace std;


///////////////////////////// Start fix //////////////////////////////




void addSV(LopTinChi* lop, string maSV, float diem) {
	if(lop == nullptr) {
		cout<<"Khong tim thay lop tin chi!"<<endl;
		return;
	}
	
	DangKy sinhVien(maSV, diem);
	
	lop->DSDK->themCuoi(sinhVien);
	
	cout<<"Da them sinh vien vao danh sach dang ky cua lop "<<lop->MALOPTC<<" - "<<lop->MAMH<<endl;
}




///////////////////////////// End fix //////////////////////////////




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
	cin.ignore();
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
	cin>>nhom;
	
	LopTinChi* lop = DSLTC->TimLopTinChiTheoMAMH(mamh, hocKy, nhom);
	
	if(lop ==nullptr) {
		cout<<"Khong tim thay lop tin chi!"<<endl;
		return;
	}
	
	cout<<"Nhap ma sinh vien can xoa: ";
	cin.ignore();
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


////////////////in danh sach sinh vien theo thu tu/////////////////////////

void swapSV(DangKy* sv1, DangKy* sv2) {
	DangKy temp = *sv1;
	*sv1 = *sv2;
	*sv2 = temp;
}

bool compareSV(const string& tenHo1, const string& tenHo2) {
	return tenHo1 < tenHo2;
}

void sortSV(DangKy* dsSV[], int soluong) {
	for(int i = 0; i < soluong - 1; i++) {
		int minIndex = i;
		for(int j = i + 1; j < soluong; j++) {
			if(compareSV(dsSV[j]->MASV, dsSV[minIndex]->MASV)) {
				minIndex = j;
			}
		}
		if(minIndex != i) {
			swapSV(dsSV[i], dsSV[minIndex]);
		}
	}
}

void indanhSachSVtheoHoTen(LopTinChi* lop) {
	if(lop == nullptr) {
		cout<<"Khong tim thay lop!!!!!!!\n";
		return;
	}
	cout<<"Danh sach cua lop "<<lop->MALOPTC<<" - "<<lop->MAMH<<": "<<endl;
	
	int soLuongSV = lop->DSDK->soLuong;
	
	DangKy* dsSinhVien[soLuongSV];
	
	Node* temp = lop->DSDK->head;
	
	for(int i = 0; i < soLuongSV; i++) {
		dsSinhVien[i] = &(temp->dataDK);
		temp = temp->next;
	}
	
	sortSV(dsSinhVien, soLuongSV);
	
	for(int i = 0; i < soLuongSV; i++) {
		cout<<dsSinhVien[i]->MASV<<" "<<dsSinhVien[i]->DIEM<<" "<<dsSinhVien[i]->huyDangKy<<endl;
	}
}
