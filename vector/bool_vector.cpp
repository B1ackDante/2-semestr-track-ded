/**
 *	@file
 *	@brief class bool vector
 *	@author Den
 *	@version 1.0
 *	@date March 2019
 */

#ifndef BOOL_VECTOR_H
#define BOOL_VECTOR_H

//{========================================================================================================
/**
 * 	@class Vector<bool>
 * 	@brief Type Vector<bool>. Effective in speed, but spends a lot of memory.
 */
template <>
class Vector<bool>
	{
		private:

			int* buffer_;	///< pointer to data buffer
			int size_;			///< number of elements in the buffer
			int capacity_;	///< buffer capacity

			double cap_increase = 2.0;			///< buffer increase ratio
			double cap_decrease = 0.5;		  ///< buffer decrease ratio

			bool increase() throw();
			bool decrease() throw();

			class BoolReference
				{
					private:

						int* bool_pointer_;			///< pointer to int cell
						int position_;					///< position in int cell

					public:

						/**
						 * 	@brief constructor
						 *	@detailed create a BoolReference
						 *	@param[in] bool_pointer pointer to int cell
						 *	@param[in] position position in int cell
						 */
						BoolReference(int* bool_pointer, int position)
							{
								bool_pointer_ = bool_pointer;
								position_ = position;
							}

						/**
						 * 	@brief destructor
						 *	@detailed free BoolReference
						 */
						~BoolReference()
							{
								bool_pointer_ = NULL;
								position_ = 0;
							}

						/**
						 * 	@brief operator=
						 *	@param[in] value
						 *	@return reference to BoolReference
						 */
						BoolReference& operator=(const bool value)
							{
								if(value == true)
									*bool_pointer_ = *bool_pointer_ | 1 << position_;
								else
									*bool_pointer_ = *bool_pointer_ & ~(1 << position_);

								return *this;
							}

						/**
						 * 	@brief operator bool()
						 *	@return bool value
						 */
						operator bool() const
							{
								return 	*bool_pointer_ & (1 << position_) ? true : false;
							}
				};

		public:

			Vector();
			Vector(int size) 														throw(DenException);
			Vector(int size, bool value) 								throw(DenException);
			Vector(int size, bool* arr)									throw(DenException);
			Vector(const Vector& arr)										throw(DenException);
			Vector(Vector&& arr)												throw(DenException);
			~Vector();

			BoolReference operator[](int index) const 	throw(DenException);
			Vector& operator=(const Vector& vector)			throw(DenException);
			Vector& operator=(Vector&& vector)					throw(DenException);

			void push_back(bool elem)										throw(DenException);
			bool pop_back(void)													throw(DenException);

			void clear(void);
			int size(void) const;
			bool empty(void);
	};
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief increases buffer
 *	@detailed increases buffer by cap_increase, if there is not enough space
 *	@return true if increase success
 *					false if increase error
 */
bool Vector<bool>::increase() throw()
	{
		try
			{
				int new_capasity = ((int)(size_*cap_increase) / sizeof(int) + 1) * sizeof(int);
				int* ptr = (int* )realloc(buffer_, sizeof(int)*new_capasity);

				if(ptr == NULL)
					throw DEN_EXCEPTION("Realloc memory error!!!", DenException::exception_code_e::DONT_HAVE_MEMORY);

				buffer_ = ptr;
				capacity_ = new_capasity;

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
bool Vector<bool>::decrease() throw()
	{
		try
			{
				int new_capasity = ((int)(size_*cap_decrease) / sizeof(int) + 1) * sizeof(int);
				int* ptr = (int* )realloc(buffer_, sizeof(int)*new_capasity);

				if(ptr == NULL)
					throw DEN_EXCEPTION("Realloc memory error!!!", DenException::exception_code_e::DONT_HAVE_MEMORY);

				buffer_ = ptr;
				capacity_ = new_capasity;

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
 *	@detailed create a Vector<bool> with size = 0
 */
Vector<bool>::Vector()
	{
		size_ = 0;
		buffer_ = NULL;
	}

/**
 * 	@brief constructor
 *	@detailed creates a Vector<bool> with a defined size
 *	@param[in] size size of Vector<bool>
 *	@throw DenException
 */
Vector<bool>::Vector(int size)	throw(DenException)
	{
		size_ = size;
		capacity_ = ((int)(size_*cap_increase) / sizeof(int) + 1) * sizeof(int);

		try
			{
				buffer_ = (int*) calloc(capacity_ / sizeof(int), sizeof(int));
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
 *	@detailed creates a Vector<bool> with a defined size. All numbers in the vector are equal value
 *	@param[in] size size of Vector<bool>
 * 	@param[in] value the value that fills the Vector<bool>
 *	@throw DenException
 */
Vector<bool>::Vector(int size, bool value) throw(DenException)
	{
		size_ = size;
		capacity_ = ((int)(size_*cap_increase) / sizeof(int) + 1) * sizeof(int);

		try
			{
				buffer_ = (int*) calloc(capacity_ / sizeof(int), sizeof(int));
				if(buffer_ == NULL)
					throw(DEN_EXCEPTION("Calloc memory error!!!", DenException::exception_code_e::DONT_HAVE_MEMORY));
			}
		catch(DenException& except)
			{
				throw;
			}

		if(value == true)
			for(int i = 0; i < size_; i++)
				{
					int cell_num = i / sizeof(int);
					int byte_num = i % sizeof(int);

					buffer_[cell_num] = buffer_[cell_num] | (1 << byte_num);
				}
	}

/**
 * 	@brief constructor
 *	@detailed creates a Vector<bool> with a defined size. Numbers in the Vector<bool> are equal numbers in the array arr
 *	@param[in] size size of Vector<bool>
 * 	@param[in] arr array that fills the Vector<bool>
 *	@throw DenException
 */
Vector<bool>::Vector(int size, bool* arr) throw(DenException)
	{
		size_ = size;
		capacity_ = ((int)(size_*cap_increase) / sizeof(int) + 1) * sizeof(int);

		try
			{
				if(arr == NULL)
					throw(DEN_EXCEPTION("Array pointer is NULL!!!", DenException::exception_code_e::NULL_POINTER));

				buffer_ = (int*) calloc(capacity_ / sizeof(int), sizeof(int));

				if(buffer_ == NULL)
					throw(DEN_EXCEPTION("Calloc memory error!!!", DenException::exception_code_e::DONT_HAVE_MEMORY));
			}
		catch(DenException& except)
			{
				throw;
			}

		for (int i = 0; i < size_; i++)
			{
				int cell_num = i / sizeof(int);
				int byte_num = i % sizeof(int);

				if(arr[i] == true)
					buffer_[cell_num] = buffer_[cell_num] | (1 << byte_num);
			}
	}

/**
 * 	@brief copy constructor
 *	@detailed deeply copies one Vector<bool> to another
 *	@param[in] vec copy Vector<bool>
 *	@throw DenException
 */
Vector<bool>::Vector(const Vector& vec) throw(DenException)
	{
		size_ = vec.size_;
		capacity_ = ((int)(size_*cap_increase) / sizeof(int) + 1) * sizeof(int);

		try
			{
				buffer_ = (int*) calloc(capacity_ / sizeof(int), sizeof(int));

				if(buffer_ == NULL)
					throw(DEN_EXCEPTION("Calloc memory error!!!", DenException::exception_code_e::DONT_HAVE_MEMORY));
			}
		catch(DenException& except)
			{
				throw;
			}

		for (int i = 0; i < size_; i++)
			{
				int cell_num = i / sizeof(int);
				int byte_num = i % sizeof(int);

				if(vec.buffer_[i] == true)
					buffer_[cell_num] = buffer_[cell_num] | (1 << byte_num);
			}

		std::cout << "copy construct" << std::endl;
	}

/**
 * 	@brief move constructor
 *	@detailed superficially copies the temporary Vector<bool>
 *	@param[in] vec copy Vector<bool>
 *	@throw DenException
 */
Vector<bool>::Vector(Vector&& vec) throw(DenException)
	{
		size_ = vec.size_;
		capacity_ = ((int)(size_*cap_increase) / sizeof(int) + 1) * sizeof(int);
		buffer_ = vec.buffer_;

		vec.size_ = 0;
		vec.buffer_ = NULL;

		std::cout << "move construct" << std::endl;
	}
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief destructor
 *	@detailed free Vector<bool>
 */
Vector<bool>::~Vector()
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
Vector<bool>::BoolReference Vector<bool>::operator[](int index) const throw(DenException)
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

		int cell_num = index / sizeof(int);
		int byte_num = index % sizeof(int);

		BoolReference reference(buffer_ + cell_num, byte_num);

		return reference;
	}
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief copy operator
 *	@detailed deeply copies one Vector<bool> to another
 *	@param[in] vector copy Vector<bool>
 *	@throw DenException
 */
Vector<bool>& Vector<bool>::operator=(const Vector &vector) throw(DenException)
	{
		size_ = vector.size_;
		capacity_ = vector.capacity_;

		try
			{
				buffer_ = (int*)realloc(buffer_, sizeof(vector.buffer_));

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
 *	@detailed superficially copies the temporary Vector<bool>
 *	@param[in] vector copy Vector<bool>
 *	@throw DenException
 */
Vector<bool>& Vector<bool>::operator=(Vector &&vector) throw(DenException)
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
 *	@detailed inserts an element at the end of a Vector<bool>
 *	@param[in] elem insert element
 * 	@throw DenException
 */
void Vector<bool>::push_back(bool elem) throw(DenException)
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
 *	@detailed returns an element from the end of a Vector<bool>
 *	@return element
 * 	@throw DenException
 */
bool Vector<bool>::pop_back(void) throw(DenException)
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
 *	@brief clear Vector<bool>
 */
void Vector<bool>::clear(void)
	{
		free(buffer_);
		buffer_ = NULL;
		size_ = 0;
		capacity_ = 0;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@return Vector<bool> size
 */
int Vector<bool>::size(void) const
	{
		return size_;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief checks if Vector<bool> is empty
 *	@return true if Vector<bool> is empty
 *					false if Vector<bool> isn't empty
 */
bool Vector<bool>::empty(void)
	{
		return size_ == 0 ? true : false;
	}
//}========================================================================================================


#endif
