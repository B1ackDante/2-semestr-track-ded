/**
 *	@file
 *	@brief class description file vector
 *	@author Den
 *	@version 1.0
 *	@date March 2019
 */

#ifndef BINARY_OPEATORS_H
#define BINARY_OPEATORS_H

//{========================================================================================================
/**
 *	@brief operator Vector + Vector
 * 	@param[in] v1 Vector1
 * 	@param[in] v2 Vector2
 *	@return result Vector
 *	@throw DenException
 */

template <typename data>
Vector<data> operator+(const Vector<data> &v1, const Vector<data> &v2) throw(DenException)
	{
		assert(v1.size() == v2.size());

		Vector<data> copy(v1.size());

		for(int i = 0; i < v1.size(); i++) copy[i] = v1[i] + v2[i];

		return copy;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief operator Vector - Vector
 * 	@param[in] v1 Vector1
 * 	@param[in] v2 Vector2
 *	@return result Vector
 *	@throw DenException
 */
template <typename data>
Vector<data> operator-(const Vector<data> &v1, const Vector<data> &v2)throw(DenException)
	{
		assert(v1.size() == v2.size());

		Vector<data> copy(v1.size());

		for(int i = 0; i < v1.size(); i++) copy[i] = v1[i] - v2[i];

		return copy;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief operator Vector * const
 * 	@param[in] v1 Vector1
 * 	@param[in] num const
 *	@return result Vector
 *	@throw DenException
 */
template <typename data>
Vector<data> operator*(const Vector<data> &v1, double num)throw(DenException)
	{
		Vector<data> copy(v1.size());

		for(int i = 0; i < v1.size(); i++) copy[i] = v1[i] * num;

		return copy;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief operator const * Vector
 * 	@param[in] num const
 * 	@param[in] v1 Vector1
 *	@return result Vector
 * 	@throw DenException
 */
template <typename data>
Vector<data> operator*(double num, const Vector<data> &v1) throw(DenException)
	{
		return v1 * num;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief operator Vector / const
 * 	@param[in] v1 Vector1
 * 	@param[in] num const
 *	@return result Vector
 * 	@throw DenException
 */
template <typename data>
Vector<data> operator/(const Vector<data> &v1, double num) throw(DenException)
	{
		Vector<data> copy(v1.size());

		for(int i = 0; i < v1.size(); i++) copy[i] = v1[i] / num;

		return copy;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief output operator
 *	@detailed print Vector to os stream
 *	@param[in] os print stream
 *	@param[in] v1 Vector to print
 *	@throw DenException
 */
template <typename data>
std::ostream& operator << (std::ostream& os, const Vector<data> &v1)
	{
		for(int i = 0; i < v1.size(); ++i)
			os << v1[i] << ' ';
		return os;
	}
//}========================================================================================================

#endif
