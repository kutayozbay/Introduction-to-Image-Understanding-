//Kutay Özbay 270201017

#include "D:\Lectures\Year 3 Term 1\CENG391\libceng391\include\ceng391\image.hpp"

#include <cstdlib>
#include <iostream>



using namespace std;
using ceng391::Image;

int main(int /*argc*/, char** /*argv*/)
{

//Exercise 1 Test
        //GrayScale Image
        Image img_gray(1, 480, 240);
        cout << "Created image of size (" << img_gray.w()
             << "x" << img_gray.h() << ")!" << endl;
        img_gray.set(255);
        img_gray.set_rect(100, -50, 230, 150, 245);
        img_gray.xsave_pnm("/tmp/test_img");

        //RGB Image
        Image img_rgb(3, 100, 240);
        cout << "Created image of size (" << img_rgb.w()
             << "x" << img_rgb.h() << ")!" << endl;
        img_rgb.set(255);
        img_rgb.set_rect_RGB(20, 30, 100, 240, 142, 200, 47);
        img_rgb.xsave_pnm("/tmp/test_img");

        //RGBA Image
        Image img_rgba(4, 100, 240);
        cout << "Created image of size (" << img_rgba.w()
             << "x" << img_rgba.h() << ")!" << endl;
        img_rgba.set(255);
        img_rgb.set_rect_RGBA(20, 30, 100, 240, 150, 210, 7, 255);
        img_rgba.xsave_pnm("/tmp/test_img");
        
//Exercise 2 Test

        img_gray.read_pnm("/tmp/test_img", 1);
        img_rgb.read_pnm("/tmp/test_img", 3);
        img_rgba.read_pnm("/tmp/test_img", 4);     
        
//Exercise 3 Test

        //RGB to GrayScale
        img_gray.to_grayscale(img_rgb);
        //RGBA to GrayScale
        img_gray.to_grayscale(img_rgba);
        //GrayScale to RGB
        img_rgb.to_rgb(img_gray);
        //RGBA to RGB
        img_rgb.to_rgb(img_rgba);
        //GrayScale to RGBA
        img_rgba.to_rgba(img_gray);
        //RGB to RGBA
        img_rgba.to_rgba(img_rgb);



        return EXIT_SUCCESS;
}

/// Local Variables:
/// mode: c++
/// compile-command: "make -C ../build image-test"
/// End:
