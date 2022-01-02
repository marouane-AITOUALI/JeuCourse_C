CFLAGS = -Wall -O3 `sdl2-config --cflags`
LDFLAGS = -m64 `sdl2-config --libs` -lSDL2_ttf -lm

INC = sdl2.h logic.h graphics.h const.h data.h sdl2-ttf.h event.h 
SRC = main.c sdl2.c logic.c graphics.c data.c sdl2-ttf.c event.c 
OBJ = $(SRC:%.c=%.o)
PROG = fastcar

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $<

fastcar: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

doc: $(PROG)
	doxygen ./$(PROG)
	make -C latex

clean:
	rm -f *~ *.o $(PROG)
	rm -rf latex html
