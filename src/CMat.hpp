/*
* @file CMat.hpp
* @authur liyi_whu@163.com
* @create 2018-11-03
*/

#ifndef __CMAT_HPP__
#define __CMAT_HPP__

#include <vector>

namespace tsr
{
    enum MAT_TYPE
    {
        MAT_SOBELX = 0,
        MAT_SOBELY,
        MAT_PREWITTX,
        MAT_PREWITTY,
        MAT_ROBERTSX,
        MAT_ROBERTSY,
        MAT_SCHARRX,
        MAT_SCHARRY
    };
	class CMat
	{
	public:
		CMat(MAT_TYPE type);
        CMat(int len, float sigma);
		~CMat();

        int GetW() { return m_len; }
		int GetH() { return m_len; }

        void Reserve(int len) { m_len = len; m_vf.resize(len * len); }

        float& Value(int x, int y) { return m_vf[x*m_len + y]; }

		void Gauss(int len, float sigma);
        void Sobelx();
        void Sobely();
        void Prewittx();
        void Prewitty();
        void Robertsx();
        void Robertsy();
        void Scharrx();
        void Scharry();

	private:
		int                 m_len;
		std::vector<float>  m_vf;
	};

}

#endif //__CMAT_HPP__