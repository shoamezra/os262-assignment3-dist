#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define SCREEN_W 640
#define SCREEN_H 480
#define FB_BYTES (SCREEN_W * SCREEN_H * 4)

int main(void)
{
    uint32 *buf[2];

    buf[0] = (uint32 *)sbrk(FB_BYTES);
    buf[1] = (uint32 *)sbrk(FB_BYTES);

    if (buf[0] == (uint32 *)-1 || buf[1] == (uint32 *)-1)
    {
        fprintf(2, "sbrk failed\n");
        exit(1);
    }

    for (int i = 0; i < FB_BYTES / 4; i++)
    {
        buf[0][i] = 0x00FF0000; // Red
        buf[1][i] = 0x000000FF; // Blue
    }

    for (int i = 0; i < 50; i++)
    {
        if (flip_display(buf[i & 1]) < 0)
        {
            fprintf(2, "flip_display failed\n");
            exit(1);
        }
        sleep(5);
    }

    exit(0);
}