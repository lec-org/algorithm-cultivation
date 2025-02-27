#pragma once
#include <graphics.h>
#include "camera.h"

void flipImage(IMAGE* src, IMAGE* dst);

void putImageAlpha(int x, int y, IMAGE* img);		//ͼ�����(͸����)

//�ü�����λ�õ�ͼ����ʾ
	//��(dst_x, dst_y) �� ��ʾ (src_x, src_y), w, h �� ͼ
void putImageAlpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y);

void putLine(int x1, int y1, int x2, int y2);

void sketchImage(IMAGE* src, IMAGE* dst);
