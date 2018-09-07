//! Copyright [2018] <Copyright Rafael Neves de Mello Oliveira>
#ifndef STRUCTURES_STRING_LIST_H
#define STRUCTURES_STRING_LIST_H

//! This include the library that allows me to use size_t values
#include <cstdint>
//! This include the library that allows me to make exceptions
#include <stdexcept>
//! This 
#include <cstring>
//! Creating a namespace for my array list definitions
namespace structures {
//! Class
/*!
	Here are defined all the methods to the structure list of strings
	implementing using array
*/
template<typename T>
class ArrayList {
//! Public methods and variables declaration of arrai list class
 public:
    //! Constructor with no parameters
    ArrayList();
    //! Contructor with parameters
    explicit ArrayList(std::size_t max);
    //! Destructor
    ~ArrayList();

    //! Clear
    void clear();
    //! Push back
    void push_back(const T& data);
    //! Push front
    void push_front(const T& data);
    //! Insert
    void insert(const T& data, std::size_t index);
    //! Insert Sorted
    void insert_sorted(const T& data);
    //! Pop
    T pop(std::size_t index);
    //! Pop back
    T pop_back();
    //! Pop front
    T pop_front();
    //! Remove a value from the ArrayList
    void remove(const T& data);
    //! Verify if the array list is full
    bool full() const;
    //! Verify if the array list is empty
    bool empty() const;
    //! Verify if a data is in the array list
    bool contains(const T& data) const;
    //! Search if there is a data in the array
    std::size_t find(const T& data) const;
    //! Return the actual size of my list
    std::size_t size() const;
    //! Return maximum size
    std::size_t max_size() const;
    //! return a value by index
    T& at(std::size_t index);
    //!
    T& operator[](std::size_t index);
    //! return a value by index
    const T& at(std::size_t index) const;
    //!
    const T& operator[](std::size_t index) const;
//! private parameters of array list class
 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};



//-------------------------------------



//! ...
//! ArrayListString e' uma especializacao da classe ArrayList
class ArrayListString : public ArrayList<char *> {
 public:
    //! Constructor with no parameters
    ArrayListString() : ArrayList() {}
    //! Constructor with parameters
    explicit ArrayListString(std::size_t max_size) : ArrayList(max_size) {}
    //! DEstructor
    ~ArrayListString();

    //! Clear
    void clear();
    //! Push Back
    void push_back(const char *data);
    //! Push Front
    void push_front(const char *data);
    //! Insert
    void insert(const char *data, std::size_t index);
    //! Insert Sorted
    void insert_sorted(const char *data);
    //! Pop
    char *pop(std::size_t index);
    //! Pop Back
    char *pop_back();
    //! Pop Front
    char *pop_front();
    //! remove a value from the array list
    void remove(const char *data);
    //! verify if there is an element in the list
    bool contains(const char *data);
    //! Search if there is a data in the list
    std::size_t find(const char *data);
};

//! Constructor with no pararmeters
/*!
	When i instantiate this class with no parameters it creates a new
	array list with the default size of 10 (DEFAULT_SIZE) 
*/

template<typename T>
ArrayList<T>::ArrayList() {
	max_size_ = DEFAULT_MAX;
	contents = new T[max_size_];
	size_ = 0;
}
//! Constructor with parameters
/*!
	Instantiate a new array list using  the parameter that the 
	constructor receives

	obs.: size_t is an integer with no signal and it's leght is longer
	than a normal int
*/
template<typename T>
ArrayList<T>::ArrayList(std::size_t max) {
	max_size_ = max;
	contents = new T[max_size_];
	size_ = 0;
}
//! Destructor
/*!	
	I need a destructor every time I make a dinamic alocation
	Dinamic alocation is when the user can define the size of my
	space memory alocation, whice means he can set the value of the 
	size of my list by parameter 
*/
template<typename T>
ArrayList<T>::~ArrayList() {
	delete[] contents;
}
//! Clear method
/*!
	Clear the vector by setting the current size of my vector to -1,
	which is the definition of array list empty that is used here in
	the class
*/
template<typename T>
void ArrayList<T>:: clear() {
	size_ = 0;
}
//! Push back
/*!
	Insert a value in the end of my list, but here is a specification
	of my insert method, so I just call it and put as parameters the
	data I want to insert and value of "size_ + 1" because my current
	size is the last position of my list that is already occupated
*/
template<typename T>
void ArrayList<T>::push_back(const T& data) {
	insert(data, size_);
}
// Push front
/*!
	Insert a value in the begining of my list, but here is a
	specification of my insert method, so I just call it and put as 
	parameters the data I want to insert and the value 0 that
	represents the first position of my list
*/
template<typename T>
void ArrayList<T>::push_front(const T& data) {
	insert(data, 0u);
}
//! Insert
/*!
	Insert a data in the list in a position defined by the varyable 
	index which is given in the parameters.
	First I check if the array list is full and if the index given is
	valid.
*/
template<typename T>
void ArrayList<T>::insert(const T& data, std::size_t index) {
	std::size_t current = 0;
	// if (full()) {
	// 	throw std::out_of_range("Array list is full");
	// } else if(index < 0 || index > max_size_) {
	// 	throw std::out_of_range("Invalid index");
	// } else {
	// 	current = size_;
	// 	while(current > index) {
	// 		contents[current] = contents[current-1];
	// 		current--;
	// 	}
	// 	contents[index] = data;
	// 	size_ = size_ + 1;
	// }

	if (full()) {
		throw std::out_of_range("List is full haha");
	}

	if (index < 0 || index >= max_size_) {
		throw std::out_of_range("Invalid index");
	}

	current = size_;

	while(current > index) {
		contents[current] = contents[current - 1];
		current--;
	}

	contents[index] = data;

	size_++;
}
//! Insert sorted
/*!
	Insert a value in the list in a sorted way.
	First it verifies if it is possible insert a value by checking if
	the list is full or not, then It starts checking if the data I 
	want to insert is grater or not of the value in the list position
	marked by the variable postion. The loop goes along all the vector
	or until satisfy the condition. After that It make a call to the
	insert method to put the value in the list 
*/ 
template<typename T>
void ArrayList<T>::insert_sorted(const T& data) {
	std::size_t current = 0;
	// if(full()) {
	// 	throw std::out_of_range("List is full");
	// } else {
		while (data > contents[current] && current < size_) {
			current++;
		}
		insert(data, current);
}
//! Pop
/*!
	Return a value by the index that is given by parameter.
	First I verify if the list is empty and if the index given is
	valid. 
*/
template<typename T>
T ArrayList<T>::pop(std::size_t index) {
	
	T value;
	std::size_t current;

	if (empty()) {
		throw std::out_of_range("Empty List");
	} else if (index < 0 || index >= size_) {
		throw std::out_of_range("Invalid index");
	} else {

		current = index;
		value = contents[index];
		size_--;
		while(current < size_) {
			contents[current] = contents[current + 1];
			current++;
		}

	}

	return value;
}
//! Pop back
/*!
	Get a value from the back of my list, but here is a specification
	of my method pop so I just call it and set the parameters to get
	the value of the last position which is defined by the variable 
	size_ - 1, because my variable size_ always points to my empty
	space.
*/
template<typename T>
T ArrayList<T>::pop_back() {
	return pop(size_ - 1);
}
//! Pop front
/*!
	Get a value from the begining of my list, but here is a
	specification of my method pop, so I just call it and set the
	parameters to get the value of the first position defined by 0
	(the first valid position of my vector)
*/
template<typename T>
T ArrayList<T>::pop_front() {
	return pop(0);
}


template<typename T>
void ArrayList<T>::remove(const T& data) {
	if(contains(data)) {
		pop(find(data));
	}
}
//! Full
/*!
	Verify if the list is full by checking if my current size (size_)
	reached the maximum size of my list and return a logic answer
*/
template<typename T>
bool ArrayList<T>::full() {
	return(size_ == max_size_);
}
//! Empty
/*!
	Verify if the list is empty by checking if my current size (size_)
	still is the value that defines a empty list, which is 0
*/
template<typename T>
bool ArrayList<T>::empty() {
	return (size_ == 0);
}
//! Contains
/*!
	Just check if there is a specific data in the list. It is donne 
	by calling the function find and making a boolean verification if
	the index is different of max_size_
*/
template<typename T>
bool ArrayList<T>::contains(const T& data) const {
    return (find(data) != max_size_);
}
//! Find
/*!
	First I set the "index" variable to have the same value of my
	"max_size_" variable, doing that I guarantee when the false
	conditiong (the value is not founded) is reached. Normally
	we use -1 value, byt because I'm using std::size_t I need set
	"index" a non valid value to mark this condition of not finding
	the value searched.

	Look if there is a specific data in the list and return the
	position of this value if it is founded.

	obs.: If it is not founded the value that is returned is the
	value previously setted (max_size_)
*/
template<typename T>
std::size_t ArrayList<T>::find(const T& data) const {
	
	std::size_t index = max_size_;

	for(int i = 0; i < size_; i++) {
		if(contents[i] == data) {
			index = i;
			break;
		}
	}

	return index;
}
//! Size
/*!
	Gives the current size of the list returning the value of my
	variable size_ + 1 (because my list starts in -1)
*/
template<typename T>
std::size_t ArrayList<T>::size() const {
	return size_;
}
//! Maximum size
/*!
	Gives the maximum size of the list by returning the value of the
	variable max_size_
*/
template<typename T>
std::size_t ArrayList<T>:: max_size() const {
	return max_size_;
}

template<typename T>
T& ArrayList<T>::at(std::size_t index) {
	if(empty()) {
		std::out_of_range("Empty List");
	} else if (index >= size_ || index < 0) {
		throw std::out_of_range("Invalid index");
	} else {
		return contents[index];
	}
}

template<typename T>
T& ArrayList<T>::operator[](std::size_t index) {
	if(empty()) {
		throw std::out_of_range("Empty List");
	} else if (index >= size_ || index < 0) {
		throw std::out_of_range("Invalid index");
	} else {
		return contents[index];
	}
}

template<typename T>
const T& ArrayList<T>::at(std::size_t index) const {
	if(empty()) {
		std::out_of_range("Empty List");
	} else if (index >= size_ || index < 0) {
		throw std::out_of_range("Invalid index");
	} else {
		return contents[index];
	}
	
}

template<typename T>
const T& ArrayList<T>::operator[](std::size_t index) const {
	if(empty()) {
		throw std::out_of_range("Empty List");
	} else if (index >= size_ || index < 0) {
		throw std::out_of_range("Invalid index");
	} else {
		return contents[index];
	}
}
template<typename T>
void ArrayList<T>::printList() {
	for(auto i = 0; i < size_; i++) {
		//std::printf(contents[i]);
		std::printf("%d\n", contents[i]);
	}
}

//------------------------------------------------------------



}  // namespace structures

#endif


popArrayListString() : pop() {

}

ArrayListString::pop(){
	ArrayList::pop();
}


