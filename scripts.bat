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
@py -3 PKSMScript.py "Set max money" -i 0x4404 4 9999999 1
@py -3 PKSMScript.py "Inject living dex" -i 0x5200 186992 "data/living7.bin" 1
@py -3 PKSMScript.py "Set max Battle Points" -i 0x0451C 4 9999 1
@py -3 PKSMScript.py "Set max Festival Coins" -i 0x51308 4 9999999 1
@py -3 PKSMScript.py "Set Island Points to 100" -i 0x6BE03 4 100 1
@py -3 PKSMScript.py "Set 100 hatched eggs" -i 0x6A220 4 100 1
@py -3 PKSMScript.py "Set max Camera Shots" -i 0x65604 4 9999999 1
@py -3 PKSMScript.py "Set max Thumbs Up" -i 0x6560C 4 9999999 1
@py -3 PKSMScript.py "Set max Camera Version" -i 0x65600 2 4 1
@py -3 PKSMScript.py "Set Moon time" -i 0x4a48 8 43200 1
@py -3 PKSMScript.py "Set Sun time" -i 0x4a48 8 86400 1

@py -3 PKSMScript.py "All Rotom Powers 99x" -i 0xDFC 44 "data\USUM_AllRotomPowers.bin" 1
@py -3 PKSMScript.py "All Berries 99x" -i 0xC64 268 "data\USUM_AllBerries.bin" 1
@py -3 PKSMScript.py "All Items 99x" -i 0x0 1340 "data\USUM_AllItems.bin" 1
@py -3 PKSMScript.py "All Medicines 99x" -i 0xB74 216 "data\USUM_AllMedicine.bin" 1
@py -3 PKSMScript.py "All TMs Owned" -i 0x9C4 400 "data\USUM_AllTM.bin" 1
@py -3 PKSMScript.py "All Z-Crystals Owned" -i 0xD70 140 "data\USUM_AllZCrystals.bin" 1

@py -3 PKSMScript.py "Reset Cosmog" -i 0x2688 1 167 1
@py -3 PKSMScript.py "Reset Aerodactyl" -i 0x260f 1 32 1
@py -3 PKSMScript.py "Reset Porygon" -i 0x260d 1 16 1
@py -3 PKSMScript.py "Reset Partner Cap Pikachu" -i 0x280A 1 84 1
@py -3 PKSMScript.py "Reset Surfing Pikachu" -i 0x2610 1 0 1
@py -3 PKSMScript.py "Reset Poipole" -i 0x25f1 1 95 1
@py -3 PKSMScript.py "Reset Solgaleo and Lunala" -i 0x269b 1 0xd7 1
@py -3 PKSMScript.py "Reset Necrozma" -i 0x2692 1 0x72 1
@py -3 PKSMScript.py "Reset Tapu Bulu" -i 0x2164 1 0x01 1
@py -3 PKSMScript.py "Reset Tapu Fini" -i 0x2128 1 0x03 1
@py -3 PKSMScript.py "Reset Stakataka (Ultramoon)" -i 0x27f2 1 0x04 1
@py -3 PKSMScript.py "Reset Tapu Lele" -i 0x2162 1 0x01 1
@py -3 PKSMScript.py "Reset Zygarde" -i 0x23e6 1 0x01 1
@py -3 PKSMScript.py "Reset Groudon Kyogre and Rayquaza" -i 0x27e8 1 0x80 1
@py -3 PKSMScript.py "Reset Xerneas and Yveltal" -i 0x27f9 1 0x50 1
@py -3 PKSMScript.py "Reset Giratina Cresselia Cobalion Terrakion Virizion Tornadus Thundurus and Reshiram" -i 0x27e6 1 0x00 1
@py -3 PKSMScript.py "Reset Articuno Zapdos Moltres and Mewtwo" -i 0x27f8 1 0x00 1
@py -3 PKSMScript.py "Reset Ho-Oh Uxie Mesprit Azelf Dialga Palkia Heatran and Regigigas" -i 0x27e5 1 0x00 1
@py -3 PKSMScript.py "Reset Zekrom Landorus Kyurem Latias Latios Regirock Regice and Registeel" -i 0x27e7 1 0x00 1
@py -3 PKSMScript.py "Reset Raikou Entei Suicune and Lugia" -i 0x27e4 1 0x0F 1
@py -3 PKSMScript.py "Reset Magearna" -i 0x2687 1 223 1
@py -3 PKSMScript.py "Reset Main Conflict" -i 0x1e88 1 0xcc 1 -i 0x1e89 1 0x06 1 -i 0x2130 1 0x02 1 -i 0x21ac 1 0xe8 1 -i 0x21ad 1 0xe4 1 -i 0x25f0 1 0x1c 1 -i 0x2802 1 0x09 1 -i 0x2652 1 0x7b 1 -i 0x2653 1 0x7c 1 -i 0x265e 1 0x7f 1 -i 0x265f 1 0x01 1 -i 0x268e 1 0xfd 1 -i 0x26a2 1 0x77 1 -i 0x26a7 1 0xf3 1

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

@py -3 PKSMScript.py "Set Battle Style Normal" -i 0x147A 1 0 1
@py -3 PKSMScript.py "Set Battle Style Elegant" -i 0x147A 1 1 1
@py -3 PKSMScript.py "Set Battle Style Girlish" -i 0x147A 1 2 1
@py -3 PKSMScript.py "Set Battle Style Reverent" -i 0x147A 1 3 1
@py -3 PKSMScript.py "Set Battle Style Smug" -i 0x147A 1 4 1
@py -3 PKSMScript.py "Set Battle Style Left-Handed" -i 0x147A 1 5 1
@py -3 PKSMScript.py "Set Battle Style Passionate" -i 0x147A 1 6 1
@py -3 PKSMScript.py "Set Battle Style Idol" -i 0x147A 1 7 1
@py -3 PKSMScript.py "Set Battle Style Nihilist" -i 0x147A 1 8 1

@mkdir usum
@move /Y *.pksm usum

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
@py -3 PKSMScript.py "Set max money" -i 0x4004 4 9999999 1
@py -3 PKSMScript.py "Inject living dex" -i 0x4E00 186064 "data/living7.bin" 1
@py -3 PKSMScript.py "Set max Battle Points" -i 0x0411C 4 9999 1
@py -3 PKSMScript.py "Set max Festival Coins" -i 0x50D08 4 9999999 1
@py -3 PKSMScript.py "Set max Camera Shots" -i 0x65004 4 9999999 1
@py -3 PKSMScript.py "Set max Thumbs Up" -i 0x6500C 4 9999999 1
@py -3 PKSMScript.py "Set max Camera Version" -i 0x65000 2 4 1
@py -3 PKSMScript.py "Set all Zygarde Cells (cores not included)" -i 0x1D42 1 95 1 -i 0x1D52 1 95 1 -i 0x1D8C 2 512 95
@py -3 PKSMScript.py "All Items 99x" -i 0x0 1340 "data/SM_AllItems.bin" 1
@py -3 PKSMScript.py "All Berries 99x" -i 0xC47 268 "data/SM_AllBerries.bin" 1
@py -3 PKSMScript.py "All Medicine 99x" -i 0xB48 216 "data/SM_AllMedicines.bin" 1
@py -3 PKSMScript.py "All TMs Owned" -i 0x998 400 "data/SM_AllTM.bin" 1
@py -3 PKSMScript.py "All Z-Crystals Owned" -i 0xD68 116 "data/SM_AllZCrystals.bin" 1

@py -3 PKSMScript.py "Set Vivillon Icy Snow form" -i 0x4130 1 0 1
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
@move /Y *.pksm sm

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
@py -3 PKSMScript.py "Unlock & max all O-Powers" -i 0x17400 68 "data/ORAS_OPower.bin" 1
@py -3 PKSMScript.py "Reset all legendaries" -i 0x14d11 1 0x0F 1 -i 0x14d12 1 0x00 1 -i 0x14d13 1 0x06 1 -i 0x14d16 1 0xDC 1 -i 0x14d1b 1 0xEF 1 -i 0x14d1c 1 0xEB 1 -i 0x14d30 1 0x22 1 -i 0x14d4c 1 0x61 1 -i 0x14d4d 1 0x7E 1 -i 0x14d71 1 0xF7 1 -i 0x14d72 1 0x8C 1 -i 0x14d73 1 0x8F 1 -i 0x14e5b 1 0x00 1 -i 0x14e5c 1 0x00 1 -i 0x14e5d 1 0x00 1 -i 0x14e5e 1 0x00 1 -i 0x14e5f 1 0x00 1 -i 0x14e68 1 0x17 1
@py -3 PKSMScript.py "Reset Delta Episode" -i 0x483f 1 0x12 1 -i 0x14d17 1 0xc0 1 -i 0x14d30 1 0x23 1 -i 0x14d35 1 0x06 1 -i 0x14d3f 1 0xff 1 -i 0x14d47 1 0xef 1 -i 0x14d51 1 0xfd 1 -i 0x14d54 1 0xf8 1 -i 0x14d55 1 0xf0 1 -i 0x14d56 1 0xcb 1 -i 0x14d59 1 0x80 1 -i 0x14d5a 1 0x8d 1 -i 0x14d5b 1 0xff 1 -i 0x14d6a 1 0xf7 1 -i 0x14d6e 1 0xff 1 -i 0x14d6f 1 0xd7 1 -i 0x14d70 1 0x8a 1 -i 0x14d73 1 0x8d 1 -i 0x14e45 1 0xfc 1 -i 0x14e51 1 0x01 1 -i 0x14e59 1 0x7f 1 -i 0x14e5f 1 0x04 1 -i 0x14e65 1 0x3e 1 -i 0x14e69 1 0x99 1
@py -3 PKSMScript.py "Give all berries 99x" -i 0xE70 268 "data\ORAS_AllBerries.bin" 1
@py -3 PKSMScript.py "Give all items 99x" -i 0x400 1220 "data\ORAS_AllItems.bin" 1
@py -3 PKSMScript.py "Give all medicines 99x" -i 0xD70 216 "data\ORAS_AllMedicines.bin" 1
@py -3 PKSMScript.py "All TMs and HMs owned" -i 0xBC0 428 "data\ORAS_AllTMHM.bin" 1

@py -3 PKSMScript.py "Set Vivillon Icy Snow form" -i 0x4244 1 0 1
@py -3 PKSMScript.py "Set Vivillon Polar form" -i 0x4244 1 1 1
@py -3 PKSMScript.py "Set Vivillon Tundra form" -i 0x4244 1 2 1
@py -3 PKSMScript.py "Set Vivillon Continental form" -i 0x4244 1 3 1
@py -3 PKSMScript.py "Set Vivillon Garden form" -i 0x4244 1 4 1
@py -3 PKSMScript.py "Set Vivillon Elegant form" -i 0x4244 1 5 1
@py -3 PKSMScript.py "Set Vivillon Meadow form" -i 0x4244 1 6 1
@py -3 PKSMScript.py "Set Vivillon Modern form" -i 0x4244 1 7 1
@py -3 PKSMScript.py "Set Vivillon Marine form" -i 0x4244 1 8 1
@py -3 PKSMScript.py "Set Vivillon Archipelago form" -i 0x4244 1 9 1
@py -3 PKSMScript.py "Set Vivillon High-Plains form" -i 0x4244 1 10 1
@py -3 PKSMScript.py "Set Vivillon Sandstorm form" -i 0x4244 1 11 1
@py -3 PKSMScript.py "Set Vivillon River form" -i 0x4244 1 12 1
@py -3 PKSMScript.py "Set Vivillon Monsoon form" -i 0x4244 1 13 1
@py -3 PKSMScript.py "Set Vivillon Savannah form" -i 0x4244 1 14 1
@py -3 PKSMScript.py "Set Vivillon Sun form" -i 0x4244 1 15 1
@py -3 PKSMScript.py "Set Vivillon Ocean form" -i 0x4244 1 16 1
@py -3 PKSMScript.py "Set Vivillon Jungle form" -i 0x4244 1 17 1
@py -3 PKSMScript.py "Set Vivillon Fancy form" -i 0x4244 1 18 1
@py -3 PKSMScript.py "Set Vivillon Pokeball form" -i 0x4244 1 19 1

@mkdir oras
@move /Y *.pksm oras

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
@py -3 PKSMScript.py "Reset Mewtwo and Zygarde" -i 0x14d74 1 0x01 1 -i 0x14d5e 1 0x1f 1 -i 0x14d0a 1 0x80 1
@py -3 PKSMScript.py "Reset Legendary Birds" -i 0x483f 1 0x1b 1 -i 0x14bcc 1 0x01 1
@py -3 PKSMScript.py "Give all berries 99x" -i 0xE68 268 "data\XY_AllBerries.bin" 1
@py -3 PKSMScript.py "Give all items 99x" -i 0x400 1156 "data\XY_AllItems.bin" 1
@py -3 PKSMScript.py "Give all medicines 99x" -i 0xD68 204 "data\XY_AllMedicines.bin" 1
@py -3 PKSMScript.py "All TMs and HMs owned" -i 0xBC0 420 "data\XY_AllTMHM.bin" 1

@py -3 PKSMScript.py "Set Vivillon Icy Snow form" -i 0x4250 1 0 1
@py -3 PKSMScript.py "Set Vivillon Polar form" -i 0x4250 1 1 1
@py -3 PKSMScript.py "Set Vivillon Tundra form" -i 0x4250 1 2 1
@py -3 PKSMScript.py "Set Vivillon Continental form" -i 0x4250 1 3 1
@py -3 PKSMScript.py "Set Vivillon Garden form" -i 0x4250 1 4 1
@py -3 PKSMScript.py "Set Vivillon Elegant form" -i 0x4250 1 5 1
@py -3 PKSMScript.py "Set Vivillon Meadow form" -i 0x4250 1 6 1
@py -3 PKSMScript.py "Set Vivillon Modern form" -i 0x4250 1 7 1
@py -3 PKSMScript.py "Set Vivillon Marine form" -i 0x4250 1 8 1
@py -3 PKSMScript.py "Set Vivillon Archipelago form" -i 0x4250 1 9 1
@py -3 PKSMScript.py "Set Vivillon High-Plains form" -i 0x4250 1 10 1
@py -3 PKSMScript.py "Set Vivillon Sandstorm form" -i 0x4250 1 11 1
@py -3 PKSMScript.py "Set Vivillon River form" -i 0x4250 1 12 1
@py -3 PKSMScript.py "Set Vivillon Monsoon form" -i 0x4250 1 13 1
@py -3 PKSMScript.py "Set Vivillon Savannah form" -i 0x4250 1 14 1
@py -3 PKSMScript.py "Set Vivillon Sun form" -i 0x4250 1 15 1
@py -3 PKSMScript.py "Set Vivillon Ocean form" -i 0x4250 1 16 1
@py -3 PKSMScript.py "Set Vivillon Jungle form" -i 0x4250 1 17 1
@py -3 PKSMScript.py "Set Vivillon Fancy form" -i 0x4250 1 18 1
@py -3 PKSMScript.py "Set Vivillon Pokeball form" -i 0x4250 1 19 1

@mkdir xy
@move /Y *.pksm xy

@rem B2W2 SCRIPTS
@py -3 PKSMScript.py "Clear Mystery Gift data" -i 0x1C800 1 0x0 2704
@py -3 PKSMScript.py "Set max money" -i 0x21100 4 9999999 1
@py -3 PKSMScript.py "Inject living dex" -i 0x00400 4080 "data/living5/boxdata BOX 1.bin" 1 -i 0x01400 4080 "data/living5/boxdata BOX 2.bin" 1 -i 0x02400 4080 "data/living5/boxdata BOX 3.bin" 1 -i 0x03400 4080 "data/living5/boxdata BOX 4.bin" 1 -i 0x04400 4080 "data/living5/boxdata BOX 5.bin" 1 -i 0x05400 4080 "data/living5/boxdata BOX 6.bin" 1 -i 0x06400 4080 "data/living5/boxdata BOX 7.bin" 1 -i 0x07400 4080 "data/living5/boxdata BOX 8.bin" 1 -i 0x08400 4080 "data/living5/boxdata BOX 9.bin" 1 -i 0x09400 4080 "data/living5/boxdata BOX 10.bin" 1 -i 0x0A400 4080 "data/living5/boxdata BOX 11.bin" 1 -i 0x0B400 4080 "data/living5/boxdata BOX 12.bin" 1 -i 0x0C400 4080 "data/living5/boxdata BOX 13.bin" 1 -i 0x0D400 4080 "data/living5/boxdata BOX 14.bin" 1 -i 0x0E400 4080 "data/living5/boxdata BOX 15.bin" 1 -i 0x0F400 4080 "data/living5/boxdata BOX 16.bin" 1 -i 0x10400 4080 "data/living5/boxdata BOX 17.bin" 1 -i 0x11400 4080 "data/living5/boxdata BOX 18.bin" 1 -i 0x12400 4080 "data/living5/boxdata BOX 19.bin" 1 -i 0x13400 4080 "data/living5/boxdata BOX 20.bin" 1 -i 0x14400 4080 "data/living5/boxdata BOX 21.bin" 1 -i 0x15400 4080 "data/living5/boxdata BOX 22.bin" 1 -i 0x16400 4080 "data/living5/boxdata BOX 23.bin" 1 -i 0x17400 4080 "data/living5/boxdata BOX 24.bin" 1
@py -3 PKSMScript.py "Set max Battle Points" -i 0x21B00 2 9999 1
@py -3 PKSMScript.py "Give all items 99x (illegal)" -i 0x18400 1044 "data\BWB2W2_AllItems_illegal.bin" 1
@py -3 PKSMScript.py "Give all items 99x" -i 0x18400 976 "data\BWB2W2_AllItems.bin" 1
@py -3 PKSMScript.py "All TMs and HMs owned" -i 0x18a24 404 "data\BWB2W2_AllTMHM.bin" 1
@py -3 PKSMScript.py "Give all medicine 99x" -i 0x18bd8 188 "data\BWB2W2_AllMedicine.bin" 1
@py -3 PKSMScript.py "Give all berries 99x (illegal)" -i 0x18c98 256 "data\BWB2W2_AllBerries_illegal.bin" 1
@py -3 PKSMScript.py "Give all berries 99x" -i 0x18c98 248 "data\BWB2W2_AllBerries.bin" 1

@mkdir b2w2
@move /Y *.pksm b2w2

@rem BW SCRIPTS
@py -3 PKSMScript.py "Clear Mystery Gift data" -i 0x1C800 1 0x0 2704
@py -3 PKSMScript.py "Set max money" -i 0x21200 4 9999999 1
@py -3 PKSMScript.py "Inject living dex" -i 0x00400 4080 "data/living5/boxdata BOX 1.bin" 1 -i 0x01400 4080 "data/living5/boxdata BOX 2.bin" 1 -i 0x02400 4080 "data/living5/boxdata BOX 3.bin" 1 -i 0x03400 4080 "data/living5/boxdata BOX 4.bin" 1 -i 0x04400 4080 "data/living5/boxdata BOX 5.bin" 1 -i 0x05400 4080 "data/living5/boxdata BOX 6.bin" 1 -i 0x06400 4080 "data/living5/boxdata BOX 7.bin" 1 -i 0x07400 4080 "data/living5/boxdata BOX 8.bin" 1 -i 0x08400 4080 "data/living5/boxdata BOX 9.bin" 1 -i 0x09400 4080 "data/living5/boxdata BOX 10.bin" 1 -i 0x0A400 4080 "data/living5/boxdata BOX 11.bin" 1 -i 0x0B400 4080 "data/living5/boxdata BOX 12.bin" 1 -i 0x0C400 4080 "data/living5/boxdata BOX 13.bin" 1 -i 0x0D400 4080 "data/living5/boxdata BOX 14.bin" 1 -i 0x0E400 4080 "data/living5/boxdata BOX 15.bin" 1 -i 0x0F400 4080 "data/living5/boxdata BOX 16.bin" 1 -i 0x10400 4080 "data/living5/boxdata BOX 17.bin" 1 -i 0x11400 4080 "data/living5/boxdata BOX 18.bin" 1 -i 0x12400 4080 "data/living5/boxdata BOX 19.bin" 1 -i 0x13400 4080 "data/living5/boxdata BOX 20.bin" 1 -i 0x14400 4080 "data/living5/boxdata BOX 21.bin" 1 -i 0x15400 4080 "data/living5/boxdata BOX 22.bin" 1 -i 0x16400 4080 "data/living5/boxdata BOX 23.bin" 1 -i 0x17400 4080 "data/living5/boxdata BOX 24.bin" 1
@py -3 PKSMScript.py "Set max Battle Points" -i 0x21D00 2 9999 1
@py -3 PKSMScript.py "Reset Victini" -i 0x20222 1 0x02 1 -i 0x204ee 1 0xd2 1 -i 0x204ef 1 0x5b 1 -i 0x23f5a 1 0xd2 1 -i 0x23f5b 1 0x5b 1
@py -3 PKSMScript.py "Reset Darmanitan" -i 0x203ce 1 0x7f 1 -i 0x203cf 1 0x30 1 -i 0x204ee 1 0x65 1 -i 0x204ef 1 0xa4 1 -i 0x23f5a 1 0x65 1 -i 0x23f5b 1 0xa4 1
@py -3 PKSMScript.py "Reset Fossil Choice" -i 0x2038e 1 0x04 1 -i 0x204ee 1 0x17 1 -i 0x204ef 1 0xdd 1 -i 0x23f5a 1 0x17 1 -i 0x23f5b 1 0xdd 1
@py -3 PKSMScript.py "Give all items 99x (illegal)" -i 0x18400 1044 "data\BWB2W2_AllItems_illegal.bin" 1
@py -3 PKSMScript.py "Give all items 99x" -i 0x18400 976 "data\BWB2W2_AllItems.bin" 1
@py -3 PKSMScript.py "All TMs and HMs owned (illegal)" -i 0x18a24 404 "data\BWB2W2_AllTMHM.bin" 1
@py -3 PKSMScript.py "All TMs and HMs owned" -i 0x18a24 400 "data\BW_AllTMHM.bin" 1
@py -3 PKSMScript.py "Give all medicine 99x" -i 0x18bd8 188 "data\BWB2W2_AllMedicine.bin" 1
@py -3 PKSMScript.py "Give all berries 99x (illegal)" -i 0x18c98 256 "data\BWB2W2_AllBerries_illegal.bin" 1
@py -3 PKSMScript.py "Give all berries 99x" -i 0x18c98 248 "data\BWB2W2_AllBerries.bin" 1

@mkdir bw
@move /Y *.pksm bw

@rem HGSS SCRIPTS
@py -3 PKSMScript.py "Clear Mystery Gift data" -i 0x9D3C 1 0x0 2336
@py -3 PKSMScript.py "Max money held by mother" -i 0xC0D8 4 999999 1
@py -3 PKSMScript.py "Set max money" -i 0x78 4 999999 1
@py -3 PKSMScript.py "Set max Battle Points" -i 0x5BB8 2 9999 1
@py -3 PKSMScript.py "Give all items 99x" -i 0x644 648 "data\HGSS_AllItems.bin" 1
@py -3 PKSMScript.py "Give all medicines 99x" -i 0xB64 152 "data\HGSS_AllMedicines.bin" 1
@py -3 PKSMScript.py "Give all battle items 99x" -i 0xD64 52 "data\HGSS_AllBattleItems.bin" 1
@py -3 PKSMScript.py "Give all berries 99x" -i 0xC04 256 "data\HGSS_AllBerries.bin" 1
@py -3 PKSMScript.py "Give all TM&HM 99x" -i 0x9A0 400 "data\HGSS_AllTMHM.bin" 1
@py -3 PKSMScript.py "Give all pokeballs 99x" -i 0xD04 96 "data\HGSS_AllPokeballs.bin" 1
@py -3 PKSMScript.py "Give all Apricorns 99x" -i 0xE558 1 99 7
@py -3 PKSMScript.py "Unlock all Pokewalker Courses" -i 0xE70C 1 0xFF 3 -i 0xE70F 1 0x07 1
@py -3 PKSMScript.py "Reset Legendary Beasts" -i 0xf26 1 0x00 1 -i 0x10fd 1 0xb1 1
@py -3 PKSMScript.py "Reset Articuno Moltres and Mewtwo" -i 0x1124 1 0x0f 1
@py -3 PKSMScript.py "Set max Game Corner coins" -i 0x84 2 50000 1

@mkdir hgss
@move /Y *.pksm hgss

@rem PT SCRIPTS
@py -3 PKSMScript.py "Clear Mystery Gift data" -i 0xB4C0 1 0x0 2336
@py -3 PKSMScript.py "Set max money" -i 0x7c 4 999999 1
@py -3 PKSMScript.py "Set max Battle Points" -i 0x7234 2 9999 1
@py -3 PKSMScript.py "Set max Underground flags" -i 0x3ce8 4 999999 1
@py -3 PKSMScript.py "Give all items 99x" -i 0x630 648 "data/Pt_AllItems.bin" 1
@py -3 PKSMScript.py "Give all medicines 99x" -i 0xB4C 152 "data/DPPt_AllMedicines.bin" 1
@py -3 PKSMScript.py "Give all battle items 99x" -i 0xD28 52 "data/DPPt_AllBattleItems.bin" 1
@py -3 PKSMScript.py "Give all berries 99x" -i 0xBEC 256 "data/DPPt_AllBerries.bin" 1
@py -3 PKSMScript.py "Give all TM&HM 99x" -i 0x98C 400 "data/DPPt_AllTMHM.bin" 1
@py -3 PKSMScript.py "Give all pokeballs 99x" -i 0xCEC 60 "data/DPPt_AllPokeballs.bin" 1
@py -3 PKSMScript.py "Set 32 people met Underground" -i 0x3cb4 2 32 1
@py -3 PKSMScript.py "Set max Game Corner coins" -i 0x88 2 50000 1
@py -3 PKSMScript.py "Get all Pokewatch apps" -i 0x1161 1 25 1 -i 0x1163 1 1 25 -i 0x1184 1 1 1

@mkdir pt
@move /Y *.pksm pt

@rem DP SCRIPTS
@py -3 PKSMScript.py "Clear Mystery Gift data" -i 0xA7D0 1 0x0 2124
@py -3 PKSMScript.py "Set max money" -i 0x78 4 999999 1
@py -3 PKSMScript.py "Set max Battle Points" -i 0x65F8 2 9999 1
@py -3 PKSMScript.py "Set max Underground Flags" -i 0x3A60 4 999999 1
@py -3 PKSMScript.py "Get all Pokewatch apps" -i 0x114D 1 25 1 -i 0x114F 1 1 25 -i 0x1170 1 1 1
@py -3 PKSMScript.py "Set all legendaries battlable" -i 0x0e08 1 0x08 1 -i 0x0e09 1 0x02 1 -i 0x0e0a 1 0x29 1 -i 0x0e0b 1 0x02 1 -i 0x0e0c 1 0x12 1 -i 0x0e0d 1 0x03 1 -i 0x0e0e 1 0x28 1 -i 0x0e0f 1 0x10 1 -i 0x0e22 1 0x09 1 -i 0x0e23 1 0x12 1 -i 0x0e24 1 0x12 1 -i 0x0e25 1 0x11 1 -i 0x0e26 1 0x23 1 -i 0x0e27 1 0x11 1 -i 0x0ecc 1 0x05 1 -i 0x0ed8 1 0x01 1 -i 0x0fff 1 0x8C 1 -i 0x1000 1 0xEA 1 -i 0x1001 1 0x10 1 -i 0x1002 1 0x08 1 -i 0x1003 1 0x50 1 -i 0x101b 1 0x7F 1 -i 0x101b 1 0xDF 1 -i 0x101b 1 0xBF 1 -i 0x101b 1 0x1F 1 -i 0x1027 1 0x10 1 -i 0x1028 1 0x00 1 -i 0x1029 1 0xD0 1 -i 0x1029 1 0xB0 1 -i 0x1029 1 0x70 1 -i 0x1029 1 0xE0 1 -i 0x1029 1 0x00 1 -i 0x102b 1 0x93 1
@py -3 PKSMScript.py "Set all legendaries disappeared" -i 0x0e08 1 0x00 1 -i 0x0e09 1 0x00 1 -i 0x0e0a 1 0x00 1 -i 0x0e0b 1 0x00 1 -i 0x0e0c 1 0x00 1 -i 0x0e0d 1 0x00 1 -i 0x0e0e 1 0x00 1 -i 0x0e0f 1 0x00 1 -i 0x0e22 1 0x00 1 -i 0x0e23 1 0x00 1 -i 0x0e24 1 0x00 1 -i 0x0e25 1 0x00 1 -i 0x0e26 1 0x00 1 -i 0x0e27 1 0x00 1 -i 0x0ecc 1 0x04 1 -i 0x0ed8 1 0x02 1 -i 0x0fff 1 0xCC 1 -i 0x1000 1 0xEB 1 -i 0x1001 1 0x30 1 -i 0x1002 1 0x00 1 -i 0x1003 1 0x40 1 -i 0x101b 1 0xFF 1 -i 0x1027 1 0x50 1 -i 0x1028 1 0x02 1 -i 0x1029 1 0xF0 1 -i 0x102b 1 0x97 1
@py -3 PKSMScript.py "Reset Darkrai" -i 0x1027 1 0x50 1 -i 0x0e22 1 0x09 1 -i 0x0e23 1 0x12 1
@py -3 PKSMScript.py "Reset Palkia" -i 0x0ecc 1 0x05 1
@py -3 PKSMScript.py "Give all items 99x" -i 0x623 644 "data/DP_AllItems.bin" 1
@py -3 PKSMScript.py "Give all medicines 99x" -i 0xB40 152 "data/DPPt_AllMedicines.bin" 1
@py -3 PKSMScript.py "Give all battle items 99x" -i 0xD1C 52 "data/DPPt_AllBattleItems.bin" 1
@py -3 PKSMScript.py "Give all berries 99x" -i 0xBE0 256 "data/DPPt_AllBerries.bin" 1
@py -3 PKSMScript.py "Give all TM&HM 99x" -i 0x980 400 "data/DPPt_AllTMHM.bin" 1
@py -3 PKSMScript.py "Give all pokeballs 99x" -i 0xCE0 60 "data/DPPt_AllPokeballs.bin" 1
@py -3 PKSMScript.py "Set 32 people met Underground" -i 0x3a2c 2 32 1
@py -3 PKSMScript.py "Set max Game Corner coins" -i 0x84 2 50000 1

@mkdir dp
@move /Y *.pksm dp

@mkdir scripts
@move /Y dp scripts
@move /Y pt scripts
@move /Y hgss scripts
@move /Y bw scripts
@move /Y b2w2 scripts
@move /Y xy scripts
@move /Y oras scripts
@move /Y sm scripts
@move /Y usum scripts
