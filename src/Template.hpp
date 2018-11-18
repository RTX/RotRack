#include "rack.hpp"

using namespace rack;

extern Plugin *plugin;

extern Model *modelButtons;

struct RotoRackLedButton : SVGSwitch, ToggleSwitch
{
    RotoRackLedButton()
    {
        addFrame(SVG::load(assetPlugin(plugin, "res/ledbutton_off.svg")));
        addFrame(SVG::load(assetPlugin(plugin, "res/ledbutton_on.svg")));
    }
};

