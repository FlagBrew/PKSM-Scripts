#!/usr/bin/env node
/* eslint no-continue: "off" */
const fs = require('fs');
const { join, sep } = require('path');

const cli = require.main === module;

const mkdirs = (dir) => {
    try {
        fs.mkdirSync(dir);
    } catch (e) {
        if (e.code === 'ENOENT') {
            mkdirs(dir.slice(0, dir.lastIndexOf(sep)));
            fs.mkdirSync(dir);
        }
    }
};

const pksmScript = (args) => {
    let scriptName = args.shift();

    // handle '-d' if present
    let d = [-1, 2, ''];
    args.forEach((v, i, a) => {
        if (v.slice(0, 2) === '-d' && (v.length === 2 || v.chatAt(2) === '=')) {
            d[0] = i;
            if (v.length > 2) {
                d[1] = 1;
                d[2] = v.split('=')[1];
            } else {
                d[2] = a[i + 1];
            }
        }
    });
    if (d[0] > -1) {
        args.splice(d[0], d[1]);                            // remove dir from args
        mkdirs(join('build', d[2]));                        // make sure that dir exists
        scriptName = join('build', d[2], scriptName);       // combine with scriptName to form path
    }

    // FIXME: openSync is failing on "Mass Inject - living dex.pksm" from genScripts.js
    const output = fs.openSync(`${scriptName}.pksm`, 'w');
    let buf = Buffer.from('PKSMSCRIPT');

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
                pldBuf = fs.readFileSync(pldArg);
            } catch (e) {
                console.log(`There was an error trying to read file ${pldArg}`);
                console.error(e);
                continue;
            }
        }

        buf = Buffer.concat([buf, ofsBuf, lenBuf, pldBuf, rptBuf]);

        fs.writeSync(output, buf, 0, buf.length, 0);
    }
    fs.closeSync(output);

    if (cli) {
        console.log(`${scriptName}.pksm compiled`);
    }
    if (args.length) {
        console.log(`Some arguments went unused${!cli ? ` while compiling ${scriptName}.pksm` : ''}`);
    }
    if (!cli) {
        return true;
    }
};

module.exports = pksmScript;

// execute if called directly from command line
if (cli) {
    const scriptArgs = process.argv.slice(2);
    const help = scriptArgs.indexOf('-h') + scriptArgs.indexOf('--help');

    if (help > -2) {
        // print help info
        console.log(
            'usage: PKSMScript.js [-h] output [-d subdir] [-i ofs len pld rpt]\n\n',
            'Creates .pksm files\n\n',
            '-h, --help      show this help message and exit\n',
            'output          output file name\n',
            '-d              add a directory argument\n',
            'subdir          Subdirectory in which to create the script\n',
            '-i              adds an input argument\n',
            'ofs             offset to write the payload to\n',
            'len             payload length\n',
            'pld             payload (can be an integer or a file path)\n',
            'rpt             repeat n times'
        );
    } else {
        pksmScript(scriptArgs);
    }
}
