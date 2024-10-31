#include "client.h"
#include <iostream>
#include <cmath>  
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


int main()
{
    msg_fsonar::Obj m_obj;
    m_obj.msg = "$FSP";
    m_obj.center_x = 5.1;
    m_obj.center_y = 5.2;
    m_obj.distance_x = 8.1;
    m_obj.distance_y = 8.2;
    client m_client("127.0.0.1",8080);
    std::vector<msg_fsonar::Obj> v1;
    v1.push_back(m_obj);
    while (true)
    {
        m_client.sendmessage(v1);
    }
}


// class test
// {
// public:
//     test(/* args */);
//     client m_client();
//     ~test();
// };

// test::test(/* args */)
// {
// }

// test::~test()
// {
// }
