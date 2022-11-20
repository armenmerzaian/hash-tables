/*************************************************************/
/*                                                           */
/*  Starter file for a2                                      */
/*                                                           */
/*  Author1 Name: <name here>                                */
/*      - class/function list/main author or main checker    */
/*  Author2 Name: <name here>                                */
/*      - class/function list/main author or main checker    */
/*                                                           */
/*************************************************************/

#include <string>
#include <utility>
#include <functional>
#include "mylist.h"

template <class TYPE>
class Table{
public:
    Table(){}
    virtual bool insert(const std::string& key, const TYPE& value)=0;
    virtual bool modify(const std::string& key, const TYPE& value)=0;
    virtual bool remove(const std::string& key)=0;
    virtual bool find(const std::string& key, TYPE& value)=0;
    virtual int numRecords() const = 0;
    virtual bool isEmpty() const = 0;
    virtual int capacity() const = 0;
    virtual ~Table(){}
};

template <class TYPE>
class SimpleTable:public Table<TYPE>{

    struct Record{
        TYPE data_;
        std::string key_;
        Record(const std::string& key, const TYPE& data){
            key_=key;
            data_=data;
        }

    };

    Record** records_;   //the table
    int capacity_;       //capacity of the array

    void grow(){
        Record** newarray=new Record*[capacity_*2+1];
        int sz = numRecords();

        for(int i=0;i<sz;i++){
            newarray[i]=records_[i];
        }
        capacity_*=2;
        delete [] records_;
    }
public:
    SimpleTable(int capacity);
    SimpleTable(const SimpleTable& rhs);
    SimpleTable(SimpleTable&& rhs);
    virtual bool insert(const std::string& key, const TYPE& value);
    virtual bool modify(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const SimpleTable& operator=(const SimpleTable& rhs);
    virtual const SimpleTable& operator=(SimpleTable&& rhs);
    virtual ~SimpleTable();
    virtual bool isEmpty() const{return numRecords()==0;}
    virtual int numRecords() const;
    virtual int capacity() const {return capacity_;}

};

template <class TYPE>
int SimpleTable<TYPE>::numRecords() const{
    int rc=0;
    for(int i=0;records_[i]!=nullptr;i++){
        rc++;
    }
    return rc;
}



template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity): Table<TYPE>(){
    records_=new Record*[capacity+1];
    capacity_=capacity;
    for(int i=0;i<capacity_+1;i++){
        records_[i]=nullptr;
    }
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& rhs){
    records_=new Record*[rhs.capacity_+1];
    capacity_=rhs.capacity_;
    for(int i=0;i<capacity_+1;i++){
        records_[i]=nullptr;
    }
    for(int i=0;i<rhs.numRecords();i++){
        insert(rhs.records_[i]->key_,rhs.records_[i]->data_);
    }
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& rhs){
    capacity_=rhs.capacity_;
    records_=rhs.records_;
    rhs.records_=nullptr;
    rhs.capacity_=0;
}

template <class TYPE>
bool SimpleTable<TYPE>::insert(const std::string& key, const TYPE& value){
    int idx=-1;
    int sz=numRecords();
    bool rc=false;
    for(int i=0;i<sz;i++){
        if(records_[i]->key_ == key){
            idx=i;
        }
    }
    if(idx==-1){
        if(sz == capacity_){
            grow();
        }
        records_[numRecords()]=new Record(key,value);
        for (int i=0; i<sz-1; i++) {      
            for (int j=0; j<sz-1-i; j++){   
                if (records_[j+1]->key_ < records_[j]->key_) {    
                    Record* tmp = records_[j];             
                    records_[j] = records_[j+1];        
                    records_[j+1] = tmp;           
                }
            }
        }
        rc=true;
    }

    return rc;
}

template <class TYPE>
bool SimpleTable<TYPE>::modify(const std::string& key, const TYPE& value){
    int idx=-1;
    bool rc=false;
    for(int i=0;i<numRecords();i++){
        if(records_[i]->key_ == key){
            idx=i;
        }
    }
    if(idx!=-1){
        records_[idx]->data_=value;
    }
    return rc;
}


template <class TYPE>
bool SimpleTable<TYPE>::remove(const std::string& key){
    int idx=-1;
    for(int i=0;i<numRecords();i++){
        if(records_[i]->key_ == key){
            idx=i;
        }
    }
    if(idx!=-1){
        delete records_[idx];
        for(int i=idx;i<numRecords()-1;i++){
            records_[i]=records_[i+1];
        }
        records_[numRecords()-1]=nullptr;
        return true;
    }
    else{
        return false;
    }
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const std::string& key, TYPE& value){
    int idx=-1;
    int size = numRecords();
    for(int i=0;i<size;i++){
        if(records_[i]->key_ == key){
            idx=i;
        }
    }
    if(idx==-1){
        return false;
    }
    else{
        value=records_[idx]->data_;
        return true;
    }
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& rhs){
    if(this!=&rhs){
        if(records_){
            while(numRecords() != 0){
                remove(records_[0]->key_);
            }
            delete [] records_;
        }
        records_=new Record*[rhs.capacity_+1];
        capacity_=rhs.capacity_;
        for(int i=0;i<capacity_;i++){
            records_[i]=nullptr;
        }
        for(int i=0;i<rhs.numRecords();i++){
            insert(rhs.records_[i]->key_,rhs.records_[i]->data_);
        }

    }
    return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& rhs){
    if(records_){
        while(numRecords() != 0){
            remove(records_[0]->key_);
        }
        delete [] records_;
    }
    records_=rhs.records_;
    capacity_=rhs.capacity_;
    rhs.records_=nullptr;
    rhs.capacity_=0;

    return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable(){
    if(records_){
        int sz=numRecords();
        for(int i=0;i<sz;i++){
            remove(records_[0]->key_);
        }
        delete [] records_;
    }
}
template <class TYPE>
class ChainingTable:public Table<TYPE>{
public:
    ChainingTable(int capacity, double maxLoadFactor=1.0);
    ChainingTable(const ChainingTable& other);
    ChainingTable(ChainingTable&& other);
    double loadFactor() const;
    virtual bool insert(const std::string& key, const TYPE& value);
    virtual bool modify(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const ChainingTable& operator=(const ChainingTable& other);
    virtual const ChainingTable& operator=(ChainingTable&& other);
    virtual ~ChainingTable();
    virtual bool isEmpty() const;
    virtual int numRecords() const;
    virtual int capacity() const;

};
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int capacity, double maxLoadFactor): Table<TYPE>(){

}

template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other){

}
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other){

}
template <class TYPE>
bool ChainingTable<TYPE>::insert(const std::string& key, const TYPE& value){
    return true;

}

template <class TYPE>
bool ChainingTable<TYPE>::modify(const std::string& key, const TYPE& value){
    return true;
}

template <class TYPE>
bool ChainingTable<TYPE>::remove(const std::string& key){
    return true;
}

template <class TYPE>
bool ChainingTable<TYPE>::find(const std::string& key, TYPE& value){
    return true;
}

template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other){
    return *this;

}

template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other){
    return *this;

}

template <class TYPE>
ChainingTable<TYPE>::~ChainingTable(){

}

template <class TYPE>
bool ChainingTable<TYPE>::isEmpty() const {
    return false;
}

template <class TYPE>
int ChainingTable<TYPE>::numRecords() const {
    return 0;
}
template <class TYPE>
int ChainingTable<TYPE>::capacity() const {
    return 0;
}

template <class TYPE>
double ChainingTable<TYPE>::loadFactor() const {
    return 0;
}



template <class TYPE>
class LPTable:public Table<TYPE>{
public:
    LPTable(int capacity, double maxLoadFactor=0.7);
    LPTable(const LPTable& other);
    LPTable(LPTable&& other);
    double loadFactor() const;
    virtual bool insert(const std::string& key, const TYPE& value);
    virtual bool modify(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const LPTable& operator=(const LPTable& other);
    virtual const LPTable& operator=(LPTable&& other);
    virtual ~LPTable();
    virtual bool isEmpty() const;
    virtual int numRecords() const;
    virtual int capacity() const;

};
template <class TYPE>
LPTable<TYPE>::LPTable(int capacity, double maxLoadFactor): Table<TYPE>(){

}

template <class TYPE>
LPTable<TYPE>::LPTable(const LPTable<TYPE>& other){

}
template <class TYPE>
LPTable<TYPE>::LPTable(LPTable<TYPE>&& other){

}
template <class TYPE>
bool LPTable<TYPE>::insert(const std::string& key, const TYPE& value){
    return true;

}

template <class TYPE>
bool LPTable<TYPE>::modify(const std::string& key, const TYPE& value){
    return true;

}

template <class TYPE>
bool LPTable<TYPE>::remove(const std::string& key){
    return true;
}

template <class TYPE>
bool LPTable<TYPE>::find(const std::string& key, TYPE& value){
    return true;
}

template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(const LPTable<TYPE>& other){
    return *this;

}

template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(LPTable<TYPE>&& other){
    return *this;

}

template <class TYPE>
LPTable<TYPE>::~LPTable(){

}

template <class TYPE>
bool LPTable<TYPE>::isEmpty() const {
    return false;
}

template <class TYPE>
int LPTable<TYPE>::numRecords() const {
    return 0;
}
template <class TYPE>
int LPTable<TYPE>::capacity() const {
    return 0;
}
template <class TYPE>
double LPTable<TYPE>::loadFactor() const {
    return 0;
}


