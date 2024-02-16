#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct calculator{
	int num1;
	int num2;
	char data[10];
};


int vulfoo (char *filename){
	FILE *fp;
  	struct calculator calc;	

	fp = fopen(filename, "r");

	if (fp == NULL){
		printf ("\n Can't open file or file doesn't exist. \n");
		exit(0);
	}

	while(fread(&calc, sizeof(calc), 1, fp) > 0){
		int size1 = calc.num1 + calc.num2;
		char* buff1 = (char*) malloc(size1);

		memcpy(buff1, calc.data, sizeof(calc.data));
		free(buff1);
		/* double free error */
		if (size1/2==0){
			free(buff1);	
		} else if (size1/3 == 0){
			/* Use after free vulnerability */
			buff1[0] = 'a';
		}

		int size2 = calc.num1 / calc.num2;
		char* buff2 = (char*) malloc(size2);	
		memcpy(buff2, calc.data, sizeof(calc.data));
		free(buff2);

	}
	fclose(fp);
	return 0;
}

int main(int argc, char **argv){
	
	vulfoo(argv[1]);
}




