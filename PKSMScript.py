#!/usr/bin/python3
import argparse, os


# PKSM script structure
# u8 magic[10]        // PKSMSCRIPT
# u32 offset          // save offset to write the data to
# u32 length          // payload length
# u8 payload[len]     // payload data
# u32 repeat_times    // repeat payload n times
# ...
 
 
parser = argparse.ArgumentParser(description = 'Creates .pksm script files')
parser.add_argument('output', help = 'Output file name')
parser.add_argument('-d', metavar = ('subdir'), help = 'Subdirectory in which to create the script')
parser.add_argument('-i', action = 'append', nargs = 4, metavar = ('ofs', 'len', 'pld', 'rpt'), help = 'ofs: offset to write the payload to. len: payload length. pld: payload (can be an integer or a file path), rpt: repeat n times.')


def main(args):
	script = b"PKSMSCRIPT"
	outdir = ""
	
	if args.d:
		outdir = "build/" + args.d + "/"
	if outdir != "" and not os.path.exists(outdir):
		os.makedirs(outdir)

	for arg in args.i:
		argoffset  = arg[0]
		arglength  = arg[1]
		argpayload = arg[2]
		argrepeat  = arg[3]
		
		offset = int(argoffset, 0)
		length = int(arglength, 0)
		
		try:
			payload = int(argpayload, 0).to_bytes(length, byteorder = 'little')
		except ValueError as e:
			with open(argpayload, 'rb') as f:
				payload = f.read(length)		
		
		repeat = int(argrepeat, 0)

		script += offset.to_bytes(0x4, byteorder = 'little')
		script += length.to_bytes(0x4, byteorder = 'little')
		script += payload
		script += repeat.to_bytes(0x4, byteorder = 'little')
	
		with open(outdir + args.output + '.pksm', 'wb') as f:
			f.write(script)

	
if __name__ == '__main__':
	main(parser.parse_args())