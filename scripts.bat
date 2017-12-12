@rem USUM SCRIPTS
@py -3 PKSMScript.py "Save language to JPN" -i 0x1435 1 0x1 1
@py -3 PKSMScript.py "Save language to ENG" -i 0x1435 1 0x2 1
@py -3 PKSMScript.py "Save language to FRE" -i 0x1435 1 0x3 1
@py -3 PKSMScript.py "Save language to ITA" -i 0x1435 1 0x4 1
@py -3 PKSMScript.py "Save language to GER" -i 0x1435 1 0x5 1
@py -3 PKSMScript.py "Save language to SPA" -i 0x1435 1 0x7 1
@py -3 PKSMScript.py "Save language to KOR" -i 0x1435 1 0x8 1
@py -3 PKSMScript.py "Save language to CHS" -i 0x1435 1 0x9 1
@py -3 PKSMScript.py "Save language to CHT" -i 0x1435 1 0xA 1
@py -3 PKSMScript.py "Clear Mystery Gift data" -i 0x66200 1 0x0 12928
@py -3 PKSMScript.py "Set max money" -i 0x4400 4 9999999 1
@py -3 PKSMScript.py "Inject living dex" -i 0x5200 186992 "data/living7.bin" 1
@py -3 PKSMScript.py "Set max Battle Points" -i 0x0451C 4 9999 1
@py -3 PKSMScript.py "Set max Festival Coins" -i 0x51308 4 9999999 1
@py -3 PKSMScript.py "Set 100 hatched eggs" -i 0x6A220 4 100 1
@py -3 PKSMScript.py "Set max Camera Shots" -i 0x65604 4 9999999 1
@py -3 PKSMScript.py "Set max Thumbs Up" -i 0x6560C 4 9999999 1
@py -3 PKSMScript.py "Set max Camera Version" -i 0x65600 2 4 1

@py -3 PKSMScript.py "Set Vivillon Icy Snow form" -i 0x4530 1 0 1
@py -3 PKSMScript.py "Set Vivillon Polar form" -i 0x4530 1 1 1
@py -3 PKSMScript.py "Set Vivillon Tundra form" -i 0x4530 1 2 1
@py -3 PKSMScript.py "Set Vivillon Continental form" -i 0x4530 1 3 1
@py -3 PKSMScript.py "Set Vivillon Garden form" -i 0x4530 1 4 1
@py -3 PKSMScript.py "Set Vivillon Elegant form" -i 0x4530 1 5 1
@py -3 PKSMScript.py "Set Vivillon Meadow form" -i 0x4530 1 6 1
@py -3 PKSMScript.py "Set Vivillon Modern form" -i 0x4530 1 7 1
@py -3 PKSMScript.py "Set Vivillon Marine form" -i 0x4530 1 8 1
@py -3 PKSMScript.py "Set Vivillon Archipelago form" -i 0x4530 1 9 1
@py -3 PKSMScript.py "Set Vivillon High-Plains form" -i 0x4530 1 10 1
@py -3 PKSMScript.py "Set Vivillon Sandstorm form" -i 0x4530 1 11 1
@py -3 PKSMScript.py "Set Vivillon River form" -i 0x4530 1 12 1
@py -3 PKSMScript.py "Set Vivillon Monsoon form" -i 0x4530 1 13 1
@py -3 PKSMScript.py "Set Vivillon Savannah form" -i 0x4530 1 14 1
@py -3 PKSMScript.py "Set Vivillon Sun form" -i 0x4530 1 15 1
@py -3 PKSMScript.py "Set Vivillon Ocean form" -i 0x4530 1 16 1
@py -3 PKSMScript.py "Set Vivillon Jungle form" -i 0x4530 1 17 1
@py -3 PKSMScript.py "Set Vivillon Fancy form" -i 0x4530 1 18 1
@py -3 PKSMScript.py "Set Vivillon Pokeball form" -i 0x4530 1 19 1

@mkdir usum
@cp *.pksm usum
@del *.pksm

@rem SM SCRIPTS
@py -3 PKSMScript.py "Save language to JPN" -i 0x1235 1 0x1 1
@py -3 PKSMScript.py "Save language to ENG" -i 0x1235 1 0x2 1
@py -3 PKSMScript.py "Save language to FRE" -i 0x1235 1 0x3 1
@py -3 PKSMScript.py "Save language to ITA" -i 0x1235 1 0x4 1
@py -3 PKSMScript.py "Save language to GER" -i 0x1235 1 0x5 1
@py -3 PKSMScript.py "Save language to SPA" -i 0x1235 1 0x7 1
@py -3 PKSMScript.py "Save language to KOR" -i 0x1235 1 0x8 1
@py -3 PKSMScript.py "Save language to CHS" -i 0x1235 1 0x9 1
@py -3 PKSMScript.py "Save language to CHT" -i 0x1235 1 0xA 1
@py -3 PKSMScript.py "Clear Mystery Gift data" -i 0x65C00 1 0x0 12928
@py -3 PKSMScript.py "Set max money" -i 0x4000 4 9999999 1
@py -3 PKSMScript.py "Inject living dex" -i 0x4E00 186992 "data/living7.bin" 1
@py -3 PKSMScript.py "Set max Battle Points" -i 0x0411C 4 9999 1
@py -3 PKSMScript.py "Set max Festival Coins" -i 0x50D08 4 9999999 1
@py -3 PKSMScript.py "Set max Camera Shots" -i 0x65004 4 9999999 1
@py -3 PKSMScript.py "Set max Thumbs Up" -i 0x6500C 4 9999999 1
@py -3 PKSMScript.py "Set max Camera Version" -i 0x65000 2 4 1

@py -3 PKSMScript.py "Set Vivillon Icy Snow form form" -i 0x4130 1 0 1
@py -3 PKSMScript.py "Set Vivillon Polar form" -i 0x4130 1 1 1
@py -3 PKSMScript.py "Set Vivillon Tundra form" -i 0x4130 1 2 1
@py -3 PKSMScript.py "Set Vivillon Continental form" -i 0x4130 1 3 1
@py -3 PKSMScript.py "Set Vivillon Garden form" -i 0x4130 1 4 1
@py -3 PKSMScript.py "Set Vivillon Elegant form" -i 0x4130 1 5 1
@py -3 PKSMScript.py "Set Vivillon Meadow form" -i 0x4130 1 6 1
@py -3 PKSMScript.py "Set Vivillon Modern form" -i 0x4130 1 7 1
@py -3 PKSMScript.py "Set Vivillon Marine form" -i 0x4130 1 8 1
@py -3 PKSMScript.py "Set Vivillon Archipelago form" -i 0x4130 1 9 1
@py -3 PKSMScript.py "Set Vivillon High-Plains form" -i 0x4130 1 10 1
@py -3 PKSMScript.py "Set Vivillon Sandstorm form" -i 0x4130 1 11 1
@py -3 PKSMScript.py "Set Vivillon River form" -i 0x4130 1 12 1
@py -3 PKSMScript.py "Set Vivillon Monsoon form" -i 0x4130 1 13 1
@py -3 PKSMScript.py "Set Vivillon Savannah form" -i 0x4130 1 14 1
@py -3 PKSMScript.py "Set Vivillon Sun form" -i 0x4130 1 15 1
@py -3 PKSMScript.py "Set Vivillon Ocean form" -i 0x4130 1 16 1
@py -3 PKSMScript.py "Set Vivillon Jungle form" -i 0x4130 1 17 1
@py -3 PKSMScript.py "Set Vivillon Fancy form" -i 0x4130 1 18 1
@py -3 PKSMScript.py "Set Vivillon Pokeball form" -i 0x4130 1 19 1

@mkdir sm
@cp *.pksm sm
@del *.pksm

@rem ORAS SCRIPTS
@py -3 PKSMScript.py "Save language to JPN" -i 0x1402D 1 0x1 1
@py -3 PKSMScript.py "Save language to ENG" -i 0x1402D 1 0x2 1
@py -3 PKSMScript.py "Save language to FRE" -i 0x1402D 1 0x3 1
@py -3 PKSMScript.py "Save language to ITA" -i 0x1402D 1 0x4 1
@py -3 PKSMScript.py "Save language to GER" -i 0x1402D 1 0x5 1
@py -3 PKSMScript.py "Save language to SPA" -i 0x1402D 1 0x7 1
@py -3 PKSMScript.py "Save language to KOR" -i 0x1402D 1 0x8 1
@py -3 PKSMScript.py "Clear Mystery Gift data" -i 0x1CC00 1 0x0 5692
@py -3 PKSMScript.py "Set max money" -i 0x4208 4 9999999 1
@py -3 PKSMScript.py "Inject living dex" -i 0x33000 186064 "data/living6.bin" 1
@py -3 PKSMScript.py "Set max Battle Points" -i 0x4230 2 9999 1
@py -3 PKSMScript.py "Set max Current Pokemiles" -i 0x1F4FC 4 9999999 1

@mkdir oras
@cp *.pksm oras
@del *.pksm

@rem XY SCRIPTS
@py -3 PKSMScript.py "Save language to JPN" -i 0x1402D 1 0x1 1
@py -3 PKSMScript.py "Save language to ENG" -i 0x1402D 1 0x2 1
@py -3 PKSMScript.py "Save language to FRE" -i 0x1402D 1 0x3 1
@py -3 PKSMScript.py "Save language to ITA" -i 0x1402D 1 0x4 1
@py -3 PKSMScript.py "Save language to GER" -i 0x1402D 1 0x5 1
@py -3 PKSMScript.py "Save language to SPA" -i 0x1402D 1 0x7 1
@py -3 PKSMScript.py "Save language to KOR" -i 0x1402D 1 0x8 1
@py -3 PKSMScript.py "Clear Mystery Gift data" -i 0x1BC00 1 0x0 5692
@py -3 PKSMScript.py "Set max money" -i 0x4208 4 9999999 1
@py -3 PKSMScript.py "Inject living dex" -i 0x22600 186064 "data/living6.bin" 1
@py -3 PKSMScript.py "Set max Style Points" -i 0x154D 1 255 1
@py -3 PKSMScript.py "Set max Battle Points" -i 0x423C 2 9999 1
@py -3 PKSMScript.py "Set max Current Pokemiles" -i 0x1E4FC 4 9999999 1

@mkdir xy
@cp *.pksm xy
@del *.pksm

@rem B2W2 SCRIPTS
@py -3 PKSMScript.py "Clear Mystery Gift data" -i 0x1C800 1 0x0 2704
@py -3 PKSMScript.py "Set max money" -i 0x21100 4 9999999 1
@py -3 PKSMScript.py "Inject living dex" -i 0x00400 4080 "data/living5/boxdata BOX 1.bin" 1 -i 0x01400 4080 "data/living5/boxdata BOX 2.bin" 1 -i 0x02400 4080 "data/living5/boxdata BOX 3.bin" 1 -i 0x03400 4080 "data/living5/boxdata BOX 4.bin" 1 -i 0x04400 4080 "data/living5/boxdata BOX 5.bin" 1 -i 0x05400 4080 "data/living5/boxdata BOX 6.bin" 1 -i 0x06400 4080 "data/living5/boxdata BOX 7.bin" 1 -i 0x07400 4080 "data/living5/boxdata BOX 8.bin" 1 -i 0x08400 4080 "data/living5/boxdata BOX 9.bin" 1 -i 0x09400 4080 "data/living5/boxdata BOX 10.bin" 1 -i 0x0A400 4080 "data/living5/boxdata BOX 11.bin" 1 -i 0x0B400 4080 "data/living5/boxdata BOX 12.bin" 1 -i 0x0C400 4080 "data/living5/boxdata BOX 13.bin" 1 -i 0x0D400 4080 "data/living5/boxdata BOX 14.bin" 1 -i 0x0E400 4080 "data/living5/boxdata BOX 15.bin" 1 -i 0x0F400 4080 "data/living5/boxdata BOX 16.bin" 1 -i 0x10400 4080 "data/living5/boxdata BOX 17.bin" 1 -i 0x11400 4080 "data/living5/boxdata BOX 18.bin" 1 -i 0x12400 4080 "data/living5/boxdata BOX 19.bin" 1 -i 0x13400 4080 "data/living5/boxdata BOX 20.bin" 1 -i 0x14400 4080 "data/living5/boxdata BOX 21.bin" 1 -i 0x15400 4080 "data/living5/boxdata BOX 22.bin" 1 -i 0x16400 4080 "data/living5/boxdata BOX 23.bin" 1 -i 0x17400 4080 "data/living5/boxdata BOX 24.bin" 1 

@mkdir b2w2
@cp *.pksm b2w2
@del *.pksm

@rem BW SCRIPTS
@py -3 PKSMScript.py "Clear Mystery Gift data" -i 0x1C800 1 0x0 2704
@py -3 PKSMScript.py "Set max money" -i 0x21200 4 9999999 1
@py -3 PKSMScript.py "Inject living dex" -i 0x00400 4080 "data/living5/boxdata BOX 1.bin" 1 -i 0x01400 4080 "data/living5/boxdata BOX 2.bin" 1 -i 0x02400 4080 "data/living5/boxdata BOX 3.bin" 1 -i 0x03400 4080 "data/living5/boxdata BOX 4.bin" 1 -i 0x04400 4080 "data/living5/boxdata BOX 5.bin" 1 -i 0x05400 4080 "data/living5/boxdata BOX 6.bin" 1 -i 0x06400 4080 "data/living5/boxdata BOX 7.bin" 1 -i 0x07400 4080 "data/living5/boxdata BOX 8.bin" 1 -i 0x08400 4080 "data/living5/boxdata BOX 9.bin" 1 -i 0x09400 4080 "data/living5/boxdata BOX 10.bin" 1 -i 0x0A400 4080 "data/living5/boxdata BOX 11.bin" 1 -i 0x0B400 4080 "data/living5/boxdata BOX 12.bin" 1 -i 0x0C400 4080 "data/living5/boxdata BOX 13.bin" 1 -i 0x0D400 4080 "data/living5/boxdata BOX 14.bin" 1 -i 0x0E400 4080 "data/living5/boxdata BOX 15.bin" 1 -i 0x0F400 4080 "data/living5/boxdata BOX 16.bin" 1 -i 0x10400 4080 "data/living5/boxdata BOX 17.bin" 1 -i 0x11400 4080 "data/living5/boxdata BOX 18.bin" 1 -i 0x12400 4080 "data/living5/boxdata BOX 19.bin" 1 -i 0x13400 4080 "data/living5/boxdata BOX 20.bin" 1 -i 0x14400 4080 "data/living5/boxdata BOX 21.bin" 1 -i 0x15400 4080 "data/living5/boxdata BOX 22.bin" 1 -i 0x16400 4080 "data/living5/boxdata BOX 23.bin" 1 -i 0x17400 4080 "data/living5/boxdata BOX 24.bin" 1 

@mkdir bw
@cp *.pksm bw
@del *.pksm

@rem HGSS SCRIPTS
@rem @py -3 PKSMScript.py "Clear Mystery Gift data (experimental)" -i 0x9D3C 1 0x0 2336 -i 0x49D3C 1 0x0 2336

@mkdir hgss
@cp *.pksm hgss
@del *.pksm

@rem PT SCRIPTS
@rem @py -3 PKSMScript.py "Clear Mystery Gift data (experimental)" -i 0xB4C0 1 0x0 2336 -i 0x4B4C0 1 0x0 2336

@mkdir pt
@cp *.pksm pt
@del *.pksm

@rem DP SCRIPTS
@rem @py -3 PKSMScript.py "Clear Mystery Gift data (experimental)" -i 0xA7D0 1 0x0 2124 -i 0x4A7D0 1 0x0 2124

@mkdir dp
@cp *.pksm dp
@del *.pksm
