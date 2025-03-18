#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUFFER_SIZE 128

typedef struct arguments
{
    unsigned int files_count;
    char **files;
} arguments;

void parse_arguments(int argc, char **argv, arguments *args)
{
    args->files = malloc(argc * sizeof(char *));
    int index = 0;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--help") == 0)
        {
            printf("Usage: %s file1 file2 [file]...\n", argv[0]);
            exit(0);
        }
        else
        {
            args->files[index] = argv[i];
            index++;
        }
    }
    args->files_count = index;
}

int read_file(char *path, char **buffer)
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
    {
        perror("File opening failed");
        *buffer = NULL;
        return(1);
    }
    int tmp_capacity = INITIAL_BUFFER_SIZE;
    int tmp_size = 0;
    char *tmp = malloc(tmp_capacity * sizeof(char));
    if (tmp == NULL)
    {
        perror("Malloc failed");
        *buffer = NULL;
        fclose(f);
        return(1);
    }
    size_t bytes_read;
    while ((bytes_read = fread(tmp + tmp_size, 1, tmp_capacity - tmp_size, f)) > 0)
    {
        if (tmp_size + bytes_read >= tmp_capacity)
        {
            tmp_capacity *= 2;
            tmp = realloc(tmp, tmp_capacity * sizeof(char));
            if (tmp == NULL)
            {
                perror("Realloc failed");
                *buffer = NULL;
                fclose(f);
                return(1);
            }
        }
        tmp_size += bytes_read;
    }
    tmp[tmp_size] = '\0';
    *buffer = tmp;
    fclose(f);
    return tmp_size;
}

int main(int argc, char *argv[])
{
    arguments args;
    parse_arguments(argc, argv, &args);
    char *buffer = NULL;
    int buffer_size = 0;
    for (unsigned int i = 0; i < args.files_count; i++)
    {
        char *content = NULL;
        int len = read_file(args.files[i], &content);
        buffer = realloc(buffer, (buffer_size + len) * sizeof(char));
        memcpy(buffer + buffer_size, content, len);
        buffer_size += len;        
        printf("%s\n", buffer);
    }
    return 0;
}
