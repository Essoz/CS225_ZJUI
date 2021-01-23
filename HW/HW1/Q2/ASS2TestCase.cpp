#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "alist.cpp"
using std::cout;
using std::cin;
using std::endl;
#define SIZE 20
AList<int>testlist(SIZE);

void length_test();
int f_length(int x);
int g_length(int n, int m);

void sublist_test();
AList <int> f_sub(int x);
AList <int> g_sub(AList <int> l_1, AList <int> l_2);

int main(){

    for(int i = 0; i<SIZE; i++){
        testlist.append(i+1);
    }


    int type, size, op;
    do {
        cout << "Choose Test Cases for ASS2 code:\n";
        cout << "0: get the length of the array (not using getlength())\n";
        cout << "1: get the sublist of this list satisfying {x|x>=14}\n";
        cin >> type;
        if ((type != 0) && (type != 1))
        cout << "You must choose 0 or 1\n\n";
    } while ((type != 0) && (type != 1));
        cout << "Below is the original array\n";
        int numelements = testlist.getlength();
        for (int i = 1; i <= numelements; ++i)
            {
                cout << "List element " << i << " is " << testlist[i] <<".\n";
            }

    switch(type){
        case 0:
        {
            length_test();
            break;
        }
        case 1:
        {
            sublist_test();
            break;
        }
        default: return -3;
    }
    return 0;
}

void length_test(){
    int e = 0;
    int value = testlist.src(e,&f_length,&g_length);
    cout << value << endl;
}
int f_length(int x){
    return 1;
}
int g_length(int n, int m){
    return n+m;
}


void sublist_test(){
    AList<int>e(1);
    AList<int> output_array(SIZE);
    output_array = testlist.src(e,&f_sub, &g_sub);

    cout << "Below is the modified array\n";
    int numelements = output_array.getlength();
    for (int i = 1; i <= numelements; ++i)
    {
            cout << "List element " << i << " is " << output_array[i] <<".\n";
    }
}



AList <int> f_sub(int x){
    AList<int> sub_list(1);
    if (x >= 14){
        sub_list.append(x);
    }
    return sub_list;
}
AList <int> g_sub(AList<int> l_1, AList<int> l_2){
    int merged_list_size = l_1.getlength() + l_2.getlength();
    AList<int>* merged_list;
    if (merged_list_size > 0){
        merged_list =  new AList<int>(merged_list_size);
        int i = 0;
        for (i; i < l_1.getlength(); i++)   {merged_list->append(l_1[i+1]);}
        for (i; i < merged_list_size; i++ ) {merged_list->append(l_2[i-l_1.getlength()+1]);}
    } else {
        merged_list = new AList<int>(1);
    } 
    return *merged_list;
}

