#include "mp3.h"

void show_help() 
{
    printf("\n========== MP3 TAG READER & EDITOR ==========\n");
    printf("Usage:\n");
    printf("  ./a.out --help\n");
    printf("  ./a.out -v <filename>               → View MP3 tag info\n");
    printf("  ./a.out -e [flags] <filename>       → Edit one or more tags\n\n");

    printf("Edit Flags (use with -e):\n");
    printf("  -t  \"Title\"     → Edit Song Title (TIT2)\n");
    printf("  -a  \"Artist\"    → Edit Artist Name (TPE1)\n");
    printf("  -A  \"Album\"     → Edit Album Name (TALB)\n");
    printf("  -y  \"Year\"      → Edit Year (TYER)\n");
    printf("  -m  \"Context\"   → Edit Context/Genre (TCON)\n");
    printf("  -c  \"Comment\"   → Edit Comment (COMM)\n");

    printf("\nExamples:\n");
    printf("  ./a.out -v sample.mp3\n");
    printf("  ./a.out -e -t \"New Title\" -a \"New Artist\" sample.mp3\n");
    printf("=============================================\n\n");
}
