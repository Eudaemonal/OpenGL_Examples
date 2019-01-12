#include <iostream>
#include <utility>
#include <GL/glut.h>
#include <boost/program_options.hpp>
#include <demo.hpp>


// Init global object
std::string Title = "Scenery";
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
        std::string configure;
        namespace po = boost::program_options;
        po::options_description desc{"Options"};
/*
        desc.add_options()
            ( "help,h", "Help screen")
            ( "config,c", po::value( &configure ), "Configuration file" );
        
        po::variables_map vm;
        po::store(parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help"))
            std::cout << desc << '\n';
        else if (vm.count("config"))
            std::cout << "Config: " << configure << '\n';
*/


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
