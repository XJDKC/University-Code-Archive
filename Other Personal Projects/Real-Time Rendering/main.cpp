//============================================================
// STUDENT NAME: 
// NUS User ID.: 
// COMMENTS TO GRADER: 
// 
// 
// ============================================================

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS
/////////////////////////////////////////////////////////////////////////////

#define PI                  3.1415926535897932384626433832795

#define PLANET_RADIUS       100.0

#define NUM_CARS            12      // Total number of cars.

#define CAR_LENGTH          32.0
#define CAR_WIDTH           16.0
#define CAR_HEIGHT          14.0

#define CAR_MIN_ANGLE_INCR  0.5     // Min degrees to rotate car around planet each frame.
#define CAR_MAX_ANGLE_INCR  3.0     // Max degrees to rotate car around planet each frame.

#define CAR_TOP_DIST        (PLANET_RADIUS + CAR_HEIGHT)  // Distance of the top of a car from planet's center.

#define EYE_INIT_DIST       (3.0 * CAR_TOP_DIST)  // Initial distance of eye from planet's center.
#define EYE_DIST_INCR       (0.1 * CAR_TOP_DIST)  // Distance increment when changing eye's distance.
#define EYE_MIN_DIST        (1.5 * CAR_TOP_DIST)  // Min eye's distance from planet's center.

#define EYE_LATITUDE_INCR   2.0     // Degree increment when changing eye's latitude.
#define EYE_MIN_LATITUDE    -85.0   // Min eye's latitude (in degrees).
#define EYE_MAX_LATITUDE    85.0    // Max eye's latitude (in degrees).
#define EYE_LONGITUDE_INCR  2.0     // Degree increment when changing eye's longitude.

#define CLIP_PLANE_DIST     (1.1 * CAR_TOP_DIST)  // Distance of near or far clipping plane from planet's center.

#define DESIRED_FPS         60      // Approximate desired number of frames per second.


// Planet's color. 
const GLfloat planetColor[] = { 0.9, 0.6, 0.4 };

// Car tyre color. 
const GLfloat tyreColor[] = { 0.2, 0.2, 0.2 };

// Material properties for all objects.
const GLfloat materialSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat materialShininess[] = { 100.0 };
const GLfloat materialEmission[] = { 0.0, 0.0, 0.0, 1.0 };

// Light 0.
const GLfloat light0Ambient[] = { 0.1, 0.1, 0.1, 1.0 };
const GLfloat light0Diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
const GLfloat light0Specular[] = { 0.9, 0.9, 0.9, 1.0 };
const GLfloat light0Position[] = { 1.0, 1.0, 1.0, 0.0 };

// Light 1.
const GLfloat light1Ambient[] = { 0.1, 0.1, 0.1, 1.0 };
const GLfloat light1Diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
const GLfloat light1Specular[] = { 0.9, 0.9, 0.9, 1.0 };
const GLfloat light1Position[] = { -1.0, 0.0, -0.5, 0.0 };


/////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES

/////////////////////////////////////////////////////////////////////////////

// Define the cars.
typedef struct CarType {
	float bodyColor[3]; // RGB color of the car body.
	double angleIncr;   // Degrees to rotate car around planet each frame.
	double angularPos;  // Angular position of car around planet (in degrees).

	double xzAxis[2];   // A vector in the x-z plane. Contains the x and z components respectively.
	double rotAngle;    // Rotation angle about the xzAxis[].
} CarType;

CarType car[NUM_CARS];    // Array of cars.


						  // Define eye position.
						  // Initial eye position is at [ 0, 0, EYE_INIT_DIST ] in the world frame, 
						  // looking at the world origin. 
						  // The up-vector is assumed to be [0, 1, 0].
double eyeLatitude = 0;
double eyeLongitude = 0;
double eyeDistance = EYE_INIT_DIST;


// Window's size.
int winWidth = 800;     // Window width in pixels.
int winHeight = 600;    // Window height in pixels.


						// Others.
bool pauseAnimation = false;    // Freeze the cars iff true.
bool drawAxes = true;           // Draw world coordinate frame axes iff true.
bool drawWireframe = false;     // Draw polygons in wireframe if true, otherwise polygons are filled.



								/////////////////////////////////////////////////////////////////////////////
								// Draw a car with its bottom on the z = 0 plane. The car is heading in the 
								// +x direction and its top facing the +z direction.
								// The z-axis passes through the center of the car.
								// The car body is drawn using the input color, and its tyres are drawn 
								// using the constant tyreColor.
								// The car has size CAR_LENGTH x CAR_WIDTH x CAR_HEIGHT.
								/////////////////////////////////////////////////////////////////////////////


void DrawOneCar(float bodyColor[3])
{
	glColor3fv(bodyColor);

	//===========================
	// WRITE YOUR CODE HERE.
	//
	// Draw the car body.
	//===========================
	
	// Part 4: Draw the car body.
	// Part 4-1: Draw the bigger rectangular of the car body.
	glPushMatrix();											//Stack the transformation matrix.
	glTranslated(0, 0,CAR_HEIGHT/4);						//Shift the cube.
	glScaled(CAR_LENGTH, CAR_WIDTH, CAR_HEIGHT / 2);		//Scale the cube.
	glutSolidCube(1.0);										//Draw a cube with side 1 at the origin.
	glPopMatrix();											//Restore transformation matrix.

	// Part 4-2: Draw the smaller rectangular of the car body.
	glPushMatrix();											//Stack the transformation matrix.
	glTranslated(0, 0, CAR_HEIGHT*3/4);						//Shift the cube.
	glScaled(CAR_LENGTH * 2 / 3, CAR_WIDTH, CAR_HEIGHT / 2);//Scale the cube.
	glutSolidCube(1.0);										//Draw a cube with side 1 at the origin.
	glPopMatrix();											//Restore transformation matrix.

	glColor3fv(tyreColor);
	//===========================
	// WRITE YOUR CODE HERE.
	//
	// Draw the four tyres.
	//===========================
	// Part 5: Draw the four tyres.
	// The four combinations of i and j represent the four quadrants.
	for (int i=-1;i<2;i+=2)
		for (int j = -1; j < 2; j += 2)
		{
			// Save the original transformation matrix.
			glPushMatrix();
			// Set the translation matrix according to the value of I and j and the size of the car.
			glTranslated(i*(CAR_LENGTH / 3), j*(CAR_WIDTH / 2 + CAR_HEIGHT / 8), CAR_HEIGHT / 4);
			// Rotate torus 90 around the X-axis so that torus's normal vector points in the Y-axis direction.
			glRotated(90, 1, 0, 0);
			// Draw a solid torus at the original point.
			glutSolidTorus(CAR_HEIGHT / 8, CAR_LENGTH / 9, 25, 25);
			// Restore the original transformation matrix.
			glPopMatrix();
		}

	glEnd();
}



/////////////////////////////////////////////////////////////////////////////
// Draw all the cars. Each is put correctly on its great circle.
/////////////////////////////////////////////////////////////////////////////

void DrawAllCars(void)
{
	for (int i = 0; i < NUM_CARS; i++)
	{
		//===========================
		// WRITE YOUR CODE HERE.
		//===========================
		// Part 3: Set the translation and rotation matrix.
		// Part 3-1: Save the previous matrix.
		glPushMatrix();
		// Part 3-2: Rotate Z=0 plane around the xzAxis vector to the great circle plane of the current vehicle.
		glRotated(car[i].rotAngle, car[i].xzAxis[0], 0, car[i].xzAxis[1]);
		// Part 3-3: Rotate the vehicle position to the specified position in great circle.(According to the angularPos)
		glRotated(car[i].angularPos, 0, 1, 0);
		// Part 3-4: Move the vehicle from the origin to the edge of the great circle at z=0.
		glTranslatef(0,0, PLANET_RADIUS);
		// Part 3-5: Draw a car at the origin.
		DrawOneCar(car[i].bodyColor);
		// Part 3-6: Finish drawing the current vehicle and restore the matrix.
		glPopMatrix();
	}
}



/////////////////////////////////////////////////////////////////////////////
// Draw the x, y, z axes. Each is drawn with the input length.
// The x-axis is red, y-axis green, and z-axis blue.
/////////////////////////////////////////////////////////////////////////////

void DrawAxes(double length)
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);
	glLineWidth(3.0);
	glBegin(GL_LINES);
	// x-axis.
	glColor3f(1.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(length, 0.0, 0.0);
	// y-axis.
	glColor3f(0.0, 1.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, length, 0.0);
	// z-axis.
	glColor3f(0.0, 0.0, 1.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, length);
	glEnd();
	glPopAttrib();
}



/////////////////////////////////////////////////////////////////////////////
// The display callback function.
/////////////////////////////////////////////////////////////////////////////

void MyDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//=======================================================================
	// WRITE YOUR CODE HERE.
	//
	// Modify the following line of code to set up a perspective view 
	// frustum using gluPerspective(). The near and far planes should be set 
	// near the planet's surface, yet still allow all of the planet (and cars) 
	// to be seen. The near and far planes should vary with the eye's 
	// distance from the planet's center. You should make use of the value of 
	// the predefined constant CLIP_PLANE_DIST to position your near and 
	// far planes.
	//=======================================================================

	// Part 1: Use gluPerspective to set the Persective view frustum.
	// In this way the current matrix allows objects in camera space to be projected onto the viewport.
	// Set the near and far planes according to eyeDistance and CLIP_PLANE_DIST.
	gluPerspective(45.0, (double)winWidth / winHeight, eyeDistance-CLIP_PLANE_DIST, eyeDistance+CLIP_PLANE_DIST);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//=======================================================================
	// WRITE YOUR CODE HERE.
	// 
	// Modify the following line of code to set up the view transformation.
	// You may use the gluLookAt() function, but you can use other method.
	//=======================================================================

	
	// Part 2: Use gluLookAt to set the camera. 
	// Part 2-1: Using spherical coordinate system. So we need to calculate two angles.
	GLdouble alpha = eyeLongitude * PI / 180.0;
	GLdouble beta = (90 - eyeLatitude) * PI / 180.0;
	// Part 2-2: Calculate camera position according to angles and radius.
	GLdouble eyePosX = eyeDistance * sin(beta) * sin(alpha);
	GLdouble eyePosY = eyeDistance * cos(beta);
	GLdouble eyePosZ = eyeDistance * sin(beta) * cos(alpha);
	// Part 2-3: Calculate the upper direction of the camera.
	GLdouble upx = -sin(alpha);
	GLdouble upy = tan(beta);
	GLdouble upz = -cos(alpha);
	// Part 2-4: Let the y value in the upper direction always be positive.
	if (upy < 0)
	{
		upx = -upx;
		upy = -upy;
		upz = -upz;
	}
	// Part 2-5: The final set.
	// In this way the current matrix can transform the object or vertex from the World Coordinate to the Camera Coordinate. 
	gluLookAt(eyePosX, eyePosY, eyePosZ, 0.0, 0.0, 0.0, upx, upy, upz);
	

	// Part 2: Another solution
	/*
		glTranslated(0, 0, -eyeDistance);
		glRotated(-eyeLongitude, 0, 1, 0);
		glRotated(eyeLatitude, 1, 0, 0);
		glTranslated(0, 0, eyeDistance);
		gluLookAt(0, 0, eyeDistance, 0.0, 0.0, 0.0, 0, 1, 0);
	*/

	// Part 2: Another solution after another
	/*
		gluLookAt(0, 0, eyeDistance, 0.0, 0.0, 0.0, 0, 1, 0);
		glRotated(-eyeLongitude, 0, 1, 0);
		glRotated(eyeLatitude, 1, 0, 0);
	*/

	// Set world positions of the two lights.
	glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
	glLightfv(GL_LIGHT1, GL_POSITION, light1Position);

	// Draw axes.
	if (drawAxes) DrawAxes(2 * PLANET_RADIUS);

	// Draw planet.
	glColor3fv(planetColor);
	glutSolidSphere(PLANET_RADIUS, 72, 36);

	// Draw the cars.
	DrawAllCars();

	glutSwapBuffers();
}



/////////////////////////////////////////////////////////////////////////////
// Update each car's angular position on the great circle by 
// the angle increment.
/////////////////////////////////////////////////////////////////////////////

void UpdateCars(void)
{
	for (int i = 0; i < NUM_CARS; i++)
	{
		car[i].angularPos += car[i].angleIncr;
		if (car[i].angularPos > 360.0) car[i].angularPos -= 360.0;
	}
	glutPostRedisplay();
}



/////////////////////////////////////////////////////////////////////////////
// Initializes each car with a random body color, a random rotation 
// increment (speed), a random anglular position, and a random great circle.
/////////////////////////////////////////////////////////////////////////////

void InitCars(void)
{
	for (int i = 0; i < NUM_CARS; i++)
	{
		car[i].bodyColor[0] = (float)rand() / RAND_MAX;  // 0.0 to 1.0.
		car[i].bodyColor[1] = (float)rand() / RAND_MAX;  // 0.0 to 1.0.
		car[i].bodyColor[2] = (float)rand() / RAND_MAX;  // 0.0 to 1.0.

		car[i].angleIncr = (double)rand() / RAND_MAX *
			(CAR_MAX_ANGLE_INCR - CAR_MIN_ANGLE_INCR) + CAR_MIN_ANGLE_INCR;
		// CAR_MIN_ANGLE_INCR to CAR_MAX_ANGLE_INCR.

		car[i].angularPos = (double)rand() / RAND_MAX * 360.0;      // 0.0 to 360.0.

																	// The following 3 items defines a random great circle.
		car[i].xzAxis[0] = (double)rand() / RAND_MAX * 2.0 - 1.0;   // -1.0 to 1.0.
		car[i].xzAxis[1] = (double)rand() / RAND_MAX * 2.0 - 1.0;   // -1.0 to 1.0.
		car[i].rotAngle = (double)rand() / RAND_MAX * 360.0;        // 0.0 to 360.0.
	}
}



/////////////////////////////////////////////////////////////////////////////
// The timer callback function.
/////////////////////////////////////////////////////////////////////////////

void MyTimer(int v)
{
	if (!pauseAnimation)
	{
		UpdateCars();
		glutTimerFunc(1000 / DESIRED_FPS, MyTimer, v);
	}
}



/////////////////////////////////////////////////////////////////////////////
// The keyboard callback function.
/////////////////////////////////////////////////////////////////////////////

void MyKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		// Quit program.
	case 'q':
	case 'Q':
		exit(0);
		break;

		// Toggle between wireframe and filled polygons.
	case 'w':
	case 'W':
		drawWireframe = !drawWireframe;
		if (drawWireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutPostRedisplay();
		break;

		// Toggle axes.
	case 'x':
	case 'X':
		drawAxes = !drawAxes;
		glutPostRedisplay();
		break;

		// Pause or resume animation.
	case 'p':
	case 'P':
		pauseAnimation = !pauseAnimation;
		if (!pauseAnimation) glutTimerFunc(0, MyTimer, 0);
		break;

		// Reset to initial view.
	case 'r':
	case 'R':
		eyeLatitude = 0.0;
		eyeLongitude = 0.0;
		eyeDistance = EYE_INIT_DIST;
		glutPostRedisplay();
		break;

	}
}



/////////////////////////////////////////////////////////////////////////////
// The special key callback function.
/////////////////////////////////////////////////////////////////////////////

void MySpecialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		eyeLongitude -= EYE_LONGITUDE_INCR;
		if (eyeLongitude < -360.0) eyeLongitude += 360.0;
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
		eyeLongitude += EYE_LONGITUDE_INCR;
		if (eyeLongitude > 360.0) eyeLongitude -= 360.0;
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		eyeLatitude -= EYE_LATITUDE_INCR;
		if (eyeLatitude < EYE_MIN_LATITUDE) eyeLatitude = EYE_MIN_LATITUDE;
		glutPostRedisplay();
		break;

	case GLUT_KEY_UP:
		eyeLatitude += EYE_LATITUDE_INCR;
		if (eyeLatitude > EYE_MAX_LATITUDE) eyeLatitude = EYE_MAX_LATITUDE;
		glutPostRedisplay();
		break;

	case GLUT_KEY_PAGE_UP:
		eyeDistance -= EYE_DIST_INCR;
		if (eyeDistance < EYE_MIN_DIST) eyeDistance = EYE_MIN_DIST;
		glutPostRedisplay();
		break;

	case GLUT_KEY_PAGE_DOWN:
		eyeDistance += EYE_DIST_INCR;
		glutPostRedisplay();
		break;
	}
}



/////////////////////////////////////////////////////////////////////////////
// The reshape callback function.
/////////////////////////////////////////////////////////////////////////////

void MyReshape(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
}



/////////////////////////////////////////////////////////////////////////////
// The init function. It initializes some OpenGL states.
/////////////////////////////////////////////////////////////////////////////

void MyInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0); // Set black background color.
	glEnable(GL_DEPTH_TEST); // Use depth-buffer for hidden surface removal.
	glShadeModel(GL_SMOOTH);

	//=======================================================================
	// The rest of the code below sets up the lighting and 
	// the material properties of all objects.
	// You can just ignore this part.
	//=======================================================================

	// Set Light 0.
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
	glEnable(GL_LIGHT0);

	// Set Light 1.
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1Specular);
	glEnable(GL_LIGHT1);

	glEnable(GL_LIGHTING);

	// Set some global light properties.
	GLfloat globalAmbient[] = { 0.1, 0.1, 0.1, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	// Set the universal material properties.
	// The diffuse and ambient components can be changed using glColor*().
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_NORMALIZE); // Let OpenGL automatically renomarlize all normal vectors.
}



/////////////////////////////////////////////////////////////////////////////
// The main function.
/////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("main");

	MyInit();
	InitCars();

	// Register the callback functions.
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MySpecialKey);
	glutTimerFunc(100, MyTimer, 0);

	// Display user instructions in console window.
	printf("Press LEFT ARROW to move eye left.\n");
	printf("Press RIGHT ARROW to move eye right.\n");
	printf("Press DOWN ARROW to move eye down.\n");
	printf("Press UP ARROW to move eye up.\n");
	printf("Press PAGE UP to move closer.\n");
	printf("Press PAGE DN to move further.\n");
	printf("Press 'P' to toggle car animation.\n");
	printf("Press 'W' to toggle wireframe.\n");
	printf("Press 'X' to toggle axes.\n");
	printf("Press 'R' to reset to initial view.\n");
	printf("Press 'Q' to quit.\n\n");

	// Enter GLUT event loop.
	glutMainLoop();
	return 0;
}
