#include "Template.hpp"


Plugin *plugin;

void init(rack::Plugin *p) {
	plugin = p;
	p->slug = TOSTRING(SLUG);
	p->version = TOSTRING(VERSION);
	p->website = "https://github.com/Miserlou/RJModules";

    
    //p->addModel(modelButtons);
    //p->addModel(modelRotMix);
	 // p->addModel(modelsingleMix);
	 
	  	p->addModel(modelChannel);
	  

	

     

}

