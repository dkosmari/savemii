#include <utils/StateUtils.h>
#include <utils/DrawUtils.h>
#include <coreinit/core.h>
#include <coreinit/dynload.h>
#include <coreinit/foreground.h>
#include <proc_ui/procui.h>
#include <whb/proc.h>

#include <string.h>


bool State::aroma = false;

void State::init() {
    OSDynLoad_Module mod;
    aroma = OSDynLoad_Acquire("homebrew_kernel", &mod) == OS_DYNLOAD_OK;
    if (aroma) {
        OSDynLoad_Release(mod);
        ProcUIInit(&OSSavesDone_ReadyToRelease);
        OSEnableHomeButtonMenu(true);
    } else
        WHBProcInit();
}

uint32_t
State::ConsoleProcCallbackAcquired(void * /*context*/)
{
    return DrawUtils::initScreen();
}

uint32_t
State::ConsoleProcCallbackReleased(void * /*context*/)
{
    return DrawUtils::deinitScreen();
}

void State::registerProcUICallbacks() {
    if (aroma) {
        ProcUIRegisterCallback(PROCUI_CALLBACK_ACQUIRE, ConsoleProcCallbackAcquired, NULL, 100);
        ProcUIRegisterCallback(PROCUI_CALLBACK_RELEASE, ConsoleProcCallbackReleased, NULL, 100);
    }
}

bool State::AppRunning() {
    if (aroma) {
        bool app = true;
        if (OSIsMainCore()) {
            switch (ProcUIProcessMessages(true)) {
                case PROCUI_STATUS_EXITING:
                    // Being closed, prepare to exit
                    app = false;
                    break;
                case PROCUI_STATUS_RELEASE_FOREGROUND:
                    // Free up MEM1 to next foreground app, deinit screen, etc.
                    ProcUIDrawDoneRelease();
                    break;
                case PROCUI_STATUS_IN_FOREGROUND:
                    // Executed while app is in foreground
                    app = true;
                    break;
                case PROCUI_STATUS_IN_BACKGROUND:
                    OSSleepTicks(OSMillisecondsToTicks(20));
                    break;
            }
        }

        return app;
    }
    return WHBProcIsRunning();
}

void State::shutdown() {
    if (!aroma)
        WHBProcShutdown();
    ProcUIShutdown();
}


