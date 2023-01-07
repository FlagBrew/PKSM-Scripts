#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int main(int argc, char **argv)
{
    unsigned char version = *argv[0];
    enum Generation gen;

    switch (version)
    {
    case 35: // red
    case 36: // green[jp]/blue[int]
    case 37: // blue[jp]
    case 38: // yellow[jp]
        gen = GEN_ONE;
        break;
    case 39: // gold
    case 40: // silver
    case 41: // crystal
        gen = GEN_TWO;
        break;
    case 1: // ruby
    case 2: // sapphire
    case 3: // emerald
    case 4: // fire red
    case 5: // leaf green
        gen = GEN_THREE;
        break;
    case 10:
    case 11:
    case 12:
    case 7:
    case 8:
        gen = GEN_FOUR;
        break;
    case 20:
    case 21:
    case 22:
    case 23:
        gen = GEN_FIVE;
        break;
    case 24:
    case 25:
    case 26:
    case 27:
        gen = GEN_SIX;
        break;
    case 30:
    case 31:
    case 32:
    case 33:
        gen = GEN_SEVEN;
        break;
    case 42:
    case 43:
        gen = GEN_LGPE;
        break;
    default:
        gui_warn("Sorry this version isn't supported yet by the script!");
        return 1;
    }

    int maxSpecies, maxMoves, maxBalls, maxItems, maxAbility, maxSlots, slotsPerBox;
    unsigned int randomizedCount, maxLevel;
    int gen_party = gui_choice("Do you want to inject into your box or your party?\nThis Will Generate 6 PKMN");
    if (gen_party == 1)
    {
        randomizedCount = 6;
    }
    else
    {
        gui_warn("Please enter how many pokemon\nyou would like to generate!");
        gui_numpad(&randomizedCount, "Number of PKMN to generate.", 3);
    }
    int gen_eggs = 0;

    if (gen != GEN_ONE)
    {
        int gen_eggs = gui_choice("Do you want to generate eggs?\nThis is for EggLocke runs");
    }

    gui_warn("Please enter the max level\nyou would like to have your pokemon be!");
    gui_numpad(&maxLevel, "Max level 1-100", 3);

    if (maxLevel <= 0 || maxLevel > 100)
    {
        gui_warn("You must choose a level\nbetween 1-100!");
        return 1;
    }
    maxSlots = sav_get_max(MAX_SLOTS);
    slotsPerBox = maxSlots / sav_get_max(MAX_BOXES);

    switch (gen)
    {
    case GEN_ONE:
        maxSpecies = 151;
        maxBalls = 5;
        maxMoves = 165;
        break;
    case GEN_TWO:
        maxSpecies = 251;
        maxMoves = 251;
        maxItems = 255;
        break;
    case GEN_THREE:
        maxSpecies = 386;
        maxItems = (version == 4 || version == 5) ? 374 : (version == 3 ? 376 : 348);
        maxMoves = 354;
        maxBalls = 12;
        maxAbility = 77;
        break;
    case GEN_FOUR:
        maxSpecies = 493;
        maxBalls = 24;
        maxMoves = 467;
        maxAbility = 123;
        maxItems = (version == 11 || version == 10) ? 464 : (version == 12 ? 467 : 536);
        break;
    case GEN_FIVE:
        maxSpecies = 649;
        maxBalls = 25;
        maxMoves = 559;
        maxAbility = 164;
        maxItems = (version == 20 || version == 21) ? 632 : 638;
        break;
    case GEN_SIX:
        maxSpecies = 721;
        maxBalls = 25;
        maxItems = (version == 26 || version == 27) ? 775 : 717;
        maxMoves = (version == 26 || version == 27) ? 621 : 617;
        maxAbility = (version == 26 || version == 27) ? 191 : 188;
        break;
    case GEN_SEVEN:
        maxBalls = 26;
        maxMoves = 720;
        maxSpecies = (version == 32 || version == 33) ? 807 : 802;
        maxMoves = (version == 32 || version == 33) ? 728 : 720;
        maxItems = (version == 32 || version == 33) ? 959 : 920;
        maxAbility = (version == 32 || version == 33) ? 233 : 232;
        break;
    case GEN_LGPE:
        gen = GEN_LGPE;
        maxSpecies = 153;
        maxBalls = 26;
        slotsPerBox = 30;
        break;
    default:
        gui_warn("How'd you get here?");
        return 1;
    }

    if (randomizedCount > maxSlots || randomizedCount == 0)
    {
        char part2[80] = {0};
        sprintf(part2, "You've inputted an invalid number\nYou must generate between 1-%d pokemon!", maxSlots);
        gui_warn(part2);
    }
    else
    {
        int randNick = gui_choice("Do you want to randomize nicknames?\nThis could produce weirdness.");
        gui_warn("Depending on how many to generate\nthis might take awhile!");
        sav_box_decrypt();
        srand(time(0) + version);
        char *data = malloc(pkx_box_size(gen));
        for (int i = 0; i < randomizedCount; i++)
        {
            // Species ID
            int pokemonID = rand() % maxSpecies + 1;
            if (gen == GEN_LGPE)
            {
                if (pokemonID == 152)
                {
                    pokemonID = 808;
                }
                else if (pokemonID == 153)
                {
                    pokemonID = 809;
                }
            }
            pkx_generate(data, pokemonID);
            // Shiny Status
            if (gen != GEN_ONE)
            {
                pkx_set_value(data, gen, SHINY, rand() % 2);
            }
            // Level
            pkx_set_value(data, gen, LEVEL, rand() % maxLevel + 1);
            // IVs
            pkx_set_value(data, gen, IV_HP, rand() % 32);
            pkx_set_value(data, gen, IV_ATK, rand() % 32);
            pkx_set_value(data, gen, IV_DEF, rand() % 32);
            pkx_set_value(data, gen, IV_SPEED, rand() % 32);
            pkx_set_value(data, gen, IV_SPATK, rand() % 32);
            pkx_set_value(data, gen, IV_SPDEF, rand() % 32);
            // Nature
            if (gen != GEN_ONE && gen != GEN_TWO)
            {
                pkx_set_value(data, gen, NATURE, rand() % 25);
            }
            // Gender
            if (gen != GEN_ONE)
            {
                pkx_set_value(data, gen, GENDER, rand() % 3);
            }
            // Since LGPE is weird, we can't really do extra stuff for it.
            if (gen != GEN_LGPE)
            {
                // Capture Ball
                if (gen != GEN_TWO)
                {
                    pkx_set_value(data, gen, BALL, rand() % maxBalls + 1);
                }
                else
                {
                    int genTwoBalls[13] = {1, 2, 3, 4, 5, 17, 18, 19, 20, 21, 22, 23, 24};
                    pkx_set_value(data, gen, BALL, genTwoBalls[rand() % 13]);
                }
                for (int ii = 0; ii < 4; ii++)
                {
                    // Move
                    pkx_set_value(data, gen, MOVE, ii, rand() % maxMoves + 1);
                }
                // Held Item
                if (gen != GEN_ONE)
                {
                    pkx_set_value(data, gen, ITEM, rand() % maxItems + 1);
                }
                // Ability
                if (gen != GEN_ONE && gen != GEN_TWO)
                {
                    pkx_set_value(data, gen, ABILITY, rand() % maxAbility + 1);
                }
            }
            // Pokerus
            if (gen != GEN_ONE)
            {
                pkx_set_value(data, gen, POKERUS, rand() % 16, rand() % 5);
            }
            if (randNick == 1)
            {
                // Nickname
                char *species1 = i18n_species(pokemonID);
                char *species2 = i18n_species(rand() % maxSpecies + 1);

                int l1 = strlen(species1) / 2;
                int l2 = strlen(species2) / 2;
                char *name = malloc(l1 + l2 + 1);
                memcpy(name, species1, l1);
                memcpy(name + l1, species2 + l2, strlen(species2) - l2);
                name[l1 + l2] = '\0';
                pkx_set_value(data, gen, NICKNAME, name);
                free(name);
            }
            if (gen_eggs == 1)
            {
                pkx_set_value(data, gen, EGG, 1);
            }
            if (gen_party == 1)
            {
                party_inject_pkx(data, gen, i);
            }
            else
            {
                sav_inject_pkx(data, gen, i / slotsPerBox, i % slotsPerBox, 0);
            }
        }

        free(data);
        sav_box_encrypt();
    }
    return 0;
}
