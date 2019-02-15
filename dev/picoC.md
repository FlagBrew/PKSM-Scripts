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
        - D = 10, P = 11, Pt = 12, HG = 7, SS = 8
            - Diamond saves cannot be told apart from Pearl saves and HeartGold saves cannot be told apart from SoulSilver saves
        - B = 21, W = 20, B2 = 23, W2 = 22
        - X = 24, Y = 25, OR = 27, AS = 26
        - S = 30, M = 31, US = 32, UM = 33
        - LGP = 42, LGE = 43

### Available Functions
```c
int gui_choice(char* lineOne, char* lineTwo);
void gui_warn(char* lineOne, char* lineTwo);
int gui_menu_6x5(char* question, int options, char** labels, struct pkx* pokemon, enum Generation generation);
int gui_menu_20x2(char* question, int options, char** labels);
void gui_keyboard(char* out, char* hint, int maxChars);
void gui_numpad(int* out, char* hint, int maxDigits);
int gui_boxes(int* fromStorage, int* box, int* slot);
// sav and storage
int sav_sbo();
int sav_gbo();
void sav_box_decrypt();
void sav_box_encrypt();
void sav_get_pkx(char* data, int box, int slot);
void sav_inject_pkx(char* data, enum Generation type, int box, int slot);
void sav_inject_ekx(char* data, enum Generation type, int box, int slot);
void party_get_pkx(char* data, int slot);
void bank_inject_pkx(char* data, enum Generation type, int box, int slot);
// io
char* current_directory();
struct directory* read_directory(char* dir);
// configurations
char* cfg_default_ot();
unsigned int cfg_default_tid();
unsigned int cfg_default_sid();
int cfg_default_day();
int cfg_default_month();
int cfg_default_year();
// networking
char* net_ip();
int net_tcp_recv(char* buffer, int size, int* received);
int net_tcp_send(char* ip, int port, char* buffer, int size);
int net_udp_recv(char* buffer, int size, int* received);
```

### Other
```c
enum Generation {
    GEN_FOUR,
    GEN_FIVE,
    GEN_SIX,
    GEN_SEVEN,
    GEN_LGPE
};
struct pkx {
    int species;
    int form;
};
struct directory {
    int count;
    char** files;
};
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

Some discussion on this topic: * http://www.cprogramming.com/tutorial/goto.html * http://kerneltrap.org/node/553/2131

### Arrays of variable size

Avoid allocating arrays which size resides in a variable, for instance `char buffer[size];`, which causes issues during script execution. Use instead `char* buffer = malloc(size);` and free the pointer after use.

### Scripting enhancements
#### Interactive mode
picoC can be used interactively, from a command line. In Linux/UNIX/cygwin run it as:

`picoC <module1.c> <module2.c>...`

You'll be presented with a picoC command prompt. You can type programs directly into the picoC command line and call functions directly as well.

Unlike standard C you can write C commands directly on the command line and they'll be executed immediately. eg.

`int i; for (i = 1; i <= 10; i++) printf("Hello world: %d\n", i);`

Use your operating system's end of file character to quit the interactive mode. (Control-D is end of file in Linux/UNIX)

#### Deleting functions or variables

You may want to delete a function or variable declaration in interactive mode so you can re-declare it. Use "delete whatever;" to do this.

#### Running programs from the command line

If you're running a picoC program from the command line on Linux/UNIX/cygwin you can invoke it like:

`picoC <module1.c> <module2.c>...`

The main() function will be run once the program is loaded. To use command line arguments with it do:

`picoC <module1.c> <module2.c>... - arg1 arg2...`

If you're running a script which has no main() function run:

`picoC -s <module1.c> <module2.c>... - arg1 arg2...`

---

## Discord
Messages from the FlagBrew Discord intended to help with understanding the picoC API and usage

```
-= from 16 Oct 2018 =-
[9:07 PM] piepie62: Oh, I forgot to put in the arguments
[9:09 PM] piepie62: Note: <picoc_unix.h> isn't an actual header, but a virtual one that provides the PKSM API
[9:09 PM] piepie62: It's name is also subject to change
[9:56 PM] piepie62: @SpiredMoth That'll be a better example for you, considering that scripts will want to edit the save's data
[9:58 PM] piepie62: For the syntax of editing it, just look up how pointers work
[10:03 PM] SpiredMoth: Which files/folders of PKSM's source should I look to for learning the scripting API?
[10:04 PM] piepie62: Well, currently that example uses all of the useful functions and structures
[10:05 PM] piepie62: But source/picoc/platform/library_unix.c has what would be most useful for you, specifically lines 25-28
[10:06 PM] piepie62: The strings there are the function declarations
[11:54 PM] piepie62: @SpiredMoth Oh! Forgot to mention: the "question" string can contain newline characters, and will be properly separated and centered with respect to them


-= from 25 Oct 2018 =-
[8:42 PM] SpiredMoth: @piepie62 here's my first attempt at making a picoC script. Does this look right (like it will work)? https://gist.github.com/SpiredMoth/11f9982b644b18c5bfad3e7362264984
[8:58 PM] piepie62: That appears correct.
[8:58 PM] piepie62: Will it work? Well, that's a different issue entirely lol
[8:59 PM] piepie62: Would you like a build to test picoC scripts?
[8:59 PM] SpiredMoth: Can the patron build use them?
[8:59 PM] piepie62: Honestly, I don't know
[9:00 PM] piepie62: Even if it can, it definitely won't have the small amount of debugging I can allow with a new build
[9:02 PM] piepie62: Although, now that I think about it, you could build it for yourself if you already have all the devkitPro stuff set up
[9:02 PM] piepie62: If not, I'll just give you a build if you want it
[9:03 PM] piepie62: Ah, okay, there's a slight problem
[9:05 PM] piepie62: You can't save non-ASCII characters in your source files
[9:06 PM] piepie62: Instead, you'll need to use their unicode values directly
[9:07 PM] piepie62: So the Japanese should be \u65E5\u672c\u8A9E, if I got that correct
[9:08 PM] piepie62: Also, your message is too long lol
[9:08 PM] piepie62: Put in a \n to split it into multiple lines
[9:08 PM] SpiredMoth: What's the limit on the message?
[9:09 PM] piepie62: I don't have an exact limit
[9:09 PM] piepie62: It's not a length issue, it's an issue of it being perfectly centered and going off the screen
[9:11 PM] SpiredMoth: Now I have to look up the Unicode values for the Korean entry
[9:13 PM] piepie62: The ñ and ç aren't good either; they need to be unicoded
[9:14 PM] piepie62: ... Oh
[9:14 PM] piepie62: Uh
[9:14 PM] piepie62: Apparently escape sequences don't work correctly with picoC
[9:15 PM] piepie62: Or at least the ones I just tried, anyway
[9:18 PM] SpiredMoth: Well, I updated the gist with the escaped characters and the \n
[9:25 PM] piepie62: Well, shoot
[9:26 PM] piepie62: \uxxxx escape sequences are C99, and picoC only does slightly-dumbed-down C90
[9:27 PM] SpiredMoth: So I should use the English names of all the languages
[9:33 PM] piepie62: I guess... that's a glaring oversight, though. I'm going to look for more about that
[10:30 PM] piepie62: @SpiredMoth After the next commit, the way to get the version will be unsigned char version = *argv[2];
[10:31 PM] piepie62: Also note, this is a game-defined version field
[10:31 PM] SpiredMoth: Time to work up the logic for choosing the target offset based on version then
[10:31 PM] piepie62: Should just be a switch
[10:32 PM] SpiredMoth: Is it going to be the game's index like found in the "source game" field of a pkx?
[10:32 PM] piepie62: Yep, exactly
[10:33 PM] piepie62: Except DP will have the same version because it isn't actually stored in the file
[10:33 PM] piepie62: Same will happen with HGSS
[10:34 PM] SpiredMoth: Scripts really only need specificity down to the pair
[10:34 PM] piepie62: Yeah, I know
[10:34 PM] piepie62: Just wanted to make sure it was known
[10:47 PM] SpiredMoth: This should work, right? (not sure if there's anything bad about using the ternary here)
char choice = (char) gui_menu20x2("Choose the language you want for your save", version < 30 ? 7 : 9, &languages[0]);
[10:47 PM] piepie62: Should work, I agree(edited)
[10:47 PM] piepie62: Will it work? :shrug:
[10:48 PM] piepie62: Sometimes picoC does weird shit
[10:48 PM] SpiredMoth: Assuming that works, the only thing I have left to work on for the language script is dealing with DS games (no changing language for them)
[10:48 PM] piepie62: Yep
[11:19 PM] SpiredMoth: Is there anything wrong with ending a switch case with return rather than break?
[11:19 PM] piepie62: Nope!
[11:19 PM] piepie62: Besides the fact that it obviously won't continue execution
[11:20 PM] SpiredMoth: Now to decide what the return value should be for DS games
[11:21 PM] piepie62: I mean, I don't even really process the return value right now
[11:22 PM] piepie62: Either way, any negative number could just indicate failure
[11:23 PM] piepie62: The exact value would be determined by the script writer
[11:23 PM] piepie62: But I don't think it matters, as long as it's unique within the script
[11:24 PM] SpiredMoth: If I want to give the user feedback, like what language they just set their save to, I should use gui_warn?
[11:24 PM] piepie62: Yep
[11:25 PM] piepie62: It's kind of a misnomer; I designed it for warnings, then realized it could be used for general feedback
[11:25 PM] piepie62: If you want them to be able to press B to exit it, you can use gui_choice and just do nothing with the return value(edited)
[11:27 PM] piepie62: gui_warn doesn't allow pressing B to exit because it's assumed that you don't want people zooming past it by pressing B
[11:27 PM] piepie62: I guess the same could be said about A, but one of the buttons has to be used :shrug:
[11:27 PM] SpiredMoth: So use gui_choice like you did in the sample in the repo?
[11:28 PM] piepie62: gui_choice and gui_warn are the same thing, except for the fact that you can exit gui_choice with either A or B and it returns which button is pressed, with A being true
[11:29 PM] piepie62: Actually, on second thought, probably don't use gui_choice just to let users press B; it says confirm or cancel on it


-= from 28 Oct 2018 =-
[9:18 PM] SpiredMoth: What's the reasoning behind passing save length to C scripts?
[9:19 PM] piepie62: Prevent segfaults? I actually don't remember why I did
[9:20 PM] SpiredMoth: Also I'm starting to question the need for atoi in this unsigned char* saveData = (unsigned char*) atoi(argv[0]);
[9:21 PM] piepie62: I ran into issues passing it as a raw pointer, so just decided to pass the value of the pointer lol
[9:22 PM] SpiredMoth: Well, while studying what atoi does it seems to me that there's a chance of losing data from the beginning of the save due to its use (it will skip any whitespace it finds at the beginning of the argument before converting it to an int)
[9:24 PM] piepie62: Yes, but in the passing code, it uses stoi to get the integer value of the pointer
[9:24 PM] piepie62: Basically, I turn the pointer into an integer, pass the integer as text, then convert that text to an integer to a pointer
[9:25 PM] SpiredMoth: That I didn't know
[9:25 PM] piepie62: It's all good
[9:30 PM] SpiredMoth: Is there an easier way to read/write multiple bytes than going one-by-one?
[9:31 PM] piepie62: @SpiredMoth Would memcpy fit your needs?
[9:32 PM] piepie62: It wouldn't if you're trying to write a multibyte value due to the little-endianness of the 3DS
[9:32 PM] piepie62: In which case you should cast it to an unsigned short* for two-byte values and unsigned int* for four
[9:33 PM] SpiredMoth: Would using unsigned short and unsigned int work for reading too? That would solve the use cases that are coming to mind atm
[9:33 PM] piepie62: Yes
[9:34 PM] piepie62: The weird thing about doing that, though, is that you would have to do it a little differently
[9:39 PM] piepie62: @SpiredMoth Instead of the normal bracket notation, you'll need to use something like this: unsigned short value = *(unsigned short*)(saveData + offset)
[9:40 PM] SpiredMoth: And that will read the value properly, considering endianness?
[9:40 PM] piepie62: Yes
[9:41 PM] piepie62: To write back, *(unsigned short*)(saveData + offset) = value;


-= from 31 Oct 2018 =-
[2:37 PM] SpiredMoth: If I wanted to have an array of pkx in a script but I can't fill it programmatically (like the Vivillon one in the example), would I have to hardcode the entire thing?
[2:39 PM] piepie62: What do you mean by not hardcoding it?
[2:40 PM] SpiredMoth: I guess I should ask "how I should include it?"
[2:41 PM] piepie62: Well, there are two things you could do. I'll type them up and paste it here
[2:47 PM] piepie62: Actually, there's a third option
[2:52 PM] piepie62: Option 1:
struct pkx array[] = {
    {<speciesValue>, <formValue> },
    {<speciesValue>, <formValue> }
};
[2:53 PM] piepie62: Option 2:
struct pkx array[2];

array[0].species = <speciesValue>;
array[0].form = <formValue>;
array[1].species = <speciesValue>;
array[1].form = <formValue>;
[2:53 PM] piepie62: Option 3:
int array[][] = {
    {<speciesValue>, <formValue>},
    {<speciesValue>, <formValue>}
};

struct pkx *pkxArray = (struct pkx*) &array[0];
[2:54 PM] piepie62: All of those SHOULD work (if you fill in the array bounds, that is), but picoC is a subset of C90, so I can't guarantee they will
[2:54 PM] SpiredMoth: It the formValue mandatory?
[2:56 PM] piepie62: In option three, yes, in option two, I don't know, and in option one, very likely
[2:57 PM] piepie62: Option two I'm not sure, because the form value may not be initialized to zero
[3:20 PM] LiquidFenrir: @piepie62 option 3 seems terrible
[3:20 PM] LiquidFenrir: 1 is best
[3:21 PM] piepie62: Yeah, I would agree that option three is terrible, but it would work, which is why I provided it as an option. Number one is the best, yes, but I'm not even sure it would work


-= from 2 Nov 2018 =-
[10:42 PM] piepie62: @SpiredMoth You know how I told you that you could use escape codes, then it didn't work?
[10:42 PM] piepie62: I just made it work


-= from 3 Nov 2018 =-
[10:14 AM] piepie62: Working on that escape code thing gave me a much better understanding of UTF-8... allowing me to do the latest commit :smiley:


-= from 12 Nov 2018 =-
[3:01 PM] SpiredMoth: I've got 2 new questions relating to picoC scripts:
1. how should scripts targeting Gen 4 saves deal with GBO/SBO?
2. if we want to combine existing scripts that rely on bins (item pouches, dex filling, etc.), what would be the best/recommended way to include the data?
[3:07 PM] piepie62: For 1, I could provide a GBO/SBO function
[3:08 PM] piepie62: For 2, theoretically fopen and other stdio functions should work
[3:50 PM] piepie62: The other thing about 2 is that a lot of that stuff is probably doable programmatically
[3:50 PM] piepie62: I would resort to fopen only if that fails
[5:32 PM] piepie62: @SpiredMoth About to push SBO/GBO functions, they are named sav_gbo() and sav_sbo(). When used with a save file of any type other than gen 4, they return zero (so that nothing is modified by a different value, like, say, -1)
[6:53 PM] piepie62: By the way, if you want to develop this in a code editor other than a text editor, I made a little dummy header file that makes things work better


-= from 13 Nov 2018 =-
[5:26 PM] piepie62: An update to the above to go with the commit I'm about to push
[5:30 PM] piepie62: @SpiredMoth There's been a change to how generations are handled. Instead of using the raw values, please use the enum that is provided in the above header(edited)
[5:49 PM] piepie62: Do note, I have already changed the Vivillon script as a test and pushed that change


-= from 14 Nov 2018 =-
[2:15 PM] SpiredMoth: Do I have to use a variable to hold the gen, like in the Vivillon script? Or can I just use the value directly (and what value should I use)?
[2:16 PM] piepie62: You can use the value directly. For right now, all of the generations are just GEN_<capital name of number>
[2:17 PM] piepie62: I honestly don't know why I used a variable to hold it there
[2:17 PM] piepie62: Six and seven have no difference in Vivillons, so that was a bit useless
[2:18 PM] SpiredMoth: So there's no difference in which value (6 or 7) is used for the Vivillon script?
[2:21 PM] piepie62: No, because there's no difference in form value/appearance


-= from 5 Dec 2018 =-
[11:50 PM] SpiredMoth: I have a question relating to pkxs and gui_menu6x5: is there an "empty" species option for the pkx? Like if I wanted to provide the user a way to back out of the selection without actually selecting a species
[11:51 PM] piepie62: Hmmm... Currently no. What's the context? I had thought there would never be a need for that
[11:52 PM] SpiredMoth: When I was testing one of my new scripts earlier I executed it before remembering that my main purpose for that session was to get screenshots for reference and didn't actually want to make changes to the save
[11:53 PM] piepie62: ... Why not just exit without saving changes?
[11:53 PM] SpiredMoth: In my case I was able to discard changes, but if the user has made, or will make, changes that they want to keep in that session, it would be nice to offer them an option to exit the script without making changes
[11:53 PM] piepie62: Ahhhh, I see
[11:55 PM] piepie62: That's kind of a "designed flaw" with the entire application, in my opinion. There are very few chances that you get to not save changes, and those that are I don't even entirely like because they are different in that way
[11:55 PM] piepie62: Not to mention, it already has a confirmation screen, so I don't really think that would be that useful
[11:56 PM] piepie62: I would like to ask for @bernardogiordano's opinion on this, though
[11:57 PM] piepie62: Like, yeah, I can understand where you're coming from, but I both can't think of a good way to do it and don't like the idea in general
[11:58 PM] piepie62: Even where it currently exists in the application


-= from 7 Dec 2018 =-
[8:00 PM] SpiredMoth: I'm also confused on how the encrypt and decrypt functions are supposed to be used if they're void of both parameters and a return
[8:00 PM] piepie62: They operate on the save directly from inside of PKSM
[8:01 PM] piepie62: PicoC scripts get the value of a pointer to the actual data, and those two operate on the Sav object inside of PKSM proper
[8:02 PM] piepie62: Which has the same pointer
[8:05 PM] SpiredMoth: So a script would execute decrypt, do whatever edits it's supposed to, execute encrypt, then return?
[8:05 PM] piepie62: Yep
[8:05 PM] piepie62: Running an odd number of those functions, or not in that order, would also end up in bad things happening
[8:08 PM] piepie62: Actually, a better way to put that would be always use them in a pair
```
