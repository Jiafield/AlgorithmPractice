.PHONY: all clean
all: ray_trace

ray_trace: ray_trace.c bitmap.c triangle.c main.c
	@gcc -o $@ $^

clean:
	@rm -f ray_trace
