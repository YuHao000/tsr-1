/*
* @file CDetect.hpp
* @authur liyi_whu@163.com
* @create 2018-11-03
*/

#ifndef __CDETECT_HPP__
#define __CDETECT_HPP__

#include <vector>
#include "CBitmap.hpp"
#include "CRect.hpp"
#include "CPointSet.hpp"

namespace tsr
{
	class CDetect
	{
	public:
        CDetect(CBitmap& bitmap);
		~CDetect();

        void FindRects();

        void MarkRects();
        void MarkRect(CRect& rect);

        bool IsInRects(int x, int y);

	private:
        CBitmap&                m_bitmap;
        std::vector<CRect>      m_rects;
        std::vector<CPointSet>  m_ptSets;
	};

}

#endif //__CDETECT_HPP__