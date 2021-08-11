#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

// int		main(void)
// {
// 	char src[] = "Append this";
// 	char dst[18] = "to This";
// 	char srcn[] = "Append this";
// 	char dstn[18] = "to This";
// 	int num = ft_strlcat(dst, src, 20);
// 	int numn = 	ft_strlcatnils(dstn, srcn, 20);

// 	printf("%s \n%s", dst, dstn);
// 	printf("\n %d - %d", num, numn);
// }

int	main(void)
{
	int		fd;
	int		i;

	i = 0;
	//fd = open("test.txt", O_RDONLY);
	// fd = open("test.txt", O_RDONLY);
	while (i < 10)
	{
		printf("%s", get_next_line(0));
		// get_next_line(fd);
		i++;
	}
    // fscanf(stdin, "c");
}
