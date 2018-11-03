/**/

#ifndef __CFILTER_HPP__
#define __CFILTER_HPP__
#include "CBitmap.hpp"

namespace tsr
{
	class CFilter
	{
	public:
        CFilter(CBitmap& bitmap);
		~CFilter();


	private:
        CBitmap&  m_bitmap;
	};

}

#endif //__CFILTER_HPP__