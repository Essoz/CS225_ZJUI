#ifndef FIBHEAP_F_H
#define FIBHEAP_F_H
#include "fibheap.h"

#define INFIMUM -100000

FibNode::FibNode(registration* n_registration){
    parent = NULL;
    child = NULL;
    left = NULL;
    right = NULL;
    degree = 0;
    mark = false;       // default marking == false
    reg_id = n_registration->getID();
    // key = priority;
    int8_t type = n_registration->getTreatmentType();
    person* Per = Per_Relation_Retrieve(n_registration->getPersonID());
    int8_t MedStat = Per->getMedicalStatusID();
    if (type == 0) {
        // for vaccination
        key = 4 - MedStat;
    } else if (type == 1) {
        // for surgery
        key = stoi(n_registration->getDateOfReg());
    } else if (type == 2) {
        // for regular registration
        key = 100 - Per->getAge();
    }
}

// build an empty heap
FibHeap::FibHeap(){
    min_ptr = NULL;
    numitems = 0;
    processin_table = new Hash_Chaining();
};

/* <===> Test Passed <===> */
void FibHeap::Insert(FibNode* fib_node){
    if(min_ptr){
        //if the Heap structure is not empty
        min_ptr->left->right = fib_node;
        fib_node->left = min_ptr->left;
        fib_node->right = min_ptr;
        min_ptr->left = fib_node;
        // update the min 
        min_ptr = (min_ptr->key > fib_node->key) ? fib_node : min_ptr;
    } else {
        // if the Heap structure is empty
        min_ptr = fib_node;
        fib_node->left = fib_node;
        fib_node->right = fib_node;
	numitems = 0;
    }
    numitems++;
    hash_table_insert(fib_node);
}
/* FibHeap - Decrease Key
 * Input: 
 1. a handle to any node;  
 2. a key;
 * Algorithm Description
 1. change the given node's key to the specified value
 2. check if the definition of the heap is violated, if so, cut the subtree and re-insert it.  

//  4. execute consolidate
 */
void FibHeap::DecreaseKey(FibNode* handle, int new_key){
    // int num = GetNum();
    handle->key = new_key;
    if (handle->parent && new_key < handle->parent->key){
        Cut(handle);
    } else if (handle->parent == NULL) {
        if (new_key < min_ptr->key) {
            min_ptr = handle;
        }
    }
    // Consolidate();
    // numitems = num; //since insertions within Cut modifies Cut 
}
/* FibHeap - Cut
 * Input
 1. a handle to any node (that is guaranteed to have a parent)
 * Algorithm Description
 1. First check if handle == parent->child. If so, there will be two cases
    i. node handle is the only child of its parent: 
        check if the parent is marked, if so, do cascaded cut
        if not, mark the parent, decrement degree.
    2. node handle is 
 */


void FibHeap::Cut(FibNode* handle){
    FibNode* par_ptr = handle->parent;
    if (handle->left == handle){
        // if handle is the only child, just set child_ptr to NULL
        par_ptr->child = NULL;
    } else {
        // delete handle from the child list
        if (par_ptr->child == handle) 
            //shift the child_ptr 
            par_ptr->child = handle->left;
        handle->left->right = handle->right;
        handle->right->left = handle->left;
    }
    handle->parent = NULL;
    Insert(handle);
    numitems--;

    // do marking or cascaded cut
    if (par_ptr->mark == false){
        par_ptr->mark = true;   // TODO: Should root nodes be marked?
    } else {
        if(par_ptr->parent) Cut(par_ptr);
    }

    // decrement degree of the parent node
    par_ptr->degree--;
}

/* FibHeap - Consolidate
 * Input
 1. the heap structure itself
 * Output: None
 * Effect
 */
void FibHeap::Consolidate(){
    int D_n = log(GetNum())/log(2) + 2;
    // D_n++;
    int num = GetNum();
    // initiate the auxillary array
    FibNode** arr = new FibNode* [D_n];
    for(int i = 0; i < D_n; i++){
        arr[i] = NULL;
    }
    FibNode* node_x = min_ptr;
    FibNode* node_y; 
    int x_degree = 0;
    // debug note : the for loop should be replaced by a while loop, and the above line should be 
    for (int i = 0; i <= num; i++){
        x_degree = node_x->degree;
        while(arr[x_degree] != NULL){
            node_y = arr[x_degree];
            if (node_x == node_y) break;
            if (node_x->key > node_y->key){
                // exchanging two pointers if necessary, making sure that node x has a smaller key.
                FibNode* temp_ptr = node_x;
                node_x = node_y;
                node_y = temp_ptr;

            }
            // merge the two heaps
            HeapLink(node_x, node_y); // add node_y as a child of x
            arr[x_degree] = NULL;
   	    x_degree++;
        } 
        arr[x_degree] = node_x;
        node_x = node_x->right;
    }
    // PrintTree();
    min_ptr = NULL;
    for (int i = 0; i < D_n; i++){
        if (arr[i]) Insert(arr[i]); // all cases are handled by this insert function
    } 
    numitems = num; //since the insert operation will change numitems
}
/* FibHeap - HeapLink
 * Input
 1. heap1 - A heap structure with smaller min
 2. heap2 - A heap structure with larger min
 * Output: NONE
 * Effect
 1. Unmark heap2
 2. heap2 will be linked to heap1 as a child of heap1
 */
FibNode* FibHeap::HeapLink(FibNode* heap1, FibNode* heap2){
    FibNode* temp = heap1->child;
    heap2->left->right = heap2->right;
    heap2->right->left = heap2->left;
    
    if (temp != 0){
	// link the second heap to the left of the child list 
	temp = temp->left;
        heap1->child->left = heap2;
        heap2->right = heap1->child;
        heap2->left = temp;
        temp->right = heap2;
    } else {
        heap1->child = heap2;
        heap2->right = heap2->left = heap2;
    }
    heap1->degree++;
    heap2->parent = heap1;
    heap2->mark = false;
    return heap1;
}

/* FibHeap - Minimum */
FibNode* FibHeap::Minimum(){
    return min_ptr;
}
/* FibHeap - ExtractMin
 * Input: NONE
 * Output
 1. the minimum node in the heap or NULL(if the heap was empty);
 * Algorithm Description
 1. First find that if the structure is empty. If so, return NULL
 2. If the structure is not empty, then add all children of min_ptr to the root list
 3. Return the given node
 */
FibNode* FibHeap::ExtractMin(){
    if (min_ptr){
        FibNode* current_node = min_ptr->child;
        FibNode* next_node = NULL;
        
        int min_degree = min_ptr->degree;
        for (int i = 0; i < min_degree; i++){
            next_node = current_node->left;
            Cut(current_node);
            current_node = next_node;
        }
        min_ptr->degree = 0;
        current_node = min_ptr;
        numitems--;
        if (min_ptr == min_ptr->right){
            min_ptr = NULL;
        } else {
            min_ptr->right->left = min_ptr->left;
            min_ptr->left->right = min_ptr->right;
            min_ptr = min_ptr->right;

        
        Consolidate();
        // TODO: Fill the definition for FINDMIN()
        
        //since finding the new min is handled by consolidation, no need for FindMin here
        //FindMin();
	    
        }
        hash_table_remove(current_node->getRegID());
        return current_node;
    } else {
        // the structure is empty
        cout <<"The heap structure has no node in it, exiting ExtractMin...\n" <<endl;
        return NULL;
    }
}

/* FibHeap - FindMin
 * Input
 1. The heap structure itself
 * Output: NONE
 * Effect
 Update min_ptr
 * Algorithm Description
 1. Traverse through all roots in the list
 */
void FibHeap::FindMin(){
    if (min_ptr) {
        FibNode* current_node = min_ptr->left;
        FibNode* current_min = min_ptr;
        while (current_node != min_ptr){
            if (current_node->key < current_min->key){
                // locate the new minimum 
                current_min = current_node;
            }
	    current_node = current_node->left;
        } 
	min_ptr = current_min;
    } else {
        // else do nothing
        ;
    }
}


/* FibHeap - Delete
 * Input
 1. A handle to the node to be deleted
 * Output
 1. The modified heap structure
 * Algorithm Description
 1. First set the node to be deleted to the infimum of all keys
 2. Then execute extract_minimum
 */
void FibHeap::Delete(FibNode* handle){
    DecreaseKey(handle, INFIMUM);
    ExtractMin();
}

FibHeap* FibHeap::Union(FibHeap* heap1, FibHeap* heap2){
    FibHeap* new_heap = new FibHeap;
    new_heap->numitems = heap1->numitems + heap2->numitems;

    // determine new min from the two heap structures
    new_heap->min_ptr = heap1->min_ptr;
    if (heap2->min_ptr && heap1->min_ptr && heap2->min_ptr->key < new_heap->min_ptr->key){
        new_heap->min_ptr = heap2->min_ptr;
    } 
    
    // concatenate the root lists
    if (new_heap->min_ptr == heap1->min_ptr){
        new_heap->min_ptr->right->left = heap2->min_ptr->right;
        heap2->min_ptr->right->left = new_heap->min_ptr->right;
        new_heap->min_ptr->right = heap2->min_ptr;
        heap2->min_ptr->right = new_heap->min_ptr;
        
        new_heap->min_ptr->right = heap2->min_ptr;
        heap2->min_ptr->left = new_heap->min_ptr;
        
    }
     
    

    
    return new_heap;
}

int FibHeap::GetNum(){
    return numitems;
}

void FibHeap::removeReg(registration* Reg){
    int64_t reg_id = Reg->getID();
    FibNode* handle = hash_table_find(reg_id);
    if (handle) {
        Delete(handle);
        hash_table_remove(reg_id);
    } else {
        cout << "Reg of ID: " << Reg->getID() << " being deleted is not in the heap" << endl;   
    }

}

/* <=== Functions for Hash tables ===> */
FibNode* FibHeap::hash_table_find(int id){
    return processin_table->retrieval(id);
};
bool FibHeap::hash_intable_check(int id){
    if (processin_table->retrieval(id) == NULL) return false;
    // else the element is in the hashtable
    return true;
};

/* hash_table_remove
 * INPUT
 * 1. the id of the element to be deleted
 * OUTPUT
 * 1. the address to the removed node (for further removing the node from the central heap)
 */
FibNode* FibHeap::hash_table_remove(int id){
    // first record the address of the node to be deleted
    FibNode* old = processin_table->retrieval(id);
    // then delete the entry from the central heap
    processin_table->deletion(id);
    // return the pointer to the old node
    return old;    
};

void FibHeap::hash_table_insert(FibNode* node){
    processin_table->insertion(node);
};

/* hash_table_swap
 * INPUT
 * the updated version of a registration (node)
 * OUTPUT
 * the older version of a registration
 * EFFECT
 * swap a registration (only in hash table) that is under assignment with its newer version
 */

FibNode* FibHeap::hash_table_swap(FibNode* node){
    int id = node->getRegID();
    FibNode* old = processin_table->retrieval(id);
    processin_table->deletion(id);
    hash_table_insert(node);
    return old;
};




// /* This Function is for Testing */
// void FibHeap::PrintTree(){
//     fiblist.clear();
//     if (!fiblist.empty())
//     {
//         cout<<"The fiblist is not empty!"<<endl;
//         return;
//     }
    
//     // cout << "\n=========================\n"; 
	
//     if (min_ptr == NULL){
//         cout << "The Heap Structure is Empty" <<endl;
//         return;
//     }
    
//     FibNode* root_pt = min_ptr;
//     int i = 0;
//     do{
//         // cout << "Heap " << i++ << " :: " <<root_pt->key;
//         fiblist.insert(fiblist.end(),root_pt);
//         _PrintTree(root_pt->child);
//         // cout << "\n------------\n";
//         // move to the next heap
//         root_pt = root_pt->right;
//     }while(root_pt != min_ptr);
    
// }

// /* Recursive Printing*/
// void FibHeap::_PrintTree(FibNode* node){
//     if (node == NULL){return;}
//     FibNode* node_pt = node;
//     // cout << "[";
//     do{
//         // cout<< node_pt->key <<", ";
//         fiblist.insert(fiblist.end(),node_pt);
//         _PrintTree(node_pt->child);
//         node_pt = node_pt->right;
//     }while(node_pt != node);
//     // cout << "]";
// }

/* <=== Computing Assignment 1 Helper Function ===>*/
/* String2Int 
 * Input
 * 1. key (key should be written in decimal form)
 * Output
 * 1. key in type int
 */
// int String2Int(string key){
//     int key_int = 0;
    
//     for (int i = int(key.size()) - 1; i >= 0; i--){
//         key_int += key[i] * pow(10, key.size() - i) ; // an explicit type cast may be needed here
//     }

//     return key_int;
// };


// /* This Function is for Testing */
// void FibHeap::debugPrintTree(){
//     cout << "\n=========================\n"; 
	
//     if (min_ptr == NULL){
//         cout << "The Heap Structure is Empty" <<endl;
//         return;
//     }
    
//     FibNode* root_pt = min_ptr;
//     int i = 0;
//     do{
//         cout << "Heap " << i++ << " :: " <<root_pt->getRegID();
//         debug_PrintTree(root_pt->child);
//         cout << "\n------------\n";
//         // move to the next heap
//         root_pt = root_pt->right;
//     }while(root_pt != min_ptr);
    
// }

// /* Recursive Printing*/
// void FibHeap::debug_PrintTree(FibNode* node){
//     if (node == NULL){return;}
//     FibNode* node_pt = node;
//     cout << "[";
//     do{
//         cout<< node_pt->getRegID() <<", ";
//         debug_PrintTree(node_pt->child);
//         node_pt = node_pt->right;
//     }while(node_pt != node);
//     cout << "]";
// }

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
    int index = calculate_hashvalue(node->getRegID(), hash_maxsize); // Calculate the hashvalue
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
        if (DEBUG) cout << "The patient of id " << id << " is not in the hashtable." << endl;
        return NULL;
    }
    else {
        // Loop through that vector entry:
        for (int i = 0; i < int(hashtable->at(index)->size()); i++) {
            if (id == hashtable->at(index)->at(i)->getRegID()) {
                // item found
                return hashtable->at(index)->at(i);
            }
        }
        if (DEBUG) cout << "The patient of id " << id << " is not in the hashtable." << endl;
        return NULL;
    }
}

// Return a list containing all the patients' pointer:
vector<FibNode*>& Hash_Chaining::list_patient()
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
    return *list;
}


#endif /* fibheap_f_h */


