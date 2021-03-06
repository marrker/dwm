/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 3; /* border pixel size of windows */
static const unsigned int gappx          = 17;   /* gaps size between windows */
static const unsigned int snap           = 32;    /* snap pixel */
static const unsigned int systrayspacing = 2;
static const int showbar                 = 1; /* 0 means no bar */
static const int topbar                  = 1;  /* 0 means bottom bar */
static const int horizpadbar             = 0;        /* horizontal padding for statusbar */
static const int vertpadbar              = 10;        /* vertical padding for statusbar */
static const char *fonts[]               = {"JetBrainsMono:size=12", "fontawesome:size=12"};
static const char dmenufont[]            = "JetBrainsMono Nerd Font:size=11";
// background color
static const char col_gray1[]            = "#202020";
// inactive window border color
static const char col_gray2[]            = "#424242";
// font color
static const char col_gray3[]            = "#d4be98";
// current tag and current window font color
static const char col_gray4[]            = "#eeeeee";
// Top bar second color (blue) and active window border color
static const char col_cyan[]             = "#6f8faf";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm]     = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]      = { col_cyan, col_gray1, col_cyan },
    [SchemeStatus]   = { col_gray3, col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
  	[SchemeTagsSel]  = { col_gray1, col_cyan,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_gray3, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]   = { col_cyan, col_gray1,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_gray3, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
// tag names (upper left)
static const char *tags[] = {"???", "???", "???", "???", "???", "???", "???", "???", "???", "???"};
/* static const char *tags[] = { "1", "2", "3", "4", "5",  "6", "7", "8", "9",
 * "???" }; */

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */


static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp",      NULL,       NULL,       0,             1,           -1},
    {"firefox",   NULL,       NULL,       1 << 8,        0,           -1},
    {"discord",   NULL,       NULL,       1 << 7,        0,           -1},
    {"Steam",     NULL,       NULL,       1 << 6,        0,           -1},
    {"Spotify",   NULL,       NULL,       1 << 5,        0,           -1},

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG) \
      {MODKEY,                           KEY,     view,         {.ui = 1 << TAG} }, \
      {MODKEY | ControlMask,             KEY,     toggleview,   {.ui = 1 << TAG} }, \
      {MODKEY | ShiftMask,               KEY,     tag,          {.ui = 1 << TAG} }, \
      {MODKEY | ControlMask | ShiftMask, KEY,     toggletag,    {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
// static const char *filemanager[] = { "
// launches htop
static const char *monitor[] = {"/usr/bin/htop", NULL};
// sets st as the default terminal
static const char *termcmd[] = {"st", NULL};
// sets urxvt as the default terminal
// static const char *termcmd[]  = { "urxvt", NULL };
// volume controls
/*static const char *upvol[]   = { "amixer", "-q", "set", "Master", "5%+",
 * "unmute", NULL }; */
/*static const char *downvol[] = { "amixer", "-q", "set", "Master", "5%-",
 * "unmute", NULL }; */
/*static const char *mutevol[] = { "amixer", "-q", "set", "Master", "toggle",
 * NULL }; */

#include "shiftview.c"
static char *endx[] = {"/bin/sh", "-c", "endx", "externalpipe", NULL};
#include <X11/XF86keysym.h>
static const char *upvol[]     = {"/usr/bin/pactl", "set-sink-volume", "0", "+5%", NULL};
static const char *downvol[]   = {"/usr/bin/pactl", "set-sink-volume", "0", "-5%", NULL};
static const char *mutevol[]   = {"/usr/bin/pactl", "set-sink-mute", "0", "toggle", NULL};
static const char *prtscrcmd[] = {"flameshot", "gui", NULL};
static Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY | ShiftMask,            XK_y,      spawn,          SHCMD("flameshot full -p ~/Pictures/screenshots") }, 
    {MODKEY,                        XK_Print,  spawn,          {.v = prtscrcmd}},
    {MODKEY,                        XK_d,      spawn,          {.v = dmenucmd}},
    {MODKEY,                        XK_Return, spawn,          {.v = termcmd}},
    {MODKEY,                        XK_t,      togglebar,      {0}},
    {MODKEY | ShiftMask,            XK_j,      rotatestack,    {.i = +1}},
    {MODKEY | ShiftMask,            XK_k,      rotatestack,    {.i = -1}},
    {MODKEY,                        XK_j,      focusstack,     {.i = +1}},
    {MODKEY,                        XK_k,      focusstack,     {.i = -1}},
    {MODKEY,                        XK_i,      incnmaster,     {.i = +1}},
    {MODKEY,                        XK_u,      incnmaster,     {.i = -1}},
    {MODKEY,                        XK_h,      setmfact,       {.f = -0.05}},
    {MODKEY,                        XK_l,      setmfact,       {.f = +0.05}},
    {MODKEY,                        XK_z,      zoom,           {0}},
    {MODKEY,                        XK_Tab,    view,           {0}},
    {MODKEY | ShiftMask,            XK_Return, zoom,           {0}},
    {MODKEY,                        XK_q,      killclient,     {0}},
    {MODKEY | ShiftMask,            XK_t,      setlayout,      {.v = &layouts[0]}},
    {MODKEY | ShiftMask,            XK_f,      setlayout,      {.v = &layouts[1]}},
    {MODKEY,                        XK_f,      setlayout,      {.v = &layouts[2]}},
    {MODKEY | ShiftMask,            XK_space,  setlayout,      {0}},
    {MODKEY | ShiftMask,            XK_space,  togglefloating, {0}},
    {MODKEY,                        XK_0,      view,           {.ui = ~0}},
    {MODKEY | ShiftMask,            XK_0,      tag,            {.ui = ~0}},
    {MODKEY,                        XK_comma,  focusmon,       {.i = -1}},
    {MODKEY,                        XK_period, focusmon,       {.i = +1}},
    {MODKEY,                        XK_minus,  setgaps,        {.i = -1}},
    {MODKEY,                        XK_equal,  setgaps,        {.i = +1}},
    {MODKEY | ShiftMask,            XK_equal,  setgaps,        {.i = 0}},
    {MODKEY | ShiftMask,            XK_comma,  tagmon,         {.i = -1}},
    {MODKEY | ShiftMask,            XK_period, tagmon,         {.i = +1}},
    {MODKEY,                        XK_n,      shiftview,      {.i = +1}},
    {MODKEY,                        XK_b,      shiftview,      {.i = -1}},
    {MODKEY,                        XK_g,      setgaps,        {0}},
    {MODKEY | ShiftMask,            XK_g,      setgaps,        {17}},
    {MODKEY | ShiftMask,            XK_b,      spawn,
     SHCMD("feh --bg-fill --randomize ~/Pictures/wallpapers/* &")},
    {MODKEY,                        XK_w,      spawn,          SHCMD("firefox")},
    {MODKEY,                        XK_e,      spawn,          SHCMD("thunar")},
    {MODKEY,                        XK_r,      spawn,          SHCMD("st -e ranger")},
    /*{ MODKEY,                       XK_F8,     spawn,          {.v = upvol   }
       }, */
    /*{ MODKEY,                       XK_F7,     spawn,          {.v = downvol }
       }, */
    /*{ MODKEY,                       XK_F5,     spawn,          {.v = mutevol }
       }, */
    {0,               XF86XK_AudioMute,        spawn,          {.v = mutevol}},
    {0,               XF86XK_AudioRaiseVolume, spawn,          {.v = upvol}},
    {0,               XF86XK_AudioLowerVolume, spawn,          {.v = downvol}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
    TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
    TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol,           0,              Button1,        setlayout, {0}},
    {ClkLtSymbol,           0,              Button3,        setlayout, {.v = &layouts[2]}},
    {ClkWinTitle,           0,              Button2,        zoom, {0}},
    {ClkStatusText,         0,              Button2,        spawn, {.v = termcmd}},
    {ClkClientWin,          MODKEY,         Button1,        movemouse, {0}},
    {ClkClientWin,          MODKEY,         Button2,        togglefloating, {0}},
    //{ClkClientWin,          MODKEY,         Button3,        resizemouse, {0}},
    {ClkTagBar,             0,              Button1,        view, {0}},
    {ClkTagBar,             0,              Button3,        toggleview, {0}},
    {ClkTagBar,             MODKEY,         Button1,        tag, {0}},
    {ClkTagBar,             MODKEY,         Button3,        toggletag, {0}},
};
