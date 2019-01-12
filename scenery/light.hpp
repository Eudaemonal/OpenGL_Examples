#ifndef LIGHT_HPP
#define LIGHT_HPP

class Light{
public:
    Light(float a, float d, float s)
        : ambient(a)
        , diffuse(d)
        , specular(s)
    {
    }

    void init(){
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }


    void set(){
        float a[4] = {ambient, ambient, ambient, 1.0};
        float d[4] = {diffuse, diffuse, diffuse, 1.0};
        float s[4] = {specular, specular, specular, 1.0};

        glLightfv(GL_LIGHT0, GL_AMBIENT, a);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
        glLightfv(GL_LIGHT0, GL_SPECULAR, s);

        glLightfv(GL_LIGHT0, GL_POSITION, location);

        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
        //glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR); 
    }

private:
    float ambient;
    float diffuse;
    float specular;
    float location[3] = {10,10,10};

};



#endif
