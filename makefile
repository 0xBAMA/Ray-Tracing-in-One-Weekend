FLAGS =  -Wall -O3 -std=c++17 -lGLEW -lGL -lstdc++fs $(shell pkg-config sdl2 --cflags --libs)
IMGUI_FLAGS   =  -Wall -lGLEW -DIMGUI_IMPL_OPENGL_LOADER_GLEW `sdl2-config --cflags`

all: msg main clean run

msg:
		@echo
		@echo 'Compiling starts on '
		@date
		@echo

main: resources/imgui/imgui.o lodepng.o perlin.o rtiow.o utils.o
		g++ -o main resources/code/main.cc *.o resources/imgui/*.o          ${FLAGS}

resources/imgui/imgui.o: resources/imgui/*.cc
		g++ -c -o resources/imgui/imgui_impl_sdl.o resources/imgui/imgui_impl_sdl.cc         ${IMGUI_FLAGS}
		g++ -c -o resources/imgui/imgui_impl_opengl3.o resources/imgui/imgui_impl_opengl3.cc ${IMGUI_FLAGS}
		g++ -c -o resources/imgui/imgui.o resources/imgui/imgui.cc                           ${IMGUI_FLAGS}
		g++ -c -o resources/imgui/imgui_demo.o resources/imgui/imgui_demo.cc                 ${IMGUI_FLAGS}
		g++ -c -o resources/imgui/imgui_draw.o resources/imgui/imgui_draw.cc                 ${IMGUI_FLAGS}
		g++ -c -o resources/imgui/imgui_widgets.o resources/imgui/imgui_widgets.cc           ${IMGUI_FLAGS}
		@echo


utils.o: resources/code/rtiow.h resources/code/rtiow_utils.cc
		g++ -c -o utils.o resources/code/rtiow_utils.cc               ${FLAGS}

rtiow.o: resources/code/rtiow.h resources/code/rtiow.cc
		g++ -c -o rtiow.o resources/code/rtiow.cc                  ${FLAGS}

debug.o: resources/code/debug.cc
		g++ -c -o debug.o resources/code/debug.cc                        ${FLAGS}

perlin.o: resources/code/perlin.cc
		g++ -c -o perlin.o resources/code/perlin.cc                      ${FLAGS}

lodepng.o: resources/code/lodepng.h resources/code/lodepng.cc
		g++ -c -o lodepng.o resources/code/lodepng.cc                    ${FLAGS}


clean:
		@echo
		@echo 'Compiling ends on '
		@date
		@echo
		@rm *.o
		@echo 'executable size:'
		@stat --printf "%s bytes\n" main
		@echo

run:
		@./main
