#pragma once
#include<DxLib.h>

struct HSVtoRGB
{
	using HSV = FLOAT3;
	FLOAT3 operator()(HSV hsv)
	{
		//wiki‚æ‚è
		auto h = hsv.x/255;
		auto s = hsv.y/255;
		auto v = hsv.z/255;
        FLOAT3 rgb = { v,v,v };
        auto& r = rgb.x;
        auto& g = rgb.y;
        auto& b = rgb.z;
		if (s == 0.0)
		{
            r *= 255;
            g *= 255;
            b *= 255;
			return rgb;
		}
		h *= 6.0;
		int i = static_cast<int>(h);
		float f = h - i;
        switch (i) {
        default:
        case 0:
            g *= 1 - s * (1 - f);
            b *= 1 - s;
            break;
        case 1:
            r *= 1 - s * f;
            b *= 1 - s;
            break;
        case 2:
            r *= 1 - s;
            b *= 1 - s * (1 - f);
            break;
        case 3:
            r *= 1 - s;
            g *= 1 - s * f;
            break;
        case 4:
            r *= 1 - s * (1 - f);
            g *= 1 - s;
            break;
        case 5:
            g *= 1 - s;
            b *= 1 - s * f;
            break;
        }           
        r *= 255;
        g *= 255;
        b *= 255;
        return rgb;
	}

};

