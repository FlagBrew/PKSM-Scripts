# picoC Script Documentation

## API
### Arguments passed to `main`
- `argv`
    - `argv[0]` save data
    - `argv[1]` save data length
    - `argv[2]` save's game version (game's index number as found in a Pokémon's *source game* field)
        - D = 10, P = 11, Pt = 12, HG = 7, SS = 8
            - Diamond saves cannot be told apart from Pearl saves and HeartGold saves cannot be told apart from SoulSilver saves
        - B = 21, W = 20, B2 = 23, W2 = 22
        - X = 24, Y = 25, OR = 27, AS = 26
        - S = 30, M = 31, US = 32, UM = 33

### Functions Available to Scripts
```c
int gui_choice(char* lineOne, char* lineTwo);
void gui_warn(char* lineOne, char* lineTwo);
int gui_menu6x5(char* question, int options, char** labels, struct pkx* pokemon, int generation);
int gui_menu20x2(char* question, int options, char** labels);
```

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
```
