#include <fstream>
#include <math.h>
#include "CBitmap.hpp"
#include "Common.hpp"
#include "CMat.hpp"

namespace tsr
{
	CBitmap::CBitmap()
	{
	}

	CBitmap::CBitmap(int w, int h)
	{
		SetSize(w, h);
	}

	CBitmap::CBitmap(CBitmap& bitmap)
	{
        *this = bitmap;
	}

	CBitmap::~CBitmap()
	{
	}

	void CBitmap::SetSize(int w, int h)
	{
		m_w = w;
		m_h = h;
		m_bitmap.resize(w * h);
	}

	// 获取宽度
	int CBitmap::GetW() const
	{
		return m_w;
	}

	// 获取高度
	int CBitmap::GetH() const
	{
		return m_h;
	}

	CColor& CBitmap::GetPixel(int x, int y)
	{
		return m_bitmap[x * m_h + y];
	}

	int CBitmap::SetPixel(int x, int y, const CColor& color)
	{
		TRUE_RET(!IsValidPixel(x, y), RET_ERR);
        GetPixel(x, y) = color;
		return RET_OK;
	}

	bool CBitmap::IsValidPixel(int x, int y)
	{
		return ((x >= 0 && x < m_w) && (y >= 0 && y < m_h));
	}

	int CBitmap::Load(char* file)
	{
		std::ifstream fin(file);

		fin >> m_w >> m_h;
		SetSize(m_w, m_h);

		int red, green, blue;
		for (int x = 0; x < m_w; x++) {
			for (int y = 0; y < m_h; y++) {
				CColor& color = GetPixel(x, y);
				fin >> red >> green >> blue;
				color.Set(red, green, blue);
			}
		}
		return RET_OK;
	}

    void CBitmap::Rgb2Hsv()
    {
        for (auto& c : m_bitmap) {
            c.Rgb2Hsv();
        }
    }
    
    void CBitmap::Hsv2Rgb()
    {
        for (auto& c : m_bitmap) {
            c.Hsv2Rgb();
        }
    }

	void CBitmap::Save(char* file)
	{
		std::ofstream  fout(file);
		
		fout << m_w << " " << m_h << std::endl;

		for (int i = 0; i < m_w; i++) {
			for (int j = 0; j < m_h; j++) {
				CColor& color = GetPixel(i, j);
				fout << color.GetR() << " " << color.GetG() << " " << color.GetB() << std::endl;
			}
		}
		return;
	}

    void CBitmap::SaveAsHsv(char* file)
    {
        std::ofstream  fout(file);

        fout << m_w << " " << m_h << std::endl;

        for (int i = 0; i < m_w; i++) {
            for (int j = 0; j < m_h; j++) {
                CColor& c = GetPixel(i, j);
                fout << c.GetH() << " " << c.GetS() << " " << c.GetV() << std::endl;
            }
        }
        return;
    }

    CBitmap& CBitmap::operator=(CBitmap& rhs)
    {
        if (this != &rhs) {
            SetSize(rhs.GetW(), rhs.GetH());
            for (int x = 0; x < m_w; x++) {
                for (int y = 0; y < m_h; y++) {
                    GetPixel(x, y) = rhs.GetPixel(x, y);
                }
            }
        }
        return *this;
    }

    void CBitmap::Magnitude(CBitmap& gx, CBitmap& gy)
    {
        for (int x = 0; x < m_w; x++) {
            for (int y = 0; y < m_h; y++) {
                int value = QBOUND(0, 255, static_cast<int>(hypot(gx.GetPixel(x, y).GetR(), gy.GetPixel(x, y).GetR())));
                GetPixel(x, y).Set(value, value, value);
            }
        }
    }

    void CBitmap::Convolution(CMat& mat, CBitmap& dst)
    {
        int mw = mat.GetW(), mh = mat.GetH();
        int offx = mw / 2;
        int offy = mh / 2;

        dst.SetSize(m_w, m_h);
        float sumR, sumG, sumB;

        for (int x = 0; x < m_w; x++) {
            for (int y = 0; y < m_h; y++) {
                sumR = 0; sumG = 0; sumB = 0;
                for (int i = 0; i < mw; i++) {
                    if ((x + i) < offx || (x + i) >= m_w) {
                        continue;
                    }
                    for (int j = 0; j < mh; j++) {
                        if ((y + j) < offy || (y+j) >= m_h) {
                            continue;
                        }

                        CColor& tmp = GetPixel(x + i, y + j);
                        sumR += mat.Value(i, j) * tmp.GetR();
                        sumG += mat.Value(i, j) * tmp.GetG();
                        sumB += mat.Value(i, j) * tmp.GetB();
                    }
                }

                int resultR = QBOUND(0, 255, static_cast<int>(sumR));
                int resultG = QBOUND(0, 255, static_cast<int>(sumG));
                int resultB = QBOUND(0, 255, static_cast<int>(sumB));
                dst.GetPixel(x, y).Set(resultR, resultG, resultB);
            }
        }
    }

    void CBitmap::GaussBlur(float sigma, CBitmap& dst)
    {
        CMat mat(5, sigma);
        Convolution(mat, dst);
    }
}


