#include "StdAfx.h"
#include "OpenCVSDL2Window.h"

#define MASK_R 0x00ff0000
#define MASK_G 0x0000ff00
#define MASK_B 0x000000ff
#define MASK_A 0x00000000

bool (*OpenCVSDL2Window::keyevent_handler_)(SDL_Event) = NULL;

OpenCVSDL2Window::OpenCVSDL2Window(void)
	: window_(NULL), surface_(NULL), screen_(NULL)
{

}

OpenCVSDL2Window::~OpenCVSDL2Window(void)
{

}

bool OpenCVSDL2Window::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error : SDL_Init() failed...\n");
		return false;
	}
}

void OpenCVSDL2Window::set_keyevent_handler(bool (*keyevent_handler)(SDL_Event))
{
	keyevent_handler_ = keyevent_handler;
}

bool OpenCVSDL2Window::process_event()
{
	SDL_Event evt;
	while(SDL_PollEvent(&evt)) {
		switch(evt.type){
			case SDL_KEYUP:
				if (keyevent_handler_ != NULL) {
					bool rv = (*keyevent_handler_)(evt);
					if (rv == true) return true;
				}
				break;
			case SDL_QUIT:
				return true;
				break;
			default:
				break;
			}
		}
	return false;
}

bool OpenCVSDL2Window::create(int x, int y, int width, int height, Uint32 flag, const char *title)
{
	window_ = SDL_CreateWindow(title, x, y, width, height, flag);
	if (window_ == NULL) {
		close();
		return false;
	}
	SDL_ShowWindow(window_);
	SDL_ShowCursor(SDL_DISABLE);

	screen_ = SDL_GetWindowSurface(window_);

	surface_ = SDL_CreateRGBSurface(
		SDL_SWSURFACE,
		width,
		height,
		24, 
		MASK_R,
		MASK_G,
		MASK_B,
		MASK_A);

	surface_img_ = cv::Mat(height, width, CV_8UC3, (uchar*)(surface_->pixels), width * 3);

	return true;
}

void OpenCVSDL2Window::close()
{
	if (surface_ != NULL) {
		SDL_FreeSurface(surface_);
		surface_ = NULL;
	}

	if (window_ != NULL) {
		SDL_DestroyWindow(window_);
		window_ = NULL;
		screen_ = NULL;
	}
}

bool OpenCVSDL2Window::blt(const cv::Mat &image)
{
	if (image.empty()) return false;

	SDL_LockSurface(surface_);

	if (image.size() == surface_img_.size()) {
		image.copyTo(surface_img_);
	}
	else {
		cv::resize(image, surface_img_, surface_img_.size());
	}

	SDL_UnlockSurface(surface_);

	SDL_BlitSurface(surface_, NULL, screen_, NULL); 
	SDL_UpdateWindowSurface(window_);

	return true;
}

