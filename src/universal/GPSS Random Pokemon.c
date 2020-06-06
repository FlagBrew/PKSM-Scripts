#include <pksm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Credit to where credit is due, piepie62 originally wrote this script for a legal living dex. I just modified it to grab 6 random pokemon from GPSS.
// This script chooses 6 random pokemon from GPSS between acceptable generations (e.g. if you're on a gen 6 game, it will choose random pokemon from gens 3 - 6 and so on.)
// It will overwrite your party so be careful!

int main(int argc, char** argv)
{
    gui_warn("This script will overwrite pokemon\nin your party!");
    int choice = gui_choice("Would you like to continue?");
    if(choice == 0) {
        return 1;
    }
    unsigned char version = *argv[0];

    enum Generation gen;
    char url[56] = {0};

    switch (version)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            gen        = GEN_THREE;
            sprintf(url, "https://flagbrew.org/api/v2/gpss-random?generation=%d",  3);
            break;
        case 10:
        case 11:
        case 12:
        case 7:
        case 8:
            gen        = GEN_FOUR;
            sprintf(url, "https://flagbrew.org/api/v2/gpss-random?generation=%d",  4);
            break;
        case 20:
        case 21:
        case 22:
        case 23:
            gen        = GEN_FIVE;
            sprintf(url, "https://flagbrew.org/api/v2/gpss-random?generation=%d",  5);
            break;
        case 24:
        case 25:
        case 26:
        case 27:
            gen        = GEN_SIX;
            sprintf(url, "https://flagbrew.org/api/v2/gpss-random?generation=%d",  6);
            break;
        case 30:
        case 31:
        case 32:
        case 33:
            gen        = GEN_SEVEN;
            sprintf(url, "https://flagbrew.org/api/v2/gpss-random?generation=%d",  7);
            break;
        case 42:
        case 43:
            gen        = GEN_LGPE;
            sprintf(url, "https://flagbrew.org/api/v2/gpss-random?generation=%s", "LGPE");
            break;
        case 44:
        case 45:
            gen        = GEN_EIGHT;
            sprintf(url, "https://flagbrew.org/api/v2/gpss-random?generation=%d",  8);
            break;
    }

    char* currentData          = NULL;
    int currentDataSize        = 0;
    enum Generation currentGen = 0xFF;
    
    int response = fetch_web_content(&currentData, &currentDataSize, url);
        if (response != 200 || currentData == NULL || currentDataSize == 0)
        {
            char printMe[64];
            sprintf(printMe, "Problem getting pokemon: %i", response);
            gui_warn(printMe);

            free(currentData);

            return 1;
        }

            struct JSON* data = json_new();
            json_parse(data, currentData);
            if(json_is_valid(data) == 1 && json_is_array(data) == 1){
                for (int pokemon = 0; pokemon < 6; pokemon++)
                {
                    struct JSON* pkmn = json_array_element(data, pokemon);
                    char* base64 = json_get_string(json_object_element(pkmn, "base_64"));
                    char* generation = json_get_string(json_object_element(pkmn, "generation"));
                    // ih8C
                    if(strcmp(generation, "3") == 0 ) {
                        currentGen = GEN_THREE;
                    } else if (strcmp(generation, "4") == 0) {
                        currentGen = GEN_FOUR;
                    } else if (strcmp(generation, "5") == 0) {
                        currentGen = GEN_FIVE;
                    } else if (strcmp(generation, "6") == 0) {
                        currentGen = GEN_SIX;
                    } else if (strcmp(generation, "7") == 0) {
                        currentGen = GEN_SEVEN;
                    } else if (strcmp(generation, "LGPE") == 0) {
                        currentGen = GEN_LGPE;
                    } else if (strcmp(generation, "8") == 0) {
                        currentGen = GEN_EIGHT;
                    } else {
                        currentGen = gen;
                    }
                    unsigned char* newPokemon = NULL;
                    int newPokemonSize = 0;
                    base64_decode(&newPokemon, &newPokemonSize, base64, strlen(base64));
                    party_inject_pkx((char*)newPokemon, currentGen, pokemon);
                    free(newPokemon);
                    free(base64);
                    free(generation);
                }
            } else {
                gui_warn("Data is either not JSON\nor is not a JSON array!");
            }
        json_delete(data);
        free(currentData);
        return 0;
}
