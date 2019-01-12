#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <GL/glut.h>
#include <boost/program_options.hpp>
#include "demo.hpp"
#include "json.hpp"
#include "options.hpp"

class ConfigGenerator{
private:
    const int size = 2048;
    char *buffer;
    rapidjson::Document conf;

public:
    ConfigGenerator(std::string filename, Options& option){
        if(!std::ifstream(filename.c_str())){
            std::cerr << "Config file does not exist\n";
            exit(0);
        }
        FILE *fp = fopen(filename.c_str(), "r");
        buffer = new char[size];
        rapidjson::FileReadStream is(fp,buffer,size);
        conf.ParseStream<0>(is);        
        if(conf.HasParseError()){                                           
            std::cerr << "Configfile error\n";
            exit(0);
        }

        rapidjson::Value& name = conf["name"];
        rapidjson::Value& screen = conf["screen"];
        rapidjson::Value& map = conf["map"];
        
        rapidjson::Value& screen_width = screen["width"];
        rapidjson::Value& screen_height = screen["height"];

        option.configfile = filename;
        option.name = name.GetString();
        option.screen_width = screen_width.GetInt();
        option.screen_height = screen_height.GetInt();
        option.map = map.GetString();
    }

    ~ConfigGenerator(){
        delete buffer;
    }
};

// Init global object
Options options;
Demo g;

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
        // config file path
        std::string configure;
        namespace po = boost::program_options;
        po::options_description desc{"Options"};
        desc.add_options()
            ( "help,h", "Help screen")
            ( "config,c", po::value( &configure ), "Configuration file path" );
        
        po::variables_map vm;
        po::store(parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")){
            std::cout << desc << '\n';
            exit(0);
        }
        else if (vm.count("config")){
            std::cout << "Config: " << configure << '\n';
        }

        // load json file
        ConfigGenerator(configure, options);

        // load demo options
        g.load(options);


        // init glut
        glutInit(&argc,argv);

        // double buffer
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );

        // Window position (from top corner), and size (width and hieght)
        glutInitWindowPosition( 0, 0 );
        glutInitWindowSize(options.screen_width, options.screen_width);
        glutCreateWindow(options.name.c_str());

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
