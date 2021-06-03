#include<iostream>
#include <cstdlib>
#include<cassert>
using namespace std; 

//safe array class
template<typename T>
class SA{
    private:
        int low, high;
        T *p;
        int size;
    public:
        struct Iterator{
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;

            Iterator(T* ptr) : m_ptr(ptr){}

            reference operator*() const{
                return *m_ptr;
            }
            pointer operator->(){
                return m_ptr;
            }
            Iterator& operator++(){
                m_ptr++;
                return *this;
            }
            Iterator operator++(int){
                Iterator temp = *this;
                ++(*this);
                return temp;
            }

            friend bool operator==(const Iterator &a, const Iterator &b){
                return a.m_ptr == b.m_ptr;
            };
            friend bool operator!=(const Iterator &a, const Iterator &b){
                return a.m_ptr != b.m_ptr;
            }

            private:
                T *m_ptr;
        };

        Iterator begin(){
            return Iterator(p);
        }
        Iterator end(){
            return Iterator(p+size);
        }

        Iterator find(Iterator begin, Iterator end, const T& val){
            int count = 0;
            while(begin != end){
                if(*begin == val){
                    cout<<endl<<*begin<<" is found!"<<endl<<"location of the value: "<<&begin<<endl<<"index in the array: "<<count<<endl;
                    return begin;
                }
                ++count;
                ++begin;
            }
            return begin;
        }

        SA(){
            low = 0;
            high = -1;
            p = NULL;
            size = 0;
        }

        SA(int i){
            low = 0;
            high = i-1;
            p = new T[i];
            size = high - low;
        }

        SA(int l, int h){
            if ((h - l + 1) <= 0) {
                cout << "constructor error in bounds definition" << endl;
			    exit(1);
            }
            low = l;
            high = h;
            p = new T[h-l+1];
            size = h-l;
        }
        
        SA(const SA & s){
		    int size=s.high-s.low+1;
		    p=new T[size];
		    for(int i=0; i<size; i++){
                p[i]=s.p[i];
            }
		    low=s.low;
		    high=s.high;
	    }

        ~SA(){
            delete [] p;
        }

        int getsize(){
            return size;
        }

        T & operator[](int i){
            if(i < low || i > high){
                cout<<"index "<<i<<" out of bound(SA)"<<endl;
                exit(1);
            }
            return p[i-low];
        }
        SA & operator=(const SA &other){
            if(this == &other)return *this;
            delete [] p;
            int size = other.high - other.low + 1;
            p = new T[size];
            for(int i = 0; i < size; i++){
                p[i] = other.p[i];
            }
            high = other.high;
            low = other.low;
            return *this;
        }
        friend ostream &operator<<(ostream &os, SA other){
            int size = other.high - other.low + 1;
            for (int i = 0; i < size; i++){
                cout << other.p[i] << " ";
            }
            cout << endl;
            return os;
        }
};

int main(){
    SA<int>ar(0,5);
    ar[0] = 1;
    ar[1] = 2;
    ar[2] = 3;
    ar[3] = 4;
    ar[4] = 5;

    for(SA<int>::Iterator i = ar.begin(); i != ar.end(); i++){
        cout << *i << " ";
    }
    ar.find(ar.begin(),ar.end(),5);

///////////////////////////////////////////////////////////////////////

    SA<char> cr(0,5);
    cr[0] = 'a';
    cr[1] = 'b';
    cr[2] = 'c';
    cr[3] = 'd';
    cr[4] = 'e';
    
    for(SA<char>::Iterator i = cr.begin(); i != cr.end(); i++){
        cout << *i << " ";
    }
    cr.find(cr.begin(),cr.end(),'c');

}



