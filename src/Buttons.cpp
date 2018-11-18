#include "Template.hpp"
#include "dsp/digital.hpp"
#include <iostream>
#include <cmath>

struct Buttons: Module {
    enum ParamIds {
       
        RESET_PARAM,
       
        NUM_PARAMS
    };
    enum InputIds {
        NUM_INPUTS
    };
    enum OutputIds {
        CH1_OUTPUT,
       
        NUM_OUTPUTS
    };
    enum LightIds {
        RESET_LIGHT,
       GATES_LIGHT,
        NUM_LIGHTS
    };
    float resetLight = 0.0;
   
    bool lastBtnPress = false;
    bool btnPress = false;
    Buttons() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
    void buttonPress();
    void step() override;
};

struct MedLEDButton : LEDButton {
        MedLEDButton() {
                addFrame(SVG::load(assetPlugin(plugin, "res/MedLEDButton.svg")));
        }
};

template <typename BASE>
struct MedLight : BASE {
        MedLight() {
                this->box.size = mm2px(Vec(10, 10));
        }
};

void Buttons::buttonPress() {
    if(btnPress){
        resetLight = 1.0;
        }
    else{
        resetLight = 0.0;
        }

};

struct ButtonsWidget: ModuleWidget {
    ButtonsWidget(Buttons *module);
};


void Buttons::step() {

    const float lightLambda = 0.075;
    float output = 0.0;
   

    // Reset
    if (params[RESET_PARAM].value > 0  ) {
        btnPress = !btnPress;
        buttonPress();
        printf("Hello");
    }
    

    resetLight -= resetLight / lightLambda / engineGetSampleRate();
    

    outputs[CH1_OUTPUT].value = output;
  

    lights[RESET_LIGHT].value = resetLight;
    

}


ButtonsWidget::ButtonsWidget(Buttons *module) : ModuleWidget(module) {
    box.size = Vec(15*10, 380);

    {
        SVGPanel *panel = new SVGPanel();
        panel->box.size = box.size;
        panel->setBackground(SVG::load(assetPlugin(plugin, "res/Buttons.svg")));
        addChild(panel);
    }

    addChild(Widget::create<ScrewSilver>(Vec(15, 0)));
    addChild(Widget::create<ScrewSilver>(Vec(box.size.x-30, 0)));
    addChild(Widget::create<ScrewSilver>(Vec(15, 365)));
    addChild(Widget::create<ScrewSilver>(Vec(box.size.x-30, 365)));


    addOutput(Port::create<PJ301MPort>(Vec(24, 223), Port::OUTPUT, module, Buttons::CH1_OUTPUT));
  

    ParamWidget *testBtn = ParamWidget::create<LEDButton>(Vec(99, 61-1), module, Buttons::RESET_PARAM, 0.0f, 1.0f, 0.0f);
    addParam(testBtn);
   
	addChild(ModuleLightWidget::create<MediumLight<GreenLight>>(Vec(103.4f, 64.4f), module, Buttons::RESET_LIGHT));

     addParam(ParamWidget::create<RotoRackLedButton>(Vec(140.0, 185.5), module, 1000 , 0.0, 1.0, 1.0));


   
}

Model *modelButtons = Model::create<Buttons, ButtonsWidget>("RotoRack", "Buttons", "[LIVE] Buttons", UTILITY_TAG);

