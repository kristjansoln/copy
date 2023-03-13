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
    ssize_t block_size, num_bytes_read, num_bytes_written;

    // Check for number of arguments
    if(!((argc == 4) || (argc == 3))){
        printf("Usage: copy src_file dest_file [block_size (optional)]\n");
        return 1;
    }

    // Check validity of source file
    file_src = open(argv[1], O_RDONLY);
    if (file_src == -1) {  // If source file can't be opened (read)
        printf("Invalid source file\n");
        return 2;
    }


    // Try to create destination file, in mode
    file_dest = creat(argv[2], 0644); // rw-r--r--
    if (file_dest == -1) {  // If destination file cannot be created
        printf("Invalid destination file\n");
        return 3;
    }

    // Check if block size is given in arguments
    if(argc == 4) {
        sscanf(argv[3], "%ld", &block_size);
        // Check if the input is valid
        if(block_size <= 0) {
            printf("Invalid block_size argument, using default value\n");
            block_size = BLCK_SIZE_DEFAULT;
        }
    }
    else block_size = BLCK_SIZE_DEFAULT;

    // Try to allocate memory
    if((buff = malloc(block_size)) == NULL) {
        printf("Error during memory allocation");
        return 5;
    }

    // Copy the files
    while ((num_bytes_read = read(file_src, buff, block_size)) != 0){
        // On end of file, read returns 0
        // On error, read returns -1
        if (num_bytes_read == -1) {
            printf("Error during read\n");
            return 6;
        }
        // Try to write to destination file. Write returns number of bytes written.
        num_bytes_written = write(file_dest, buff, num_bytes_read);
        if(num_bytes_written != num_bytes_read) {
            printf("Error during write\n");
            return 7;
        }
    }

    // Close the files
    if(close(file_src) == -1 || close(file_dest) == -1) {
        printf("Error during closing the files\n");
        return 8;
    }

    return 0;
}