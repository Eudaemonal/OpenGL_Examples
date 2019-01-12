#ifndef DEMO_HPP
#define DEMO_HPP

#include "options.hpp"
#include "terrain.hpp"
#include "light.hpp"
#include "json.hpp"


class Demo{
public:
    Demo()
        : Name("")
        , xRotated(0.0)
        , yRotated(0.0)
        , zRotated(0.0)
    {
        terrain = new Terrain;
        light = new Light(0.5, 0.9, 0.8);
    }

    // Configure settings
    void load(Options& options){
        // read map configuration
        int w, d;
        const int size = 2048;
        char *buffer;
        rapidjson::Document conf;
        if(!std::ifstream(options.map.c_str())){
            std::cerr << "Map does not exist\n";
            exit(0);
        }
        FILE *fp = fopen(options.map.c_str(), "r");
        buffer = new char[size];
        rapidjson::FileReadStream is(fp,buffer,size);
        conf.ParseStream<0>(is);        
        if(conf.HasParseError()){                                           
            std::cerr << "map file error\n";
            exit(0);
        }

        rapidjson::Value& width = conf["width"];
        rapidjson::Value& depth = conf["depth"];
        rapidjson::Value& altitude = conf["altitude"];

        w = width.GetInt();
        d = depth.GetInt();
        std::vector<std::vector<double>> altitudes(d, std::vector<double>(w));
        for(int i = 0; i < d; ++i){
            for(int j = 0; j < w; ++j){
                altitudes[i][j] = altitude[i*w + j].GetDouble();
            }
        }
        // load terrain altitudes
        terrain->load(altitudes);       

    }


    void init(void) {
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        
        glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
        
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_NORMALIZE);

        // init lighting
        light->init();

    }

    void display(void) {
        glMatrixMode(GL_MODELVIEW);
        // clear the drawing buffer.
        glClear(GL_COLOR_BUFFER_BIT);
        // clear the identity matrix.
        glLoadIdentity();
    
        // set position -10
        glTranslatef(0.0,0.0,-10.0);
    
        glRotatef(xRotated,1.0,0.0,0.0);
        glRotatef(yRotated,0.0,1.0,0.0);
        glRotatef(zRotated,0.0,0.0,1.0);
        
        glScalef(1.0,1.0,1.0);
        // Start drawing
        light->set();
        terrain->draw();
            
     
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
    // Basic Universal parameters
    std::string Name;

    double xRotated;
    double yRotated;
    double zRotated;
    
    double CameraFovy = 60.0;
    double CameraNearPlane = 0.5;
    double CameraFarPlane = 100.0;

    std::pair<int, int> MousePoint;
    double RotationScale = 1;

    // User defined Scenery parameters
    Terrain *terrain;
    Light *light;

};

#endif
