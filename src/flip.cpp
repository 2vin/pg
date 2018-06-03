#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

Mat rotate(Mat src, double angle)
{
    Mat dst;
    Point2f pt(src.cols/2., src.rows/2.);    
    Mat r = getRotationMatrix2D(pt, -angle, 1.0);
    warpAffine(src, dst, r, Size(src.cols, src.rows));
    return dst;
}

int ind = 1;
int main(int argc, char** argv)
{
	cout<<"Usage: ./main image output_folder num_images\n";
	for(int i=1; i<=stoi(argv[3]); i++)
	{
		string imn = argv[1]+to_string(i)+".jpg";
		cout<<imn.c_str()<<endl;
		Mat im = imread(imn.c_str());
		Mat flipped;

		flip(im, flipped, 1);

		Mat rot10, rot10a;

		rot10 = rotate(im, 10);
		rot10a = rotate(im, -10);

		Mat frot10, frot10a;

		frot10 = rotate(flipped, 10);
		frot10a = rotate(flipped, -10);

		Mat croptl, cropbr;

		croptl = im(Rect(0,0,im.cols*0.9, im.rows*0.9));
		cropbr = im(Rect(im.cols*0.1,im.rows*0.1,im.cols*0.8, im.rows*0.8));
		
		Mat flippedtl, flippedbr;

		flippedtl = flipped(Rect(0,0,im.cols*0.9, im.rows*0.9));
		flippedbr = flipped(Rect(im.cols*0.1,im.rows*0.1,im.cols*0.8, im.rows*0.8));
		

		string ss;
		ss=argv[2]+to_string(stoi(argv[3])+ind++)+".jpg";
		imwrite(ss.c_str(), flipped);

		string ssr;
		ss=argv[2]+to_string(stoi(argv[3])+ind++)+".jpg";
		imwrite(ss.c_str(), rot10);

		
		string ssra;
		ss=argv[2]+to_string(stoi(argv[3])+ind++)+".jpg";
		imwrite(ss.c_str(), rot10a);

		string ssfr;
		ss=argv[2]+to_string(stoi(argv[3])+ind++)+".jpg";
		imwrite(ss.c_str(), frot10);

		string ssfra;
		ss=argv[2]+to_string(stoi(argv[3])+ind++)+".jpg";
		imwrite(ss.c_str(), frot10a);

		string sstl;
		ss=argv[2]+to_string(stoi(argv[3])+ind++)+".jpg";
		imwrite(ss.c_str(), croptl);

		string ssbr;
		ss=argv[2]+to_string(stoi(argv[3])+ind++)+".jpg";
		imwrite(ss.c_str(), cropbr);

		string ssftl;
		ss=argv[2]+to_string(stoi(argv[3])+ind++)+".jpg";
		imwrite(ss.c_str(), flippedtl);

		string ssfbr;
		ss=argv[2]+to_string(stoi(argv[3])+ind++)+".jpg";
		imwrite(ss.c_str(), flippedbr);
	}
	return 0;
}