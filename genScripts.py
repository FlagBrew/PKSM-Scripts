#!/usr/bin/env python3
import shlex, PKSMScript, sys, glob, shutil, os

games = ["USUM", "SM", "ORAS", "XY", "B2W2", "BW", "HGSS", "PT", "DP"]

def main(args):
	print("Generating scripts...")
	shutil.rmtree("build", True)
	if os.path.isdir("scripts"):
		for game in games:
			if os.path.isfile("src\scripts%s.txt" % game):
				generate(game)
				dirchk(game)
				scriptFiles = glob.glob("*.pksm")
				for pksmFile in scriptFiles:
					if os.path.isdir("scripts\%s" % game.lower()):
						if os.path.isfile("scripts\%s\%s" % (game.lower(), pksmFile)):
							os.remove("scripts\%s\%s" % (game.lower(), pksmFile))
							shutil.move(pksmFile, "scripts\%s" % game.lower())
						else:
							shutil.move(pksmFile, "scripts\%s" % game.lower())
					else:
						os.mkdir(game.lower())
						shutil.move(pksmFile,game.lower())
						shutil.move(game.lower(), "scripts")
	else:
		os.mkdir("scripts")
		for game in games:
			if os.path.isfile("src\scripts%s.txt" % game):
				generate(game)
				dirchk(game)
				os.mkdir(game.lower())
				scriptFiles = glob.glob("*.pksm")
				for pksmFile in scriptFiles:
					shutil.move(pksmFile,game.lower())
				shutil.move(game.lower(), "scripts")

	if os.path.isdir("__pycache__"):
		shutil.rmtree("__pycache__", True)
		
def dirchk(game):
	if os.path.exists("src/" + game.lower()):
		shutil.copytree("src/" + game.lower(), "scripts/" + game.lower())

	if os.path.exists("build"):
		for f in os.listdir("build"):
			shutil.move("build/" + f, "scripts/" + game.lower())
	
def generate(game):
	with open(os.path.join("src", "scripts%s.txt" % game)) as pksmArgFile:
		for line in pksmArgFile:
			if (not line.startswith('#')):
				line.replace('\\', '/')
				pksmArgs = PKSMScript.parser.parse_args(shlex.split(line))
				PKSMScript.main(pksmArgs)

if __name__ == '__main__':
	main(sys.argv)
