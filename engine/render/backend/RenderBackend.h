#pragma once

#if defined(CHIRA_USE_RENDER_BACKEND_GL)
    #include "api/BackendGL.h"
#elif defined(CHIRA_USE_RENDER_BACKEND_VK)
    #include "api/BackendVK.h"
#else
    #error "No render backend present!"
#endif
