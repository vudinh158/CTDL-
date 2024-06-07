#pragma once
#include <iostream>
#include <string>


using namespace std;

struct SinhVien
{
	string MASV;
	string HO;
	string TEN;
	string PHAI;
	string MALOP;
	int year;
};

struct DanhSachSinhVien
{
	struct Node
	{
		SinhVien sv;
		Node* next;
		Node()
		{
			next = nullptr;
		}
	};

	void AddNodeAtTail(Node* temp, SinhVien newSv)
	{
		Node* newNode = new Node;
		newNode->sv = temp->sv;
		temp->sv = newSv;
		newNode->next = temp->next;
		temp->next = newNode;
		soLuong++;
	}

	Node* head;
	int soLuong;

	DanhSachSinhVien()
	{
		head = new Node;
		soLuong = 0;
	}

	void Add(SinhVien newSv)
	{
		if (soLuong == 0)
		{
			head->sv = newSv;
			soLuong++;
			return;
		}

		Node* temp = head;
		Node* tempp = NULL;
		
		while (temp !=nullptr)
		{
			if (CheckForInsert(newSv, temp->sv))
			{
				AddNodeAtTail(temp, newSv);
				return;
			}
			tempp = temp;
			temp = temp->next;
		}
		Node* newNode = new Node();
		newNode->sv = newSv;
		tempp->next = newNode;
		soLuong++;
	}

	bool CheckForInsert(SinhVien sv1, SinhVien sv2)
	{
		if (sv1.MALOP < sv2.MALOP)
			return true;
		if (sv1.MALOP > sv2.MALOP) return false;

		if (sv1.TEN[0] < sv2.TEN[0])
			return true;
		if (sv1.TEN[0] >sv2.TEN[0]) return false;		
		if (sv1.HO < sv2.HO)
			return true;
			
		return false;
	}

	void InDSSV()
	{
		Node* temp = head;
		for (int i = 0; i < soLuong; i++)
		{
			SinhVien svTemp = temp->sv;
			cout << svTemp.MALOP << " " << svTemp.HO << " " << svTemp.TEN << endl;
			temp = temp->next;
		}
	}

	void DeleteFirstNode() 
	{
    if (head == nullptr) {
        return;
    }

    Node* temp = head;

    head = head->next;

    delete temp;

    soLuong--;
	return;
	}

	SinhVien* timKiemTheoMaSV(DanhSachSinhVien* ds, string MASV)
	{
		Node* tmp = ds->head;
		while (tmp != NULL)
		{
			if(tmp->sv.MASV == MASV)
			{
				return &(tmp->sv);
			}
			tmp = tmp->next;
		}
		return NULL;		
	}

};

