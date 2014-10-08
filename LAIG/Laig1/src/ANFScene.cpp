#include "ANFScene.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

ANFScene :: ANFScene(char *filename){


	doc=new TiXmlDocument( filename );
	bool loadOkay = doc->LoadFile();

	if ( !loadOkay )
	{
		printf( "Could not load file '%s'. Error='%s'. Exiting.\n", filename, doc->ErrorDesc() );

	}

	TiXmlElement* anfElement= doc->FirstChildElement( "anf" );

	if (anfElement == NULL)
	{
		printf("Main anf block element not found! Exiting!\n");

	}

	globalsElement = anfElement->FirstChildElement( "globals" );
	camerasElement = anfElement->FirstChildElement( "cameras" );
	lightElement =  anfElement->FirstChildElement( "lights" );
	texturesElement =  anfElement->FirstChildElement( "textures" );
	appearancesElement =  anfElement->FirstChildElement( "appearances" );
	nodesElement =  anfElement->FirstChildElement( "node" );
	graphElement =  anfElement->FirstChildElement( "graph" );


	this->parseGlobals();
	this->parseCameras();
	this->parseTextures();
	this->parseLights();

}

int ANFScene :: parseCameras(){
	if(camerasElement == NULL)
		printf("Camera block not found!\n");
	else {
		char *initial_c=NULL;
		char *initial=NULL;
		initial_c = (char *)camerasElement->Attribute("initial");
		if(initial_c)
			printf("Cameras attribute: %s\n",initial_c);
		else{
			printf("Error parsing Cameras\n");
			return -1;
		}

		bool perspectiveRead = false, orthoRead = false;

		TiXmlElement* camElement=camerasElement->FirstChildElement();
		while(camElement)
		{
			if(strcmp(camElement->Value(),"perspective")==0)
			{
				float near, far, angle;
				char *id=NULL;
				float position[3], target[3];

				id = (char *)camElement->Attribute("id");
				if (camElement->QueryFloatAttribute("near",&near)==TIXML_SUCCESS && 
					camElement->QueryFloatAttribute("far",&far)==TIXML_SUCCESS &&
					camElement->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS)
				{
					printf("  -perspective attributes: %s %f %f %f\n", id, near, far, angle);


					float pos0,pos1,pos2,tar0,tar1,tar2;

					initial=(char *)camElement->Attribute("pos");

					if(initial && sscanf(initial,"%f %f %f",&pos0, &pos1, &pos2)==3)
					{
						printf("  pos		: (%f,%f,%f)\n", pos0, pos1, pos2);
						position[0]=pos0;
						position[1]=pos1;
						position[2]=pos2;
					}
					else
					{
						cout << "\nError parsing pos...\n";		
						system("pause");
						exit(1);
					}

					initial=(char *)camElement->Attribute("target");

					if(initial && sscanf(initial,"%f %f %f",&tar0, &tar1, &tar2)==3)
					{
						printf("  tar		: (%f,%f,%f)\n\n", tar0, tar1, tar2);
						target[0] = tar0;
						target[1] = tar1;
						target[2] = tar2;
					}
					else
					{
						cout << "\nError parsing target...\n";		
						system("PAUSE");
						exit(1);
					}


				}
				Camera* camera = new PerspectiveCamera(string(id),near,far, angle);
				camera->setPosition(position);
				camera->setTarget(target);

				if(strcmp(id,initial_c)==0)
				{
					camera->setInitial(true);
				}
				cameras.push_back(camera);
				perspectiveRead = true;
			}
			else if(strcmp(camElement->Value(),"ortho")==0)
			{
				char *id=NULL;
				float near,far,left,right,top,bottom;
				id = (char *)camElement->Attribute("id");
				if (camElement->QueryFloatAttribute("near",&near)==TIXML_SUCCESS && 
					camElement->QueryFloatAttribute("far",&far)==TIXML_SUCCESS &&
					camElement->QueryFloatAttribute("left",&left)==TIXML_SUCCESS &&
					camElement->QueryFloatAttribute("right",&right)==TIXML_SUCCESS && 
					camElement->QueryFloatAttribute("top",&top)==TIXML_SUCCESS &&
					camElement->QueryFloatAttribute("bottom",&bottom)==TIXML_SUCCESS)
				{
					printf("  -ortho attributes: ID:%s near:%f far:%f left:%f right:%f top:%f bottom:%f\n\n", id, near, far, left, right, top, bottom);
					Camera* camera = new OrthoCamera(string(id),near,far,left,right,top,bottom);

					if(strcmp(id,initial_c)==0)
					{
						camera->setInitial(true);
					}

					cameras.push_back(camera);
					orthoRead = true;
				}
				else
					printf("Error parsing ortho\n");							
			}
			camElement=camElement->NextSiblingElement();

		}

		if(!perspectiveRead)
			printf("Error reading perspective camera!\n");
		if(!orthoRead)
			printf("Error reading ortho camera!\n");

		printf("Cameras counter: %i\n\n",cameras.size());
	}
	return 0;


}

int ANFScene:: parseGlobals(){

	if(globalsElement == NULL)
		printf("Globals block not found!\n");
	else {
		char* valString= NULL;
		ANFGlobals = Globals();

		TiXmlElement* gElement=globalsElement->FirstChildElement();

		if(strcmp(gElement->Value(),"drawing")==0)
		{
			char *mode, *shading;
			float bg[4];
			float bg0, bg1, bg2, bg3;


			mode =(char *)gElement->Attribute("mode");
			shading =(char *)gElement->Attribute("shading");
			valString=(char *)gElement->Attribute("background");

			if(valString &&sscanf(valString,"%f %f %f %f",&bg0, &bg1, &bg2, &bg3)==4)
			{
				GLenum drawmode, drawshading;

				if(strcmp(mode,"fill")==0)
					drawmode = GL_FILL;
				else if(strcmp(mode,"line")==0)
					drawmode = GL_LINE;
				else if(strcmp(mode,"point")==0)
					drawmode = GL_POINT;
				printf("  drawmode: %s\n", mode);

				if(strcmp(shading,"flat")==0)
					drawshading = GL_FLAT;
				else if(strcmp(shading,"gouraud")==0)
					drawshading = GL_SMOOTH;
				printf("  shading: %s\n", shading);

				bg[0] = bg0;
				bg[1] = bg1;
				bg[2] = bg2;
				bg[3] = bg3;
				printf("  background  : (%f,%f,%f,%f)\n", bg[0], bg[1], bg[2], bg[3]);

				ANFGlobals.updateDraw(drawmode,drawshading,bg);

			}
			else
			{
				cout << "\nError parsing globals<background>...\n";		
				system("PAUSE");
				exit(1);
			}
		}
		else
		{
			cout << "\nError parsing globals<drawing>...\n";		
			system("pause");
			exit(1);
		}


		gElement=gElement->NextSiblingElement();
		if(gElement->Value(),"culling")
		{
			char * cullface, *cullorder;
			GLenum fl, ol;
			cullface =(char *)gElement->Attribute("face");
			cullorder =(char *)gElement->Attribute("order");

			if(cullorder && cullface)
			{
				if(strcmp(cullorder,"CCW")==0)
					ol = GL_CCW;
				else if(strcmp(cullorder,"CW")==0)
					ol = GL_CW;
				printf("  cullorder: %s\n", cullorder);

				if(strcmp(cullface,"back")==0)
					fl = GL_BACK;
				else if(strcmp(cullface,"front")==0)
					fl = GL_FRONT;
				else if(strcmp(cullface,"both")==0)
					fl = GL_FRONT_AND_BACK ;
				printf("  cullface: %s\n\n", cullface);

				ANFGlobals.updateCulli(fl,ol);
			}
			else
			{
				printf("Error parsing culling\n");
				return -1;
			}



		}


		gElement=gElement->NextSiblingElement();
		if(gElement->Value(),"lighting")
		{
			bool doublesided , local , enabled;
			float ambient[4];
			float a0, a1, a2, a3;

			valString =(char *)gElement->Attribute("doublesided");

			if(valString){
				if(strcmp(valString,"true")==0)
					doublesided = true;
				else
					doublesided = false;
			}

			valString =(char *)gElement->Attribute("local");

			if(valString){
				if(strcmp(valString,"true")==0)
					local= true;
				else
					local = false;
			}

			valString =(char *)gElement->Attribute("enabled");

			if(valString){
				if(strcmp(valString,"true")==0)
					enabled = true;
				else
					enabled = false;
			}


			valString=(char *)gElement->Attribute("ambient");

			if(valString &&sscanf(valString,"%f %f %f %f",&a0, &a1, &a2, &a3)==4)
			{
				ambient[0] = a0;
				ambient[1] = a1;
				ambient[2] = a2;
				ambient[3] = a3;
			}


			ANFGlobals.updateLight(doublesided,local,enabled,ambient);
		}
		else
		{
			printf("\nError parsing globals<lighting>...\n");
			return -1;
		}


	}
	return 0;
}

int ANFScene :: parseLights(){

	if(lightElement == NULL)
		printf("Lighting block not found!\n");
	else
	{
		TiXmlElement* lElement = lightElement->FirstChildElement();
		TiXmlElement* compElement;
		char* lightid, *type, *ValString;
		float pos[3], a[4], d[4], s[4];
		float x0,x1,x2;
		bool marker;
		Light *Ltemp;
		CGFlight * CGFLtemp;
		while(lElement){


			lightid = (char *)lElement->Attribute("id");
			type = (char *)lElement->Attribute("type");
			ValString = (char *)lElement->Attribute("pos");

			if(ValString &&sscanf(ValString,"%f %f %f %f",&x0, &x1, &x2)==3)
			{
				pos[0] = x0;
				pos[1] = x1;
				pos[2] = x2;
			}
			CGFLtemp = new CGFlight(atoi(lightid), pos);

			ValString = (char *)lElement->Attribute("enable");

			if(strcmp(ValString,"true") == 0)
				CGFLtemp->enable();
			else
				CGFLtemp->disable();

			ValString = (char *)lElement->Attribute("marker");
			if(strcmp(ValString,"true") == 0)
				marker = true;
			else
				marker = false;


			compElement = lElement->FirstChildElement();
			ValString = (char *)compElement->Attribute("type");

			if(strcmp(ValString,"ambient") == 0)
			{

				ValString = (char *)lElement->Attribute("value");

				if(ValString &&sscanf(ValString,"%f %f %f %f",&x0, &x1, &x2)==3)
				{
					a[0] = x0;
					a[1] = x1;
					a[2] = x2;
				}
			}

			compElement = compElement->NextSiblingElement();

			ValString = (char *)compElement->Attribute("type");

			if(strcmp(ValString,"diffuse") == 0)
			{

				ValString = (char *)lElement->Attribute("value");

				if(ValString &&sscanf(ValString,"%f %f %f %f",&x0, &x1, &x2)==3)
				{
					d[0] = x0;
					d[1] = x1;
					d[2] = x2;
				}
			}

			compElement = compElement->NextSiblingElement();

			ValString = (char *)compElement->Attribute("type");

			if(strcmp(ValString,"specular") == 0)
			{

				ValString = (char *)lElement->Attribute("value");

				if(ValString &&sscanf(ValString,"%f %f %f %f",&x0, &x1, &x2)==3)
				{
					s[0] = x0;
					s[1] = x1;
					s[2] = x2;
				}
			}


			if(strcmp(type,"spot") == 0){
				float target[3];
				float exponent, angle;

				ValString = (char *)lElement->Attribute("target");
				if(ValString &&sscanf(ValString,"%f %f %f %f",&x0, &x1, &x2)==3)
				{
					target[0] = x0;
					target[1] = x1;
					target[2] = x2;
				}

				if (lElement->QueryFloatAttribute("exponent",&exponent)==TIXML_SUCCESS && 
					lElement->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS)
				{
				}


				Ltemp = new SpotLight(CGFLtemp,pos,type,marker, target,exponent, angle);

			}
			else{
				Ltemp = new Light(CGFLtemp,pos,type,marker);

			}


			lights.push_back(Ltemp);
			lElement = lElement->NextSiblingElement();
		}


	}

	return 0;
}

int ANFScene :: parseTextures(){
	if(globalsElement == NULL)
		printf("Textures block not found!\n");
	else {
		char* valString= NULL;

		TiXmlElement* tElement=texturesElement->FirstChildElement();

		Texture *temp;
		string id = "", file = ""; 
		float texlength_s , texlength_t;


		while(tElement){

			id =(char *)tElement->Attribute("id");
			file =(char *)tElement->Attribute("file");

			if(tElement->QueryFloatAttribute("texlength_s",&texlength_s) ==TIXML_SUCCESS &&
				tElement->QueryFloatAttribute("texlength_s",&texlength_t) ==TIXML_SUCCESS
				&& id != "" && file != "" )
			{
				temp = new Texture(id,file,texlength_s,texlength_t);
				textures.push_back(temp);


			}
			else
				printf("Error Texture");


			tElement=tElement->NextSiblingElement();

		}


	}
	return 0;
}

int ANFScene :: parseAppearences(){
	if(appearancesElement == NULL)
		printf("Appearence block not found!\n");
	else {
		TiXmlElement* appearanceElement=appearancesElement->FirstChildElement("appearance");
		char* valString = NULL;
		char* appid,* textref, *type;
		float ambient[4], diffuse[4], specular[4];
		float shininess;
		float x0,x1,x2,x3;
		Appearance* temp;
		CGFappearance* app;

		while(appearanceElement)
		{

			appid = (char *)appearanceElement->Attribute("id");
			if(appid)
			{
				printf("Appearance attribute: %s\n",appid);
			}
			else
			{
				printf("Error1 parsing Appearances\n");
				return -1;
			}

			if(appearanceElement->QueryFloatAttribute("shininess",&shininess) ==TIXML_SUCCESS)
				printf("Appearance Shininess:%f\n",shininess);
			else
				printf("Error2 Appearance Shininess\n");

			textref = (char *)appearanceElement->Attribute("textureref");
			if(textref)
			{
				printf("Appearance textureref: %s\n",textref);
			}
			else
			{
				printf("Error3 parsing Appearances\n");
				return -1;
			}


			TiXmlElement* compElement=appearanceElement->FirstChildElement("component");
			while(compElement){
				type = (char *)compElement->Attribute("type");

				if(strcmp(type,"ambient"))
				{


					valString = (char *)compElement->Attribute("value");
					if(valString &&sscanf(valString,"%f %f %f %f",&x0, &x1, &x2, &x3)==4)
					{
						ambient[0] = x0;
						ambient[1] = x1;
						ambient[2] = x2;
						ambient[3] = x3;
						printf("		Appearence component type=ambient value=<%f %f %f %f>", ambient[0],ambient[1],ambient[2],ambient[3]);
					}
					else
						printf("		Appearence compoenent Ambient Error");


				}


				if(strcmp(type,"diffuse"))
				{
					if(valString &&sscanf(valString,"%f %f %f %f",&x0, &x1, &x2, &x3)==4)
					{
						diffuse[0] = x0;
						diffuse[1] = x1;
						diffuse[2] = x2;
						diffuse[3] = x3;
						printf("		Appearence component type=diffuse value=<%f %f %f %f>", diffuse[0],diffuse[1],diffuse[2],diffuse[3]);
					}


					else
						printf("		Appearence compoenent diffuse Error");

				}


				if(strcmp(type,"specular"))
				{
					if(valString &&sscanf(valString,"%f %f %f %f",&x0, &x1, &x2, &x3)==4)
					{
						diffuse[0] = x0;
						diffuse[1] = x1;
						diffuse[2] = x2;
						diffuse[3] = x3;
						printf("		Appearence component type=specular value=<%f %f %f %f>", specular[0],specular[1],specular[2],specular[3]);
					}


					else
						printf("		Appearence compoenent specular Error");

				}



			}
			app = new CGFappearance(ambient,diffuse,specular,shininess);
			string file = findTexture(textref);
			if(file == "")
			{
				printf("Textura inexistente");
				system("pause");
				exit(1);

			}
			CGFtexture * ttemp = new CGFtexture(file);
			app->setTexture(ttemp);


			temp = new Appearance(string(appid),string(textref),app);

			Apps.push_back(temp);

			appearanceElement = appearanceElement->NextSiblingElement();
		}



	}
	return 0;
}

string ANFScene ::findTexture(string id){

	for(unsigned int i = 0; i < textures.size(); i++){
		if(textures[i]->getId() == id)
			return textures[i]->getFile();
	}
	return "";
}


ANFScene::~ANFScene()
{
	delete(doc);
}


TiXmlElement *ANFScene::findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val)
	// Searches within descendants of a parent for a node that has an attribute _attr_ (e.g. an id) with the value _val_
	// A more elaborate version of this would rely on XPath expressions
{
	TiXmlElement *child=parent->FirstChildElement();
	int found=0;

	while (child && !found)
		if (child->Attribute(attr) && strcmp(child->Attribute(attr),val)==0)
			found=1;
		else
			child=child->NextSiblingElement();

	return child;
}


int main(){

	ANFScene("aula1.anf");

	system("pause");

	return 0;

}