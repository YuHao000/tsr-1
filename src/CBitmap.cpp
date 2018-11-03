
#include "CBitmap.hpp"
#include "Common.hpp"
#include <fstream>

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
}


