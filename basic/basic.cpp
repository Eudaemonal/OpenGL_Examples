#include <iostream>
#include <utility>
#include <GL/glut.h>


class Demo{
public:
    Demo() 
        : Title("")
        , xRotated(0.0)
        , yRotated(0.0)
        , zRotated(0.0)
    {}

    Demo(std::string _title)
        : Title(_title)
        , xRotated(0.0)
        , yRotated(0.0)
        , zRotated(0.0)
    {}

    void init(void) {
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        
        glClearColor(0.0,0.0,0.0,0.0);
    }

    void display(void) {
        glMatrixMode(GL_MODELVIEW);
        // clear the drawing buffer.
        glClear(GL_COLOR_BUFFER_BIT);
        // clear the identity matrix.
        glLoadIdentity();
    
        // set position -5
        glTranslatef(0.0,0.0,-5.0);
    
        glRotatef(xRotated,1.0,0.0,0.0);
        glRotatef(yRotated,0.0,1.0,0.0);
        glRotatef(zRotated,0.0,0.0,1.0);
        
        glScalef(1.0,1.0,1.0);
        
        
        // Red color used to draw.
        glColor3f(0.8, 0.2, 0.1); 
        glutSolidTeapot(1);
     
        glFlush();        
    }


    // Called when the window is resized
    void reshape(int x, int y) {
        if (y == 0 || x == 0) return;  //Nothing is visible then, so return
        //Set a new projection matrix
        glMatrixMode(GL_PROJECTION);  
        glLoadIdentity();
    
        gluPerspective(CameraFovy,(GLdouble)x/(GLdouble)y,CameraNearPlane,CameraFarPlane);
 
        glViewport(0,0,x,y);  //Use the whole window for rendering
    }

    void idle(){
        yRotated += 0.01;
     
        display();
    }

    // mouse passive move event
    void move(int x, int y) {
        MousePoint = std::make_pair(x, y);
    }

    // mouse drag event
    void drag(int x, int y) {
        std::pair<int, int> point = std::make_pair(x, y);
        int dx = point.first - MousePoint.first;
        int dy = point.second - MousePoint.second;

        xRotated += dy * RotationScale;
        yRotated += dx * RotationScale;

        MousePoint = point;
    }


    // handle all normal key presses
    void keyboard(unsigned char key, int x, int y){
        switch(key){
            case 27: //Escape key
                exit(1);
        }
    }

    // handle all special key presses
    // See glut.h for the names of all special keys
    void specialkey(int key, int x, int y) {
        switch ( key ) {
            case GLUT_KEY_LEFT:
                break;
            case GLUT_KEY_UP:
                break;
            case GLUT_KEY_RIGHT:
                break;
            case GLUT_KEY_DOWN:
                break;
        }
    }



private:
    std::string Title;

    double xRotated;
    double yRotated;
    double zRotated;
    
    double CameraFovy = 60.0;
    double CameraNearPlane = 0.5;
    double CameraFarPlane = 100.0;

    std::pair<int, int> MousePoint;
    double RotationScale = 1;
};



// Init global object
std::string Title = "Demo";
int Width = 800;
int Height = 600;
Demo g(Title);



// Wrapper for class members
void initRendering(){
    g.init();
} 

void drawScene(){
    g.display();
}

void resizeWindow(int w, int h){
    g.reshape(w, h);
}

void idleFunc(void){
    g.idle();
}

void mouseMove(int x, int y){
    g.move(x, y);
}

void mouseDrag(int x, int y){
    g.drag(x, y);
}

void KeyboardFunc(unsigned char key, int x, int y){
    g.keyboard(key, x, y);
}

void SpecialKeyFunc(int key, int x, int y){
    g.specialkey(key, x, y);
}

// main
int main(int argc, char *argv[]){
    try{
        // init glut
        glutInit(&argc,argv);

        // double buffer
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );

        // Window position (from top corner), and size (width and hieght)
        glutInitWindowPosition( 0, 0 );
        glutInitWindowSize(Width, Height);
        glutCreateWindow(Title.c_str());

        initRendering();

        // callback functions for key presses
        glutKeyboardFunc( KeyboardFunc );  // normal ascii symbols
        glutSpecialFunc( SpecialKeyFunc ); // special keys

        // Resize the window
        glutReshapeFunc( resizeWindow );

        // Background process
        glutIdleFunc(idleFunc);

        // Mouse passive move
        glutPassiveMotionFunc(mouseMove);
        
        // Mouse drag
        glutMotionFunc(mouseDrag);

        // Redraw the window
        glutDisplayFunc( drawScene );

        // start main loop
        glutMainLoop();

        return EXIT_SUCCESS;
    }catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
