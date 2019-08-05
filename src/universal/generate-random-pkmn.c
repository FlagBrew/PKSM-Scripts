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

    int maxSpecies, maxMoves, maxBalls, maxItems, maxAbility, randomizedCount;
    gui_warn("Please enter how many pokemon", "you would like to generate!");
    gui_numpad(&randomizedCount, "Number of PKMN to generate.", 3);

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

    if (randomizedCount > maxSpecies || randomizedCount == 0){
        char part2[41] = {0};
        sprintf(part2, "You must generate between 1-%d pokemon!", maxSpecies);
        gui_warn("You've inputted an invalid number", part2);
    } else {
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
            pkx_set_value(data, gen, LEVEL, rand() % 100+1);
            // IVs
            pkx_set_value(data, gen, IV_HP, rand() % 32);
            pkx_set_value(data, gen, IV_ATK, rand() % 32);
            pkx_set_value(data, gen, IV_DEF, rand() % 32);
            pkx_set_value(data, gen, IV_SPEED, rand() % 32);
            pkx_set_value(data, gen, IV_SPATK, rand() % 32);
            pkx_set_value(data, gen, IV_SPDEF, rand() % 32);
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
            pkx_set_value(data, gen, POKERUS, rand() % 255+1, rand() % 255+1);
            sav_inject_pkx(data, gen, i / 30, i % 30, 0);
        }
        free(data);
        sav_box_encrypt();   
    }
    return 0;
}
