#include "svg.h"
//#include "histogram.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

string text_decoration18(size_t bin)
{
    size_t k=-1;

    while ((k<0) or (k>3))
    {
        cerr<<endl;
        cerr<<"Now choose the text of "<<bin+1<<" column"<<endl;
        cerr<<"0 - none"<<endl;
        cerr<<"1 - underline"<<endl;
        cerr<<"2 - overline"<<endl;
        cerr<<"3 - line-through"<<endl;
        cerr<<"If you enter another number you will have one more try!"<<endl;
        cin>>k;
    }

    if (k==0)
        return "none";

    if (k==1)
        return "underline";

    if (k==2)
        return "overline";

    if (k==3)
        return "line-through";
}

void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, size_t text, string text_decoration = "none")
{
    cout << "<text x='" << left << "' y='"<<baseline<<"' text-decoration='"<<text_decoration<<"'>"<<text<<"</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill)
{
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />";
}

void show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const size_t MAX_ASTERISK = IMAGE_WIDTH - TEXT_LEFT - TEXT_WIDTH;

    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }

    const bool scaling_needed = max_count * BLOCK_WIDTH > MAX_ASTERISK;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);


    double top = 0;
    size_t i = 0;
    for (size_t bin : bins)
    {
        size_t height = bin;
        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_ASTERISK / (max_count * BLOCK_WIDTH);
            height = (size_t)(bin * scaling_factor);
        }

        const double bin_width = BLOCK_WIDTH * height;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, bin,text_decoration18(i));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "red", "black");
        top += BIN_HEIGHT;
        i++;
    }
    svg_end();
}
