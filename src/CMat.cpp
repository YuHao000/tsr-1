/*
* @file CMat.cpp
* @authur liyi_whu@163.com
* @create 2018-11-03
*/

#include "Common.hpp"
#include "CMat.hpp"


namespace tsr
{
	CMat::CMat(MAT_TYPE type)
	{
        switch (type)
        {
        case tsr::MAT_SOBELX:
            Sobelx();
            break;
        case tsr::MAT_SOBELY:
            Sobely();
            break;
        case tsr::MAT_PREWITTX:
            Prewittx();
            break;
        case tsr::MAT_PREWITTY:
            Prewitty();
            break;
        case tsr::MAT_ROBERTSX:
            Robertsx();
            break;
        case tsr::MAT_ROBERTSY:
            Robertsy();
            break;
        case tsr::MAT_SCHARRX:
            Scharrx();
            break;
        case tsr::MAT_SCHARRY:
            Scharry();
            break;
        default:
            break;
        }
	}

    CMat::CMat(int len, float sigma)
    {
        Gauss(len, sigma);
    }

	CMat::~CMat()
	{
	}

    void CMat::Gauss(int len, float sigma)
    {
        Reserve(len);
        float sum = 0, s = 2 * sigma * sigma;

        for (int x = -2; x <= 2; x++)
            for (int y = -2; y <= 2; y++)
                sum += (Value(x+2, y+2) = exp(-(x * x + y * y) / s) / s / M_PI);

        for (int x = 0; x < m_len; x++)
            for (int y = 0; y < m_len; y++)
                Value(x, y) /= sum;
    }

    void CMat::Sobelx()
    {
        Reserve(3);
        float v[3][3] = {
            {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}
        };

        for (int x = 0; x < m_len; x++) {
            for (int y = 0; y < m_len; y++) {
                Value(x, y) = v[x][y];
            }
        }
    }
    void CMat::Sobely()
    {
        Reserve(3);
        float v[3][3] = {
            {1,   2,   1}, 
            {0,   0,   0}, 
            {-1,  -2,  -1}
        };

        for (int x = 0; x < m_len; x++) {
            for (int y = 0; y < m_len; y++) {
                Value(x, y) = v[x][y];
            }
        }
    }

    void CMat::Prewittx()
    {
        Reserve(3);
        float v[3][3] = {
            {-1, 0, 1}, 
            {-1, 0, 1}, 
            {-1, 0, 1}
        };

        for (int x = 0; x < m_len; x++) {
            for (int y = 0; y < m_len; y++) {
                Value(x, y) = v[x][y];
            }
        }
    }
    void CMat::Prewitty()
    {
        Reserve(3);
        float v[3][3] = {
            {-1, -1, -1},
            {0, 0, 0},
            {1, 1, 1}
        };

        for (int x = 0; x < m_len; x++) {
            for (int y = 0; y < m_len; y++) {
                Value(x, y) = v[x][y];
            }
        }
    }
    void CMat::Robertsx()
    {
        Reserve(2);
        float v[2][2] = {
            {1, 0},
            {0, -1}
        };

        for (int x = 0; x < m_len; x++) {
            for (int y = 0; y < m_len; y++) {
                Value(x, y) = v[x][y];
            }
        }
    }
    void CMat::Robertsy()
    {
        Reserve(2);
        float v[2][2] = {
            {0, 1},
            {-1, 0}
        };

        for (int x = 0; x < m_len; x++) {
            for (int y = 0; y < m_len; y++) {
                Value(x, y) = v[x][y];
            }
        }
    }
    void CMat::Scharrx()
    {
        Reserve(3);
        float v[3][3] = {
            {3, 10, 3},
            {0, 0, 0},
            {-3, -10, -3}
        };

        for (int x = 0; x < m_len; x++) {
            for (int y = 0; y < m_len; y++) {
                Value(x, y) = v[x][y];
            }
        }
    }

    void CMat::Scharry()
    {
        Reserve(3);
        float v[3][3] = {
            {3, 0, -3},
            {10, 0, -10},
            {3, 0, -3}
        };

        for (int x = 0; x < m_len; x++) {
            for (int y = 0; y < m_len; y++) {
                Value(x, y) = v[x][y];
            }
        }
    }
}