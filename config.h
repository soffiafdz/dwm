/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 2;   /* border pixel of windows */
static unsigned int snap      = 32;  /* snap pixel */
static int swallowfloating    = 0;   /* 1 means swallow floating windows by default */
static unsigned int gappih    = 25;  /* horiz inner gap between windows */
static unsigned int gappiv    = 10;  /* vert inner gap between windows */
static unsigned int gappoh    = 10;  /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 20;  /* vert outer gap between windows and screen edge */
static int smartgaps          = 0;   /* 1 means no outer gap when there is only one window */
static int showbar            = 1;   /* 0 means no bar */
static int topbar             = 1;   /* 0 means bottom bar */
static int focusonwheel       = 1;
static int user_bh            = 0;   /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */

static char font[]                      = "FiraCode Nerd Font:style=Regular:size=14:antialias=true";
static const char *fonts[]              = { font, "JoyPixels:pixelsize=14:antialias=true:autohint=true" };
static char normbgcolor[]               = "#222222";
static char normbordercolor[]           = "#444444";
static char normfgcolor[]               = "#bbbbbb";
static char selfgcolor[]                = "#eeeeee";
static char selbordercolor[]            = "#420000";
static char selbgcolor[]                = "#420000";
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
	"xcompmgr", NULL,
	"dunst", NULL,
	"unclutter", NULL,
	"redshift", NULL,
	"dwmbar", NULL,
	"clipmenud", NULL,
	NULL
};

/* tagging */
static const char *tags[]       = { "", "", "󰿉", "", "", "", "󰑈", "", "󰖟" };
static const char *tagsalt[]    = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class           instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "kitty",         NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "kitty",         NULL,     "tmux",         1,         0,          1,           0,        -1 },
	{ "kitty",         NULL,     "Yazi: ~/",     1 << 1,    0,          1,           0,        -1 },
	{ "Todoist",       NULL,     NULL,           1 << 2,    0,          0,           0,        -1 },
	{ "thunderbird",   NULL,     NULL,           1 << 2,    0,          0,           0,        -1 },
	{ "Zotero",        NULL,     NULL,           1 << 3,    0,          0,           0,        -1 },
	{ "calibre",       NULL,     NULL,           1 << 3,    0,          0,           0,        -1 },
	{ "sioyek",        NULL,     NULL,           1 << 3,    0,          0,           0,        -1 },
	{ NULL,   "libreoffice",     NULL,           1 << 3,    0,          0,           0,        -1 },
	{ "zoom",          NULL,     NULL,           1 << 4,    0,          0,           0,        -1 },
	{ "Microsoft Teams - Preview",NULL,NULL,     1 << 4,    0,          0,           0,        -1 },
	{ "Slack",         NULL,     NULL,           1 << 4,    0,          0,           0,        -1 },
	{ "TelegramDesktop",NULL,    NULL,           1 << 4,    0,          0,           0,        -1 },
	{ "Signal",        NULL,     NULL,           1 << 4,    0,          0,           0,        -1 },
	{ "discord",       NULL,     "Discord",      1 << 4,    0,          0,           0,        -1 },
	{ "Ferdium",       NULL,     NULL,           1 << 4,    0,          0,           0,        -1 },
	{ "Gimp",          NULL,     NULL,           1 << 5,    1,          0,           0,        -1 },
	{ "Rawtherapee",   NULL,     NULL,           1 << 5,    0,          0,           0,        -1 },
	{ "ART",           NULL,     NULL,           1 << 5,    0,          0,           0,        -1 },
	{ "digikam",       NULL,     NULL,           1 << 5,    0,          0,           0,        -1 },
	{ "mpv",           NULL,     NULL,           1 << 6,    0,          0,           0,        -1 },
	{ "Jellyfin Media Player",NULL,NULL,        1 << 6,    0,          0,           0,        -1 },
	{ "Feishin",       NULL,     NULL,           1 << 7,    0,          0,           0,        -1 },
	{ "firefox",       NULL,     NULL,           1 << 8,    0,          0,           0,        -1 },
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

	{ "[M]",      monocle },
	{ "H[]",      deck },

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
	&((Keychord){1, {{MODKEY, KEY}}, view, {.ui = 1 << TAG}}), \
	&((Keychord){1, {{MODKEY|ControlMask, KEY}}, toggleview, {.ui = 1 << TAG}}), \
	&((Keychord){1, {{MODKEY|ShiftMask, KEY}}, tag, {.ui = 1 << TAG}}), \
	&((Keychord){1, {{MODKEY|ControlMask|ShiftMask, KEY}}, toggletag, {.ui = 1 << TAG}}),
#define STACKKEYS(MOD,ACTION) \
	&((Keychord){1, {{MOD, XK_j}}, ACTION##stack, {.i = INC(+1)}}), \
	&((Keychord){1, {{MOD, XK_k}}, ACTION##stack, {.i = INC(-1)}}), \
	&((Keychord){1, {{MOD, XK_v}}, ACTION##stack, {.i = 0}}),
/* Move mode: Super+M, then number to send window to tag */
#define MOVEKEYS(KEY,TAG) \
	&((Keychord){2, {{MODKEY, XK_m}, {0, KEY}}, tag, {.ui = 1 << TAG}}),
/* Toggleview mode: Super+C, then number to toggle viewing that tag */
#define TOGGLEVIEWKEYS(KEY,TAG) \
	&((Keychord){2, {{MODKEY, XK_c}, {0, KEY}}, toggleview, {.ui = 1 << TAG}}),

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "kitty", NULL };

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
/* 		{ "borderpx",           INTEGER,     &borderpx },         */
/* 		{ "snap",               INTEGER,     &snap },             */
/* 		{ "showbar",            INTEGER,     &showbar },          */
/* 		{ "topbar",             INTEGER,     &topbar },           */
/* 		{ "focusonwheel",       INTEGER,     &focusonwheel  },    */
/* 		{ "user_bh",            INTEGER,     &user_bh  },         */
/* 		{ "nmaster",            INTEGER,     &nmaster },          */
/* 		{ "resizehints",        INTEGER,     &resizehints },      */
/* 		{ "mfact",              FLOAT,       &mfact },            */
/* 		{ "gappih",             INTEGER,     &gappih },           */
/* 		{ "gappiv",             INTEGER,     &gappiv },           */
/* 		{ "gappoh",             INTEGER,     &gappoh },           */
/* 		{ "gappov",             INTEGER,     &gappov },           */
/* 		{ "smartgaps",          INTEGER,     &smartgaps },        */
};

#include "shiftview.c"
#include <X11/XF86keysym.h>
static Keychord *keychords[] = {
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
	/* Move mode: Super+M, then 1-9 to send window to tag */
	MOVEKEYS(                       XK_1,                            0)
	MOVEKEYS(                       XK_2,                            1)
	MOVEKEYS(                       XK_3,                            2)
	MOVEKEYS(                       XK_4,                            3)
	MOVEKEYS(                       XK_5,                            4)
	MOVEKEYS(                       XK_6,                            5)
	MOVEKEYS(                       XK_7,                            6)
	MOVEKEYS(                       XK_8,                            7)
	MOVEKEYS(                       XK_9,                            8)
	/* Move mode: Super+M, then G/; to send window to prev/next tag */
	&((Keychord){2, {{MODKEY, XK_m}, {0, XK_g}}, shifttag, {.i = -1}}),
	&((Keychord){2, {{MODKEY, XK_m}, {0, XK_semicolon}}, shifttag, {.i = +1}}),
	/* Move mode: Super+M, then N/P to send window to monitor */
	&((Keychord){2, {{MODKEY, XK_m}, {0, XK_n}}, tagmon, {.i = +1}}),
	&((Keychord){2, {{MODKEY, XK_m}, {0, XK_p}}, tagmon, {.i = -1}}),
	/* Move mode: Super+M, then M/U for mount/unmount drives */
	&((Keychord){2, {{MODKEY, XK_m}, {0, XK_m}}, spawn, SHCMD("dmenumount")}),
	&((Keychord){2, {{MODKEY, XK_m}, {0, XK_u}}, spawn, SHCMD("dmenuumount")}),
	/* Toggleview mode: Super+C, then 1-9 to toggle viewing that tag */
	TOGGLEVIEWKEYS(                 XK_1,                            0)
	TOGGLEVIEWKEYS(                 XK_2,                            1)
	TOGGLEVIEWKEYS(                 XK_3,                            2)
	TOGGLEVIEWKEYS(                 XK_4,                            3)
	TOGGLEVIEWKEYS(                 XK_5,                            4)
	TOGGLEVIEWKEYS(                 XK_6,                            5)
	TOGGLEVIEWKEYS(                 XK_7,                            6)
	TOGGLEVIEWKEYS(                 XK_8,                            7)
	TOGGLEVIEWKEYS(                 XK_9,                            8)
	&((Keychord){1, {{MODKEY, XK_0}}, view, {.ui = ~0}}),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_0}}, tag, {.ui = ~0}}),
	&((Keychord){1, {{MODKEY, XK_minus}}, spawn, SHCMD("pamixer --allow-boost -d 5; refbar")}),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_minus}}, spawn, SHCMD("pamixer --allow-boost -i 5; refbar")}),
	&((Keychord){1, {{MODKEY, XK_equal}}, spawn, SHCMD("pamixer -t; refbar")}),
	/* Shift+= is FREE */

	&((Keychord){1, {{MODKEY, XK_Return}}, spawn, {.v = termcmd}}),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_Return}}, spawn, SHCMD("$TERMINAL -e init_tmux")}),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_Escape}}, spawn, SHCMD("prompt 'ShutDown?' 'sudo shutdown -h now'")}),
	&((Keychord){1, {{MODKEY, XK_BackSpace}}, spawn, SHCMD("sysaction")}),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_BackSpace}}, quit, SHCMD("sysaction")}),
	&((Keychord){1, {{MODKEY, XK_Tab}}, view, {0}}),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_Tab}}, view, {0}}),
	&((Keychord){1, {{MODKEY, XK_space}}, zoom, {0}}),
	/* Shift+Space is FREE */
	&((Keychord){1, {{MODKEY, XK_o}}, togglefloating, {0}}),

	&((Keychord){1, {{MODKEY, XK_q}}, killclient, {0}}),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_q}}, spawn, SHCMD("kill -9 $(xdotool getwindowfocus getwindowpid)")}),
	&((Keychord){1, {{MODKEY, XK_w}}, spawn, SHCMD("$BROWSER")}),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_w}}, spawn, SHCMD("$TERMINAL -e sudo nmtui")}),
	&((Keychord){1, {{MODKEY, XK_e}}, spawn, SHCMD("$TERMINAL -e nvim")}),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_e}}, spawn, SHCMD("$TERMINAL -e nvim -c VimwikiIndex")}),
	&((Keychord){1, {{MODKEY, XK_r}}, spawn, SHCMD("$TERMINAL -e yazi")}),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_r}}, spawn, SHCMD("$TERMINAL -e btm")}),
	&((Keychord){1, {{MODKEY, XK_t}}, setlayout, {.v = &layouts[0]}}), /* Tile */
	&((Keychord){1, {{MODKEY|ShiftMask, XK_t}}, setlayout, {.v = &layouts[1]}}), /* Bstack */
	&((Keychord){1, {{MODKEY, XK_y}}, setlayout, {.v = &layouts[4]}}), /* Monocle */
	&((Keychord){1, {{MODKEY|ShiftMask, XK_y}}, setlayout, {.v = &layouts[5]}}), /* Deck */
	&((Keychord){1, {{MODKEY, XK_u}}, setlayout, {.v = &layouts[6]}}), /* CenteredMaster */
	&((Keychord){1, {{MODKEY|ShiftMask, XK_u}}, setlayout, {.v = &layouts[7]}}), /* CFloatingMaster */
	&((Keychord){1, {{MODKEY, XK_i}}, incnmaster, {.i = +1}}),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_i}}, incnmaster, {.i = -1}}),
	/* O is float toggle (see above) */
	/* Shift+O is FREE */
	/* P is for monitor prev (see below) */

	/* A is FREE - Aerospace uses for accordion layout */
	&((Keychord){1, {{MODKEY|ShiftMask, XK_a}}, spawn, SHCMD("$TERMINAL -e pulsemixer")}),
	&((Keychord){1, {{MODKEY, XK_s}}, spawn, SHCMD("flameshot gui")}),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_s}}, spawn, SHCMD("flameshot full -p ~/Pictures/screenshots")}),
	&((Keychord){1, {{MODKEY, XK_d}}, spawn, {.v = dmenucmd}}),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_d}}, spawn, SHCMD("dmenupass")}),
	&((Keychord){1, {{MODKEY, XK_f}}, togglefullscr, {0}}),
	/* Shift+F is FREE */
	&((Keychord){1, {{MODKEY, XK_g}}, shiftview, {.i = -1}}),
	/* Shift+G is FREE - use move mode G instead */
	&((Keychord){1, {{MODKEY, XK_h}}, setmfact, {.f = -0.05}}),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_h}}, setcfact, {.f = +0.25}}),
	/* J & K: STACKKEYS */
	&((Keychord){1, {{MODKEY, XK_l}}, setmfact, {.f = +0.05}}),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_l}}, setcfact, {.f = -0.25}}),
	&((Keychord){1, {{MODKEY, XK_semicolon}}, shiftview, {.i = 1}}),
	/* Shift+; is FREE - use move mode ; instead */
	&((Keychord){1, {{MODKEY, XK_apostrophe}}, setcfact, {.f = 0.00}}),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_apostrophe}}, spawn, SHCMD("refbar")}),

	&((Keychord){1, {{MODKEY, XK_z}}, togglegaps, {0}}),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_z}}, defaultgaps, {0}}),
	&((Keychord){1, {{MODKEY, XK_x}}, spawn, SHCMD("clipmenu")}),
	/* Shift+X is FREE */
	/* V is STACKKEY (focus master) */
	&((Keychord){1, {{MODKEY, XK_b}}, togglealttag, {0}}),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_b}}, togglebar, {0}}),
	/* N/P for monitors */
	&((Keychord){1, {{MODKEY, XK_n}}, focusmon, {.i = +1}}),
	/* Shift+N is FREE - use move mode N instead */
	&((Keychord){1, {{MODKEY, XK_p}}, focusmon, {.i = -1}}),
	/* Shift+P is FREE - use move mode P instead */
	/* ,/. are FREE */

	&((Keychord){1, {{0, XF86XK_AudioMute}}, spawn, SHCMD("pamixer -t; refbar")}),
	&((Keychord){1, {{0, XF86XK_AudioRaiseVolume}}, spawn, SHCMD("pamixer --allow-boost -i 3; refbar")}),
	&((Keychord){1, {{0, XF86XK_AudioLowerVolume}}, spawn, SHCMD("pamixer --allow-boost -d 3; refbar")}),
	&((Keychord){1, {{0, XF86XK_AudioPrev}}, spawn, SHCMD("playerctl previous")}),
	&((Keychord){1, {{0, XF86XK_AudioNext}}, spawn, SHCMD("playerctl next")}),
	&((Keychord){1, {{0, XF86XK_AudioPause}}, spawn, SHCMD("playerctl pause")}),
	&((Keychord){1, {{0, XF86XK_AudioPlay}}, spawn, SHCMD("playerctl play")}),
	&((Keychord){1, {{0, XF86XK_AudioStop}}, spawn, SHCMD("playerctl stop")}),
	&((Keychord){1, {{0, XF86XK_AudioRewind}}, spawn, SHCMD("playerctl position OFFSET -10")}),
	&((Keychord){1, {{0, XF86XK_AudioForward}}, spawn, SHCMD("playerctl position OFFSET +10")}),
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

