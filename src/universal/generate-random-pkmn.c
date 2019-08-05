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

    int maxSpecies = 0;
    int maxMoves = 0;
    int maxBalls = 0;
    int maxItems = 0;
    int maxAbility = 0;

    gui_warn("Please enter how many pokemon", "you would like to generate!");

    int randomizedCount = 0;
    gui_numpad(&randomizedCount, "You are entering how many randomized\npokemon you would like to generate", 3);

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
            if(version == 11 || version == 10){
                maxItems = 464;
            } else if (version == 12) {
                maxItems = 467;
            } else if (version == 7 || version == 8){
                maxItems = 536;
            }
            maxAbility = 123;
            break;
        case 20:
        case 21:
        case 22:
        case 23:
            gen = GEN_FIVE;
            maxSpecies = 649;
            maxBalls = 19;
            maxMoves = 559;
            if (version == 20 || version == 21){
                maxItems = 632;
            } else {
                maxItems = 638;
            }
            maxAbility = 164;
            break;
        case 24:
        case 25:
        case 26:
        case 27:
            gen = GEN_SIX;
            maxSpecies = 721;
            maxBalls = 19;
            if (version == 26 || version == 27){
                maxMoves = 621;
                maxItems = 775;
                maxAbility = 191;
            } else {
                maxMoves = 617;
                maxItems = 717;
                maxAbility = 188;
            }
            break;
        case 30:
        case 31:
        case 32:
        case 33:
            gen = GEN_SEVEN;
            
            maxBalls = 26;
            maxMoves = 720;
            if (version == 32 || version == 33){
                maxSpecies = 807;
                maxMoves = 728;
                maxItems = 959;
                maxAbility = 233;
            } else {
                maxSpecies = 802;
                maxMoves = 720;
                maxItems = 920;
                maxAbility = 232;
            }
            break;
        case 42:
        case 43:
            gen = GEN_LGPE;
            maxSpecies = 153;
            break;
    }

    if (randomizedCount > maxSpecies) {
        char part2[256];
        sprintf(part2, "The game can only handle %d pokemon!", maxSpecies);
        gui_warn("You've put a number more than the game can handle!", part2);
    } else {
        sav_box_decrypt();
        srand(time(0) + version); 
        char* data = malloc(pkx_box_size(gen));
        for (int i = 0; i < randomizedCount ; i++)
        {
            int pokemonID = (rand() % maxSpecies)+1;
            int shiny = (rand() % 2);
            int randLevel = (rand() % 100)+1;
            if (gen == GEN_LGPE){
                if (pokemonID == 152) {
                    pokemonID = 808;
                } else if (pokemonID == 153) {
                    pokemonID = 809;
                }
            }
            pkx_generate(data, pokemonID);
            // Shiny or not
            pkx_set_value(data, gen, SHINY, shiny);
             pkx_set_value(data, gen, LEVEL, randLevel);
            // IVs
            pkx_set_value(data, gen, IV_HP, (rand() % 32));
            pkx_set_value(data, gen, IV_ATK, (rand() % 32));
            pkx_set_value(data, gen, IV_DEF, (rand() % 32));
            pkx_set_value(data, gen, IV_SPEED, (rand() % 32));
            pkx_set_value(data, gen, IV_SPATK, (rand() % 32));
            pkx_set_value(data, gen, IV_SPDEF, (rand() % 32));
            // Gender
            pkx_set_value(data, gen, GENDER, (rand() % 3));
            if(gen != GEN_LGPE){
                int randBall = (rand() % maxBalls)+1;
                int randItem = (rand() % maxItems)+1;
                int randAbility = (rand() % maxAbility)+1;
                pkx_set_value(data, gen, BALL, randBall);
                pkx_set_value(data, gen, MOVE, 0, (rand() % maxMoves)+1);
                pkx_set_value(data, gen, MOVE, 1, (rand() % maxMoves)+1);
                pkx_set_value(data, gen, MOVE, 2, (rand() % maxMoves)+1);
                pkx_set_value(data, gen, MOVE, 3, (rand() % maxMoves)+1);
                pkx_set_value(data, gen, ITEM, randItem);
                pkx_set_value(data, gen, ABILITY, randAbility);
            }
            pkx_set_value(data, gen, POKERUS, (rand() %  255)+1, (rand() %  255)+1) ;
            sav_inject_pkx(data, gen, i / 30, i % 30, 0);
        }
        free(data);
    sav_box_encrypt();   
    }
    return 0;
}
