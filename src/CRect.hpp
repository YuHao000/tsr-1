/*
* @file CRect.hpp
* @authur liyi_whu@163.com
* @create 2018-11-03
*/

#ifndef __CRECT_HPP__
#define __CRECT_HPP__

#include <vector>

namespace tsr
{
	class CRect
	{
	public:
        CRect();
        CRect(int x, int y, int w, int h);
		~CRect();

        int GetW() { return m_w; }
		int GetH() { return m_h; }
        int GetX() { return m_x; }
        int GetY() { return m_y; }

        bool IsInRect(CRect& rect);

        int Aera() { return m_w * m_h; }

        void Set(int x, int y, int w, int h) { m_x = x; m_y = y; m_w = w; m_h = h; }

        bool IsInRect(int x, int y) { return (x >= m_x && x <= (m_x + m_w)) && (y >= m_y && y <= (m_y + m_h)); }

	private:
        int     m_x;
        int     m_y;
        int     m_w;
        int     m_h;
	};

}

#endif //__CRECT_HPP__