//
//  solution.h
//

#ifndef TRIE_SOLUTION_H
#define TRIE_SOLUTION_H

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cassert>
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
    // if the string is already in MyDict
    if (intrie(list)){
        result.append(CharList2Str(list));
        return result;
    }

    // This leaves the case where the string is not in MyDict

    // call find_last_exist to find the pointer to the last symbol
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.append(list[i]);
    }
    trienode<T>* lnode = find_last_exist(start, newlist);   // lnode = last node
    
    // if the word is not prefix of any words in the dictionary, return 0;
    if (lnode == NULL){
        return result; // the result list should be empty
    }

    // else, further determine that if any alternative words exist
    lnode = lnode->getfollow();
    do {
        if (lnode->getlast()){
            // an alternative has been found
            list.append(lnode->getdata());
            result.append(CharList2Str(list));
            list.remove(list.getlength());
        } 
        lnode = lnode->getnext();
    } while (lnode);
    return result;
}

/* ========== Function headers for Ex.2 (ii) ========== */
template<class T> AList<string> trie<T>::return_prefix(AList<T> list, AList<string> &result) {
    /* TODO */
    if (intrie(list)){
        result.append(CharList2Str(list));
        return result;
    }

    // This leaves the case where the string is not in MyDict

    // call find_last_exist to find the pointer to the last symbol
    // AList<T> newlist;
    // for (int i = 1; i <= list.getlength(); i++)
    // {
    //     newlist.append(list[i]);
    // }
    // trienode<T>* lnode = find_last_nonexist(start, newlist);   // lnode = last node

    // // assert(lnode != NULL);

    // //if no prefix exists, return 0;
    // if (lnode == NULL){
    //     return result;
    // }    

    // // if the prefix found is one symbol shorter than list
    // if (lnode->getdata() == list[list.getlength() - 1]){
    //     char temp = list[list.getlength()];
    //     list.remove(list.getlength()); 
    //     result.append(CharList2Str(list));
        
    
    //     // see if shorter prefix exists
    //     list.remove(list.getlength());
    //     if (intrie(list))
    // }

    // assert(lnode == NULL);
    // // if the prefix found is two symbols shorter than
    // if (lnode && lnode->getdata() == list[list.getlength() - 2]){
    //     list.remove(list.getlength()); 
    //     list.remove(list.getlength()); 
    //     result.append(CharList2Str(list));
    // }
    // // else, further determine that if any alternative
    // return result;
    list.remove(list.getlength());
    if (intrie(list)) result.append(CharList2Str(list));
    list.remove(list.getlength());
    if (intrie(list)) result.append(CharList2Str(list));
    return result;
}

/* ========== Function headers for Ex.2 (iii) ========== */
template<class T> AList<string> trie<T>::return_diff(AList<T> list, AList<string> &result) {
    /* TODO */
    if (intrie(list)){
        result.append(CharList2Str(list));
        return result;
    }

    // This leaves the case where the string is not in MyDict

    // call find_last_nonexist to find a pointer to the longest prefix 
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.append(list[i]);
    }
    AList<T> path;
    find_diff(start, newlist, path, false, result);

    return result;
}

// Helper function you may or may not use

/* find_last_exist
 * Helper function for return_extend
 * Input
 * 1. pointer to the current node
 * 2. a list of symbols to be searched
 * Output
 * 1. the pointer to the last symbol (if found), else return NULL
 * Algorithm Description
 * This operation adopts a recursive approach similar to the contains procedure, but returns a pointer instead of a truth-value.
 */

template<class T> trienode<T>* trie<T>::find_last_exist(trienode<T> *pt, AList<T> list) {
    if (list.getlength() == 0)
        return 0;
    if (pt == 0)
        return 0; // not found
    T key = list[1];  // examine the first element of the input list
    if ((*pt).getdata() == key)
    {
        list.remove(1);
        if (list.getlength() == 0)
            return pt;      //return the pointer to the last symbol of the word.
        /* proceed recursively with the follow pointer */
        return find_last_exist((*pt).getfollow(), list);
    }
    /* otherwise follow the next pointer */
    return find_last_exist((*pt).getnext(), list);
}
// /* find_last_nonexist
//  * Helper function for return_prefix
//  * Input
//  * 1. pointer to the current node
//  * 2. a list of symbols to be searched
//  * Output
//  * 1. a pointer to the last symbol that appeared in MyDict
//  */
// template<class T> trienode<T>* trie<T>::find_last_nonexist(trienode<T> *pt, AList<T> list) {
//     trienode<T>* prefix_node = NULL;    // the pointer to the end of the longest word that is a prefix
//     trienode<T>* found_result = NULL;
//     if (list.getlength() == 0)
//         return 0;
//     if (pt == 0)
//         return 0;
//     T key = list[1];  // examine the first element of the input list
//     if ((*pt).getdata() == key)
//     {
//         list.remove(1);
//         if (list.getlength() == 0)
//             return 0;      // no prefix exist in this branch of MyDict, terminating.
//         /* proceed recursively with the follow pointer */
//         if (pt->getlast()) prefix_node = pt;

//         found_result = find_last_nonexist((*pt).getfollow(), list);
//         if (found_result)   return found_result;
//         else return prefix_node;
//     }
//     /* otherwise follow the next pointer */
//     return find_last_nonexist((*pt).getnext(), list);

// }


/* find_diff
 * Input
 * 1. a pointer to the current node
 * 2. a list of symbols to be searched for
 * 3. a mark that indicates if a different symbol has appeared before.
 * Output
 * 
 * 
 * Algorithm Description
 * 1. the function 
 * Cases
 * 1. mark == false and list.getlength == 1                                 append
 * 2. mark == true  and list.getlength == 0                                 append
 * 3. mark == true  and list.getlength != 0 and (*pt).getdata() != key      terminate
 * 4. mark == true  and list.getlength != 0 and (*pt).getdata() == key      recursion (with mark = true)
 * 5. mark == false and list.getlength != 0 and (*pt).getdata() == key      recursion (with mark = false)
 * 6. mark == false and list.getlength != 0 and (*pt).getdata() != key      recursion (with mark = true)
 */
template<class T> void trie<T>::find_diff(trienode<T> *pt, AList<T> list, AList<T> path, bool mark, AList<string> &result){
    if (pt == NULL) return;
    int length = list.getlength();
    T key;
    // first explore all "next" nodes
    find_diff((*pt).getnext(), list, path, mark, result);

    AList<T> newlist;
    AList<T> newpath;

    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.append(list[i]);
    }

    for (int i = 1; i <= path.getlength(); i++)
    {
        newpath.append(path[i]);
    }


    // main routine
    if (mark == false){
        // case 1. 5. 6
        if (length == 1) {
            if (pt->getlast()){
                newpath.append(pt->getdata());
                result.append(CharList2Str(newpath));
            }            
            return;
        }
        if (length > 1){

            key = newlist[1];
            newlist.remove(1);
            newpath.append((*pt).getdata());
            if (key != (*pt).getdata()) find_diff((*pt).getfollow(), newlist, newpath, true, result);
            if (key == (*pt).getdata()) find_diff((*pt).getfollow(), newlist, newpath, false, result);
        }
    } else {

        // case 2. 3. 4 where mark == true
        if (length == 1){
            key = newlist[1];
            newlist.remove(1);
            if (key == (*pt).getdata() && (*pt).getlast()){
                newpath.append(key);
                result.append(CharList2Str(newpath));
            }    
        }
        if (length > 1){

            key = newlist[1];
            newlist.remove(1);
            newpath.append((*pt).getdata());
            if (key == (*pt).getdata()) find_diff((*pt).getfollow(), newlist, newpath, true, result);
        } 
    }



}

#endif //TRIE_SOLUTION_H
