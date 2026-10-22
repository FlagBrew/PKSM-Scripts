#include <pksm.h> // PKSM provided virtual header giving access to scripting API
#include <stdlib.h>

void main(int argc, char **argv)
{
    unsigned char version = *argv[24];

	sav_set_bit(0, 0, 0x14D21, 6);
	sav_set_bit(0, 0, 0x14E47, 1);

}