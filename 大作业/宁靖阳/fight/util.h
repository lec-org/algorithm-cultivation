#pragma once
#include <graphics.h>
#include "camera.h"

void flipImage(IMAGE* src, IMAGE* dst);

void putImageAlpha(int x, int y, IMAGE* img);		//图像绘制(透明度)

//裁剪任意位置的图并显示
	//在(dst_x, dst_y) 处 显示 (src_x, src_y), w, h 的 图
void putImageAlpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y);

void putLine(int x1, int y1, int x2, int y2);

void sketchImage(IMAGE* src, IMAGE* dst);
