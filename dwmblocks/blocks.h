//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{"  "," ~/.dotfiles/scripts/mpd", 2 , 0},
	{" ", "~/.dotfiles/scripts/netscript", 2 , 0},
	{"  "," ~/.dotfiles/scripts/temp", 2 , 0},
	{"  "," ~/.dotfiles/scripts/cpuload", 2 , 0},
	{"  "," free -h | awk '/^Mem/ { print $3\"/\"$2 }' | sed s/i//g",	5, 0},
	{"  "," ~/.dotfiles/scripts/hdd", 40, 0},
	{" ", "~/.dotfiles/scripts/voidupdates", 500 , 0},
	{"  "," iwgetid -r" , 1, 0},
//	{"  "," acpi |cut -d , -f 2", 5, 0},
//	{"   "," /usr/bin/checkupdates| wc -l", 1500, 0},
	{" "," ~/.dotfiles/scripts/batt", 5, 0},
	{"  ", " pamixer --get-volume", 2, 0},
	{" ","date '+%I:%M%p' ", 5, 0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " : ";
static unsigned int delimLen = 2;
