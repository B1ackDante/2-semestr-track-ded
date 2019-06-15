/**
 *	@file
 *	@brief some example of Vector
 *	@author Den
 *	@version 1.0
 *	@date March 2019
 */

#include "vector.cpp"

int main(void)
	{
		try
			{
				Vector<bool> a1(64, true);
				bool b = a1[2] = false;
				a1[62] = false;
				std::cout << a1 << '\n';
				std::cout << b << '\n';
			}
		catch(DenException& except)
			{
				except.where(std::cout);
				except.what(std::cout);
				except.code(std::cout);
			}

		return 0;
	}
