#include <X11/XF86keysym.h>

#define MODKEY Mod1Mask

#define TAGKEYS(KEY,TAG) \
  { MODKEY, KEY, view, {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask, KEY, toggleview, {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask, KEY, tag, {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY, toggletag, {.ui = 1 << TAG} },

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

// Appearance
static const unsigned int borderpx = 1;
static const unsigned int snap = 32;
static const int showbar = 1;
static const int topbar = 1;
static const char *fonts[] = { "monospace:size=10" };

// Gaps
static const unsigned int gappih = 10;
static const unsigned int gappiv = 10;
static const unsigned int gappoh = 10;
static const unsigned int gappov = 10;
static int smartgaps = 1;

// Colors
static const char col_gray1[] = "#212121";
static const char col_gray2[] = "#424242";
static const char col_gray3[] = "#bdbdbd";
static const char col_gray4[] = "#e0e0e0";
static const char col_prime[] = "#6200ea";

// Themes
static const char *colors[][3] = {
  [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
  [SchemeSel] = { col_gray4, col_prime, col_prime },
};

// Tags
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

// Rules
static const Rule rules[] = {
  { "Gimp", NULL, NULL, 0, 1, -1 },
  { "Firefox", NULL, NULL, 1 << 8, 0, -1 },
};

// Systray
static const unsigned int systraypinning = 1;
static const unsigned int systrayonleft = 0;
static const unsigned int systrayspacing = 5;
static const int systraypinningfailfirst = 1;
static const int showsystray = 1;

// Misc
static const float mfact = 0.5;
static const int nmaster = 1;
static const int resizehints = 1;
static const int lockfullscreen = 1;

// Layouts
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
  { "[\\]", dwindle },
  { "[]=", tile },
  { "><>", NULL },
  { "[M]", monocle },
};

// dmenu
static char dmenumon[2] = "0";
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };

static Key keys[] = {
  // Layouts
  { MODKEY, XK_d, setlayout, {.v = &layouts[0]} },
  { MODKEY, XK_t, setlayout, {.v = &layouts[1]} },
  { MODKEY, XK_f, setlayout, {.v = &layouts[2]} },
  { MODKEY, XK_m, setlayout, {.v = &layouts[3]} },
  { MODKEY, XK_space, setlayout, {0} },
  { MODKEY|ShiftMask, XK_space, togglefloating, {0} },

  // Tags
  TAGKEYS(XK_1, 0)
  TAGKEYS(XK_2, 1)
  TAGKEYS(XK_3, 2)
  TAGKEYS(XK_4, 3)
  TAGKEYS(XK_5, 4)
  TAGKEYS(XK_6, 5)
  TAGKEYS(XK_7, 6)
  TAGKEYS(XK_8, 7)
  TAGKEYS(XK_9, 8)
  { MODKEY, XK_0, view, {.ui = ~0 } },
  { MODKEY|ShiftMask, XK_0, tag, {.ui = ~0 } },
  { MODKEY, XK_Tab, view, {0} },

  // Monitor switching
  { MODKEY|ShiftMask, XK_comma, tagmon, {.i = -1 } },
  { MODKEY|ShiftMask, XK_period, tagmon, {.i = +1 } },

  // Focus
  { MODKEY, XK_j, focusstack, {.i = +1 } },
  { MODKEY, XK_k, focusstack, {.i = -1 } },
  { MODKEY, XK_comma, focusmon, {.i = -1 } },
  { MODKEY, XK_period, focusmon, {.i = +1 } },

  // Window adjustment
  { MODKEY, XK_h, setmfact, {.f = -0.05} },
  { MODKEY, XK_l, setmfact, {.f = +0.05} },
  { MODKEY, XK_Return, zoom, {0} },

  // Quicklaunch
  { MODKEY, XK_p, spawn, {.v = dmenucmd } },

  // Terminal
  { MODKEY|ShiftMask, XK_Return, spawn, SHCMD("st") },

  // Browser
  { MODKEY, XK_b, spawn, SHCMD("chromium") },

  // File explorer
  { MODKEY, XK_e, spawn, SHCMD("nautilus") },

  // Media control
  { 0, XF86XK_AudioPlay, spawn, SHCMD("playerctl play-pause") },
  { 0, XF86XK_AudioStop, spawn, SHCMD("playerctl stop") },
  { 0, XF86XK_AudioPrev, spawn, SHCMD("playerctl previous") },
  { 0, XF86XK_AudioNext, spawn, SHCMD("playerctl next") },

  // Volume
  { 0, XF86XK_AudioMute, spawn, SHCMD("pamixer -t && pkill -RTMIN+10 dwmblocks") },
  { 0, XF86XK_AudioLowerVolume, spawn, SHCMD("pamixer -d 5 && pkill -RTMIN+10 dwmblocks") },
  { 0, XF86XK_AudioRaiseVolume, spawn, SHCMD("pamixer -i 5 && pkill -RTMIN+10 dwmblocks") },

  // Visibility
  { MODKEY, XK_x, togglebar, {0} },

  // Close
  { MODKEY|ShiftMask, XK_c, killclient, {0} },

  // Quit
  { MODKEY|ShiftMask, XK_q, quit, {0} },
};

static Button buttons[] = {
  // Window adjustment
  { ClkWinTitle, 0, Button2, zoom, {0} },
  { ClkClientWin, MODKEY, Button1, movemouse, {0} },
  { ClkClientWin, MODKEY, Button2, togglefloating, {0} },
  { ClkClientWin, MODKEY, Button3, resizemouse, {0} },

  // Tags
  { ClkTagBar, 0, Button1, view, {0} },
  { ClkTagBar, 0, Button3, toggleview, {0} },
  { ClkTagBar, MODKEY, Button1, tag, {0} },
  { ClkTagBar, MODKEY, Button3, toggletag, {0} },
};
