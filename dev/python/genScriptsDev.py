#!/usr/bin/env python3
import shlex, PKSMScript, sys, glob, shutil, os

games = ["usum", "sm", "oras", "xy", "b2w2", "bw", "hgss", "pt", "dp"]

def main(args):
    print("Generating scripts...")
    shutil.rmtree("build", True)
    if not os.path.exists("scripts"):
        os.mkdir("scripts")
    if len(args) > 1:
        for i in range(1, len(args)):
            if os.path.exists("src/scripts%s.txt" % args[i].upper()):
                generate(args[i].upper())
                moveScripts(args[i])
            else:
                print("File does not exist: %s" % ("src/scripts%s.txt" % args[i].upper()))
    else:
        for game in games:
            if os.path.exists("src/scripts%s.txt" % game.upper()):
                generate(game.upper())
                moveScripts(game)

def generate(game):
    with open(os.path.join("src", "scripts%s.txt" % game)) as pksmArgFile:
        for line in pksmArgFile:
            if (not line.startswith('#')):
                line.replace('\\', '/')
                pksmArgs = PKSMScript.parser.parse_args(shlex.split(line))
                PKSMScript.main(pksmArgs)

def moveScripts(game):
    if not os.path.exists("scripts/" + game):
        os.mkdir("scripts/" + game)

    if os.path.exists("build"):
        for f in os.listdir("build"):
            shutil.move("build/" + f, "scripts/" + game)
    scriptFiles = glob.glob("*.pksm")
    for pksmFile in scriptFiles:
        if os.path.exists("scripts/%s/%s" % (game, pksmFile)):
            os.remove("scripts/%s/%s" % (game, pksmFile))
        shutil.move(pksmFile,"scripts/" + game)

if __name__ == '__main__':
    main(sys.argv)
