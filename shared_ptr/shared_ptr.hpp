/**
 *	@file
 *	@brief class description file SharedPtr
 *	@author Den
 *	@version 1.0
 *	@date April 2019
 */

#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <iostream>

//{========================================================================================================
/**
 * 	@class SharedPtr_c
 * 	@brief Type SharedPtr. Very save pointer.
 */
template <typename data>
class SharedPtr_c
  {
    private:

      class Storage
        {
          public:

            int counter_;
            data* ptr_;

            Storage(data *ptr)
              {
                ptr_ = ptr;
                counter_ = 1;
              }

            ~Storage()
              {
                std::cout << "delete last" << std::endl;
                delete[] ptr_;
              }

        };

      Storage* strg_;

    public:

      SharedPtr_c(data* ptr);
      SharedPtr_c(const SharedPtr_c& sh_ptr);

      SharedPtr_c& operator=(const SharedPtr_c& sh_ptr);
      SharedPtr_c& operator=(data* ptr);

      data operator*(void);

      ~SharedPtr_c();

  };
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief constructor
 *	@detailed create a SharedPtr_c with pointer = ptr
 *  @param[in] ptr
 */
template <typename data>
SharedPtr_c<data>::SharedPtr_c(data* ptr)
  {
    strg_ = new Storage(ptr);
  }

/**
 * 	@brief copy constructor
 *	@detailed create a SharedPtr_c = sh_ptr
 *  @param[in] sh_ptr copy SharedPtr_c
 */
template <typename data>
SharedPtr_c<data>::SharedPtr_c(const SharedPtr_c& sh_ptr)
  {
    strg_ = sh_ptr.strg_;
    strg_->counter_++;
  }
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief destructor
 *	@detailed free SharedPtr_c
 */
template <typename data>
SharedPtr_c<data>::~SharedPtr_c()
  {
    if(strg_->counter_ == 1)
        delete strg_;
    else
        strg_->counter_--;
  }
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief copy operator
 *	@detailed SharedPtr_c = sh_ptr
 *  @param[in] sh_ptr copy SharedPtr_c
 *  @return SharedPtr_c
 */
template <typename data>
SharedPtr_c<data>& SharedPtr_c<data>::operator=(const SharedPtr_c& sh_ptr)
  {
    if(strg_ == sh_ptr.strg_) return *this;

    if(strg_->counter_ == 1)
      delete strg_;
    else
      strg_->counter_--;

    strg_ = sh_ptr.strg_;
    strg_->counter_++;

    return *this;
  }

/**
 * 	@brief operator=
 *	@detailed SharedPtr_c = ptr
 *  @param[in] ptr
 *  @return SharedPtr_c
 */
template <typename data>
SharedPtr_c<data>& SharedPtr_c<data>::operator=(data* ptr)
  {
    if(strg_->ptr_ == ptr) return *this;

    if(strg_->counter_ == 1)
      delete strg_;
    else
      strg_->counter_--;

    strg_ = new Storage(ptr);

    return *this;
  }
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief operator*
 *  @return data
 */
template <typename data>
data SharedPtr_c<data>::operator*(void)
  {
    return *(strg_->ptr_);
  }
//}========================================================================================================

#endif
