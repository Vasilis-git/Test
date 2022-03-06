#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
	FILE *src, *dest;
	unsigned char* filename;
	unsigned char read;

	if(argc < 2 || argc > 3){
		printf("\nInvalid arguement count.Needs:\n%s [input file name] [output file name]\nOr:\n%s [input file name]\n", argv[0], argv[0]);
		exit(1);
	}
	src = fopen(argv[1], "rb");
	if(src == NULL){
		printf("\n\tDisk is full or file %s does not exist.\n", argv[1]);
		exit(1);
	}
	filename = (unsigned char*)malloc((strlen(argv[1])+8)*sizeof(char));
	if(filename == NULL){
		puts("\n\tMemory error.");
		exit(1);
	}
	if(argc == 2){
		strncpy((char *)filename, argv[1], strlen(argv[1])+1);
		strcat((char *)filename, "(copy)");
		dest = fopen((char*)filename, "wb");
		if(dest == NULL){
			puts("\n\tDisk is full.");
			exit(1);
		}
	}
	else{/*argc is 3*/
		dest = fopen(argv[2], "wb");
		if(dest == NULL){
			puts("\n\tDisk is full.");
			exit(1);
		}
	}

	while(feof(src) == 0){
		fread(&read, sizeof(unsigned char), 1, src);
		fwrite(&read, sizeof(unsigned char), 1, dest);
	}
	
	fclose(dest);
	fclose(src);
	free(filename);
	return 0;
}
