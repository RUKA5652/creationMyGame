#pragma once
#include<DxLib.h>
#include<map>
#include<typeinfo>
#include<functional>

inline namespace DxShDraw
{
	extern void DrawGraph(int x, int y, double ExRate,int image, int p_shader);
	extern void DrawGraph(int x, int y, double ExRate, int image,int blendImage ,int p_shader);
	extern void DrawGraph(int x, int y, int image, int blendImage, int p_shader);
	extern void DrawGraph(int x, int y, int image,std::function<void(void)>&& func);
	extern void DrawGraph(std::array<VERTEX2DSHADER, 4>& verts, int image, std::function<void(void)>&& func);
	extern void DrawChangeHueGraph(int x, int y, int image, float hue);
	extern void DrawMULGraph(int x, int y, int image, int r,int g,int b);
};



