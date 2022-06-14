/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 24;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "Hermit:size=9","FontAwesome:pixelsize=14" };
static const char dmenufont[]       = "Hack:size=9";
// colors
//static const char col_bg_bar[]        = "#111111";
static const char col_bg_bar[]        = "#000000";
static const char winbord_sel[]       = "#444444";
static const char winbord_norm[]      = "#000000";
static const char col_norm_bar[]       	  = "#7F7F7F";
static const char col_sel_bar[]       	  = "#005577";


static const unsigned int baralpha = OPAQUE;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_norm_bar, col_bg_bar, winbord_norm },
	[SchemeSel]  = { col_norm_bar, col_bg_bar, winbord_sel  },

};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "","","","","","","","","" };

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance    title       tags mask    isfloating        monitor */
	{ "qBittorrent",	NULL,       NULL,       1 << 8,			0,           -1 },
	{ "firefox",		NULL,       NULL,       1 << 2,			0,           -1 },
	{ "Zathura",		NULL,       NULL,       1 << 5,			0,           -1 },
	{ "qutebrowser",	NULL,       NULL,       1 << 2,			0,           -1 },
    { "Subl",	        NULL,       NULL,       1 << 3,			0,           -1 },
    { "Code",	        NULL,       NULL,       1 << 3,			0,           -1 },
	{ "LF",	                NULL,       NULL,       1 << 4,			0,           -1 },
	{ "newsboat",           NULL,       NULL,       1 << 5,			0,           -1 },
    { "ncmpcpp",	        NULL,       NULL,       1 << 6,			0,           -1 },
	// { "",	            NULL,       NULL,       1 << 6,			0,           -1 },
	// { "",	            NULL,       NULL,       1 << 6,			0,           -1 },

};
/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
//static const char *dmenucmd[] = { "rofi -show drun", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *browcmd[]  = { "qutebrowser", NULL };

static Key keys[] = {
	/* media keys */
	{0,                XF86XK_AudioRaiseVolume,        spawn,   SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +10%") },
    {0,                XF86XK_AudioLowerVolume,        spawn,   SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -10%") },
    {0,                XF86XK_AudioMute,               spawn,   SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle") },
    {0,                XF86XK_AudioMicMute,            spawn,   SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
    {0,                XF86XK_AudioPrev,               spawn,   SHCMD("mpc prev") },
	{0,                XF86XK_AudioPlay,               spawn,   SHCMD("mpc toggle") },
	{0,                XF86XK_AudioNext,               spawn,   SHCMD("mpc next") },
      /*ThinkVantage Key*/
    {0,                XF86XK_Launch1,                 spawn,   SHCMD("xset dpms force off") },
      /* brightness control */
    {0,					XF86XK_MonBrightnessDown,		spawn,  SHCMD("light -U 4") },
    {0,					XF86XK_MonBrightnessUp,			spawn,  SHCMD("light -A 4") },
      /* screenshot: pacman -S scrot */
    {0,                 XK_Print,                       spawn,  SHCMD("scrot scrot_%Y-%m-%d-%T_$wx$h.png") },
      /* dmenu scripts */
    { MODKEY,                       XK_b,	   spawn,           SHCMD("~/.bin/bmenu") },
    { MODKEY|ShiftMask,             XK_e,      spawn,           SHCMD("~/.bin/pmenu") },
    { MODKEY          ,             XK_x,      spawn,           SHCMD("~/.bin/favmenu") },
      /* ncmpcpp */
	{ MODKEY|ShiftMask,             XK_m,      spawn,           SHCMD("st -c ncmpcpp -e ncmpcpp") },
      /*lf file manager*/
	{ MODKEY|ShiftMask,             XK_f,      spawn,           SHCMD("st -c LF -e lfrun") },
      /* newsboat */ 
	{ MODKEY|ShiftMask,             XK_n,      spawn,           SHCMD("st -c newsboat -e newsboat") },
      /* nvim shortcut */
    { MODKEY|ShiftMask,             XK_v,      spawn,           SHCMD("st -c vim -e nvim") },
      /* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = browcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY,                       XK_Left,   viewtoleft,     {0} },
    { MODKEY,                       XK_Right,  viewtoright,    {0} },
    { MODKEY|ShiftMask,             XK_Left,   tagtoleft,      {0} },
    { MODKEY|ShiftMask,             XK_Right,  tagtoright,     {0} },	
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

