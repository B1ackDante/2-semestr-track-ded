/**
 *	@file
 *	@brief some example of DenException
 *	@author Den
 *	@version 1.0
 *	@date March 2019
 */

#include "den_exception.cpp"
#define DEN_EXCEPTION(message, exc_code) DenException(__FILE__, __func__, __LINE__, message, exc_code)

void goo(void)
  {
    try
      {
        if(0 == 0)
          throw(DEN_EXCEPTION("GOO", DenException::DIV_BY_ZERO));
      }
    catch(DenException& except)
      {
        throw;
      }
  }


void foo(void)
  {
    goo();
  }

int main(int argc, char const *argv[])
  {
    try
      {
        foo();
      }
    catch(DenException& except)
      {
        except.where(std::cout);
        except.what(std::cout);
        except.code(std::cout);
      }

    return 0;
  }
