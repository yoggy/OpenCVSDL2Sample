#pragma once

class OpenCVSDL2Window
{
public:
	OpenCVSDL2Window();
	virtual ~OpenCVSDL2Window();

	bool create(int x, int y, int width, int height, Uint32 flag, const char *title);
	void close();

	bool blt(const cv::Mat &image);

	static bool init();
	static bool process_event();

	static void set_keyevent_handler(bool (*keyevent_handler)(SDL_Event));

protected:
	SDL_Window * window_;
	SDL_Surface* screen_; 

	SDL_Surface* surface_;
	cv::Mat surface_img_;

	static bool (*keyevent_handler_)(SDL_Event);
};

