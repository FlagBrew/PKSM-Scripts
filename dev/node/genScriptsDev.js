#!/usr/bin/env node
const fse = require('fs-extra');
const { join } = require('path');
const pksmScript = require('./PKSMScript');

const games = ['usum', 'sm', 'oras', 'xy', 'b2w2', 'bw', 'hgss', 'pt', 'dp'];

function generate(game) {
    let scriptSrc = fse.readFileSync(join('src', `scripts${game.toUpperCase()}.txt`), 'utf8');
    scriptSrc = scriptSrc.split(/\r?\n/);
    scriptSrc.forEach((l) => {
        if (l.length && l.charAt(0) !== '#') {
            let scriptArgs = l.replace(/\\/g, '/');
            scriptArgs = pksmScript.parser.parseArgs(scriptArgs.match(/"[^"]+"|'[^']+'|\S+/g));
            pksmScript(scriptArgs);
        }
    });
}

/**
 * @param {String[]} gameArgs
 */
function genScripts(gameArgs) {
    console.log('Generating scripts...');
    let compileGames;
    if (gameArgs.length > 0) {
        compileGames = gameArgs.map(v => v.toLowerCase()).filter(v => games.includes(v));
    } else {
        compileGames = games.slice();
    }

    // empty existing /build directory
    fse.remove('build');

    compileGames.forEach((game) => {
        if (fse.pathExistsSync(join('src', `scripts${game.toUpperCase()}.txt`))) {
            console.log(`Compiling scripts for ${game}`);
            const gameDir = join('scripts', game);
            fse.ensureDirSync(gameDir);

            generate(game); // compile scripts for game

            // move scripts
            if (fse.pathExistsSync('build')) { // scripts with -d flag
                fse.readdirSync('build').forEach((v) => {
                    fse.moveSync(join('build', v), join(gameDir, v));
                });
            }
            fse.readdirSync('.').forEach((v) => {
                if (v.slice(-5) === '.pksm') {
                    fse.moveSync(v, join(gameDir, v), { overwrite: true });
                }
            });
        }
    });

    console.log('Finished compiling scripts');
}

module.exports = genScripts;

// execute if called directly from command line
if (require.main === module) {
    genScripts(process.argv.slice(2));
}
