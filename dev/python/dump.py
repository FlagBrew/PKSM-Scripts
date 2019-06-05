#!/usr/bin/python3
import argparse
from Sav import Sav

parser = argparse.ArgumentParser(description = 'Dump portion of file')
parser.add_argument('input', help = 'Input file name')
parser.add_argument('output', help = 'Output file name')
parser.add_argument('offset', help = 'Start offset')
parser.add_argument('length', help = 'Length to dump')


def main(args):
    save = Sav(args.input)
    offset = int(args.offset, 0)
    length = int(args.length, 0)
    with open(args.output, 'wb') as fw:
        fw.write(save.getCurrent()[offset:offset+length])


if __name__ == '__main__':
    main(parser.parse_args())
