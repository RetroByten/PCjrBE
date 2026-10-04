#include <stdio.h>
#include <stdlib.h>

#define MEMORY_ADDRESSABLE_SIZE (size_t) 0x100000 // PCjr memory space is 0:0000 - F:FFFF

unsigned char *pcjr_memory; // PCjr Memory space

// Allocate some memory
int allocateMemory(unsigned char *memory, size_t size);
int allocateMemory(unsigned char *memory, size_t size){
	int rc;
	rc = 0;
	memory = (unsigned char *)calloc(size,(size_t)1); // Allocate zero'd out memory
	if ( memory == NULL ){
		rc = 1;
		return rc;
	}
	return rc;
}


int main(int argc, char **argv){
	int rc; // Return code
	rc = 0; // Assume success
	fprintf(stderr,"PCjrBE\n");

	fprintf(stderr,"ALLOC: Main Memory\n");
	rc = allocateMemory(pcjr_memory,MEMORY_ADDRESSABLE_SIZE);
	if (rc != 0){
		fprintf(stderr,"ERROR: Unable to allocate memory 0x%06lX, exiting\n",MEMORY_ADDRESSABLE_SIZE);
		return rc;
	}
	else {
		fprintf(stderr,"INFO: Allocated 0x%06lX\n",MEMORY_ADDRESSABLE_SIZE);
	}

	free(pcjr_memory);
	fprintf(stderr,"FREE: Main Memory\n");
	return rc;
}
