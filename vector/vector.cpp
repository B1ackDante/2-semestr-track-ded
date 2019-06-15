/**
 *	@file
 *	@brief class description file vector
 *	@author Den
 *	@version 1.0
 *	@date March 2019
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <fstream>
#include <assert.h>

#include "den_exception/den_exception.cpp"
#define DEN_EXCEPTION(message, exc_code) DenException(__FILE__, __func__, __LINE__, message, exc_code)

//{========================================================================================================
/**
 * 	@class Vector
 * 	@brief Type Vector. Effective in speed, but spends a lot of memory.
 */
template <typename data>
class Vector
	{
		private:

			data* buffer_;	///< pointer to data buffer
			int size_;			///< number of elements in the buffer
			int capacity_;	///< buffer capacity

			double cap_increase = 2.0;			///< buffer increase ratio
			double cap_decrease = 0.5;		  ///< buffer decrease ratio

			bool increase() throw();
			bool decrease() throw();

		public:

			Vector();
			Vector(int size) 												throw(DenException);
			Vector(int size, int value) 						throw(DenException);
			Vector(int size, data* arr)							throw(DenException);
			Vector(const Vector& arr)								throw(DenException);
			Vector(Vector&& arr)										throw(DenException);
			~Vector();

			data& operator[](int index) const				throw(DenException);
			Vector& operator=(const Vector& vector)	throw(DenException);
			Vector& operator=(Vector&& vector)			throw(DenException);

			void push_back(data elem)								throw(DenException);
			data pop_back(void)											throw(DenException);

			void clear(void);
			int size(void) const;
			bool empty(void);

			void *operator new(size_t size, const char* file, const char* func, int line, std::ofstream& os);
			void operator delete(void *pointer);
	};
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief increases buffer
 *	@detailed increases buffer by cap_increase, if there is not enough space
 *	@return true if increase success
 *					false if increase error
 */
template <typename data>
bool Vector<data>::increase() throw()
	{
		try
			{
				data* ptr = (data* )realloc(buffer_, sizeof(data)*cap_increase*size_);

				if(ptr == NULL)
					throw DEN_EXCEPTION("Realloc memory error!!!", DenException::exception_code_e::DONT_HAVE_MEMORY);

				buffer_ = ptr;
				capacity_ = cap_increase * size_;

				return true;
			}
		catch(DenException& except)
			{
				except.where(std::cout);
				except.what(std::cout);
				except.code(std::cout);

				return false;
			}
	}
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief decrease buffer
 *	@detailed decrease buffer by cap_decrease, if a lot of free space
 *	@return true if decrease success
 *					false if decrease error
 */
template <typename data>
bool Vector<data>::decrease() throw()
	{
		try
			{
				data* ptr = (data* )realloc(buffer_, sizeof(data)*cap_decrease*size_);

				if(ptr == NULL)
					throw DEN_EXCEPTION("Realloc memory error!!!", DenException::exception_code_e::DONT_HAVE_MEMORY);

				buffer_ = ptr;
				capacity_ = cap_decrease * size_;

				return true;
			}
		catch(DenException& except)
			{
				except.where(std::cout);
				except.what(std::cout);
				except.code(std::cout);

				return false;
			}
	}
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief constructor
 *	@detailed create a Vector with size = 0
 */
template <typename data>
Vector<data>::Vector()
	{
		size_ = 0;
		buffer_ = NULL;
	}

/**
 * 	@brief constructor
 *	@detailed creates a vector with a defined size
 *	@param[in] size size of Vector
 *	@throw DenException
 */
template <typename data>
Vector<data>::Vector(int size)	throw(DenException)
	{
		size_ = size;
		capacity_ = size*cap_increase;

		try
			{
				buffer_ = (data*) calloc(capacity_, sizeof(data));
				if(buffer_ == NULL)
					throw(DEN_EXCEPTION("Calloc memory error!!!", DenException::exception_code_e::DONT_HAVE_MEMORY));
			}
		catch(DenException& except)
			{
				throw;
			}
	}

/**
 * 	@brief constructor
 *	@detailed creates a vector with a defined size. All numbers in the vector are equal value
 *	@param[in] size size of Vector
 * 	@param[in] value the value that fills the Vector
 *	@throw DenException
 */
template <typename data>
Vector<data>::Vector(int size, int value) throw(DenException)
	{
		size_ = size;
		capacity_ = size*cap_increase;

		try
			{
				buffer_ = (data*) calloc(capacity_, sizeof(data));
				if(buffer_ == NULL)
					throw(DEN_EXCEPTION("Calloc memory error!!!", DenException::exception_code_e::DONT_HAVE_MEMORY));
			}
		catch(DenException& except)
			{
				throw;
			}

		for (int i = 0; i < size; i++)
			buffer_[i] = value;
	}

/**
 * 	@brief constructor
 *	@detailed creates a vector with a defined size. Numbers in the vector are equal numbers in the array arr
 *	@param[in] size size of Vector
 * 	@param[in] arr array that fills the Vector
 *	@throw DenException
 */
template <typename data>
Vector<data>::Vector(int size, data* arr) throw(DenException)
	{
		size_ = size;
		capacity_ = size*cap_increase;

		try
			{
				if(arr == NULL)
					throw(DEN_EXCEPTION("Array pointer is NULL!!!", DenException::exception_code_e::NULL_POINTER));

				buffer_ = (data*) calloc(capacity_, sizeof(data));

				if(buffer_ == NULL)
					throw(DEN_EXCEPTION("Calloc memory error!!!", DenException::exception_code_e::DONT_HAVE_MEMORY));
			}
		catch(DenException& except)
			{
				throw;
			}

		for (int i = 0; i < size; i++)
			buffer_[i] = arr[i];
	}

/**
 * 	@brief copy constructor
 *	@detailed deeply copies one vector to another
 *	@param[in] Vector copy Vector
 *	@throw DenException
 */
template <typename data>
Vector<data>::Vector(const Vector& vec) throw(DenException)
	{
		size_ = vec.size_;
		capacity_ = size_*cap_increase;

		try
			{
				buffer_ = (data*) calloc(capacity_, sizeof(data));

				if(buffer_ == NULL)
					throw(DEN_EXCEPTION("Calloc memory error!!!", DenException::exception_code_e::DONT_HAVE_MEMORY));
			}
		catch(DenException& except)
			{
				throw;
			}

		for (int i = 0; i < vec.size(); i++)
			buffer_[i] = vec.buffer_[i];

		std::cout << "copy construct" << std::endl;
	}

/**
 * 	@brief move constructor
 *	@detailed superficially copies the temporary vector
 *	@param[in] Vector copy Vector
 *	@throw DenException
 */
	template <typename data>
	Vector<data>::Vector(Vector&& vec) throw(DenException)
		{
			size_ = vec.size();
			capacity_ = size_*cap_increase;
			buffer_ = vec.buffer_;

			vec.size_ = 0;
			vec.buffer_ = NULL;

			std::cout << "move construct" << std::endl;
		}
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief destructor
 *	@detailed free Vector
 */
template <typename data>
Vector<data>::~Vector()
	{
		free(buffer_);

		std::cout << "destruct" << std::endl;
	}
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief index operator
 *	@detailed returns the value of an item by its index
 *	@param[in] index index
 *	@return value
 *	@throw DenException
 */

 //отрицательный инт
template <typename data>
data& Vector<data>::operator[](int index) const throw(DenException)
	{
		try
			{
				if(index >= size_)
					throw(DEN_EXCEPTION("Index >= Vector size!!!", DenException::exception_code_e::ARRAY_OUT_OF_RANGE));
			}
		catch(DenException& except)
			{
				throw;
			}

		return buffer_[index];
	}
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief copy operator
 *	@detailed deeply copies one vector to another
 *	@param[in] vector copy Vector
 *	@throw DenException
 */
template <typename data>
Vector<data>& Vector<data>::operator=(const Vector &vector) throw(DenException)
	{
		size_ = vector.size_;
		capacity_ = vector.capacity_;

		try
			{
				buffer_ = (data* )realloc(buffer_, sizeof(vector.buffer_));

				if(buffer_ == NULL)
					throw(DEN_EXCEPTION("Calloc memory error!!!", DenException::exception_code_e::DONT_HAVE_MEMORY));
			}
		catch(DenException& except)
			{
				throw;
			}

		for(int i = 0; i < vector.size_; i++) buffer_[i] = vector.buffer_[i];

		std::cout << "copy operator =" << std::endl;

		return *this;
	}

/**
 * 	@brief move operator
 *	@detailed superficially copies the temporary vector
 *	@param[in] vector copy Vector
 *	@throw DenException
 */
template <typename data>
Vector<data>& Vector<data>::operator=(Vector &&vector) throw(DenException)
		{

			size_ = vector.size_;
			capacity_ = vector.capacity_;
			buffer_ = vector.buffer_;

			vector.size_ = 0;
			vector.buffer_= 0;

			std::cout << "move operator =" << std::endl;

			return *this;
		}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief push
 *	@detailed inserts an element at the end of a Vector
 *	@param[in] elem insert element
 * 	@throw DenException
 */
template <typename data>
void Vector<data>::push_back(data elem) throw(DenException)
	{
		if(size_ < capacity_) buffer_[size_++] = elem;
		else
			if(increase() == true)  buffer_[size_++] = elem;
			else					std::cout << "Increase error" << std::endl;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief pop
 *	@detailed returns an element from the end of a Vector
 *	@return element
 * 	@throw DenException
 */
template <typename data>
data Vector<data>::pop_back(void) throw(DenException)
	{
		assert(size_ > 0);

		if(size_ < capacity_ / 4)
			if(decrease() == true)  return buffer_[size_--];
			else
				{
					std::cout << "Decrease error" << std::endl;
					return NULL;
				}

		return buffer_[size_--];
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief clear Vector
 */
template <typename data>
void Vector<data>::clear(void)
	{
		free(buffer_);
		buffer_ = NULL;
		size_ = 0;
		capacity_ = 0;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@return Vector size
 */
template <typename data>
int Vector<data>::size(void) const
	{
		return size_;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief checks if Vector is empty
 *	@return true if Vector is empty
 *					false if Vector isn't empty
 */
template <typename data>
bool Vector<data>::empty(void)
	{
		return size_ == 0 ? true : false;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief operator NEW
 *	@detailed Made to check for memory leaks. Prints detailed information about its use in a file.
 *	@param[in] size the number of bytes to initialize
 *	@param[in] file the name of the file from which it is called NEW
 *	@param[in] func the name of the function from which it is called NEW
 *	@param[in] line the name of the line from which it is called NEW
 *	@param[in] os information stream
 *	@return pointer to the alloсated place in memory
 */

template <typename data>
void* Vector<data>::operator new(size_t size, const char* file, const char* func, int line, std::ofstream& os)
	{
		void* pointer = calloc(size, sizeof(char));

		os << "N " << file << "|" << func << "|" << line << " " << pointer << std::endl;

		return pointer;
	}

	std::ofstream memory_leak("memory_leak/memory_leak.txt");
	#define NEW new(__FILE__, __func__, __LINE__, memory_leak)
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief operator DELETE
 *	@detailed Made to check for memory leaks. Prints detailed information about its use in a file.
 *	@param[in] pointer pointer to free data
 *	@param[in] file the name of the file from which it is called DELETE
 *	@param[in] func the name of the function from which it is called DELETE
 *	@param[in] line the name of the line from which it is called DELETE
 */
template <typename data>
void Vector<data>::operator delete(void *pointer)
	{
		free(pointer);
	}

#define DELETE(x)  memory_leak << "D " << __FILE__ << "|" << __func__ << "|" << __LINE__ << " " << x << std::endl; \
	 			delete x;
//}========================================================================================================

#include "bool_vector.cpp"

#include "binary_operators.cpp"

#endif
