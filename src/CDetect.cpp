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

    void ClearBitmapInPt(CBitmap& bmp, CPointSet& ps)
    {
        CColor white(255, 255, 255);
        for (int i = 0; i < ps.size(); i++) {
            std::pair<int, int>& pt = ps[i];
            bmp.GetPixel(pt.first, pt.second) = white;
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

    void CDetect::RemoveSmallRect(int len)
    {
        int ptNum = len * len;
        int width, height;
        std::vector<CPointSet>::iterator begin = m_ptSets.begin();
        for (int i = 0; i < m_ptSets.size(); ) {
            begin = m_ptSets.begin();
            CPointSet& cur = *(begin + i);
            CRect &rect = cur.GetRect();
            
            width = rect.GetW();  height = rect.GetH();
            if (width <= len || height <= len || cur.size() <= ptNum 
                || !IsRatioOK(width, height) || IsCloseToEdge(rect)) {
                ClearBitmapInPt(m_bitmap, cur);
                m_ptSets.erase(begin + i);
                continue;
            }
            i++;
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

    void CDetect::FindClosure()
    {

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

    bool CDetect::IsCloseToEdge(CRect& rect)
    {
        int hx = rect.GetX() + rect.GetW() / 2, hy = rect.GetY() + rect.GetH() / 2;

        float w = m_bitmap.GetW();
        float h = m_bitmap.GetH();

        TRUE_RET(hx < (int)(w * 0.1), true);
        TRUE_RET(hy < (int)(h * 0.1), true);
        TRUE_RET(hx > (int)(w * 0.9), true);
        TRUE_RET(hy > (int)(h * 0.9), true);
        return false;
    }
}