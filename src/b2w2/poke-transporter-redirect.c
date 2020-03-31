#include <pksm.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define VERSION_OFFSET 0x27
#define SIZE_OFFSET_LE 0x116
#define SIZE_OFFSET_BE 0x11d

int main(int argc, char **argv) {
    unsigned char version = *argv[2];

    char patch[] = {
      0x11, 0xa7, 0xe0,       // Record 1 offest
      0x00, 0x04,             // Record 1 length
      0x75, 0xca, 0x01, 0xea, // b ReadSDSaveFile

      0x11, 0xaa, 0x40,       // Record 2 offset
      0x00, 0x04,             // Record 2 length
      0x34, 0x00, 0x00, 0xea, // b LAB_0013de00

      0x11, 0xab, 0x18,       // Record 3 offset
      0x00, 0x20,             // Record 3 length
      0x49, 0x00, 0xa0, 0xe3, // mov  r0, #0x49   ; ascii I
      0x00, 0x00, 0xc6, 0xe5, // strb r0, [r6,#0] 
      0x52, 0x00, 0xa0, 0xe3, // mov  r0, #0x52   ; ascii R
      0x01, 0x00, 0xc6, 0xe5, // strb r0, [r6,#1]
      0xff, 0x00, 0xa0, 0xe3, // mov  r0, <version> 
      0x02, 0x00, 0xc6, 0xe5, // strb r0, [r6,#2]
      0x4f, 0x00, 0xa0, 0xe3, // mov  r0, #0x4f   ; ascii O
      0x03, 0x00, 0xc6, 0xe5, // strb r0, [r6,#3]

      0x11, 0xab, 0x50,       // Record 4 offset
      0x00, 0x04,             // Record 4 length
      0xa9, 0xc9, 0x01, 0xea, // b WriteSDSaveFile

      0x18, 0xd1, 0xbc,       // Record 5 offset
      0x00, 0x84,             // Record 5 length
      /* ReadSDSaveFile */
      0x3f, 0x40, 0x2d, 0xe9, // stmdb sp!, { r0-r5, lr }
      0x03, 0x50, 0xa0, 0xe1, // mov   r5, r3          ; set read size to r4
      0x02, 0x40, 0xa0, 0xe1, // mov   r4, r2          ; set buffer pointer to r4
      0x00, 0x30, 0xa0, 0xe3, // mov   r3, #0x0        ; set offsetHigh as 0 to r3
      0x01, 0x20, 0xa0, 0xe1, // mov   r2, r1          ; set offsetLow to r2
      0x0d, 0x10, 0xa0, 0xe1, // mov   r1, sp          ; set r1 to sp to store file handle
      0x26, 0x00, 0x00, 0xeb, // bl    OpenSDSaveFile
      0x01, 0x00, 0xa0, 0xe1, // mov   r0, r1          ; set r0 to file handle
      0x30, 0x00, 0x2d, 0xe9, // stmdb sp!, { r4,r5 }  ; push variables
      0x08, 0x10, 0x8d, 0xe2, // add   r1, sp, #0x8    ; set r1 to throwaway location for bytes read
      0x48, 0x30, 0xfb, 0xeb, // bl    FSFILE_Read
      0x30, 0x00, 0xbd, 0xe8, // ldmia sp!, { r4,r5 }  ; pop variables
      0x0d, 0x00, 0xa0, 0xe1, // mov   r0, sp          ; set r0 to file handle
      0x5b, 0x30, 0xfb, 0xeb, // bl    FSFILE_Close
      0x3f, 0x80, 0xbd, 0xe8, // ldmia sp!, { r0-r5, pc }
      0x00, 0x00, 0x00, 0x00, // nop
      /* WriteSDSaveFile */
      0x7f, 0x40, 0x2d, 0xe9, // stmdb sp!, { r0-r6, lr }
      0x00, 0x60, 0xa0, 0xe3, // mov   r6, #0x0        ; set flags 0 to r6
      0x03, 0x50, 0xa0, 0xe1, // mov   r5, r3          ; set write size to r5
      0x02, 0x40, 0xa0, 0xe1, // mov   r4, r2          ; set buffer pointer to r4
      0x00, 0x30, 0xa0, 0xe3, // mov   r3, #0x0        ; set offsetHigh as 0 to r3
      0x01, 0x20, 0xa0, 0xe1, // mov   r2, r1          ; set offsetLow to r2
      0x0d, 0x10, 0xa0, 0xe1, // mov   r1, sp          ; set r1 to sp to store file handle
      0x15, 0x00, 0x00, 0xeb, // bl    OpenSDSaveFile
      0x01, 0x00, 0xa0, 0xe1, // mov   r0, r1          ; set r0 to file handle
      0x70, 0x00, 0x2d, 0xe9, // stmdb sp!, { r4-r6 }  ; push variables
      0x0c, 0x10, 0x8d, 0xe2, // add   r1, sp, #0xc    ; set r1 to throwaway location for bytes written
      0x58, 0x30, 0xfb, 0xeb, // bl    FSFILE_Write
      0x70, 0x00, 0xbd, 0xe8, // ldmia sp!, { r4-r6 }  ; pop variables
      0x0d, 0x00, 0xa0, 0xe1, // mov   r0, sp          ; set r0 to file handle
      0x4a, 0x30, 0xfb, 0xeb, // bl    FSFILE_Close
      0x7f, 0x80, 0xbd, 0xe8, // ldmia sp!, { r0-r6, pc }
      0x00, 0x00, 0x00, 0x00, // nop

      0x18, 0xd2, 0x74,       // Record 6 offset
      0x00, 0x4c,             // Record 6 length
      /* OpenSDSaveFile */
      0xfc, 0x4f, 0x2d, 0xe9, // stmdb sp!, { r2-r11, lr }
      0x34, 0x00, 0x9f, 0xe5, // ldr   r0, fsHandle     ; set r0 to fsHandle
      0x00, 0x20, 0xa0, 0xe3, // mov   r2, #0x0         ; always set to 0
      0x09, 0x30, 0xa0, 0xe3, // mov   r3, #0x9         ; set archiveId to ARCHIVE_SDMC
      0x01, 0x40, 0xa0, 0xe3, // mov   r4, #0x1         ; set archivePath.type to PATH_EMPTY
      0x28, 0x50, 0x8f, 0xe2, // adr   r5, emptyString  ; set archivePath.data to emptyString
      0x01, 0x60, 0xa0, 0xe3, // mov   r6, #0x1         ; set archivePath.size to 1 (null terminator)
      0x04, 0x70, 0xa0, 0xe3, // mov   r7, #0x4         ; set filePath.type to PATH_UTF16
      0x24, 0x80, 0x8f, 0xe2, // adr   r8, savePath     ; set filePath.data to savePath
      0x1c, 0x90, 0x9f, 0xe5, // ldr   r9, pathSize     ; set filePath.size to pathSize
      0x03, 0xa0, 0xa0, 0xe3, // mov   r10, #0x3        ; set openFlags to OPEN_READ|OPEN_WRITE
      0x00, 0xb0, 0xa0, 0xe3, // mov   r11, #0x0        ; set attributes to 0
      0xf0, 0x0f, 0x2d, 0xe9, // stmdb sp!, { r4-r11 }  ; push variables
      0x66, 0x48, 0xfd, 0xeb, // bl    FSUSER_OpenFileDirectly
      0xf0, 0x0f, 0xbd, 0xe8, // ldmia sp!, { r4-r11 }  ; pop variables
      0xfc, 0x8f, 0xbd, 0xe8, // ldmia sp!, { r2-r11, pc }
      /* fsHandle: .word 0x00311f80 */
      0x80, 0x1f, 0x31, 0x00,
      /* emptyString: .string "" */
      0x00, 0x00, 0x00, 0x00,
      /* pathSize: .word <path_size> */
      0xff, 0xff, 0x00, 0x00,

      0x18, 0xd2, 0xc0,       // Record 7 offset
      0xff, 0xff,             // Record 7 length VAR
      /* savePath: .string <save_path> */
    };

    switch (version) {
      case 22:
        patch[VERSION_OFFSET] = 'D';
        break;
      case 23:
        patch[VERSION_OFFSET] = 'E';
        break;
      default:
        gui_warn("Unsupported version");
        return 1;
    }

    char *path_utf8 = save_path();

    if (path_utf8 == NULL) {
        gui_warn("Save is not a file");
        return 1;
    }

    char *path_utf16 = utf8_to_utf16(path_utf8);
    free(path_utf8);
    short *tmp = (short*) path_utf16;
    size_t path_size = 1;
    while (*tmp++) ++path_size;

    if (path_size > 0xff) {
        free(path_utf16);
        gui_warn("Save path too long");
        return 1;
    }

    char size_bytes[] = { path_size << 1, path_size >> 7 };
    patch[SIZE_OFFSET_LE + 0] = size_bytes[0];
    patch[SIZE_OFFSET_LE + 1] = size_bytes[1];
    patch[SIZE_OFFSET_BE + 0] = size_bytes[1];
    patch[SIZE_OFFSET_BE + 1] = size_bytes[0];

    mkdir("/luma", 0777);
    mkdir("/luma/titles", 0777);
    mkdir("/luma/titles/00040000000C9C00", 0777);
    FILE *ips = fopen("/luma/titles/00040000000C9C00/code.ips", "wb");
    
    if (ips == NULL) {
        free(path_utf16);
        gui_warn("Failed to open patch file");
        return 1;
    }

    fputs("PATCH", ips);
    fwrite(patch, 1, sizeof(patch), ips);
    fwrite(path_utf16, 2, path_size, ips);
    fputs("EOF", ips);
    fclose(ips);

    free(path_utf16);

    gui_warn("Poke Transporter Redirect Complete");

    return 0;
}
