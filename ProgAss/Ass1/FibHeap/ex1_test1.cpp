#include "fibheap_f.h"
#include "alist.cpp"
#include <assert.h>

int main(){
	int input1[]= {1,2,3,4,5};
	FibHeap<int>* fib_heap_1 = new FibHeap<int>;

	FibNode<int>* fib_nodes = NULL;
	AList<FibNode<int>*> node_list_1;
	for (auto i: input1) {
		fib_nodes = new FibNode<int>(i);
		node_list_1.append(fib_nodes);
		fib_heap_1->Insert(fib_nodes);
		if(fib_heap_1->Minimum()==NULL) cout << "FUCK" << endl;
	}

	for (int i = 0; i < 6; i++)
	{
		cout << i << "\n";
		cout <<fib_heap_1->GetNum() << "\n";
		fib_heap_1->ExtractMin();
		fib_heap_1->PrintTree();
	}
	
	cout << "FUCKKKKKKKKKKKKKKKKKKKKKK" << endl;


}
