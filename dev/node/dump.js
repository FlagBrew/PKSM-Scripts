#!/usr/bin/env node
const fse = require('fs-extra');
const ArgumentParser = require('argparse').ArgumentParser;
const Sav = require('./Sav');

const parser = new ArgumentParser({
    description: 'Dump portion of file',
});
parser.addArgument('input', { help: 'Input file name' });
parser.addArgument('output', { help: 'Output file name' });
parser.addArgument('off', { help: 'Start offset' });
parser.addArgument('len', { help: 'Length to dump' });

const dumpData = (args) => {
    const save = new Sav(args.input);
    const ofs = +args.off;         // beginning of data to pull
    const len = +args.len;            // total number of bytes of data to pull

    fse.writeFileSync(args.output, save.getCurrent().slice(ofs, ofs + len));
};

module.exports = dumpData;

// execute if called directly from command line
if (require.main === module) {
    dumpData(parser.parseArgs());
}
