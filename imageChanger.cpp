#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "bitmap/bitmap_image.hpp"

using namespace std;

double pi = 3.14159265359;
int num = 0;
int all = 0;
int pers = 9;
double eps = 1e-12;

void widthTransformation(bitmap_image* imageIN, bitmap_image* imageOUT){
	bitmap_image& imgIN = *imageIN;
	bitmap_image& imgOUT = *imageOUT;
	for(int y = 0; y < imgOUT.height(); y++){
		for(int x = 0; x < imgOUT.width(); x++){
			double tx = (double)x / imgOUT.width();
			rgb_t newColor; rgb_t oldColor;
			double r = 0, g = 0, b = 0;
			for(int nx = 0; nx < imgIN.width(); nx++){
				imgIN.get_pixel(nx, y, oldColor);
				double k = (pi*(tx*imgIN.width() - nx));
				double supl = (k==0)?1:(sin(k)/k);
				r += oldColor.red * supl;
				g += oldColor.green * supl;
				b += oldColor.blue * supl;
			}
			newColor.green = abs(g); newColor.red = abs(r); newColor.blue = abs(b);
			imgOUT.set_pixel(x, y, newColor);
		}
		cout << '\r' << ++num << '/' << all;
	}
	cout << '\n';
}
void heightTransformation(bitmap_image* imageIN, bitmap_image* imageOUT){
	bitmap_image& imgIN = *imageIN;
	bitmap_image& imgOUT = *imageOUT;
	for(int x = 0; x < imgOUT.width(); x++){
		for(int y = 0; y < imgOUT.height(); y++){
			double ty = (double)y / imgOUT.height();
			rgb_t newColor; rgb_t oldColor;
			double r = 0, g = 0, b = 0;
			for(int ny = 0; ny < imgIN.height(); ny++){
				imgIN.get_pixel(x, ny, oldColor);
				double k = (pi*(ty*imgIN.height() - ny));
				double supl = (k==0)?1:(sin(k)/k);
				r += oldColor.red * supl;
				g += oldColor.green * supl;
				b += oldColor.blue * supl;
			}
			newColor.green = abs(g); newColor.red = abs(r); newColor.blue = abs(b);
			imgOUT.set_pixel(x, y, newColor);
		}
		cout << '\r' << ++num << '/' << all;
	}
	cout << '\n';
}

int main(){
	double x = 0.5;
	double y = 0.5;
	string file, res_file;
	cout << "input image filename: ";
	cin >> file;
	cout << "input result image filename: ";
	cin >> res_file;
	cout << "enter the new image resolution in the proportions (x, y): ";
	cin >> x >> y;
	bitmap_image image(file);
	if(!image){
		cout << "[X] No such imagefile";
		return -1;
	}
	bitmap_image res_half_image(image.width()*x, image.height());
	bitmap_image res_image(res_half_image.width(), res_half_image.height()*y);
	
	::all = (res_half_image.height()) + (res_image.width());

	cout << "begin...\n";
	widthTransformation(&image, &res_half_image);
	res_half_image.save_image("half_" + res_file);
	cout << "half passed...\n";
	heightTransformation(&res_half_image, &res_image);
	cout << "end...\n";

	res_image.save_image(res_file);
	return 0;
}
