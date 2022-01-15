//Kutay Özbay 270201017


#include "ceng391/image.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <fstream>
#include <cstring>



using namespace std;

namespace ceng391 { 

Image::Image(int n_channels, int width, int height, int step)
{       
        m_n_channels = n_channels;
        if(m_n_channels == 1 || m_n_channels == 3 || m_n_channels == 4 ){
                if (m_n_channels == 1)
                {
                        cout << "Creating grayscale image..."
                        << endl;
                }
                else if (m_n_channels == 3)
                {
                        cout << "Creating RGB image..."
                        << endl;
                }
                else{
                        cout << "Creating RGBA image..."
                        << endl;
                } 
        }
        else{
                        cout << "You entered a nonvalid number of channels per pixel!! "
                        << endl;
        }
        m_width = width;
        m_height = height;
        m_step = m_width*m_n_channels;
        if (step > m_step)
                m_step = step;
        

        m_data = new uchar[m_step * m_height];
}

Image::~Image()
{
        delete [] m_data;
}

//Exercise 1
//set_rect Function for RGB Image
void Image::set_rect_RGB(int x_tl, int y_tl, int width, int height, uchar R, uchar G, uchar B)
{       
        if (x_tl < 0) {
                width += x_tl;
                x_tl = 0;
        }
        if (y_tl < 0) {
                height += y_tl;
                y_tl = 0;
        }

        for (int j = y_tl; j < y_tl+height; ++j) {
        if (j >= m_height)
            break;
        uchar* row_data = data(j);
        for (int i = x_tl; i < x_tl+width; ++i) {
            if (i >= m_width)
                break;
            for (int c = 0; c < m_n_channels; ++c)
                if (c == 0) {
                    //Red data    
                    row_data[i*m_n_channels + c] = R;
                } else if (c == 1) {
                    //Green data
                    row_data[i*m_n_channels + c] = G;
                } else if (c == 2) {
                    //Blue data
                    row_data[i*m_n_channels + c] = B;
                }
        }
        }
}
//set_rect Function for RGBA Image 
void Image::set_rect_RGBA(int x_tl, int y_tl, int width, int height, uchar R, uchar G, uchar B, uchar A)
{
        if (x_tl < 0) {
                width += x_tl;
                x_tl = 0;
        }

        if (y_tl < 0) {
                height += y_tl;
                y_tl = 0;
        }
        for (int j = y_tl; j < y_tl+height; ++j) {
        if (j >= m_height)
            break;
        uchar* row_data = data(j);
        for (int i = x_tl; i < x_tl+width; ++i) {
            if (i >= m_width)
                break;
            for (int c = 0; c < m_n_channels; ++c)
                if (c == 0) {
                        //Red data
                        row_data[i*m_n_channels + c] = R;
                } 
                else if (c == 1) {
                        //Green data
                        row_data[i*m_n_channels + c] = G;
                } 
                else if (c == 2) {
                        //Blue data
                        row_data[i*m_n_channels + c] = B;
                }
                else if (c == 3)
                {
                        //Alpha value
                        row_data[i*m_n_channels + c] = A;
                }
                
                
        }
        }

        
}

//Original set_rect Function
void Image::set_rect(int x_tl, int y_tl, int width, int height, uchar value)
{
        if (x_tl < 0) {
                width += x_tl;
                x_tl = 0;
        }

        if (y_tl < 0) {
                height += y_tl;
                y_tl = 0;
        }

        size_t length = min(width, m_width - x_tl);
        int y_max = min(y_tl + height, m_height);
        for (int y = y_tl; y < y_max; ++y) {
                uchar *row_y = data(y) + x_tl;
                memset(row_y, value, length);
        }
}

void Image::xsave_pnm(const  std::string& filename) const
{
        //x_save_ppm function for RGB and RGBA images that write them in .ppm format
        if (m_n_channels != 1) {
            const string magic_head = "P6";
            ofstream fout;
            string extended_name = filename + ".ppm";
            fout.open(extended_name.c_str(), ios::out | ios::binary);
            fout << magic_head << "\n";
            fout << m_width << " " << m_height << " 255\n";
            for (int y = 0; y < m_height; ++y) {
                    const uchar *row_data = data(y);
                    cout << reinterpret_cast<const char*>(row_data);
                    fout.write(reinterpret_cast<const char*>(row_data), m_width*sizeof(uchar)*3);
            }
            fout.close();
        }

        else{
                const string magic_head = "P5";
                ofstream fout;
                string extended_name = filename + ".pgm";
                fout.open(extended_name.c_str(), ios::out | ios::binary);
                fout << magic_head << "\n";
                fout << m_width << " " << m_height << " 255\n";
                for (int y = 0; y < m_height; ++y) {
                        const uchar *row_data = this->data(y);
                        fout.write(reinterpret_cast<const char*>(row_data),m_width*sizeof(uchar));
                }
                fout.close();
        }
}

//Exercise  2
void Image::read_pnm(const std::string& filename, int m_n_channels) const
{
        //Opening file
	ifstream imageFile;
        string extended_name;
        if(m_n_channels == 1){
                string extended_name = filename + ".pgm";
        }
        else{
                string extended_name = filename + ".ppm";
        }
	imageFile.open(extended_name.c_str(), std::ifstream::binary);
	//Loading file values into vector for parsing
	std::vector<char> data;
	char temp;
	while(imageFile.get(temp)){
		data.push_back(temp);
	}
	
	//Closing file
	imageFile.close();
	
	//Building Image and parse file contents
	if(data[1] == '5' || data[1] == '2'){
		int m_n_channels = 1;
	}else if(data[1] == '6' || data[1] == '3'){
		int m_n_channels = 3;
	}else{
		throw std::invalid_argument("Error parsing file. Invalid magic number: " + data[1]);
	}
	
	
	int index = 3;
	while(data[index] == '#'){
		while(data[index] != 10){
			index++;
		}
		index++;
	}
	
	//Getting width and height numbers
	std::vector<char> widthVector;
	while(data[index] != ' '){
		widthVector.push_back(data[index] - 48);
		index++; 
	}
	index++;
	
	std::vector<char> heightVector;
	while(data[index] != 10){
		heightVector.push_back(data[index] - 48);
		index++;
	}
	index++;
	
	//Converting vectors to int
	int m_width = 0;
	for(int i = widthVector.size() - 1; i >= 0; i--){
		m_width += widthVector[i] * (int)pow(10, widthVector.size() - 1 - i);
	}
	
	int m_height = 0;
	for(int i = heightVector.size() - 1; i >= 0; i--){
		m_height += heightVector[i] * (int)pow(10, heightVector.size() - 1 - i);
	}

        Image img(m_n_channels, m_width, m_height);
	
	//Skipping past the max value
	while(data[index] != 10){
		index++;
	}
	index++;
	
	//Copying pixel data into char array

        int m_step = m_width*m_n_channels;
	int length = m_step * m_height;
	for(int j = 0; j < length; j++){
		img.m_data[j] = data[index];
		index++;
	}
	
	
	
	
	
	
}//end of reading and loading Image


//Exercise 3
void Image::to_grayscale(Image img)
{
        if(img.n() != 1){
                //RGB to GrayScale conversion
                if(img.n() == 3){
                        int k = 0;
                        for(int i = 0; i < (img.step() / 3) ; i++){
                                Image img_gray(1, img.w(), img.h());
                                img_gray.m_data[i] = (img.m_data[k] * 0.3f) + (img.m_data[k + 1] * 0.59f) + (img.m_data[k + 2] * 0.11f);
                                k += 3;
                        }
                }
                // RGBA to GrayScale conversion
                else{
                        int k = 0;
                        for(int i = 0; i < (img.step() / 4) ; i++){
                                Image img_gray(1, img.w(), img.h());
                                img_gray.m_data[i] = (img.m_data[k] * 0.3f) + (img.m_data[k + 1] * 0.59f) + (img.m_data[k + 2] * 0.11f);
                                k += 4;
                        } 
                }
        }
        else{
                cout << "The image is already in the desired format."  << endl;
        }
}
void Image::to_rgb(Image img)
{
        if(img.n() != 3){
                //GrayScale to RGB conversion
                if(img.n() == 1){
                        int k = 0;
                        for(int i = 0; i < (img.step()) ; i++){
                                Image img_rgb(3, img.w(), img.h());
                                img_rgb.m_data[k] = img.m_data[i];
                                img_rgb.m_data[k + 1] = img.m_data[i];
                                img_rgb.m_data[k + 2] = img.m_data[i];
                                k += 3;
                        }
                }
                // RGBA to RGB conversion
                else{
                        int k = 0;
                        for(int i = 0; i < ((img.step() / 4) ) ; i++){
                                Image img_rgb(3, img.w(), img.h());
                                img_rgb.m_data[k] = img.m_data[k];
                                img_rgb.m_data[k + 1] = img.m_data[k + 1];
                                img_rgb.m_data[k + 2] = img.m_data[k + 2];
                                k += 3;
                        }
                }
        }
        else{
                cout << "The image is already in the desired format."  << endl;
        }
}
void Image::to_rgba(Image img)
{
        if(img.n() != 4){
                //GrayScale to RGB conversion
                if(img.n() == 1){
                        int k = 0;
                        for(int i = 0; i < (img.step()) ; i++){
                                Image img_rgba(4, img.w(), img.h());
                                img_rgba.m_data[k] = img.m_data[i];
                                img_rgba.m_data[k + 1] = img.m_data[i];
                                img_rgba.m_data[k + 2] = img.m_data[i];
                                img_rgba.m_data[k + 3] = 255;                                
                                k += 4;
                        }
                }
                // RGBA to RGB conversion
                else{
                         int k = 0;
                        for(int i = 0; i < ((img.step() / 3)); i++){
                                Image img_rgba(4, img.w(), img.h());
                                img_rgba.m_data[k] = img.m_data[k];
                                img_rgba.m_data[k + 1] = img.m_data[k + 1];
                                img_rgba.m_data[k + 2] = img.m_data[k + 2];
                                img_rgba.m_data[k + 3] = 255;
                                k += 4;
                        }
                }
        }
        else{
                cout << "The image is already in the desired format."  << endl;
        }
}
}
