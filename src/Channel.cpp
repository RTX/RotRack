#include "Template.hpp"
#define nCHANNELS 8
#define CV_MAX (10.0f)
#define AUDIO_MAX (6.0f)
#define VOCT_MAX (6.0f)
#define AMP_MAX (2.0f)


struct Channel : Module 
{
	enum ParamIds 
    {
        PARAM_MASTER_LEVEL,
        ENUMS(PARAM_SEND_LEVEL_1_, 8),
        ENUMS(PARAM_SEND_LEVEL_2_, 8),
        ENUMS(PARAM_SEND_LEVEL_3_, 8),

        ENUMS(PARAM_CHANNEL_LEVEL, 8),

        ENUMS(PARAM_CHANNEL_BALANCE, 8),

        ENUMS(PARAM_SEND_BALANCE, 3),
        ENUMS(PARAM_SEND_LEVEL, 3),

        ENUMS(PARAM_EQ_HI_CHANNEL, 8),
        ENUMS(PARAM_EQ_MID_CHANNEL, 8),
        ENUMS(PARAM_EQ_LOW_CHANNEL, 8),


        nPARAMS
    };

	enum InputIds 
    {
        ENUMS(INPUT_CHANNEL_L, 8),
        ENUMS(INPUT_CHANNEL_R, 8) ,   

        ENUMS(CV_CHANNEL_LEVEL, 8),
        ENUMS(CV_CHANNEL_PAN, 8),

        ENUMS(CV_CHANNEL_SEND_LEVEL_1_, 8),
        ENUMS(CV_CHANNEL_SEND_LEVEL_2_, 8),
        ENUMS(CV_CHANNEL_SEND_LEVEL_3_, 8),

        ENUMS(INPUT_CHANNEL_SEND_L, 3),
        ENUMS(INPUT_CHANNEL_SEND_R, 3) ,   

        ENUMS(CV_SEND_BALANCE, 3),
        ENUMS(CV_SEND_LEVEL, 3),       

        INPUT_THRU_L,
        INPUT_THRU_R,

        nINPUTS
	};

	enum OutputIds 
    {
        OUTPUT_MASTER_L,
        OUTPUT_MASTER_R,   
        ENUMS(OUTPUT_SEND_L, 3),
        ENUMS(OUTPUT_SEND_R, 3),
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

      // LED Meters
    LEDMeterWidget  *m_pLEDMeterChannel[ nCHANNELS ][ 2 ] ={};
    LEDMeterWidget  *m_pLEDMeterMain[ 2 ] ={};

    
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
  
  
    float lvl_l = 0.0f;
    float lvl_r = 0.0f;
  
    for (int i =0 ; i < 8; i++)
    {               
        lvl_l +=   (inputs[ INPUT_CHANNEL_L + i].value   * params[ PARAM_CHANNEL_LEVEL+ i ].value  * PanL(params[PARAM_CHANNEL_BALANCE + i].value)) ;

        lvl_l +=  (inputs[INPUT_CHANNEL_L +i].value * params[ PARAM_CHANNEL_LEVEL + i].value) * PanL(params[PARAM_CHANNEL_BALANCE + i].value) ;
        lvl_r +=  (inputs[INPUT_CHANNEL_L +i].value * params[ PARAM_CHANNEL_LEVEL  + i].value) * PanR(params[PARAM_CHANNEL_BALANCE + i].value);
    }


    lvl_l = clamp( lvl_l * params[ PARAM_MASTER_LEVEL ].value, -AUDIO_MAX, AUDIO_MAX );
    lvl_r = clamp( lvl_r * params[ PARAM_MASTER_LEVEL ].value, -AUDIO_MAX, AUDIO_MAX );

    outputs[ OUTPUT_MASTER_L].value = lvl_l;
    outputs[ OUTPUT_MASTER_R].value = lvl_r;


   
      //  lvl_l +=   (inputs[ INPUT_CHANNEL_L + i].value   * params[ PARAM_CHANNEL_LEVEL+ i ].value  * PanL(params[PARAM_CHANNEL_BALANCE + i].value)) / i;
   
  // if(INPUT_CHANNEL_R1.active)
  // {
   // outputs[ OUTPUT_MASTER_R].value =   inputs[ INPUT_CHANNEL_R +1].value   * params[ PARAM_CHANNEL_LEVEL+1 ].value * PanR(params[PARAM_CHANNEL_BALANCE + 1].value);
  // }
  // else{
       // lvl_r +=   (inputs[ INPUT_CHANNEL_L+ i].value   * params[ PARAM_CHANNEL_LEVEL+ i ].value * PanR(params[PARAM_CHANNEL_BALANCE + i].value) ) / i;

  //}
    
     

   /*
    outputs[ OUT_SND1_L  ].value =   inputs[ IN].value   * params[ PARAM_LEVEL ].value * PanL(params[PARAM_BALANCE].value)  *  params[ PARAM_SEND1_LEVEL ].value;
    outputs[ OUT_SND1_R  ].value =   inputs[ IN].value   * params[ PARAM_LEVEL ].value  * PanR(params[PARAM_BALANCE].value) *  params[ PARAM_SEND1_LEVEL ].value;

     if(inputs[IN_THRU].value != 0 )
     {
        // outputs[ OUT_L].value += inputs[IN_THRU].value;    
     }   
    */

    
}

struct Channel_Widget : ModuleWidget {
	Channel_Widget( Channel *module );
};

Channel_Widget::Channel_Widget( Channel *module ) : ModuleWidget(module) 
{
    

	box.size = Vec( 15*55, 380);
	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/compmix8_strip.svg")));
		addChild(panel);
	}



	addChild(Widget::create<ScrewSilver>(Vec(15, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x -15, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(15, 365))); 
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x -15, 365)));

    for (int i =0 ; i < 8; i++)
    {
        int xPosition = 30 * i;
        // in L/R
        addInput(Port::create<as_PJ301MPort>(Vec(44 + xPosition, 348 ), Port::INPUT, module, Channel::INPUT_CHANNEL_L + i));
        addInput(Port::create<as_PJ301MPort>(Vec(44 + xPosition, 328 ), Port::INPUT, module, Channel::INPUT_CHANNEL_R + i));
        // Level CV
        addInput(Port::create<as_PJ301MPort>(Vec(44 + xPosition, 308 ), Port::INPUT, module, Channel::CV_CHANNEL_LEVEL + i));
        // Balance / Pan
        addParam(ParamWidget::create<as_Knob>(Vec(44 + xPosition, 217), module, Channel::PARAM_CHANNEL_BALANCE + i, -1.0f, 1.0f, 0.0f));
        // Pan CV
        addInput(Port::create<as_PJ301MPort>(Vec(44 + xPosition, 195 ), Port::INPUT, module, Channel::CV_CHANNEL_PAN + i));
        // EQ
        addParam(ParamWidget::create<as_Knob>(Vec(44 + xPosition, 177), module, Channel::PARAM_EQ_LOW_CHANNEL + i, -1.0f, 1.0f, 0.0f));
        addParam(ParamWidget::create<as_Knob>(Vec(44 + xPosition, 159), module, Channel::PARAM_EQ_MID_CHANNEL + i, -1.0f, 1.0f, 0.0f));
        addParam(ParamWidget::create<as_Knob>(Vec(44 + xPosition, 141), module, Channel::PARAM_EQ_HI_CHANNEL + i, -1.0f, 1.0f, 0.0f));
        // SEND s
        addInput(Port::create<as_PJ301MPort>(Vec(44 + xPosition, 119 ), Port::INPUT, module, Channel::CV_CHANNEL_SEND_LEVEL_3_ + i));
        addParam(ParamWidget::create<as_Knob>(Vec(44 + xPosition, 101), module, Channel::PARAM_SEND_LEVEL_3_ + i, -1.0f, 1.0f, 0.0f));

        addInput(Port::create<as_PJ301MPort>(Vec(44 + xPosition, 82 ), Port::INPUT, module, Channel::CV_CHANNEL_SEND_LEVEL_2_ + i));
        addParam(ParamWidget::create<as_Knob>(Vec(44 + xPosition, 64), module, Channel::PARAM_SEND_LEVEL_2_ + i, -1.0f, 1.0f, 0.0f));

        addInput(Port::create<as_PJ301MPort>(Vec(44 + xPosition, 45 ), Port::INPUT, module, Channel::CV_CHANNEL_SEND_LEVEL_2_ + i));
        addParam(ParamWidget::create<as_Knob>(Vec(44 + xPosition, 27), module, Channel::PARAM_SEND_LEVEL_2_ + i, -1.0f, 1.0f, 0.0f));

        // Meters         
        module->m_pLEDMeterMain[ 0 ] = new LEDMeterWidget( 48 + xPosition, 239, 2, 3, 2, true );
        addChild( module->m_pLEDMeterMain[ 0 ] );

        module->m_pLEDMeterMain[ 0 ] = new LEDMeterWidget( 54 + xPosition, 239, 2, 3, 2, true );
        addChild( module->m_pLEDMeterMain[ 0 ] );

        // Volume Faders 
        addChild(ParamWidget::create<as_FaderPot>(Vec(36 + xPosition, 239), module, Channel::PARAM_CHANNEL_LEVEL + i, 0.0f, 1.0f, 0.0f));


        //Output Master 
        addOutput(Port::create<as_PJ301MPort>(Vec(430, 348), Port::OUTPUT, module, Channel::OUTPUT_MASTER_L));
        addOutput(Port::create<as_PJ301MPort>(Vec(450, 348), Port::OUTPUT, module, Channel::OUTPUT_MASTER_R));

         //Input Thru   
     //   addInput(Port::create<as_PJ301MPort>(Vec(430 , 328 ), Port::INPUT, module, Channel::INPUT_THRU_L ));
       // addInput(Port::create<as_PJ301MPort>(Vec(450 , 328 ), Port::INPUT, module, Channel::INPUT_THRU_R ));

        addInput(Port::create<as_PJ301MPort>(Vec(430, 328), Port::INPUT, module, Channel::INPUT_THRU_L));
        addInput(Port::create<as_PJ301MPort>(Vec(450, 328), Port::INPUT, module, Channel::INPUT_THRU_R));

    
    }


 // Meters         
        module->m_pLEDMeterMain[ 0 ] = new LEDMeterWidget( 429, 239, 2, 3, 2, true );
        addChild( module->m_pLEDMeterMain[ 0 ] );

        module->m_pLEDMeterMain[ 0 ] = new LEDMeterWidget( 433, 239, 2, 3, 2, true );
        addChild( module->m_pLEDMeterMain[ 0 ] );

        // Volume Faders 
        addChild(ParamWidget::create<as_FaderPot>(Vec(420, 239), module, Channel::PARAM_MASTER_LEVEL, 0.0f, 1.0f, 0.0f));

    /*
    


   
   
    //addInput(Port::create<as_PJ301MPort>(Vec(5, 320), Port::INPUT, module, Channel::IN_THRU));

    addOutput(Port::create<as_PJ301MPort>(Vec(5, 700), Port::OUTPUT, module, Channel::OUT_SND1_L ));
    addOutput(Port::create<as_PJ301MPort>(Vec(35, 700), Port::OUTPUT, module, Channel::OUT_SND1_R ));

    

	addOutput(Port::create<as_PJ301MPort>(Vec(4, 700), Port::OUTPUT, module, Channel::OUT_L));
	addOutput(Port::create<as_PJ301MPort>(Vec(36, 700), Port::OUTPUT, module, Channel::OUT_R));



    //	addOutput(Port::create<as_PJ301MPort>(Vec(20, 70), Port::OUTPUT, module, Channel::TEST));



	//addOutput(Port::create<as_PJ301MPort>(Vec(20, 160]), Port::OUTPUT, module, Channel::OUT_R));
    */

}

void Channel::onReset(){}

void Channel::onRandomize(){}

Model *modelChannel = Model::create<Channel, Channel_Widget>( "RotRack", "Channel", "Single Channel", MIXER_TAG, MULTIPLE_TAG );






