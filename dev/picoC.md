# picoC Script Documentation

## API
Header inclusion
```c
#include <pksm.h>
```

### Arguments passed to `main`
- `argv`
    - `argv[0]` pointer to save data, converted to int, passed as text
    - `argv[1]` save data length (int passed as text)
    - `argv[2]` save's game version (game's index number as found in a Pokémon's *source game* field)
        - DP = 10, Pt = 12, HGSS = 7
            - Based on content alone Diamond saves cannot be told apart from Pearl saves and HeartGold saves cannot be told apart from SoulSilver saves
        - B = 21, W = 20, B2 = 23, W2 = 22
        - X = 24, Y = 25, OR = 27, AS = 26
        - S = 30, M = 31, US = 32, UM = 33
        - LGP = 42, LGE = 43

### GUI Functions
> All `char*` arguments for showing text to the user can contain newlines (`\n`), but sometimes it is not advised. When in doubt, test it to see if things look okay.

```c
int gui_choice(char* lineOne, char* lineTwo);
void gui_warn(char* lineOne, char* lineTwo);
```
![gui_choice](https://i.imgur.com/vPrM81g.png) ![gui_warn](https://i.imgur.com/fsB2uE1.png)

Use of newlines is not advised in the arguments of these functions.
- `gui_choice` returns `1` if the user exits with `A` or it returns `0` if the user exits with `B`
- `gui_warn` only allows the user to exit with `A`. "Warn" is somewhat of a misnomer -- it was originally made to warn users that something wrong or unexpected happened, but can be used to show any simple information to the user

```c
int gui_menu_6x5(char* question, int options, char** labels, struct pkx* pokemon, enum Generation generation);
int gui_menu_20x2(char* question, int options, char** labels);
```
![gui_menu_6x5](https://i.imgur.com/YuisnjQ.png) ![gui_menu_20x2](https://i.imgur.com/XrLOjRo.png)
- `char* question`: Text shown on the bottom screen
- `int options`: Total number of options to be displayed to the user
- `char** labels`: Array of strings to use as text labels for the options
- `struct pkx* pokemon`: Array of `pkx` structs (see [Enums and Structs](#enums-and-structs) below)
- `enum Generation generation`: Which generation of species info and sprites should be used in the display (some species have different forms in different generations, like Pikachu)

```c
void gui_numpad(int* out, char* hint, int maxDigits);
void gui_keyboard(char* out, char* hint, int maxChars);
```
![gui_numpad](https://i.imgur.com/5h4vjsd.png) ![gui_numpad hint](https://i.imgur.com/x1bPwMh.png)
![gui_keyboard](https://i.imgur.com/JThRhQY.png)

Brings up the numpad/keyboard to allow user input.
- `int* out`: pointer to an existing `int` variable to hold the user's input
- `char* out`: pointer to an existing string variable that should be large enough to hold whatever you're prompting the user for, including the `NULL` terminator
- `char* hint`:
    - **numpad**: string to be shown to the user if they click on the `What?` button in the bottom left
    - **keyboard**: string shown in input box when it's empty
- `int maxDigits`: max length of the number provided by user
- `int maxChars`: max length of the string provided by user, including the `NULL` terminator

```c
int gui_boxes(int* fromStorage, int* box, int* slot, int doCrypt);
```
![gui_boxes](https://i.imgur.com/5qwOewI.png)
- All arguments except `doCrypt` should be pointers to existing variables
- `fromStorage`: whether or not the user's selection is in PKSM's storage (`1`) or save's PC (`0`)
- `box`, `slot`: Box and slot numbers of user's selection
- `doCrypt`: whether this should (`1`) or should not (`0`) it should decrypt and encrypt the boxes itself
    - If you use `gui_boxes` after `sav_box_decrypt`, make sure this is `0`
- Returns `0` if a selection was successfully made

### Save and Storage Functions
```c
int sav_sbo();
int sav_gbo();

// example usage
int ofs = sav_gbo() + 0x0;
```
These are only needed for Gen 4 (DP, PT, HGSS). Gen 4 save files store 2 saves (current and backup) broken up into 3 blocks apiece and the blocks can be mixed up within the file. A Gen 4 save file could look like the following:
- Save 1 (starting at `0x0`): current general block, backup storage block, current HoF block
- Save 2 (starting at `0x40000`): backup general block, current storage block, backup HoF block

The return values of `sav_gbo` and `sav_sbo` point you the proper portion of the file containing the current version of the general and storage blocks respectively.

A value of `0` is returned if used on a Gen 5+ save, meaning they'll have no adverse effect on setting offsets on other games.

#### Encryption and Decryption
```c
void sav_box_decrypt();
void sav_box_encrypt();
```
**IMPORTANT**: These should *always* be used as a pair and *always* in this order. Mixing them or not using them in pairs *will* produce unpredictable results.

Any edits you aim to make should be done after calling `sav_box_decrypt` and before calling `sav_box_encrypt`.

```c
void pkx_decrypt(char* data, enum Generation type);
void pkx_encrypt(char* data, enum Generation type);
```
For encrypting or decrypting PKX data, usually for reading from or writing to a `.pk*` file
- `char* data`: pointer to an existing variable with Pokémon data to encrypt/decrypt
- `enum Generation type`: which generation the data comes from, so that it can be properly decrypted/encrypted

#### Pkx Editing
```c
void party_get_pkx(char* data, int slot);
void sav_get_pkx(char* data, int box, int slot);
```
Read Pkm data into a variable
- `char* data`: pointer to an existing variable to write the Pokémon data to
- `slot`: slot within the party or box to read the Pokémon from
- `box`: which box number the Pokémon should be read from

```c
void party_inject_pkx(char* data, enum Generation type, int slot);
void sav_inject_pkx(char* data, enum Generation type, int box, int slot, int doTradeEdits);
void bank_inject_pkx(char* data, enum Generation type, int box, int slot);
```
Storing pkm data from a variable into the party, PC boxes, or PKSM bank
- `char* data`: pointer to an existing variable to write the Pokémon data from
- `enum Generation type`: which generation the data comes from, so that it can be properly written
- `slot`: slot within the party or box to inject to
- `box`: which box number the Pokémon should be injected into
- `doTradeEdits`: boolean controlling whether PKSM applies appropriate trade logic (non-`0`) or not (`0`)

### IO Functions
```c
char* current_directory();
```
Returns the directory from which the script was called

```c
struct directory* read_directory(char* dir);
```
For reading the files in directory `dir`. Returns a `directory` struct (see [Enums and Structs](#enums-and-structs) below for details)
- The file names stored within must be manually freed
- The file name array must be manually freed
- The directory structure must be manually freed

### Config Reading Functions
All these functions return the values exactly as they appear in PKSM's `config.json`
```c
char* cfg_default_ot();
```
- Older generations have smaller OT name limits so depending on the contents of the default OT field and the generation(s) you're editing your script may have to trim the string to fit
- You will have to use `utf8_to_utf16` (see [Text Functions](#text-functions) below) before writing the OT to a pkm or the save

```c
unsigned int cfg_default_tid();
unsigned int cfg_default_sid();
```
Return 5-digit IDs

```c
int cfg_default_day();
int cfg_default_month();
int cfg_default_year();
```
- Scripts should check the result of `cfg_default_year()` to make sure it is the correct format for the intended usage (i.e. 2-digit or 4-digit) and modify it if necessary

### Networking Functions
```c
char* net_ip();
```
Returns the IP address of your 3DS as a string

```c
int net_udp_recv(char* buffer, int size, int* received);
int net_tcp_recv(char* buffer, int size, int* received);
```
Receives data (such as pkx, WC, etc.) sent from a client running on another device
- `char* buffer`: pointer to an existing `char` Array to hold the data being received
- `int size`: expected number of bytes
- `int* received`: pointer to an existing `int` variable to hold the number of received bytes
- returns `0` if data was successfully received (scripts will need to check the validity of the received data themselves)

```c
int net_tcp_send(char* ip, int port, char* buffer, int size);
```
Sends data to a compatible client on another device
- `char* ip`: IP address of device to send data to
- `int port`: port on device to send data to
- `char* buffer`: data to send
- `int size`: size of data being sent, in bytes
- returns `0` if successful

### Text Functions
```c
char* i18n_species(int species);
```
Translates the National Dex number of a species into it's name in the user's language

```c
char* utf16_to_utf8(char* data);
char* utf8_to_utf16(char* data);
```
Converts strings between UTF8 (like OT is stored in config) and UTF16 (like OT is stored in save files)
- returned strings must be manually freed

### Enums and Structs
```c
enum Generation {
    GEN_FOUR,
    GEN_FIVE,
    GEN_SIX,
    GEN_SEVEN,
    GEN_LGPE
};

// example usage
int pokePick = gui_menu_6x5("Choose Honey Tree Pokémon", optNum, &treePokes[0], &pokes[0], GEN_FOUR);
```
When something depends on the generation being worked with (sprites, data structure, etc.), use one of these. The example usage code comes from the [DPPT Honey Tree](https://github.com/FlagBrew/PKSM-Scripts/blob/master/src/universal/DPPt%20-%20Honey%20Tree%20Manipulator.c) script, though there are other examples available in the [repo](https://github.com/FlagBrew/PKSM-Scripts/tree/master/src).

```c
struct pkx {
    int species;
    int form;
};
```
- `species` is the National Dex number of the Pokémon you want to display
- `form` is always necessary, even if all the species you're working with do not have alternate forms. If you're not trying to display a certain alternate form, set `form` to `0`.

```c
struct directory {
    int count;
    char** files;
};
```

## Tips
- Avoid allocating arrays based a size stored in a variable (for instance `char buffer[size];`). Use something along the lines of `char* buffer = malloc(size);` instead and free the pointer after use.

### Accessing Save Values
All data types in these examples are signed, but unsigned works just as well (and might be needed instead depending on the data you're working with)
```c
// 1 byte value
char val = saveData[offset];
saveData[offset] = val;

// 2 byte values
short val = *(short *)(saveData + offset);
*(short)(saveData + offset) = val;

// 4 byte values
int val = *(int *)(saveData + offset);
*(int)(saveData + offset) = val;
```


## Differences From C90
> From [this wiki page](https://code.google.com/archive/p/picoc/wikis/DifferencesFromC90.wiki)

### How picoC differs from C90
picoC is a tiny C language, not a complete implementation of C90. It doesn't aim to implement every single feature of C90 but it does aim to be close enough that most programs will run without modification.

picoC also has scripting abilities which enhance it beyond what C90 offers.


### C preprocessor
There is no true preprocessor in picoC. The most popular preprocessor features are implemented in a slightly limited way.

#### #define
define macros are implemented but have some limitations. They can only be used as part of expressions and operate a bit like functions. Since they're used in expressions they must result in a value.

#### #if / #ifdef / #else / #endif
The conditional compilation operators are implemented, but have some limitations. The operator "defined()" is not implemented. These operators can only be used at statement boundaries.

#### #include
include is supported however the level of support depends on the specific port of picoC on your platform. Linux/UNIX and cygwin support #include fully.


### Function declarations
This style of function declaration is supported:

`int my_function(char param1, int param2, char *param3) { ... }`

The old "K&R" form of function declaration is not supported.


### Predefined macros
A few macros are pre-defined:

- **picoC_VERSION** - gives the picoC version as a string eg. `"v2.1 beta r524"`
- **LITTLE_ENDIAN** - is 1 on little-endian architectures or 0 on big-endian architectures
- **BIG_ENDIAN** - is 1 on big-endian architectures or 0 on little-endian architectures

### Function pointers
Pointers to functions are currently not supported.


### Storage classes
Many of the storage classes in C90 really only have meaning in a compiler so they're not implemented in picoC. This includes: static, extern, volatile, register and auto. They're recognised but currently ignored.


### struct and unions
Structs and unions can only be defined globally. It's not possible to define them within the scope of a function.

Bitfields in structs are not supported.


### Linking with libraries
Because picoC is an interpreter (and not a compiler) libraries must be linked with picoC itself. Also a glue module must be written to interface to picoC. This is the same as other interpreters like python.

If you're looking for an example check the interface to the C standard library time functions in cstdlib/time.c.


### goto
The goto statement is implemented, but only supports forward gotos, not backward. The rationale for this is that backward gotos are not necessary for any "legitimate" use of goto.

Some discussion on this topic:
* http://www.cprogramming.com/tutorial/goto.html
* http://kerneltrap.org/node/553/2131
