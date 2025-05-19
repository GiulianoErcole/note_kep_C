#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

#define DEFAULT_FILENAME "notes.txt"
#define MAX_NOTE_LEN 256
#define BUFFER_SIZE 512
#define MAX_FILE_SIZE_MB 1

void xor_cipher(char *data, size_t length, char key) {
    for (size_t i = 0; i < length; i++) {
        data[i] ^= key;
    }
}

void display_notes(const char *filename, const char *search_term, char key) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        return;
    }

    char buffer[BUFFER_SIZE];
    int bytes_read;
    printf("\n📒 \033[1;34mYour notes:\033[0m\n");
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        xor_cipher(buffer, bytes_read, key);

        char *line = strtok(buffer, "\n");
        while (line) {
            if (!search_term || strstr(line, search_term)) {
                printf("\033[0;32m%s\033[0m\n", line);
            }
            line = strtok(NULL, "\n");
        }
    }

    close(fd);
}

int file_size_warning(const char *filename) {
    struct stat st;
    if (stat(filename, &st) == -1) return 0;
    return st.st_size > MAX_FILE_SIZE_MB * 1024 * 1024;
}

int main(int argc, char *argv[]) {
    const char *filename = DEFAULT_FILENAME;
    const char *search_term = NULL;
    int read_only = 0;
    char key = 0x5A; // Simple XOR key

    // Parse arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            read_only = 1;
        } else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            search_term = argv[++i];
        } else {
            filename = argv[i];
        }
    }

    // Warn if file too large
    if (file_size_warning(filename)) {
        fprintf(stderr, "\033[1;33mWarning:\033[0m %s exceeds %dMB\n", filename, MAX_FILE_SIZE_MB);
    }

    // Read-only or search mode
    if (read_only || search_term) {
        display_notes(filename, search_term, key);
        return 0;
    }

    // Prompt user for input
    char note[MAX_NOTE_LEN];
    printf("Write a note: ");
    if (!fgets(note, MAX_NOTE_LEN, stdin)) {
        perror("Error reading input");
        return 1;
    }
    note[strcspn(note, "\n")] = '\0'; // remove newline

    // Get timestamp
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S]", t);

    // Format entry
    char entry[MAX_NOTE_LEN + 100];
    snprintf(entry, sizeof(entry), "%s %s\n", timestamp, note);

    // Encrypt
    xor_cipher(entry, strlen(entry), key);

    // Write note to file
    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file for writing");
        return 1;
    }
    if (write(fd, entry, strlen(entry)) == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    close(fd);

    // Display updated notes
    display_notes(filename, NULL, key);
    return 0;
}
