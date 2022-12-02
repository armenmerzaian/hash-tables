/********************************************************************/
/*                                                                  */
/*  Put your linked list code from A1 into                          */
/*  this file                                                       */
/*                                                                  */
/********************************************************************/

#include <utility>
#include <iostream>

using namespace std;

template <typename T>
/*
	CacheList is a Doubly-Linked List which automatically caches the most recently
	accessed node by shifting it to the front of the list for fast future
	reading.
*/
class CacheList{

	/*
		public class of the Node objects that make up the Linked List
	*/
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		unsigned int access_;
		Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
			access_ = 0;
		}

	};
	Node* front_;
	Node* back_;
	Node* insertAt_;

	int m_size = 0;
	bool m_empty = true;

public:
	/*
		public class of Constant Iterator that allows the list to be iterated
		through simply. Similar to a normal array.
	*/
	class const_iterator{
		friend class CacheList;
		Node *curr_;
	public:
		//Constructs an iterator pointing to the Node passed as an argument
		const_iterator(Node *n){
			curr_ = n;
		}
		//Constructs an iterator that points to null
		const_iterator() {
			curr_ = nullptr;
		}
		//This function allows the iterator to increment via prefix ++
		const_iterator operator++(){
			curr_ = curr_->next_;
			return *this;
		}
		//This function allows the iterator to increment via postfix ++
		const_iterator operator++(int){
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}
		//This function allows the iterator to increment via prefix --
		const_iterator operator--(){
			curr_ = curr_->prev_;
			return *this;
		}
		//This function allows the iterator to increment via postfix --
		const_iterator operator--(int){
			const_iterator old = *this;
			curr_ = curr_->prev_;
			return old;
		}
		//This function allows the iterator to compare Nodes to true
		bool operator==(const_iterator rhs){
			bool rc = false;
			if (curr_ == rhs.curr_) {
				rc = true;
			}
			return rc;
		}
		//This function allows the iterator to compare Nodes to false
		bool operator!=(const_iterator rhs){
			return !(*this == rhs);
		}
		//This function allows the iterator to be be dereferenced but remain constant
		const T& operator*()const{
			return curr_->data_;
		}
	};
	/*
		public class of Iterator that allows the list to be iterated
		through simply and be mutated. Similar to a normal array.
	*/
	class iterator:public const_iterator{
		friend class CacheList;
	public:
		//Constructs an iterator pointing to the Node passed as an argument
		iterator(Node *n = nullptr){
			this->curr_ = n;
		}
		//This function allows the iterator to increment via prefix ++
		iterator operator++(){
			this->curr_ = this->curr_->next_;
			return *this;
		}
		//This function allows the iterator to increment via postfix ++
		iterator operator++(int){
			iterator old = *this;
			this->curr_ = this->curr_->next_;
			return old;
		}
		//This function allows the iterator to increment via prefix --
		iterator operator--(){
			this->curr_ = this->curr_->prev_;
			return *this;
		}
		//This function allows the iterator to increment via postfix --
		iterator operator--(int){
			iterator old = *this;
			this->curr_ = this->curr_->prev_;
			return old;
		}
		//This function allows the iterator to be be dereferenced and mutated
		T& operator*(){
			return this->curr_->data_;
		}
		//This function allows the iterator to be be dereferenced but remain constant
		const T& operator*()const{
			return this->curr_->data_;
		}
	};
	CacheList();
	~CacheList();
	CacheList(const CacheList& rhs); //copy constructor
	CacheList& operator=(const CacheList& rhs); //copy assignment
	CacheList(CacheList&& rhs); //move constructor
	CacheList& operator=(CacheList&& rhs); //move assignment
	iterator begin();
	iterator end();
	const_iterator cbegin() const;
	const_iterator cend() const;
	iterator insert(const T& data);
	iterator search(const T& data);
	iterator erase(iterator it);
	/*
		This function will delete the data-filled
		Nodes within the Linked List and deallocate their memory.
		This function will relink Sentinel nodes to reset the Listed List
	*/
	void deleteList() {
		Node* current = front_->next_;
		Node* next;

		while (current != back_) {
			next = current->next_;
			delete current;
			current = next;
		} 
		front_->next_ = back_;
		back_->prev_ = front_;
	}
	/*
		This function will take a reference to data of type <T>
		and it's access count and add it to the back of the Linked List.
	*/
	void pushBack(const T& data, const int access){
		//push into our current list
		Node* dataNode = new Node(data, back_, back_->prev_);
		dataNode->access_ = access;
		back_->prev_->next_ = dataNode;
		back_->prev_ = dataNode;
	}
	
	bool empty() const; //return true/false
	int size() const;	//return getSize
};

template <typename T>
CacheList<T>::CacheList(){
	front_=new Node();
	back_=new Node();
	front_->next_=back_;
	back_->prev_=front_;
	//insertAt_ = new Node();
}

/*
	This function will call the deleteList() function
	to empty the Linked List then further deallocate memory
	for the Sentinels and the Linked List itself to fully 
	destruct the object
*/
template <typename T>
CacheList<T>::~CacheList(){
	deleteList();
	delete front_;
	delete back_;
}

/*
	This function performs a deep copy of the Linked List
	by calling the copy assignment operator
*/
template <typename T>
CacheList<T>::CacheList(const CacheList& rhs){
	*this = rhs;
}

/*
	This function performs a deep copy of the Linked List
	through the (=) operator.
	It allocated memory to the current Linked List
	then iterates through the original List to copy into the current.
	It take a CacheList as an argument and returns the deeply copied
	CacheList
*/
template <typename T>
CacheList<T>& CacheList<T>::operator=(const CacheList& rhs){
	if (this == &rhs) return *this;
	//delete current list
	else if (rhs.empty()) {
		deleteList(); 
		return *this;
	}
	
	front_=new Node();
	back_=new Node();
	front_->next_=back_;
	back_->prev_=front_;
	deleteList();
	
	
	for (Node *p = rhs.front_->next_; p != rhs.back_; p = p->next_) {
		pushBack(p->data_, p->access_);
	}

	m_empty = rhs.empty();
	m_size = rhs.size();
	//this->front_ = t
	return *this;
}

/*
	This function performs a shallow copy of the Linked List
	by calling the move assignment operator
*/
template <typename T>
CacheList<T>::CacheList(CacheList&& rhs){
	*this = std::move(rhs);

}

/*
	This function performs a shallow copy of the Linked List
	through the (=) operator.
	It allocated memory to the current Linked List
	then links the first and last data-full Nodes of the old list to the
	new List sentinels.
	It take a CacheList as an argument and returns the shallow copied
	CacheList
*/
template <typename T>
CacheList<T>& CacheList<T>::operator=(CacheList&& rhs){
	front_=new Node();
	back_=new Node();
	front_->next_=back_;
	back_->prev_=front_;
	deleteList();
	//std::swap( front_, rhs.front_ );
    //std::swap( back_, rhs.back_ );
	this->front_->next_ = rhs.front_->next_;
	this->front_->next_->prev_ = this->front_;
	this->back_->prev_ = rhs.back_->prev_;
	this->back_->prev_->next_ = this->back_;

	rhs.front_->next_ = rhs.back_;
	rhs.back_->prev_ = rhs.front_;
	return *this;
}

/*
	This function sets the iterator the first data-full Node
	in the Linked List
*/
template <typename T>
typename CacheList<T>::iterator CacheList<T>::begin(){
	return iterator(front_->next_);
}
/*
	This function sets the iterator to the back sentinel data-less Node
	in the Linked List
*/
template <typename T>
typename CacheList<T>::iterator CacheList<T>::end(){
	return iterator(back_);
}

/*
	This function sets the constant iterator the first data-full Node
	in the Linked List 
*/
template <typename T>
typename CacheList<T>::const_iterator CacheList<T>::cbegin() const{
	return const_iterator(front_->next_);
}

/*
	This function sets the constant iterator to the back sentinel data-less Node
	in the Linked List
*/
template <typename T>
typename CacheList<T>::const_iterator CacheList<T>::cend() const{
	return iterator(back_);
}

/*
	creates a new node with number of access set to 0. 
	This node is to be placed before all other nodes that have access counts of 0. 
	Function returns iterator to newly inserted node.
*/
template <typename T>
typename CacheList<T>::iterator CacheList<T>::insert(const T& data){
	Node* newNode = new Node(data);
	if (empty()) {
		newNode->next_ = back_;
		newNode->prev_ = front_;
		front_->next_ = newNode;
		back_->prev_ = newNode;
	}
	else {
		Node* ptr;
		ptr = front_;
		while (ptr->next_ != back_) {

			if (ptr->next_->access_ == 0) {
				newNode->next_ = ptr->next_;
				newNode->prev_ = ptr;
				ptr->next_ = newNode;
				newNode->next_->prev_ = newNode;
				break;
			}
			ptr = ptr->next_;
		}
	}

	m_size++;
	m_empty = false;
	return iterator(newNode);
}

/*
	This function accepts as argument a key of the unknown data type T. 
	The function finds and returns an iterator to the node containing a matching key. 
	It will also adjust the linked list and found node by moving it closer to the front
	such that the access count within the linked list sorted from highest to lowest.
	Function returns an iterator to the node if found, end() if it is not.
*/
template <typename T>
typename CacheList<T>::iterator CacheList<T>::search(const T& data){
	Node* k;
	for(k = front_->next_; k != back_; k = k->next_){
		if(k->data_ == data){
			k->access_++;
			k->next_->prev_ = k->prev_;
			k->prev_->next_ = k->next_;
			Node *j = front_->next_;
			while (j != back_) {
				if (j->access_ <= k->access_) {
					break;}

				j = j->next_;
			}
			j->prev_->next_ = k;
			k->prev_ = j->prev_;
			j->prev_ = k;
			k->next_ = j;
			return iterator(k);
		}
	}
	return this->end();
}

/*
	This function removes a node referred to by loc. 
	Function returns an iterator to the node that follows the removed node
*/
template <typename T>
typename CacheList<T>::iterator CacheList<T>::erase(iterator it){
	Node *k = front_->next_;
	bool next = true;
	while(next){
		if(k->data_ == *it){
			next = false;
			k->prev_->next_ = k->next_;
			k->next_->prev_ = k->prev_;
			//free(k);
			m_size--;
			break;
		}
		k = k->next_;
	}
	delete k;
	return ++it;
}

/*
	This function gets the value of the member variable m_empty;
*/
template <typename T>
bool CacheList<T>::empty() const{
	return m_empty;
}
/*
	This function gets the value of the member variable m_size;
*/
template <typename T>
int CacheList<T>::size() const{
	return m_size;
}