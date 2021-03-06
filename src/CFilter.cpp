
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
                if (!dst.GetPixel(x, y).IsRed()) {
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
                if (!(dst.GetPixel(x, y).IsGreen())) {
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
                if ((!(dst.GetPixel(x, y).IsGreen()) && 
                    (!(dst.GetPixel(x, y)).IsRed()))) {
                    dst.GetPixel(x, y) = white;
                }
            }
        }
        return;
    }
}