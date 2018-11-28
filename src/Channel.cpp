#include "Template.hpp"


struct Channel : Module 
{
	enum ParamIds 
    {
        PARAM_SEND1_LEVEL,
       
        PARAM_LEVEL,
        PARAM_BALANCE,
        nPARAMS
    };

	enum InputIds 
    {
        IN,
        IN_THRU,
        nINPUTS
	};

	enum OutputIds 
    {
        OUT_L,
        OUT_R,               
        OUT_SND1_L,
        OUT_SND1_R,
        TEST,
        nOUTPUTS   
	};

   // CLog            lg;

    // Contructor
	Channel() : Module(nPARAMS, nINPUTS, nOUTPUTS){}

    // Overrides 
	void    step() override;
    //json_t* toJson() override;
    //void    fromJson(json_t *rootJ) override;
    void    onRandomize() override;
    void    onReset() override;
    
};



//PAN LEVEL
	float PanL(float balance) //, float cv) 
    { // -1...+1
		float p, inp;
		inp = balance ; //+ cv / 5;
		p = M_PI * (clamp(inp, -1.0f, 1.0f) + 1) / 4;
		return ::cos(p);
	}

	float PanR(float balance )//, float cv) 
    { // -1...+1
		float p, inp;
		inp = balance ; //+ cv / 5;
		p = M_PI * (clamp(inp, -1.0f, 1.0f) + 1) / 4;
		return ::sin(p);
	}

void Channel::step() 
{
    outputs[TEST].value = params[PARAM_SEND1_LEVEL].value;
  


    outputs[ OUT_L].value =   inputs[ IN].value   * params[ PARAM_LEVEL ].value  * PanL(params[PARAM_BALANCE].value);
   
    outputs[ OUT_R].value =   inputs[ IN].value   * params[ PARAM_LEVEL ].value * PanR(params[PARAM_BALANCE].value);

    outputs[ OUT_SND1_L  ].value =   inputs[ IN].value   * params[ PARAM_LEVEL ].value * PanL(params[PARAM_BALANCE].value)  *  params[ PARAM_SEND1_LEVEL ].value;
    outputs[ OUT_SND1_R  ].value =   inputs[ IN].value   * params[ PARAM_LEVEL ].value  * PanR(params[PARAM_BALANCE].value) *  params[ PARAM_SEND1_LEVEL ].value;

     if(inputs[IN_THRU].value != 0 )
     {
        // outputs[ OUT_L].value += inputs[IN_THRU].value;    
     }   
    

    
}

struct Channel_Widget : ModuleWidget {
	Channel_Widget( Channel *module );
};

Channel_Widget::Channel_Widget( Channel *module ) : ModuleWidget(module) 
{
    

	box.size = Vec( 15*4, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/rtxblank.svg")));
		addChild(panel);
	}

    //module->lg.Open("XFade.txt");

	addChild(Widget::create<ScrewSilver>(Vec(5, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x-5, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(5, 365))); 
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x-5, 365)));


    addParam(ParamWidget::create<RoundBlackKnob>(Vec(15, 140), module, Channel::PARAM_SEND1_LEVEL, 0.0f, 1.0f, 0.0f));

    addParam(ParamWidget::create<RoundBlackKnob>(Vec(15, 180), module, Channel::PARAM_BALANCE, -1.0f, 1.0f, 0.0f));
    addParam(ParamWidget::create<as_FaderPot>(Vec(15, 210), module, Channel::PARAM_LEVEL, 0.0f, 1.0f, 0.0f));
	addInput(Port::create<as_PJ301MPort>(Vec(15, 340), Port::INPUT, module, Channel::IN));
    //addInput(Port::create<as_PJ301MPort>(Vec(5, 320), Port::INPUT, module, Channel::IN_THRU));

    addOutput(Port::create<as_PJ301MPort>(Vec(5, 80), Port::OUTPUT, module, Channel::OUT_SND1_L ));
    addOutput(Port::create<as_PJ301MPort>(Vec(35, 80), Port::OUTPUT, module, Channel::OUT_SND1_R ));

    

	addOutput(Port::create<as_PJ301MPort>(Vec(4, 20), Port::OUTPUT, module, Channel::OUT_L));
	addOutput(Port::create<as_PJ301MPort>(Vec(36, 20), Port::OUTPUT, module, Channel::OUT_R));



    //	addOutput(Port::create<as_PJ301MPort>(Vec(20, 70), Port::OUTPUT, module, Channel::TEST));



	//addOutput(Port::create<as_PJ301MPort>(Vec(20, 160]), Port::OUTPUT, module, Channel::OUT_R));


}

void Channel::onReset(){}

void Channel::onRandomize(){}

Model *modelChannel = Model::create<Channel, Channel_Widget>( "RotRack", "Channel", "Single Channel", MIXER_TAG, MULTIPLE_TAG );






