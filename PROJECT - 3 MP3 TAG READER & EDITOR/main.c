#include "mp3.h"

char* get_input(const char *prompt) 
{
    static char buffer[256];
    printf("%s", prompt);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline
    return buffer;
}

int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        printf("Error: Not enough arguments.\nUse --help to see usage.\n");
        return 1;
    }

    // --help
    if (strcmp(argv[1], "--help") == 0) 
    {
        show_help();
        return 0;
    }

    // View
    if (strcmp(argv[1], "-v") == 0 && argc == 3) 
    {
        view_mp3_data(argv[2]);
        return 0;
    }

    // Edit mode
    if (strcmp(argv[1], "-e") == 0) 
    {
        char *title = NULL, *artist = NULL, *album = NULL;
        char *year = NULL, *context = NULL, *comment = NULL;
        const char *filename = argv[argc - 1];

    for (int i = 2; i < argc - 1; i++) 
    {
        if (strcmp(argv[i], "-t") == 0) 
        {
            title = get_input("Enter new title: ");
        } 
        else if (strcmp(argv[i], "-a") == 0) 
        {
            artist = get_input("Enter new artist name: ");
        } 
        else if (strcmp(argv[i], "-A") == 0) 
        {
            album = get_input("Enter new album name: ");
        } 
        else if (strcmp(argv[i], "-y") == 0) 
        {
            year = get_input("Enter new year: ");
        } 
        else if (strcmp(argv[i], "-m") == 0) 
        {
            context = get_input("Enter new context/genre: ");
        } 
        else if (strcmp(argv[i], "-c") == 0) 
        {
            comment = get_input("Enter new comment: ");
        } 
        else if (argv[i][0] == '-') 
        {
            printf("Invalid flag: %s\n", argv[i]);
            return 1;
        }
    }

    edit_mp3_data(filename, title, artist, album, year, context, comment);
    printf("\nFile updated! Use `-v` to view changes.\n");
    return 0;
}
    printf("Invalid command. Use --help.\n");
    return 1;
}
