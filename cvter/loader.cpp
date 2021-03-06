/*
 * @authur   liyi_whu@163.com
 * @date     20181102
 */

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <gdiplus.h>
#include "loader.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

namespace tsr
{
	std::wstring CharToWchar(const char* c, size_t m_encode = CP_ACP)
	{
		std::wstring str;
		size_t len = MultiByteToWideChar(m_encode, 0, c, strlen(c), NULL, 0);
		wchar_t*	m_wchar = new wchar_t[len + 1];
		MultiByteToWideChar(m_encode, 0, c, strlen(c), m_wchar, len);
		m_wchar[len] = '\0';
		str = m_wchar;
		delete m_wchar;
		return str;
	}

	std::string WcharToChar(const wchar_t* wp, size_t m_encode = CP_ACP)
	{
		std::string str;
		int len = WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);
		char	*m_char = new char[len + 1];
		WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), m_char, len, NULL, NULL);
		m_char[len] = '\0';
		str = m_char;
		delete m_char;
		return str;
	}

	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
	{
		UINT num = 0;                     // number of image encoders   
		UINT size = 0;                   // size of the image encoder array in bytes   
		ImageCodecInfo* pImageCodecInfo = NULL;
		GetImageEncodersSize(&num, &size);
		if (size == 0)
			return -1;     //   Failure   

		pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
		if (pImageCodecInfo == NULL)
			return -1;     //   Failure   

		GetImageEncoders(num, size, pImageCodecInfo);
		for (UINT j = 0; j < num; ++j)
		{
			if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
			{
				*pClsid = pImageCodecInfo[j].Clsid;
				free(pImageCodecInfo);
				return j;     //   Success   
			}
		}
		free(pImageCodecInfo);
		return -1;     //   Failure   
	}

	CPicLoader::CPicLoader(char* pic, CBitmap& bitmap) : m_bitmap(&bitmap), m_file(pic)
	{
		GdiplusStartupInput gdiplusstartupinput;
		GdiplusStartup(&m_token, &gdiplusstartupinput, NULL);
	}
	CPicLoader::~CPicLoader()
	{
		GdiplusShutdown(m_token);
	}

	int CPicLoader::Load()
	{
		std::wstring wstringfile = CharToWchar(m_file.c_str());
		Bitmap* bmp = new Bitmap(wstringfile.c_str());
		UINT height = bmp->GetHeight();
		UINT width = bmp->GetWidth();

        m_bitmap->SetSize(width, height);

		Color  color;
		CColor dstColor;
		for (UINT x = 0; x < width; x++) {
			for (UINT y = 0; y < height; y++) {
                bmp->GetPixel(x, y, &color);
				dstColor.Set((int)color.GetRed(), (int)color.GetGreen(), (int)color.GetBlue());
                m_bitmap->SetPixel(x, y, dstColor);
			}
		}
		return 0;
	}

	int CPicLoader::SaveAsJpg(const char* dst)
	{
		UINT height = m_bitmap->GetH();
		UINT width  = m_bitmap->GetW();

		Bitmap* bmp = new Bitmap(width, height);
		for (UINT x = 0; x < width; x++)
		{
			for (UINT y = 0; y < height; y++)
			{
				CColor& tmp = m_bitmap->GetPixel(x, y);
				Color color((BYTE)tmp.GetR(), (BYTE)tmp.GetG(), (BYTE)tmp.GetB());
				bmp->SetPixel(x, y, color);
			}
		}

		CLSID  id;
		GetEncoderClsid(L"image/jpeg", &id);
		std::wstring  outfile = CharToWchar(dst);
		bmp->Save(outfile.c_str(), &id);
		delete bmp;
		return 0;
	}
}

