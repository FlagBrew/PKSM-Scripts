#include <pksm.h>

/*
 * Clears the "Received Gift Type: Null" event flag(s) so that Gladion offers
 * Type: Null again.
 *
 * Flag numbers are taken from PKHeX
 * (PKHeX.Core/Resources/text/script/gen7/flags_sm_en.txt and flags_usum_en.txt):
 *     SM    -  499  Received Gift Type: Null
 *     USUM  -  654  Received Gift Type: Null (1) -- Aether Paradise
 *             1101  Received Gift Type: Null (2) -- Ancient Poni Path
 *
 * The event flag array sits 0x7D0 bytes into the event work block (SM: 0x1C00,
 * USUM: 0x1E00), so flag n is bit (n & 7) of the byte at base + n / 8.
 *
 * Only those bits may be touched. The old .pksm version of this script wrote
 * whole bytes, which overwrote the seven unrelated flags sharing each byte and,
 * on SM, wrote a value that left the gift flag set -- the script appeared to do
 * nothing at all (see issue #56).
 */

#define SM_FLAG_BASE 0x23D0
#define USUM_FLAG_BASE 0x25D0

int clearFlag(int base, int flag)
{
    int offset = base + flag / 8;
    int bit    = flag & 7;

    if (!sav_get_bit(offset, 0, bit))
    {
        return 0;
    }

    sav_set_bit(0, offset, 0, bit);
    return 1;
}

int main(int argc, char** argv)
{
    unsigned char version = *argv[0];
    int base, firstFlag, secondFlag, cleared;

    switch (version)
    {
        case 30: // S
        case 31: // M
            base       = SM_FLAG_BASE;
            firstFlag  = 499;
            secondFlag = -1;
            break;
        case 32: // US
        case 33: // UM
            base       = USUM_FLAG_BASE;
            firstFlag  = 654;
            secondFlag = 1101;
            break;
        default:
            gui_warn("This script only works on\nSun/Moon and Ultra Sun/Ultra Moon.");
            return 1;
    }

    cleared = clearFlag(base, firstFlag);
    if (secondFlag >= 0)
    {
        cleared = clearFlag(base, secondFlag) + cleared;
    }

    if (cleared)
    {
        gui_warn("Type: Null gift reset.\nTalk to Gladion again to get it.");
    }
    else
    {
        gui_warn("The Type: Null gift flag was\nalready cleared.\nNo changes were made.");
    }

    return 0;
}
