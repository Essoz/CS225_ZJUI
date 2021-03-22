class HashSet_RH
{
    /* Refer to the given code to design the new hashset */
    public:
        HashSet_RH(int size = 20);
        void add(int index, int item,int distance, int** HashArray, int* DistArray);
        void add(int item);
        void rehash(int newsize);
        void remove(int item);
        void display(void);
        int numitems;           // contains the number of elements in the hashtable
        int **reprarray;
        int *disarray;
/* reprarray defines a pointer to (an array of) pointers to values of type T. We will use a null pointer, if an entry is undefined, and a fixed pointer as placeholder for free entries (after remove) */
        int *pt_nil;              // used as placeholder
        int maxsize;            // defines the size of the hashtable
};
class HashSet_LCFS
{
public:
    HashSet_LCFS(int size = 20);
//    virtual ~hashset();
// The operation add inserts an element into the hashtable, remove deletes an
// element and member checks, if the element is in the hashtable
    void add(int item);
    void remove(int item);
// The function display is only used for testing purposes. It shows the size of
// the hashtable, the number of elements, and displays all entries
    void display(void);
    int numitems;           // contains the number of elements in the hashtable
    int **reprarray;
    int *disarray;
/* reprarray defines a pointer to (an array of) pointers to values of type T. We will use a null pointer, if an entry is undefined, and a fixed pointer as placeholder for free entries (after remove) */
    int *pt_nil;              // used as placeholder
    int maxsize;            // defines the size of the hashtable
    void rehash(int newsize);
// rehash is an internal function to enlarge or shrink the hashtable,
// if the fill factors 0.75 or 0.25 are exceeded or undershot, resp.
};
