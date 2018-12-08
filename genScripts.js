#!/usr/bin/env node
/* eslint comma-dangle: ["error", "always-multiline"], no-console: "off" */
const fs = require('fs');
const { join } = require('path');
const pksmScript = require('./PKSMScript');

const games = ['usum', 'sm', 'oras', 'xy', 'b2w2', 'bw', 'hgss', 'pt', 'dp'];
let subdir; // track if scripts use -d flag

function generate(game) {
    let scriptSrc = fs.readFileSync(join('src', `scripts${game.toUpperCase()}.txt`), 'utf8');
    scriptSrc = scriptSrc.split(/\r?\n/);
    scriptSrc.forEach((l) => {
        if (l.length && l.charAt(0) !== '#') {
            subdir = l.indexOf(' -d') > -1 || subdir;
            let scriptArgs = l.replace(/\\/g, '/').match(/"[^"]+"|'[^']+'|\S+/g);
            scriptArgs = scriptArgs.map(v => v.replace(/\b'|'\b|"/g, ''));
            pksmScript(scriptArgs);
        }
    });
}

// abstracted try/catch around FS calls
function tryFSSync(op, args, errCodes) {
    try {
        return fs[`${op}Sync`](...args);
    } catch (e) {
        if (errCodes.retry && errCodes.retry.indexOf(e.code) > -1) {
            return fs[`${op}Sync`](...args);
        } else if (errCodes.skip && errCodes.skip.indexOf(e.code) === -1) {
            console.log(`There was an error trying to execute fs.${op}Sync(${args})`);
            console.error(e);
        }
    }
}

// recursive rmDir
function rmDir(dir) {
    try {
        fs.accessSync(dir);
        const dirStat = fs.statSync(dir);
        if (dirStat.isDirectory()) {
            fs.readdirSync(dir).forEach((file) => {
                const curPath = join(dir, file);
                if (fs.statSync(curPath).isDirectory()) {
                    rmDir(curPath);
                } else {
                    fs.unlinkSync(curPath);
                }
            });
            fs.rmdirSync(dir);
        } else {
            fs.unlinkSync(dir);
        }
    } catch (e) {
        if (e.code !== 'ENOENT') {
            console.log(`There was an error accessing or deleting ${dir}`);
            console.error(e);
        }
    }
}

function genScripts(/* args */) {
    console.log('Generating scripts...');
    const srcContents = fs.readdirSync('src');

    // empty existing /build and /scripts directories
    rmDir('scripts');
    rmDir('build');
    tryFSSync('mkdir', ['scripts'], { retry: ['EPERM'] });

    const cScripts = tryFSSync('readdir', [join('src', 'universal')], { skip: ['ENOENT'] });
    if (cScripts) {
        fs.mkdirSync(join('scripts', 'universal'));
        cScripts.forEach((f) => {
            if (f.slice(-2) === '.c') {
                fs.copyFileSync(join('src', 'universal', f), join('scripts', 'universal', f));
            }
        });
    }

    games.forEach((game) => {
        // remake game directory
        // console.log(`Compiling scripts for ${game}`);
        const gameDir = join('scripts', game);
        tryFSSync('mkdir', [gameDir], { retry: ['ENOENT', 'EPERM'] });

        subdir = false;
        generate(game); // compile scripts for game

        // move scripts
        if (subdir) { // scripts with -d flag
            fs.readdirSync('build').forEach((v) => {
                const files = fs.readdirSync(join('build', v));
                if (files.length > 0) {
                    fs.mkdirSync(join(gameDir, v));
                }
                files.forEach((f) => {
                    tryFSSync('rename', [join('build', v, f), join(gameDir, v, f)], { retry: ['EPERM'] });
                });
            });
        }
        if (srcContents.indexOf(game) > -1) {
            fs.readdirSync(join('src', game)).forEach((v) => {
                if (v.slice(-2) === '.c') { // game-specific picoC scripts
                    fs.copyFileSync(join('src', game, v), join(gameDir, v));
                }
            });
        }
        fs.readdirSync('.').forEach((v) => {
            if (v.slice(-5) === '.pksm') {
                fs.renameSync(v, join(gameDir, v));
            }
        });
    });

    console.log('Finished compiling scripts');
}

module.exports = genScripts;

// execute if called directly from command line
if (require.main === module) {
    genScripts(/* process.argv */);
}
