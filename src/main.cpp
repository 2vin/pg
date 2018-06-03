#include "libraries.hpp"
#include <stdio.h>
#include <stdlib.h>

// Program Mode variables
bool SearchMode = false;
bool captureMode = false;
bool GoMode = false;

int rotationAngle = -40;

// Click Positions
Point Search_TL, Search_BR;
Point Go_TL, Go_BR;

// Query image
Mat Query;

// Image Database
struct Product
{
	Mat im;
	int id;
	string location;
};

// Mouse Callback
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    if  ( event == EVENT_LBUTTONDOWN )
    {
        if(!SearchMode)
        {
        	if(x < Search_BR.x && x > Search_TL.x && y < Search_BR.y && y > Search_TL.y)
        	{
        		SearchMode = true;
        	}
        }
        else
        {
        	if(!captureMode)
        	{
        		if(x < Go_BR.x && x > Go_TL.x && y < Go_BR.y && y > Go_TL.y)
	        	{
	        		captureMode = true;
	        		GoMode = true;
	        	}
        	}
        }
    }
}

Mat rotate(Mat src, double angle)
{
    Mat dst;
    Point2f pt(src.cols/2., src.rows/2.);    
    Mat r = getRotationMatrix2D(pt, -angle, 1.0);
    warpAffine(src, dst, r, Size(src.cols, src.rows));
    return dst;
}

Mat drawSearchPage(Mat im)
{
	Mat temp = Mat::zeros(im.size(), CV_8UC4);
	Mat overlay = imread("./data/icon-png/search.png", CV_LOAD_IMAGE_UNCHANGED);

	Mat roi = temp(Rect(temp.cols/2 - overlay.cols/2, temp.rows/2 - overlay.rows/2, overlay.cols, overlay.rows));

	addWeighted(roi, 0.2, overlay, 0.8, 0, roi);

	roi.copyTo(temp(Rect(temp.cols/2 - overlay.cols/2, temp.rows/2 - overlay.rows/2, overlay.cols, overlay.rows)));

	Search_TL = Point(temp.cols/2 - 0.9*overlay.cols/2, temp.rows/2 - 0.9*overlay.rows/2);
	Search_BR = Point(temp.cols/2 + 0.9*overlay.cols/2 , temp.rows/2 + 0.9*overlay.rows/2);

	return temp;
}

Mat drawScanPage(Mat im)
{
	Mat temp = im.clone();
	// cvtColor(temp, temp, COLOR_BGR2BGRA);

	// Mat overlay = imread("./data/icon-png/scan.png", CV_LOAD_IMAGE_UNCHANGED);

	// Mat roi = temp(Rect(temp.cols/2 - overlay.cols/2, temp.rows/2 - overlay.rows/2, overlay.cols, overlay.rows));

	// addWeighted(roi, 0.8, overlay, 0.2, 0, roi);

	// roi.copyTo(temp(Rect(temp.cols/2 - overlay.cols/2, temp.rows/2 - overlay.rows/2, overlay.cols, overlay.rows)));

	Mat zero = Mat::zeros(im.size(), im.type());
	Mat r = temp(Rect(temp.cols/2-160, temp.rows/2-160, 320, 320));
	r.copyTo(zero(Rect(temp.cols/2-160, temp.rows/2-160, 320, 320)));
	return zero;
}

Mat drawLoaderPage(Mat im)
{
	Mat temp = im.clone();
	cvtColor(temp, temp, COLOR_BGR2BGRA);

	Mat overlay = imread("./data/icon-png/loader.png", CV_LOAD_IMAGE_UNCHANGED);

	overlay = rotate(overlay, rotationAngle);
	rotationAngle += 5;
	if(rotationAngle > 360)
	{	
		rotationAngle -= 360 ;
	}

	Mat roi = temp(Rect(temp.cols/2 - overlay.cols/2, temp.rows/2 - overlay.rows/2, overlay.cols, overlay.rows));

	addWeighted(roi, 0.7, overlay, 0.3, 0, roi);

	roi.copyTo(temp(Rect(temp.cols/2 - overlay.cols/2, temp.rows/2 - overlay.rows/2, overlay.cols, overlay.rows)));

	cvtColor(temp, temp, COLOR_BGRA2RGB);

	if(!captureMode && rotationAngle > 320)
	{
		captureMode = true;
	}

	return temp;
}

Mat drawGoPage(Mat im)
{
	Mat temp = im.clone();
	cvtColor(temp, temp, COLOR_BGR2BGRA);

	Mat overlay = imread("./data/icon-png/go.png", CV_LOAD_IMAGE_UNCHANGED);

	overlay.copyTo(temp(Rect(temp.cols*5/6 - overlay.cols/2, temp.rows/2 - overlay.rows/2, overlay.cols, overlay.rows)));
	
	Go_TL = Point(temp.cols*5/6 - 0.9*overlay.cols/2, temp.rows/2 - 0.9*overlay.rows/2);
	Go_BR = Point(temp.cols*5/6 + 0.9*overlay.cols/2 , temp.rows/2 + 0.9*overlay.rows/2);

	return temp;
}

Mat drawResultPage(Mat im, string output)
{
	Mat temp = im.clone();

	putText(temp, output, Point(temp.cols*0.55, temp.rows*0.3),  FONT_HERSHEY_SIMPLEX, 1.2, Scalar(255, 255, 255), 3);
	putText(temp, "Section - Food", Point(temp.cols*0.55, temp.rows*0.5),  FONT_HERSHEY_SIMPLEX, 1.0, Scalar(200, 200, 200), 2);
	putText(temp, "Row    - 2", Point(temp.cols*0.55, temp.rows*0.7),  FONT_HERSHEY_SIMPLEX, 1.0, Scalar(200, 200, 200), 2);
	
	return temp;
}

string GetStdoutFromCommand(string cmd) {
	string data;
	FILE * stream;
	const int max_buffer = 256;
	char buffer[max_buffer];
	cmd.append(" 2>&1");

	stream = popen(cmd.c_str(), "r");
	if (stream) {
		while (!feof(stream))
		if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
		pclose(stream);
	}
	return data;
}

vector<string> ParseString(string in)
{
	stringstream ss(in);
	vector<string> result;
	while( ss.good() )
	{
	    string substr;
	    getline( ss, substr, ',' );
	    result.push_back( substr );
	}
	return result;
}

int main(int argc, char** argv) 
{
	VideoCapture cap(1);
	Mat im;
	cap >> im;
	im = im(Rect(im.cols/2-320, im.rows/2-180, 640, 360));

	Mat SearchPage = drawSearchPage(im);

    namedWindow("Product Search", WINDOW_NORMAL);
    cv::setWindowProperty("Product Search", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);

    setMouseCallback("Product Search", CallBackFunc, NULL);

	while(waitKey(10)<0)
	{
		cap >> im;
		im = im(Rect(im.cols/2-320, im.rows/2-180, 640, 360));

		if(SearchMode)
		{
			Mat ScanPage = drawScanPage(im);

			if(!captureMode)
			{	
				// Mat LoadPage = drawLoaderPage(ScanPage);
				Mat LoadPage = drawGoPage(ScanPage);
				imshow("Product Search", LoadPage);
				moveWindow("Product Search", 0, 0);
			}
			else
			{
				// if(!GoMode)
				{
					if(Query.empty())
					{
						Query = Mat::zeros(im.size(), im.type());
						imwrite("./data/query/query.jpg", im(Rect(im.cols/2-160, im.rows/2-160, 320, 320)));
						im(Rect(im.cols/2-160, im.rows/2-160, 320, 320)).copyTo(Query(Rect(im.cols/2-300, im.rows/2-160, 320, 320)));

						// Caffe Command
						string str = "../caffe/build/examples/cpp_classification/classification.bin '/home/mouz/Desktop/models/deploy.prototxt' '/home/mouz/Desktop/models/snapshot_iter_100.caffemodel' '/home/mouz/Desktop/models/mean.binaryproto' '/home/mouz/Desktop/models/labels.txt' '/home/mouz/Desktop/PG/code-MV/data/query/query.jpg'";
					    const char *command = str.c_str();  
					 	string output = GetStdoutFromCommand(command);
					 	vector<string> result = ParseString(output);
					 	cout<<"Result is : "<<result[1]<<endl;
						Query = drawResultPage(Query, result[1]);
					}
					
					imshow("Product Search", Query);
					moveWindow("Product Search", 0, 0);
					
					waitKey(3000);

					GoMode = false;
					captureMode = false;
					SearchMode = false;

					rotationAngle = -40;
					Query.release();
				}
			}
		}
		else
		{
			imshow("Product Search", SearchPage);
			moveWindow("Product Search", 0, 0);
		}
	}

	return 0;
}
