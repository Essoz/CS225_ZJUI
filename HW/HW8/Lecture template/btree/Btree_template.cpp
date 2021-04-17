/*
*Copyright@Naveen
*6:24:49 PM
*Btree.cpp
*
*/
#include <iostream>
#include <stdio.h>

using namespace std;
/* In BtreeNode class 
   We just store the key and we do not store value 
   if you want, you can modify the class definition of Btree Node.
*/
class BtreeNode
{
	int *a;
	BtreeNode **C;
	int n;
	int t;
	bool leaf;
public:
	BtreeNode(int t,bool leaf)
    {
		this->t = t;
		this->leaf = leaf;
		a = new int[2*t-1];
		C = new BtreeNode*[2*t];
		n = 0;
    }
	int findId(int k);
	void remove(int k);
	void removeFromLeaf(int id);
	void removeFromNonLeaf(int id);
	void borrowFromPrev(int id);
	void borrowFromSucc(int id);
	int findSucc(int id);
	int findPrec(int id);
	void merge(int id);
	void fill(int id);
	void traverse();
	BtreeNode *search(int k);
	void insertNonFull(int k);
	void splitChild(int i,BtreeNode *y);

friend class Btree;
};

class Btree
{
	BtreeNode* root;
	int t;
public:
	Btree(int t)
    {
		root = new BtreeNode(t,true);
		this->t = t;
    }
	void insert(int k);
	void remove(int k);
    int find_max();
    int find_min();
	void traverse()
	{
		if(root == NULL) return;
		else
			root->traverse();
	}
	BtreeNode *search(int k)
	{
		return (root==NULL) ? NULL : root->search(k);
	}
};

int BtreeNode :: findId(int k)
{
	int i ;
	for(i=0;i<n && a[i] < k ;i++);
	return i;

}
void BtreeNode :: remove(int k)
{
	int id = findId(k);

	if(id < n && a[id] == k)
	{
		if(leaf)
			removeFromLeaf(id);
		else
			removeFromNonLeaf(id);
	}
	else
	{
		if(leaf)
		{
		cout<<"Element does not exist"<<endl;
		return;
		}
		else
		{
			bool flag;
			if(n == id)
				flag = true;
			else
				flag = false;

			if(C[id]->t < t)
				fill(id);

			if(flag && id > n)
				C[id-1]->remove(k);
			else
				C[id]->remove(k);
		}


	}


}

void BtreeNode::removeFromLeaf(int id)
{
	for(int i = id+1;i < n;i++)
	{
		a[i-1] = a[i];
	}
	n--;
}

void BtreeNode :: removeFromNonLeaf(int id)
{
	if(C[id]->t >= t)
	{
		a[id]=findPrec(id);
		C[id]->remove(a[id]);
	}
	else if(C[id+1]->t >= t)
	{
		a[id]=findSucc(id);
		C[id+1]->remove(a[id]);
	}
	else
	{
		int d = a[id];
		merge(id);
		C[id]->remove(d);
	}
}

int BtreeNode :: findPrec(int id)
{
	BtreeNode *curr = C[id];
	while(!curr->leaf)
		curr = curr->C[curr->n];
	return curr->a[curr->n-1];
}

int BtreeNode :: findSucc(int id)
{
	BtreeNode *curr = C[id+1];
	while(!curr->leaf)
		curr = curr->C[0];
	return curr->a[0];
}

void BtreeNode :: fill(int id)
{
	if(id!=0 && C[id-1]->n>=t)
		borrowFromPrev(id);
	else if(id!=n && C[id+1]->n>=t)
		borrowFromSucc(id);
	else
	{
		if(id!=n)
			merge(id);
		else
			merge(id-1);
	}

}

void BtreeNode :: borrowFromPrev(int id)
{
	BtreeNode *child = C[id];
	BtreeNode *sibling = C[id-1];

	for(int i = child->n-1;i >=0 ;i--)
		child->a[i+1] = child->a[i];

	if(!child->leaf)
	{
		for(int i=child->n;i>=0;i++)
			child->C[i+1] = child->C[i];
	}
	child->a[0] = a[id-1];
	if(!child->leaf)
		child->C[0] = sibling->C[sibling->n];
	a[id-1] = sibling->a[sibling->n-1];
	(child->n)++;
	(sibling->n)--;

}

void BtreeNode :: borrowFromSucc(int id)
{

	BtreeNode *child = C[id];
	BtreeNode *sibling = C[id+1];

	child->a[child->n] = a[id];
	a[id] = sibling->a[0];

	if(!child->leaf){
	child->C[(child->n)+1] = sibling->C[0];
	}

	for(int i = 1;i<sibling->n;i++ )
		sibling->a[i-1] = sibling->a[i];
	if(!child->leaf){
	    for(int i = 1;i<=sibling->n;i++ )
		    sibling->C[i-1] = sibling->C[i];
	}

	(sibling->n)--;
	(child->n)++;
}


void BtreeNode ::merge(int id)
{
	BtreeNode *child = C[id];
	BtreeNode *sibling = C[id+1];

	child->a[child->n] = a[id];

	for(int i=0;i<sibling->n;i++)
		child->a[child->n+1+i] = sibling->a[i];

	if(!child->leaf)
	{	for(int i=0;i<=sibling->n;i++)
				child->C[child->n+1+i] = sibling->C[i];
	}

	for(int i=id+1;i<n;i++)
		a[i-1] = a[i];
	for(int i=id+1;i<=n;i++)
		C[i-1]=C[i];
	child->n += sibling->n+1;
	n--;
	delete(sibling);
	return ;
}

void Btree :: remove(int k)
{
	if(!root)
	{
		cout<<"The tree is empty\n";
		return;
	}
	root->remove(k);
	if(root->n == 0)
	{
		BtreeNode *t = root;
		if(root->leaf)
			root = NULL;
		else
			root = root->C[0];
		delete t;
	}
	return;
}

void BtreeNode ::traverse()
{
	int i;
	for(i=0;i<n;i++)
	{
		if(leaf == false)
			C[i]->traverse();
		cout<<a[i]<<" ";
	}
	if(leaf == false)
		C[i]->traverse();
}

BtreeNode * BtreeNode :: search(int k)
{	int i;
	for(i=0;i<n && a[i]<k;i++);
	if(a[i] == k)
		return this;

	if(leaf == true)
		return NULL;

	return C[i]->search(k);

}

void Btree ::insert(int k)
{
	if(root == NULL)
	{
		root = new BtreeNode(t,true);
		root->a[0] = k;
		root->n = 1;
	}
	else
	{
		if(root->n == 2*t-1)
		{
			BtreeNode *p = new BtreeNode(t,false);
			p->C[0] = root;
			p->splitChild(0,p->C[0]);
			int i=0;
			if(p->a[0] < k)
				i++;
			p->C[i]->insertNonFull(k);
			root = p;
		}
		else
			root->insertNonFull(k);
	}
}

void BtreeNode :: insertNonFull(int k)
{
 int i = n-1;
 if(leaf == true)
 {

	 while(i >=0 && k < a[i])
		 {
		 a[i+1] = a[i];
		 i--;
		 }
	 a[i+1] = k;
	 n = n+1;
}
 else
 {
	 while(i >=0 && k <a[i])
		 i--;
	 if(C[i+1]->n == 2*t-1)
	 {
		 splitChild(i+1,C[i+1]);
		 if(a[i+1] < k)
			 i++;
	 }
	 C[i+1]->insertNonFull(k);

 }
}

void BtreeNode::splitChild(int i,BtreeNode *y)
{
	BtreeNode *z = new BtreeNode(y->t,y->leaf);
	z->n = t-1;

	for(int j=0;j<t-1;j++)
		z->a[j] = y->a[j+t];
	if(y->leaf == false)
	{
		for(int j=0;j<t;j++)
			z->C[j] = y->C[j+t];
	}
	y->n = t-1;
	for(int j=n;j>=i+1;j--)
		C[j+1] = C[j];
	C[i+1] = z;
	for(int j=n-1;j>=i;j--)
		a[j+1] = a[j];
	a[i]=y->a[t-1];
	n = n+1;
}
//find the max key stored in B-tree//
int Btree::find_max()
{
    //Implement your code here//
    return 0;
}

//find the min key stored in B-tree//
int Btree::find_min()
{
    //Implement your code here//
    return 0;
}


//find the predecessor of the given key//
int BtreeNode :: findPrec(int id)
{
	BtreeNode *curr = C[id];
	while(!curr->leaf)
		curr = curr->C[curr->n];
	return curr->a[curr->n-1];
}

//find the successor of the given key//
int BtreeNode :: findSucc(int id)
{
	BtreeNode *curr = C[id+1];
	while(!curr->leaf)
		curr = curr->C[0];
	return curr->a[0];
}

int main()
{
	Btree t(3);
	t.insert(1);
	t.insert(3);
	t.insert(7);
	t.insert(10);
	t.insert(11);
	t.insert(13);
	t.insert(14);
	t.insert(15);
	t.insert(18);
	t.insert(16);
	t.insert(19);
	t.insert(24);
	t.insert(25);
	t.insert(26);
	t.insert(4);
	t.insert(5);
	t.insert(20);
	t.insert(22);
	t.insert(2);
	t.insert(17);
	t.insert(12);
	t.insert(6);
    //write your test here//
    return 0;
}
