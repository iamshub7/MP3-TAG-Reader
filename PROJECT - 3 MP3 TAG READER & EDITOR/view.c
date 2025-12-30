#include "mp3.h"
#include <stdint.h>

void view_mp3_data(const char *filename) 
{
    FILE *file = fopen(filename, "rb");
    if (!file) 
    {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }

    // 1. Read first 10 bytes (Header)
    uint8_t header[10];
    fread(header, 1, 10, file);

    // 2. Check for ID3v2.3
    if (header[0] != 'I' || header[1] != 'D' || header[2] != '3') 
    {
        printf("Not a valid ID3 file.\n");
        fclose(file);
        return;
    }

    // 3. Convert tag size from 4 bytes (7-bit sync safe) to int
    uint32_t tag_size = (header[6] << 21) | (header[7] << 14) | (header[8] << 7) | header[9];

    int tags_read = 0;
    const char *valid_tags[] = {"TIT2", "TPE1", "TALB", "TYER", "TCON", "COMM"};

    // 4. Start reading frames after 10 bytes
    while (tags_read < 6 && ftell(file) < tag_size + 10) 
    {
        char frame_id[5] = {0};
        fread(frame_id, 1, 4, file);  // 3. Read 4-byte frame ID

        if (frame_id[0] == 0) break;  // Reached padding

        // 4. Read 4-byte size (big endian)
        uint8_t size_bytes[4];
        fread(size_bytes, 1, 4, file);
        uint32_t frame_size = (size_bytes[0] << 24) | (size_bytes[1] << 16) | (size_bytes[2] << 8) | size_bytes[3];

        // 5. Skip 2 bytes of flags
        fseek(file, 2, SEEK_CUR);

        // 6. Check if it's one of the 6 required tags
        int matched = 0;
        for (int i = 0; i < 6; i++) 
        {
            if (strncmp(frame_id, valid_tags[i], 4) == 0) 
            {
                matched = 1;
                char *data = malloc(frame_size + 1);
                fread(data, 1, frame_size, file);
                data[frame_size] = '\0';

                // 7. Display based on tag
                if (strcmp(frame_id, "TIT2") == 0)
                    printf("Title   : %s\n", data + 1);  // skip encoding byte
                else if (strcmp(frame_id, "TPE1") == 0)
                    printf("Artist  : %s\n", data + 1);
                else if (strcmp(frame_id, "TALB") == 0)
                    printf("Album   : %s\n", data + 1);
                else if (strcmp(frame_id, "TYER") == 0)
                    printf("Year    : %s\n", data + 1);
                else if (strcmp(frame_id, "TCON") == 0)
                    printf("Context : %s\n", data + 1);
                else if (strcmp(frame_id, "COMM") == 0) 
                {
                // COMM format: [encoding][lang x3][short desc][0x00][actual comment]
                int offset = 4; // encoding + 3-byte lang
                while (offset < frame_size && data[offset] != 0)
                offset++; // skip short description

                offset++; // skip 0 byte after desc
                if (offset < frame_size)
                printf("Comment : %s\n", data + offset);
                else
                printf("Comment : (empty)\n");
                }
                
                free(data);
                tags_read++;
                break;
            }
        }

        // If not matched, skip the frame data
        if (!matched)
            fseek(file, frame_size, SEEK_CUR);
    }

    fclose(file);
}
