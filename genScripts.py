#!/usr/bin/env python3
import shlex, PKSMScript, sys, glob, shutil, os

games = ["USUM", "SM", "ORAS", "XY", "B2W2", "BW", "HGSS", "PT", "DP"]

def main(args):
	print("Generating scripts...")
	shutil.rmtree("scripts", True)
	shutil.rmtree("build", True)
	os.mkdir("scripts")
	if os.path.exists("src/universal"):
		# shutil.copytree("src/universal", "scripts/universal")
		os.mkdir("scripts/universal")
		for path, _, files in os.walk("src/universal"):
			for fullname in files:
				data = ""
				with open(os.path.join(path, fullname), 'r') as f:
					data = f.read()

				data = data.replace("\r\n", "\n")
				lines = data.split("\n")
				out = ""
				for line in lines:
					line = line.strip()
					# preprocessor directives and comments
					if "#" in line or "//" in line:
						out += line + "\n"
					# just in case there are multiline strings/macros
					elif line[len(line) - 1:] == "\\":
						out += line + "\n"
					# all other cases
					else:
						out += line
				with open(os.path.join(path.replace("src/", "scripts/"), fullname), 'w') as f:
					f.write(out)
	for game in games:
		generate(game)

		if os.path.exists("src/" + game.lower()):
			shutil.copytree("src/" + game.lower(), "scripts/" + game.lower())
		else:
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
