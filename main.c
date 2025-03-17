#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arguments
{
    unsigned int files_count;
    char **files;
} arguments;

void parse_arguments(int argc, char **argv, arguments *args){
    args->files = malloc(argc * sizeof(char*));
    int index = 0;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--help") == 0)
        {
            printf("Usage: %s file1 file2 [file]...\n", argv[0]);
            exit(0);
        }else
        {
            args->files[index] = argv[i];
            index++;
        }
    }
    args->files_count = index;
}

int main(int argc, char *argv[]) {
    arguments args;
    parse_arguments(argc, argv, &args);
    printf("Files count: %d\n", args.files_count);
    return 0;
}
