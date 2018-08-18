#!/usr/bin/env node
/* eslint no-continue: "off" */
const { createWriteStream, readFileSync } = require('fs');

const cli = require.main === module;

/** argparse code (Python 3)

parser = argparse.ArgumentParser(description = 'Creates .pksm script files')
parser.add_argument('output', help = 'Output file name')
parser.add_argument('-i', action = 'append', nargs = 4, metavar = ('ofs', 'len', 'pld', 'rpt'), help = 'ofs: offset to write the payload to. len: payload length. pld: payload (can be an integer or a file path), rpt: repeat n times.')
**/

const pksmScript = (args) => {
    const scriptName = args.shift();
    const output = createWriteStream(`${scriptName}.pksm`);

    output.write('PKSMSCRIPT');

    while (args.length >= 5) {
        const ofsBuf = Buffer.allocUnsafe(4);
        const lenBuf = Buffer.allocUnsafe(4);
        const rptBuf = Buffer.allocUnsafe(4);

        args.shift(); // discard '-i'
        ofsBuf.writeUInt32LE(+(args.shift()), 0);
        const len = +args.shift();
        const pldArg = args.shift();
        rptBuf.writeUInt32LE(+(args.shift()), 0);

        lenBuf.writeUInt32LE(len, 0);

        let pldBuf;
        if ((+pldArg) >= 0) {
            pldBuf = Buffer.allocUnsafe(len).fill(0);
            pldBuf.writeUIntLE(+pldArg, 0, len);
        } else {
            try {
                pldBuf = readFileSync(pldArg);
            } catch (e) {
                console.log(`There was an error trying to read file ${pldArg}`);
                console.error(e);
                continue;
            }
        }

        const buf = Buffer.concat([ofsBuf, lenBuf, pldBuf, rptBuf]);

        output.write(buf);
    }

    output.end(() => {
        if (cli) {
            console.log(`${scriptName}.pksm compiled`);
        }
        if (args.length) {
            console.log(`Some arguments went unused${!cli ? ` while compiling ${scriptName}.pksm` : ''}`);
        }
    });
};

module.exports = pksmScript;

// execute if called directly from command line
if (cli) {
    pksmScript(process.argv.slice(2));
}
