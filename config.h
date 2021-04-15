/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 3;   /* border pixel of windows */
static unsigned int snap      = 32;  /* snap pixel */
static int swallowfloating    = 0;   /* 1 means swallow floating windows by default */
static unsigned int gappih    = 20;  /* horiz inner gap between windows */
static unsigned int gappiv    = 10;  /* vert inner gap between windows */
static unsigned int gappoh    = 10;  /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 20;  /* vert outer gap between windows and screen edge */
static int smartgaps          = 0;   /* 1 means no outer gap when there is only one window */
static int showbar            = 1;   /* 0 means no bar */
static int topbar             = 1;   /* 0 means bottom bar */
static int focusonwheel       = 1;
static int user_bh            = 0;   /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */

static char font[]                      = "monospace:size=10";
static const char *fonts[]              = { font, "JoyPixels:pixelsize=10:antialias=true:autohint=true" };
static char normbgcolor[]               = "#222222";
static char normbordercolor[]           = "#444444";
static char normfgcolor[]               = "#bbbbbb";
static char selfgcolor[]                = "#eeeeee";
static char selbordercolor[]            = "#005577";
static char selbgcolor[]                = "#005577";
static const unsigned int baralpha      = 0xd0;
static const unsigned int borderalpha   = OPAQUE;
static char *colors[][3]                = {
	/*               fg             bg              border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};
static const unsigned int alphas[][3]   = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

static const char *const autostart[]    = {
	"setwp", NULL,
	"xrdb", "/home/soffiafdz/.config/x11/xresources", NULL,
	"xcompmgr", NULL,
	"dunst", NULL,
	"xset", "r" "rate" "300", "50", NULL,
	"unclutter", NULL,
	"redshift", NULL,
	"setxkbmap", "-option", "compose:ralt", NULL,
	NULL
};

/* tagging */
static const char *tags[]    = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tagsalt[] = { "X", "X", "X", "X", "X", "X", "X", "X", "X" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class           instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",          NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Brave-browser", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",            NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,            NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "TTT",      bstack },

	{ "HHH",      grid },
	{ "###",      nrowgrid },

	{ "H[]",      deck },
	{ "[M]",      monocle },

	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },

/* 	{ "[@]",      spiral },      */
/* 	{ "[\\]",     dwindle },     */
/* 	{ "===",      bstackhoriz }, */
/* 	{ "---",      horizgrid },   */
/* 	{ ":::",      gaplessgrid }, */

	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,  view,         {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,  toggleview,   {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,  tag,          {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,  toggletag,    {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_v,     ACTION##stack, {.i = 0 } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \       */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \       */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } },        */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "st", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "font",               STRING,      &font },
		{ "color0",             STRING,      &normbgcolor },
		{ "color15",            STRING,      &selbgcolor },
		{ "color15",            STRING,      &normfgcolor },
		{ "color0",             STRING,      &selfgcolor },
		{ "color0",             STRING,      &normbordercolor },
		{ "color3",             STRING,      &selbordercolor },
		{ "borderpx",           INTEGER,     &borderpx },
		{ "snap",               INTEGER,     &snap },
		{ "showbar",            INTEGER,     &showbar },
		{ "topbar",             INTEGER,     &topbar },
		{ "focusonwheel",       INTEGER,     &focusonwheel  },
		{ "user_bh",            INTEGER,     &user_bh  },
		{ "nmaster",            INTEGER,     &nmaster },
		{ "resizehints",        INTEGER,     &resizehints },
		{ "mfact",              FLOAT,       &mfact },
		{ "gappih",             INTEGER,     &gappih },
		{ "gappiv",             INTEGER,     &gappiv },
		{ "gappoh",             INTEGER,     &gappoh },
		{ "gappov",             INTEGER,     &gappov },
		{ "smartgaps",          INTEGER,     &smartgaps },
};

#include "shiftview.c"

static Key keys[] = {
	/* modifier                     key              function        argument */
	STACKKEYS(MODKEY,                                focus)
	STACKKEYS(MODKEY|ShiftMask,                      push)
	TAGKEYS(                        XK_1,                            0)
	TAGKEYS(                        XK_2,                            1)
	TAGKEYS(                        XK_3,                            2)
	TAGKEYS(                        XK_4,                            3)
	TAGKEYS(                        XK_5,                            4)
	TAGKEYS(                        XK_6,                            5)
	TAGKEYS(                        XK_7,                            6)
	TAGKEYS(                        XK_8,                            7)
	TAGKEYS(                        XK_9,                            8)
	{ MODKEY,                       XK_0,            view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,            tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_minus,        spawn,          SHCMD("pamixer --allow-boost -d 5") },
	{ MODKEY|ShiftMask,             XK_minus,        spawn,          SHCMD("pamixer --allow-boost -d 15") },
	{ MODKEY,                       XK_plus,         spawn,          SHCMD("pamixer --allow-boost -i 5") },
	{ MODKEY|ShiftMask,             XK_plus,         spawn,          SHCMD("pamixer --allow-boost -i 15") },
	{ MODKEY,                       XK_equal,        spawn,          SHCMD("pamixer --mute") },
	{ MODKEY|ShiftMask,             XK_equal,        spawn,          SHCMD("pamixer --unmute") },

	{ MODKEY,                       XK_Return,       spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return,       spawn,          SHCMD("$TERMINAL -e tmux") },
	{ MODKEY,                       XK_Escape,       spawn,          SHCMD("sudo -A zzz") },
	{ MODKEY|ShiftMask,             XK_Escape,       spawn,          SHCMD("prompt 'ShutDown?' 'sudo shutdown -h now'") },
	{ MODKEY,                       XK_BackSpace,    spawn,          SHCMD("sysaction") },
	{ MODKEY|ShiftMask,             XK_BackSpace,    quit,           {0} },
	{ MODKEY,                       XK_Tab,          view,           {0} },
	{ MODKEY|ShiftMask,             XK_Tab,          view,           {0} },
	{ MODKEY,                       XK_Space,        zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_Space,        togglefloating, {0} },

	{ MODKEY,                       XK_q,            killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,            spawn,          SHCMD("kill -9 $(xdotool getwindowfocus getwindowpid)") },
	{ MODKEY,                       XK_w,            spawn,          SHCMD("$BROWSER") },
	{ MODKEY|ShiftMask,             XK_w,            spawn,          SHCMD("$TERMINAL -e sudo nmtui") },
	{ MODKEY,                       XK_e,            spawn,          SHCMD("$TERMINAL -e nvim") },
	{ MODKEY|ShiftMask,             XK_e,            spawn,          SHCMD("$TERMINAL -e nvim -c VimwikiIndex") },
	{ MODKEY,                       XK_r,            spawn,          SHCMD("$TERMINAL -e lf") },
	{ MODKEY|ShiftMask,             XK_r,            spawn,          SHCMD("$TERMINAL -e bpytop") },
	{ MODKEY,                       XK_t,            spawn,          {.v = &layouts[0]} }, /* Tile */
	{ MODKEY|ShiftMask,             XK_t,            spawn,          {.v = &layouts[1]} }, /* Bstack */
	{ MODKEY,                       XK_y,            spawn,          {.v = &layouts[2]} }, /* Grid */
	{ MODKEY|ShiftMask,             XK_y,            spawn,          {.v = &layouts[3]} }, /* Nrowgrid */
	{ MODKEY,                       XK_u,            spawn,          {.v = &layouts[4]} }, /* Deck */
	{ MODKEY|ShiftMask,             XK_u,            spawn,          {.v = &layouts[5]} }, /* Monocle */
	{ MODKEY,                       XK_i,            spawn,          {.v = &layouts[6]} }, /* CenteredMaster */
	{ MODKEY|ShiftMask,             XK_i,            spawn,          {.v = &layouts[7]} }, /* CFloatingMaster */
	{ MODKEY,                       XK_o,            incnmaster,     {.i = +1} },
	{ MODKEY|ShiftMask,             XK_o,            incnmaster,     {.i = -1} },
	{ MODKEY,                       XK_p,            spawn,          SHCMD("flameshot gui") },
	{ MODKEY|ShiftMask,             XK_p,            spawn,          SHCMD("fullscreenshot") },

	{ MODKEY,                       XK_a,            spawn,          SHCMD("$TERMINAL -e pulsemixer") },
/* 	{ MODKEY|ShiftMask,             XK_a,            spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_s,            togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_s,            defaultgaps,    {0} },
	{ MODKEY,                       XK_d,            spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_d,            spawn,          SHCMD("passmenu") },
	{ MODKEY,                       XK_f,            togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_f,            setlayout,      {.v = &layouts[8]} },
	{ MODKEY,                       XK_g,            shiftview,      { .i = -1 } },
	{ MODKEY|ShiftMask,             XK_g,            shifttag,       { .i = -1 } },
	{ MODKEY,                       XK_h,            setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_h,            setcfact,       {.f = +0.25} },
                                /* J & K: STACKKEYS */
	{ MODKEY,                       XK_l,            setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_l,            setcfact,       {.f = -0.25} },
	{ MODKEY,                       XK_semicolon,    shiftview,      { .i = -1 } },
	{ MODKEY|ShiftMask,             XK_semicolon,    shifttag,       { .i = -1 } },
	{ MODKEY,                       XK_apostrophe,   setcfact,       {.f = 0.00} },
/*  For Tango; Broken Keyboard */
/* 	{ MODKEY|ShiftMask,             XK_apostrophe,   spawn,          SHCMD("kill_keyboard") }, */

	{ MODKEY,                       XK_z,            incrigaps,      {.i = +2 } },
	{ MODKEY|ShiftMask,             XK_z,            incrgaps,       {.i = +2 } },
	{ MODKEY,                       XK_x,            incrigaps,      {.i = -2 } },
	{ MODKEY|ShiftMask,             XK_x,            incrgaps,       {.i = -2 } },
/*  For Tango; Disable touch/trackpads */
/* 	{ MODKEY,                       XK_c,            spawn,          SHCMD("tpadToggle") }, */
/* 	{ MODKEY|ShiftMask,             XK_c,            spawn,          SHCMD("tpointToggle") }, */
/*                  V is TAGKEY                                                    */
	{ MODKEY,                       XK_b,            togglealttag,   {0} },
	{ MODKEY|ShiftMask,             XK_b,            togglebar,      {0} },
/* 	{ MODKEY,                       XK_n,            spawn,          SHCMD("seldisplay") }, */
/* 	{ MODKEY|ShiftMask,             XK_n,            spawn,          SHCMD("offScreen") }, */
	{ MODKEY,                       XK_m,            spawn,          SHCMD("dmenumount") },
	{ MODKEY|ShiftMask,             XK_m,            spawn,          SHCMD("dmenuumount") },
	{ MODKEY,                       XK_comma,        focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,        tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_period,       focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period,       tagmon,         {.i = +1 } },

	{ 0, XF86XK_AudioMute,          spawn,  SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,   spawn,  SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,   spawn,  SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,          spawn,  SHCMD("playerctl previous") },
	{ 0, XF86XK_AudioNext,          spawn,  SHCMD("playerctl next") },
	{ 0, XF86XK_AudioPause,         spawn,  SHCMD("playerctl pause") },
	{ 0, XF86XK_AudioPlay,          spawn,  SHCMD("playerctl play") },
	{ 0, XF86XK_AudioStop,          spawn,  SHCMD("playerctl stop") },
	{ 0, XF86XK_AudioRewind,        spawn,  SHCMD("playerctl position OFFSET -10") },
	{ 0, XF86XK_AudioForward,       spawn,  SHCMD("playerctl position OFFSET +10") },
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

