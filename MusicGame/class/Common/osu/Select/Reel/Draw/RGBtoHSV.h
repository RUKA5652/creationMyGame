#pragma once
#include<DxLib.h>

struct RGBtoHSV
{
	using RGB = FLOAT3;
	FLOAT3 operator()(RGB rgb)
	{
		//wiki‚æ‚è
		auto r = rgb.x/255;
		auto g = rgb.y/255;
		auto b = rgb.z/255;

        FLOAT3 hsv = { 0,0,0 };
        auto& h = hsv.x;
        auto& s = hsv.y;
        auto& v = hsv.z;

        float max = r > g ? r : g;
        max = max > b ? max : b;
        float min = r < g ? r : g;
        min = min < b ? min : b;
        h = max - min;

        if (h > 0.0f) 
        {
            if (max == r) 
            {
                h = (g - b) / h;
                if (h < 0.0f) 
                {
                    h += 6.0f;
                }
            }
            else if (max == g) 
            {
                h = 2.0f + (b - r) / h;
            }
            else
            {
                h = 4.0f + (r - g) / h;
            }
        }
        h /= 6.0f;
        s = (max - min);
        if (max != 0.0f)
        {
            s /= max;
        }
        s /= max;
        v = max;

        h *= 255;
        s *= 255;
        v *= 255;


        return hsv;
	}

};

