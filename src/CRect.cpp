/*
* @file CRect.cpp
* @authur liyi_whu@163.com
* @create 2018-11-03
*/

#include "Common.hpp"
#include "CRect.hpp"


namespace tsr
{
    CRect::CRect() :
        m_x(0), m_y(0), m_w(0), m_h(0)
    {

    }
    CRect::CRect(int x, int y, int w, int h):
        m_x(x), m_y(y), m_w(w), m_h(h)
    {

    }
    CRect::~CRect()
    {

    }
}