/*
* @file CDetect.cpp
* @authur liyi_whu@163.com
* @create 2018-11-03
*/

#include <vector>
#include "Common.hpp"
#include "CDetect.hpp"


namespace tsr
{
    void FindNearPoints(CBitmap& bmp, int x, int y, CPointSet& found)
    {
        CColor   white(255, 255, 255);
        int      cur = 0;

        found.push_back(x, y);
        bmp.GetPixel(x, y) = white;

        while (cur < found.size())
        {
            int cx = found[cur].first;
            int cy = found[cur].second;
            cur++;

            /* 找到当前节点临近节点含有颜色的店 */
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (0 == i && 0 == j) {
                        continue; //跳过当前节点
                    }
                    int nx = cx + i;
                    int ny = cy + j;
                    if (!bmp.IsValidPixel(nx, ny)) {
                        continue;
                    }
                    CColor& color = bmp.GetPixel(nx, ny);
                    if (color.IsPureWhite()) {
                        continue;
                    }

                    found.push_back(nx, ny);
                    color = white;
                }
            }
        }
    }

    CDetect::CDetect(CBitmap& bitmap): m_bitmap(bitmap)
    {

    }
    CDetect::~CDetect()
    {

    }

    void CDetect::FindRects()
    {
        CBitmap    bmp = m_bitmap;
        CPointSet  ps(bmp.GetW(), bmp.GetH());

        for (int x = 0; x < bmp.GetW(); x++) {
            for (int y = 0; y < bmp.GetH(); y++) {
                CColor& color = bmp.GetPixel(x, y);
                if (color.IsPureWhite()) {
                    continue;
                }

                m_ptSets.push_back(ps);
                CPointSet& psBack = m_ptSets.back();
                FindNearPoints(bmp, x, y, psBack);
                psBack.CalcRect();
            }
        }
    }

    void CDetect::MarkRect(CRect& rect)
    {
        CColor blue(0, 0, 255);
        int  lx = rect.GetX(), ly = rect.GetY();
        int  rx = lx + rect.GetW(), ry = ly + rect.GetH();

        for (int x = lx; x <= rx; x++) {
            m_bitmap.GetPixel(x, ly) = blue;
            m_bitmap.GetPixel(x, ry) = blue;
        }

        for (int y = ly; y <= ry; y++) {
            m_bitmap.GetPixel(lx, y) = blue;
            m_bitmap.GetPixel(rx, y) = blue;
        }
    }

    void CDetect::MarkRects()
    {
        for (auto& ps : m_ptSets) {
            MarkRect(ps.GetRect());
        }
    }

    bool CDetect::IsInRects(int x, int y)
    {
        for (auto& rect : m_rects) {
            if (rect.IsInRect(x, y)) {
                return true;
            }
        }
        return false;
    }
}