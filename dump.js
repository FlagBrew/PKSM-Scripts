#!/usr/bin/env node
const { createReadStream, createWriteStream } = require('fs');

/** argparse code (Python 3)

parser = argparse.ArgumentParser(description = 'Dump portion of file')
parser.add_argument('input', help = 'Input file name')
parser.add_argument('output', help = 'Output file name')
parser.add_argument('offset', help = 'Start offset')
parser.add_argument('length', help = 'Length to dump')
*/

const dumpData = (args) => {
    if (args.length < 4) {
        console.log('Insufficient arguments were passed.');
        return;
    }

    const input = args[0];          // name of file to read data from
    const output = args[1];         // name of file to write data to
    const offset = +args[2];        // beginning of data to pull
    const len = +args[3];           // total number of bytes of data to pull

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
    dumpData(process.argv.slice(2));
}
