all:
	gcc -Iinclude/ data/src/draw.c  data/src/model.c data/src/main.c -lSOIL -lobj -lopengl32 -lglu32 -lglut32 -lm -o grafika.exe -Wall -Wextra -Wpedantic
linux:
	gcc -Iinclude/ data/src/draw.c  data/src/model.c data/src/main.c -lSOIL -lobj -lGL -lGLU -lglut -lm -o grafika -Wall -Wextra -Wpedantic

