#include <stdio.h>
#include <stdlib.h>

#define MEMORY_ADDRESSABLE_SIZE (size_t) 0x100000 // PCjr memory space is 0:0000 - F:FFFF

unsigned char *pcjr_memory; // PCjr Memory space
char *system_rom_file_name; // System ROM, loads at top of memory

// Allocate some memory
int allocateMemory(unsigned char **memory, size_t memory_size);
int allocateMemory(unsigned char **memory, size_t memory_size){
	int rc; // Return code
	rc = 0; // Assume success
	*memory = (unsigned char *)calloc(memory_size,(size_t)1); // Allocate zero'd out memory
	if ( *memory == NULL ){ // If memory allocation failed, note it failed
		rc = 1; // Return error code
		return rc;
	}
	return rc;
}

// Free memory - in C this returns no value so hard code 0
int freeMemory(unsigned char **memory);
int freeMemory(unsigned char **memory){
		free(*memory);
		return 0;
}

// Function to get the file size of an open file
size_t getFileSize(char *file_name);
size_t getFileSize(char *file_name){
	size_t file_size;
	FILE *fp; // File pointer
	file_size = 0;

	// Attempt to open file
	fp = fopen(file_name,"rb");
	if ( fp == NULL ){ // File failed to open
		return file_size; // failed to open, return 0 size
	}

	while (1){ // Attempt to read all characters in the file until end of file is reached
		fgetc(fp);
		if ( feof(fp) ){ // Are we at the end of the file?
			break;
		}
		++file_size;
	}
	fclose(fp); // Close the file

	return file_size;
}

int loadMemory(char *file_name, size_t file_size, size_t load_address, unsigned char *memory);
int loadMemory(char *file_name, size_t file_size, size_t load_address, unsigned char *memory){
	int rc;
	unsigned char c;
	FILE *fp; // File pointer
	size_t index;
	size_t effective_address;

	rc = 0;

	fprintf(stderr,"FILE: Opening %s\n",file_name);
	fp = fopen(file_name,"rb"); // Open the file
	if (fp == NULL){
		fprintf(stderr,"ERROR: Failed opening %s\n",file_name);
		rc = 3;
		return rc;
	}

	// Reading file data and saving it into memory
	for (index = 0; index < file_size; ++index){ // For each byte of the file
		effective_address = load_address + index; // Effective address for this byte is the base load address + current index
		c = (unsigned char)fgetc(fp); // Read the byte in and load it into memory
		memory[effective_address] = c; // Save the value in memory
	}
	fclose(fp); // Close file

	return rc;
}

// This is just a debug function to allow for hexdumping of a chunk of memory
void hexDump(size_t load_address, size_t length, unsigned char *memory);
void hexDump(size_t load_address, size_t length, unsigned char *memory){
	// TODO - doesn't handle an unaligned last-line for the ASCII print'
	size_t index;
	size_t effective_address;
	size_t sub_index;
	char c;

	// Goal is to mimic hexdump -C output here:
	// 0FFFCF  30 31 32 33 34 35 36 37  38 39 41 42 43 44 45 46 | 0123456789ABCDEF
	for (index = 0; index < length; ++index){
		// For the length requested
		effective_address = load_address + index;
		// Each memory address after the load_address
		if ( index % 16 == 0 ){
			if ( index != 0 ){
				// Print ASCII representation of the last 16 chararacters
				fprintf(stderr," | ");
				for ( sub_index = 0; sub_index < 16; ++sub_index){
					c = memory[effective_address - ( 16 - sub_index )];
					if ( c < 32 || c > 126 ){
						c = '.';
					}
					fprintf(stderr,"%c",c);
				}
			}
			// Start a new line with the current effective address
			fprintf(stderr,"\n%06lX", effective_address);
		}
		if ( index % 8 == 0 ){
			// Add an extra character in the middle for readability
			fprintf(stderr," ");
		}
		// Ensure each character is separated by a space
		fprintf(stderr," ");

		// Now, print the actual current cell, todo would save the current char version in a buffer
		fprintf(stderr,"%02X",memory[effective_address]);
	}
	// TODO - here, i'd then calculate the %16 final offset, space over as much as needed ,and print the final part of the buffer'
	fprintf(stderr,"\n");
}

// --- MAIN ---
int main(int argc, char **argv){
	int rc; // Return code
	size_t load_address;
	size_t file_size;

	fprintf(stderr,"PCjrBE\n");
	rc = 0; // Assume success

	fprintf(stderr,"INFO: Processing Arguments\n");
	if (argc != 2){
		fprintf(stderr,"ERROR: Expecting $1 = SYSTEM.ROM, exiting\n");
		rc = 1;
		return rc;
	}
	else {
		system_rom_file_name=argv[1];
		fprintf(stderr,"INFO: SYSTEM.ROM=%s\n",system_rom_file_name);
	}

	fprintf(stderr,"ALLOC: Main Memory (0x%06lX)\n",MEMORY_ADDRESSABLE_SIZE);
	rc = allocateMemory(&pcjr_memory,MEMORY_ADDRESSABLE_SIZE); // Allocate the main memory
	if (rc != 0){ // Check if the allocation failed
		fprintf(stderr,"ERROR: Unable to allocate memory 0x%06lX, exiting\n",MEMORY_ADDRESSABLE_SIZE);
		return rc;
	}

	fprintf(stderr,"FILE: Getting size of SYSTEM.ROM=%s\n",system_rom_file_name);
	file_size = getFileSize(system_rom_file_name);
	if ( file_size == 0 ){
			rc = 2;
			fprintf(stderr,"FILE: Failed to get size of SYSTEM.ROM=%s, exiting\n",system_rom_file_name);
			freeMemory(&pcjr_memory);
			return rc;
	}
	load_address = MEMORY_ADDRESSABLE_SIZE - file_size; // Calculate load address so that it winds up at at end of memory
	fprintf(stderr,"FILE: %s, size=0x%06lx, loading at memory address: 0x%06lX\n",system_rom_file_name,file_size,load_address);

	rc = loadMemory(system_rom_file_name, file_size, load_address, pcjr_memory);
	hexDump(load_address,file_size,pcjr_memory);

	// EXITING
	fprintf(stderr,"FREE: Main Memory\n");
	rc = freeMemory(&pcjr_memory);
	if ( rc != 0 ){
		fprintf(stderr,"ERROR: Unable to free memory. Hard to imagine the world where it came to this...and yet here we are. Grab a shovel, we've got work to do.\n");
		return rc;
	}
	return rc;
}
