// save this file as file_syscall.c

#include <fcntl.h>      // for open()
#include <unistd.h>     // for write(), read(), close()
#include <stdio.h>      // for perror()
#include <stdlib.h>     // for exit()

int main() {
    int file;
    char *filename = "selam_output.txt";
    char *text = "This is a test file created using system calls in NetBSD.\n";
    char buffer[100];
    int bytes_written, bytes_read;

    // 1. Create and open file using system call open
    file = open(filename, O_CREAT | O_WRONLY, 0644);
    if (file < 0) {
        perror("Error creating file");
        exit(1);
    }

    // 2. Write data to the file using system call write
    bytes_written = write(file, text, 56); // length of text
    if (bytes_written < 0) {
        perror("Error writing to file");
        close(file);
        exit(1);
    }

    // 3. Close the file using close
    close(file);

    // 4. Reopen the file for reading
    file = open(filename, O_RDONLY);
    if (file < 0) {
        perror("Error opening file for reading");
        exit(1);
    }

    // 5. Read the content using read
    bytes_read = read(file, buffer, sizeof(buffer));
    if (bytes_read < 0) {
        perror("Error reading file");
        close(file);
        exit(1);
    }

    // 6. Write content to screen (stdout)
    write(1, buffer, bytes_read); // 1 = stdout

    // 7. Close the file again
    close(file);

    return 0;
}