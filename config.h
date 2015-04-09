/* See LICENSE file for copyright and license details. */

/* appearance */
#define NUMCOLORS 8             // need at least 3
static const char colors[NUMCOLORS][3][8] = {
    // border   foreground  background
    { "#4f3d52", "#ebaf7b", "#000000" },  // 1 normal
    { "#d08252", "#ffffff", "#000000" },  // 2 selected
    { "#ffffff", "#ffffff", "#d7656d" },  // 3 warning
    { "#a64a4c", "#000000", "#faff41" },  // 4 error
    { "#ffffff", "#ffffff", "#555555" },  // 5 time

    { "#ffffff", "#ffa442", "#000000" },  //  light
    { "#ffffff", "#816a62", "#000000" },  //  dark
    { "#ffffff", "#585d70", "#000000" },  //  separator
   };

static const char *fonts[] = {
    "Terminus:size=12",
};

/* appearance */
static const char font[]            = "-*-terminus-*-*-normal-*-12-*-*-*-*-*-*-u";
static const char normbordercolor[] = "#374757";//#4d3258";// "#02313b";
static const char normbgcolor[]     = "#000000";//#100414";//"#000B0F";
static const char normfgcolor[]     = "#70a0a9";//#d68573";//"#24968f";
static const char selbordercolor[]  = "#aa0000";//#ffceb8";//"#ffceb8";//"#ffcf69";
static const char selbgcolor[]      = "#265165";//#4d3258";//"#094C4D";
static const char selfgcolor[]      = "#ffffff";//#ffceb8";//"#1BD0CD";*/
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 0;   /* systray spacing */
static const Bool systraypinningfailfirst = True;   /* True: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const Bool showsystray       = True;     /* False means no systray */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "Q", "W", "E", "A", "S", "D" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[#]",      tile },    /* first entry is default */
	{ "[~]",      NULL },    /* no layout function means floating behavior */
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
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", colors[0][2], "-nf", colors[0][1], "-sb", colors[1][2], "-sf", colors[1][1], NULL };
static const char *termcmd[]  = { "urxvt", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_v,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_plus, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_Left,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_Right,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_y,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_x,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_Up,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_Down,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_c,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_backslash,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_backslash,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    TAGKEYS(                        XK_q,                      0)
        TAGKEYS(                        XK_w,                      1)
        TAGKEYS(                        XK_e,                      2)
        TAGKEYS(                        XK_a,                      3)
        TAGKEYS(                        XK_s,                      4)
        TAGKEYS(                        XK_d,                      5)
        { MODKEY|ShiftMask,             XK_F10,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

