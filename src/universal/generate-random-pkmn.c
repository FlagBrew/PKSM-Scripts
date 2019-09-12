#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int main(int argc, char **argv)
{
    unsigned char version = *argv[2];
    enum Generation gen;

    int maxSpecies, maxMoves, maxBalls, maxItems, maxAbility, maxBoxes;
    unsigned int randomizedCount, maxLevel;
    gui_warn("Please enter how many pokemon\nyou would like to generate!");
    gui_numpad(&randomizedCount, "Number of PKMN to generate.", 3);
    gui_warn("Please enter how the max level\nyou would like to have your pokemon be!");
    gui_numpad(&maxLevel, "Max level 1-100", 3);

    if(maxLevel <= 0 || maxLevel > 100) {
         gui_warn("You must choose a level\nbetween 1-100!");
         return 1;
    }


    switch (version)
    {
        case 10:
        case 11:
        case 12:
        case 7:
        case 8:
            gen = GEN_FOUR;
            maxSpecies = 493;
            maxBalls = 18;
            maxBoxes = 18;
            maxMoves = 467;
            maxAbility = 123;
            maxItems = (version == 11 || version == 10) ? 464 : (version == 12 ? 467 : 536);
            break;
        case 20:
        case 21:
        case 22:
        case 23:
            gen = GEN_FIVE;
            maxSpecies = 649;
            maxBoxes = 24;
            maxBalls = 19;
            maxMoves = 559;
            maxAbility = 164;
            maxItems = (version == 20 || version == 21) ? 632 : 638;
            break;
        case 24:
        case 25:
        case 26:
        case 27:
            gen = GEN_SIX;
            maxSpecies = 721;
            maxBalls = 19;
            maxItems = (version == 26 || version == 27) ? 775 : 717;
            maxBoxes = 31;
            maxMoves = (version == 26 || version == 27) ? 621 : 617;
            maxAbility = (version == 26 || version == 27) ? 191 : 188;
            break;
        case 30:
        case 31:
        case 32:
        case 33:
            gen = GEN_SEVEN;
            maxBalls = 26;
            maxMoves = 720;
            maxBoxes = 32;
            maxSpecies = (version == 32 || version == 33) ? 807 : 802;
            maxMoves = (version == 32 || version == 33) ? 728 : 720;
            maxItems = (version == 32 || version == 33) ? 959 : 920;
            maxAbility = (version == 32 || version == 33) ? 233 : 232;
            break;
        case 42:
        case 43:
            gen = GEN_LGPE;
            maxSpecies = 153;
            break;
    }

    if (randomizedCount > 30*maxBoxes || randomizedCount == 0){
        char part2[80] = {0};
        sprintf(part2, "You've inputted an invalid number\nYou must generate between 1-%d pokemon!", 30*maxBoxes);
        gui_warn(part2);
    } else {
        int randNick = gui_choice("Do you want to randomize nicknames?\nThis could produce weirdness.");
        gui_warn("Depending on how many to generate\nthis might take awhile!");
        sav_box_decrypt();
        srand(time(0) + version);
        char* data = malloc(pkx_box_size(gen));
        for (int i = 0; i < randomizedCount; i++)
        {
            // Species ID
            int pokemonID = rand() % maxSpecies+1;
            if (gen == GEN_LGPE){
                if (pokemonID == 152) {
                    pokemonID = 808;
                } else if (pokemonID == 153) {
                    pokemonID = 809;
                }
            }
            pkx_generate(data, pokemonID);
            // Shiny Status
            pkx_set_value(data, gen, SHINY, rand() % 2);
            // Level
            pkx_set_value(data, gen, LEVEL, rand() % maxLevel+1);
            // IVs
            pkx_set_value(data, gen, IV_HP, rand() % 32);
            pkx_set_value(data, gen, IV_ATK, rand() % 32);
            pkx_set_value(data, gen, IV_DEF, rand() % 32);
            pkx_set_value(data, gen, IV_SPEED, rand() % 32);
            pkx_set_value(data, gen, IV_SPATK, rand() % 32);
            pkx_set_value(data, gen, IV_SPDEF, rand() % 32);
            // Nature
            pkx_set_value(data, gen, NATURE, rand() % 25);
            // Gender
            pkx_set_value(data, gen, GENDER, rand() % 3);
            // Since LGPE is weird, we can't really do extra stuff for it.
            if(gen != GEN_LGPE){
                // Capture Ball
                pkx_set_value(data, gen, BALL, rand() % maxBalls+1);
                for (int ii = 0; ii < 4; ii++)
                {
                    // Move
                    pkx_set_value(data, gen, MOVE, ii, rand() % maxMoves+1);
                }
                // Held Item
                pkx_set_value(data, gen, ITEM, rand() % maxItems+1);
                // Ability
                pkx_set_value(data, gen, ABILITY, rand() % maxAbility+1);
            }
            // Pokerus
            pkx_set_value(data, gen, POKERUS, rand() % 16, rand() % 5);
            if (randNick == 1){
                // Nickname
                char* species1 = i18n_species(pokemonID);
                char* species2 = i18n_species(rand() % maxSpecies+1);

                int l1 = strlen(species1)/2;
                int l2 = strlen(species2)/2;
                char* name = malloc(l1 + l2 + 1);
                memcpy(name, species1, l1);
                memcpy(name + l1, species2 + l2, strlen(species2) - l2);
                name[l1+l2] = '\0';
                pkx_set_value(data, gen, NICKNAME, name);
                free(name);
            }
            sav_inject_pkx(data, gen, i / 30, i % 30, 0);

        }

        free(data);
        sav_box_encrypt();
    }
    return 0;
}
