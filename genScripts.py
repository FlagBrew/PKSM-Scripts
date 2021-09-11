#!/usr/bin/env python3
import shlex, PKSMScript, sys, glob, shutil, os

games = ["LGPE", "USUM", "SM", "ORAS", "XY", "B2W2", "BW", "HGSS", "PT", "DP", "RS", "E", "FRLG"]

def main(args):
	print("Generating scripts...")
	script_list = []
	shutil.rmtree("scripts", True)
	shutil.rmtree("build", True)
	os.mkdir("scripts")
	if os.path.exists("src/universal"):
		# shutil.copytree("src/universal", "scripts/universal")
		script_list.extend(cleanCScripts("src/universal"))
	for game in games:
		script_list.extend(generate(game))

		if os.path.exists("src/" + game.lower()):
			script_list.extend(cleanCScripts("src/" + game.lower()))
		else:
			os.mkdir("scripts/" + game.lower())

		if os.path.exists("build"):
			for f in os.listdir("build"):
				shutil.move("build/" + f, "scripts/" + game.lower())
		scriptFiles = glob.glob("*.pksm")
		for pksmFile in scriptFiles:
			shutil.move(pksmFile, "scripts/" + game.lower())
	with open("script_list.txt", "w", encoding="UTF-8") as f:
		f.write("\n".join(script_list))

def generate(game):
	path = os.path.join("src", "scripts%s.txt" % game)
	script_list = []
	if os.path.exists(path):
		with open(path, 'r', encoding="UTF-8") as pksmArgFile:
			for line in pksmArgFile:
				if not line.startswith('#'):
					line.replace('\\', '/')
					pksmArgs = PKSMScript.parser.parse_args(shlex.split(line))
					PKSMScript.main(pksmArgs)
					if pksmArgs.d:
						script_list.append(f"{game.lower()}/{pksmArgs.d}/{pksmArgs.output}.pksm")
					else:
						script_list.append(f"{game.lower()}/{pksmArgs.output}.pksm")
	return script_list

def cleanCScripts(folder):
	os.mkdir(folder.replace("src/", "scripts/"))
	scripts_list = []
	for path, _, files in os.walk(folder):
		for fullname in files:
			data = ""
			with open(os.path.join(path, fullname), 'r', encoding="UTF-8") as f:
				data = f.read()

			data = data.replace("\r\n", "\n")

			with open(os.path.join(path.replace("src/", "scripts/"), fullname), 'w', encoding="UTF-8") as f:
				f.write(data)
			scripts_list.append(f"{path[4:]}/{fullname}")
	return scripts_list

if __name__ == '__main__':
	main(sys.argv)
