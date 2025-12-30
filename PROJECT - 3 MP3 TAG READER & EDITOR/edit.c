#include "mp3.h"
#include <stdint.h>

void edit_mp3_data(const char *filename, const char *title, const char *artist, const char *album, const char *year, const char *context, const char *comment) 
{
    FILE *src = fopen(filename, "rb");
    if (!src) 
    {
        printf("Error: Could not open %s\n", filename);
        return;
    }

    // Create new file name
    char newfile[256];
    sprintf(newfile, "new_%s", filename);

    FILE *dest = fopen(newfile, "wb");
    if (!dest) 
    {
        printf("Error: Could not create %s\n", newfile);
        fclose(src);
        return;
    }

    // Read 10-byte ID3 header and copy as-is
    uint8_t header[10];
    fread(header, 1, 10, src);
    fwrite(header, 1, 10, dest);

    uint32_t tag_size = (header[6] << 21) | (header[7] << 14) | (header[8] << 7) | header[9];
    uint32_t copied = 10;
    while (copied < tag_size + 10) 
    {
        char frame_id[5] = {0};
        uint8_t size_bytes[4], flags[2];

        fread(frame_id, 1, 4, src);
        fread(size_bytes, 1, 4, src);
        fread(flags, 1, 2, src);

        uint32_t frame_size = (size_bytes[0] << 24) | (size_bytes[1] << 16) | (size_bytes[2] << 8) | size_bytes[3];

        if (frame_id[0] == 0) break;  // padding

        char *data = malloc(frame_size);
        fread(data, 1, frame_size, src);

        // Prepare replacement if applicable
        const char *new_data = NULL;
        if (strncmp(frame_id, "TIT2", 4) == 0 && title) new_data = title;
        else if (strncmp(frame_id, "TPE1", 4) == 0 && artist) new_data = artist;
        else if (strncmp(frame_id, "TALB", 4) == 0 && album) new_data = album;
        else if (strncmp(frame_id, "TYER", 4) == 0 && year) new_data = year;
        else if (strncmp(frame_id, "TCON", 4) == 0 && context) new_data = context;
        else if (strncmp(frame_id, "COMM", 4) == 0 && comment) new_data = comment;

        // Write frame
        fwrite(frame_id, 1, 4, dest);

        if (new_data) 
        {
            uint32_t new_len = strlen(new_data) + 1;
            uint8_t new_size[4] = 
            {
                (new_len >> 24) & 0xFF,
                (new_len >> 16) & 0xFF,
                (new_len >> 8) & 0xFF,
                new_len & 0xFF
            };
            fwrite(new_size, 1, 4, dest);
            fwrite(flags, 1, 2, dest);

            fputc(0, dest); // encoding byte
            fwrite(new_data, 1, strlen(new_data), dest);
        } 
        else 
        {
            // No change, copy original
            fwrite(size_bytes, 1, 4, dest);
            fwrite(flags, 1, 2, dest);
            fwrite(data, 1, frame_size, dest);
        }

        copied += 10 + frame_size;
        free(data);
    }

    // Copy remaining file (audio data)
    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) 
    {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);

    // Replace old file
    remove(filename);
    rename(newfile, filename);

    printf("MP3 tags updated successfully.\n");
}
