#include "rtiow.h"
// This contains the lower level code

void rtiow::create_window()
{
	if(SDL_Init( SDL_INIT_EVERYTHING ) != 0)
	{
		printf("Error: %s\n", SDL_GetError());
	}

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 8);

	// this is how you query the screen resolution
	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);

	// pulling these out because I'm going to try to span the whole screen with
	// the window, in a way that's flexible on different resolution screens
	int total_screen_width = dm.w;
	int total_screen_height = dm.h;
	
	cout << "creating window...";

	// window = SDL_CreateWindow( "OpenGL Window", 0, 0, total_screen_width, total_screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_BORDERLESS );
	window = SDL_CreateWindow( "OpenGL Window", 0, 0, total_screen_width, total_screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE );
  	SDL_ShowWindow(window);
	
	cout << "done." << endl;


	cout << "setting up OpenGL context...";
	// OpenGL 4.3 + GLSL version 430
	const char* glsl_version = "#version 430";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
	GLcontext = SDL_GL_CreateContext( window );

	SDL_GL_MakeCurrent(window, GLcontext);
	SDL_GL_SetSwapInterval(1); // Enable vsync
	// SDL_GL_SetSwapInterval(0); // explicitly disable vsync


	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
	}

	glEnable(GL_DEPTH_TEST);
    /* glEnable(GL_POINT_SMOOTH); */

    glPointSize(3.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io; // void cast prevents unused variable warning

	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(window, GLcontext);
	ImGui_ImplOpenGL3_Init(glsl_version);

	clear_color = ImVec4(75.0f/255.0f, 75.0f/255.0f, 75.0f/255.0f, 0.5f); // initial value for clear color

	// really excited by the fact imgui has an hsv picker to set this
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear( GL_COLOR_BUFFER_BIT );
	SDL_GL_SwapWindow( window );
	
	cout << "done." << endl;
	
	ImVec4* colors = ImGui::GetStyle().Colors;
	
	colors[ImGuiCol_Text]                   = ImVec4(0.64f, 0.37f, 0.37f, 1.00f);
	colors[ImGuiCol_TextDisabled]           = ImVec4(0.49f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_WindowBg]               = ImVec4(0.17f, 0.00f, 0.00f, 0.94f);
	colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg]                = ImVec4(0.18f, 0.00f, 0.00f, 0.94f);
	colors[ImGuiCol_Border]                 = ImVec4(0.35f, 0.00f, 0.03f, 0.50f);
	colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg]                = ImVec4(0.14f, 0.04f, 0.00f, 1.00f);
	colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.14f, 0.04f, 0.00f, 1.00f);
	colors[ImGuiCol_FrameBgActive]          = ImVec4(0.14f, 0.04f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBg]                = ImVec4(0.14f, 0.04f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgActive]          = ImVec4(0.14f, 0.04f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark]              = ImVec4(0.87f, 0.23f, 0.09f, 1.00f);
	colors[ImGuiCol_SliderGrab]             = ImVec4(0.87f, 0.23f, 0.09f, 1.00f);
	colors[ImGuiCol_SliderGrabActive]       = ImVec4(1.00f, 0.33f, 0.00f, 1.00f);
	colors[ImGuiCol_Button]                 = ImVec4(0.81f, 0.38f, 0.09f, 0.08f);
	colors[ImGuiCol_ButtonHovered]          = ImVec4(0.87f, 0.23f, 0.09f, 1.00f);
	colors[ImGuiCol_ButtonActive]           = ImVec4(1.00f, 0.33f, 0.00f, 1.00f);
	colors[ImGuiCol_Header]                 = ImVec4(0.81f, 0.38f, 0.09f, 0.08f);
	colors[ImGuiCol_HeaderHovered]          = ImVec4(0.87f, 0.23f, 0.09f, 1.00f);
	colors[ImGuiCol_HeaderActive]           = ImVec4(1.00f, 0.33f, 0.00f, 1.00f);
	colors[ImGuiCol_Separator]              = ImVec4(0.81f, 0.38f, 0.09f, 0.08f);
	colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.87f, 0.23f, 0.09f, 1.00f);
	colors[ImGuiCol_SeparatorActive]        = ImVec4(1.00f, 0.33f, 0.00f, 1.00f);
	colors[ImGuiCol_ResizeGrip]             = ImVec4(0.81f, 0.38f, 0.09f, 0.08f);
	colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.87f, 0.23f, 0.09f, 1.00f);
	colors[ImGuiCol_ResizeGripActive]       = ImVec4(1.00f, 0.33f, 0.00f, 1.00f);
	colors[ImGuiCol_Tab]                    = ImVec4(0.81f, 0.38f, 0.09f, 0.08f);
	colors[ImGuiCol_TabHovered]             = ImVec4(0.87f, 0.23f, 0.09f, 1.00f);
	colors[ImGuiCol_TabActive]              = ImVec4(1.00f, 0.33f, 0.00f, 1.00f);
	colors[ImGuiCol_TabUnfocused]           = ImVec4(0.81f, 0.38f, 0.09f, 0.08f);
	colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.81f, 0.38f, 0.09f, 0.08f);
	colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.81f, 0.38f, 0.09f, 0.08f);
	colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight]           = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);



    // use the defines
    num_samples = NUM_SAMPLES;

    // initialize timer, sample count
    sample_count = 0;
    total_time = 0;

    // initialize the image model
    model.resize(WIDTH);

    for(auto & x : model)
    {
        x.resize(HEIGHT);
        for(auto & y : x)
        {
            y.resize(0); // no samples initially
        }
    }


    // create the camera
    const auto aspect_ratio = 2.0;
    const int image_width = WIDTH;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    glm::dvec3 lookfrom(13,5,3);
    /* glm::dvec3 lookat(0,0,0); */
    glm::dvec3 lookat(0.25,0,0.25);
    glm::dvec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    cam = camera(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);



    // create the world
    world = hittable_list();

    // add stuff to it
    auto ground_material = make_shared<lambertian>(glm::dvec3(0.4,0.3,0.2));
    world.add(make_shared<sphere>(glm::dvec3(0,-1000,0), 1000, ground_material));

    /* long unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count(); */

    /* std::default_random_engine engine{seed}; */
    /* std::uniform_real_distribution<double> distribution{0, 1}; */
    /* std::uniform_real_distribution<double> distribution2{0.5, 1}; */
    /* std::uniform_real_distribution<double> distribution3{0, 0.5}; */

    /* for (int a = -11; a < 11; a++) */ 
    /* { */
    /*     for (int b = -11; b < 11; b++) */ 
    /*     { */
    /*         auto choose_mat = distribution(engine); */
    /*         glm::dvec3 center(a + 0.9*distribution(engine), 0.2, b + 0.9*distribution(engine)); */

    /*         if (glm::length(center - glm::dvec3(4, 0.2, 0)) > 0.9) */ 
    /*         { */
    /*             shared_ptr<material> sphere_material; */

    /*             if (choose_mat < 0.8) */ 
    /*             { */
    /*                 // diffuse */
    /*                 auto albedo = glm::dvec3(distribution(engine), distribution(engine), distribution(engine)); */
    /*                 sphere_material = make_shared<lambertian>(albedo); */
    /*                 world.add(make_shared<sphere>(center, 0.2, sphere_material)); */
    /*             } */ 
    /*             else if (choose_mat < 0.95) */ 
    /*             { */
    /*                 // metal */
    /*                 auto albedo = glm::dvec3(distribution2(engine), distribution2(engine), distribution2(engine)); */
    /*                 auto fuzz = distribution3(engine); */
    /*                 sphere_material = make_shared<metal>(albedo, fuzz); */
    /*                 world.add(make_shared<sphere>(center, 0.2, sphere_material)); */
    /*             } */ 
    /*             else */ 
    /*             { */
    /*                 // glass */
    /*                 sphere_material = make_shared<dielectric>(1.5); */
    /*                 world.add(make_shared<sphere>(center, 0.2, sphere_material)); */
    /*             } */
    /*         } */
    /*     } */
    /* } */

    /* auto material1 = make_shared<dielectric>(1.5); */
    /* world.add(make_shared<sphere>(glm::dvec3(0, 1, 0), 1.0, material1)); */

    /* auto material2 = make_shared<lambertian>(glm::dvec3(0.4, 0.2, 0.1)); */
    /* world.add(make_shared<sphere>(glm::dvec3(-4, 1, 0), 1.0, material2)); */

    /* auto material3 = make_shared<metal>(glm::dvec3(0.7, 0.6, 0.5), 0.0); */
    /* world.add(make_shared<sphere>(glm::dvec3(4, 1, 0), 1.0, material3)); */ 


    // materials test
   
    for(float x = -1.0; x < 5; x+=1.0)
    {
        for(float z = -2.0; z < 5; z+=1.0)
        {
            auto material = make_shared<metal>(glm::dvec3(0.7+0.05*x, 0.6, 0.5+0.1*z), (z+1.0)/8.0);
            world.add(make_shared<sphere>(glm::dvec3(x, 0.75, z), 0.3, material));
            
            auto material2 = make_shared<dielectric>(1.05 + (z+2)/5.0);
            world.add(make_shared<sphere>(glm::dvec3(x-0.15, 0.5, z-0.5), 0.25, material2));
        }
    }
}

void rtiow::gl_setup() 
{
	// some info on your current platform
	const GLubyte *renderer = glGetString( GL_RENDERER ); // get renderer string
	const GLubyte *version = glGetString( GL_VERSION );		// version as a string
	printf( "Renderer: %s\n", renderer );
	printf( "OpenGL version supported %s\n\n\n", version );
	
	
	
    // create the shader for the triangles to draw the pheremone field
    display_shader = Shader("resources/code/shaders/blit.vs.glsl", "resources/code/shaders/blit.fs.glsl").Program;

    // set up the points for the continuum
    //  A---------------B
    //  |          .    |
    //  |       .       | 
    //  |    .          | 
    //  |               | 
    //  C---------------D

    // diagonal runs from C to B 
    //  A is -1, 1
    //  B is  1, 1
    //  C is -1,-1
    //  D is  1,-1
    std::vector<glm::vec3> points;
    
    points.clear();
    points.push_back(glm::vec3(-1, 1, 0.5));  //A
    points.push_back(glm::vec3(-1,-1, 0.5));  //C
    points.push_back(glm::vec3( 1, 1, 0.5));  //B

    points.push_back(glm::vec3( 1, 1, 0.5));  //B
    points.push_back(glm::vec3(-1,-1, 0.5));  //C
    points.push_back(glm::vec3( 1,-1, 0.5));  //D

    // vao, vbo
    cout << "  setting up vao, vbo for display geometry...";
    glGenVertexArrays( 1, &display_vao );
    glBindVertexArray( display_vao );

    glGenBuffers( 1, &display_vbo );
    glBindBuffer( GL_ARRAY_BUFFER, display_vbo );
    cout << "done." << endl;

    // buffer the data
    cout << "  buffering vertex data...";
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), NULL, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * points.size(), &points[0]);
    cout << "done." << endl;

    // set up attributes
    cout << "  setting up attributes in continuum shader...";
    GLuint points_attrib = glGetAttribLocation(display_shader, "vPosition");
    glEnableVertexAttribArray(points_attrib);
    glVertexAttribPointer(points_attrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) (static_cast<const char*>(0) + (0)));
    cout << "done." << endl; 


    // create the image textures
    glGenTextures(1, &display_texture);
    glActiveTexture(GL_TEXTURE0+1);  
    glBindTexture(GL_TEXTURE_2D, display_texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 




    // compile the compute shader to do the raytracing
    
    // ...



}


static void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}



void rtiow::one_thread_sample(int index)
{
    long unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine engine{seed};
    std::uniform_real_distribution<double> distribution{0, 1};

    // do a sample for all the pixels - this takes time
    for(auto & x : model)
    {
        for(auto & y : x)
        {
            int x_coord = &x - &model[0];
            int y_coord = &y - &x[0];
            if(x_coord % 16 == index)
            {
                double x_fl = (static_cast<double>(x_coord) + distribution(engine))/(static_cast<double>(WIDTH-1)); 
                double y_fl = (static_cast<double>(y_coord) + distribution(engine))/(static_cast<double>(HEIGHT-1)); 

                ray r = cam.get_ray(x_fl, y_fl);

                // figure out the color, put it in 'sample'
                glm::dvec3 sample = ray_color(r, world, max_depth);
            
                // push it onto the vector of samples for this pixel
                y.push_back(sample);
            }
        }
    }
}


void rtiow::do_a_sample()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io; // void cast prevents unused variable warning
    //get the screen dimensions and pass in as uniforms
    

	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);   // from hsv picker
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                     // clear the background


    // start a timer
    auto start = std::chrono::high_resolution_clock::now();
   

    // launch all the threads
    std::thread t0(&rtiow::one_thread_sample, this, 0);
    std::thread t1(&rtiow::one_thread_sample, this, 1);
    std::thread t2(&rtiow::one_thread_sample, this, 2);
    std::thread t3(&rtiow::one_thread_sample, this, 3);
    std::thread t4(&rtiow::one_thread_sample, this, 4);
    std::thread t5(&rtiow::one_thread_sample, this, 5);
    std::thread t6(&rtiow::one_thread_sample, this, 6);
    std::thread t7(&rtiow::one_thread_sample, this, 7);
    std::thread t8(&rtiow::one_thread_sample, this, 8);
    std::thread t9(&rtiow::one_thread_sample, this, 9);
    std::thread t10(&rtiow::one_thread_sample, this, 10);
    std::thread t11(&rtiow::one_thread_sample, this, 11);
    std::thread t12(&rtiow::one_thread_sample, this, 12);
    std::thread t13(&rtiow::one_thread_sample, this, 13);
    std::thread t14(&rtiow::one_thread_sample, this, 14);
    std::thread t15(&rtiow::one_thread_sample, this, 15);


    // join all the threads
    t0.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join(); 
    t8.join();
    t9.join();
    t10.join();
    t11.join();
    t12.join();
    t13.join();
    t14.join();
    t15.join(); 



    // increment the sample count
    sample_count++;

    // stop that timer, add its value to the total time
    auto end = std::chrono::high_resolution_clock::now();
    int time_in_milliseconds = (int)std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count();
    total_time += time_in_milliseconds;

    // start a new timer, to see how long it took to send the data to the GPU
    start = std::chrono::high_resolution_clock::now();

    if(send_tex)
    {
        // these hold the running average values, the data for the texture
        std::vector<unsigned char> tex_data;
        tex_data.resize(0);             //zero it out

        long unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();

        std::default_random_engine engine{seed};
        std::uniform_real_distribution<double> distribution{0, 1};
    
        // iterate through the samples per pixel and compute the average color
        for(unsigned int y = 0; y < HEIGHT; y++)         // iterating through y
        {   for(unsigned int x = 0; x < WIDTH; x++)         // iterating through x
            {   glm::dvec3 sum = glm::dvec3(0,0,0);
                for(auto samp : model[x][y])     // samples
                {
                    // add up the samples
                    sum += samp;
                }

                //average it out, store it 
                tex_data.push_back(static_cast<unsigned char>(255 * (sum.x / (double)sample_count)));
                tex_data.push_back(static_cast<unsigned char>(255 * (sum.y / (double)sample_count)));
                tex_data.push_back(static_cast<unsigned char>(255 * (sum.z / (double)sample_count)));
                /* tex_data.push_back(255*distribution(engine)); */
                tex_data.push_back(255);
            }
        }

        // buffer the averaged data to the GPU
        glBindTexture(GL_TEXTURE_2D, display_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, &tex_data[0]);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    // stop the timer
    end = std::chrono::high_resolution_clock::now();
    int time_buffering = (int)std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count();
    total_time += time_buffering;

    // display this texture
    glUseProgram(display_shader);
    glBindVertexArray( display_vao );
    glBindBuffer( GL_ARRAY_BUFFER, display_vbo );

    glDrawArrays( GL_TRIANGLES, 0, 6 );


	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(window);
	ImGui::NewFrame();

	// show the demo window
	 /* static bool show_demo_window = true; */
	 /* if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window); */

	// do my own window
	ImGui::SetNextWindowPos(ImVec2(10,10));
	ImGui::SetNextWindowSize(ImVec2(300,200));
	ImGui::Begin("Controls", NULL, 0);

    
    ImGui::Text("How many samples do you want?");

    ImGui::InputInt(" ", &num_samples);
    ImGui::SameLine(); HelpMarker("You can apply arithmetic operators +,*,/ on numerical values.\n  e.g. [ 100 ], input \'*2\', result becomes [ 200 ]\nUse +- to subtract.\n");
    ImGui::Text("%i samples have been completed", sample_count);

    ImGui::Text(" ");
    ImGui::Checkbox("Send to GPU each sample: ", &send_tex);
    
    ImGui::Text(" ");
    ImGui::Text("Previous sample took:        %*i ms", 9, time_in_milliseconds);
    ImGui::Text("Averaging/GPU buffering took:%*i ms", 9, time_buffering);
    ImGui::Text("Total elapsed:              %*li ms", 10, total_time);


	ImGui::End();
	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());   // put imgui data into the framebuffer
	
	SDL_GL_SwapWindow(window);			// swap the double buffers 
	
	// handle events
	
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);

		if (event.type == SDL_QUIT)
			pquit = true;

		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
			pquit = true;

		if ((event.type == SDL_KEYUP  && event.key.keysym.sym == SDLK_ESCAPE) || (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_X1)) //x1 is browser back on the mouse
			pquit = true;
	
        if((event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE))
            send_tex = !send_tex;
    }
}



void rtiow::quit()
{
  //shutdown everything
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  //destroy window
  SDL_GL_DeleteContext(GLcontext);
  SDL_DestroyWindow(window);
  SDL_Quit();

  //average the samples and create your output using LodePNG
    std::vector<unsigned char> tex_data;
    tex_data.resize(0);             //zero it out

    long unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine engine{seed};
    std::uniform_real_distribution<double> distribution{0, 1};
    
    // iterate through the samples per pixel and compute the average color
    for(unsigned int y = 1; y <= HEIGHT; y++)         // iterating through y
    {   for(unsigned int x = 0; x < WIDTH; x++)         // iterating through x
        {   glm::dvec3 sum = glm::dvec3(0,0,0);
            for(auto samp : model[x][HEIGHT-y])     // samples
            {
               // add up the samples
                sum += samp;
            }

            // average it out, store it 
            tex_data.push_back(static_cast<unsigned char>(255 * (sum.x / (double)sample_count)));
            tex_data.push_back(static_cast<unsigned char>(255 * (sum.y / (double)sample_count)));
            tex_data.push_back(static_cast<unsigned char>(255 * (sum.z / (double)sample_count)));
            /* tex_data.push_back(255*distribution(engine)); */
            tex_data.push_back(255);
        }
    }


    unsigned width, height;

    width = WIDTH;
    height = HEIGHT;

    tex_data.resize(4*WIDTH*HEIGHT);
    std::string filename = std::string("save3.png");

    unsigned error = lodepng::encode(filename.c_str(), tex_data, width, height);

    if(error) std::cout << "decode error during save(\" "+ filename +" \") " << error << ": " << lodepng_error_text(error) << std::endl;

  cout << "goodbye." << endl;
}



bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    glm::dvec3 oc = r.origin - center_point;
    auto a = pow(glm::length(r.direction), 2);
    auto half_b = glm::dot(oc, r.direction);
    auto c = pow(glm::length(oc), 2) - radius*radius; 
    auto discriminant = half_b*half_b - a*c;

    if(discriminant > 0)
    {
        auto root = std::sqrt(discriminant);
        auto temp = (-half_b - root)/a;
        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.point = r.origin + rec.t * r.direction;
            rec.normal = (rec.point - center_point) / radius;
            glm::dvec3 outward_normal = (rec.point - center_point) / radius;
            rec.set_face_normal(r, outward_normal);

            rec.mat_ptr = mat_ptr;

            return true;
        }
        temp = (-half_b + root) / a;
        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.point = r.origin + rec.t * r.direction;
            rec.normal = (rec.point - center_point) / radius;
            glm::dvec3 outward_normal = (rec.point - center_point) / radius;
            rec.set_face_normal(r, outward_normal);
            
            rec.mat_ptr = mat_ptr;

            return true;
        }
    }
    return false;
}


bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for(const auto& object : objects)
    {
        if(object->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

glm::dvec3 rtiow::ray_color(const ray& r, const hittable& world, int depth)
{
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
    {
        return glm::dvec3(0,0,0);
    }

    if (world.hit(r, 0.001, std::numeric_limits<double>::infinity(), rec)) 
    {
        ray scattered;
        glm::dvec3 attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return glm::dvec3(0,0,0);
    }

    glm::dvec3 unit_direction = glm::normalize(r.direction);
    auto t = 0.5*(unit_direction.y + 1.0);
    return (1.0-t)*glm::dvec3(1.0, 1.0, 1.0) + t*glm::dvec3(0.5, 0.7, 1.0);
}

double schlick(double cosine, double ref_idx) 
{
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}

