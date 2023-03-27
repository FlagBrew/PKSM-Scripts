#include <pksm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    unsigned char version = *argv[0];

    enum Generation gen;

    int maxSpecies = 0;

    switch (version)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            gen        = GEN_THREE;
            maxSpecies = 386;
            break;
        case 10:
        case 11:
        case 12:
        case 7:
        case 8:
            gen        = GEN_FOUR;
            maxSpecies = 493;
            break;
        case 20:
        case 21:
        case 22:
        case 23:
            gen        = GEN_FIVE;
            maxSpecies = 649;
            break;
        case 24:
        case 25:
        case 26:
        case 27:
            gen        = GEN_SIX;
            maxSpecies = 721;
            break;
        case 30:
        case 31:
            gen        = GEN_SEVEN;
            maxSpecies = 802;
            break;
        case 32:
        case 33:
            gen        = GEN_SEVEN;
            maxSpecies = 807;
            break;
        case 42:
        case 43:
            gen        = GEN_LGPE;
            maxSpecies = 809;
            break;
        case 44:
        case 45:
            gen        = GEN_EIGHT;
            maxSpecies = 890;
            break;
        case 35:
        case 36:
        case 37:
        case 38:
            gen        = GEN_ONE;
            maxSpecies = 151;
            break;
        case 39:
        case 40:
        case 41:
            gen        = GEN_TWO;
            maxSpecies = 251;
            break;
    }

    char* currentData          = NULL;
    int currentDataSize        = 0;
    enum Generation currentGen = 0xFF;

    if (gen == GEN_LGPE)
    {
        // LGPE is weird
        int response = fetch_web_content(
            &currentData, &currentDataSize, "https://cdn.sigkill.tech/dex/pb7.txt");
        currentGen = GEN_LGPE;
        if (response != 200 || currentData == NULL || currentDataSize == 0)
        {
            char printMe[64];
            sprintf(printMe, "Problem downloading dex: %i", response);
            gui_warn(printMe);

            free(currentData);

            return 1;
        }

        char* currentPokemon = currentData;
        for (int pokemon = 0; pokemon < 153; pokemon++)
        {
            char* nextNewline = strchr(currentPokemon, '\n');
            int badNewline    = *(nextNewline - 1) == '\r';
            int size          = (int)nextNewline - (int)currentPokemon - (badNewline ? 1 : 0);

            unsigned char* newPokemon = NULL;
            int newPokemonSize        = 0;
            base64_decode(&newPokemon, &newPokemonSize, currentPokemon, size);

            sav_inject_pkx((char*)newPokemon, GEN_LGPE, pokemon / 30, pokemon % 30, 0);

            free(newPokemon);

            currentPokemon = nextNewline + 1;
        }

        free(currentData);
        return 0;
    }
    else if (gen == GEN_ONE)
    {
        int response = fetch_web_content(
            &currentData, &currentDataSize, "https://cdn.sigkill.tech/dex/pk1.txt");
        currentGen = GEN_LGPE;
        if (response != 200 || currentData == NULL || currentDataSize == 0)
        {
            char printMe[64];
            sprintf(printMe, "Problem downloading dex: %i", response);
            gui_warn(printMe);

            free(currentData);

            return 1;
        }

        char* currentPokemon = currentData;
        for (int pokemon = 1; pokemon <= maxSpecies; pokemon++)
        {
            char* nextNewline = strchr(currentPokemon, '\n');
            int badNewline    = *(nextNewline - 1) == '\r';
            int size          = (int)nextNewline - (int)currentPokemon - (badNewline ? 1 : 0);

            unsigned char* newPokemon = NULL;
            int newPokemonSize        = 0;
            base64_decode(&newPokemon, &newPokemonSize, currentPokemon, size);

            sav_inject_pkx((char*)newPokemon, GEN_ONE, pokemon / 20, pokemon % 20, 0);

            free(newPokemon);

            currentPokemon = nextNewline + 1;
        }

        free(currentData);
        return 0;
    }
    else if (gen == GEN_TWO)
    {
        int response = fetch_web_content(
            &currentData, &currentDataSize, "https://cdn.sigkill.tech/dex/pk2.txt");
        currentGen = GEN_LGPE;
        if (response != 200 || currentData == NULL || currentDataSize == 0)
        {
            char printMe[64];
            sprintf(printMe, "Problem downloading dex: %i", response);
            gui_warn(printMe);

            free(currentData);

            return 1;
        }

        char* currentPokemon = currentData;
        for (int pokemon = 1; pokemon <= maxSpecies; pokemon++)
        {
            char* nextNewline = strchr(currentPokemon, '\n');
            int badNewline    = *(nextNewline - 1) == '\r';
            int size          = (int)nextNewline - (int)currentPokemon - (badNewline ? 1 : 0);

            unsigned char* newPokemon = NULL;
            int newPokemonSize        = 0;
            base64_decode(&newPokemon, &newPokemonSize, currentPokemon, size);

            sav_inject_pkx((char*)newPokemon, GEN_TWO, pokemon / 20, pokemon % 20, 0);

            free(newPokemon);

            currentPokemon = nextNewline + 1;
        }

        free(currentData);
        return 0;
    }
    else
    {
        char* currentPokemon = NULL;
        for (int species = 1; species <= maxSpecies; species++)
        {
            if (species <= 386)
            {
                // get from g3 data
                if (currentGen != GEN_THREE)
                {
                    free(currentData);
                    int response = fetch_web_content(
                        &currentData, &currentDataSize, "https://cdn.sigkill.tech/dex/pk3.txt");
                    currentGen = GEN_THREE;
                    if (response != 200 || currentData == NULL || currentDataSize == 0)
                    {
                        char printMe[64];
                        sprintf(printMe, "Problem downloading dex: %i", response);
                        gui_warn(printMe);

                        free(currentData);

                        return 1;
                    }
                    currentPokemon = currentData;
                }

                char* nextNewline = strchr(currentPokemon, '\n');
                int badNewline    = *(nextNewline - 1) == '\r';
                int size          = (int)nextNewline - (int)currentPokemon - (badNewline ? 1 : 0);

                unsigned char* newPokemon = NULL;
                int newPokemonSize        = 0;
                base64_decode(&newPokemon, &newPokemonSize, currentPokemon, size);

                if (sav_check_value(
                        SAV_VALUE_SPECIES, pkx_get_value((char*)newPokemon, GEN_THREE, SPECIES)))
                {
                    sav_inject_pkx(
                        (char*)newPokemon, GEN_THREE, (species - 1) / 30, (species - 1) % 30, 0);
                }

                free(newPokemon);

                currentPokemon = nextNewline + 1;
            }
            else if (species <= 493)
            {
                // get from g4
                if (currentGen != GEN_FOUR)
                {
                    free(currentData);
                    int response = fetch_web_content(
                        &currentData, &currentDataSize, "https://cdn.sigkill.tech/dex/pk4.txt");
                    currentGen = GEN_FOUR;
                    if (response != 200 || currentData == NULL || currentDataSize == 0)
                    {
                        char printMe[64];
                        sprintf(printMe, "Problem downloading dex: %i", response);
                        gui_warn(printMe);

                        free(currentData);

                        return 1;
                    }
                    currentPokemon = currentData;
                }

                char* nextNewline = strchr(currentPokemon, '\n');
                int badNewline    = *(nextNewline - 1) == '\r';
                int size          = (int)nextNewline - (int)currentPokemon - (badNewline ? 1 : 0);

                unsigned char* newPokemon = NULL;
                int newPokemonSize        = 0;
                base64_decode(&newPokemon, &newPokemonSize, currentPokemon, size);

                if (sav_check_value(
                        SAV_VALUE_SPECIES, pkx_get_value((char*)newPokemon, GEN_FOUR, SPECIES)))
                {
                    sav_inject_pkx(
                        (char*)newPokemon, GEN_FOUR, (species - 1) / 30, (species - 1) % 30, 0);
                }

                free(newPokemon);

                currentPokemon = nextNewline + 1;
            }
            else if (species <= 649)
            {
                // get from g5
                if (currentGen != GEN_FIVE)
                {
                    free(currentData);
                    int response = fetch_web_content(
                        &currentData, &currentDataSize, "https://cdn.sigkill.tech/dex/pk5.txt");
                    currentGen = GEN_FIVE;
                    if (response != 200 || currentData == NULL || currentDataSize == 0)
                    {
                        char printMe[64];
                        sprintf(printMe, "Problem downloading dex: %i", response);
                        gui_warn(printMe);

                        free(currentData);

                        return 1;
                    }
                    currentPokemon = currentData;
                }

                char* nextNewline = strchr(currentPokemon, '\n');
                int badNewline    = *(nextNewline - 1) == '\r';
                int size          = (int)nextNewline - (int)currentPokemon - (badNewline ? 1 : 0);

                unsigned char* newPokemon = NULL;
                int newPokemonSize        = 0;
                base64_decode(&newPokemon, &newPokemonSize, currentPokemon, size);

                if (sav_check_value(
                        SAV_VALUE_SPECIES, pkx_get_value((char*)newPokemon, GEN_FIVE, SPECIES)))
                {
                    sav_inject_pkx(
                        (char*)newPokemon, GEN_FIVE, (species - 1) / 30, (species - 1) % 30, 0);
                }

                free(newPokemon);

                currentPokemon = nextNewline + 1;
            }
            else if (species <= 721)
            {
                // get from g6
                if (currentGen != GEN_SIX)
                {
                    free(currentData);
                    int response = fetch_web_content(
                        &currentData, &currentDataSize, "https://cdn.sigkill.tech/dex/pk6.txt");
                    currentGen = GEN_SIX;
                    if (response != 200 || currentData == NULL || currentDataSize == 0)
                    {
                        char printMe[64];
                        sprintf(printMe, "Problem downloading dex: %i", response);
                        gui_warn(printMe);

                        free(currentData);

                        return 1;
                    }
                    currentPokemon = currentData;
                }

                char* nextNewline = strchr(currentPokemon, '\n');
                int badNewline    = *(nextNewline - 1) == '\r';
                int size          = (int)nextNewline - (int)currentPokemon - (badNewline ? 1 : 0);

                unsigned char* newPokemon = NULL;
                int newPokemonSize        = 0;
                base64_decode(&newPokemon, &newPokemonSize, currentPokemon, size);

                if (sav_check_value(
                        SAV_VALUE_SPECIES, pkx_get_value((char*)newPokemon, GEN_SIX, SPECIES)))
                {
                    sav_inject_pkx(
                        (char*)newPokemon, GEN_SIX, (species - 1) / 30, (species - 1) % 30, 0);
                }

                free(newPokemon);

                currentPokemon = nextNewline + 1;
            }
            else if (species <= 807)
            {
                // get from g7
                if (currentGen != GEN_SEVEN)
                {
                    free(currentData);
                    int response = fetch_web_content(
                        &currentData, &currentDataSize, "https://cdn.sigkill.tech/dex/pk7.txt");
                    currentGen = GEN_SEVEN;
                    if (response != 200 || currentData == NULL || currentDataSize == 0)
                    {
                        char printMe[64];
                        sprintf(printMe, "Problem downloading dex: %i", response);
                        gui_warn(printMe);

                        free(currentData);

                        return 1;
                    }
                    currentPokemon = currentData;
                }

                char* nextNewline = strchr(currentPokemon, '\n');
                int badNewline    = *(nextNewline - 1) == '\r';
                int size          = (int)nextNewline - (int)currentPokemon - (badNewline ? 1 : 0);

                unsigned char* newPokemon = NULL;
                int newPokemonSize        = 0;
                base64_decode(&newPokemon, &newPokemonSize, currentPokemon, size);

                if (sav_check_value(
                        SAV_VALUE_SPECIES, pkx_get_value((char*)newPokemon, GEN_SEVEN, SPECIES)))
                {
                    sav_inject_pkx(
                        (char*)newPokemon, GEN_SEVEN, (species - 1) / 30, (species - 1) % 30, 0);
                }

                free(newPokemon);

                currentPokemon = nextNewline + 1;
            }
            else if (species <= 809)
            {
                // get from lgpe
                if (currentGen != GEN_LGPE)
                {
                    free(currentData);
                    int response = fetch_web_content(
                        &currentData, &currentDataSize, "https://cdn.sigkill.tech/dex/pb7.txt");
                    currentGen = GEN_LGPE;
                    if (response != 200 || currentData == NULL || currentDataSize == 0)
                    {
                        char printMe[64];
                        sprintf(printMe, "Problem downloading dex: %i", response);
                        gui_warn(printMe);

                        free(currentData);

                        return 1;
                    }
                    currentPokemon = currentData;
                    // Skip the first 151
                    for (int unnecessarySpecies = 0; unnecessarySpecies < 151; unnecessarySpecies++)
                    {
                        currentPokemon = strchr(currentPokemon, '\n') + 1;
                    }
                }

                char* nextNewline = strchr(currentPokemon, '\n');
                int badNewline    = *(nextNewline - 1) == '\r';
                int size          = (int)nextNewline - (int)currentPokemon - (badNewline ? 1 : 0);

                unsigned char* newPokemon = NULL;
                int newPokemonSize        = 0;
                base64_decode(&newPokemon, &newPokemonSize, currentPokemon, size);

                if (sav_check_value(
                        SAV_VALUE_SPECIES, pkx_get_value((char*)newPokemon, GEN_LGPE, SPECIES)))
                {
                    sav_inject_pkx(
                        (char*)newPokemon, GEN_LGPE, (species - 1) / 30, (species - 1) % 30, 0);
                }

                free(newPokemon);

                currentPokemon = nextNewline + 1;
            }
            else if (species <= 890)
            {
                // get from g8
                if (currentGen != GEN_EIGHT)
                {
                    free(currentData);
                    int response = fetch_web_content(
                        &currentData, &currentDataSize, "https://cdn.sigkill.tech/dex/pk8.txt");
                    currentGen = GEN_EIGHT;
                    if (response != 200 || currentData == NULL || currentDataSize == 0)
                    {
                        char printMe[64];
                        sprintf(printMe, "Problem downloading dex: %i", response);
                        gui_warn(printMe);

                        free(currentData);

                        return 1;
                    }
                    currentPokemon = currentData;
                }

                char* nextNewline = strchr(currentPokemon, '\n');
                int badNewline    = *(nextNewline - 1) == '\r';
                int size          = (int)nextNewline - (int)currentPokemon - (badNewline ? 1 : 0);

                unsigned char* newPokemon = NULL;
                int newPokemonSize        = 0;
                base64_decode(&newPokemon, &newPokemonSize, currentPokemon, size);

                if (sav_check_value(
                        SAV_VALUE_SPECIES, pkx_get_value((char*)newPokemon, GEN_EIGHT, SPECIES)))
                {
                    sav_inject_pkx(
                        (char*)newPokemon, GEN_EIGHT, (species - 1) / 30, (species - 1) % 30, 0);
                }

                free(newPokemon);

                currentPokemon = nextNewline + 1;
            }
        }
    }

    return 0;
}
