#pragma once

// Plugin information
#ifndef PLUGIN_NAME
#error You need to define PLUGIN_NAME
#endif // PLUGIN_NAME
#define PLUGIN_VERSION 1

#include "bridgemain.h"
#include "_plugins.h"

#include "_scriptapi_argument.h"
#include "_scriptapi_assembler.h"
#include "_scriptapi_bookmark.h"
#include "_scriptapi_comment.h"
#include "_scriptapi_debug.h"
#include "_scriptapi_flag.h"
#include "_scriptapi_function.h"
#include "_scriptapi_gui.h"
#include "_scriptapi_label.h"
#include "_scriptapi_memory.h"
#include "_scriptapi_misc.h"
#include "_scriptapi_module.h"
#include "_scriptapi_pattern.h"
#include "_scriptapi_register.h"
#include "_scriptapi_stack.h"
#include "_scriptapi_symbol.h"

#include "jansson/jansson.h"
#include "lz4/lz4file.h"
#include "XEDParse/XEDParse.h"

#define Cmd(x) DbgCmdExecDirect(x)
#define Eval(x) DbgValFromString(x)
#define dprintf(x, ...) _plugin_logprintf("[" PLUGIN_NAME "] " x, __VA_ARGS__)
#define dputs(x) _plugin_logprintf("[" PLUGIN_NAME "] %s\n", x)
#define PLUG_EXPORT extern "C" __declspec(dllexport)

// Global variables required by some of the _plugin_xxx functions
extern int pluginHandle;
extern HWND hwndDlg;
extern int hMenu;
extern int hMenuDisasm;
extern int hMenuDump;
extern int hMenuStack;
extern int hMenuGraph;
extern int hMenuMemmap;
extern int hMenuSymmod;