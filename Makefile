CC := g++
CFLAGS := -Iinclude/ -lglfw -lGL
GLAD_PATH := src/glad.c
UTILS_PATH := src/utils/*.cpp

shaders-exercises: src/chapterShaders/exercises.cpp
	$(CC) src/chapterShaders/exercises.cpp $(GLAD_PATH) $(UTILS_PATH) $(CFLAGS) -o bin/shaders-exercises

shaders: src/chapterShaders/shaders.cpp
	$(CC) src/chapterShaders/shaders.cpp $(GLAD_PATH) $(UTILS_PATH) $(CFLAGS) -o bin/shaders

triangle-exercises: src/triangle/exercises.cpp
	$(CC) src/triangle/exercises.cpp $(GLAD_PATH) $(UTILS_PATH) $(CFLAGS) -o bin/triangle-exercises

triangle: src/triangle/triangle.cpp
	$(CC) src/triangle/triangle.cpp $(GLAD_PATH) $(UTILS_PATH) $(CFLAGS) -o bin/triangle
