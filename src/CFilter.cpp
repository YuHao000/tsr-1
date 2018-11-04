
#include "Common.hpp"
#include "CFilter.hpp"

namespace tsr
{
    CFilter::CFilter(CBitmap& bitmap) : m_bitmap(bitmap)
    {

    }
    CFilter::~CFilter()
    {
        
    }

    void CFilter::FilterRed(CBitmap& dst)
    {
        dst = m_bitmap;

        CColor white(255, 255, 255);

        for (int x = 0; x < dst.GetW(); x++) {
            for (int y = 0; y < dst.GetH(); y++) {
                if (!IsRed(dst.GetPixel(x, y))) {
                    dst.GetPixel(x, y) = white;
                }
            }
        }
    }
    void CFilter::FilterGreen(CBitmap& dst)
    {
        dst = m_bitmap;

        CColor white(255, 255, 255);

        for (int x = 0; x < dst.GetW(); x++) {
            for (int y = 0; y < dst.GetH(); y++) {
                if (!IsGreen(dst.GetPixel(x, y))) {
                    dst.GetPixel(x, y) = white;
                }
            }
        }
    }

    void CFilter::FilterGreenAndRed(CBitmap& dst)
    {
        dst = m_bitmap;

        CColor white(255, 255, 255);

        for (int x = 0; x < dst.GetW(); x++) {
            for (int y = 0; y < dst.GetH(); y++) {
                if ((!IsGreen(dst.GetPixel(x, y)) && 
                    (!IsRed(dst.GetPixel(x, y))))) {
                    dst.GetPixel(x, y) = white;
                }
            }
        }
        return;
    }

    bool CFilter::IsRed(CColor& c)
    {
        int h = c.GetHi();
        int s = c.GetSi();
        int v = c.GetVi();
        return (((h>=0 && h<=10)||(h>=156 && h<=180))
            && (s>=43 && s<=255) && (v>=46 && v<=255));
    }
    bool CFilter::IsGreen(CColor& c)
    {
        int h = c.GetHi();
        int s = c.GetSi();
        int v = c.GetVi();
        return ((h >= 73 && h <= 93)
            && (s >= 43 && s <= 255) && (v >= 100 && v <= 255));
    }
}