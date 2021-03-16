//
//  hashset.cpp
//  
//
//  Created by KD on 6.03.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "solution.h"
#include <vector>
#include <algorithm>


int main()
{
    std::vector<int> temp;
    for (int i = 0; i< 100; i++){
        temp.push_back(i);
    }
    srand(1234);
    std::random_shuffle(temp.begin(),temp.end());
    std::cout<<"Here is test case 1:"<<std::endl;
    hashset<int> myhashtable1(20);
    int size = 15;
    std::cout<<"The num of item is: "<< size << std::endl;
    for (int i = 0; i< size; i++)
    {
        myhashtable1.add(temp[i]);
    }
    std::cout << "The number of elements in the hashtable is: " << myhashtable1.get_num() <<std::endl;
    std::cout<<"Correct hash table is: "<<std::endl;
    std::cout<<"None None 92 None 44 None 97 None 75 62 None None None 43 45 8 None 48 99 None 64 None 29 None 69 None 34 None 25 None "<<std::endl;
    std::cout<<"Your hash table is:" <<std::endl; 
    myhashtable1.display();
    
    std::cout<<'\n'<<std::endl;
    std::cout<<"Here is test case 2:"<<std::endl;
    hashset<int> myhashtable2(20);
    size = 25;
    std::cout<<"The num of item is: "<< size << std::endl;
    for (int i = 0; i< size; i++)
    {
        myhashtable2.add(temp[i]);
    }
    std::cout << "The number of elements in the hashtable is: " << myhashtable2.get_num() <<std::endl;
    std::cout<<"Correct hash table is: "<<std::endl;
    std::cout<<"67 34 None None 32 None None None None 25 98 44 77 None None None None None 68 None 75 14 21 None None None None 99 None 45 12 64 92 None None None 69 97 57 43 None 62 41 8 48 29 "<<std::endl;
    std::cout<<"Your hash table is:" <<std::endl; 
    myhashtable2.display();

    return 0;
}



