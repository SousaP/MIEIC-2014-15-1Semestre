#include "TPinterface.h"
#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];

TPinterface::~TPinterface(){
	delete(Scene);

	for(unsigned int i = 0; i < lights.size(); i++)
		delete(lights[i]);

	for(unsigned int i = 0; i < cameras.size(); i++)
		delete(cameras[i]);
}

TPinterface::TPinterface(): CGFinterface() {
}

TPinterface::TPinterface(ANFScene* S): CGFinterface() {
	testVar=0;
	Scene = S;
}

void TPinterface::initGUI() {
	lights = Scene->getLights();
	cameras = Scene->getCameras();

	int i = 1;
	GLUI_Panel * panelLights = addPanel("Lights: ", 1);
	for(std::vector<Light *>::iterator it = lights.begin(); it != lights.end() ;it++) {
		addCheckboxToPanel (panelLights,(char *)((*it)->getid_s()).c_str(),(int *)&((*it)->active), i);
	}
	addColumn();
	i++;

	GLUI_Panel * cameraPanel = addPanel("Cameras: ", 1);
	GLUI_RadioGroup *modeCamera = addRadioGroupToPanel(cameraPanel,&Scene->Active_Camera,2);

	addRadioButtonToGroup(modeCamera, "OpenGL Default");

	for(unsigned int i = 0; i < cameras.size(); i++)
	{
		addRadioButtonToGroup(modeCamera, (char *)cameras[i]->cameraid.c_str());
	}

	addColumn();


	GLUI_Panel * texturePanel = addPanel( (char*)"Draw Mode");
	GLUI_Listbox * textureList = addListboxToPanel(texturePanel, (char*)"", &(Scene->drawMode), 3);

	textureList->add_item (0, "Fill");
	textureList->add_item (1, "Wireframe");
	textureList->add_item (2, "Point");

	GLUI_Panel * windPanel = addPanel("Wind: ", 1);
	GLUI_Spinner* winrot =addSpinnerToPanel( windPanel,"",  2, &(Scene->globalWind), 4);

	addColumn();
	GLUI_Panel * movPanel = addPanel("Mov: ", 1);
	GLUI_RadioGroup *modeGame = addRadioGroupToPanel(movPanel,&Scene->play_Mode,5);

	addRadioButtonToGroup(modeGame, "New Piece");
	addRadioButtonToGroup(modeGame, "Move Piece");


	GLUI_Panel * movPiece = addPanel("In Case Move", 1);
	GLUI_Listbox * wallList = addListboxToPanel(movPiece, (char*)"", &(Scene->wallPosition), 6);

	wallList->add_item (0, "Top");
	wallList->add_item (1, "Bottom");
	wallList->add_item (2, "Left");
	wallList->add_item (2, "Right");

}

void TPinterface::processGUI(GLUI_Control *ctrl) {
	printf ("\nGUI control id: %d",ctrl->user_id);
	switch (ctrl->user_id)
	{
	case 1:
		for(unsigned int i = 0; i < lights.size(); i++) {
			if(lights[i]->active)
				lights[i]->turnOn();
			else
				lights[i]->turnOff();
		}
		break;
	case 2:
		printf("\nCamera Changed");
		Scene->changeCamera();
		break;
	case 3:
		printf("\nDraw Mode Changed");
		break;
	case 4:
		printf("\nWind Changed");
		Scene->setGlobalWind();
		break;
	case 5:
		printf("\nPlay Mode Changed");
		break;
	case 6:
		printf("\nWall position Changed");
		break;
	}
}

void TPinterface::processMouse(int button, int state, int x, int y) 
{
	CGFinterface::processMouse(button,state, x, y);

	// do picking on mouse press (GLUT_DOWN)
	// this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		performPicking(x,y);
}

void TPinterface::performPicking(int x, int y) 
{
	// Sets the buffer to be used for selection and activate selection mode
	glSelectBuffer (BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);

	// Initialize the picking name stack
	glInitNames();

	// The process of picking manipulates the projection matrix
	// so we will be activating, saving and manipulating it
	glMatrixMode(GL_PROJECTION);

	//store current projmatrix to restore easily in the end with a pop
	glPushMatrix ();

	//get the actual projection matrix values on an array of our own to multiply with pick matrix later
	GLfloat projmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX,projmat);

	// reset projection matrix
	glLoadIdentity();

	// get current viewport and use it as reference for 
	// setting a small picking window of 5x5 pixels around mouse coordinates for picking
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// this is multiplied in the projection matrix
	gluPickMatrix ((GLdouble) x, (GLdouble) (CGFapplication::height - y), 5.0, 5.0, viewport);

	// multiply the projection matrix stored in our array to ensure same conditions as in normal render
	glMultMatrixf(projmat);

	// force scene drawing under this mode
	// only the names of objects that fall in the 5x5 window will actually be stored in the buffer
	scene->display();

	// restore original projection matrix
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();

	glFlush();

	// revert to render mode, get the picking results and process them
	GLint hits;
	hits = glRenderMode(GL_RENDER);
	processHits(hits, selectBuf);
}

void TPinterface::processHits (GLint hits, GLuint buffer[]) 
{
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *selected=NULL;
	GLuint nselected;

	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (int i=0;i<hits;i++) {
		int num = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && num>0) {
			mindepth = z1;
			selected = ptr;
			nselected=num;
		}
		for (int j=0; j < num; j++) 
			ptr++;
	}
	
	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected!=NULL)
	{
		// this should be replaced by code handling the picked object's ID's (stored in "selected"), 
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		printf("\nPicked ID's: ");
		for (unsigned int i=0; i<nselected; i++)
			printf("%d ",selected[i]);
		printf("\n");
	}
}
