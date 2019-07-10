#!/usr/bin/env python3
import argparse
import glob
import os
import shlex
import shutil
import sys

import PKSMScript


class PatchedParser(argparse.ArgumentParser):
    def error(self, message):
        # raise error rather than exit
        raise argparse.ArgumentError(None, message)


games = [
    "LGPE",
    "USUM", "SM",
    "ORAS", "XY",
    "B2W2", "BW",
    "HGSS", "PT", "DP"]

# patch PKSMScript's argument parser to prevent exiting on error
# and allow logging of all errors
parser = PatchedParser(parents=[PKSMScript.parser], add_help=False)


def main(args):
    print("Generating scripts...")
    shutil.rmtree("build", True)
    if not os.path.exists("scripts"):
        os.mkdir("scripts")
    failed_scripts = dict()
    fail_count = 0
    if len(args) > 1:
        to_compile = [g.upper() for g in args[1:] if g.upper() in games]
        if not len(to_compile):
            print('No valid games requested. Exiting without compiling.')
            sys.exit()
    else:
        to_compile = games
    for game in to_compile:
        if os.path.exists("src/scripts{}.txt".format(game)):
            failed_scripts[game] = generate(game)
            fail_count += len(failed_scripts[game])
            if not len(failed_scripts[game]):
                del failed_scripts[game]
            move_scripts(game.lower())
        else:
            print("File does not exist: src/scripts{}.txt\n".format(game))

    print('Finished generating scripts')
    if fail_count:
        print('\n\nScripts that failed to compile:\n')
        for game, scripts in failed_scripts.items():
            for script in scripts:
                print('{}: {}'.format(game, script))


def generate(game):
    failures = []
    with open(os.path.join("src", "scripts{}.txt".format(game))) as arg_file:
        for line in arg_file:
            if (not line.startswith('#')):
                line.replace('\\', '/')
                try:
                    pksm_args = parser.parse_args(shlex.split(line))
                    PKSMScript.main(pksm_args)
                except:
                    # catch errors from both arg parsing and compiling
                    bad_script = '{}    Reason: {}'.format(
                        line, sys.exc_info()[1])
                    failures.append(bad_script)
    return failures


def move_scripts(game):
    if not os.path.exists("scripts/" + game):
        os.mkdir("scripts/" + game)

    if os.path.exists("build"):
        for f in os.listdir("build"):
            shutil.move("build/" + f, "scripts/" + game)
        shutil.rmtree('build', True)
    script_files = glob.glob("*.pksm")
    for pksm_file in script_files:
        if os.path.exists("scripts/{}/{}".format(game, pksm_file)):
            os.remove("scripts/{}/{}".format(game, pksm_file))
        shutil.move(pksm_file, "scripts/" + game)


if __name__ == '__main__':
    main(sys.argv)
