#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "DanhSachDangKy.cpp"
#include "DanhSachLopTinChi.cpp"
#include "DanhSachSinhVien.cpp"
#include "HienChinhSinhVien.cpp"


DanhSachMonHoc* docFileDanhSachMonHoc(DanhSachMonHoc* DSMH)
{
    ifstream infile;
    infile.open("data\\danhSachMonHoc.txt", ios::in);
    string data;
    if(!infile)
    {
        cout << "Khong Tim Thay File" << endl;
        return DSMH;
    }
    while (infile.good())
    {
        MH mh;
        getline(infile, data);
        if(data.size() == 0){break;}
        stringstream ss(data);
        string tmp;
        int i = 0;
        vector<string> chuoi;

        while (getline(ss,tmp,'@'))
            chuoi.push_back(tmp);
            
        mh.MAMH = chuoi[0];
        mh.TENMH = chuoi[1];
        mh.STCLT = stoi(chuoi[2]);
        mh.STCTH = stoi(chuoi[3]);

        DSMH = insertDanhSachMonHoc(DSMH ,mh);
    }
    infile.close();

    return DSMH;
}

void xoaDuLieuFileDanhSachMonHoc()
{
    ofstream file("data\\danhSachMonHoc.txt", std::ios::out);
    file << "";
    file.close();
    return;
}

DanhSachSinhVien* docFileDanhSachSinhVien(DanhSachSinhVien* DSSV)
{
    DSSV = new DanhSachSinhVien();
    ifstream infile;
    infile.open("data\\danhSachSinhVien.txt", ios::in);
    string data;
    if(!infile)
    {
        cout << "Khong Tim Thay File" << endl;
        return DSSV;
    }
    while (infile.good())
    {
        SinhVien sv;
        getline(infile, data);
        if(data.size() == 0){break;}
        stringstream ss(data);
        string tmp;
        vector<string> chuoi;

        while (getline(ss,tmp,'@'))
            chuoi.push_back(tmp);

        sv.MASV = chuoi[0];
        sv.HO = chuoi[1];
        sv.TEN = chuoi[2];
        sv.PHAI = chuoi[3];
        sv.MALOP = chuoi[4];
        sv.year = stoi(chuoi[5]);
        DSSV->Add(sv);
    }
    infile.close();
    
    return DSSV;
}   

void xoaDuLieuFileDanhSachSinhVien()
{ 
    ofstream file("data\\danhSachSinhVien.txt", std::ios::out);
    file << "";
    file.close();
    return;
}

DanhSachLopTinChi* docFileDanhSachLopTinChi(DanhSachLopTinChi* DSLTC)
{
    DSLTC = new DanhSachLopTinChi();
    ifstream infile;
    infile.open("data\\danhSachLopTinChi.txt", ios::in);
    string data;
    if(!infile)
    {
        cout << "Khong Tim Thay File" << endl;
        return DSLTC;
    }

    while (infile.good())
    {
        LopTinChi loptc;
        getline(infile, data);
        if(data.size() == 0){break;}
        stringstream ss(data);
        string tmp;
        vector<string> chuoi;

        while (getline(ss,tmp,'@'))
            chuoi.push_back(tmp);

        loptc.MALOPTC = stoi(chuoi[0]);
        loptc.MAMH = chuoi[1];
        loptc.NienKhoa = stoi(chuoi[2]);
        loptc.HocKy = stoi(chuoi[3]);
        loptc.Nhom = stoi(chuoi[4]);
        loptc.SoSVMin = stoi(chuoi[5]);
        loptc.SoSVMax = stoi(chuoi[6]);
        loptc.HuyLop = 0;

        DSLTC->ThemLopTinChi(DSLTC, &loptc);
        
    }
    infile.close();

    return DSLTC;
}

void xoaDuLieuFileDanhSachLopTinChi()
{  
    ofstream file("data\\danhSachLopTinChi.txt", std::ios::out);
    file << "";
    file.close();
}

void docFileDanhSachDangKy(DanhSachLopTinChi* DSLTC)
{
    ifstream infile;
    infile.open("data\\danhSachDangKy.txt", ios::in);
    string data;
    if(!infile)
    {
        cout << "Khong Tim Thay File" << endl;
        return;
    }
    while (infile.good())
    {
        DangKy dk;
        getline(infile, data);
        if(data.size() == 0){break;}
        stringstream ss(data);
        string tmp;
        vector<string> chuoi;
        
        while (getline(ss,tmp,'@'))
            chuoi.push_back(tmp);
        
        LopTinChi* loptinchi = DSLTC->TimLopTinChi(stoi(chuoi[0]));
        
        dk.MASV = chuoi[1];
        dk.DIEM = stoi(chuoi[2]);
        dk.huyDangKy = 0;
        
        loptinchi->DSDK->themCuoi(dk);
    }
    
    infile.close();    

    return;    
}

void xoaDuLieuFileDanhSachDangKy()
{ 
    ofstream file("data\\danhSachDangKy.txt", std::ios::out);
    file << "";
    file.close();
    return;
}

void ghiFileDanhSachMonHoc(DanhSachMonHoc *DSMH)
{
    ofstream outfile;
    outfile.open("data\\danhSachMonHoc.txt", ios::app);
    if(DSMH != NULL)
    {
        string tmp = DSMH->data.MAMH + "@" + DSMH->data.TENMH + "@" + to_string(DSMH->data.STCLT) + "@" +to_string(DSMH->data.STCTH) + "@";
        outfile << tmp << endl;
        ghiFileDanhSachMonHoc(DSMH->leftChild);
        ghiFileDanhSachMonHoc(DSMH->rightChild); 
    }
    outfile.close();
    return;
}

void ghiFileDanhSachSinhVien(DanhSachSinhVien *DSSV)
{
    ofstream outfile;
    outfile.open("data\\danhSachSinhVien.txt", ios::app);
    if(DSSV->head != nullptr )
    {
        string tmp = DSSV->head->sv.MASV + "@" + DSSV->head->sv.HO + "@" + DSSV->head->sv.TEN + "@" + DSSV->head->sv.PHAI + "@" + DSSV->head->sv.MALOP + "@" + to_string(DSSV->head->sv.year) + "@";

        outfile << tmp << endl;
        DSSV->head = DSSV->head->next;

        ghiFileDanhSachSinhVien(DSSV);

    }

    outfile.close();
    return;

}

void ghiFileDanhSachLopTinChi(DanhSachLopTinChi* DSLTC)
{
    ofstream outfile;
    outfile.open("data\\danhSachLopTinChi.txt", ios::app);

    for(int i = 0; i < DSLTC->SoLuongLop; i++)
    {
        bool check = DSLTC->DanhSach[i]->HuyLop;
        if(!check)
        {
            string tmp = to_string(DSLTC->DanhSach[i]->MALOPTC) + "@" + DSLTC->DanhSach[i]->MAMH + "@" + to_string(DSLTC->DanhSach[i]->NienKhoa) + "@" + to_string(DSLTC->DanhSach[i]->HocKy) + "@" + to_string(DSLTC->DanhSach[i]->Nhom) + "@" + to_string(DSLTC->DanhSach[i]->SoSVMin) + "@" + to_string(DSLTC->DanhSach[i]->SoSVMax) + "@";
            outfile << tmp << endl;
        }
    }
    
    outfile.close();
    return;
}

void ghiFileDanhSachDangKy(DanhSachLopTinChi* DSLTC)
{
    ofstream outfile;
    outfile.open("data\\danhSachDangKy.txt", ios::app);

    for(int i = 0; i < DSLTC->SoLuongLop; i++)
    {
        if(DSLTC->DanhSach[i]->HuyLop == 0)
        {
            while(DSLTC->DanhSach[i]->DSDK->head != nullptr)
            {
                DangKy svdk = DSLTC->DanhSach[i]->DSDK->head->dataDK;

                string tmp = to_string(DSLTC->DanhSach[i]->MALOPTC) +"@"+ svdk.MASV + "@" + to_string(svdk.DIEM) + "@";

                outfile << tmp << endl;
                DSLTC->DanhSach[i]->DSDK->head = DSLTC->DanhSach[i]->DSDK->head->next;
                
            }
        }
    } 

    outfile.close();
    return;
}
