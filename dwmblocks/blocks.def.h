//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{"  ", "~/.dotfiles/scripts/temp.sh", 2 , 0},
	{" ", "~/.dotfiles/scripts/cpuload.sh", 2 , 0},
	{" ", "free -h | awk '/^Mem/ { print $3\"/\"$2 }' | sed s/i//g ",	5, 0},
	{" ", "~/.dotfiles/scripts/hdd.sh", 40, 0},
	{" ", "iwgetid -r" , 1, 0},
//	{"", "acpi |cut -d , -f 2", 5, 0},
//	{" ", "/usr/bin/checkupdates| wc -l ", 1500, 0},
	{" ", "~/.dotfiles/scripts/batt.sh ", 5, 0},
	{" ", "pulsemixer --get-volume|cut -d \" \" -f 1", 2, 0},
	{"", "date '+%I:%M%p' ", 5, 0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
