#!/usr/bin/python3
import argparse

 
parser = argparse.ArgumentParser(description = 'Dump portion of file')
parser.add_argument('input', help = 'Input file name')
parser.add_argument('output', help = 'Output file name')
parser.add_argument('offset', help = 'Start offset')
parser.add_argument('length', help = 'Length to dump')


def main(args):
	offset = int(args.offset, 0)
	length = int(args.length, 0)
	with open(args.input, 'rb') as fr:
		buffer = fr.read()
	with open(args.output, 'wb') as fw:
		fw.write(buffer[offset:offset+length])

	
if __name__ == '__main__':
	main(parser.parse_args())