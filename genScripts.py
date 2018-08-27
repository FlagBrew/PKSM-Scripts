#!/usr/bin/env python3
import shlex, PKSMScript, sys, glob, shutil, os

games = ["USUM", "SM", "ORAS", "XY", "B2W2", "BW", "HGSS", "PT", "DP"]

def main(args):
	shutil.rmtree("scripts", True)
	os.mkdir("scripts")
	for game in games:
		generate(game)
		os.mkdir("scripts/" + game.lower())
		if os.path.exists("build"):
			for f in os.listdir("build"):
				shutil.move("build/" + f, "scripts/" + game.lower())
		scriptFiles = glob.glob("*.pksm")
		for pksmFile in scriptFiles:
			shutil.move(pksmFile,"scripts/" + game.lower())

def generate(game):
	with open(os.path.join("src", "scripts%s.txt" % game)) as pksmArgFile:
		for line in pksmArgFile:
			if (not line.startswith('#')):
				line.replace('\\', '/')
				pksmArgs = PKSMScript.parser.parse_args(shlex.split(line))
				PKSMScript.main(pksmArgs)

if __name__ == '__main__':
	main(sys.argv)
