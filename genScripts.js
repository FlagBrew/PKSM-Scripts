#!/usr/bin/env node
const fs = require('fs');
const { createInterface } = require('readline');
const { join } = require('path');
const pksmScript = require('./PKSMScript');

let err = false;

const games = ['usum', 'sm', 'oras', 'xy', 'b2w2', 'bw', 'hgss', 'pt', 'dp'];

const generate = (game) => {
    const rl = createInterface({
        input: fs.createReadStream(join('src', `scripts${game.toUpperCase()}.txt`)),
        crlfDelay: Infinity,
    });
    rl.on('line', (l) => {
        if (l.length && l.charAt(0) !== '#') {
            const line = l.replace(/\\/g, '/');

            let argGroups = line.split(' -i ');
            let scriptArgs = [];
            const scriptName = join('scripts', game, argGroups.shift().slice(1, -1));
            scriptArgs.push(scriptName);

            argGroups = argGroups.map((v) => {
                const argGroup = ['-i'];
                const spaces = [v.indexOf(' '), v.lastIndexOf(' ')];
                spaces.splice(1, 0, v.indexOf(' ', spaces[0] + 1));
                argGroup.push(v.substring(0, spaces[0]));                                   // offset
                argGroup.push(v.substring(spaces[0] + 1, spaces[1]));                       // length
                argGroup.push(v.substring(spaces[1] + 1, spaces[2]).replace(/"/g, ''));     // payload
                argGroup.push(v.substr(spaces[2] + 1));                                     // repeat
                return argGroup;
            });
            scriptArgs = Array.prototype.concat.apply(scriptArgs, argGroups);

            pksmScript(scriptArgs);
        }
    });
};

// recursive rmDir
const rmDir = (dir) => {
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
            err = true;
            console.error(e);
        }
    }
};

// FIXME: is this still not successful 100% of the time?
const genScripts = (/* args */) => {
    // TODO: allow user to provide a subset of games to compile scripts for
    // TODO: error check provided list against internal one
    // args.splice(0, 2);
    // const gamesList = (args.length ? args : games);

    const gamesList = games;

    // ensure /scripts exists
    try {
        fs.mkdirSync('scripts');
    } catch (e) {
        // intentionally empty
    }

    // empty and delete game's scripts directory
    gamesList.forEach((game) => {
        rmDir(join('scripts', game));
    });

    gamesList.forEach((game) => {
        // remake game directory
        const gameDir = join('scripts', game);
        try {
            fs.mkdirSync(gameDir);
        } catch (e) {
            if (e.code === 'ENOENT' || e.code === 'EPERM') {
                fs.mkdirSync(gameDir);
            } else {
                console.log(`There was an error creating /scripts/${game}`);
                console.error(e);
            }
        }

        // compile scripts for game
        generate(game);
    });

    console.log(`All scripts have been compiled${err ? '.' : ' without error! Congrats!'}`);
};

module.exports = genScripts;

// execute if called directly from command line
if (require.main === module) {
    genScripts(/* process.argv */);
}
