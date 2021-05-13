all: part1 part2 part3

part1:
	gcc -o smsh2 smsh2.c splitline.c execute.c pipelinePart1.c

part2:
	gcc -o smsh3 smsh3.c splitline.c execute.c pipelinePart2.c redirect.c

part3:
	gcc -o smsh4 smsh4.c splitline.c execute.c pipelinePart3.c redirect.c glob.c

clean:
	$(RM) smsh2
	$(RM) smsh3