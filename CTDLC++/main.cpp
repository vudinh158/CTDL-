#include "DocGhiXoaFile.cpp"
#include <stack>

void inMenu();
void inCapNhat();

int main()
{
    DanhSachMonHoc *DSMH = NULL;
    DSMH = docFileDanhSachMonHoc(DSMH);
    DanhSachSinhVien *DSSV = NULL; 
    DSSV = docFileDanhSachSinhVien(DSSV);
    DanhSachLopTinChi *DSLTC(0);
    DSLTC = docFileDanhSachLopTinChi(DSLTC);
    docFileDanhSachDangKy(DSLTC);   
    
    //=== xu ly du lieu tai day ===
    menu:
    inMenu();
    int i; cin >> i;

    switch (i)
    {
        case 1: //Mo lop tin chi
        {//cau a
            capnhat:
            inCapNhat();
            int tmp; cin >> tmp;
            switch (tmp)
            {
                case 1:
                {
                    string mamh; cin.ignore(); getline(cin, mamh);
                    int hocky; cin >> hocky;
                    int nhom; cin >> nhom;

                    while (TimKiemTheoMAMH(DSMH, mamh) == NULL)
                    {
                        cout << "Mon hoc nay khong ton tai"<< endl;
                        goto capnhat;   
                    }

                    if(DSLTC->TimLopTinChiTheoMAMH(mamh, hocky, nhom) == nullptr)
                    {
                        LopTinChi lopmoi(mamh,hocky,nhom);
                        DSLTC->ThemLopTinChi(DSLTC, &lopmoi);
                    }
                    else
                    {
                        cout << "Mon hoc da ton tai vui long them lop khac" << endl;
                        goto capnhat;
                    }
                    cout << "Them thanh cong!" << endl;
                }

                    break;
                case 2:
                {
                    int maloptc; cin >> maloptc;
                    DSLTC->xoaLopTinChi(maloptc);
                    goto menu;
                    break;
                }
                case 3:
                {
                    DSLTC->inDanhSachLopTinChi(DSMH);
                    cout << endl;
                    cout << "Ban muon hieu chinh lop tin chi nao vui long nhap maloptc: ";
                    int malop; cin >> malop;
                    DSLTC->hieuChinhLopTinChi(DSLTC, malop);
                    DSLTC->inDanhSachLopTinChi(DSMH);
                    goto capnhat;
                }
                case 4:
                { 
                    goto menu;
                    break;
                }
                default:
                    cout << "Ban da nhap sai!"<<endl;
                    goto capnhat;
                    break;
            }
        //Ket thuc cau a
        }
        case 2: //In danh sach sinh vien
        {
            cout << "2. In danh sach sinh vien dang ky theo lop tin chi" << endl;
            cout << "===Danh Sanh Sinh Vien Dang Ky===" << endl;
            for (int i = 0; i < DSLTC->SoLuongLop; i++)
            {
                cout << DSLTC->DanhSach[i]->NienKhoa << " " << DSLTC->DanhSach[i]->HocKy << " " << DSLTC->DanhSach[i]->Nhom << " " << DSLTC->DanhSach[i]->MAMH << endl <<endl;
                if(DSLTC->DanhSach[i]->DSDK->head != NULL)
                    DSLTC->DanhSach[i]->DSDK->inDanhSach();
                else
                    cout << "lop khong co sinh vien dang ky!" << endl;
                cout <<endl;
            }
            goto menu;
        }
        case 3: //Cap nhat sinh vien cua mot lop
        {
			
			int tmp;
			do {
				cout << "===3. Hieu chinh sinh vien===" << endl;
				cout << "\t1. Them sinh vien\n\t2. Sua thong tin sinh vien\n\t3. Xoa sinh vien\n\t0. Quay lai!!!\n";
				cin>>tmp;
				switch(tmp) {
					case 1:
						{
							int maLop;
							
							
							
							string maSV;
							float diem;
							
							cout<<"Nhap ma sinh vien: ";
							cin>>maSV;
							
							cout<<"Nhap diem: ";
							cin>>diem;
							
							cout<<"Nhap ma lop: ";
							cin>>maLop;
							LopTinChi* lop = DSLTC->TimLopTinChi(maLop);
							if(lop != nullptr) {
								addSV(lop, maSV, diem);
							} else {
								cout<<"Khong tim thay lop tin chi!"<<endl;
							}
							break;
						}
					case 2:
						{
							suaThongTinSinhVien(DSLTC, DSMH);
							break;
						}
					case 3:
						{
							xoaSinhVienKhoiLop(DSLTC, DSMH);
							break;
						}
				}
			} while(tmp != 0);
			goto menu;
        }
        case 4: //In DSSV mot lop
        {
            	int maLop;
            	cout<<"Nhap lop can in danh sach: ";
            	cin>>maLop;
            	LopTinChi* lop = DSLTC->TimLopTinChi(maLop);
            	indanhSachSVtheoHoTen(lop);
            	goto menu;
        }
        case 5: //Nhap mon hoc
        {
        capnhatmonhoc: 
            DSMH->InDS(DSMH);
            cout << "\t===5. Cap nhat mon hoc===\nBan muon lam gi? \n\t1. Them mon\n\t2. Xoa mon\n\t3. Hieu chinh\n\t0. Thoat!\n";
            int tmp; cin >> tmp;
            switch (tmp)
            {
                case 1:
                {   
                    MH MHmoi;
                    
                    string mamh, tenmh;
                    cout <<"Nhap MAMH: ";
                    cin.ignore(); getline(cin, mamh);
                    cout << "Nhap tenmh; ";
                    cin.ignore(); getline(cin, tenmh);
                    int sotcll, sotcth;
                    cout << "Nhap sotcll: ";
                    cin >> sotcll;
                    cout << "Nhap sotcth: ";
                    cin >> sotcth;

                    MHmoi.MAMH = mamh;
                    MHmoi.TENMH = tenmh;
                    MHmoi.STCLT = sotcll;
                    MHmoi.STCTH = sotcth;

                    DSMH = insertDanhSachMonHoc(DSMH, MHmoi);

                    cout <<"Them Lop Thanh Cong!" << endl;

                    DSMH->InDS(DSMH);

                    goto capnhatmonhoc;
                    break;
                }
                case 2:
                {
                    string mamh; cin.ignore(); getline(cin, mamh);
                    for(int i = 1; i < 4; i++)
                        for(int j = 1; j < 11; j++)
                            if(DSLTC->TimLopTinChiTheoMAMH(mamh,i,j) != NULL)
                            {
                                cout << "Mon hoc nay da co lop tin chi hay chinh lop tc truoc khi xoa! ";
                                goto capnhatmonhoc;
                            }
                    DSMH = deleteNode(DSMH,mamh);
                    DSMH->InDS(DSMH);
                    goto capnhatmonhoc;
                }
                case 3:
                {
                    cout << "Nhap mamh can hieu chinh: ";
                    string mamh; cin.ignore(); getline(cin, mamh);
                    MH mhhc = TimKiemTheoMAMH(DSMH, mamh)->data;
                    cout << mhhc.MAMH << " " << mhhc.TENMH << " " << mhhc.STCLT << " " << mhhc.STCTH << endl;
                    string mmh, tenmh;
                    int stclt, stcth;
                    cout <<"Ma mon hoc: "; cin.ignore(); getline(cin, mmh);
                    cout << "Ten mon hoc: "; cin.ignore(); getline(cin, tenmh);
                    cout << "So tin chi ly thuyet: "; cin >> stclt;
                    cout << "So tin chi thuc hanh: "; cin >> stcth;
                    if(mmh != "") mhhc.MAMH = mamh;
                    if(tenmh != "") mhhc.TENMH = tenmh;
                    if(stclt != 0) mhhc.STCLT = stclt;
                    if(stcth != 0) mhhc.STCTH = stcth;

                    DSMH = insertDanhSachMonHoc(DSMH, mhhc);
                    goto capnhatmonhoc;

                }
                case 0:
                    goto menu;
                default:
                    cout << "Ban dan nhap sai!"<< endl;
                    goto capnhatmonhoc;
                    break;
                }
            break;
        }
        case 6: //In danh sach mon hoc
        {
            cout << "\t1. In theo mamh:\n\t2. In theo tenmh: \n\t0. Thoat! \n";
            int i; cin >> i;
            switch (i)
            {
                case 1:
                {
                    DSMH->InDS(DSMH);
                    goto menu;
                    break;
                }
                case 2:
                {
                    DanhSachMonHoc* DSMHT = NULL;
                    DanhSachMonHoc* tmp = DSMH;

                    stack<DanhSachMonHoc*> s;
                    while (tmp != nullptr || !s.empty()) 
                    {
                        while (tmp != nullptr) 
                        {
                            DSMHT = insertDanhSachMonHocT(DSMHT, tmp->data);
                            s.push(tmp);
                            tmp = tmp->leftChild;
                        }
                        tmp = s.top();
                        s.pop();
                        tmp = tmp->rightChild;              
                    }

                    DSMHT->InDS(DSMHT);
                    delete(DSMHT);
                    delete(tmp);
                    goto menu;
                }
            }
        }
        case 7: //Dang ky lop tin chi
        {
            cout << "===Dang ky lop tin chi===";

            nhapmasinhvien:
            cout << "\nNhap ma sinh vien: ";
            string masv; cin.ignore(); getline(cin, masv);
            SinhVien* tmp = DSSV->timKiemTheoMaSV(DSSV,masv);
            
            if(tmp  == NULL)
            {
                cout <<"Sinh Vien Khong Ton Tai\n";
                goto nhapmasinhvien;
            }

            cout << tmp->MALOP << " " << tmp->HO << " "<< tmp->TEN << " " << tmp->PHAI << "\nNhap nien khoa: ";
            int nienkhoa, hocky; 
            cin >> nienkhoa;
            cout << "Hoc Ky: "; cin >> hocky;
            DanhSachLopTinChi DS;
            DS = DSLTC->locDanhSach(DSLTC, nienkhoa, hocky);
            if(DS.SoLuongLop != 0)
                DS.inDanhSachLopTinChi(DSMH);
            else  
                cout << "Khong co lop nao!\n";
            
        }
        case 0: //Thoat
        {
            goto thoat;
            break;
        }
        default:
            cout << "Ban da nhap sai!" << endl;
            goto menu;
            break;
    }

    //=== ket thuc xu ly du lieu ===
    thoat:
    xoaDuLieuFileDanhSachMonHoc();
    ghiFileDanhSachMonHoc(DSMH);
    xoaDuLieuFileDanhSachSinhVien();
    ghiFileDanhSachSinhVien(DSSV);
    xoaDuLieuFileDanhSachLopTinChi();
    ghiFileDanhSachLopTinChi(DSLTC);
    xoaDuLieuFileDanhSachDangKy();
    ghiFileDanhSachDangKy(DSLTC);
    delete DSMH;
    delete DSSV;
    delete DSLTC;
    return 0;
}

void inMenu()
{
    cout << "===Menu===" << endl
        << "1. Cap Nhat Lop Tin Chi." << endl
        << "2. In danh sach sinh vien dang ky theo lop tin chi" << endl
        << "3. Nhap sinh vien" << endl
        << "4. In danh sach sinh vien theo lop tin chi." << endl
        << "5. Cap Nhat Mon Hoc." << endl
        << "6. In danh sach mon hoc." << endl
        << "7. Dang ky lop tin chi." << endl
        << "0. Thoat! " << endl; 
    return;
}

void inCapNhat()
{
    cout << "1. Cap Nhat Lop Tin Chi." << endl
                << "\t1. Them lop tin chi" << endl
                << "\t2. Xoa lop tin chi" << endl
                << "\t3. Hieu chinh" << endl
                << "\t4. Den menu" <<endl;
    return;
}
