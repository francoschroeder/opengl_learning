CC := g++
CFLAGS := -Iinclude/ -lglfw -lGL
GLAD_PATH := src/glad.c include/*/*.cpp
UTILS_PATH := src/utils/*.cpp

transformations: src/transformations/transformations.cpp
	$(CC) src/transformations/transformations.cpp $(GLAD_PATH) $(UTILS_PATH) $(CFLAGS) -o bin/transformations

textures: src/textures/textures.cpp
	$(CC) src/textures/textures.cpp $(GLAD_PATH) $(UTILS_PATH) $(CFLAGS) -o bin/textures

shaders-exercises: src/chapterShaders/exercises.cpp
	$(CC) src/chapterShaders/exercises.cpp $(GLAD_PATH) $(UTILS_PATH) $(CFLAGS) -o bin/shaders-exercises

shaders: src/chapterShaders/shaders.cpp
	$(CC) src/chapterShaders/shaders.cpp $(GLAD_PATH) $(UTILS_PATH) $(CFLAGS) -o bin/shaders

triangle-exercises: src/triangle/exercises.cpp
	$(CC) src/triangle/exercises.cpp $(GLAD_PATH) $(UTILS_PATH) $(CFLAGS) -o bin/triangle-exercises

triangle: src/triangle/triangle.cpp
	$(CC) src/triangle/triangle.cpp $(GLAD_PATH) $(UTILS_PATH) $(CFLAGS) -o bin/triangle
