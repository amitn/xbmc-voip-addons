#pragma once

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       do { delete (p);     (p)=NULL; } while (0)
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) do { delete[] (p);   (p)=NULL; } while (0)
#endif


#include "libXBMC_addon.h"
#include "libXBMC_voip.h"
#include "libXBMC_gui.h"

extern bool                          m_bCreated;
extern std::string                   g_strUserPath;
extern std::string                   g_strClientPath;
extern ADDON::CHelper_libXBMC_addon *XBMC;
extern CHelper_libXBMC_voip         *VOIP;
