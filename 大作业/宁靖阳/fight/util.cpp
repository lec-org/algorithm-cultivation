#include "util.h"
#pragma comment(lib, "MSIMG32.LIB")		//AlphaBlend

void flipImage(IMAGE* src, IMAGE* dst) {

	int height = src->getheight();
	int width = src->getwidth();
	Resize(dst, width, height);

	auto srcPixels = GetImageBuffer(src);
	auto dstPixels = GetImageBuffer(dst);

	for (int h = 0; h < height; h++)
		for (int w = 0; w < width; w++)
			dstPixels[h * width + w] = srcPixels[h * width + width - 1 - w];
}

void putImageAlpha(int x, int y, IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();

	auto cameraX = Camera::getCamera().getPostion().x;
	auto cameraY = Camera::getCamera().getPostion().y;

	AlphaBlend(GetImageHDC(nullptr), x - cameraX, y - cameraY, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255, AC_SRC_ALPHA });
}

//在(dst_x, dst_y) 处 显示 (src_x, src_y), w, h 的 图
void putImageAlpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y) {

	int w = width;
	int h = height;

	//将(src_x, src_y), w, h 的图像 复制到 (dst_x, dst_y)处
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
		GetImageHDC(img), src_x, src_y, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

void putLine(int x1, int y1, int x2, int y2) {

	auto cameraX = Camera::getCamera().getPostion().x;
	auto cameraY = Camera::getCamera().getPostion().y;

	line(x1 - cameraX, y1 - cameraY, x2 - cameraX, y2 - cameraY);
}

void sketchImage(IMAGE* src, IMAGE* dst) {

	auto W = src->getwidth(), H = src->getheight();
	Resize(dst, W, H);

	auto srcBuffer = GetImageBuffer(src);
	auto dstBuffer = GetImageBuffer(dst);

	for (int h = 0; h < H;h++)
		for (int w = 0; w < W; w++) {

			auto idx = h * W + w;

			dstBuffer[idx] = BGR(RGB(255, 255, 255)) | (srcBuffer[idx] & 0xFF000000);
		}

}

