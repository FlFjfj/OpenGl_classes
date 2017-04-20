//
// Created by opot on 19.04.17.
//

#ifndef GLUTGL_ENGINE_H
#define GLUTGL_ENGINE_H


namespace fjfj {

    class Engine {
        void (*init)(void);
        void (*update)(float);
        void (*render)(void);

    public:
        Engine(void (*init)(void), void (*update)(float), void (*render)(void));

        void start();

    };

    //TODO obj loader
    //TODO Mesh concat
    //TODO OrthographicCamera
    //TODO 2dRenderer
}

#endif //GLUTGL_ENGINE_H