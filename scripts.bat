@rem USUM SCRIPTS
@python PKSMScript.py "Save language to JPN" -i 0x1435 1 0x1 1
@python PKSMScript.py "Save language to ENG" -i 0x1435 1 0x2 1
@python PKSMScript.py "Save language to FRE" -i 0x1435 1 0x3 1
@python PKSMScript.py "Save language to ITA" -i 0x1435 1 0x4 1
@python PKSMScript.py "Save language to GER" -i 0x1435 1 0x5 1
@python PKSMScript.py "Save language to SPA" -i 0x1435 1 0x7 1
@python PKSMScript.py "Save language to KOR" -i 0x1435 1 0x8 1
@python PKSMScript.py "Save language to CHS" -i 0x1435 1 0x9 1
@python PKSMScript.py "Save language to CHT" -i 0x1435 1 0xA 1
@python PKSMScript.py "Clear Mystery Gift data" -i 0x66200 1 0x0 12928
@python PKSMScript.py "Set 9999999 money" -i 0x4400 4 9999999 1
@python PKSMScript.py "Inject living dex" -i 0x5200 186992 "data/living7.bin" 1

@mkdir usum
@cp *.pksm usum
@del *.pksm

@rem SM SCRIPTS
@python PKSMScript.py "Save language to JPN" -i 0x1235 1 0x1 1
@python PKSMScript.py "Save language to ENG" -i 0x1235 1 0x2 1
@python PKSMScript.py "Save language to FRE" -i 0x1235 1 0x3 1
@python PKSMScript.py "Save language to ITA" -i 0x1235 1 0x4 1
@python PKSMScript.py "Save language to GER" -i 0x1235 1 0x5 1
@python PKSMScript.py "Save language to SPA" -i 0x1235 1 0x7 1
@python PKSMScript.py "Save language to KOR" -i 0x1235 1 0x8 1
@python PKSMScript.py "Save language to CHS" -i 0x1235 1 0x9 1
@python PKSMScript.py "Save language to CHT" -i 0x1235 1 0xA 1
@python PKSMScript.py "Clear Mystery Gift data" -i 0x65C00 1 0x0 12928
@python PKSMScript.py "Set 9999999 money" -i 0x4000 4 9999999 1
@python PKSMScript.py "Inject living dex" -i 0x4E00 186992 "data/living7.bin" 1

@mkdir sm
@cp *.pksm sm
@del *.pksm

@rem ORAS SCRIPTS
@python PKSMScript.py "Save language to JPN" -i 0x1402D 1 0x1 1
@python PKSMScript.py "Save language to ENG" -i 0x1402D 1 0x2 1
@python PKSMScript.py "Save language to FRE" -i 0x1402D 1 0x3 1
@python PKSMScript.py "Save language to ITA" -i 0x1402D 1 0x4 1
@python PKSMScript.py "Save language to GER" -i 0x1402D 1 0x5 1
@python PKSMScript.py "Save language to SPA" -i 0x1402D 1 0x7 1
@python PKSMScript.py "Save language to KOR" -i 0x1402D 1 0x8 1
@python PKSMScript.py "Clear Mystery Gift data" -i 0x1CC00 1 0x0 5692
@python PKSMScript.py "Set 9999999 money" -i 0x4208 4 9999999 1
@python PKSMScript.py "Inject living dex" -i 0x33000 186064 "data/living6.bin" 1

@mkdir oras
@cp *.pksm oras
@del *.pksm

@rem XY SCRIPTS
@python PKSMScript.py "Save language to JPN" -i 0x1402D 1 0x1 1
@python PKSMScript.py "Save language to ENG" -i 0x1402D 1 0x2 1
@python PKSMScript.py "Save language to FRE" -i 0x1402D 1 0x3 1
@python PKSMScript.py "Save language to ITA" -i 0x1402D 1 0x4 1
@python PKSMScript.py "Save language to GER" -i 0x1402D 1 0x5 1
@python PKSMScript.py "Save language to SPA" -i 0x1402D 1 0x7 1
@python PKSMScript.py "Save language to KOR" -i 0x1402D 1 0x8 1
@python PKSMScript.py "Clear Mystery Gift data" -i 0x1BC00 1 0x0 5692
@python PKSMScript.py "Set 9999999 money" -i 0x4208 4 9999999 1
@python PKSMScript.py "Inject living dex" -i 0x22600 186064 "data/living6.bin" 1

@mkdir xy
@cp *.pksm xy
@del *.pksm

@rem B2W2 SCRIPTS
@python PKSMScript.py "Clear Mystery Gift data" -i 0x1C800 1 0x0 2704
@python PKSMScript.py "Set 9999999 money" -i 0x21100 4 9999999 1
@python PKSMScript.py "Inject living dex" -i 0x00400 4080 "data/living5/boxdata BOX 1.bin" 1 -i 0x01400 4080 "data/living5/boxdata BOX 2.bin" 1 -i 0x02400 4080 "data/living5/boxdata BOX 3.bin" 1 -i 0x03400 4080 "data/living5/boxdata BOX 4.bin" 1 -i 0x04400 4080 "data/living5/boxdata BOX 5.bin" 1 -i 0x05400 4080 "data/living5/boxdata BOX 6.bin" 1 -i 0x06400 4080 "data/living5/boxdata BOX 7.bin" 1 -i 0x07400 4080 "data/living5/boxdata BOX 8.bin" 1 -i 0x08400 4080 "data/living5/boxdata BOX 9.bin" 1 -i 0x09400 4080 "data/living5/boxdata BOX 10.bin" 1 -i 0x0A400 4080 "data/living5/boxdata BOX 11.bin" 1 -i 0x0B400 4080 "data/living5/boxdata BOX 12.bin" 1 -i 0x0C400 4080 "data/living5/boxdata BOX 13.bin" 1 -i 0x0D400 4080 "data/living5/boxdata BOX 14.bin" 1 -i 0x0E400 4080 "data/living5/boxdata BOX 15.bin" 1 -i 0x0F400 4080 "data/living5/boxdata BOX 16.bin" 1 -i 0x10400 4080 "data/living5/boxdata BOX 17.bin" 1 -i 0x11400 4080 "data/living5/boxdata BOX 18.bin" 1 -i 0x12400 4080 "data/living5/boxdata BOX 19.bin" 1 -i 0x13400 4080 "data/living5/boxdata BOX 20.bin" 1 -i 0x14400 4080 "data/living5/boxdata BOX 21.bin" 1 -i 0x15400 4080 "data/living5/boxdata BOX 22.bin" 1 -i 0x16400 4080 "data/living5/boxdata BOX 23.bin" 1 -i 0x17400 4080 "data/living5/boxdata BOX 24.bin" 1 

@mkdir b2w2
@cp *.pksm b2w2
@del *.pksm

@rem BW SCRIPTS
@python PKSMScript.py "Clear Mystery Gift data" -i 0x1C800 1 0x0 2704
@python PKSMScript.py "Set 9999999 money" -i 0x21200 4 9999999 1
@python PKSMScript.py "Inject living dex" -i 0x00400 4080 "data/living5/boxdata BOX 1.bin" 1 -i 0x01400 4080 "data/living5/boxdata BOX 2.bin" 1 -i 0x02400 4080 "data/living5/boxdata BOX 3.bin" 1 -i 0x03400 4080 "data/living5/boxdata BOX 4.bin" 1 -i 0x04400 4080 "data/living5/boxdata BOX 5.bin" 1 -i 0x05400 4080 "data/living5/boxdata BOX 6.bin" 1 -i 0x06400 4080 "data/living5/boxdata BOX 7.bin" 1 -i 0x07400 4080 "data/living5/boxdata BOX 8.bin" 1 -i 0x08400 4080 "data/living5/boxdata BOX 9.bin" 1 -i 0x09400 4080 "data/living5/boxdata BOX 10.bin" 1 -i 0x0A400 4080 "data/living5/boxdata BOX 11.bin" 1 -i 0x0B400 4080 "data/living5/boxdata BOX 12.bin" 1 -i 0x0C400 4080 "data/living5/boxdata BOX 13.bin" 1 -i 0x0D400 4080 "data/living5/boxdata BOX 14.bin" 1 -i 0x0E400 4080 "data/living5/boxdata BOX 15.bin" 1 -i 0x0F400 4080 "data/living5/boxdata BOX 16.bin" 1 -i 0x10400 4080 "data/living5/boxdata BOX 17.bin" 1 -i 0x11400 4080 "data/living5/boxdata BOX 18.bin" 1 -i 0x12400 4080 "data/living5/boxdata BOX 19.bin" 1 -i 0x13400 4080 "data/living5/boxdata BOX 20.bin" 1 -i 0x14400 4080 "data/living5/boxdata BOX 21.bin" 1 -i 0x15400 4080 "data/living5/boxdata BOX 22.bin" 1 -i 0x16400 4080 "data/living5/boxdata BOX 23.bin" 1 -i 0x17400 4080 "data/living5/boxdata BOX 24.bin" 1 

@mkdir bw
@cp *.pksm bw
@del *.pksm

@rem HGSS SCRIPTS
@rem @python PKSMScript.py "Clear Mystery Gift data (experimental)" -i 0x9D3C 1 0x0 2336 -i 0x49D3C 1 0x0 2336

@mkdir hgss
@cp *.pksm hgss
@del *.pksm

@rem PT SCRIPTS
@rem @python PKSMScript.py "Clear Mystery Gift data (experimental)" -i 0xB4C0 1 0x0 2336 -i 0x4B4C0 1 0x0 2336

@mkdir pt
@cp *.pksm pt
@del *.pksm

@rem DP SCRIPTS
@rem @python PKSMScript.py "Clear Mystery Gift data (experimental)" -i 0xA7D0 1 0x0 2124 -i 0x4A7D0 1 0x0 2124

@mkdir dp
@cp *.pksm dp
@del *.pksm
