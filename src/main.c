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
    printf("%d\n", file_src);
    if (file_src == -1) {  // If source file can't be opened (read)
        printf("Invalid source file\n");
        return 1;
    }


    // Try to create destination file
    file_dest = creat(argv[2], 0644);
    //printf("%d\n", file_dest);
    if (file_dest == -1) {  // If destination file cannot be created
        printf("Invalid destination file\n");
        return 1;
    }

    // Zagotovimo si pomnilnik
    // Check if block size is given in arguments
    if(argc == 4) {
        sscanf(argv[3], "%ld", &block_size);
    }
    else block_size = BLCK_SIZE_DEFAULT;

    if((buff = malloc(block_size)) == NULL) {
        printf("Error during memory allocation");
        return 2;
    }

    // Copy the files
    while ((file_dest = read(file_src, buff, n_pod)) != 0){
        // error: p_pod = -1
        if (file_dest == -1) {
            printf("Error during read\n");
            return 3;
        }
        if( write() )

    return 0;
}