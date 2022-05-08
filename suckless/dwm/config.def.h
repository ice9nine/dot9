/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 6;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 6;       /* vert inner gap between windows */
static const unsigned int gappoh    = 6;       /* horiz outer gap between windows and screen
edge */
static const unsigned int gappov    = 6;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 1;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Linux Libertine Mono:style=Mono:autohint=true:antialias=true:size=14", "Joypixels:style=Regular:autohint=true:antialias=true:size=12" };
static const char dmenufont[]       = "Linux Libertine Mono:style=Mono:autohint=true:antialias=true:size=18";
static const char col_red[]         = "#ff0000";
static const char col_yellow[]      = "#ffff00";
static const char col_teal[]        = "#008080";
static const char col_magenta[]     = "#ff00ff";
static const char col_green[]       = "#00ff00";
static const char col_black[]       = "#000000";
static const char col_grey1[]       = "#575757";
static const char col_blue[]        = "#0000ff";
static const char col_darkblue[]    = "#01018e";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_red, col_black, col_red },
	[SchemeSel]  = { col_yellow, col_black, col_yellow },
};

/* tagging */
static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
        { "[@]",      spiral },
        { "[\\]",     dwindle },
        { "TTT",      bstack },
        { "###",      nrowgrid },
        { "---",      horizgrid },
        { ":::",      gaplessgrid },
        { "|M|",      centeredmaster },
        { "><>",      NULL },    /* no layout function means floating behavior */
        { NULL,       NULL },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_black, "-nf", col_red, "-sb", col_magenta, "-sf", col_black, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *term2cmd[]  = { "terminator", NULL };
static const char *web2cmd[]  = { "brave", NULL };
static const char *webcmd[]  = { "firefox", NULL };
static const char *filecmd[]  = { "st", "-e", "ranger", NULL };
static const char *file2cmd[]  = { "pcmanfm", NULL };
static const char *volcmd[]  = { "pavucontrol", NULL };
static const char *vol2cmd[]  = { "st", "-e", "alsamixer", NULL };
static const char *calccmd[]  = { "st", "-e", "bc", NULL };
static const char *calcmd[]  = { "st","-e", "cal", NULL };
static const char *msgcmd[]  = { "android-messages-desktop", NULL };
static const char *msg2cmd[]  = { "caprine", NULL };
static const char *bluetoothcmd[]  = { "blueberry", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = bluetoothcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ Mod1Mask|ShiftMask,           XK_Return, spawn,          {.v = term2cmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = webcmd } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = web2cmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = filecmd } },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = file2cmd } },
	{ MODKEY,                       XK_v,      spawn,          {.v = volcmd } },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = vol2cmd } },
	{ MODKEY,                       XK_c,      spawn,          {.v = calccmd } },
	{ MODKEY|ShiftMask,             XK_c,      spawn,          {.v = calcmd } },
	{ MODKEY,                       XK_m,      spawn,          {.v = msgcmd } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = msg2cmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
        { MODKEY|Mod1Mask,              XK_comma,  cyclelayout,    {.i = -1 } },
        { MODKEY|Mod1Mask,              XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_z,      incrgaps,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_z,      incrgaps,       {.i = -1 } },
	{ MODKEY,                       XK_x,      defaultgaps,    {0} },
	{ MODKEY|ShiftMask,             XK_x,      togglegaps,     {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|Mod1Mask,              XK_1,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|Mod1Mask,              XK_2,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|Mod1Mask,              XK_3,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|Mod1Mask,              XK_4,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|Mod1Mask,              XK_5,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|Mod1Mask,              XK_6,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|Mod1Mask,              XK_7,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY|Mod1Mask,              XK_8,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY|Mod1Mask,              XK_9,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY|Mod1Mask,              XK_0,      setlayout,      {.v = &layouts[9]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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
