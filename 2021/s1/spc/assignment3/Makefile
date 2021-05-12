all: part1 part2

part1:
	gcc -o smsh2 smsh2.c splitline.c execute.c pipelinePart1.c

part2:
	gcc -o smsh3 smsh3.c splitline.c execute.c pipelinePart2.c redirect.c

clean:
	$(RM) smsh2
	$(RM) smsh3