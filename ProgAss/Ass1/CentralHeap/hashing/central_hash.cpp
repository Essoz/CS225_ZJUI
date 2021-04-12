//#include "central_hash.h"

/*
 *  File: hash.cpp
 *
 *  Writter: Tianyu Zhang
 *
 *  Description: The function definition for hash.h
 */

// Constructor:
Hash_Chaining::Hash_Chaining(int length)
{
    // Initialize the attributes of the hashtable
    hash_maxsize = length;
    if (length < 20) {
        hash_maxsize = 20;  // Default size for hashtable
    }
    hash_numitems = 0;   // The current number of pairs in hashtable
    hashtable = new vector<vector<FibNode*>*>(hash_maxsize);
    for (int i = 0; i < hash_maxsize; i++) {
        hashtable->at(i) = NULL;
    }
}

int Hash_Chaining::get_numitems() {
    return hash_numitems;
}
// Calculate the hashvalue:
int Hash_Chaining::calculate_hashvalue(int id, int size)
{
    hash<int> hashfunction; // use the predefined hashfunction to get "key" values
    return hashfunction(id) % size;
}

// Insert a value:
void Hash_Chaining::insertion(FibNode* node)
{
    int index = calculate_hashvalue(node->getid(), hash_maxsize); // Calculate the hashvalue
    // If the corresponding entry is not defined, define it:
    if (hashtable->at(index) == NULL) {
        vector<FibNode*>* entry = new vector<FibNode*>;
        hashtable->at(index) = entry;
        hash_numitems++;
        hashtable->at(index)->push_back(node);   // Add that item into the entry
        return;
    }
    // Go through that entry to check if the item is already there:
    for (int i = 0; i < int(hashtable->at(index)->size()); i++)
    {
        if (hashtable->at(index)->at(i) == node) {
            return;
        }
    }
    hashtable->at(index)->push_back(node);   // Add that item into the entry
    return;
}

// Delete a value:
void Hash_Chaining::deletion(int id)
{
    // Get the correspoding node pointer:
    FibNode* node = retrieval(id);
    // If no node in the table, do nothing:
    if (NULL == node){
        return;
    }

    int index = calculate_hashvalue(id, hash_maxsize); // Calculate the hashvalue
    // If the corresponding entry is not defined, just return:
    for (int i = 0; i < int(hashtable->at(index)->size()); i++)
    {
        if (node == hashtable->at(index)->at(i)) {
            // item found
            hashtable->at(index)->erase(hashtable->at(index)->begin() + i);
            // If now the entry is empty, undefine that entry:
            if (0 >= int(hashtable->at(index)->size())) {
                hashtable->at(index) = NULL;
                hash_numitems--;
            }
            return;
        }
    }
    return;
}

// Return the pointer of the patient instance in the hash table:
FibNode* Hash_Chaining::retrieval(int id)
{
    int index = calculate_hashvalue(id, hash_maxsize); // Calculate the hashvalue
    // If the corresponding entry is not defined, just return:
    if (hashtable->at(index) == NULL) {
        cout << "The patient of id " << id << " is not in the hashtable." << endl;
        return NULL;
    }
    else {
        // Loop through that vector entry:
        for (int i = 0; i < int(hashtable->at(index)->size()); i++) {
            if (id == hashtable->at(index)->at(i)->getid()) {
                // item found
                return hashtable->at(index)->at(i);
            }
        }
        cout << "The patient of id " << id << " is not in the hashtable." << endl;
        return NULL;
    }
}

// Return a list containing all the patients' pointer:
vector<FibNode*>* Hash_Chaining::list_patient()
{
    // Creat a vector to store the pointers:
    vector<FibNode*>* list = new vector<FibNode*>;
    // Loop through all the entries of the hashtable:
    for (int i = 0; i < hash_numitems; i++)
    {
        // Loop through each entry:
        for (int j = 0; j < int(hashtable->at(i)->size()); j++)
        {
            // Add each patient to the list:
            list->push_back(hashtable->at(i)->at(j));
        }
    }
    return list;
}
