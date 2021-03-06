/*
* @file CDetect.cpp
* @authur liyi_whu@163.com
* @create 2018-11-03
*/

#include <vector>
#include "Common.hpp"
#include "CDetect.hpp"
#include "CLog.hpp"

namespace tsr
{
    void FindNearPoints(CBitmap& bmp, int x, int y, CPointSet& found)
    {
        CColor   white(255, 255, 255);
        int      cur = 0;

        found.push_back(x, y, bmp.GetPixel(x, y));
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

                    found.push_back(nx, ny, bmp.GetPixel(nx, ny));
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

    CDetect::CDetect(CBitmap& bitmap, CBitmap& orig): m_bitmap(bitmap), m_origPic(orig)
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

    void CDetect::MergeRects()
    {
        std::vector<CPointSet>::iterator  begin = m_ptSets.begin();

        for (size_t i = 0; i < m_ptSets.size(); i++) {
            begin = m_ptSets.begin();
            CPointSet& cur = *(begin + i);
            for (size_t j = (i + 1); j < m_ptSets.size(); ) {
                CPointSet& tmp = *(begin + j);
                if (cur.GetRect().IsInRect(tmp.GetRect())) {
                    cur = tmp;
                    m_ptSets.erase(begin + j);
                    continue;
                }
                if (tmp.GetRect().IsInRect(cur.GetRect())) {
                    m_ptSets.erase(begin + j);
                    continue;
                }
                j++;
            }
            i++;
        }
    }

    void CDetect::RemoveRects(int len)
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

        TRUE_RET(hx < (int)(w * 0.05), true);
        TRUE_RET(hy < (int)(h * 0.05), true);
        TRUE_RET(hx > (int)(w * 0.95), true);
        TRUE_RET(hy > (int)(h * 0.95), true);
        return false;
    }

    void CDetect::ExpandLightArea(CPointSet& ps, int T, int x, int y, CRect& rect)
    {
        int  cur = 0;
        /*在原图中找相似点的区域，并加到ps中*/
        cur = ps.size();
        ps.push_back(x, y, m_origPic.GetPixel(x, y));
        m_bitmap.GetPixel(x, y) = m_origPic.GetPixel(x, y);

        while (cur < ps.size())
        {
            int cx = ps[cur].first;
            int cy = ps[cur].second;
            CColor &curColor = m_origPic.GetPixel(cx, cy);
            cur++;

            /* 找到当前节点临近节点含有颜色的店 */
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (0 == i && 0 == j) {
                        continue; //跳过当前节点
                    }
                    int nx = cx + i;
                    int ny = cy + j;
                    if (!m_bitmap.IsValidPixel(nx, ny)) {
                        continue;
                    }
                    if (!m_bitmap.GetPixel(nx, ny).IsPureWhite()) {
                        continue;
                    }
                    CColor& color = m_origPic.GetPixel(nx, ny);
                    if (color.Tolerance(curColor) > T) {
                        continue;
                    }

                    ps.push_back(nx, ny, m_origPic.GetPixel(nx, ny));
                    m_bitmap.GetPixel(nx, ny) = color;
                }
            }
        }
    }

    void CDetect::ExpandLightArea(CPointSet& ps, int T)
    {
        CRect rect = ps.GetRect();
        int  lx, ly, rx, ry;
        int found = 0;

        lx = rect.GetX(); ly = rect.GetY();
        rx = lx + rect.GetX(); ry = ly + rect.GetH();

        CColor&  baseColor = m_origPic.GetPixel(lx, ly);
        for (int x = lx - 1; x > 2; x--) {
            for (int y = ly; y <= ry; y++) {
                CColor& cur = m_origPic.GetPixel(x, y);
                //CColor& next = m_origPic.GetPixel(x - 1, y);
                if (cur.Tolerance(baseColor) < T) {
                    found++;
                }
                m_bitmap.GetPixel(x, y) = cur;
            }
            if (found < rect.GetW()/2) {
                lx = x; break;
            }
        }

        found = 0;
        for (int y = ly - 1; y > 2; y--) {
            for (int x = lx; x <= rx; x++) {
                CColor& cur = m_origPic.GetPixel(x, y);
                //CColor& next = m_origPic.GetPixel(x - 1, y);
                if (cur.Tolerance(baseColor) < T) {
                    found++;
                }
                m_bitmap.GetPixel(x, y) = cur;
            }
            if (found < rect.GetH() / 2) {
                ly = y; break;
            }
        }

        found = 0;
        for (int x = rx + 1; x < m_bitmap.GetW()-2; x++) {
            for (int y = ly; y <= ry; y++) {
                CColor& cur = m_origPic.GetPixel(x, y);
                //CColor& next = m_origPic.GetPixel(x - 1, y);
                if (cur.Tolerance(baseColor) < T) {
                    found++;
                }
                m_bitmap.GetPixel(x, y) = cur;
            }
            if (found < rect.GetW() / 2) {
                rx = x; break;
            }
        }

        found = 0;
        for (int y = ry + 1; y < m_bitmap.GetH() - 2; y++) {
            for (int x = lx; x <= rx; x++) {
                CColor& cur = m_origPic.GetPixel(x, y);
                //CColor& next = m_origPic.GetPixel(x - 1, y);
                if (cur.Tolerance(baseColor) < T) {
                    found++;
                }
                m_bitmap.GetPixel(x, y) = cur;
            }
            if (found < rect.GetH() / 2) {
                ry = y; break;
            }
        }

        ps.GetRect().Set(lx, ly, rx - lx, ry - ly);

        //if (m_bitmap.GetPixel(x, y).IsPureWhite()) {
            //ExpandLightArea(ps, T, x, y, rect);
        //}
    }

    void CDetect::FindLights()
    {
        //m_origPic.Sobel(m_edgePic);

        for (auto& ps : m_ptSets) {
            if ((ps.size() < (ps.GetRectArea() * 0.5))) {
                continue;
            }

            if (ps.GetGNum() > ps.size() * 0.7) {
                ps.SetType(PS_GREEN_LIGHT);
                //ExpandLightArea(ps, 40);
                continue;
            }

            if (ps.GetRNum() > ps.size() * 0.7) {
                ps.SetType(PS_RED_LIGHT);
                //ExpandLightArea(ps, 40);
                continue;
            }


        }
    }
}