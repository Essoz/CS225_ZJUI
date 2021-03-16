
#ifndef ex6_h
#define ex6_h

template<class T> class pair{
    public:
        pair(){
            pair_t = 0;
            pair_n = 0;
        }
        pair(T t, int n):pair_t(t), pair_n(n){}
        T get_t(){
            return pair_t;
        }
        int get_n(){
            return pair_n;
        }
        void set_t(T t){
            pair_t = t;
        }
        void set_n(int n){
            pair_n = n;
        }
        void print_pairs();
    private:
        T pair_t;
        int pair_n;
};


template<class T> class fifo
{
public:
    fifo(int size = 10);
    virtual ~fifo();
    pair<T> &operator[](int index);
    int getlength(void);
    bool isempty(void);
    pair<T> back(void);
    pair<T> front(void);
    void pushback(pair<T> value);
    pair<T> popfront(void);

    T pop_vip(void);    //finish this function in the bottom of ex6.cpp
    
private:
    int maxsize, minsize;
    int first, last;
    int numitems;
    pair<T> *reprarray;
    void allocate(void);
    void deallocate(void);
};

#endif
