//
//  test.cpp
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "solution.h"
#include "trie.h"
#include "trie.cpp"
using namespace std;

void Str2CharList(AList<char> &list, string s);
vector<string> split(string str,string separator);

int main() {
    /* You may change to smaller test text for debugging */
    string text = "In computer science, a trie, also called digital tree or prefix tree, is a kind of search tree an ordered tree data structure used to store a dynamic set or associative array where the keys are usually strings. Unlike a binary search tree, no node in the tree stores the key associated with that node; instead, its position in the tree defines the key with which it is associated. All the descendants of a node have a common prefix of the string associated with that node, and the root is associated with the empty string. Keys tend to be associated with leaves, though some inner nodes may correspond to keys of interest. Hence, keys are not necessarily associated with every node. For the space-optimized presentation of prefix tree, see compact prefix tree.";
    string temp;
    trie<char> MyDict;

    /* Remove the punctuations and transfer all letters to lowercase */
    for (string::size_type i = 0; i < text.size(); i++) {
        if (!ispunct(text[i])){
            temp += tolower(text[i]);
        }
    }
    vector<string> words = split(temp, " ");

    /* Build the dictionary */
    AList<char> curr;
    for (int i = 0; i < words.size(); ++i) {
        while (curr.getlength())
            curr.remove(1);
        for (int j = 0; j < words[i].size(); ++j)
            curr.append(words[i][j]);
        MyDict.insert(curr);
    }

    /* Displaying the dictionary */
    MyDict.display();

    AList<char> in_str;
    AList<string> result;

    /* Comment or uncomment different cases to sea if outputs are correct */

    /* ========== Tests for part (i) ========== */
//      Given test 1:       associate
//      Expected output:    associated
    Str2CharList(in_str, "associate");

//      Given test 2:       fo
//      Expected output:    for
//    Str2CharList(in_str, "fo");

    cout << "Test for part (i)" << endl;
    // Clear result list
    while (result.getlength())
        result.remove(1);
    MyDict.return_extend(in_str, result);
    for (int i = 0; i < result.getlength(); ++i)
        cout << result[i+1] << ' ';

    /* ========== Tests for part (ii) ========== */
//      Given test 1:       storeas
//      Expected output:    store
    Str2CharList(in_str, "storeas");

//      Given test 2:       inn
//      Expected output:    in
//    Str2CharList(in_str, "ina");

    cout << "\nTest for part (ii)" << endl;
    // Clear result list
    while (result.getlength())
        result.remove(1);
    MyDict.return_prefix(in_str, result);
    for (int i = 0; i < result.getlength(); ++i)
        cout << result[i+1] << ' ';

    /* ========== Tests for part (iii) ========== */
//      Given test 1:       strong
//      Expected output:    string
    Str2CharList(in_str, "strong");

//      Given test 2:       than
//      Expected output:    that
//    Str2CharList(in_str, "than");

    cout << "\nTest for part (iii)" << endl;
    // Clear result list
    while (result.getlength())
        result.remove(1);
    MyDict.return_diff(in_str, result);
    for (int i = 0; i < result.getlength(); ++i)
        cout << result[i+1] << ' ';

    return 0;
}

/* ========== You do not need to modify anything below ==========  */
// Helper function, convert string to AList
void Str2CharList(AList<char> &list, string s) {
    while (list.getlength())
        list.remove(1);
    for (int i = 0; i < s.size(); ++i) {
        list.append(tolower(s[i]));
    }
}

// Helper function, split string by separator
vector<string> split(string str,string separator) {
    vector<string> result;
    int cutAt;
    while((cutAt = str.find_first_of(separator))!=str.npos){
        if(cutAt>0){
            result.push_back(str.substr(0,cutAt));
        }
        str=str.substr(cutAt+1);
    }
    if(str.length()>0){
        result.push_back(str);
    }
    return result;
}
