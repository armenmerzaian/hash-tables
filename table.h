/*************************************************************/
/*                                                           */
/*  Starter file for a2                                      */
/*                                                           */
/*  Author1 Name: Yuanqing Dai                               */
/*  Author2 Name: Armen Merzanian                            */
/*                                                           */
/*************************************************************/

#include <string>
#include <utility>
#include <functional>
#include "mylist.h"

#include <iostream>
using namespace std;
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
class ChainingTable :public Table<TYPE>{
	struct Record{
		TYPE data_;
		std::string key_;

		Record(const string& key = "", const TYPE& data = TYPE{}){
			key_ = key;
			data_ = data;
		}

		bool operator==(const Record& r){
			return key_ == r.key_;
		}
	};

    CacheList<Record>* records_;
    int capacity_;
    int maxLoadFactor_;
    std::hash<std::string> hashFunction;
    int size_ = 0;

	void grow(){
		capacity_ *= 2;
		CacheList<Record>* biggerRecords = records_;
		records_ = new CacheList<Record>[capacity_];

		for (int i = 0; i < capacity_ / 2; i++){
			for (typename CacheList<Record>::iterator it = biggerRecords[i].begin(); it != biggerRecords[i].end(); it++){
				size_t idx = hashFunction((*it).key_)%capacity_;
				records_[idx].insert(*it);
			}
		} 
	}

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

/* Constructor that takes capacity and max load factor */

template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int capacity, double maxLoadFactor): Table<TYPE>(){
    capacity_= capacity;
    maxLoadFactor_= maxLoadFactor;
	records_= new CacheList<Record>[capacity_];
}

/* Copy Constructor */
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other){
	records_=nullptr;
	*this=other;
}

/* Move Constructor */
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other){ ////goood
    maxLoadFactor_ = other.maxLoadFactor_;
	capacity_ = other.capacity_;
	size_ = other.numRecords();
	records_ = other.records_;

	other.maxLoadFactor_ = 0;
	other.capacity_ = 0;
	other.size_ = 0;
	other.records_ = nullptr; 
}

/* This function inserts a key value pair in the table */
template <class TYPE>
bool ChainingTable<TYPE>::insert(const string& key, const TYPE& value){
    int val = value;
	Record temp(key, value); 

	if (find(key, val) == false){
		if (loadFactor() >= maxLoadFactor_)
            grow();
		records_[hashFunction(key)%capacity_].insert(temp);
        size_++;
        return true;
	}
    return false; 
}

/* This function modifies the matching key and return true if found */
template <class TYPE>
bool ChainingTable<TYPE>::modify(const std::string& key, const TYPE& value){
    TYPE temp;
    bool found= find(key, temp);
    auto i = hashFunction(key)%capacity();

	if(found != false){
		(*(records_[i].begin())).data_= value; 
        return true;
	} 
    return false;
}

/* This function from a key pair from the table and returns true if found */
template <class TYPE>
bool ChainingTable<TYPE>::remove(const string& key){
  int idx = hashFunction(key) % capacity_;
  CacheList<Record>* temp = &records_[idx];

  if(temp != nullptr){
    Record rec(key, TYPE{});
    typename CacheList<Record>::iterator it = temp->search(rec);
    if (it != temp->end()) {
      temp->erase(it);
      size_--;
      return true;
    }
  }
 
  return false;
}

/* This function looks for a key pair in the table and returns true if found */
template <class TYPE>
bool ChainingTable<TYPE>::find(const string& key, TYPE& value){
    int idx = hashFunction(key)%capacity_;
    CacheList<Record>* temp = &records_[idx];

    if(temp != nullptr)
    {
        Record rec(key, TYPE{});
        typename CacheList<Record>::const_iterator it = temp->search(rec);
        if (it!=temp->end()) {
            value=(*it).data_;
            return true;
        }
    }

  return false;
}

/* Copy Assignment Operator */
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other){
    if (this != &other){
		maxLoadFactor_ = other.maxLoadFactor_;
		size_ = other.size_;
        capacity_ = other.capacity_;
		delete[] records_;
		records_ = new CacheList<Record>[capacity_];
		for (int i = 0; i < capacity_; i++){
			records_[i] = other.records_[i];
		}
	} 
    return *this;
}

/* Move Assignment Operator */
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other){
    records_ = other.records_;
    maxLoadFactor_ = other.maxLoadFactor_;
	capacity_ = other.capacity_;
	size_ = other.size_;
		
	other.records_ = nullptr;
    other.maxLoadFactor_ = 0;
	other.capacity_ = 0;
	other.size_ = 0;	

	return *this; 
}


template <class TYPE>
ChainingTable<TYPE>::~ChainingTable(){
	delete[] records_;
    records_ = nullptr;
}

template <class TYPE>
bool ChainingTable<TYPE>::isEmpty()const{
    return numRecords() == 0;
}
 
template <class TYPE>
int ChainingTable<TYPE>::numRecords() const {
    return size_;
}

template <class TYPE>
int ChainingTable<TYPE>::capacity() const{
	return capacity_;
}

template <class TYPE>
double ChainingTable<TYPE>::loadFactor() const { 
    return numRecords()/capacity_;
}

template <class TYPE>
class LPTable:public Table<TYPE>{
        struct Record{
            TYPE data_;
            std::string key_;
            Record() {}
            Record(const std::string& key, const TYPE& data){
                key_=key;
                data_=data;
            }
        };

    Record** records_;
    int capacity_ = 0;
    double maxLoadFactor_ = 0.7;
    std::hash<std::string> hashFunction;
    int size_ = 0;

    void grow(){
        capacity_=capacity_*2;
        Record** newArr = new Record*[capacity_];
        for(int i = 0; i < capacity_; i++){
            newArr[i] = nullptr;
        }
        for (int i = 0; i < capacity_/2; i++){
            if (records_[i]!=nullptr){
                int hash = hashFunction(records_[i]->key_)%capacity_;
                while (newArr[hash] != NULL){
                    hash = (hash+1)%capacity_;
                }
                newArr[hash] = new Record(records_[i]->key_,records_[i]->data_);
            }
        }
        delete[] records_;
        records_ = newArr;
    }
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

/* Constructor that takes capacity and max load factor */
template <class TYPE>
LPTable<TYPE>::LPTable(int capacity, double maxLoadFactor): Table<TYPE>(){
    capacity_ = capacity;
    maxLoadFactor_ = maxLoadFactor;
    records_ = new Record*[capacity];
    for(int i =0; i < capacity_; i++){
        records_[i] = nullptr;
    }
}

/* Copy Constructor */
template <class TYPE>
LPTable<TYPE>::LPTable(const LPTable<TYPE>& other){
    records_=nullptr;
	*this=other;
}

/* Move Constructor */
template <class TYPE>
LPTable<TYPE>::LPTable(LPTable<TYPE>&& other){
    records_=other.records_;
    capacity_=other.capacity_;
    size_=other.size_;
    other.records_=nullptr;
    other.capacity_=0;
    other.size_=0;
}

/* This function inserts a key value pair in the table */
template <class TYPE>
bool LPTable<TYPE>::insert(const std::string& key, const TYPE& value){
    int hash = hashFunction(key)%capacity_;
    while (records_[hash] != NULL && records_[hash]->key_ != key && records_[hash]->key_ != "spongebob"){
        hash = (hash + 1) % capacity_;
    }
    if(records_[hash]!=NULL){
        return false;
    }
    records_[hash]=new Record(key,value); 
    size_++;
    if(size_ > maxLoadFactor_*capacity_) {
        grow();
    }
    return true; 
}

/* This function modifies the matching key and return true if found */
template <class TYPE>
bool LPTable<TYPE>::modify(const std::string& key, const TYPE& value){
    int hash = hashFunction(key)%capacity_;
    while (records_[hash] != NULL) {
        if (records_[hash]->key_ == key) {
            records_[hash]->key_ = key;
            records_[hash]->data_ = value;
            return true;
        }
        hash = (hash + 1) % capacity_;
    }
    return false;
}

/* This function from a key pair from the table and returns true if found */
template <class TYPE>
bool LPTable<TYPE>::remove(const std::string& key){
    int hash = hashFunction(key)%capacity_;
    while (records_[hash] != NULL) {
        if (records_[hash]->key_ == key) {
            records_[hash]->key_ = "spongebob";
            size_--;
            return true;
        }
        hash = (hash + 1) % capacity_;
    }
    return false;
}

/* This function looks for a key pair in the table and returns true if found */
template <class TYPE>
bool LPTable<TYPE>::find(const std::string& key, TYPE& value){
    int hash = hashFunction(key)%capacity_;
    while (records_[hash] != NULL && records_[hash]->key_ != key) {
        hash = (hash + 1) % capacity_;
    }

    if (records_[hash] == NULL) {
        return false;
    }
    else {
        value = records_[hash]->data_;
        return true;
    }
}

/* Copy Assignment Operator */
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(const LPTable<TYPE>& other){  
    if (this != &other) {
        records_= new Record *[other.capacity_];
        maxLoadFactor_ = other.maxLoadFactor_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        for (int i = 0; i < capacity_; i++) {
            if (other.records_[i] == nullptr){
                records_[i] = nullptr;
            }
            else{
                auto key = other.records_[i]->key_;
                auto data = other.records_[i]->data_;
                records_[i] = new Record(key, data);
            }
        }
    }
    return *this;
}

/* Move Assignment Operator */
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(LPTable<TYPE>&& other){
    records_ = other.records_;
    maxLoadFactor_ = other.maxLoadFactor_;
	capacity_ = other.capacity_;
	size_ = other.size_;
		
	other.records_ = nullptr;
    other.maxLoadFactor_ = 0;
	other.capacity_ = 0;
	other.size_ = 0;	

	return *this; 
}

template <class TYPE>
LPTable<TYPE>::~LPTable(){
   delete[] records_;
}

template <class TYPE>
bool LPTable<TYPE>::isEmpty() const {
    return numRecords() == 0;
}

template <class TYPE>
int LPTable<TYPE>::numRecords() const {
    return size_;
}
template <class TYPE>
int LPTable<TYPE>::capacity() const{
    return capacity_;
}
template <class TYPE>
double LPTable<TYPE>::loadFactor() const {
    return numRecords()/capacity();
}


