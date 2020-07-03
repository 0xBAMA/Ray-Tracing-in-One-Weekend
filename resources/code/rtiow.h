#ifndef SDF
#define SDF

#include "includes.h"

class rtiow
{
public:

	rtiow();
	~rtiow();
	
private:

	SDL_Window * window;
	SDL_GLContext GLcontext;
	
	ImVec4 clear_color;
	
    GLuint display_shader;
    GLuint display_vao;
    GLuint display_vbo;


    int num_samples;
    int sample_count;
    long int total_time;

	void create_window();
	void gl_setup();
	void do_a_sample();
	
	void quit();
	
	bool pquit;
		
};

#endif
