//Kutay Özbay 270201017
#include <string>

namespace ceng391 {
typedef unsigned char uchar;

class Image
{
public:
        Image(int n_channels, int width, int height, int step=-1);
        ~Image();
        
        //Integer member field that stores the number of channels per pixel
        int n() const {return m_n_channels; }

        int w() const { return m_width; }
        int h() const { return m_height; }
        int step() const { return m_step; }

        const uchar *data() const { return m_data; }
        uchar *      data()       { return m_data; }
        const uchar *data(int y) const { return m_data + y*m_step; }
        uchar *      data(int y)       { return m_data + y*m_step; }
        
        //Set function for RGB
        void set_RGB(uchar R, uchar G, uchar B){set_rect_RGB(0, 0, m_width, m_height, R, G, B);}

        //Set_Rect function for RGB
        void set_rect_RGB(int x_tl, int y_tl, int width, int height, uchar R, uchar G, uchar B);
        
        //Set function for RGBA
        void set_RGBA(uchar R, uchar G, uchar B, uchar A){set_rect_RGBA(0, 0, m_width, m_height, R, G, B, A);}

        //Set_Rect function for RGBA
        void set_rect_RGBA(int x_tl, int y_tl, int width, int height, uchar R, uchar G, uchar B, uchar A);

        void set(uchar value) { set_rect(0, 0, m_width, m_height, value); }
        void set_rect(int x_tl, int y_tl, int width, int height, uchar value);

        void xsave_pnm(const std::string& filename) const;
        void read_pnm(const std::string& filename, int m_n_channels)const;

        void to_grayscale(Image img);
        void to_rgb(Image img);
        void to_rgba(Image img);
private:
        int m_n_channels;
        int m_width;
        int m_height;
        int m_step;

        uchar *m_data;
};

}
