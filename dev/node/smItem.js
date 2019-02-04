let radix = 0;
if (process.argv[3].charAt(0) == '0') {
    radix = 16;
}

const itemID = `000000000${parseInt(process.argv[2]).toString(2)}`;
const itemQuantity = `000000000${parseInt(process.argv[3], radix).toString(2)}`;

let output = parseInt(`000000000000${itemQuantity.slice(-10)}${itemID.slice(-10)}`,2).toString(16);
console.log(output);
