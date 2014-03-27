#include "stdafx.h"
#include "OpenCVSDL2Window.h"

bool keyevent_handler(SDL_Event evt)
{
	switch(evt.key.keysym.sym) {
		case SDLK_ESCAPE:
			return true;
			break;
		case SDLK_c:
			break;
		case SDLK_SPACE:
			break;
		case SDLK_LEFT:
			break;
		case SDLK_RIGHT:
			break;
		default:
			break;
	}					
	return false;
}

int main(int argc, char* argv[])
{
	OpenCVSDL2Window::init();
	OpenCVSDL2Window::set_keyevent_handler(keyevent_handler);

	OpenCVSDL2Window window;
	window.create(0, 0, 640, 480, SDL_SWSURFACE | SDL_WINDOW_BORDERLESS, "image");

	cv::Mat image;
	image.create(cv::Size(640, 480), CV_8UC3);

	cv::VideoCapture capture;
	capture.open(0);

	while(true) {
		capture >> image;

		// show image
		window.blt(image);

		if (OpenCVSDL2Window::process_event() == true) break;
	}

	return 0;
}

