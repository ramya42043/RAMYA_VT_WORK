source = $(patsubst %.c,%.out, $(wildcard *.c))
all: $(source)
	@echo $(source)
%.out:%.c
	gcc $< -o out/$@
