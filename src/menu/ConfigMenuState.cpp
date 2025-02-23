#include <menu/ConfigMenuState.h>
#include <savemng.h>
#include <utils/InputUtils.h>
#include <utils/LanguageUtils.h>
#include <utils/Colors.h>
#include <Metadata.h>
#include <GlobalConfig.h>

static int cursorPos = 0;

static std::string language;

void ConfigMenuState::render() {
    DrawUtils::setFontColor(COLOR_INFO);
    consolePrintPosAligned(0, 4, 1,LanguageUtils::gettext("Configuration Options"));
    DrawUtils::setFontColor(COLOR_TEXT);
    language = LanguageUtils::getLoadedLanguage();
    consolePrintPos(M_OFF, 2, LanguageUtils::gettext("   Language: %s"), language.c_str());

    DrawUtils::setFontColor(COLOR_INFO);
    consolePrintPos(M_OFF + 2, 8,LanguageUtils::gettext("WiiU Serial Id: %s"),Metadata::thisConsoleSerialId.c_str());

    DrawUtils::setFontColor(COLOR_TEXT);
    consolePrintPos(M_OFF, 2 + cursorPos, "\u2192");
    consolePrintPosAligned(17,4,2,LanguageUtils::gettext("\ue045 SaveConfig  \ue001: Back"));
}

ApplicationState::eSubState ConfigMenuState::update(Input *input) {
    if (input->get(TRIGGER, PAD_BUTTON_B))
        return SUBSTATE_RETURN;
    if (input->get(TRIGGER, PAD_BUTTON_RIGHT)) {
        if (language == LanguageUtils::gettext("Japanese"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__German);
        else if (language == LanguageUtils::gettext("German"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__Italian);
        else if (language == LanguageUtils::gettext("Italian"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__Portuguese);
        else if (language == LanguageUtils::gettext("Portuguese"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__Spanish);
        else if (language == LanguageUtils::gettext("Spanish"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__Chinese1);
        else if (language == LanguageUtils::gettext("Traditional Chinese"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__Korean);
        else if (language == LanguageUtils::gettext("Korean"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__Russian);
        else if (language == LanguageUtils::gettext("Russian"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__Chinese2);
        else if (language == LanguageUtils::gettext("Simplified Chinese"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__English);
        else if (language == LanguageUtils::gettext("English"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__Japanese);
    }
    if (input->get(TRIGGER, PAD_BUTTON_LEFT)) {
        if (language == LanguageUtils::gettext("Japanese"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__English);
        else if (language == LanguageUtils::gettext("English"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__German);
        else if (language == LanguageUtils::gettext("German"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__Chinese2);
        else if (language == LanguageUtils::gettext("Simplified Chinese"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__Russian);
        else if (language == LanguageUtils::gettext("Russian"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__Korean);
        else if (language == LanguageUtils::gettext("Korean"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__Chinese1);
        else if (language == LanguageUtils::gettext("Traditional Chinese"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__Spanish);
        else if (language == LanguageUtils::gettext("Spanish"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__Portuguese);
        else if (language == LanguageUtils::gettext("Portuguese"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__Italian);
        else if (language == LanguageUtils::gettext("Italian"))
            LanguageUtils::loadLanguage(Swkbd_LanguageType__Japanese);
    }
    if (input->get(TRIGGER, PAD_BUTTON_PLUS)) {
        GlobalConfig::setLanguage(LanguageUtils::getSwkbdLoadedLang());
        if(GlobalConfig::write())
            promptMessage(COLOR_BG_OK,LanguageUtils::gettext("Configuration saved"));
        else
            promptMessage(COLOR_BG_KO,LanguageUtils::gettext("Error saving configuration"));
        
    }
    return SUBSTATE_RUNNING;
}