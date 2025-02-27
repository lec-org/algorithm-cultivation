#include "platform.h"


void Platform::render() const {

	putImageAlpha(renderPos.x, renderPos.y, img);

	if (isDebug) {
		setlinecolor(RGB(255, 0, 0));
		putLine(shape.left, shape.y, shape.right, shape.y);
	}
}

