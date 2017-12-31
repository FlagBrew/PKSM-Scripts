# PKSMScript

## .pksm file format

```
# PKSM script structure
# u8 magic[10]        // PKSMSCRIPT
# u32 offset          // save offset to write the data to
# u32 length          // payload length
# u8 payload[len]     // payload data
# u32 repeat_times    // repeat payload n times
# ...
```

## Usage

```
PKSMScript.py [-h] output [-i ofs len pld rpt]

-h:       help
<output>: output file name
-i:       adds an input argument
          ofs: offset
		  len: length
		  pld: value number or data payload
		  rpt: repeat n times
```

## Examples

Examples can be found [here](https://github.com/BernardoGiordano/PKSM-Tools/blob/master/PKSMScript/scripts.bat).

