#!/usr/bin/env node
const { createReadStream, createWriteStream } = require('fs');
const ArgumentParser = require('argparse').ArgumentParser;

const parser = new ArgumentParser({
    description: 'Dump portion of file',
});
parser.addArgument('input', { help: 'Input file name' });
parser.addArgument('output', { help: 'Output file name' });
parser.addArgument('off', { help: 'Start offset' });
parser.addArgument('len', { help: 'Length to dump' });

const dumpData = (args) => {
    const input = args.input;       // name of file to read data from
    const output = args.output;     // name of file to write data to
    const offset = +args.off;       // beginning of data to pull
    const len = +args.len;          // total number of bytes of data to pull

    let wasError = false;

    const readable = createReadStream(input, {
        start: offset,
        end: (offset + len) - 1,
    });
    const writable = createWriteStream(output);
    readable.pipe(writable);

    readable.on('error', (err) => {
        wasError = true;
        console.log('An error occurred in the read stream.');
        console.error(err);
        writable.destroy();
    });
    writable.on('error', (err) => {
        wasError = true;
        console.log('An error occurred in the write stream.');
        console.error(err);
        readable.destroy();
    });
    writable.on('finish', () => {
        if (!wasError) {
            console.log('Dumping completed successfully!');
        }
    });
};

module.exports = dumpData;

// execute if called directly from command line
if (require.main === module) {
    dumpData(parser.parseArgs());
}
