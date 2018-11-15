//! Copyright [2018] <Copyright Rafael Neves de Mello Oliveira>
#ifndef STRUCTURES_STRING_LIST_H
#define STRUCTURES_STRING_LIST_H

//! This include the library that allows me to use size_t values
#include <cstdint>
//! This include the library that allows me to make exceptions
#include <stdexcept>
//! This include the library that allows me to work with strings
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
//! Public methods and variables declaration of array list class
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
    //! Return a value
    T& operator[](std::size_t index);
    //! return a value by index
    const T& at(std::size_t index) const;
    //! Return a value
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
//! ArrayListString  class is an specilization of ArrayList class
class ArrayListString : public ArrayList<char *> {
 public:
    //! Constructor with no parameters
    ArrayListString();
    //! Constructor with parameters
    explicit ArrayListString(std::size_t max_size);
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

		//  Implementation of superclass (ArrayList) methods
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
bool ArrayList<T>::full() const {
	return(size_ == max_size_);
}
//! Empty
/*!
	Verify if the list is empty by checking if my current size (size_)
	still is the value that defines a empty list, which is 0
*/
template<typename T>
bool ArrayList<T>::empty() const {
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

//! at
/*!
	Acces the value in the index but without make a copy of this value
*/
template<typename T>
T& ArrayList<T>::at(std::size_t index) {
	if(empty()) {
		std::out_of_range("Empty List");
	}
	if (index >= size_ || index < 0) {
		throw std::out_of_range("Invalid index");
	}
	return contents[index];
}

//! operator
/*!

*/
template<typename T>
T& ArrayList<T>::operator[](std::size_t index) {
	if(empty()) {
		throw std::out_of_range("Empty List");
	}
	if (index >= size_ || index < 0) {
		throw std::out_of_range("Invalid index");
	}
	return contents[index];
}

//! at
/*!
	Acces the value in the index but without make a copy of this value	
*/
template<typename T>
const T& ArrayList<T>::at(std::size_t index) const {
	if(empty()) {
		std::out_of_range("Empty List");
	}
	if (index >= size_ || index < 0) {
		throw std::out_of_range("Invalid index");
	}
		return contents[index];
}

//! operator
/*!

*/
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

//------------------------------------------------------------

		//  Implementation of subclass (ArrayListString) methods

//! Constructor with no parameters
/*!
	Here the single colon means inheritance, i mean the constructor
	ArrayListString() is implemented like the constructor ArrayList()
	of my super class
*/
ArrayListString::ArrayListString() : ArrayList::ArrayList() {
}
//! Constructor with parameters
/*!
	Here the single colon means inheritance, I mean the constructor
	ArrayListString(std::size_t max_size) is implemented like the constructor 
	ArrayList(std::size_t max_size) of my super class
*/
ArrayListString::ArrayListString(std::size_t max_size)
:ArrayList::ArrayList(max_size) {
}

//! Destructor
ArrayListString::~ArrayListString() {
	for(std::size_t i = 0; i < size(); i++) {
		delete at(i);
	}
}
//! Clear method
/*!
	Clear the list by calling the 'clear' method from the
	superclass, which just set the size of my list to 0. 
*/
void ArrayListString::clear() {
	ArrayList::clear();
}

//! Push Back
/*!
	Insert a new string at the end of my list, but this method is a
	specification of my 'insert' method, so I just call it given 
	as parameters the string I want to insert and the size (last
	position empty). Because my "size_" is private I access it
	using the method 'size()' as a getter

*/
void ArrayListString::push_back(const char *data) {
	insert(data, size());
}

//! Push Front
/*!
	Isert a new string at the begining of my list, but this is a
	specification of my 'insert', so i just call it given as
	parameters the string I want to insert and the position 0
	(begining of my list).
*/
void ArrayListString::push_front(const char *data) {
	insert(data, 0u);
}

//! Insert
/*!
	Insert a new string in the list by index. First I check if the list
	is empty and if the index given is valid.
	
	0. create a pointer to char

	1. I created a int (sizeVector) to get, using 'strlen()' the 
	size of my string given by parameter (data), and I do that
	because I have to alocate this string in a vector before insert
	in my list. I increment my  sizeVector in '+1' because I have
	to alocate a space to the '/' character which is responsible
	to determinate the end of my string.
	
	2. alocate a vector to insert my string with the right size got
	in the 'sizeVector' variable

	3. copy the string (data) given by parameter to my vector alocated
	using strcpy.

	4. instantiate my pointer (ptr) with the vector I created, now
	already with all the values. Vectors are considerated pointer
	pointing to the first value of my vector for that reason I can
	instantiate my 'ptr' with 'vector'

*/
void ArrayListString::insert(const char *data, std::size_t index) {
	char* ptr = NULL;
	int sizeVector = 0;
	if(full()) {
		std::out_of_range("List is full");
	}
	if (index > size()) {
		std::out_of_range("Invalid index");
	}
	sizeVector = strlen(data) + 1;
	char* vector = new char[sizeVector];
	strcpy(vector, data);
	ptr = vector;
	ArrayList::insert(ptr, index);
}

//! Insert Sorted
/*!
	Insert my strings in the list in a sorted way. I use the 'strcmp()'
	to compare the string I want to insert and the strings that are
	already in my lsit.
	It funciton 'strcmp()' uses a precedence validation based on the
	ASCII table position of the values for each character in the strings
	compared.
*/
void ArrayListString::insert_sorted(const char *data) {
	std::size_t current = 0;
	for(std::size_t i = 0; i < size(); i++) {
		if(strcmp(data, at(i)) <= 0) {
			break;
		}
		current++;
	}
	insert(data, current);
}

//! Pop
/*!
	Pop a string from any position of my list. First I create a pointer
	to receive the value of my vector which is alocated my string then I
	check if the list is empty or if the index given os valid. Then I
	just instantiate my pointer 'ptr' with the value coming from a call
	of my superclass 'pop()' method in the index I received by parameter
*/
char* ArrayListString::pop(std::size_t index) {
	char* ptr;
	if(empty()) {
		std::out_of_range("List is empty");
	}
	if(index >= size()) {
		std::out_of_range("List is empty");
	}
	ptr = ArrayList::pop(index);
	return ptr;
}

//! Pop Back
/*!
	Gives back a string from the end of my list. It is a specification
	of my 'pop()' method so I just call it. Because the 'size_'
	variable gives point to the position empty I have to decrease
	its values in '-1'. I use 'size()' because I can't access the
	private variable 'size_'

*/
char* ArrayListString::pop_back() {
	return pop(size() - 1);
}

//! Pop Front
/*!
	Gives back a string from the begining of my list. It is a specification
	of my 'pop()' method, so i just call it given '0' (first valid position
	of my list) by parameter
*/
char* ArrayListString::pop_front() {
	return pop(0);
}

// Remove
/*!
	Remove a string from my list. First I check if the string exists in my
	list of not. If I find it I delete. I use 'at()' method because I can't
	access the list, because it is private. 
*/
void ArrayListString::remove(const char *data) {
	std::size_t aux = find(data);
	if(aux != size()) {
		delete at(aux);
		ArrayList::remove(at(aux));
	}
}

// Contains
/*!
	Just return a boolean to check if there is or not a specific string, 
	given by parameters, in my list. I just call de 'find()' method and
	compare the value with my size (last position empty). If I get the
	size value It means I don't have that string in my list. I use
	'size()' because the variable 'size_' from the superclass is private
*/
bool ArrayListString::contains(const char *data) {
	return (find(data) != size());
}

// Find
/*!
	Try to find a string that is given by parameters and gives back the
	index of the value, if it is found and the size value if it is not.
	Here I use 'strcmp()' to compare the string comming from parameters
	and the string in the position at(i). I use 'at()' function
	because I cannot access the list because it is private.
*/
std::size_t ArrayListString::find(const char *data) {
	std::size_t index = size();
	for (std::size_t i = 0; i < size(); i++) {
		if(strcmp(data, at(i)) == 0) {
			index = i;
			break;
		}
	}
	return index;
}
}  // namespace structures

#endif

// -------------------------------------------------------

	// -------------NOTES------------------------ //
/*!

EXAḾPLE 1

// call the function from the superclass
popArrayListString() : pop() {

}

EXAMPLE 2

//  implements the function pop from the subclass
ArrayListString::pop(){
	//  call the function from the superclass
	ArrayList::pop();
}

*/
