/*
* @file CDetect.hpp
* @authur liyi_whu@163.com
* @create 2018-11-03
*/

#ifndef __CDETECT_HPP__
#define __CDETECT_HPP__

#include <vector>
#include <bitset>
#include "Common.hpp"
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
        void RemoveSmallRect(int len);
        void FindClosure();

        bool IsInRects(int x, int y);
        bool IsRatioOK(int w, int h)
        {
            float max_ = (float)MAX(w, h);
            float min_ = (float)MIN(w, h);
            return (max_ / min_ < 1.5);
        }

        bool IsCloseToEdge(CRect& rect);

	private:
        CBitmap&                m_bitmap;
        std::vector<CRect>      m_rects;
        std::vector<CPointSet>  m_ptSets;
	};

}

#endif //__CDETECT_HPP__