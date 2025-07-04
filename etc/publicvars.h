#ifndef PUBLICVARS_H
#define PUBLICVARS_H

#include <iostream>
//using namespace std;

class publicVars
{
public:
    publicVars();
//    class camera
//    {
//    public:
//        camera();
        std::string camNo = "1";

        std::string zoomStopCmd = camNo + "00" + camNo;

        // Default set 1
        int temp_set1 = 10;


        // Default set 2
        int temp_set2 = 20;



//    };
};

#endif // PUBLICVARS_H
