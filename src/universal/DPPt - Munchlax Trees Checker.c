#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int rollover(int num) {
	num++;
	if (num == 21) {
		num = 0;
	}
	return num;
}

int main(int argc, char **argv) {
	unsigned char *saveData = (unsigned char *)atoi(argv[0]);
    unsigned char version = *argv[2];
    int gbo = sav_gbo();
    int TID;
    int SID;
	int res[4];
	char* trees[] = {"Route 205 (Near Floaroma Town)", "Route 205 (Near Eterna City)", "Route 206 (Under Bike Path)",
		"Route 207", "Route 208 (Near Hearthome City)", "Route 209 (Near Hallowed Tower)", "Route 210 South (Near Café Cabin)",
		"Route 210 North (Near Wilma's House)", "Route 211 (Near Celestic Town)", "Route 212 (Near Hearthome City)", 
		"Route 212 (Near Pastoria City)", "Route 213 (Near Pastoria City)", "Route 214 (Near Valor Lakefront)", "Route 215 (Near Café Cabin)", 
		"Route 218 (Near Canalave City)", "Route 221 (Near Pal Park)", "Route 222 (Near Sunyshore City)", "Valley Windworks",
		"Eterna Forest (Exterior)", "Fuego Ironworks", "Floaroma Meadow (Near Honey Man)"};
		
	switch (version) {
		case 10:
			TID = *(unsigned short*)(saveData + 0x74);
			SID = *(unsigned short*)(saveData + 0x76);
			break;
		case 11:
			TID = *(unsigned short*)(saveData + 0x74);
			SID = *(unsigned short*)(saveData + 0x76);
			break;
		case 12:
			TID = *(unsigned short*)(saveData + 0x78);
			SID = *(unsigned short*)(saveData + 0x7A);
			break;
		default:
			gui_warn("This script is only meant for", "the Sinnoh games (DPPt)");
			return 1;
	}
	
	res[0] = (SID % 256) % 21;
	res[1] = (SID / 256) % 21;
	res[2] = (TID % 256) % 21;
	res[3] = (TID / 256) % 21;
	
	if (res[0] == res[1]) {
		res[1] = rollover(res[1]);
	} if (res[0] == res[2]) {
		res[2] = rollover(res[2]);
	} if (res[1] == res[2]) {
		res[2] = rollover(res[2]);
	} if (res[0] == res[3]) {
		res[3] = rollover(res[3]);
	} if (res[1] == res[3]) {
		res[3] = rollover(res[3]);
	} if (res[2] == res[3]) {
		res[3] = rollover(res[3]);
	}
	
	gui_warn("Your Munchlax trees are,", "as follows...");
	gui_warn(trees[res[0]], trees[res[1]]);
	gui_warn(trees[res[2]], trees[res[3]]);
	return 0;
}