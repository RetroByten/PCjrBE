#include <stdio.h>
#include <stdlib.h>

#define MEMORY_ADDRESSABLE_SIZE (size_t) 0x100000 // PCjr memory space is 0:0000 - F:FFFF

unsigned char *pcjr_memory; // PCjr Memory space

// Allocate some memory
int allocateMemory(unsigned char *memory, size_t size);
int allocateMemory(unsigned char *memory, size_t size){
	int rc; // Return code
	rc = 0; // Assume success
	memory = (unsigned char *)calloc(size,(size_t)1); // Allocate zero'd out memory
	if ( memory == NULL ){ // If memory allocation failed, note it failed
		rc = 1; // Return error code
		return rc;
	}
	return rc;
}

// Free memory - in C this returns no value so hard code 0
int freeMemory(unsigned char *memory);
int freeMemory(unsigned char *memory){
		free(memory);
		return 0;
}


int main(int argc, char **argv){
	int rc; // Return code

	fprintf(stderr,"PCjrBE\n");
	rc = 0; // Assume success

	fprintf(stderr,"ALLOC: Main Memory (0x%06lX)\n",MEMORY_ADDRESSABLE_SIZE);
	rc = allocateMemory(pcjr_memory,MEMORY_ADDRESSABLE_SIZE); // Allocate the main memory
	if (rc != 0){ // Check if the allocation failed
		fprintf(stderr,"ERROR: Unable to allocate memory 0x%06lX, exiting\n",MEMORY_ADDRESSABLE_SIZE);
		return rc;
	}

	fprintf(stderr,"FREE: Main Memory\n");
	rc = freeMemory(pcjr_memory);
	if ( rc != 0 ){
		fprintf(stderr,"ERROR: Unable to free memory. Hard to imagine the world where it came to this...and yet here we are. Grab a shovel, we've got work to do.\n");
		return rc;
	}
	return rc;
}
