#!/usr/bin/env node
const fse = require('fs-extra');
const ArgumentParser = require('argparse').ArgumentParser;

const parser = new ArgumentParser({
    addHelp: true,
    description: 'Creates .pksm script files',
});
parser.addArgument('output', { help: 'Output file name' });
parser.addArgument('-d', {
    metavar: ['subdir'],
    help: 'Subdirectory in which to create the script',
});
parser.addArgument('-i', {
    action: 'append',
    nargs: 4,
    metavar: ['ofs', 'len', 'pld', 'rpt'],
    help: 'ofs: offset to write the payload to. len: payload length. pld: payload (can be an integer or a file path), rpt: repeat n times.',
});

const pksmScript = (args) => {
    let buf = Buffer.from('PKSMSCRIPT');
    let output = `${args.output.slice(1, args.output.length - 1)}.pksm`;

    if (args.d) {
        output = `build/${args.d.slice(1, args.d.length - 1)}/${output}`;
    }
    fse.ensureFileSync(output);
    output = fse.openSync(output, 'w');

    args.i.forEach((v) => {
        const ofsBuf = Buffer.allocUnsafe(4);
        const lenBuf = Buffer.allocUnsafe(4);
        const rptBuf = Buffer.allocUnsafe(4);

        ofsBuf.writeUInt32LE(+v[0], 0);
        const lenArg = +v[1];
        lenBuf.writeUInt32LE(lenArg, 0);
        rptBuf.writeUInt32LE(+v[3], 0);

        const pldArg = v[2];
        let pldBuf;
        if ((+pldArg) >= 0) {
            pldBuf = Buffer.allocUnsafe(lenArg).fill(0);
            pldBuf.writeUIntLE(+pldArg, 0, lenArg);
        } else {
            try {
                pldBuf = fse.readFileSync(pldArg.slice(1, pldArg.length - 1));
            } catch (e) {
                console.log(`There was an error trying to read file ${pldArg}`);
                console.error(e);
            }
        }

        buf = Buffer.concat([buf, ofsBuf, lenBuf, pldBuf, rptBuf]);

        fse.writeSync(output, buf, 0, buf.length, 0);
    });
    fse.closeSync(output);
};
pksmScript.parser = parser;

module.exports = pksmScript;

// execute if called directly from command line
if (require.main === module) {
    pksmScript(parser.parseArgs());
}
