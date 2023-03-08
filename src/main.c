/*

Copy files.

Usage: copy src_file dest_file [block_size (optional)]

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BLCK_SIZE_DEFAULT 1000000

int main(int argc, char **argv) {

    // File descriptors (file offset & status flags)
    int file_src;
    int file_dest;

    char *buff;
    ssize_t block_size, p_pod;

    // Check for number of arguments
    if(!((argc == 4) || (argc == 3))){
        printf("Usage: copy src_file dest_file [block_size (optional)]\n");
        return 1;
    }

    // Check validity of source file
    file_src = open(argv[1], O_RDONLY);
    if (file_src == -1) {  // If source file can't be opened (read)
        printf("Invalid source file\n");
        return 1;
    }


    // Try to create destination file, in mode 
    file_dest = creat(argv[2], 0644); // Flags rw-r--r--
    if (file_dest == -1) {  // If destination file cannot be created
        printf("Invalid destination file\n");
        return 1;
    }

    // Zagotovimo si pomnilnik
    // Check if block size is given in arguments
    if(argc == 4) {
        sscanf(argv[3], "%ld", &block_size);  // TODO: make this safer
    }
    else block_size = BLCK_SIZE_DEFAULT;
    // Try to allocate memory
    if((buff = malloc(block_size)) == NULL) {
        printf("Error during memory allocation");
        return 2;
    }

    return 0;
}