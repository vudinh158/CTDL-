#pragma once
#include <iostream>
using namespace std;

struct MH
{
	string MAMH;
	string TENMH;
	int STCLT;
	int STCTH;
};

struct DanhSachMonHoc
{
	MH data;
	struct DanhSachMonHoc* leftChild;
	struct DanhSachMonHoc* rightChild;
	int height;
	void InDS(DanhSachMonHoc* root);
};

int max(int a, int b);

int height(struct DanhSachMonHoc* N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

struct DanhSachMonHoc* newNode(MH data)
{
	DanhSachMonHoc* node = new DanhSachMonHoc;
	node->data = data;
	node->leftChild = NULL;
	node->rightChild = NULL;
	node->height = 1;
	return (node);
}

struct DanhSachMonHoc* rightRotate(struct DanhSachMonHoc* y)
{
	struct DanhSachMonHoc* x = y->leftChild;
	struct DanhSachMonHoc* T2 = x->rightChild;
	x->rightChild = y;
	y->leftChild = T2;
	y->height = max(height(y->leftChild), height(y->rightChild)) + 1;
	x->height = max(height(x->leftChild), height(x->rightChild)) + 1;
	return x;
}

struct DanhSachMonHoc* leftRotate(struct DanhSachMonHoc* x)
{
	struct DanhSachMonHoc* y = x->rightChild;
	struct DanhSachMonHoc* T2 = y->leftChild;
	y->leftChild = x;
	x->rightChild = T2;
	x->height = max(height(x->leftChild), height(x->rightChild)) + 1;
	y->height = max(height(y->leftChild), height(y->rightChild)) + 1;
	return y;
}

int getBalance(struct DanhSachMonHoc* N)
{
	if (N == NULL)
		return 0;
	return height(N->leftChild) - height(N->rightChild);
}

DanhSachMonHoc* insertDanhSachMonHoc(DanhSachMonHoc* node, MH data)
{
	if (node == NULL)
		return (newNode(data));

	if (data.MAMH < node->data.MAMH)
		node->leftChild = insertDanhSachMonHoc(node->leftChild, data);

	else if (data.MAMH > node->data.MAMH)
		node->rightChild = insertDanhSachMonHoc(node->rightChild, data);

	else
		return node;

	node->height = 1 + max(height(node->leftChild), height(node->rightChild));

	int balance = getBalance(node);
	if (balance > 1 && data.MAMH < node->leftChild->data.MAMH)
		return rightRotate(node);

	if (balance < -1 && data.MAMH > node->rightChild->data.MAMH)
		return leftRotate(node);

	if (balance > 1 && data.MAMH > node->leftChild->data.MAMH)
	{
		node->leftChild = leftRotate(node->leftChild);
		return rightRotate(node);

	}

	if (balance < -1 && data.MAMH < node->rightChild->data.MAMH)
	{
		node->rightChild = rightRotate(node->rightChild);
		return leftRotate(node);
	}

	return node;
}

DanhSachMonHoc* insertDanhSachMonHocT(DanhSachMonHoc* node, MH data)
{
	if (node == NULL)
		return (newNode(data));

	if (data.TENMH < node->data.TENMH)
		node->leftChild = insertDanhSachMonHocT(node->leftChild, data);

	else if (data.TENMH > node->data.TENMH)
		node->rightChild = insertDanhSachMonHocT(node->rightChild, data);

	else
		return node;

	node->height = 1 + max(height(node->leftChild), height(node->rightChild));

	int balance = getBalance(node);
	if (balance > 1 && data.TENMH < node->leftChild->data.TENMH)
		return rightRotate(node);

	if (balance < -1 && data.TENMH > node->rightChild->data.TENMH)
		return leftRotate(node);

	if (balance > 1 && data.TENMH > node->leftChild->data.TENMH)
	{
		node->leftChild = leftRotate(node->leftChild);
		return rightRotate(node);

	}

	if (balance < -1 && data.TENMH < node->rightChild->data.TENMH)
	{
		node->rightChild = rightRotate(node->rightChild);
		return leftRotate(node);
	}

	return node;
}

struct DanhSachMonHoc* minValueNode(struct DanhSachMonHoc* node)
{
	struct DanhSachMonHoc* current = node;
	while (current->leftChild != NULL)
		current = current->leftChild;

	return current;
}

DanhSachMonHoc* TimKiemTheoMAMH(DanhSachMonHoc* root, string MAMH) 
{
  	if (root == nullptr) 
	{
    	return nullptr;
  	}

  	if (MAMH == root->data.MAMH) 
	{
    	return root;
  	} 
	else if (MAMH < root->data.MAMH) 
	{
    	return TimKiemTheoMAMH(root->leftChild, MAMH);
  	} 
	else 
	{
    	return TimKiemTheoMAMH(root->rightChild, MAMH);
  	}
}

void DanhSachMonHoc::InDS(DanhSachMonHoc* root)
{
	if(root != NULL)
	{
		InDS(root->leftChild);
		cout <<root->data.MAMH << " " << root->data.TENMH << " " << root->data.STCLT << " " << root->data.STCTH << endl;
		InDS(root->rightChild);
	}
}

DanhSachMonHoc* deleteNode(DanhSachMonHoc* node, string MAMH) 
{
  if (node == nullptr) 
  {
    return nullptr;
  }

  if (MAMH < node->data.MAMH) 
  {
    node->leftChild = deleteNode(node->leftChild, MAMH);
  } 
  else if (MAMH > node->data.MAMH) {
    node->rightChild = deleteNode(node->rightChild, MAMH);
  } 
  else
  {
    if (node->leftChild == nullptr) 
	{
      DanhSachMonHoc* temp = node->rightChild;
      delete node;
      return temp;
    } 
	else if (node->rightChild == nullptr) 
	{
      DanhSachMonHoc* temp = node->leftChild;
      delete node;
      return temp;
    }

    DanhSachMonHoc* temp = minValueNode(node->rightChild);
    node->data = temp->data;
    node->rightChild = deleteNode(node->rightChild, temp->data.MAMH);
  }

  int balance = getBalance(node);

  if (balance > 1 && getBalance(node->leftChild) >= 0) 
  {
    return rightRotate(node);
  }

  if (balance > 1 && getBalance(node->leftChild) < 0) 
  {
    node->leftChild = leftRotate(node->leftChild);
    return rightRotate(node);
  }

  if (balance < -1 && getBalance(node->rightChild) <= 0) 
  {
    return leftRotate(node);
  }

  if (balance < -1 && getBalance(node->rightChild) > 0) 
  {
    node->rightChild = rightRotate(node->rightChild);
    return leftRotate(node);
  }

  return node;
}
