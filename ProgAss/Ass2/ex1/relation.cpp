#include "relation.h"



/*==============================================*/
/* Member Function of Block Header              */




/* Block::Find(int64_t id)
 * INPUT:
    * id of the tuple to be found
 * OUTPUT:
 * the index of the entry to be found 
 * (-1                  if not found, 
 * 0    to size - 1     if in main block,
 * size to 2* size - 1  if in overflow block) 
 */
template <class T>
int64_t Block<T>::Find(int64_t id) {
    // do an linear search in the main block
    int64_t index = -1;
    for ( int64_t i = 0; i < getSize(); i++ ){
        if (reparray[i]->ID == id) {
            index = i;
            break
        }
    }
    if ( index == -1 ){
        // examine the overflow block
        for ( int64_t i = 0; i < header.of_block_ptr->getSize(); i++ ){
            if ( header.of_block_ptr->reparray[i]->ID == id){
                index = i + getSize();
            }
        }
    }
    return index;
}

/* Block::Insert(T* n_tuple)
 * INPUT:
    * the tuple to be inserted
 * OUTPUT:
    * -1 if cannot insert
    * the ID of the tuple
 * EFFECT:
    * new tuple is added to the first empty entry in the array (assume no holes)
    * num_items++
 */
//TODO Can insertion happen at where the tuple is marked deleted?

template <class T>
int64_t Block<T>::Insert(T* n_tuple){
    if ( getNum() >= getSize()) {
        // no available space in main block, try overflow block
        Block<T>* of_ptr = header.getOverflowBlock();
        
        if ( of_ptr->getNum() >= of_ptr->getSize() ){
            // cannot insert
            return -1;
        } else {
            of_ptr->Insert(n_tuple);
        }
    } else {
        reparray[getNum()] = n_tuple;
    }
    header.num_items++;
}

/* Block::Delete(T* ID)
 * INPUT:
 * ID of the tuple to be deleted
 * OUTPUT:
 * true / false -- whether the tuple has been deleted
 * EFFECT:
 * 1. the tuple is marked with tombstone = true. 
 */
template <class T>
bool Block<T>::Delete(int64_t id){
    int64_t result = Find(id);
    if ( result == -1 ){
        // the tuple is not in the block, return false
        return false;
    } else if ( result < getSize() ){ 
        // TODO the deletion method here do not examine if the tuple has already been deleted
        header.markDeleted(result);
    } else {
        header->of_block_ptr->header.markDeleted(result - getSize());
    }
    return true;
}
