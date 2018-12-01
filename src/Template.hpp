#include "rack.hpp"




#define ENUMS(name, count) name, name ## _LAST = name + (count) - 1


using namespace rack;

extern Plugin *plugin;


extern Model *modelChannel;


struct SmallKnob : RoundKnob {
	SmallKnob() {
		setSVG(SVG::load(assetPlugin(plugin,"res/Knob_28.svg")));
	}
};


struct RotoRackLedButton : SVGSwitch, ToggleSwitch
{
    RotoRackLedButton()
    {
        addFrame(SVG::load(assetPlugin(plugin, "res/ledbutton_off.svg")));
        addFrame(SVG::load(assetPlugin(plugin, "res/ledbutton_on.svg")));
    }
};

struct as_HexScrew : SVGScrew {
	as_HexScrew() {
		sw->svg = SVG::load(assetPlugin(plugin, "res/as-hexscrew.svg"));
		sw->wrap();
		box.size = sw->box.size;
	}
};

struct as_Knob : SVGKnob {
	as_Knob() {
        minAngle = -0.83 * M_PI;
		maxAngle = 0.83 * M_PI;
		setSVG( SVG::load(assetPlugin(plugin, "res/mx8/mx8_Knob_darkblue.svg")) );
	}
};
struct as_KnobBlack : SVGKnob {
	as_KnobBlack() {
        minAngle = -0.83 * M_PI;
		maxAngle = 0.83 * M_PI;
		setSVG( SVG::load(assetPlugin(plugin, "res/as-knobBlack.svg")) );
	}
};

struct as_KnobBlackSnap : as_KnobBlack {
	as_KnobBlackSnap() {
		snap = true;
	}
};

struct as_KnobBlackSnap4 : as_KnobBlack {
	as_KnobBlackSnap4() {
		minAngle = -0.30 * M_PI;
		maxAngle = 0.30 * M_PI;
		snap = true;
	}
};





struct as_FxKnobWhite : SVGKnob {
	as_FxKnobWhite() {
        minAngle = -0.83 * M_PI;
		maxAngle = 0.83 * M_PI;
		setSVG( SVG::load(assetPlugin(plugin, "res/rosmallknob.svg")) );
	}
};
struct as_FxKnobBlack : SVGKnob {
	as_FxKnobBlack() {
        minAngle = -0.83 * M_PI;
		maxAngle = 0.83 * M_PI;
		setSVG( SVG::load(assetPlugin(plugin, "res/as-FxKnobBlack.svg")) );
	}
};

struct BigLEDBezel : SVGSwitch, MomentarySwitch {
        BigLEDBezel() {
                addFrame(SVG::load(assetPlugin(plugin, "res/as_bigLEDBezel.svg")));
        }
};

struct as_CKSS : SVGSwitch, ToggleSwitch {
	as_CKSS() {
		addFrame(SVG::load(assetPlugin(plugin,"res/as_CKSS_0.svg")));
		addFrame(SVG::load(assetPlugin(plugin,"res/as_CKSS_1.svg")));
	}
};

struct as_CKSSH : SVGSwitch, ToggleSwitch {
	as_CKSSH() {
		addFrame(SVG::load(assetPlugin(plugin, "res/as_CKSSH_0.svg")));
		addFrame(SVG::load(assetPlugin(plugin, "res/as_CKSSH_1.svg")));
		sw->wrap();
		box.size = sw->box.size;
	}
};

struct as_CKSSThree : SVGSwitch, ToggleSwitch {
	as_CKSSThree() {
		addFrame(SVG::load(assetPlugin(plugin,"res/as_CKSSThree_2.svg")));
		addFrame(SVG::load(assetPlugin(plugin,"res/as_CKSSThree_1.svg")));
		addFrame(SVG::load(assetPlugin(plugin,"res/as_CKSSThree_0.svg")));
	}
};

struct as_MuteBtn : SVGSwitch, ToggleSwitch {
	as_MuteBtn() {
		addFrame(SVG::load(assetPlugin(plugin,"res/as_mute-off.svg")));
		addFrame(SVG::load(assetPlugin(plugin,"res/as_mute-on.svg")));
	}
};

struct as_SoloBtn : SVGSwitch, ToggleSwitch {
	as_SoloBtn() {
		addFrame(SVG::load(assetPlugin(plugin,"res/as_solo-off.svg")));
		addFrame(SVG::load(assetPlugin(plugin,"res/as_solo-on.svg")));
	}
};

template <typename BASE>
struct GiantLight : BASE {
        GiantLight() {
                this->box.size = mm2px(Vec(18.0, 18.0));
        }
};

template <typename BASE>
 struct MeterLight : BASE {
 	MeterLight() {
 		this->box.size = Vec(8, 8);
		 this->bgColor = nvgRGB(0x14, 0x14, 0x14);
 	}
 };

 template <typename BASE>
 struct DisplayLedLight : BASE {
 	DisplayLedLight() {
 		this->box.size = mm2px(Vec(2.0, 2.0));
		 this->bgColor = nvgRGB(0x14, 0x14, 0x14);
 	}
 };
 struct OrangeLight : GrayModuleLightWidget {
	OrangeLight() {
		addBaseColor(COLOR_ORANGE);
	}
};

template <typename BASE>
struct LedLight : BASE {
	LedLight() {
	  //this->box.size = Vec(20.0, 20.0);
	  this->box.size = mm2px(Vec(6.0, 6.0));
	}
};

/** Reads two adjacent lightIds, so `lightId` and `lightId + 1` must be defined */
struct YellowRedLight : GrayModuleLightWidget {
	YellowRedLight() {
		addBaseColor(COLOR_YELLOW);
		addBaseColor(COLOR_RED);
	}
};

struct as_PJ301MPort : SVGPort {
	as_PJ301MPort() {
		
		setSVG(SVG::load(assetPlugin(plugin,"res/mx8/mx8_jack_off.svg")));
		//background->svg = SVG::load(assetPlugin(plugin,"res/as-PJ301M.svg"));
		//background->wrap();
		//box.size = background->box.size; 
	}
};

struct as_SlidePot : SVGFader {
	as_SlidePot() {
		Vec margin = Vec(4, 4);
		maxHandlePos = Vec(-1.5, -8).plus(margin);
		minHandlePos = Vec(-1.5, 87).plus(margin);
		background->svg = SVG::load(assetPlugin(plugin,"res/as-SlidePot.svg"));
		background->wrap();
		background->box.pos = margin;
		box.size = background->box.size.plus(margin.mult(2));
		handle->svg = SVG::load(assetPlugin(plugin,"res/as-SlidePotHandle.svg"));
		handle->wrap();
	}
};

struct as_FaderPot : SVGFader {
	as_FaderPot() {
		Vec margin = Vec(4, 2);
		maxHandlePos = Vec(2,-3).plus(margin);
		minHandlePos = Vec(2, 55).plus(margin);
		background->svg = SVG::load(assetPlugin(plugin,"res/mx8/mx8_Fader_bg.svg"));
		background->wrap();
		background->box.pos = margin;
		box.size = background->box.size.plus(margin.mult(4));
		handle->svg = SVG::load(assetPlugin(plugin,"res/mx8/mx8_Fader_knog.svg"));
		handle->wrap();
	}
};


#pragma once

#define PI 3.14159f
#define DEG2RAD( x ) ( ( x ) * ( PI / 180.0f ) )
#define RAD2DEG( x ) ( ( x ) * ( 180.0f / PI ) )

struct CyanValueLight : ModuleLightWidget 
{
	CyanValueLight() 
    {
		addBaseColor( COLOR_CYAN );
    }
};

struct OrangeValueLight : ModuleLightWidget 
{
	OrangeValueLight() 
    {
		addBaseColor( nvgRGB( 242, 79, 0 ) );
	}
};

struct DarkRedValueLight : ModuleLightWidget 
{
	DarkRedValueLight() 
    {
		addBaseColor( nvgRGB(0x70, 0, 0x30) );
	}
};

struct DarkGreenValueLight : ModuleLightWidget 
{
	DarkGreenValueLight() 
    {
		addBaseColor( nvgRGB(0, 0x90, 0x40) );;
	}
};

struct DarkGreen2ValueLight : ModuleLightWidget 
{
	DarkGreen2ValueLight() 
    {
		addBaseColor( nvgRGB(0, 0x40, 0) );;
	}
};

struct DarkYellow2ValueLight : ModuleLightWidget 
{
	DarkYellow2ValueLight() 
    {
		addBaseColor( nvgRGB(0x40, 0x40, 0) );;
	}
};

#define lvl_to_db( x ) ( 20.0 * log10( x ) )
#define db_to_lvl( x ) ( 1.0 / pow( 10, x / 20.0 ) )

#define DWRGB( r, g, b ) (b | g<<8 | r<<16)
#define nDISPLAY_LEDS 13
const float fleveldb[ nDISPLAY_LEDS ] = { 0, 3, 6, 10, 20, 30, 40, 50, 60, 80 };


typedef struct
{
    union
    {
        unsigned int dwCol;
        unsigned char Col[ 4 ];
    };
}RGB_STRUCT;



typedef struct
{
    int x, y, x2, y2;
}RECT_STRUCT;

typedef struct
{
    float fx, fy, fx2, fy2;
}fRECT_STRUCT;

typedef struct
{
    float fx, fy;
}POINT_STRUCT;

typedef struct
{
    int nUsed;
    POINT_STRUCT p[ 8 ];
}DRAW_VECT_STRUCT;

typedef struct
{
	float fx, fy;
	float fmx; // as in function y = fx + fn
	float fb;
    bool bVert;
    bool bHorz;
    bool bSet;
}fLine;
 

//-----------------------------------------------------
// LEDMeterWidget
//-----------------------------------------------------
struct LEDMeterWidget : TransparentWidget 
{
    bool            m_bInitialized = false;
    bool            m_bOn[ nDISPLAY_LEDS ] = {};
    int             m_space;
    int             m_StepCount = 0;
    bool            m_bVert;
    float           m_fLargest = 0.0;
    RECT_STRUCT     m_Rects[ nDISPLAY_LEDS ];
    RGB_STRUCT      m_ColoursOn[ nDISPLAY_LEDS ];
    RGB_STRUCT      m_ColoursOff[ nDISPLAY_LEDS ];
    float           flevels[ nDISPLAY_LEDS ] = {};

    //-----------------------------------------------------
    // Procedure:   Constructor
    //-----------------------------------------------------
    LEDMeterWidget( int x, int y, int w, int h, int space, bool bVert )
    {
        int i, xoff = 0, yoff = 0, xpos = 0, ypos = 0;

        m_space = space;
		box.pos = Vec(x, y);

        if( bVert )
        {
            box.size = Vec( w, h * nDISPLAY_LEDS + (m_space * nDISPLAY_LEDS) );
            yoff = h + m_space; 
        }
        else
        {
            box.size = Vec( w * nDISPLAY_LEDS + (m_space * nDISPLAY_LEDS), h );
            xoff = w + m_space;
        }

        for( i = 0; i < nDISPLAY_LEDS; i++ )
        {
            flevels[ i ] = db_to_lvl( fleveldb[ i ] );

            m_Rects[ i ].x = xpos;
            m_Rects[ i ].y = ypos;
            m_Rects[ i ].x2 = xpos + w;
            m_Rects[ i ].y2 = ypos + h;

            // always red
            if( i == 0 )
            {
                m_ColoursOn[ i ].dwCol = DWRGB( 0xFF, 0, 0 );
                m_ColoursOff[ i ].dwCol= DWRGB( 0x80, 0, 0 );
            }
            // yellow
            else if( i < 3 )
            {
                m_ColoursOn[ i ].dwCol = DWRGB( 0xFF, 0xFF, 0 );
                m_ColoursOff[ i ].dwCol= DWRGB( 0x80, 0x80, 0 );
            }
            // green
            else
            {
                m_ColoursOn[ i ].dwCol = DWRGB( 0, 0xFF, 0 );
                m_ColoursOff[ i ].dwCol= DWRGB( 0, 0x80, 0 );
            }

            xpos += xoff;
            ypos += yoff;
        }

        m_bInitialized = true;
    }

    //-----------------------------------------------------
    // Procedure:   draw
    //-----------------------------------------------------
    void draw(NVGcontext *vg) override
    {
        int i;

        if( !m_bInitialized )
            return;

		nvgFillColor(vg, nvgRGBA(0, 0, 0, 0xc0));
		nvgBeginPath(vg);
		nvgMoveTo(vg, -1, -1 );
		nvgLineTo(vg, box.size.x + 1, -1 );
		nvgLineTo(vg, box.size.x + 1, box.size.y + 1 );
		nvgLineTo(vg, -1, box.size.y + 1 );
		nvgClosePath(vg);
		nvgFill(vg);

        for( i = 0; i < nDISPLAY_LEDS; i++ )
        {
            if( m_bOn[ i ] )
                nvgFillColor( vg, nvgRGB( m_ColoursOn[ i ].Col[ 2 ], m_ColoursOn[ i ].Col[ 1 ], m_ColoursOn[ i ].Col[ 0 ] ) );
            else
                nvgFillColor( vg, nvgRGB( m_ColoursOff[ i ].Col[ 2 ], m_ColoursOff[ i ].Col[ 1 ], m_ColoursOff[ i ].Col[ 0 ] ) );

			nvgBeginPath(vg);
			nvgMoveTo(vg, m_Rects[ i ].x, m_Rects[ i ].y );
			nvgLineTo(vg, m_Rects[ i ].x2, m_Rects[ i ].y );
			nvgLineTo(vg, m_Rects[ i ].x2, m_Rects[ i ].y2 );
			nvgLineTo(vg, m_Rects[ i ].x, m_Rects[ i ].y2 );
			nvgClosePath(vg);
		    nvgFill(vg);
        }
	}

    //-----------------------------------------------------
    // Procedure:   Process
    //-----------------------------------------------------
    void Process( float level )
    {
        int steptime = (int)( engineGetSampleRate() * 0.05 );
        int i;

        if( !m_bInitialized )
            return;

        if( fabs( level ) > m_fLargest )
            m_fLargest = fabs( level );

        // only process every 1/10th of a second
        if( ++m_StepCount >= steptime )
        {
            m_StepCount = 0;

            for( i = 0; i < nDISPLAY_LEDS; i++ )
            {
                if( m_fLargest >= flevels[ i ] )
                    m_bOn[ i ] = true;
                else
                    m_bOn[ i ] = false;
            }

            m_fLargest = 0.0;
        }
    }
};

