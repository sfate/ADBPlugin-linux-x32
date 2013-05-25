#include "adb_wrapper.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PLUGIN_NAME        "ADB"
#define PLUGIN_DESCRIPTION PLUGIN_NAME " Wrapper for Google Chrome"
#define PLUGIN_VERSION     "0.0.1"

static NPNetscapeFuncs* sBrowserFuncs = NULL;

NPError NP_Initialize(NPNetscapeFuncs* bFuncs, NPPluginFuncs* pFuncs) {
  sBrowserFuncs = bFuncs;

  if (pFuncs->size < (offsetof(NPPluginFuncs, setvalue) + sizeof(void*)))
    return NPERR_INVALID_FUNCTABLE_ERROR;

  return NP_GetEntryPoints(pFuncs);
}

NPError NP_GetEntryPoints(NPPluginFuncs *pFuncs) {
  pFuncs->newp = NPP_New;
  pFuncs->destroy = NPP_Destroy;
  pFuncs->setwindow = NPP_SetWindow;
  pFuncs->newstream = NPP_NewStream;
  pFuncs->destroystream = NPP_DestroyStream;
  pFuncs->asfile = NPP_StreamAsFile;
  pFuncs->writeready = NPP_WriteReady;
  pFuncs->write = NPP_Write;
  pFuncs->print = NPP_Print;
  pFuncs->event = NPP_HandleEvent;
  pFuncs->urlnotify = NPP_URLNotify;
  pFuncs->getvalue = NPP_GetValue;
  pFuncs->setvalue = NPP_SetValue;

  return NPERR_NO_ERROR;
}

char* NP_GetPluginVersion() {
  return PLUGIN_VERSION;
}

const char* NP_GetMIMEDescription() {
  return "application/adb_wrapper:adb:ADB Wrapper";
}

NPError NP_GetValue(void* future, NPPVariable aVariable, void* aValue) {
  switch (aVariable) {
    case NPPVpluginNameString:
      *((char**)aValue) = PLUGIN_NAME;
      break;
    case NPPVpluginDescriptionString:
      *((char**)aValue) = PLUGIN_DESCRIPTION;
      break;
    default:
      return NPERR_INVALID_PARAM;
      break;
  }
  return NPERR_NO_ERROR;
}

NPError NP_Shutdown() {
  return NPERR_NO_ERROR;
}

NPError NPP_New(NPMIMEType pluginType, NPP instance, uint16_t mode, int16_t argc, char* argn[], char* argv[], NPSavedData* saved) {
  // Make sure we can render this plugin
  NPBool browserSupportsWindowless = false;
  sBrowserFuncs->getvalue(instance, NPNVSupportsWindowless, &browserSupportsWindowless);
  if (!browserSupportsWindowless) {
    printf("Windowless mode not supported by the browser\n");
    return NPERR_GENERIC_ERROR;
  }

  sBrowserFuncs->setvalue(instance, NPPVpluginWindowBool, (void*)false);

  PluginInstance* instanceData = (PluginInstance*) malloc(sizeof(PluginInstance));
  if (!instanceData)
    return NPERR_OUT_OF_MEMORY_ERROR;

  memset(instanceData, 0, sizeof(PluginInstance));
  instanceData->npp = instance;
  instance->pdata = instanceData;

  return NPERR_NO_ERROR;
}

NPError NPP_Destroy(NPP instance, NPSavedData** save) {
  PluginInstance* instanceData = (PluginInstance*) (instance->pdata);
  free(instanceData);

  return NPERR_NO_ERROR;
}

NPError NPP_NewStream(NPP instance, NPMIMEType type, NPStream* stream, NPBool seekable, uint16_t* stype) {
  return NPERR_GENERIC_ERROR;
}

NPError NPP_DestroyStream(NPP instance, NPStream* stream, NPReason reason) {
  return NPERR_GENERIC_ERROR;
}

int32_t NPP_WriteReady(NPP instance, NPStream* stream) {
  return 0;
}

int32_t NPP_Write(NPP instance, NPStream* stream, int32_t offset, int32_t len, void* buffer) {
  return 0;
}

void NPP_StreamAsFile(NPP instance, NPStream* stream, const char* fname) {

}

void NPP_Print(NPP instance, NPPrint* platformPrint) {

}

int16_t NPP_HandleEvent(NPP instance, void* event) {
  return 1;
}

void NPP_URLNotify(NPP instance, const char* URL, NPReason reason, void* notifyData) {

}

NPError NPP_GetValue(NPP instance, NPPVariable variable, void *value) {
  return NPERR_GENERIC_ERROR;
}

NPError NPP_SetValue(NPP instance, NPNVariable variable, void *value) {
  return NPERR_GENERIC_ERROR;
}

