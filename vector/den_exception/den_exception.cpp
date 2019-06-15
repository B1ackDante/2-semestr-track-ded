/**
 *	@file
 *	@brief special exception class
 *	@author Den
 *	@version 1.0
 *	@date March 2019
 */

#ifndef DEN_EXCEPTION
#define DEN_EXCEPTION

#include <iostream>
#include <fstream>
#include <string.h>

//{========================================================================================================
/**
 * 	@class DenException
 * 	@brief Special exception class. Displays more information than the standard class.
 */
class DenException
  {
    public:

      enum exception_code_e
        {
          UNTITLED            = 0,
          DIV_BY_ZERO         = 1,
          CANT_OPEN_FILE      = 2,
          CANT_CLOSE_FILE     = 3,
          ARRAY_OUT_OF_RANGE  = 4,
          NULL_POINTER        = 5,
          DONT_HAVE_MEMORY    = 6
        };

      DenException(const char* filename, const char* func, const long int line, const char* message, exception_code_e exc_code);
      DenException(const DenException& except);
      DenException(DenException&& except);
      ~DenException(void);

      void where(std::ostream& os);
      void what(std::ostream& os);
      void code(std::ostream& os);

    private:

      char* message_;
      exception_code_e exc_code_;

      char* filename_;
      char* func_;
      long int line_;
  };
//{========================================================================================================


//{========================================================================================================
/**
 * 	@brief constructor
 *	@detailed create a DenException
 *  @param[in] filename
 *  @param[in] func
 *  @param[in] line
 *  @param[in] message
 *  @param[in] exc_code
 */
DenException::DenException(const char* filename, const char* func, const long int line, const char* message = NULL, exception_code_e exc_code = UNTITLED)
  {
    filename_ = strdup(filename);
    func_     = strdup(func);
    line_     = line;

    exc_code_ = exc_code;
    message_  = strdup(message);
  }

/**
 *  @brief copy constructor
 *	@detailed deeply copies one DenException to another
 *	@param[in] DenException copy DenException
 */
DenException::DenException(const DenException& except)
  {
    filename_ = strdup(except.filename_);
    func_     = strdup(except.func_);
    line_     = except.line_;

    exc_code_ = except.exc_code_;
    message_  = strdup(except.message_);
  }

/**
 * 	@brief move constructor
 *	@detailed superficially copies the temporary vector
 *	@param[in] Vector copy Vector
 */
DenException::DenException(DenException&& except)
  {
    filename_ = except.filename_;
    func_     = except.func_;
    line_     = except.line_;

    exc_code_ = except.exc_code_;
    message_  = except.message_;
  }
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief destructor
 *	@detailed free Vector
 */
DenException::~DenException(void)
  {
    free(filename_);
    free(func_);

    if(message_ != NULL)  free(message_);
  }
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief displays the location of DenException
 *	@param[in] os output stream
 */
void DenException::where(std::ostream& os)
  {
    os << "file: " << filename_ << ", function: " << func_ << ", line: " << line_ << std::endl;
  }

/**
 * 	@brief displays an exception message
 *	@param[in] os output stream
 */
void DenException::what(std::ostream& os)
  {
    if(message_ != NULL)
      os << message_ << std::endl;
    else
      os << "message is null" << std::endl;
  }

/**
 * 	@brief displays an exception code
 *	@param[in] os output stream
 */
void DenException::code(std::ostream& os)
  {
    os << "code error: " << exc_code_ << std::endl;
  }
//}========================================================================================================


#endif
