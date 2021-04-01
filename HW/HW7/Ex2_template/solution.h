//
//  solution.h
//

#ifndef TRIE_SOLUTION_H
#define TRIE_SOLUTION_H

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "trie.h"
using std::cout;
using std::cin;

// Helper function you may or may not use, convert AList<char> into string
string CharList2Str(AList<char> list) {
    string s;
    for (int i = 0; i < list.getlength(); ++i) {
        s += list[i+1];
    }
    return s;
}

/* ========== Function headers for Ex.2 (i) ========== */
template<class T> AList<string> trie<T>::return_extend(AList<T> list, AList<string> &result) {
    /* TODO */
    return result;
}

/* ========== Function headers for Ex.2 (ii) ========== */
template<class T> AList<string> trie<T>::return_prefix(AList<T> list, AList<string> &result) {
    /* TODO */
    return result;
}

/* ========== Function headers for Ex.2 (iii) ========== */
template<class T> AList<string> trie<T>::return_diff(AList<T> list, AList<string> &result) {
    /* TODO */
    return result;
}

// Helper function you may or may not use
template<class T> bool trie<T>::contains_extend(trienode<T> *pt, AList<T> list, AList<T> path, AList<string> &result) {
    return 0;
}

// Helper function you may or may not use
template<class T> bool trie<T>::contains_diff(trienode<T> *pt, AList<T> list, AList<T> path, AList<string> &result, int diff) {
    return 0;
}

#endif //TRIE_SOLUTION_H
