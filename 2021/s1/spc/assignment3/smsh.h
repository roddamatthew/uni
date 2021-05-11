#define	YES	1
#define	NO	0

char	*next_cmd();
char	**splitline(char *);
char	***splitPipes(char **);
void 	printCommands(char ***);
void	freelist(char **);
void	*emalloc(size_t);
void	*erealloc(void *, size_t);
int		execute(char **);
int 	pipeline(char ***);
int 	nCommands(char ***);
void	fatal(char *, char *, int );

int	process();
