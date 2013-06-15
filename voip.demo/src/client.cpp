#include "client.h"
#include "xbmc_voip_dll.h"
#include "StdString.h"

using namespace std;
using namespace ADDON;

#ifdef TARGET_WINDOWS
#define snprintf _snprintf
#endif

bool           m_bCreated       = false;
ADDON_STATUS   m_CurStatus      = ADDON_STATUS_UNKNOWN;
bool           m_bIsPlaying     = false;

/* User adjustable settings are saved here.
 * Default values are defined inside client.h
 * and exported to the other source files.
 */
std::string g_strUserPath             = "";
std::string g_strClientPath           = "";

CHelper_libXBMC_addon *XBMC           = NULL;
CHelper_libXBMC_voip  *VOIP           = NULL;

extern "C" {

void ADDON_ReadSettings(void)
{
  //STUB
}

ADDON_STATUS ADDON_Create(void* hdl, void* props)
{
  if (!hdl || !props)
    return ADDON_STATUS_UNKNOWN;

  VOIP_PROPERTIES* voipprops = (VOIP_PROPERTIES*)props;

  XBMC = new CHelper_libXBMC_addon;
  if (!XBMC->RegisterMe(hdl))
  {
    SAFE_DELETE(XBMC);
    return ADDON_STATUS_PERMANENT_FAILURE;
  }

  VOIP = new CHelper_libXBMC_voip;
  if (!VOIP->RegisterMe(hdl))
  {
    SAFE_DELETE(VOIP);
    SAFE_DELETE(XBMC);
    return ADDON_STATUS_PERMANENT_FAILURE;
  }

  XBMC->Log(LOG_DEBUG, "%s - Creating the VOIP demo add-on", __FUNCTION__);

  m_CurStatus     = ADDON_STATUS_UNKNOWN;
  g_strUserPath   = voipprops->strUserPath;
  g_strClientPath = voipprops->strClientPath;

  ADDON_ReadSettings();

  m_CurStatus = ADDON_STATUS_OK;
  m_bCreated = true;
  return m_CurStatus;
}

ADDON_STATUS ADDON_GetStatus()
{
  return m_CurStatus;
}

void ADDON_Destroy()
{
  m_bCreated = false;
  m_CurStatus = ADDON_STATUS_UNKNOWN;
}

bool ADDON_HasSettings()
{
  return true;
}

unsigned int ADDON_GetSettings(ADDON_StructSetting ***sSet)
{
  return 0;
}

ADDON_STATUS ADDON_SetSetting(const char *settingName, const void *settingValue)
{
  return ADDON_STATUS_OK;
}

void ADDON_Stop()
{
}

void ADDON_FreeSettings()
{
}

void ADDON_Announce(const char *flag, const char *sender, const char *message, const void *data)
{
}


const char* GetVOIPAPIVersion(void)
{
  static const char *strApiVersion = XBMC_VOIP_API_VERSION;
  return strApiVersion;
}

const char* GetMininumVOIPAPIVersion(void)
{
  static const char *strMinApiVersion = XBMC_VOIP_MIN_API_VERSION;
  return strMinApiVersion;
}

const char* GetGUIAPIVersion(void)
{
  static const char *strGuiApiVersion = "1.0.0";
  return strGuiApiVersion;
}

const char* GetMininumGUIAPIVersion(void)
{
  static const char *strMinGuiApiVersion = "1.0.0";
  return strMinGuiApiVersion;
}

VOIP_ERROR GetAddonCapabilities(VOIP_ADDON_CAPABILITIES* pCapabilities)
{
  pCapabilities->bSupportsVideo = false;
  pCapabilities->bSupportsVoice = true;
  

  return VOIP_ERROR_NO_ERROR;
}

const char *GetBackendName(void)
{
  static const char *strBackendName = "demo voip add-on";
  return strBackendName;
}

const char *GetBackendVersion(void)
{
  static CStdString strBackendVersion = "0.1";
  return strBackendVersion.c_str();
}


int GetNumberOfContacts(void)
{
  return 99;
}


VOIP_CONTACT *GetContactById(int)
{
  VOIP_CONTACT * pNewContact = new VOIP_CONTACT;
  pNewContact->strContactNew = "Amit";
  
  return pNewContact;
}

VOIP_ERROR GetContact(VOIP_CONTACT& contact, int contact_id)
{
	return VOIP_ERROR_NOT_IMPLEMENTED;
}

VOIP_ERROR CallMenuHook(const VOIP_MENUHOOK &menuhook) { return VOIP_ERROR_NOT_IMPLEMENTED; }
}
