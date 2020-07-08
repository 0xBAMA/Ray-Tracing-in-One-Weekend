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

    glm::dvec3 lookfrom(-7,5,-2);
    /* glm::dvec3 lookfrom(13,5,3); */
    glm::dvec3 lookat(0,0,0);
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
   
    /* for(float x = -1.0; x < 5; x+=1.0) */
    /* { */
    /*     for(float z = -2.0; z < 5; z+=1.0) */
    /*     { */
    /*         auto material = make_shared<metal>(glm::dvec3(0.7+0.05*x, 0.6, 0.5+0.1*z), (z+1.0)/8.0); */
    /*         world.add(make_shared<sphere>(glm::dvec3(x, 0.75, z), 0.3, material)); */
            
    /*         auto material2 = make_shared<dielectric>(1.05 + (z+2)/5.0); */
    /*         world.add(make_shared<sphere>(glm::dvec3(x-0.15, 0.5, z-0.5), 0.25, material2)); */
    /*     } */
    /* } */
















    /* auto material = make_shared<dielectric>(1.4); */
    auto material = make_shared<metal>(glm::dvec3(0.7, 0.4, 0.1),0.05);



  world.add(make_shared<sphere>(glm::dvec3(0.4362469698291557, 0.3 ,0.17647058823529438), 0.10778805730537211, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5115465719880611, 0.3 ,-1.1166145945296537), 0.40898646594099775, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3091735647707088, 0.3 ,0.5295867823853555), 0.22496840231697413, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.40867297637918376, 0.3 ,1.1582290129360184), 0.40898646594099775, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4205502715329005, 0.3 ,0.024489699948873567), 0.04500126412035183, material));
  world.add(make_shared<sphere>(glm::dvec3(0.574441826111077, 0.3 ,0.23237316009433379), 0.041285467652066095, material));
  world.add(make_shared<sphere>(glm::dvec3(0.31929742726210886, 0.3 ,0.2747934301139328), 0.04500126412035183, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.09046606425645554, 0.3 ,-1.3843640519895728), 0.24988300987963333, material));
  world.add(make_shared<sphere>(glm::dvec3(0.43237488414093084, 0.3 ,-0.6216199697132115), 0.09229971455247453, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0757586072856888, 0.3 ,-1.0026784773368547), 0.16661466294571936, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5072939304964494, 0.3 ,0.263068615672539), 0.10712136341401346, material));
  world.add(make_shared<sphere>(glm::dvec3(1.043283854268617, 0.3 ,0.42202909863481425), 0.06185208768446871, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2662708628149195, 0.3 ,0.8588935856375124), 0.10712136341401346, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0275273513050804, 0.3 ,0.9321134477857367), 0.24988300987963333, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.12142340317391626, 0.3 ,0.7474060371336348), 0.09229971455247453, material));
  world.add(make_shared<sphere>(glm::dvec3(0.07607062961137279, 0.3 ,1.4686163451951408), 0.16661466294571936, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3777200743414306, 0.3 ,0.06763068715992254), 0.015789940580690984, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4154729377282037, 0.3 ,-0.045018298404019386), 0.024691928901564464, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4705262002912015, 0.3 ,0.05824529710349635), 0.015306561197097234, material));
  world.add(make_shared<sphere>(glm::dvec3(0.558575871304806, 0.3 ,0.17882524593774968), 0.014563503980682294, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6329408880460498, 0.3 ,0.25603719580080625), 0.021818627565193892, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5258079873482709, 0.3 ,0.2598296230790104), 0.014563503980682294, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3185077971638395, 0.3 ,0.21400735396723614), 0.015789940580690984, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2673213643188169, 0.3 ,0.32122219312249284), 0.024691928901564464, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3786868331086183, 0.3 ,0.2852782890885957), 0.015306561197097234, material));
  world.add(make_shared<sphere>(glm::dvec3(0.22189866014313642, 0.3 ,-1.5274654450390828), 0.09370064767983724, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.49805818359911114, 0.3 ,-1.3930390127163947), 0.15780141549598642, material));
  world.add(make_shared<sphere>(glm::dvec3(0.03844423103441552, 0.3 ,-1.0976294972371752), 0.0644966477336341, material));
  world.add(make_shared<sphere>(glm::dvec3(0.33492842308102966, 0.3 ,-0.7068882343573402), 0.03718576621089122, material));
  world.add(make_shared<sphere>(glm::dvec3(0.41948043337158036, 0.3 ,-0.48922478048652834), 0.04072191147507205, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5477465359965056, 0.3 ,-0.6744960055224625), 0.03461164512342332, material));
  world.add(make_shared<sphere>(glm::dvec3(0.980499306473872, 0.3 ,-1.2207991016858917), 0.0713999188713826, material));
  world.add(make_shared<sphere>(glm::dvec3(1.287589420290348, 0.3 ,-0.8656247532468793), 0.08568677705244263, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9011894150566572, 0.3 ,-0.8778569175129436), 0.047989215566228816, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5441766076878136, 0.3 ,0.40604057025157086), 0.04053130900660721, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5722985715714728, 0.3 ,0.10779467318173536), 0.061210453477297956, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3694747065494681, 0.3 ,0.28005992853001876), 0.03174131408418697, material));
  world.add(make_shared<sphere>(glm::dvec3(1.114559511754134, 0.3 ,0.37541252006738807), 0.023314365495911482, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9591193190376998, 0.3 ,0.38798286778863406), 0.02893786123867828, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0621021893883333, 0.3 ,0.5050904916561687), 0.023314365495911482, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3921841989130366, 0.3 ,0.78177586092008), 0.04053130900660721, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2050358507076853, 0.3 ,1.0156924181272884), 0.061210453477297956, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1790268220443463, 0.3 ,0.7508596995091701), 0.03174131408418697, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9025091120149105, 0.3 ,1.2521449612132882), 0.09370064767983724, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3265156149530397, 0.3 ,0.6549625702936606), 0.15780141549598642, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7355155417691938, 0.3 ,0.8156502681425015), 0.0644966477336341, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.25074739474050695, 0.3 ,0.7409411369948586), 0.03718576621089122, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.038641070722980175, 0.3 ,0.6432818880374951), 0.04072191147507205, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.07526307622511419, 0.3 ,0.8656249756788814), 0.03461164512342332, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.1440494157504041, 0.3 ,1.5591597424557875), 0.0713999188713826, material));
  world.add(make_shared<sphere>(glm::dvec3(0.32361317845036885, 0.3 ,1.5173882955297273), 0.08568677705244263, material));
  world.add(make_shared<sphere>(glm::dvec3(0.03738353486453849, 0.3 ,1.2575283697620994), 0.047989215566228816, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3986989331096037, 0.3 ,0.06979739917481198), 0.005300511196604404, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3632985771408549, 0.3 ,0.08655139267005424), 0.008000239715123056, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3742023096024585, 0.3 ,0.0460212616972544), 0.006103938417452883, material));
  world.add(make_shared<sphere>(glm::dvec3(0.39339850083481487, 0.3 ,-0.020971214548529654), 0.00795072733399889, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4131995115108177, 0.3 ,-0.08524425963113985), 0.015598224032020897, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4406050680113768, 0.3 ,-0.02438313870530684), 0.007826278127141015, material));
  world.add(make_shared<sphere>(glm::dvec3(0.450967841422789, 0.3 ,0.06443704558074953), 0.0052084857399970425, material));
  world.add(make_shared<sphere>(glm::dvec3(0.48794671688227054, 0.3 ,0.07323126253221307), 0.007672854768727611, material));
  world.add(make_shared<sphere>(glm::dvec3(0.46989276545251324, 0.3 ,0.03703669950833283), 0.005911493653629326, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5474616802427675, 0.3 ,0.19484526348061038), 0.004934347312141251, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5500446010594217, 0.3 ,0.1585780879633365), 0.007407612924032056, material));
  world.add(make_shared<sphere>(glm::dvec3(0.577515641609268, 0.3 ,0.18562779610930064), 0.0055608491274861315, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6226667216765297, 0.3 ,0.2290550130784061), 0.007053446815660073, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6656760885187513, 0.3 ,0.2692792363946475), 0.01349348068504942, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6067964663412945, 0.3 ,0.2682873342807371), 0.007053446815660073, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5289578778222378, 0.3 ,0.2405878873194935), 0.004934347312141251, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5055989235152293, 0.3 ,0.26845074348373016), 0.007407612924032056, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5441505468443512, 0.3 ,0.26810851788176043), 0.0055608491274861315, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3350927987503509, 0.3 ,0.22703597164317685), 0.005300511196604404, material));
  world.add(make_shared<sphere>(glm::dvec3(0.32129731863645894, 0.3 ,0.19038128259552606), 0.008000239715123056, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3009550485930239, 0.3 ,0.22709333712461116), 0.006103938417452883, material));
  world.add(make_shared<sphere>(glm::dvec3(0.26817454532433227, 0.3 ,0.28859068858646214), 0.00795072733399889, material));
  world.add(make_shared<sphere>(glm::dvec3(0.23771949115058255, 0.3 ,0.34855396087255747), 0.015598224032020897, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2997320617228383, 0.3 ,0.32386425333125174), 0.007826278127141015, material));
  world.add(make_shared<sphere>(glm::dvec3(0.36893419101783564, 0.3 ,0.267229656922133), 0.0052084857399970425, material));
  world.add(make_shared<sphere>(glm::dvec3(0.40162710073408525, 0.3 ,0.2866190647604973), 0.007672854768727611, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3634858796871855, 0.3 ,0.3000815612514614), 0.005911493653629326, material));
  world.add(make_shared<sphere>(glm::dvec3(0.1869135431684822, 0.3 ,-1.4101763096141642), 0.028695020946365012, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3617063734184406, 0.3 ,-1.5479071346314548), 0.047593582084370104, material));
  world.add(make_shared<sphere>(glm::dvec3(0.10752804914436076, 0.3 ,-1.5946402659635397), 0.03893831049786449, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.34924841075319235, 0.3 ,-1.544011298392765), 0.05418202616114306, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7546366120413746, 0.3 ,-1.3325430474888913), 0.10581241523128955, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.3528721923724302, 0.3 ,-1.254410541079532), 0.04293927593663331, material));
  world.add(make_shared<sphere>(glm::dvec3(0.08298432262817712, 0.3 ,-1.1732990550101254), 0.02330825949104532, material));
  world.add(make_shared<sphere>(glm::dvec3(0.08479347611633181, 0.3 ,-1.0158540241385718), 0.029500589035134545, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.05092565724881282, 0.3 ,-1.1114018171308118), 0.025928203535302778, material));
  world.add(make_shared<sphere>(glm::dvec3(0.38409284662552323, 0.3 ,-0.71475181549318), 0.012603554438644485, material));
  world.add(make_shared<sphere>(glm::dvec3(0.29393051451181806, 0.3 ,-0.7468474125097271), 0.020064250607129405, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3326409454084036, 0.3 ,-0.6564222822092991), 0.013332001755549326, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3811766836376155, 0.3 ,-0.52839185623755), 0.014061635932598442, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4150322344529348, 0.3 ,-0.4257293727816053), 0.02292911580048925, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4640079319387048, 0.3 ,-0.5204744652864843), 0.013676994108973096, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5060631887522401, 0.3 ,-0.6955684286133446), 0.012095404156178479, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5950784868384599, 0.3 ,-0.6977513746481776), 0.018124734764453438, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5368814198609365, 0.3 ,-0.6287088598437889), 0.012446972132499927, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9420805959775872, 0.3 ,-1.135699118603634), 0.02197033568968148, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9155718271569263, 0.3 ,-1.3100190584368552), 0.03894399012723961, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0764560519240818, 0.3 ,-1.1968034790158433), 0.027511591605000853, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2719982819309577, 0.3 ,-0.981074170597237), 0.03081065451529095, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3861292139006571, 0.3 ,-0.770304231295815), 0.05141206623146557, material));
  world.add(make_shared<sphere>(glm::dvec3(1.179241401387606, 0.3 ,-0.8408725794911294), 0.025452609781315538, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9013632695231452, 0.3 ,-0.9434195923585258), 0.01757368978644049, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8421251618155684, 0.3 ,-0.8388731433900221), 0.022780274016460877, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9636537459126956, 0.3 ,-0.8555885232321101), 0.01832574513751683, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4961734914058265, 0.3 ,0.38257427159580487), 0.012900576093804331, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5471436233941276, 0.3 ,0.4674743500831881), 0.02097407682748969, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5801415397027152, 0.3 ,0.36237462090338984), 0.01603892581095758, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6062546140903482, 0.3 ,0.18226626007602414), 0.020637149285992015, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5978729866232557, 0.3 ,0.010600917164644091), 0.039291670450262633, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4990343470811203, 0.3 ,0.13813310043819793), 0.018086877868519653, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3991400745946123, 0.3 ,0.3111736363296795), 0.011248183171497728, material));
  world.add(make_shared<sphere>(glm::dvec3(1.323596897719963, 0.3 ,0.2898768606257897), 0.015175052982857267, material));
  world.add(make_shared<sphere>(glm::dvec3(1.389837643431942, 0.3 ,0.2408827104145682), 0.012411869467457336, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1113751633853162, 0.3 ,0.4065425704166455), 0.007978127362301185, material));
  world.add(make_shared<sphere>(glm::dvec3(1.145493535244717, 0.3 ,0.3579281020388974), 0.01221898057662913, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0844704032278623, 0.3 ,0.364935982649591), 0.008546461363608229, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9935963146924914, 0.3 ,0.3705456632089252), 0.009697864882816246, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9167424024261798, 0.3 ,0.3708405609779724), 0.016774956923086528, material));
  world.add(make_shared<sphere>(glm::dvec3(0.971776118706155, 0.3 ,0.42448663136292525), 0.009697864882816246, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0814571857766868, 0.3 ,0.48050179050933867), 0.007978127362301185, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0721796517849422, 0.3 ,0.5391648725713942), 0.01221898057662913, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0331916350462125, 0.3 ,0.49170049031921675), 0.008546461363608229, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3413665782801747, 0.3 ,0.7652672032339416), 0.012900576093804331, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4370297200498063, 0.3 ,0.7396832045466386), 0.02097407682748969, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3876744299712245, 0.3 ,0.8381660502388426), 0.01603892581095758, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2812195128359738, 0.3 ,0.9857745354679162), 0.020637149285992015, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1558416940578016, 0.3 ,1.103331518222266), 0.039291670450262633, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1734705454477665, 0.3 ,0.9429483581469948), 0.018086877868519653, material));
  world.add(make_shared<sphere>(glm::dvec3(1.221981189643523, 0.3 ,0.7491221211796204), 0.011248183171497728, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1528775516628187, 0.3 ,0.7119063792747748), 0.015175052982857267, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1664239930177098, 0.3 ,0.793176035814084), 0.012411869467457336, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8461072109006583, 0.3 ,1.1435193415411626), 0.028695020946365012, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8162347831697195, 0.3 ,1.3640413398274884), 0.047593582084370104, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0314175329181756, 0.3 ,1.2209085682286178), 0.03893831049786449, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3245248816537674, 0.3 ,0.8669366642715162), 0.05418202616114306, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4688704148525789, 0.3 ,0.43309016845812104), 0.10581241523128955, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.12577915923183, 0.3 ,0.6562666183499273), 0.04293927593663331, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7561130190494545, 0.3 ,0.9010050902817557), 0.02330825949104532, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6453461025032481, 0.3 ,0.7890993219704929), 0.029500589035134545, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8093256106564191, 0.3 ,0.7634130452274919), 0.025928203535302778, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.22087776642941204, 0.3 ,0.7807755662652689), 0.012603554438644485, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.30799700370206406, 0.3 ,0.7411572374632862), 0.020064250607129405, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.21730412700800605, 0.3 ,0.7030783224707984), 0.013332001755549326, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.09340352908758182, 0.3 ,0.6448018289684994), 0.014061635932598442, material));
  world.add(make_shared<sphere>(glm::dvec3(0.002308150044128321, 0.3 ,0.5945518706785728), 0.02292911580048925, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.028363855984326558, 0.3 ,0.6967011709413069), 0.013676994108973096, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.11987397632999613, 0.3 ,0.851789656953265), 0.012095404156178479, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.057411964681863714, 0.3 ,0.9152481918216193), 0.018124734764453438, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.05123801339968492, 0.3 ,0.8251612905492043), 0.012446972132499927, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.11249551712712386, 0.3 ,1.4712828062411607), 0.02197033568968148, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.2527478766602623, 0.3 ,1.5781445481941736), 0.03894399012723961, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.058397101782203364, 0.3 ,1.6086286015149218), 0.027511591605000853, material));
  world.add(make_shared<sphere>(glm::dvec3(0.23213869203988813, 0.3 ,1.5895275351834521), 0.03081065451529095, material));
  world.add(make_shared<sphere>(glm::dvec3(0.46071202173427694, 0.3 ,1.5173882955297275), 0.05141206623146557, material));
  world.add(make_shared<sphere>(glm::dvec3(0.26294744926024716, 0.3 ,1.424266694342814), 0.025452609781315538, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.008075176925149918, 0.3 ,1.3047724178603002), 0.01757368978644049, material));
  world.add(make_shared<sphere>(glm::dvec3(0.022035297222977035, 0.3 ,1.188443260968), 0.022780274016460877, material));
  world.add(make_shared<sphere>(glm::dvec3(0.09776228816502552, 0.3 ,1.2849524497469997), 0.01832574513751683, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3562152464512537, 0.3 ,0.09724418655366085), 0.004825882641050805, material));
  world.add(make_shared<sphere>(glm::dvec3(0.37390389399127655, 0.3 ,0.03670427728850778), 0.003217823773775999, material));
  world.add(make_shared<sphere>(glm::dvec3(0.38696929000122215, 0.3 ,-0.011035601356577024), 0.00388359400027659, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3908896953888651, 0.3 ,-0.031837879744882835), 0.0032017843676430324, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3997557480023618, 0.3 ,-0.06994015963522823), 0.004772103750225276, material));
  world.add(make_shared<sphere>(glm::dvec3(0.41198656772312126, 0.3 ,-0.11156099495819666), 0.010746448881235595, material));
  world.add(make_shared<sphere>(glm::dvec3(0.42820790907144557, 0.3 ,-0.07153797411134477), 0.004726988392158296, material));
  world.add(make_shared<sphere>(glm::dvec3(0.44829902571188585, 0.3 ,-0.015660484364748845), 0.003804787337470569, material));
  world.add(make_shared<sphere>(glm::dvec3(0.44156724315283846, 0.3 ,-0.03531518404738607), 0.003148028063417162, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4967704998663077, 0.3 ,0.08176677462134446), 0.0046037128612365676, material));
  world.add(make_shared<sphere>(glm::dvec3(0.46853260492946835, 0.3 ,0.028110735595845315), 0.0031175078645608247, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5448189269640721, 0.3 ,0.14790068833169223), 0.004479965998719326, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6174221114253805, 0.3 ,0.21994968446905483), 0.00345430964186835, material));
  world.add(make_shared<sphere>(glm::dvec3(0.658729490616092, 0.3 ,0.25307179304846594), 0.004139909296485974, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6866854837627497, 0.3 ,0.2777779552250113), 0.009169769529254131, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6494146946989986, 0.3 ,0.2760985848444503), 0.004139909296485974, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5966962535741703, 0.3 ,0.2711853763490228), 0.00345430964186835, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4944193094784798, 0.3 ,0.2724918773139758), 0.004479965998719326, material));
  world.add(make_shared<sphere>(glm::dvec3(0.32364053862416076, 0.3 ,0.1777710195219508), 0.004825882641050805, material));
  world.add(make_shared<sphere>(glm::dvec3(0.29426275559032067, 0.3 ,0.23358244066175654), 0.003217823773775999, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2704614699929244, 0.3 ,0.2769794381368735), 0.00388359400027659, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2588160902235901, 0.3 ,0.29465681052577836), 0.0032017843676430324, material));
  world.add(make_shared<sphere>(glm::dvec3(0.23869724643225876, 0.3 ,0.3282071122574695), 0.004772103750225276, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2185504878608805, 0.3 ,0.36662579264982537), 0.010746448881235595, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2580363269537469, 0.3 ,0.3491374358379728), 0.004726988392158296, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3113266815629454, 0.3 ,0.3229442127856908), 0.003804787337470569, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2928229171563774, 0.3 ,0.33239063109228656), 0.003148028063417162, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4139036683640497, 0.3 ,0.2866190647604974), 0.0046037128612365676, material));
  world.add(make_shared<sphere>(glm::dvec3(0.35630232180527877, 0.3 ,0.3055514208998233), 0.0031175078645608247, material));
  world.add(make_shared<sphere>(glm::dvec3(0.1634451942932018, 0.3 ,-1.4413835078201596), 0.010351779419351965, material));
  world.add(make_shared<sphere>(glm::dvec3(0.17292653838227723, 0.3 ,-1.3699386726120908), 0.01390431865414905, material));
  world.add(make_shared<sphere>(glm::dvec3(0.22437933405503718, 0.3 ,-1.422916539577253), 0.01087768361457494, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3258068703987045, 0.3 ,-1.497217989685037), 0.014520536539844597, material));
  world.add(make_shared<sphere>(glm::dvec3(0.43785610475343273, 0.3 ,-1.5479071346314546), 0.02855614925062206, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3129856535806206, 0.3 ,-1.589936033519336), 0.01675031337777217, material));
  world.add(make_shared<sphere>(glm::dvec3(0.11725253907641053, 0.3 ,-1.5443365482986438), 0.012296733323216855, material));
  world.add(make_shared<sphere>(glm::dvec3(0.05120287087560027, 0.3 ,-1.6153239718116168), 0.021064534389835902, material));
  world.add(make_shared<sphere>(glm::dvec3(0.15738986863644466, 0.3 ,-1.614729211226875), 0.014818240403903891, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.34240131256973655, 0.3 ,-1.4729767657067518), 0.01718174327022965, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.2799827011300167, 0.3 ,-1.5859065255521811), 0.02676825851001271, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.42472282114568904, 0.3 ,-1.5577975261623613), 0.02254115612563512, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6808435610204323, 0.3 ,-1.4513741553676385), 0.03406698489135133, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9210158045044592, 0.3 ,-1.2618885140092757), 0.07494736676097292, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6364396656208267, 0.3 ,-1.2671845614970927), 0.029251457933528315, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.3453565743730572, 0.3 ,-1.311954226173836), 0.015093130597517365, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.3022267892755651, 0.3 ,-1.2172060328092509), 0.019902846007786752, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.41166520641186444, 0.3 ,-1.2405418274879454), 0.017467343870525013, material));
  world.add(make_shared<sphere>(glm::dvec3(0.05179093071635277, 0.3 ,-1.1690615971753946), 0.008171634852261914, material));
  world.add(make_shared<sphere>(glm::dvec3(0.09978874375811586, 0.3 ,-1.2043745590997015), 0.012019852883289153, material));
  world.add(make_shared<sphere>(glm::dvec3(0.09495242310136087, 0.3 ,-1.1438326705630337), 0.008495879254093269, material));
  world.add(make_shared<sphere>(glm::dvec3(0.09769690197393655, 0.3 ,-1.0529098836035795), 0.00973759542277735, material));
  world.add(make_shared<sphere>(glm::dvec3(0.10937115464849312, 0.3 ,-0.9765003604267466), 0.016897397231229228, material));
  world.add(make_shared<sphere>(glm::dvec3(0.04583754137995122, 0.3 ,-1.0233330200345805), 0.010166780814625466, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.02491933968478821, 0.3 ,-1.134242631355258), 0.008684385903751991, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.08975676218544726, 0.3 ,-1.120522367071929), 0.013959628466804439, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.03349652579729934, 0.3 ,-1.0806478608090375), 0.009421201729789594, material));
  world.add(make_shared<sphere>(glm::dvec3(0.37585050361620176, 0.3 ,-0.6999755819672977), 0.0043160583079497215, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4029849129530636, 0.3 ,-0.7157533852037098), 0.006315042549748594, material));
  world.add(make_shared<sphere>(glm::dvec3(0.37177428340918195, 0.3 ,-0.7271049990802659), 0.004842022205629699, material));
  world.add(make_shared<sphere>(glm::dvec3(0.32032855382110137, 0.3 ,-0.7479083618370077), 0.00635510012012219, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2712441133044783, 0.3 ,-0.7702792538084051), 0.012550531108939444, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2933010818565116, 0.3 ,-0.7202554623980492), 0.0065351478110591815, material));
  world.add(make_shared<sphere>(glm::dvec3(0.34693013615737534, 0.3 ,-0.6670145435423804), 0.0044549870961026325, material));
  world.add(make_shared<sphere>(glm::dvec3(0.33436374208231445, 0.3 ,-0.636351701491739), 0.006812383038227066, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3182578485670935, 0.3 ,-0.6679955278120613), 0.0051291327851109075, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3998665765520043, 0.3 ,-0.5302121331333848), 0.004716689475404036, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3686186884468914, 0.3 ,-0.5453934520664696), 0.007075002966247133, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3777948842736404, 0.3 ,-0.5091459354381664), 0.00547914282246469, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3946664107236949, 0.3 ,-0.4480911029524667), 0.007316772389558767, material));
  world.add(make_shared<sphere>(glm::dvec3(0.412976324843929, 0.3 ,-0.38815097688221556), 0.014705477364465655, material));
  world.add(make_shared<sphere>(glm::dvec3(0.43814494067882126, 0.3 ,-0.44507476598264717), 0.00721124629400224, material));
  world.add(make_shared<sphere>(glm::dvec3(0.446449396711491, 0.3 ,-0.5257037048122508), 0.004643680151084822, material));
  world.add(make_shared<sphere>(glm::dvec3(0.47918185769204136, 0.3 ,-0.5342507627614104), 0.006817746555046723, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4638666172565743, 0.3 ,-0.5014744199346137), 0.005323576756464569, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5093579060188475, 0.3 ,-0.6796850388819673), 0.004126101052207632, material));
  world.add(make_shared<sphere>(glm::dvec3(0.48904539472108877, 0.3 ,-0.702104138799837), 0.006134264555252048, material));
  world.add(make_shared<sphere>(glm::dvec3(0.520952344934, 0.3 ,-0.7031308720095122), 0.004604222244585058, material));
  world.add(make_shared<sphere>(glm::dvec3(0.572704433424475, 0.3 ,-0.7063253186838074), 0.005835874211487959, material));
  world.add(make_shared<sphere>(glm::dvec3(0.621169316509239, 0.3 ,-0.7110306203190399), 0.011151019000338247, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5882742058962392, 0.3 ,-0.6746931238651679), 0.005916504145237264, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5267163545941663, 0.3 ,-0.6418836409831405), 0.004193442824691223, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5304799854249896, 0.3 ,-0.6110058287727134), 0.006377896311693545, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5526888512714897, 0.3 ,-0.6354558258415148), 0.0047401287857414005, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9711119091372619, 0.3 ,-1.1421817115494124), 0.0077759439949404915, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9310200085177663, 0.3 ,-1.1050139968721662), 0.01064734802071337, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9265500898930538, 0.3 ,-1.1618906536413864), 0.008479510399840037, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9071320081358284, 0.3 ,-1.2599990853364411), 0.011783007162911648, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8725030167608524, 0.3 ,-1.3564398769260777), 0.024379108487265325, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9674213606805661, 0.3 ,-1.3043921714959203), 0.013209974087047454, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0468614001295515, 0.3 ,-1.1757212730779893), 0.008824379856425472, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1146083131791213, 0.3 ,-1.1794689008109838), 0.014394048115843066, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0618152710158948, 0.3 ,-1.2320957146578597), 0.010696972385460383, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2445501622712936, 0.3 ,-0.9509893893610717), 0.009913949041762406, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2566338831495827, 0.3 ,-1.0248880212343723), 0.015619058574134028, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3102012622980048, 0.3 ,-0.9610090915020395), 0.012341113791714983, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3864887758441808, 0.3 ,-0.8385634336295442), 0.016848083109333965, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4402208717898604, 0.3 ,-0.7041000689303325), 0.03408003029048098, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3196087732007422, 0.3 ,-0.7700500625749529), 0.01510886004477894, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1932272585483483, 0.3 ,-0.8722583326599849), 0.008908264807335654, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1418755631890698, 0.3 ,-0.8365804757745936), 0.012158931247904705, material));
  world.add(make_shared<sphere>(glm::dvec3(1.20527222493106, 0.3 ,-0.8166930468556088), 0.01007559834719302, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9197785517620968, 0.3 ,-0.9286079142474133), 0.00605909313067401, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9030996496794713, 0.3 ,-0.9700390088726709), 0.009102298510168843, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8821873527112306, 0.3 ,-0.9289018912629086), 0.006477909550800259, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8463933352154235, 0.3 ,-0.8688875530955218), 0.007536092753665721, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8116637955573477, 0.3 ,-0.8195344776572915), 0.013301283968744986, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8714831968371396, 0.3 ,-0.8307866472566365), 0.007671091142478472, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9553777865795067, 0.3 ,-0.8786815318227625), 0.0062054298985988075, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9906664445451631, 0.3 ,-0.8483143428076318), 0.009649236332653131, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9425664291497954, 0.3 ,-0.8420191266377519), 0.006750208527177009, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5117613987494378, 0.3 ,0.3746751301202223), 0.0045745288101519755, material));
  world.add(make_shared<sphere>(glm::dvec3(1.479461379408646, 0.3 ,0.37305537169002073), 0.006332316117786002, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4991275567151585, 0.3 ,0.4001316798688292), 0.004903611254048803, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5263462232437468, 0.3 ,0.4495447475499211), 0.006485029130571462, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5451986085015874, 0.3 ,0.5011552191600654), 0.012762906213469384, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5672925116971337, 0.3 ,0.44779242004586656), 0.007192500349033051, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5589338700030302, 0.3 ,0.36278458570432176), 0.005172706026997607, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5925489686489973, 0.3 ,0.3411889586902109), 0.008512582828389823, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5852531655756135, 0.3 ,0.383932614796275), 0.006116791729897536, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5798001638984114, 0.3 ,0.17530699897812424), 0.0067173613107351475, material));
  world.add(make_shared<sphere>(glm::dvec3(1.613082542302978, 0.3 ,0.2123395805822249), 0.010201547345764122, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6211796853410503, 0.3 ,0.15735701186040135), 0.008401245960750354, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6238658240548656, 0.3 ,0.05527453658902581), 0.012393529270939323, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6089935889297369, 0.3 ,-0.05502091104567347), 0.027265764396066504, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5547568270538683, 0.3 ,0.03730820560493192), 0.011426003706244954, material));
  world.add(make_shared<sphere>(glm::dvec3(1.520027602717938, 0.3 ,0.15042465423972728), 0.006240042961882734, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4760210308885742, 0.3 ,0.15165030934027235), 0.008602589317627123, material));
  world.add(make_shared<sphere>(glm::dvec3(1.504020106496795, 0.3 ,0.11325490358304513), 0.007285991021590574, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4012965434900426, 0.3 ,0.2961585841499655), 0.003920935130384311, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4115295325787462, 0.3 ,0.3228139348378382), 0.005751676195557728, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3838360139082209, 0.3 ,0.3129639463253387), 0.004160239310161829, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3398636176128762, 0.3 ,0.30172607164245996), 0.004949806713351403, material));
  world.add(make_shared<sphere>(glm::dvec3(1.300299827163876, 0.3 ,0.2958990196621117), 0.008887779268439535, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3334433501159793, 0.3 ,0.2720814640899934), 0.005162812260408753, material));
  world.add(make_shared<sphere>(glm::dvec3(1.39624086241639, 0.3 ,0.25615322677790836), 0.004146810533250326, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4001652371944813, 0.3 ,0.22492672638074535), 0.006594777249195802, material));
  world.add(make_shared<sphere>(glm::dvec3(1.373114742686918, 0.3 ,0.2439173147964953), 0.004584136918830466, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1090465246516388, 0.3 ,0.4183082335632335), 0.004015762233278774, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1208908712725254, 0.3 ,0.4009927355255683), 0.0030377413693477647, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1417087053164665, 0.3 ,0.37359210320556707), 0.0038957912224130563, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1629956791225617, 0.3 ,0.3488050679973809), 0.007518161831618453, material));
  world.add(make_shared<sphere>(glm::dvec3(1.13005097173343, 0.3 ,0.35288387408345573), 0.004026541990115184, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0718027066311775, 0.3 ,0.36221897120038543), 0.004409336113999103, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0942320598375366, 0.3 ,0.35829908864612076), 0.003257703231080737, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9909743829984007, 0.3 ,0.38324349050896095), 0.0032678338623347643, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0073436861918212, 0.3 ,0.36586983632224196), 0.004822933312008134, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9816584497344528, 0.3 ,0.3642264155003376), 0.0038093743376481884, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9369159332487834, 0.3 ,0.36196924204423647), 0.005263002271780263, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8910419025799755, 0.3 ,0.36044419690104385), 0.010948680615390062, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9250741781372779, 0.3 ,0.3912428441584049), 0.005263002271780263, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9787200060146451, 0.3 ,0.4135371211913697), 0.0032678338623347643, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9784060863197724, 0.3 ,0.4374054977859981), 0.004822933312008134, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9588022037085638, 0.3 ,0.4207285678996326), 0.0038093743376481884, material));
  world.add(make_shared<sphere>(glm::dvec3(1.087963772926925, 0.3 ,0.4704261907114448), 0.004015762233278774, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0844379748403523, 0.3 ,0.4911067073157475), 0.0030377413693477647, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0803499935634608, 0.3 ,0.5252748982964937), 0.0038957912224130563, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0784163585168542, 0.3 ,0.5578907445025905), 0.007518161831618453, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0575732159113564, 0.3 ,0.532053681775372), 0.004026541990115184, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0221976753486874, 0.3 ,0.484845890516897), 0.004409336113999103, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0355934016780837, 0.3 ,0.5032577312886064), 0.003257703231080737, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3470783615839665, 0.3 ,0.7817824938125177), 0.0045745288101519755, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3227365554934427, 0.3 ,0.7604895056934433), 0.006332316117786002, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3556969275342308, 0.3 ,0.7547016849137538), 0.004903611254048803, material));
  world.add(make_shared<sphere>(glm::dvec3(1.40961569889346, 0.3 ,0.7381103269114135), 0.006485029130571462, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4590489915606684, 0.3 ,0.7141227721004355), 0.012762906213469384, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4378275054145377, 0.3 ,0.7678384812874703), 0.007192500349033051, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3727164530311167, 0.3 ,0.823126361043645), 0.005172706026997607, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3818625436463492, 0.3 ,0.8620197408089549), 0.008512582828389823, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4063370074761106, 0.3 ,0.8262251951344424), 0.006116791729897536, material));
  world.add(make_shared<sphere>(glm::dvec3(1.257366820983124, 0.3 ,0.9723835556173073), 0.0067173613107351475, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3070361219300541, 0.3 ,0.9689065804991315), 0.010201547345764122, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2746282894600975, 0.3 ,1.0140549911381371), 0.008401245960750354, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2055842111606632, 0.3 ,1.0892943581643313), 0.012393529270939323, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1182098298005405, 0.3 ,1.1582290129360184), 0.027265764396066504, material));
  world.add(make_shared<sphere>(glm::dvec3(1.14342069362905, 0.3 ,1.0541583424025713), 0.011426003706244954, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1971053794405067, 0.3 ,0.9487097554796124), 0.006240042961882734, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1663278154539984, 0.3 ,0.9172324279301716), 0.008602589317627123, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1597570307266407, 0.3 ,0.9642960041462187), 0.007285991021590574, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2130916572315962, 0.3 ,0.7614135150612675), 0.003920935130384311, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2389792467120144, 0.3 ,0.7493696578354321), 0.005751676195557728, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2122261423640452, 0.3 ,0.7371949028975371), 0.004160239310161829, material));
  world.add(make_shared<sphere>(glm::dvec3(1.172807641037266, 0.3 ,0.7146994985559023), 0.004949806713351403, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1403198003319646, 0.3 ,0.6913802306475607), 0.008887779268439535, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1475821087412643, 0.3 ,0.7315427497876215), 0.005162812260408753, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1816434173206853, 0.3 ,0.7866523093290276), 0.004146810533250326, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1627532562234322, 0.3 ,0.8118248510793709), 0.006594777249195802, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1565142732721783, 0.3 ,0.779368005989096), 0.004584136918830466, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8846724719161847, 0.3 ,1.1496327089932696), 0.010351779419351965, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8281844047164545, 0.3 ,1.1048738145958175), 0.01390431865414905, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8280365556550885, 0.3 ,1.178725170110637), 0.01087768361457494, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.806794979709174, 0.3 ,1.3026487193988958), 0.014520536539844597, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.761502163772694, 0.3 ,1.4169858575449235), 0.02855614925062206, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8804741745856466, 0.3 ,1.3603756238327045), 0.01675031337777217, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9894534600131064, 0.3 ,1.1915139037371465), 0.012296733323216855, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0862819861755384, 0.3 ,1.196613853507344), 0.021064534389835902, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0095465631709868, 0.3 ,1.2700148554754866), 0.014818240403903891, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2702154491621376, 0.3 ,0.820641166327426), 0.01718174327022965, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3038685891380029, 0.3 ,0.9452071323156281), 0.02676825851001271, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3883572455165902, 0.3 ,0.824370527215232), 0.02254115612563512, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4984511984128641, 0.3 ,0.5698060191215659), 0.03406698489135133, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5393315802824858, 0.3 ,0.2666289929481854), 0.07494736676097292, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.338474656025506, 0.3 ,0.4682923830787085), 0.029251457933528315, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.160385626638995, 0.3 ,0.702851515277384), 0.015093130597517365, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0635106490734083, 0.3 ,0.6647380369517866), 0.019902846007786752, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1583941568768088, 0.3 ,0.6054215434149388), 0.017467343870525013, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7755870980751662, 0.3 ,0.8762716312845567), 0.008171634852261914, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7656406638387033, 0.3 ,0.9350241953361735), 0.012019852883289153, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7270238947321631, 0.3 ,0.8881471710187807), 0.008495879254093269, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6618355410026967, 0.3 ,0.8247045678975473), 0.00973759542277735, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6003195290631345, 0.3 ,0.7779019645226064), 0.016897397231229228, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.678545591662113, 0.3 ,0.7673900117468109), 0.010166780814625466, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8065140710224673, 0.3 ,0.7979112566675548), 0.008684385903751991, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8435766993928869, 0.3 ,0.7429703922148587), 0.013959628466804439, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7754161620182297, 0.3 ,0.753426567087039), 0.009421201729789594, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.21652849914989747, 0.3 ,0.7644245060664299), 0.0043160583079497215, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.20799545373511297, 0.3 ,0.7946305051556264), 0.006315042549748594, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.23832051450016, 0.3 ,0.7810897066664664), 0.004842022205629699, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.28976105771062877, 0.3 ,0.7602735228411253), 0.00635510012012219, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.3405942782563197, 0.3 ,0.7422257308050062), 0.012550531108939444, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.2899608602805203, 0.3 ,0.7216066485543289), 0.0065351478110591815, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.21439823795155633, 0.3 ,0.7206263360677954), 0.0044549870961026325, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.202111422178067, 0.3 ,0.6898503990256737), 0.006812383038227066, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.23568849222488436, 0.3 ,0.7013964770258205), 0.0051291327851109075, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.08123574993920746, 0.3 ,0.6591046488207246), 0.004716689475404036, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.11425026399947552, 0.3 ,0.6482905461329349), 0.007075002966247133, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.08245311281339363, 0.3 ,0.6286175644570575), 0.00547914282246469, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.027877194773324065, 0.3 ,0.5964646463205125), 0.007316772389558767, material));
  world.add(make_shared<sphere>(glm::dvec3(0.026957544026705804, 0.3 ,0.5661129892135197), 0.014705477364465655, material));
  world.add(make_shared<sphere>(glm::dvec3(0.005470163038686859, 0.3 ,0.6245259111304253), 0.00721124629400224, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.04461977926572902, 0.3 ,0.6882517885016066), 0.004643680151084822, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.027035824020178123, 0.3 ,0.7171528389903346), 0.006817746555046723, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.015255290825237022, 0.3 ,0.6829466366822916), 0.005323576756464569, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.10646267602314186, 0.3 ,0.8426641840720897), 0.004126101052207632, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.13664958991462006, 0.3 ,0.8446552606797257), 0.006134264555252048, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.1144303248187381, 0.3 ,0.8675771260395073), 0.004604222244585058, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.07945450970930434, 0.3 ,0.9058547371210728), 0.005835874211487959, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.0478918235110557, 0.3 ,0.9429327844786299), 0.011151019000338247, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.046270863680457186, 0.3 ,0.8939442711310681), 0.005916504145237264, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.0677041658058144, 0.3 ,0.8275632137131774), 0.004193442824691223, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.04353068262742965, 0.3 ,0.807986520556327), 0.006377896311693545, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.04456737573192693, 0.3 ,0.8410010831955521), 0.0047401287857414005, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.0961364041683207, 0.3 ,1.4961267306146744), 0.0077759439949404915, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.09911091248625198, 0.3 ,1.4415377957479891), 0.01064734802071337, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.14186822048679104, 0.3 ,1.4793100987000503), 0.008479510399840037, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.22403667950368994, 0.3 ,1.5363247513042864), 0.011783007162911648, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.31597852199333265, 0.3 ,1.5815651196238927), 0.024379108487265325, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.2115688265884194, 0.3 ,1.6101495762123736), 0.013209974087047454, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.06501046178005787, 0.3 ,1.5728995336347722), 0.008824379856425472, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.018922975943519882, 0.3 ,1.6226954430113263), 0.014394048115843066, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.09345774661382678, 0.3 ,1.6238156205181342), 0.010696972385460383, material));
  world.add(make_shared<sphere>(glm::dvec3(0.23332736001152854, 0.3 ,1.5488202827174316), 0.009913949041762406, material));
  world.add(make_shared<sphere>(glm::dvec3(0.19063313546493488, 0.3 ,1.6103363561728707), 0.015619058574134028, material));
  world.add(make_shared<sphere>(glm::dvec3(0.27354770379394633, 0.3 ,1.6016670925713392), 0.012341113791714983, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4135119762801448, 0.3 ,1.5666995893391187), 0.016848083109333965, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5456200766647351, 0.3 ,1.5074122855235133), 0.03408003029048098, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4130771705140063, 0.3 ,1.4709560375416413), 0.01510886004477894, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2511782551726035, 0.3 ,1.4565491318750758), 0.008908264807335654, material));
  world.add(make_shared<sphere>(glm::dvec3(0.23907491803214564, 0.3 ,1.3952024504793306), 0.012158931247904705, material));
  world.add(make_shared<sphere>(glm::dvec3(0.29846837368368817, 0.3 ,1.4249860697154848), 0.01007559834719302, material));
  world.add(make_shared<sphere>(glm::dvec3(0.015458902009001019, 0.3 ,1.3069300918691837), 0.00605909313067401, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.025334798357750654, 0.3 ,1.3251123740943769), 0.009102298510168843, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.01176416529920521, 0.3 ,1.2810054072057135), 0.006477909550800259, material));
  world.add(make_shared<sphere>(glm::dvec3(0.004234969993279325, 0.3 ,1.212983644922953), 0.007536092753665721, material));
  world.add(make_shared<sphere>(glm::dvec3(0.013586757432649033, 0.3 ,1.1533647632514357), 0.013301283968744986, material));
  world.add(make_shared<sphere>(glm::dvec3(0.04875867180632365, 0.3 ,1.2030428120200425), 0.007671091142478472, material));
  world.add(make_shared<sphere>(glm::dvec3(0.07575809845312564, 0.3 ,1.2957965349447131), 0.0062054298985988075, material));
  world.add(make_shared<sphere>(glm::dvec3(0.12223517460638089, 0.3 ,1.298505213947888), 0.009649236332653131, material));
  world.add(make_shared<sphere>(glm::dvec3(0.09204015472549198, 0.3 ,1.2605380965691242), 0.006750208527177009, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3520401614469536, 0.3 ,0.10412894737420225), 0.0032259038904709383, material));
  world.add(make_shared<sphere>(glm::dvec3(0.40294390981663997, 0.3 ,-0.10097226270226589), 0.003178022843086194, material));
  world.add(make_shared<sphere>(glm::dvec3(0.41126333516399305, 0.3 ,-0.13014689624471226), 0.007853518644722196, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4219317585578407, 0.3 ,-0.10184371608246781), 0.0031579507637570716, material));
  world.add(make_shared<sphere>(glm::dvec3(0.502094031839675, 0.3 ,0.08729023645130707), 0.0030675727714665145, material));
  world.add(make_shared<sphere>(glm::dvec3(0.541303663589178, 0.3 ,0.1412981073592346), 0.003000084274690122, material));
  world.add(make_shared<sphere>(glm::dvec3(0.7013389836454732, 0.3 ,0.2837055877883337), 0.0066372506396059384, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4873021466447559, 0.3 ,0.2747934301139328), 0.003000084274690122, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3254264543505684, 0.3 ,0.16991979214227532), 0.0032259038904709383, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2194130906284124, 0.3 ,0.35272806516412164), 0.003178022843086194, material));
  world.add(make_shared<sphere>(glm::dvec3(0.20510847074003502, 0.3 ,0.3794815683047435), 0.007853518644722196, material));
  world.add(make_shared<sphere>(glm::dvec3(0.23245471273241636, 0.3 ,0.366556077447488), 0.0031579507637570716, material));
  world.add(make_shared<sphere>(glm::dvec3(0.42157024658867936, 0.3 ,0.28635036123585805), 0.0030675727714665145, material));
  world.add(make_shared<sphere>(glm::dvec3(0.1773597961242328, 0.3 ,-1.4409926762150378), 0.003568310144285815, material));
  world.add(make_shared<sphere>(glm::dvec3(0.1549081163954209, 0.3 ,-1.4545349542511001), 0.005327577782353713, material));
  world.add(make_shared<sphere>(glm::dvec3(0.1595242368434684, 0.3 ,-1.4277413146620208), 0.003842703363989884, material));
  world.add(make_shared<sphere>(glm::dvec3(0.1639752525391197, 0.3 ,-1.3860929272686524), 0.004564180520254724, material));
  world.add(make_shared<sphere>(glm::dvec3(0.16521708442914962, 0.3 ,-1.3492176038682997), 0.008204466254576858, material));
  world.add(make_shared<sphere>(glm::dvec3(0.19011110922600138, 0.3 ,-1.3769713000427837), 0.004663592473974677, material));
  world.add(make_shared<sphere>(glm::dvec3(0.21202378207586303, 0.3 ,-1.4305965679271773), 0.003670254389338569, material));
  world.add(make_shared<sphere>(glm::dvec3(0.23954065470493557, 0.3 ,-1.429636612906455), 0.005706194984802537, material));
  world.add(make_shared<sphere>(glm::dvec3(0.21961481530018334, 0.3 ,-1.408784555759904), 0.004035854046864424, material));
  world.add(make_shared<sphere>(glm::dvec3(0.31995038900638606, 0.3 ,-1.5158747004948196), 0.005033778394164784, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3113700728688429, 0.3 ,-1.4812650329391124), 0.006994991616712024, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3460729463513442, 0.3 ,-1.4969080098576393), 0.005747909922860627, material));
  world.add(make_shared<sphere>(glm::dvec3(0.411426513550177, 0.3 ,-1.521924509151352), 0.008506232189465085, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4852088351382121, 0.3 ,-1.5437670731878195), 0.018977219908850373, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4116063719651034, 0.3 ,-1.5750809654393534), 0.009225665849171305, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3125056690853004, 0.3 ,-1.5677377095461074), 0.00545319923478931, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2911689432484432, 0.3 ,-1.6025248669390173), 0.008437929446740513, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3357357979538882, 0.3 ,-1.5955724411041914), 0.006687650686265683, material));
  world.add(make_shared<sphere>(glm::dvec3(0.1283413608808357, 0.3 ,-1.5567153588306262), 0.004322439917261156, material));
  world.add(make_shared<sphere>(glm::dvec3(0.12218810026040006, 0.3 ,-1.5267047659493442), 0.006012813722354153, material));
  world.add(make_shared<sphere>(glm::dvec3(0.10173806749593095, 0.3 ,-1.5513557676477512), 0.004731721353951997, material));
  world.add(make_shared<sphere>(glm::dvec3(0.06235600601822411, 0.3 ,-1.590166075356201), 0.00645477115320161, material));
  world.add(make_shared<sphere>(glm::dvec3(0.018093580282974475, 0.3 ,-1.6239492342526487), 0.013149794125036505, material));
  world.add(make_shared<sphere>(glm::dvec3(0.07617015040167818, 0.3 ,-1.6283313821722092), 0.0070878681936411125, material));
  world.add(make_shared<sphere>(glm::dvec3(0.1512431297332404, 0.3 ,-1.596097667000666), 0.004801057223619916, material));
  world.add(make_shared<sphere>(glm::dvec3(0.17941066091489533, 0.3 ,-1.6195654610267758), 0.007727371246652624, material));
  world.add(make_shared<sphere>(glm::dvec3(0.13986356770083985, 0.3 ,-1.6254609156151918), 0.005732689102169598, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.36236443561125353, 0.3 ,-1.4850983362013948), 0.006173315128912512, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.3409684009931475, 0.3 ,-1.4474051562180246), 0.00842998153366245, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.3246567167685754, 0.3 ,-1.4885876739883783), 0.006452366349638557, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.28720911417741823, 0.3 ,-1.5515740180268527), 0.00831652620513706, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.24106837708938944, 0.3 ,-1.6033154050331455), 0.01586264225834634, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.31435367230493144, 0.3 ,-1.5971600476920078), 0.009398099062438207, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.40949210961183047, 0.3 ,-1.5322543653634997), 0.007198172001007833, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.45949012647092996, 0.3 ,-1.5586451444975433), 0.01223648002779916, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.40158734763624704, 0.3 ,-1.5784461835551007), 0.00846879689962462, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6661262386111686, 0.3 ,-1.4087760800849696), 0.011001802497329708, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6448966339876403, 0.3 ,-1.4868986456478324), 0.01647182171078829, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7291634077655604, 0.3 ,-1.4498980638845589), 0.014275402674211546, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8820589988988669, 0.3 ,-1.3518207528147177), 0.023059981328601376, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0340932954680322, 0.3 ,-1.1968197595751542), 0.05551512503734008, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8303891889117327, 0.3 ,-1.2311573016096928), 0.020747935471373106, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6417551298100033, 0.3 ,-1.306181726306901), 0.010106298897238594, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.5961876818972378, 0.3 ,-1.2525227486869472), 0.013587670775676332, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6728473170666913, 0.3 ,-1.2476678857963515), 0.012057351226401135, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.36296126269345375, 0.3 ,-1.3016094994897376), 0.005325939435836308, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.3432030417193753, 0.3 ,-1.3346436265224644), 0.00769824038078963, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.330653204907508, 0.3 ,-1.2974897250777535), 0.00553236007783416, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.3046645184581796, 0.3 ,-1.2434866480281057), 0.006490586126918097, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.27588144267563663, 0.3 ,-1.2001760736805902), 0.011467471099220887, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.32830718082407784, 0.3 ,-1.2110530939591444), 0.006893524638569055, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.4011153210737868, 0.3 ,-1.261267236797795), 0.005788680546975699, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.4383190791041839, 0.3 ,-1.236826519406982), 0.009444223226818885, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.3929856036125926, 0.3 ,-1.2257172377464778), 0.006380004446245755, material));
  world.add(make_shared<sphere>(glm::dvec3(0.03978905380944753, 0.3 ,-1.1662647790564904), 0.0041518078841951, material));
  world.add(make_shared<sphere>(glm::dvec3(0.05719231795198054, 0.3 ,-1.1789495826441068), 0.0030954517586886244, material));
  world.add(make_shared<sphere>(glm::dvec3(0.08438096632996062, 0.3 ,-1.2004510476847363), 0.003879629721466879, material));
  world.add(make_shared<sphere>(glm::dvec3(0.10867382608432452, 0.3 ,-1.2215665008242822), 0.0073323446199631, material));
  world.add(make_shared<sphere>(glm::dvec3(0.10505572282264541, 0.3 ,-1.189296952459702), 0.00395122380104112, material));
  world.add(make_shared<sphere>(glm::dvec3(0.09844793179857703, 0.3 ,-1.1314422197377134), 0.004378197516961052, material));
  world.add(make_shared<sphere>(glm::dvec3(0.10102583671364218, 0.3 ,-1.1538509273774957), 0.0032195730421845374, material));
  world.add(make_shared<sphere>(glm::dvec3(0.08535529112344276, 0.3 ,-1.0486638153479801), 0.0033140119118094022, material));
  world.add(make_shared<sphere>(glm::dvec3(0.10070469154037764, 0.3 ,-1.0671552065589394), 0.004821800999413032, material));
  world.add(make_shared<sphere>(glm::dvec3(0.10557168847600695, 0.3 ,-1.0418878796148845), 0.0038085049156966113, material));
  world.add(make_shared<sphere>(glm::dvec3(0.11463572169995506, 0.3 ,-0.9980251617779365), 0.005261861317908158, material));
  world.add(make_shared<sphere>(glm::dvec3(0.12469261480658078, 0.3 ,-0.9532510181201097), 0.010946436180624275, material));
  world.add(make_shared<sphere>(glm::dvec3(0.08756455410847452, 0.3 ,-0.9810789752791025), 0.00538469291036548, material));
  world.add(make_shared<sphere>(glm::dvec3(0.05618748295563114, 0.3 ,-1.032097098839262), 0.0033953122360305807, material));
  world.add(make_shared<sphere>(glm::dvec3(0.031422800367551185, 0.3 ,-1.0283814615033453), 0.005106448042368384, material));
  world.add(make_shared<sphere>(glm::dvec3(0.0517440201838153, 0.3 ,-1.0104739546442454), 0.0039839101428300406, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.014330707894083416, 0.3 ,-1.141815906564879), 0.004333817528356983, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.0366321908028554, 0.3 ,-1.1369356690454189), 0.003334072121911528, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.07440764081485973, 0.3 ,-1.1305912711814048), 0.004397341784706102, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.11159697452070189, 0.3 ,-1.1266278767248303), 0.008717940251439554, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.08061669755121093, 0.3 ,-1.1043939025072538), 0.004578660308916098, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.0289771819003406, 0.3 ,-1.092357772288855), 0.003130550981451086, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.024844415497114247, 0.3 ,-1.0693145113868163), 0.004837263186628701, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.04645049563231762, 0.3 ,-1.0821901599561419), 0.003624258060716731, material));
  world.add(make_shared<sphere>(glm::dvec3(0.41308898103266134, 0.3 ,-0.7157533852037098), 0.003789025529849156, material));
  world.add(make_shared<sphere>(glm::dvec3(0.32971217659553786, 0.3 ,-0.7468255797107317), 0.003090787530379588, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2875925770087472, 0.3 ,-0.7698581311689239), 0.003803355577939535, material));
  world.add(make_shared<sphere>(glm::dvec3(0.25681647921069783, 0.3 ,-0.7857321362670888), 0.008590618382654333, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2710504907784711, 0.3 ,-0.753862746594206), 0.0038671178943871687, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2947098594037246, 0.3 ,-0.710617412396511), 0.0032053173734010523, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3360267482128477, 0.3 ,-0.6255383819326443), 0.004128068016336034, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3625388929062884, 0.3 ,-0.5549493171910558), 0.004251005690593096, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3888260654917136, 0.3 ,-0.4572676634427137), 0.0035606765236693505, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4003539082180554, 0.3 ,-0.4025901423495269), 0.00447302364237859, material));
  world.add(make_shared<sphere>(glm::dvec3(0.41185817005248937, 0.3 ,-0.36323772116314496), 0.010232858198707463, material));
  world.add(make_shared<sphere>(glm::dvec3(0.42703340578755766, 0.3 ,-0.4011391895932384), 0.004433362571186285, material));
  world.add(make_shared<sphere>(glm::dvec3(0.44511671967657096, 0.3 ,-0.4531990145154362), 0.0034943184559764447, material));
  world.add(make_shared<sphere>(glm::dvec3(0.48677557080860956, 0.3 ,-0.5420639241874984), 0.004077663963463019, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4796911562301506, 0.3 ,-0.7051546165215001), 0.0037048000382809607, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6073023712517759, 0.3 ,-0.715485145447524), 0.0034138347542924724, material));
  world.add(make_shared<sphere>(glm::dvec3(0.637763826674718, 0.3 ,-0.7196587590567891), 0.0075525246668398565, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6166363870523274, 0.3 ,-0.6971602415508021), 0.0034412685734359284, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5264372044993125, 0.3 ,-0.6015865631573634), 0.003872305751950424, material));
  world.add(make_shared<sphere>(glm::dvec3(0.982397021923021, 0.3 ,-1.1454501333905784), 0.00397294326807771, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9440904342801467, 0.3 ,-1.1103412699872497), 0.0034670371395613304, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9258867360797439, 0.3 ,-1.0888830329559924), 0.006280690341360884, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9241323439733226, 0.3 ,-1.1174861040173663), 0.0036002264928007787, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9210623610603591, 0.3 ,-1.1736301655251022), 0.004479320836389914, material));
  world.add(make_shared<sphere>(glm::dvec3(0.922234997570259, 0.3 ,-1.1510947275912924), 0.003146840748880045, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9211424070282671, 0.3 ,-1.2673832426148668), 0.004054197635845192, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9065890856853646, 0.3 ,-1.2425735211051534), 0.005651012842983555, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8952033727603986, 0.3 ,-1.2713997295551287), 0.004717508905413467, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8718822774205027, 0.3 ,-1.32486714505324), 0.007199724854750059, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8424305059608422, 0.3 ,-1.3843640519895721), 0.016658867325308885, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9045723448517217, 0.3 ,-1.3553563285377312), 0.007708519678582261, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9549424830404082, 0.3 ,-1.292077750740448), 0.004321921010198787, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9863018915096041, 0.3 ,-1.298539607787884), 0.006556840181895375, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9585473396566632, 0.3 ,-1.3206732972071842), 0.005332498875280116, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0472320536451956, 0.3 ,-1.187651760529307), 0.003111863893377485, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0356256371449826, 0.3 ,-1.1688576179697978), 0.004341945799945727, material));
  world.add(make_shared<sphere>(glm::dvec3(1.058389459485956, 0.3 ,-1.1717665382274765), 0.003363158051726136, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0971253547358262, 0.3 ,-1.1724127253023724), 0.004459159800538187, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1347355724416968, 0.3 ,-1.1679025631015698), 0.00881988592022961, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1088419029589764, 0.3 ,-1.1978726062706793), 0.004891901730462695, material));
  world.add(make_shared<sphere>(glm::dvec3(1.05535650593606, 0.3 ,-1.2194880849152838), 0.0034687600023261653, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0532880400590927, 0.3 ,-1.2460267514997074), 0.005636657195240972, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0761351567693809, 0.3 ,-1.2284044548871602), 0.004091013504702878, material));
  world.add(make_shared<sphere>(glm::dvec3(1.257928800486936, 0.3 ,-0.9497575372621063), 0.0035212815144569504, material));
  world.add(make_shared<sphere>(glm::dvec3(1.235204134572443, 0.3 ,-0.9395124531272998), 0.004887006976743385, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2417533897272954, 0.3 ,-0.964359527186148), 0.003745572257477994, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2471902238082566, 0.3 ,-1.0067114223364244), 0.004864384721657157, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2459663772163934, 0.3 ,-1.0475197457306404), 0.009400746311388559, material));
  world.add(make_shared<sphere>(glm::dvec3(1.276113140697273, 0.3 ,-1.0170340939874967), 0.005383932827294795, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2950257455157406, 0.3 ,-0.9549879263803356), 0.003985267896571111, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3254441067308287, 0.3 ,-0.9497805873544238), 0.006590965116748325, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3073265196012072, 0.3 ,-0.9777766976413578), 0.004671139475154205, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3690332195467834, 0.3 ,-0.8245960130869292), 0.0055077949156038565, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3814823098070663, 0.3 ,-0.8631457175620325), 0.00823883351105301, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4060713830644054, 0.3 ,-0.82511095054151), 0.006910027227463393, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4441632006670555, 0.3 ,-0.7485655058828764), 0.010559829032288208, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4734785761321119, 0.3 ,-0.656258234301178), 0.02418587774157503, material));
  world.add(make_shared<sphere>(glm::dvec3(1.396684093203182, 0.3 ,-0.7099590615705251), 0.009849218331175769, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3318273888624255, 0.3 ,-0.7862505069619632), 0.005182738389660756, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2975767222482264, 0.3 ,-0.7733131510954989), 0.007163522312463025, material));
  world.add(make_shared<sphere>(glm::dvec3(1.331435757662907, 0.3 ,-0.752400031781987), 0.006137343109218608, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1988714469229165, 0.3 ,-0.8616356022083156), 0.0031208359344668214, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1993111975360877, 0.3 ,-0.8842447527627904), 0.004533780442084801, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1813286843856599, 0.3 ,-0.8695450622205994), 0.003295746974953463, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1512022969201139, 0.3 ,-0.8497102190606294), 0.003946289050092036, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1226376802594182, 0.3 ,-0.8353926360143176), 0.007115588276873885, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1539015758010058, 0.3 ,-0.8255498121573668), 0.004159785588258071, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2059501712479297, 0.3 ,-0.8300987836300533), 0.003347269814055119, material));
  world.add(make_shared<sphere>(glm::dvec3(1.217596132794318, 0.3 ,-0.8073663769798392), 0.005379675056848634, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1916555133287958, 0.3 ,-0.8144719435041272), 0.003721072807733579, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9263425847709775, 0.3 ,-0.922278552317799), 0.0030594238418234663, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9045275271265699, 0.3 ,-0.9846359908716626), 0.005564354737345602, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8936277716323725, 0.3 ,-0.962492562940586), 0.0030082473051525507, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8751106305115827, 0.3 ,-0.9220805621226784), 0.0033511559353149012, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8495031059836095, 0.3 ,-0.8797165064438386), 0.003730535173566082, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8152985410372299, 0.3 ,-0.8365957255853991), 0.00414284270953488, material));
  world.add(make_shared<sphere>(glm::dvec3(0.7929519625370184, 0.3 ,-0.8079251610103697), 0.008719363796231965, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8286771563043004, 0.3 ,-0.8155025162783984), 0.004183313723705624, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8828881733231747, 0.3 ,-0.8293885497564841), 0.003819259821131959, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8632141768356195, 0.3 ,-0.8240083437776577), 0.003021059709369768, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9514421967874606, 0.3 ,-0.8871261986752985), 0.003111289763470008, material));
  world.add(make_shared<sphere>(glm::dvec3(0.98467492042966, 0.3 ,-0.859523230659986), 0.0030605051325896166, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0058864911648353, 0.3 ,-0.8448913066413875), 0.00595098788690298, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9798400144494458, 0.3 ,-0.841417460003467), 0.0031873746309867813, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9333148951499061, 0.3 ,-0.8376348072695516), 0.0034876202305963, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4708497879016909, 0.3 ,0.36779076683611106), 0.003761026864123577, material));
  world.add(make_shared<sphere>(glm::dvec3(1.519942780150449, 0.3 ,0.44236528875064424), 0.0031351949884195806, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5342771261613612, 0.3 ,0.4886724227125661), 0.003823201939366353, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5425985106409676, 0.3 ,0.5223284403881334), 0.00856936525624314, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5578703329322514, 0.3 ,0.4900922685784412), 0.004058552570422048, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5735206481753812, 0.3 ,0.4389899497365208), 0.00359050329274501, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5984806133500546, 0.3 ,0.3287571083581045), 0.005261861317908156, material));
  world.add(make_shared<sphere>(glm::dvec3(1.58598327921912, 0.3 ,0.39321825600987065), 0.003197509031837793, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5702177212197759, 0.3 ,0.17229798363327387), 0.0033264119361517586, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6014822688756243, 0.3 ,0.20562349064190105), 0.003202638853922936, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6150594885069394, 0.3 ,0.22847959645615212), 0.00605909313067401, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6212140860723374, 0.3 ,0.20126094546609524), 0.003541020103928491, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6261851749779161, 0.3 ,0.14544062588103285), 0.004523736875372135, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6253779167267313, 0.3 ,0.1681188327031088), 0.003150461039440207, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6075772216464657, 0.3 ,0.052865117588199284), 0.0040723101653140316, material));
  world.add(make_shared<sphere>(glm::dvec3(1.629603372570616, 0.3 ,0.07272352387288106), 0.005974557733502101, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6315852146257623, 0.3 ,0.03953658190972459), 0.0051356523492560955, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6287602055554147, 0.3 ,-0.025526648820538844), 0.008239596284139212, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6139841107366548, 0.3 ,-0.10201720501512218), 0.01999475776321732, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5813190825467704, 0.3 ,-0.03348578171064981), 0.007800460080159464, material));
  world.add(make_shared<sphere>(glm::dvec3(1.569066825642289, 0.3 ,0.04277264767676825), 0.0038918351346962318, material));
  world.add(make_shared<sphere>(glm::dvec3(1.542136069774501, 0.3 ,0.04841805097264035), 0.005388043349686989, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5551790239236336, 0.3 ,0.021191505244239572), 0.00469622569024927, material));
  world.add(make_shared<sphere>(glm::dvec3(1.528338200873797, 0.3 ,0.15481486798616084), 0.0031588941294876088, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4647549691609378, 0.3 ,0.15930869002000464), 0.005020000064961365, material));
  world.add(make_shared<sphere>(glm::dvec3(1.50738009584588, 0.3 ,0.10256637070618357), 0.00391821637945787, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4184415068985183, 0.3 ,0.3289512949638322), 0.0034918392781858373, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2861400557788776, 0.3 ,0.29993471614742656), 0.005835874211487957, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4064148862006256, 0.3 ,0.21626460465041297), 0.004086536601220547, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1742967354546052, 0.3 ,0.34321136497657473), 0.0050914927118255815, material));
  world.add(make_shared<sphere>(glm::dvec3(0.904255816364678, 0.3 ,0.35512888234505174), 0.003294215380112249, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8737460945553573, 0.3 ,0.35344769806621107), 0.007708649610830622, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8968438317594255, 0.3 ,0.37345179868366857), 0.003294215380112249, material));
  world.add(make_shared<sphere>(glm::dvec3(1.082649866641745, 0.3 ,0.5697684882555718), 0.0050914927118255815, material));
  world.add(make_shared<sphere>(glm::dvec3(1.312886659608501, 0.3 ,0.7582860711910631), 0.003761026864123577, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4000215718433995, 0.3 ,0.7388184499564514), 0.0031351949884195806, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4425202796165686, 0.3 ,0.715501418221286), 0.003823201939366353, material));
  world.add(make_shared<sphere>(glm::dvec3(1.471901247276961, 0.3 ,0.6970967529221153), 0.00856936525624314, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4604650712421217, 0.3 ,0.7308845200389391), 0.004058552570422048, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4361838972278838, 0.3 ,0.7784954846030072), 0.00359050329274501, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3774824379979131, 0.3 ,0.8750792195905917), 0.005261861317908156, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4133177914998787, 0.3 ,0.8200587656088936), 0.003197509031837793, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2483873663970928, 0.3 ,0.9678839138124204), 0.0033264119361517586, material));
  world.add(make_shared<sphere>(glm::dvec3(1.294028938899022, 0.3 ,0.9656684641835671), 0.003202638853922936, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3196786983865816, 0.3 ,0.958680452725392), 0.00605909313067401, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3051780417967196, 0.3 ,0.982522956607607), 0.003541020103928491, material));
  world.add(make_shared<sphere>(glm::dvec3(1.26994089604236, 0.3 ,1.0261000533738174), 0.004523736875372135, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2851281244671888, 0.3 ,1.0092388308997196), 0.003150461039440207, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1922015847844345, 0.3 ,1.0797011741457307), 0.0040723101653140316, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2218398072590975, 0.3 ,1.0807420359248867), 0.005974557733502101, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2001904172882507, 0.3 ,1.1059730630281908), 0.0051356523492560955, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1529235201463761, 0.3 ,1.150773119991173), 0.008239596284139212, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0891217194522005, 0.3 ,1.1954773523772737), 0.01999475776321732, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1132914777372034, 0.3 ,1.1235094231919251), 0.007800460080159464, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1575052601481621, 0.3 ,1.0601800674648565), 0.0038918351346962318, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1420738510602422, 0.3 ,1.0373983246969145), 0.005388043349686989, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1325187118011995, 0.3 ,1.0660357610168327), 0.00469622569024927, material));
  world.add(make_shared<sphere>(glm::dvec3(1.206130999666061, 0.3 ,0.9513323873622077), 0.0031588941294876088, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1635549652632564, 0.3 ,0.9038950277597366), 0.005020000064961365, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1547406216946712, 0.3 ,0.9743144822696508), 0.00391821637945787, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2482143420869591, 0.3 ,0.7497641090098561), 0.0034918392781858373, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1329483577273192, 0.3 ,0.6786347292559554), 0.005835874211487957, material));
  world.add(make_shared<sphere>(glm::dvec3(1.161222690127393, 0.3 ,0.8223959358390707), 0.004086536601220547, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8743996189040111, 0.3 ,1.1590261846253225), 0.003568310144285815, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.899952284510614, 0.3 ,1.1531497488477203), 0.005327577782353713, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8780056714338003, 0.3 ,1.137101264032106), 0.003842703363989884, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8458496875672381, 0.3 ,1.11026113708076), 0.004564180520254724, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8193188661200737, 0.3 ,1.0846204051165125), 0.008204466254576858, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8207225595080101, 0.3 ,1.1218764082140604), 0.004663592473974677, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.842256791261641, 0.3 ,1.1756547630594716), 0.003670254389338569, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8218116124683363, 0.3 ,1.1940964131222023), 0.005706194984802537, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.821635528790838, 0.3 ,1.165255186418653), 0.004035854046864424, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8239757510675614, 0.3 ,1.311986402627044), 0.005033778394164784, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8060798379009031, 0.3 ,1.2811450796128123), 0.006994991616712024, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7920132183750601, 0.3 ,1.3165162878185157), 0.005747909922860627, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7624335285960047, 0.3 ,1.3799351803908364), 0.008506232189465085, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7245889340509992, 0.3 ,1.4469330553297595), 0.018977219908850373, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7992622707386302, 0.3 ,1.41826643325765), 0.009225665849171305, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8653853656291906, 0.3 ,1.344086860324944), 0.00545319923478931, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9049075558270245, 0.3 ,1.3542553740257035), 0.008437929446740513, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.868041325573935, 0.3 ,1.380244252998279), 0.006687650686265683, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9900899677104883, 0.3 ,1.2081208835091637), 0.004322439917261156, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9736472006386443, 0.3 ,1.182272600928494), 0.006012813722354153, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0054847293288365, 0.3 ,1.1857722425821386), 0.004731721353951997, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.060774174638856, 0.3 ,1.1862860401773048), 0.00645477115320161, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.116076163001424, 0.3 ,1.179793410499163), 0.013149794125036505, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0773803981134127, 0.3 ,1.223321895389788), 0.0070878681936411125, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0010106039355395, 0.3 ,1.2523497984609127), 0.004801057223619916, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9970816113879668, 0.3 ,1.288801275617299), 0.007727371246652624, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0296050091417583, 0.3 ,1.2655427811468063), 0.005732689102169598, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2929916912948147, 0.3 ,0.8154738123487439), 0.006173315128912512, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.251406406628692, 0.3 ,0.8032578304448819), 0.00842998153366245, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2683152954032142, 0.3 ,0.8441987670799727), 0.006452366349638557, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2851922587938656, 0.3 ,0.9155063443903042), 0.00831652620513706, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2880027661402478, 0.3 ,0.9847756723559884), 0.01586264225834634, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3363969453450864, 0.3 ,0.9293985440635586), 0.009398099062438207, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3596508137448644, 0.3 ,0.8166008160005616), 0.007198172001007833, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4139355686392643, 0.3 ,0.8008071369105085), 0.01223648002779916, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3860849872176093, 0.3 ,0.8552971181824163), 0.00846879689962462, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4582560184189077, 0.3 ,0.5494211447795554), 0.011001802497329708, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.497313407520934, 0.3 ,0.6203320164363615), 0.01647182171078829, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5321548081899596, 0.3 ,0.5351498057748609), 0.014275402674211546, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.573858438756908, 0.3 ,0.3583532336015601), 0.023059981328601376, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5753657645820978, 0.3 ,0.1412415959416023), 0.05551512503734008, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4528272530529258, 0.3 ,0.3075507749218643), 0.020747935471373106, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.369408650411182, 0.3 ,0.49262591989719745), 0.010106298897238594, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2993496445384878, 0.3 ,0.4857401458208052), 0.013587670775676332, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3510733235517551, 0.3 ,0.4289516752714701), 0.012057351226401135, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.165846632645777, 0.3 ,0.6831762558274836), 0.005325939435836308, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1746130028446555, 0.3 ,0.7206568054287243), 0.00769824038078963, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1397608662907537, 0.3 ,0.702677946338226), 0.00553236007783416, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0835348536883513, 0.3 ,0.6819323525644585), 0.006490586126918097, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0327345352242152, 0.3 ,0.6708148462902241), 0.011467471099220887, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0779779852684626, 0.3 ,0.6421827346209343), 0.006893524638569055, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.165221153274579, 0.3 ,0.6276529354517013), 0.005788680546975699, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.174968490796057, 0.3 ,0.5842195647627444), 0.009444223226818885, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1346611204886616, 0.3 ,0.6077537109775879), 0.006380004446245755, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7822689072611823, 0.3 ,0.8659168900091598), 0.0041518078841951, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.778579656893948, 0.3 ,0.8871340358256699), 0.0030954517586886244, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7739871095445865, 0.3 ,0.9214916275392742), 0.003879629721466879, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7712075283112476, 0.3 ,0.9535584222730924), 0.0073323446199631, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7513720360530174, 0.3 ,0.9278491307671044), 0.00395122380104112, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7158968063561788, 0.3 ,0.8816718519548246), 0.004378197516961052, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7296240081699685, 0.3 ,0.899570446933198), 0.0032195730421845374, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6677539158352438, 0.3 ,0.8130719717402957), 0.0033140119118094022, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.669578018115854, 0.3 ,0.8370346154372255), 0.004821800999413032, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6485122848319219, 0.3 ,0.8222575943815658), 0.0038085049156966113, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6115011401713707, 0.3 ,0.7970332037002366), 0.005261861317908158, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.5731426917082167, 0.3 ,0.7718440300188836), 0.010946436180624275, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6191763903769948, 0.3 ,0.7660313991414633), 0.00538469291036548, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6771999600269741, 0.3 ,0.7808851828615897), 0.0033953122360305807, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6924162096381672, 0.3 ,0.760996462131732), 0.005106448042368384, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6653598055255917, 0.3 ,0.7622541477946274), 0.0039839101428300406, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8041689524371436, 0.3 ,0.8107164915119669), 0.004333817528356983, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8168050673301528, 0.3 ,0.791703299812853), 0.003334072121911528, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8395451113537213, 0.3 ,0.7608791792954317), 0.004397341784706102, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8635193212073632, 0.3 ,0.7321739132455163), 0.008717940251439554, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8257936628273057, 0.3 ,0.7377328583257838), 0.004578660308916098, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7803094174486012, 0.3 ,0.7649852239042161), 0.003130550981451086, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7613177356613339, 0.3 ,0.7512962628759192), 0.004837263186628701, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7857991400185306, 0.3 ,0.7455286060216129), 0.003624258060716731, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.20073315480290216, 0.3 ,0.8016555465061348), 0.003789025529849156, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.28226375441962054, 0.3 ,0.7660194115337944), 0.003090787530379588, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.32855102661745755, 0.3 ,0.7532896225131858), 0.003803355577939535, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.36170804434041426, 0.3 ,0.7433014089966854), 0.008590618382654333, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.32931956232513687, 0.3 ,0.7302917465806342), 0.0038671178943871687, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.2822472678084647, 0.3 ,0.7156587789201887), 0.0032053173734010523, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.1933979748822488, 0.3 ,0.6832345615503201), 0.004128068016336034, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.12526401008926957, 0.3 ,0.6509317332077871), 0.004251005690593096, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.0384551173486084, 0.3 ,0.5989996904722339), 0.0035606765236693505, material));
  world.add(make_shared<sphere>(glm::dvec3(0.007846083599334364, 0.3 ,0.5677151693539968), 0.00447302364237859, material));
  world.add(make_shared<sphere>(glm::dvec3(0.04347527489902103, 0.3 ,0.5474291687398802), 0.010232858198707463, material));
  world.add(make_shared<sphere>(glm::dvec3(0.028030774380792267, 0.3 ,0.5852217142021097), 0.004433362571186285, material));
  world.add(make_shared<sphere>(glm::dvec3(0.0048325942235389885, 0.3 ,0.6352124738435687), 0.0034943184559764447, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.027010088587730796, 0.3 ,0.728048219114698), 0.004077663963463019, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.14549385022976158, 0.3 ,0.8403440831661309), 0.0037048000382809607, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.0609557819009755, 0.3 ,0.9364932226860683), 0.0034138347542924724, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.04196339334086929, 0.3 ,0.9606719011823235), 0.0075525246668398565, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.041506227617294056, 0.3 ,0.929811846184541), 0.0034412685734359284, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.039887511723437186, 0.3 ,0.7984056047279819), 0.003872305751950424, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.0902976604579605, 0.3 ,1.5063220934725552), 0.00397294326807771, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.09342042973358144, 0.3 ,1.4544542300273922), 0.0034670371395613304, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.091585099220719, 0.3 ,1.4263746622499227), 0.006280690341360884, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.11273288595330155, 0.3 ,1.445713345817277), 0.0036002264928007787, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.15397463967322034, 0.3 ,1.4839324272789753), 0.004479320836389914, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.13746362461509642, 0.3 ,1.4685503786181713), 0.003146840748880045, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.21910067805319378, 0.3 ,1.55137310488594), 0.004054197635845192, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.21231145722537997, 0.3 ,1.5234226500765724), 0.005651012842983555, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.24053689621789398, 0.3 ,1.5362253586216825), 0.004717508905413467, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.2944731490490073, 0.3 ,1.558440638013092), 0.007199724854750059, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.3570079414613979, 0.3 ,1.580727147722823), 0.016658867325308885, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.29217533524817496, 0.3 ,1.6030831163263006), 0.007708519678582261, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.21197618971326476, 0.3 ,1.5926224144060412), 0.004321921010198787, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.19392934123156375, 0.3 ,1.6190700864381484), 0.006556840181895375, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.22926678481198304, 0.3 ,1.6156818070712269), 0.005332498875280116, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.07303894797069899, 0.3 ,1.5817322752443403), 0.003111863893377485, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.06831408249121884, 0.3 ,1.5601544082338035), 0.004341945799945727, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.053975066122463944, 0.3 ,1.5780721657445393), 0.003363158051726136, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.02658291499979648, 0.3 ,1.6054684646810318), 0.004459159800538187, material));
  world.add(make_shared<sphere>(glm::dvec3(0.003585203172249085, 0.3 ,1.628375989316356), 0.00881988592022961, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.03586310196929432, 0.3 ,1.6319139023026126), 0.004891901730462695, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.08933429483157507, 0.3 ,1.6102633100331347), 0.0034687600023261653, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.10927250645935827, 0.3 ,1.6278998372493727), 0.005636657195240972, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.08059891168535838, 0.3 ,1.6311186945948548), 0.004091013504702878, material));
  world.add(make_shared<sphere>(glm::dvec3(0.24379972432333474, 0.3 ,1.557236636192636), 0.0035212815144569504, material));
  world.add(make_shared<sphere>(glm::dvec3(0.23458945608423543, 0.3 ,1.5340732351293547), 0.004887006976743385, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2220213426289116, 0.3 ,1.5564855611251849), 0.003745572257477994, material));
  world.add(make_shared<sphere>(glm::dvec3(0.19648312393031053, 0.3 ,1.5907060458287405), 0.004864384721657157, material));
  world.add(make_shared<sphere>(glm::dvec3(0.1672307379845558, 0.3 ,1.6191861261518008), 0.009400746311388559, material));
  world.add(make_shared<sphere>(glm::dvec3(0.21009444089290374, 0.3 ,1.618234662247454), 0.005383932827294795, material));
  world.add(make_shared<sphere>(glm::dvec3(0.26682662820039393, 0.3 ,1.5867883197087218), 0.003985267896571111, material));
  world.add(make_shared<sphere>(glm::dvec3(0.29231032468052853, 0.3 ,1.6041944764485285), 0.006590965116748325, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2598234922978765, 0.3 ,1.6117200911303387), 0.004671139475154205, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4106769042317123, 0.3 ,1.5445242054924726), 0.0055077949156038565, material));
  world.add(make_shared<sphere>(glm::dvec3(0.39282228848070533, 0.3 ,1.580887267242143), 0.00823883351105301, material));
  world.add(make_shared<sphere>(glm::dvec3(0.43694006441266475, 0.3 ,1.5706457891858459), 0.006910027227463393, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5175382030837653, 0.3 ,1.5421127958445309), 0.010559829032288208, material));
  world.add(make_shared<sphere>(glm::dvec3(0.602786977435411, 0.3 ,1.4961490046926162), 0.02418587774157503, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5102544433973629, 0.3 ,1.4813536810316938), 0.009849218331175769, material));
  world.add(make_shared<sphere>(glm::dvec3(0.41059564010022676, 0.3 ,1.4910953268496092), 0.005182738389660756, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3949729108778858, 0.3 ,1.457983189015003), 0.007163522312463025, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4338493279396859, 0.3 ,1.4664930089349981), 0.006137343109218608, material));
  world.add(make_shared<sphere>(glm::dvec3(0.26262066658287087, 0.3 ,1.452838271358347), 0.0031208359344668214, material));
  world.add(make_shared<sphere>(glm::dvec3(0.24721730469827996, 0.3 ,1.469394343116135), 0.004533780442084801, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2445126067551383, 0.3 ,1.4463262636495244), 0.003295746974953463, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2366498095612849, 0.3 ,1.4111240386460795), 0.003946289050092036, material));
  world.add(make_shared<sphere>(glm::dvec3(0.22607355737330925, 0.3 ,1.380973194563088), 0.007115588276873885, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2553878887372629, 0.3 ,1.3956354700549272), 0.004159785588258071, material));
  world.add(make_shared<sphere>(glm::dvec3(0.289635059650341, 0.3 ,1.4350927978142576), 0.003347269814055119, material));
  world.add(make_shared<sphere>(glm::dvec3(0.31381072324374804, 0.3 ,1.4268509520095198), 0.005379675056848634, material));
  world.add(make_shared<sphere>(glm::dvec3(0.29022562565533694, 0.3 ,1.4139223795581146), 0.003721072807733579, material));
  world.add(make_shared<sphere>(glm::dvec3(0.024577407393510775, 0.3 ,1.3069446290763083), 0.0030594238418234663, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.03445733480050028, 0.3 ,1.3365967132714272), 0.005564354737345602, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.02689590374430828, 0.3 ,1.3131028666141733), 0.0030082473051525507, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.012107903363037131, 0.3 ,1.271182354092052), 0.0033511559353149012, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.0010589135894572, 0.3 ,1.222929081135765), 0.003730535173566082, material));
  world.add(make_shared<sphere>(glm::dvec3(0.004337080645777536, 0.3 ,1.1681546596305956), 0.00414284270953488, material));
  world.add(make_shared<sphere>(glm::dvec3(0.008209220876141954, 0.3 ,1.1320108168111962), 0.008719363796231965, material));
  world.add(make_shared<sphere>(glm::dvec3(0.028618406645600447, 0.3 ,1.162295646657103), 0.004183313723705624, material));
  world.add(make_shared<sphere>(glm::dvec3(0.05792805195867168, 0.3 ,1.2099674515694105), 0.003819259821131959, material));
  world.add(make_shared<sphere>(glm::dvec3(0.04752805530578208, 0.3 ,1.192421716367179), 0.003021059709369768, material));
  world.add(make_shared<sphere>(glm::dvec3(0.0670580815211107, 0.3 ,1.2991298472079484), 0.003111289763470008, material));
  world.add(make_shared<sphere>(glm::dvec3(0.11013557879217672, 0.3 ,1.3023958834591933), 0.0030605051325896166, material));
  world.add(make_shared<sphere>(glm::dvec3(0.1355545127052743, 0.3 ,1.3066269273328694), 0.00595098788690298, material));
  world.add(make_shared<sphere>(glm::dvec3(0.11924886408301472, 0.3 ,1.2860208024483473), 0.0031873746309867813, material));
  world.add(make_shared<sphere>(glm::dvec3(0.08843889428795193, 0.3 ,1.250954565855734), 0.0034876202305963, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4107974792609633, 0.3 ,-0.14398266936819984), 0.005990095032602429, material));
  world.add(make_shared<sphere>(glm::dvec3(0.7121516478440385, 0.3 ,0.288079525817654), 0.005026584105248577, material));
  world.add(make_shared<sphere>(glm::dvec3(0.1951540580872756, 0.3 ,0.389102135251945), 0.005990095032602429, material));
  world.add(make_shared<sphere>(glm::dvec3(0.15049884377385803, 0.3 ,-1.4618868290058378), 0.003245155006005677, material));
  world.add(make_shared<sphere>(glm::dvec3(0.16030601028295577, 0.3 ,-1.3365166457452065), 0.005412911852605546, material));
  world.add(make_shared<sphere>(glm::dvec3(0.24778289154407152, 0.3 ,-1.4337629489553378), 0.0035112405208421655, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3034572682903732, 0.3 ,-1.4734729119583996), 0.0041103956199005035, material));
  world.add(make_shared<sphere>(glm::dvec3(0.35485163445030143, 0.3 ,-1.497711926585638), 0.0030675110452118076, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4012033011897215, 0.3 ,-1.5146373362149168), 0.0040483271565445456, material));
  world.add(make_shared<sphere>(glm::dvec3(0.42313896235882564, 0.3 ,-1.5194743430992537), 0.003459751714003821, material));
  world.add(make_shared<sphere>(glm::dvec3(0.46595235506290245, 0.3 ,-1.528612935990227), 0.005527063371716275, material));
  world.add(make_shared<sphere>(glm::dvec3(0.517350640389879, 0.3 ,-1.539067527000413), 0.013506335610883512, material));
  world.add(make_shared<sphere>(glm::dvec3(0.46897614287546696, 0.3 ,-1.5625155220864204), 0.005822067060746959, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4100587793033791, 0.3 ,-1.5629180659964386), 0.0030352952022744822, material));
  world.add(make_shared<sphere>(glm::dvec3(0.40031396472002123, 0.3 ,-1.5828709079837255), 0.004492995391394693, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4244176196440438, 0.3 ,-1.5773179472745185), 0.003779416035308351, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2788855872174615, 0.3 ,-1.6081318651662535), 0.00506463566156694, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3459431169611896, 0.3 ,-1.5965812593341417), 0.0035693993544575193, material));
  world.add(make_shared<sphere>(glm::dvec3(0.12513705527529628, 0.3 ,-1.5175941594470619), 0.0035631711627274547, material));
  world.add(make_shared<sphere>(glm::dvec3(0.0674113287546837, 0.3 ,-1.5820486986811158), 0.0031080784249829722, material));
  world.add(make_shared<sphere>(glm::dvec3(0.026947991099523283, 0.3 ,-1.6093654021947477), 0.003911529047603961, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.0036167100617973125, 0.3 ,-1.6282193559252958), 0.008976449251404514, material));
  world.add(make_shared<sphere>(glm::dvec3(0.03298152407896737, 0.3 ,-1.632731371676034), 0.004135367378283991, material));
  world.add(make_shared<sphere>(glm::dvec3(0.08631255172321062, 0.3 ,-1.6314074243161185), 0.003510732649778259, material));
  world.add(make_shared<sphere>(glm::dvec3(0.19176349538572346, 0.3 ,-1.6211685822097084), 0.004729053480806247, material));
  world.add(make_shared<sphere>(glm::dvec3(0.1318017824290698, 0.3 ,-1.6288597620587904), 0.0030162844899319684, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.36996696425348874, 0.3 ,-1.4905313189986231), 0.0031709742411243098, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.3404808626350659, 0.3 ,-1.433977138836558), 0.005006883593575135, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.31791738381811707, 0.3 ,-1.4957342119845172), 0.003370648154442307, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.29118145084997094, 0.3 ,-1.5398823342473635), 0.004031547662462053, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.2765129868469246, 0.3 ,-1.5560578545967272), 0.003281401638037011, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.24849330256204344, 0.3 ,-1.58405939690986), 0.004775268661087869, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.21630950074839705, 0.3 ,-1.6122836741425253), 0.010470451150647824, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.26052225126510276, 0.3 ,-1.611159542874852), 0.005113146616548956, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.30982513646612186, 0.3 ,-1.585536482793821), 0.0030764709816852713, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.32835413079862596, 0.3 ,-1.5991001319418385), 0.004736141806108741, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.3037951842527791, 0.3 ,-1.6049675288443135), 0.003733482407097328, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.40321477496161634, 0.3 ,-1.523551141904947), 0.0035326727411496834, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.448653643073255, 0.3 ,-1.5468686968268275), 0.0037670849553284977, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.47935087600722387, 0.3 ,-1.557440277260805), 0.007660783030258914, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.448174807022032, 0.3 ,-1.5704118264066658), 0.004088079916685779, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.39073954024599533, 0.3 ,-1.5853616357422804), 0.004395821405213218, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.41308532074095117, 0.3 ,-1.5808434935890214), 0.0032764353635209623, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6803601864836608, 0.3 ,-1.4133586200885508), 0.003951623361691646, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6612940843513774, 0.3 ,-1.3930661496434071), 0.005434487511950192, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6574991889070465, 0.3 ,-1.4211749226235069), 0.0041030736323456034, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6441490679151451, 0.3 ,-1.4652694371151342), 0.005170301955425548, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6243356613126656, 0.3 ,-1.503027071998976), 0.009660145951546503, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6670831565373243, 0.3 ,-1.4887855538867398), 0.005794794681238947, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.716335293643451, 0.3 ,-1.4360784733817418), 0.004580407931419172, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7508924937390054, 0.3 ,-1.44608027108423), 0.007786526504978628, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7175402117553791, 0.3 ,-1.4656681720435483), 0.005315283807821648, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.867708052900464, 0.3 ,-1.3248140602750067), 0.0075228748654095675, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8617364120836924, 0.3 ,-1.379129586834234), 0.01098087574588771, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9143854229170416, 0.3 ,-1.3463088864920243), 0.00973298072367538, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0124223160429522, 0.3 ,-1.2655300722404752), 0.01653165432029956, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1144455522218797, 0.3 ,-1.1404774167118061), 0.04262225196432698, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9646542321600104, 0.3 ,-1.1828831855448378), 0.01530868175668881, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8390872438208752, 0.3 ,-1.2576047514471076), 0.007093109087066396, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8003719194843123, 0.3 ,-1.2265579307696264), 0.009619657057551672, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8533498928411724, 0.3 ,-1.2128012685675442), 0.008648286632493032, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6513694805530085, 0.3 ,-1.2964321884506622), 0.0035863717195463024, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.644285237490327, 0.3 ,-1.3211970592510125), 0.00512070567675887, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6296899423665514, 0.3 ,-1.2994482199213337), 0.003710678206676293, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6028498903942615, 0.3 ,-1.2692318694410771), 0.004400651503900313, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.5755834388115453, 0.3 ,-1.2466686336063089), 0.007832074706277186, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6121089460543727, 0.3 ,-1.2434560409987663), 0.004734224340937118, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6694318195100041, 0.3 ,-1.2633229098489525), 0.0039659256434294654, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6900587822845662, 0.3 ,-1.240587541846675), 0.006553554323620725, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6577388085535671, 0.3 ,-1.2411194537402808), 0.004409251091142057, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.34225604879082905, 0.3 ,-1.3469736036170885), 0.004668049716109567, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.30675581682580666, 0.3 ,-1.2529491403884128), 0.0032002492618038786, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.2788916025488391, 0.3 ,-1.2148860929192309), 0.0035473791652146933, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.2596472475545484, 0.3 ,-1.1904574219400075), 0.0074534507304441205, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.2906089959332959, 0.3 ,-1.1967012998787436), 0.003664444771916792, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.33863560841443047, 0.3 ,-1.2102423155586217), 0.003466677005410157, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.4536141167775325, 0.3 ,-1.2354754580729168), 0.005910370358084544, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.4286100049758557, 0.3 ,-1.2288736477952098), 0.0031062463780488114, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.38464475147412314, 0.3 ,-1.220842751299364), 0.003280763251970802, material));
  world.add(make_shared<sphere>(glm::dvec3(0.11418319259950527, 0.3 ,-1.2325317873421098), 0.004939192684574164, material));
  world.add(make_shared<sphere>(glm::dvec3(0.12729522923568104, 0.3 ,-0.9672364741793753), 0.0032791247240364046, material));
  world.add(make_shared<sphere>(glm::dvec3(0.1351798636708057, 0.3 ,-0.9378723482729276), 0.007667694876419757, material));
  world.add(make_shared<sphere>(glm::dvec3(0.11075448423319145, 0.3 ,-0.9563239173185389), 0.00332641193615176, material));
  world.add(make_shared<sphere>(glm::dvec3(0.02393197292487026, 0.3 ,-1.0316453272797896), 0.003064556521494565, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.12562485757728975, 0.3 ,-1.1309482091355783), 0.005960165048246253, material));
  world.add(make_shared<sphere>(glm::dvec3(0.24682467747475134, 0.3 ,-0.7967039014256871), 0.006249049154925427, material));
  world.add(make_shared<sphere>(glm::dvec3(0.40327197166487083, 0.3 ,-0.3733251507311117), 0.003013991918970795, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4111827652838437, 0.3 ,-0.34548646819064865), 0.007531239124125098, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6492680894741384, 0.3 ,-0.7257264580392881), 0.005453821226621046, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9229486901942846, 0.3 ,-1.07888267254956), 0.004142328505576398, material));
  world.add(make_shared<sphere>(glm::dvec3(0.90689518630532, 0.3 ,-1.2336159549148098), 0.0033117819021797573, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8734390511483415, 0.3 ,-1.314369437048135), 0.0034127874679818395, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8440415723557148, 0.3 ,-1.3629486171707044), 0.004817081627178985, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8203947076257866, 0.3 ,-1.4028296885864222), 0.012091022121263978, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8641272420467826, 0.3 ,-1.3846411005664876), 0.005039637524032921, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9156881390794313, 0.3 ,-1.3526863325562652), 0.0037234425262986756, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8988242302564652, 0.3 ,-1.3646024825288126), 0.0031787290568419065, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9959522340131705, 0.3 ,-1.2945009584351428), 0.003904507677273607, material));
  world.add(make_shared<sphere>(glm::dvec3(1.147090896219328, 0.3 ,-1.1598097671500225), 0.005949926941262233, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0479106227337702, 0.3 ,-1.2533770931811505), 0.0034707101479943426, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2384178570525313, 0.3 ,-1.0612518577353016), 0.006269322506992211, material));
  world.add(make_shared<sphere>(glm::dvec3(1.333503189162896, 0.3 ,-0.9427719299122421), 0.004089394839203914, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3775844786276195, 0.3 ,-0.8756571945758158), 0.004865751372486477, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4139298330730972, 0.3 ,-0.8179307951668606), 0.0037346835597408426, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4324416569405258, 0.3 ,-0.7408427298995826), 0.0034771170822012394, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4422528755356163, 0.3 ,-0.7640653537721533), 0.005057297038104308, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4558673002628626, 0.3 ,-0.7392525572896451), 0.004397341784706099, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4779690660613514, 0.3 ,-0.6873421684857084), 0.007220737233503656, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4956308394636393, 0.3 ,-0.6203209231579014), 0.01803038811553242, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4432079334444667, 0.3 ,-0.6632478470089656), 0.006881251101109193, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4060158083293182, 0.3 ,-0.7192863416335142), 0.0033446840698876067, material));
  world.add(make_shared<sphere>(glm::dvec3(1.382887780626323, 0.3 ,-0.714355363796649), 0.004630619857900174, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4026646051432086, 0.3 ,-0.6973888351015772), 0.0040711665968868735, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2865109093998912, 0.3 ,-0.7757722206297217), 0.004172228080366608, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3375189431279555, 0.3 ,-0.7451690547069763), 0.0033121105713653665, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1108584148502478, 0.3 ,-0.8350294670275553), 0.00466927427186314, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2248239631397566, 0.3 ,-0.8024846233899454), 0.0033423115067087923, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9056179384117368, 0.3 ,-0.993889196285384), 0.003752876997420986, material));
  world.add(make_shared<sphere>(glm::dvec3(0.780257994136707, 0.3 ,-0.8001683080498012), 0.006156979894338513, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0156832111227794, 0.3 ,-0.8429520328766307), 0.0040358286563724945, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5401740908589119, 0.3 ,0.5368427707031858), 0.006146055083457069, material));
  world.add(make_shared<sphere>(glm::dvec3(1.601861979395104, 0.3 ,0.320597588475723), 0.0035705449817134537, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6156795712047547, 0.3 ,0.23852747995989526), 0.0040079057000064556, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6316392546881677, 0.3 ,0.08197922504391397), 0.0035024048687259486, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6332275386464445, 0.3 ,-0.014227834692031205), 0.003910311767232056, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6333414865517302, 0.3 ,-0.036286879439272), 0.0034553042513730957, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6293127598558006, 0.3 ,-0.0811897552457291), 0.005865446174773989, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6161083748166645, 0.3 ,-0.13722399131341323), 0.015276055940681673, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5949932862926142, 0.3 ,-0.08479916380811914), 0.005639445092936042, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5737298287183985, 0.3 ,-0.02491128484411534), 0.0036502503862557594, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5803502019431073, 0.3 ,-0.04449434766009405), 0.003250659948481043, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5362077979240598, 0.3 ,0.05453203122931577), 0.003128127251689793, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4580692251271614, 0.3 ,0.16424005300616457), 0.00328767796120486, material));
  world.add(make_shared<sphere>(glm::dvec3(1.276606072379673, 0.3 ,0.302819942623405), 0.004125118272898268, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1822087175439258, 0.3 ,0.33943354152071653), 0.003676141555486866, material));
  world.add(make_shared<sphere>(glm::dvec3(0.861296040985328, 0.3 ,0.3484114034234668), 0.0057214694364875395, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0857100017123953, 0.3 ,0.5779847516395398), 0.003676141555486866, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4802500537952055, 0.3 ,0.6849789550406937), 0.006146055083457069, material));
  world.add(make_shared<sphere>(glm::dvec3(1.374239736810873, 0.3 ,0.8832948321698924), 0.0035705449817134537, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3271103608042898, 0.3 ,0.951889660491334), 0.0040079057000064556, material));
  world.add(make_shared<sphere>(glm::dvec3(1.229738296001865, 0.3 ,1.0755049856344656), 0.0035024048687259486, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1639901265785983, 0.3 ,1.145758093796719), 0.003910311767232056, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1487350652966541, 0.3 ,1.1616922566103096), 0.0034553042513730957, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1146198580193838, 0.3 ,1.1911651513936439), 0.005865446174773989, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0661703609521238, 0.3 ,1.2222591641594533), 0.015276055940681673, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0874432279283708, 0.3 ,1.1698981611806218), 0.005639445092936042, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1137982800501733, 0.3 ,1.1120699336228388), 0.0036502503862557594, material));
  world.add(make_shared<sphere>(glm::dvec3(1.104941184477755, 0.3 ,1.1307481976993008), 0.003250659948481043, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1420637642111457, 0.3 ,1.0288821600691476), 0.003128127251689793, material));
  world.add(make_shared<sphere>(glm::dvec3(1.162178208618725, 0.3 ,0.8957022226645215), 0.00328767796120486, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1281018145553352, 0.3 ,0.6699322933581107), 0.004125118272898268, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9082329769354939, 0.3 ,1.155368279989073), 0.003245155006005677, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8140181231860427, 0.3 ,1.072077075779319), 0.005412911852605546, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8187564166617363, 0.3 ,1.2027927856926508), 0.0035112405208421655, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8063495490827628, 0.3 ,1.270042968031969), 0.0041103956199005035, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7862624743684911, 0.3 ,1.3231976492228432), 0.0030675110452118076, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7647149198951075, 0.3 ,1.3675896462139423), 0.0040483271565445456, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7523116824739723, 0.3 ,1.3863174215222864), 0.003459751714003821, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.727893333227813, 0.3 ,1.422652593118868), 0.005527063371716275, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6982195645896372, 0.3 ,1.4659024447088047), 0.013506335610883512, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7492913895858343, 0.3 ,1.449122421619336), 0.005822067060746959, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7919181207973158, 0.3 ,1.408448356687131), 0.0030352952022744822, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8127947909565458, 0.3 ,1.4160141981932943), 0.004492995391394693, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7916094897164181, 0.3 ,1.428781522294272), 0.003779416035308351, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.917634587827728, 0.3 ,1.3497451721502711), 0.00506463566156694, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8614062146840664, 0.3 ,1.3880661695803609), 0.0035693993544575193, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9651933205193047, 0.3 ,1.1777746683537271), 0.0035631711627274547, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0514969042391864, 0.3 ,1.1839664828948917), 0.0031080784249829722, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0995723746104176, 0.3 ,1.1754674750920917), 0.003911529047603961, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.134649315738766, 0.3 ,1.1677680771005055), 0.008976449251404514, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.111481397861127, 0.3 ,1.1964566917337034), 0.004135367378283991, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0722292227036148, 0.3 ,1.232584493930998), 0.003510732649778259, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9893176114456368, 0.3 ,1.2985420569969597), 0.004729053480806247, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.037762528542051, 0.3 ,1.2623805958029126), 0.0030162844899319684, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3022333911440356, 0.3 ,0.8140929692266288), 0.0031709742411243098, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2417199094785905, 0.3 ,0.7939454130676034), 0.005006883593575135, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2684401633708473, 0.3 ,0.8540209879051246), 0.003370648154442307, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2799185150687897, 0.3 ,0.9043411056843069), 0.004031547662462053, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.28062188808625, 0.3 ,0.9261657834867316), 0.003281401638037011, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2799513333570234, 0.3 ,0.9657730989182742), 0.004775268661087869, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2764426797514894, 0.3 ,1.0084356852716918), 0.010470451150647824, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3074390210035012, 0.3 ,0.9768879784081457), 0.005113146616548956, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3250605604222614, 0.3 ,0.9241926556026621), 0.0030764709816852713, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3478086545635324, 0.3 ,0.9210589003275387), 0.004736141806108741, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3342363286116414, 0.3 ,0.9423511564341274), 0.003733482407097328, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3490879014044441, 0.3 ,0.8147098078649684), 0.0035326727411496834, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3979590518160365, 0.3 ,0.7998770818764884), 0.0037670849553284977, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4273727760017643, 0.3 ,0.7861325828968855), 0.007660783030258914, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4139836873390474, 0.3 ,0.8171316259368704), 0.004088079916685779, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3830962224728793, 0.3 ,0.8678097393878164), 0.004395821405213218, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3960159297972397, 0.3 ,0.8490260050120682), 0.0032764353635209623, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4716727646624128, 0.3 ,0.5428184282811255), 0.003951623361691646, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4438602860722052, 0.3 ,0.5414892774413269), 0.005434487511950192, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4606758524386985, 0.3 ,0.5643309296944863), 0.0041030736323456034, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.481737984694084, 0.3 ,0.6053057820262198), 0.005170301955425548, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4937487969518508, 0.3 ,0.6462197217304986), 0.009660145951546503, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5145718786685203, 0.3 ,0.6062626390799313), 0.005794794681238947, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.513326273710387, 0.3 ,0.5341359601520248), 0.004580407931419172, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.545118197246825, 0.3 ,0.5172982158381649), 0.007786526504978628, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5347650972079574, 0.3 ,0.5545658143265646), 0.005315283807821648, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.544766790787325, 0.3 ,0.34891993558880646), 0.0075228748654095675, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5782385545028652, 0.3 ,0.39211111470239063), 0.01098087574588771, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.593260828393399, 0.3 ,0.33191603184804924), 0.00973298072367538, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6075618715737363, 0.3 ,0.2056942848722541), 0.01653165432029956, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.593945886820558, 0.3 ,0.04487913529238885), 0.04262225196432698, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5157667754008075, 0.3 ,0.1795034842557769), 0.01530868175668881, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4774670616568506, 0.3 ,0.3205123949620819), 0.007093109087066396, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.428054542489559, 0.3 ,0.3251150422662897), 0.009619657057551672, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4565678854575612, 0.3 ,0.27839351950930497), 0.008648286632493032, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3695404173921555, 0.3 ,0.4789338833035242), 0.0035863717195463024, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3816668549436044, 0.3 ,0.5016590860053707), 0.00512070567675887, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3560552013234357, 0.3 ,0.49617475826363194), 0.003710678206676293, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3157554340261122, 0.3 ,0.493117801933804), 0.004400651503900313, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.280470162376492, 0.3 ,0.4958579840190836), 0.007832074706277186, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.304489255916426, 0.3 ,0.4681538944991633), 0.004734224340937118, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3595028814667312, 0.3 ,0.44257841204170684), 0.0039659256434294654, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3585213232938802, 0.3 ,0.41189608659112426), 0.006553554323620725, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3356611638166584, 0.3 ,0.4347494614165415), 0.004409251091142057, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1825049976905513, 0.3 ,0.7301773909208584), 0.004668049716109567, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0916169482832079, 0.3 ,0.6872795048431108), 0.0032002492618038786, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.045125502235213, 0.3 ,0.6792948029526009), 0.0035473791652146933, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0143091340120156, 0.3 ,0.6751166915982019), 0.0074534507304441205, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.040904062983259, 0.3 ,0.6580777471650152), 0.003664444771916792, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0848378338289666, 0.3 ,0.6344189561702791), 0.003466677005410157, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.185022448590495, 0.3 ,0.5726143298739013), 0.005910370358084544, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1624607117898873, 0.3 ,0.5852538527475588), 0.0031062463780488114, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1252770556065317, 0.3 ,0.6100493065009505), 0.003280763251970802, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7748714906238444, 0.3 ,0.9652702115466629), 0.004939192684574164, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.5809957111561823, 0.3 ,0.783705592673192), 0.0032791247240364046, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.5549126752069724, 0.3 ,0.7680820659875336), 0.007667694876419757, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.5852972134065643, 0.3 ,0.7643619316735693), 0.00332641193615176, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7000695052782208, 0.3 ,0.7581342284884727), 0.003064556521494565, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8766056536563175, 0.3 ,0.7255260054374828), 0.005960165048246253, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.37651797572906015, 0.3 ,0.7442403791184138), 0.006249049154925427, material));
  world.add(make_shared<sphere>(glm::dvec3(0.03029047169223531, 0.3 ,0.5487097945394666), 0.003013991918970795, material));
  world.add(make_shared<sphere>(glm::dvec3(0.055331716668933106, 0.3 ,0.5342008679324541), 0.007531239124125098, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.03791338508011355, 0.3 ,0.9730316126105147), 0.005453821226621046, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.08674388303996206, 0.3 ,1.4171441721342903), 0.004142328505576398, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.2058635328270787, 0.3 ,1.5171972215292577), 0.0033117819021797573, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.28605549109848877, 0.3 ,1.5519777862874053), 0.0034127874679818395, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.34096050793031607, 0.3 ,1.5664549278367863), 0.004817081627178985, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.3856847489702957, 0.3 ,1.5786785251885853), 0.012091022121263978, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.34160603557809455, 0.3 ,1.5960113358876804), 0.005039637524032921, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.28232949375716826, 0.3 ,1.6088925194959727), 0.0037234425262986756, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.3027353532297762, 0.3 ,1.605732305873172), 0.0031787290568419065, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.18418521144277755, 0.3 ,1.6228768874166384), 0.003904507677273607, material));
  world.add(make_shared<sphere>(glm::dvec3(0.018092259114819043, 0.3 ,1.6311495609924858), 0.005949926941262233, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.11824798699232897, 0.3 ,1.6294441458736098), 0.0034707101479943426, material));
  world.add(make_shared<sphere>(glm::dvec3(0.15225773271613052, 0.3 ,1.623807832547116), 0.006269322506992211, material));
  world.add(make_shared<sphere>(glm::dvec3(0.30297568968350974, 0.3 ,1.6047602309375928), 0.004089394839203914, material));
  world.add(make_shared<sphere>(glm::dvec3(0.38132188511101406, 0.3 ,1.5871698516868031), 0.004865751372486477, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4475804619901548, 0.3 ,1.570948786110196), 0.0037346835597408426, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5144827472393988, 0.3 ,1.528412429214246), 0.0034771170822012394, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5053885992267929, 0.3 ,1.5519251224196697), 0.005057297038104308, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5324255254745819, 0.3 ,1.5435566070789497), 0.004397341784706099, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5844028334152743, 0.3 ,1.5216126790708298), 0.007220737233503656, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6436950010047319, 0.3 ,1.4857208356026064), 0.01803038811553242, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5761702947047088, 0.3 ,1.4801265612166326), 0.006881251101109193, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5104766486169116, 0.3 ,1.4945457121645103), 0.0033446840698876067, material));
  world.add(make_shared<sphere>(glm::dvec3(0.49728173280291454, 0.3 ,1.4749213802135954), 0.004630619857900174, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5232926202156437, 0.3 ,1.4764768929697953), 0.0040711665968868735, material));
  world.add(make_shared<sphere>(glm::dvec3(0.3853096440407039, 0.3 ,1.4520569329454467), 0.004172228080366608, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4432490888593067, 0.3 ,1.4655251920538293), 0.0033121105713653665, material));
  world.add(make_shared<sphere>(glm::dvec3(0.21785971035642338, 0.3 ,1.3725224133876102), 0.00466927427186314, material));
  world.add(make_shared<sphere>(glm::dvec3(0.32239985632838286, 0.3 ,1.4283674751611106), 0.0033423115067087923, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.04010706493835159, 0.3 ,1.344005583399105), 0.003752876997420986, material));
  world.add(make_shared<sphere>(glm::dvec3(0.00447852745005517, 0.3 ,1.1176098610040102), 0.006156979894338513, material));
  world.add(make_shared<sphere>(glm::dvec3(0.14394422134632, 0.3 ,1.3120444261641946), 0.0040358286563724945, material));
  world.add(make_shared<sphere>(glm::dvec3(0.41047983306701796, 0.3 ,-0.1546875629384657), 0.004719510256821078, material));
  world.add(make_shared<sphere>(glm::dvec3(0.720462753158447, 0.3 ,0.29144153345358875), 0.003938769590577656, material));
  world.add(make_shared<sphere>(glm::dvec3(0.18748297343222187, 0.3 ,0.3965754280784202), 0.004719510256821078, material));
  world.add(make_shared<sphere>(glm::dvec3(0.15689679521554767, 0.3 ,-1.3279159478295333), 0.0038388313351675014, material));
  world.add(make_shared<sphere>(glm::dvec3(0.502940468959843, 0.3 ,-1.5293728150866017), 0.0038614644724549365, material));
  world.add(make_shared<sphere>(glm::dvec3(0.540543572624019, 0.3 ,-1.5346923440341012), 0.01009566285547753, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5063770337775774, 0.3 ,-1.5527116847909073), 0.004003178485557379, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2710226455222474, 0.3 ,-1.6111915033336248), 0.0033726173165990925, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.018925606424885832, 0.3 ,-1.6305770575603162), 0.006512936303082828, material));
  world.add(make_shared<sphere>(glm::dvec3(0.19965833342931916, 0.3 ,-1.621767450139545), 0.0031884657349580438, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.3402761259801274, 0.3 ,-1.4256560652681105), 0.0033167083251457443, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.22239563240438376, 0.3 ,-1.600187869492914), 0.0030702094187469954, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.1992132130692295, 0.3 ,-1.6175578677347224), 0.0074208922996590225, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.22878097271011733, 0.3 ,-1.6178979106722466), 0.0032064368251905916, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.4921692994540456, 0.3 ,-1.5559751443968008), 0.005241100319516604, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6588846670129795, 0.3 ,-1.3847336448190781), 0.0032393771721479616, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6111144825953077, 0.3 ,-1.5120348685851306), 0.006337977876385826, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6369858884737083, 0.3 ,-1.504818278212728), 0.0031162646134818123, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7631682848712801, 0.3 ,-1.4429165909402892), 0.0048903784791411485, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8627206933930371, 0.3 ,-1.3147264728175663), 0.0037302658325391418, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8590035475435228, 0.3 ,-1.364941839358183), 0.0034676787506393238, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8498927757026178, 0.3 ,-1.3918394087828727), 0.006391841275154456, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.876560394956621, 0.3 ,-1.3781865410396967), 0.003873073344757322, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9044163487376962, 0.3 ,-1.338180686752919), 0.0031297589142120458, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9287563965068417, 0.3 ,-1.3417927294095564), 0.005330901800835266, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9079920546427827, 0.3 ,-1.358010868450536), 0.0036016186196735273, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0000682643244572, 0.3 ,-1.2473776612526508), 0.005425864176428362, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0000202405671184, 0.3 ,-1.2864478015218574), 0.007786299425800709, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.035148106072438, 0.3 ,-1.259346391734819), 0.0070204037014592845, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1019389604055179, 0.3 ,-1.194046301633911), 0.012387204228756785, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1737705251575858, 0.3 ,-1.0924884599960516), 0.03368235065234884, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0604140595846663, 0.3 ,-1.1349859352726341), 0.011687586601093253, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9735495540483029, 0.3 ,-1.2013608810665823), 0.005198682366733508, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9422703148960689, 0.3 ,-1.1826665152031068), 0.007076284138214028, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.979693166661622, 0.3 ,-1.1671749860185494), 0.006437975073763301, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.842700192431237, 0.3 ,-1.2676474333896515), 0.0035797002085319438, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8073200937500089, 0.3 ,-1.2372164822177392), 0.0031036225746245392, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7852534783344275, 0.3 ,-1.2254858492010579), 0.005536748244900292, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8101626716233997, 0.3 ,-1.218023406436547), 0.0033686812904038955, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8646229505040253, 0.3 ,-1.2056110714545047), 0.004722605768329325, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8418377016494164, 0.3 ,-1.2101670771483402), 0.003161434383202089, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6457791720725168, 0.3 ,-1.3292748534718526), 0.003094073687904187, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.5630159921927422, 0.3 ,-1.2436592578278953), 0.005090659412018604, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7001325476060678, 0.3 ,-1.2370817268570031), 0.0041128174350653504, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.341743502451331, 0.3 ,-1.3547574074398572), 0.003132610877806642, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.24862008367278965, 0.3 ,-1.184186734749786), 0.005231968502390467, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.46355423888875735, 0.3 ,-1.2349126132092496), 0.004045674133912252, material));
  world.add(make_shared<sphere>(glm::dvec3(0.11793743250219146, 0.3 ,-1.2401492962354026), 0.003553201500007564, material));
  world.add(make_shared<sphere>(glm::dvec3(0.14281591575237396, 0.3 ,-0.926937018811405), 0.00566987318617953, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.13540498875606283, 0.3 ,-1.134152968726451), 0.004331649656134189, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2394926634427672, 0.3 ,-0.804902526185937), 0.004749854323357907, material));
  world.add(make_shared<sphere>(glm::dvec3(0.410743627945232, 0.3 ,-0.33218778772509894), 0.005774689769678494, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6577199911193102, 0.3 ,-0.7302302137313796), 0.004123154118116148, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8225740721173641, 0.3 ,-1.3874555755892926), 0.0034367909905576115, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8036056815652398, 0.3 ,-1.4158740528544638), 0.009169900606102985, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8360187592816405, 0.3 ,-1.4035273273845403), 0.0035485971208218618, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1554229719067584, 0.3 ,-1.1538711624914766), 0.0042819111414860705, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2328559813710416, 0.3 ,-1.0704455635937586), 0.004475847966675166, material));
  world.add(make_shared<sphere>(glm::dvec3(1.3747272975152707, 0.3 ,-0.883207842631694), 0.0032073998073503646, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4772044129138848, 0.3 ,-0.6979472099671232), 0.0034118353271919326, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4856923104592035, 0.3 ,-0.6805891202386684), 0.00303851052916413, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4998555708164236, 0.3 ,-0.6432077062145249), 0.005243055842853909, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5112799874397438, 0.3 ,-0.592431987284009), 0.013949114328315599, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4735289553207545, 0.3 ,-0.6270106686774393), 0.0050617312714289825, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4339786295026151, 0.3 ,-0.6673340277739146), 0.0032121588526639626, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1028907006995143, 0.3 ,-0.8349451665019592), 0.0032988858273327146, material));
  world.add(make_shared<sphere>(glm::dvec3(0.7710699561170323, 0.3 ,-0.7946141110732641), 0.00457936709638254, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5380710416335917, 0.3 ,0.5474028254344867), 0.004621375992347106, material));
  world.add(make_shared<sphere>(glm::dvec3(1.628267798261131, 0.3 ,-0.12177417738800164), 0.004384776412799709, material));
  world.add(make_shared<sphere>(glm::dvec3(1.616804343616694, 0.3 ,-0.16453611289008246), 0.01204493155225817, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6023903083679163, 0.3 ,-0.12331844774581133), 0.004257235871061925, material));
  world.add(make_shared<sphere>(glm::dvec3(1.2697434743374032, 0.3 ,0.3049828985982099), 0.0030702712536470667, material));
  world.add(make_shared<sphere>(glm::dvec3(0.8518993228498698, 0.3 ,0.34461024377874777), 0.004414956282763663, material));
  world.add(make_shared<sphere>(glm::dvec3(1.486080561719687, 0.3 ,0.6759267315947801), 0.004621375992347106, material));
  world.add(make_shared<sphere>(glm::dvec3(1.085651717177167, 0.3 ,1.21960867581489), 0.004384776412799709, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0476813277724952, 0.3 ,1.2423736368016067), 0.01204493155225817, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0659785886141138, 0.3 ,1.2027268137537008), 0.004257235871061925, material));
  world.add(make_shared<sphere>(glm::dvec3(1.124673157602579, 0.3 ,0.6636063197619733), 0.0030702712536470667, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8104887012466627, 0.3 ,1.0635250039375765), 0.0038388313351675014, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7018364464460973, 0.3 ,1.4489154306871697), 0.0038614644724549365, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6785077171748932, 0.3 ,1.4788830996654685), 0.01009566285547753, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7155931989388128, 0.3 ,1.468079578924835), 0.004003178485557379, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9254133475412805, 0.3 ,1.3464774305545537), 0.0033726173165990925, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1472918209339857, 0.3 ,1.1588188800837664), 0.006512936303082828, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9840595706738545, 0.3 ,1.3044615263797905), 0.0031884657349580438, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2357873737694784, 0.3 ,0.7881069884094012), 0.0033167083251457443, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2724072536158562, 0.3 ,0.9955103293942154), 0.0030702094187469954, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2678217042201287, 0.3 ,1.0241130240555705), 0.0074208922996590225, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2893099526419056, 0.3 ,1.0037998948248323), 0.0032064368251905916, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.435567356967034, 0.3 ,0.7761672712221384), 0.005241100319516604, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4363351883284903, 0.3 ,0.5371754818381973), 0.0032393771721479616, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4905089129438411, 0.3 ,0.6618863460519182), 0.006337977876385826, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5040865171750226, 0.3 ,0.638711845365401), 0.0031162646134818123, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.55174181463279, 0.3 ,0.5064893485200439), 0.0048903784791411485, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5341685432500825, 0.3 ,0.3451370366069196), 0.0037302658325391418, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5664100126739446, 0.3 ,0.3838137461291267), 0.0034676787506393238, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5785626810702258, 0.3 ,0.40948080781025936), 0.006391841275154456, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5882376220557788, 0.3 ,0.3811266505980409), 0.003873073344757322, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5804442742074978, 0.3 ,0.33300507261493634), 0.0031297589142120458, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.600450023412085, 0.3 ,0.3186783571392658), 0.005330901800835266, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5968016156553446, 0.3 ,0.3447719396422612), 0.0036016186196735273, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.58606159537872, 0.3 ,0.20123662381827445), 0.005425864176428362, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6131913203489243, 0.3 ,0.2293516765476905), 0.007786299425800709, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6195967142189232, 0.3 ,0.18544923610555836), 0.0070204037014592845, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6222015380133028, 0.3 ,0.09207721201520425), 0.012387204228756785, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6032204959750334, 0.3 ,-0.030859718709507267), 0.03368235065234884, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5512926968305831, 0.3 ,0.07849853369094856), 0.011687586601093253, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5350072496555218, 0.3 ,0.1865996898435761), 0.005198682366733508, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4995276907804236, 0.3 ,0.19491058744904372), 0.007076284138214028, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5156545915524169, 0.3 ,0.15775711678703375), 0.006437975073763301, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4870462299669867, 0.3 ,0.3252186028565867), 0.0035797002085319438, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.440459098973415, 0.3 ,0.32794502866862035), 0.0031036225746245392, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4164427782530609, 0.3 ,0.334855861174789), 0.005536748244900292, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4291578587351155, 0.3 ,0.31217365028925476), 0.0033686812904038955, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4596712773135199, 0.3 ,0.2653877622232898), 0.004722605768329325, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4464620274368158, 0.3 ,0.2845042595735761), 0.003161434383202089, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3883568571695217, 0.3 ,0.5064263147839503), 0.003094073687904187, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2693449856103234, 0.3 ,0.5024327462971947), 0.005090659412018604, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3633243590103554, 0.3 ,0.40237230927323414), 0.0041128174350653504, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1875484394591247, 0.3 ,0.7361283572985562), 0.003132610877806642, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.002023548017017, 0.3 ,0.6782764760643107), 0.005231968502390467, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1917755829929628, 0.3 ,0.5652987302628767), 0.004045674133912252, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7774693454997147, 0.3 ,0.9733555012155763), 0.003553201500007564, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.5418212714788042, 0.3 ,0.7655314052396935), 0.00566987318617953, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.885863291681311, 0.3 ,0.7210296082010841), 0.004331649656134189, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.3874881072404765, 0.3 ,0.745035421473778), 0.004749854323357907, material));
  world.add(make_shared<sphere>(glm::dvec3(0.06426224176452289, 0.3 ,0.5243371229416303), 0.005774689769678494, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.034969900724202585, 0.3 ,0.9821450289073939), 0.004123154118116148, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.37342919259668517, 0.3 ,1.569143625188642), 0.0034367909905576115, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.4068211984403548, 0.3 ,1.576381279224674), 0.009169900606102985, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.3749400081988205, 0.3 ,1.5900428657233996), 0.0035485971208218618, material));
  world.add(make_shared<sphere>(glm::dvec3(0.02820986391055047, 0.3 ,1.632674219560483), 0.0042819111414860705, material));
  world.add(make_shared<sphere>(glm::dvec3(0.1418680394939701, 0.3 ,1.626548811069025), 0.004475847966675166, material));
  world.add(make_shared<sphere>(glm::dvec3(0.37401855762195746, 0.3 ,1.5906103716417064), 0.0032073998073503646, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5764798865352155, 0.3 ,1.5287034133060284), 0.0034118353271919326, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5946490977818225, 0.3 ,1.522128655026284), 0.00303851052916413, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6308190648633883, 0.3 ,1.5051080340120773), 0.005243055842853909, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6743331277408072, 0.3 ,1.4765560242755633), 0.013949114328315599, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6231581017206852, 0.3 ,1.4751623439689219), 0.0050617312714289825, material));
  world.add(make_shared<sphere>(glm::dvec3(0.566695739283345, 0.3 ,1.4766466583354543), 0.0032121588526639626, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2121915273196826, 0.3 ,1.3669221208569993), 0.0032988858273327146, material));
  world.add(make_shared<sphere>(glm::dvec3(0.0017362839247665462, 0.3 ,1.107229627521416), 0.00457936709638254, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4102535575832019, 0.3 ,-0.16321848116031135), 0.003814408321557444, material));
  world.add(make_shared<sphere>(glm::dvec3(0.7270523884384269, 0.3 ,0.29410717217325594), 0.003169600328534809, material));
  world.add(make_shared<sphere>(glm::dvec3(0.18138905828975538, 0.3 ,0.40254970330967726), 0.003814408321557444, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5580464711307328, 0.3 ,-1.5308279396480393), 0.007828763980416925, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.03029157803116156, 0.3 ,-1.6319794907421108), 0.004939230713864851, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.18671304250650866, 0.3 ,-1.6209503195274577), 0.005531443136977438, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.5011177610972315, 0.3 ,-1.554620743147633), 0.0038092791489541507, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6019195952700533, 0.3 ,-1.5177236342920852), 0.00447442279103037, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.771040239041985, 0.3 ,-1.4404692311805487), 0.003353239189047714, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8422070636865184, 0.3 ,-1.3990914115971225), 0.00417516937177424, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.936828229501347, 0.3 ,-1.3385796465866069), 0.003356928142155005, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9926415945348631, 0.3 ,-1.2962815042146374), 0.004507850643207951, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0451837246236488, 0.3 ,-1.2551479339566276), 0.0038580468968871582, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.091611430841795, 0.3 ,-1.1812184040331322), 0.004081336196722243, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.093886136410813, 0.3 ,-1.21033910747296), 0.005787049439513466, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.118619693603304, 0.3 ,-1.188204403055825), 0.005286919201059217, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1664030593300694, 0.3 ,-1.1351472241991727), 0.009607945212395604, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.218998040367269, 0.3 ,-1.0516540554799012), 0.027251849303264918, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.130921296981501, 0.3 ,-1.0913633274613426), 0.009181646810636728, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.068541563147418, 0.3 ,-1.1483471884437468), 0.003951447910829487, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0434211361628112, 0.3 ,-1.1366377888445265), 0.005385435001540765, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0706602159632448, 0.3 ,-1.1218780914145248), 0.0049496995701205845, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9311624770626715, 0.3 ,-1.1835302797093497), 0.0040650869827611276, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9873308725898806, 0.3 ,-1.1607712757701811), 0.003529073475913306, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.7761244441330739, 0.3 ,-1.2252665926523914), 0.0035949185735735696, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.5545387490314742, 0.3 ,-1.2418713112284603), 0.0035730813884496215, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.2406343742853504, 0.3 ,-1.1798101152978637), 0.003874422234206629, material));
  world.add(make_shared<sphere>(glm::dvec3(0.14862700244958693, 0.3 ,-0.9187587339750587), 0.004362727247752719, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.14261634378846622, 0.3 ,-1.1366202770504334), 0.0032901120673101514, material));
  world.add(make_shared<sphere>(glm::dvec3(0.23388187825796913, 0.3 ,-0.8112638171997173), 0.0037322995158477284, material));
  world.add(make_shared<sphere>(glm::dvec3(0.41044207119676457, 0.3 ,-0.32184903208882065), 0.004568462775808859, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6641951226755, 0.3 ,-0.7337073385770772), 0.003226521103451741, material));
  world.add(make_shared<sphere>(glm::dvec3(0.7904100732877842, 0.3 ,-1.425546024603139), 0.007190756939339108, material));
  world.add(make_shared<sphere>(glm::dvec3(1.1614126218010545, 0.3 ,-1.1493410268536086), 0.0032279513575031943, material));
  world.add(make_shared<sphere>(glm::dvec3(1.228606456151701, 0.3 ,-1.077022337362633), 0.003354376665911525, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5150464714555811, 0.3 ,-0.6099584614001771), 0.003977505453067519, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5228412861900358, 0.3 ,-0.5702018833937552), 0.011107644196381288, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4945044538965875, 0.3 ,-0.5984472445016813), 0.0038722729648306017, material));
  world.add(make_shared<sphere>(glm::dvec3(0.7641072348690988, 0.3 ,-0.7904389408855059), 0.0035392247318332863, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5362772241928835, 0.3 ,0.5554266994944523), 0.003600566353642406, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6266535959855073, 0.3 ,-0.1526385755225858), 0.0034004291633594817, material));
  world.add(make_shared<sphere>(glm::dvec3(1.616761787927203, 0.3 ,-0.1863185982953672), 0.009737595422777344, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6064901438747916, 0.3 ,-0.15314324751466069), 0.003323220509013126, material));
  world.add(make_shared<sphere>(glm::dvec3(0.844552597240838, 0.3 ,0.34163834694164913), 0.0035101019495002005, material));
  world.add(make_shared<sphere>(glm::dvec3(1.4903700031839433, 0.3 ,0.6689123871588767), 0.003600566353642406, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0630324621586724, 0.3 ,1.2406701578046513), 0.0034004291633594817, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0325060625605622, 0.3 ,1.2580002105516526), 0.009737595422777344, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0481890983605857, 0.3 ,1.2270138755141315), 0.003323220509013126, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.663240709814308, 0.3 ,1.4882747748966065), 0.007828763980416925, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1564361807923476, 0.3 ,1.1519244756740405), 0.004939230713864851, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.261195871864376, 0.3 ,1.03524232497057), 0.005531443136977438, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4410573911016678, 0.3 ,0.7689722108524215), 0.0038092791489541507, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4878553078940668, 0.3 ,0.6723680629166573), 0.00447442279103037, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5556982092791496, 0.3 ,0.4992571860729241), 0.003353239189047714, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5780806654617279, 0.3 ,0.4200368191291937), 0.00417516937177424, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6040176977546539, 0.3 ,0.31075686176883893), 0.003356928142155005, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.61472498329756, 0.3 ,0.241549791315116), 0.004507850643207951, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6238907591567222, 0.3 ,0.1754541440353058), 0.0038580468968871582, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6058597916287973, 0.3 ,0.09003756772019933), 0.004081336196722243, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.62774144720593, 0.3 ,0.10938654194261843), 0.005787049439513466, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6301291263057833, 0.3 ,0.07628075725860473), 0.005286919201059217, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6275844295250583, 0.3 ,0.004923635773088242), 0.009607945212395604, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6073368929387937, 0.3 ,-0.09165471850609799), 0.027251849303264918, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5716403438920639, 0.3 ,-0.0018766844838892516), 0.009181646810636728, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5664239999119334, 0.3 ,0.08245113631775364), 0.003951447910829487, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.540227515054947, 0.3 ,0.09150044966191745), 0.005385435001540765, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5495436493724113, 0.3 ,0.06195344003355491), 0.0049496995701205845, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.492144480683707, 0.3 ,0.2032543491380569), 0.0040650869827611276, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5166918939768763, 0.3 ,0.14784419287570355), 0.003529073475913306, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4097288427254155, 0.3 ,0.34104540143350276), 0.0035949185735735696, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2620088639444993, 0.3 ,0.5070416207326638), 0.0035730813884496215, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.9932408932799882, 0.3 ,0.6806829938842585), 0.003874422234206629, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.5319584481998372, 0.3 ,0.7636935291734686), 0.004362727247752719, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.8927618951351806, 0.3 ,0.7177891572825819), 0.0032901120673101514, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.395943665041335, 0.3 ,0.7457065965837844), 0.0037322995158477284, material));
  world.add(make_shared<sphere>(glm::dvec3(0.07123371009295765, 0.3 ,0.5166964793872655), 0.004568462775808859, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.03273343567007614, 0.3 ,0.9891461680949978), 0.003226521103451741, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.42303016022569084, 0.3 ,1.574158516718075), 0.007190756939339108, material));
  world.add(make_shared<sphere>(glm::dvec3(0.03566458587181609, 0.3 ,1.63358260011617), 0.0032279513575031943, material));
  world.add(make_shared<sphere>(glm::dvec3(0.1342410688980662, 0.3 ,1.6283213057307895), 0.003354376665911525, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6648546808623986, 0.3 ,1.4917718956459272), 0.003977505453067519, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6980987046087247, 0.3 ,1.4686163451951404), 0.011107644196381288, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6580934934931767, 0.3 ,1.469215988542986), 0.0038722729648306017, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.0003653072068903196, 0.3 ,1.0993877624378716), 0.0035392247318332863, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4100866765166594, 0.3 ,-0.17017777295380215), 0.00314688405538798, material));
  world.add(make_shared<sphere>(glm::dvec3(0.1764305354041018, 0.3 ,0.4074356671193848), 0.00314688405538798, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5717144114811957, 0.3 ,-1.5274654450390823), 0.006246709845322481, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.03906031672305266, 0.3 ,-1.6328591767581477), 0.0038735228702018406, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.17718078449429953, 0.3 ,-1.6232779295284954), 0.004280881313847517, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.5951617216838883, 0.3 ,-1.521619560397843), 0.003326032043664565, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0889877934185415, 0.3 ,-1.218036736189813), 0.0033369437615174864, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1577923309169522, 0.3 ,-1.1257010691971319), 0.0031738577952805306, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1609077597966202, 0.3 ,-1.14809835402333), 0.004460817373009744, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1790911069664047, 0.3 ,-1.1299121549377613), 0.004117669636990835, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2146462593583833, 0.3 ,-1.086293741648943), 0.0076601236550056274, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2544148309934142, 0.3 ,-1.0167374462930001), 0.022482632249948974, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1843788980206058, 0.3 ,-1.052813169066593), 0.007386692252715715, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1380745908497882, 0.3 ,-1.1013403151434795), 0.0030947490927051963, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.117736039202724, 0.3 ,-1.093752552318627), 0.00421833147708711, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1381568003004046, 0.3 ,-1.0804526161726773), 0.003910187633109828, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.0350977670202821, 0.3 ,-1.1382252741394816), 0.003087969476265296, material));
  world.add(make_shared<sphere>(glm::dvec3(0.15319868149452065, 0.3 ,-0.9124098940928911), 0.003460828027139072, material));
  world.add(make_shared<sphere>(glm::dvec3(0.2294492753479539, 0.3 ,-0.8163443045695828), 0.003010053224349094, material));
  world.add(make_shared<sphere>(glm::dvec3(0.4102260602089255, 0.3 ,-0.3135789710718101), 0.003704418824452663, material));
  world.add(make_shared<sphere>(glm::dvec3(0.7797755105092564, 0.3 ,-1.43298725245684), 0.005788680546975698, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5261436587129924, 0.3 ,-0.5840406315836967), 0.0031196751486317897, material));
  world.add(make_shared<sphere>(glm::dvec3(1.531687464481061, 0.3 ,-0.5520873390987827), 0.00905151216917943, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5097078878268575, 0.3 ,-0.5755011368144032), 0.003054567473487983, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6163330167298438, 0.3 ,-0.20408451829861013), 0.008033497911660777, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0198457967890309, 0.3 ,1.270471354400374), 0.008033497911660777, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6510790407406805, 0.3 ,1.4953608717603706), 0.006246709845322481, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1633503297991368, 0.3 ,1.146460121252392), 0.0038735228702018406, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2559628755838737, 0.3 ,1.0435427744196364), 0.004280881313847517, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4857068013750756, 0.3 ,0.6798667971675807), 0.003326032043664565, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.629572682784374, 0.3 ,0.1183248766974091), 0.0033369437615174864, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6148278534373484, 0.3 ,0.004120981024448078), 0.0031738577952805306, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6326391969924003, 0.3 ,0.018052969592273482), 0.004460817373009744, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.633064184444644, 0.3 ,-0.007660671479000236), 0.004117669636990835, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6282929367286867, 0.3 ,-0.06373178734701135), 0.0076601236550056274, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.60851628893011, 0.3 ,-0.1413752140835019), 0.022482632249948974, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.583260279667254, 0.3 ,-0.0667520027004252), 0.007386692252715715, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5837184601993362, 0.3 ,0.0003208147410461437), 0.0030947490927051963, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5638245929046857, 0.3 ,0.009007866706433942), 0.00421833147708711, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5692549868507628, 0.3 ,-0.014749376544526155), 0.003910187633109828, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5353488221752603, 0.3 ,0.09842843199663787), 0.003087969476265296, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.5242584048179526, 0.3 ,0.7623088454347098), 0.003460828027139072, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.4026619017653559, 0.3 ,0.74627634722508), 0.003010053224349094, material));
  world.add(make_shared<sphere>(glm::dvec3(0.07682836600818688, 0.3 ,0.510602187372426), 0.003704418824452663, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.43584740435564095, 0.3 ,1.5721130215764505), 0.005788680546975698, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6908506376668301, 0.3 ,1.48085898140434), 0.0031196751486317897, material));
  world.add(make_shared<sphere>(glm::dvec3(0.717051369254912, 0.3 ,1.4617469865511112), 0.00905151216917943, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6849746699851015, 0.3 ,1.463293943990785), 0.003054567473487983, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5826782316419553, 0.3 ,-1.5245451757814112), 0.005099361062916003, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.04602896778779575, 0.3 ,-1.633432727729143), 0.0031186912554151134, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.16967412625287104, 0.3 ,-1.624954595294918), 0.0034107456951733804, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2107425537502015, 0.3 ,-1.0967906291112952), 0.00353914256527146, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2245837968979947, 0.3 ,-1.0816849661101182), 0.0032941204685500085, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2518973322859925, 0.3 ,-1.045354660501303), 0.0062451025856721885, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.282780923787472, 0.3 ,-0.9866704960095707), 0.018853268850031, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2259660761997941, 0.3 ,-1.019076927148714), 0.006062153963679718, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1739280508814236, 0.3 ,-1.0554216701357326), 0.0033847739313398895, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1896506248593148, 0.3 ,-1.04367855243863), 0.00315998138411487, material));
  world.add(make_shared<sphere>(glm::dvec3(0.410066034555007, 0.3 ,-0.30681212795702034), 0.0030643162087783944, material));
  world.add(make_shared<sphere>(glm::dvec3(0.7710272996094186, 0.3 ,-1.4388808423938286), 0.0047595703171921955, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5386493617268275, 0.3 ,-0.5370530458562299), 0.0075164685938370465, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6157064473529537, 0.3 ,-0.21884442409168797), 0.006739701071788505, material));
  world.add(make_shared<sphere>(glm::dvec3(1.0091333508919882, 0.3 ,1.2806444026705597), 0.006739701071788505, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6411684234578862, 0.3 ,1.5008847282147648), 0.005099361062916003, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.1687578197372366, 0.3 ,1.142027276686222), 0.0031186912554151134, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.251733198046626, 0.3 ,1.0499670217667427), 0.0034107456951733804, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6327853046588223, 0.3 ,-0.053473025518558176), 0.00353914256527146, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6322312048810574, 0.3 ,-0.07395360265929682), 0.0032941204685500085, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.626603487426323, 0.3 ,-0.11905625354891736), 0.0062451025856721885, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6079998114505063, 0.3 ,-0.18270788845572694), 0.018853268850031, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.589695314020577, 0.3 ,-0.11991418606906402), 0.006062153963679718, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5775623421937053, 0.3 ,-0.057610996612374454), 0.0033847739313398895, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5806983211435295, 0.3 ,-0.0769827745835498), 0.00315998138411487, material));
  world.add(make_shared<sphere>(glm::dvec3(0.08141812116352509, 0.3 ,0.5056272580700003), 0.0030643162087783944, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.4462328090124862, 0.3 ,1.5702666829273955), 0.0047595703171921955, material));
  world.add(make_shared<sphere>(glm::dvec3(0.7325081050378043, 0.3 ,1.45578147689128), 0.0075164685938370465, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5916654140778156, 0.3 ,-1.5220007770812292), 0.004241057176162887, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2814104381011677, 0.3 ,-1.0106708957450263), 0.005186228201239196, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.305937754402962, 0.3 ,-0.9605817683845621), 0.016030258971081984, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2590468310578602, 0.3 ,-0.9895876815494735), 0.005059429223838272, material));
  world.add(make_shared<sphere>(glm::dvec3(0.763707108833895, 0.3 ,-1.4436590906826163), 0.003982102846416672, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5442560118860014, 0.3 ,-0.5243809478568378), 0.006340536627839049, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6149861562174492, 0.3 ,-0.23129784819913982), 0.005734536031936448, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9999571667922652, 0.3 ,1.2890945054325353), 0.005734536031936448, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.632939845539219, 0.3 ,1.5053044474725161), 0.004241057176162887, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6237014993829542, 0.3 ,-0.16450474547024108), 0.005186228201239196, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6065051101107488, 0.3 ,-0.21755937882775106), 0.016030258971081984, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5929691598311857, 0.3 ,-0.16410959173074036), 0.005059429223838272, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.45481636216960686, 0.3 ,1.56861155003296), 0.003982102846416672, material));
  world.add(make_shared<sphere>(glm::dvec3(0.7453483967782809, 0.3 ,1.4505715343068548), 0.006340536627839049, material));
  world.add(make_shared<sphere>(glm::dvec3(0.5991647084448996, 0.3 ,-1.5197722475765942), 0.0035823538290960053, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3052993132063149, 0.3 ,-0.9809760143387809), 0.004373977726298789, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3251528931987688, 0.3 ,-0.9377739363963229), 0.013792865596036418, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.2858712406840134, 0.3 ,-0.9637410996721714), 0.004283439535532087, material));
  world.add(make_shared<sphere>(glm::dvec3(0.7574932092996255, 0.3 ,-1.447608220204511), 0.0033805170271535433, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5488586291441795, 0.3 ,-0.513558445968313), 0.0054200174727294555, material));
  world.add(make_shared<sphere>(glm::dvec3(1.614230787880301, 0.3 ,-0.24194386110215557), 0.00493824111630119, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9920124072263513, 0.3 ,1.2962211433141573), 0.00493824111630119, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6260003011059351, 0.3 ,1.508916715847884), 0.0035823538290960053, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6202257094998278, 0.3 ,-0.20245712642596847), 0.004373977726298789, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.604458421518506, 0.3 ,-0.24731219087555997), 0.013792865596036418, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5942788872423233, 0.3 ,-0.20133699240068037), 0.004283439535532087, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.4620283082460148, 0.3 ,1.5671296575963523), 0.0033805170271535433, material));
  world.add(make_shared<sphere>(glm::dvec3(0.7561810737574964, 0.3 ,1.445992916369489), 0.0054200174727294555, material));
  world.add(make_shared<sphere>(glm::dvec3(0.6055164012407687, 0.3 ,-1.5178088225598891), 0.003065881964655587, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.324988055292569, 0.3 ,-0.9553037166772076), 0.003737689678438318, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.341323106494208, 0.3 ,-0.9176913644169007), 0.011990568917787799, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3079867584567797, 0.3 ,-0.9409869718145691), 0.003671377261271171, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5526986544353294, 0.3 ,-0.5042103438866112), 0.0046860602415267115, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6134736185489817, 0.3 ,-0.25114779395786835), 0.004296783811047891, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9850689861832281, 0.3 ,1.3023100339870697), 0.004296783811047891, material));
  world.add(make_shared<sphere>(glm::dvec3(-0.6200699141303029, 0.3 ,1.5119216367268045), 0.003065881964655587, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6165278502107574, 0.3 ,-0.23459805467705785), 0.003737689678438318, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6021179804560925, 0.3 ,-0.2729891811774242), 0.011990568917787799, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5943541848359306, 0.3 ,-0.23306774705905633), 0.003671377261271171, material));
  world.add(make_shared<sphere>(glm::dvec3(0.7654405338588414, 0.3 ,1.441943817037763), 0.0046860602415267115, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3414667187908695, 0.3 ,-0.9329114526240143), 0.0032301968160400006, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3550982673131249, 0.3 ,-0.8998901954050194), 0.010518022192643433, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3264850586887573, 0.3 ,-0.920852879606691), 0.003180549728248407, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5559470474033321, 0.3 ,-0.49605597260061646), 0.004091515046924248, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6127333605230083, 0.3 ,-0.25918306981001904), 0.003772518511035105, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9789502506691116, 0.3 ,1.3075707103384022), 0.003772518511035105, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.6128032513382298, 0.3 ,-0.26214959190017695), 0.0032301968160400006, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5996422832920847, 0.3 ,-0.2953612082945342), 0.010518022192643433, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5936512358616235, 0.3 ,-0.26040041328917796), 0.003180549728248407, material));
  world.add(make_shared<sphere>(glm::dvec3(0.7734447946790696, 0.3 ,1.438341368333592), 0.004091515046924248, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3669594190262515, 0.3 ,-0.884013840244831), 0.00929978730119928, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5587279721691734, 0.3 ,-0.4888813335677261), 0.0036032226227785645, material));
  world.add(make_shared<sphere>(glm::dvec3(1.6120201924895348, 0.3 ,-0.26625830738494227), 0.0033385710950360192, material));
  world.add(make_shared<sphere>(glm::dvec3(0.9735184705638978, 0.3 ,1.3121601939993583), 0.0033385710950360192, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5971291547309336, 0.3 ,-0.31501902500874157), 0.00929978730119928, material));
  world.add(make_shared<sphere>(glm::dvec3(0.7804318856490037, 0.3 ,1.4351180862200614), 0.0036032226227785645, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3772693859780387, 0.3 ,-0.8697737745656762), 0.008280738546840555, material));
  world.add(make_shared<sphere>(glm::dvec3(1.5611336120356927, 0.3 ,-0.482520496844506), 0.003197317575386209, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5946387728326035, 0.3 ,-0.3324222685884329), 0.008280738546840555, material));
  world.add(make_shared<sphere>(glm::dvec3(0.7865834293983843, 0.3 ,1.4322188007069891), 0.003197317575386209, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3863064412718094, 0.3 ,-0.8569347534869558), 0.007419861143696778, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.592207588009395, 0.3 ,-0.3479334958447754), 0.007419861143696778, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.3942872280686158, 0.3 ,-0.845303485007578), 0.0066861434052694225, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5898569226727468, 0.3 ,-0.3618422605926075), 0.0066861434052694225, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.401382693616891, 0.3 ,-0.8347199431517429), 0.006055794813109371, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5875983841200045, 0.3 ,-0.37438243575752284), 0.006055794813109371, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.407729377003848, 0.3 ,-0.825050676688915), 0.005510323980308291, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5854373253687908, 0.3 ,-0.38574487075259556), 0.005510323980308291, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4134375435757494, 0.3 ,-0.8161836239166227), 0.005035186461542984, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5833750866528253, 0.3 ,-0.3960867739603019), 0.005035186461542984, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4185971390709233, 0.3 ,-0.8080240669323522), 0.004618817674222954, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5814104620872826, 0.3 ,-0.4055387603213718), 0.004618817674222954, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4232822103997194, 0.3 ,-0.8004914521957043), 0.004251930779356219, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5795406665410607, 0.3 ,-0.4142102101852646), 0.004251930779356219, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4275542311086138, 0.3 ,-0.7935168736751421), 0.003926999864481934, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.577761975925048, 0.3 ,-0.4221933903892449), 0.003926999864481934, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4314646331390506, 0.3 ,-0.7870410661694403), 0.0036378746811103983, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.576070151713189, 0.3 ,-0.4295666568110364), 0.0036378746811103983, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.4350567557909686, 0.3 ,-0.7810127941908804), 0.00337949008024513, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5744607216010806, 0.3 ,-0.43639696741218426), 0.00337949008024513, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.438367361498444, 0.3 ,-0.7753875497003524), 0.00314764449233604, material));
  world.add(make_shared<sphere>(glm::dvec3(-1.5729291635458105, 0.3 ,-0.4427418721121714), 0.00314764449233604, material));



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



void rtiow::one_thread_sample(int index, int count)
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
            if(x_coord % count == index)
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
   
    int num_threads = 16;

    // launch all the threads
    std::thread t0(&rtiow::one_thread_sample, this, 0, num_threads);
    std::thread t1(&rtiow::one_thread_sample, this, 1, num_threads);
    std::thread t2(&rtiow::one_thread_sample, this, 2, num_threads);
    std::thread t3(&rtiow::one_thread_sample, this, 3, num_threads);
    std::thread t4(&rtiow::one_thread_sample, this, 4, num_threads);
    std::thread t5(&rtiow::one_thread_sample, this, 5, num_threads);
    std::thread t6(&rtiow::one_thread_sample, this, 6, num_threads);
    std::thread t7(&rtiow::one_thread_sample, this, 7, num_threads);
    std::thread t8(&rtiow::one_thread_sample, this, 8, num_threads);
    std::thread t9(&rtiow::one_thread_sample, this, 9, num_threads);
    std::thread t10(&rtiow::one_thread_sample, this, 10, num_threads);
    std::thread t11(&rtiow::one_thread_sample, this, 11, num_threads);
    std::thread t12(&rtiow::one_thread_sample, this, 12, num_threads);
    std::thread t13(&rtiow::one_thread_sample, this, 13, num_threads);
    std::thread t14(&rtiow::one_thread_sample, this, 14, num_threads);
    std::thread t15(&rtiow::one_thread_sample, this, 15, num_threads);


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

