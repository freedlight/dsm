#include <stdio.h>
#include "tsth8.h"

void main(void)
{
	FILE *f;

	if ((f = fopen(OUTNAME, "wb")) == NULL)
	{
		printf("cannot create file\n");
		return;
	}
	fwrite(objcode, 1, sizeof(objcode), f);
	fclose(f);
}

