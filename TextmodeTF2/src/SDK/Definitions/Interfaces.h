#pragma once

#include "../../Utils/Feature/Feature.h"
#include "Interfaces/IMaterialSystem.h"
#include "Interfaces/IMDLCache.h"
#include "Interfaces/IStudioRender.h"
#include "Interfaces/IVideoServices.h"
#include "Interfaces/IPhysics.h"

MAKE_INTERFACE_VERSION(IMDLCache, MDLCache, "datacache.dll", "MDLCache004");
MAKE_INTERFACE_VERSION(IStudioRender, StudioRender, "studiorender.dll", "VStudioRender025");
MAKE_INTERFACE_VERSION(IVideoServices, VideoServices, "video_services.dll", "IVideoServices002");
MAKE_INTERFACE_VERSION(IPhysics, Physics, "vphysics.dll", "VPhysics031");