#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

bool leftDown=false,leftup=false;
Mat img;
Point cor0,cor1,cor2;
Rect box;


void mouse_call(int event,int x,int y,int,void*)
{
    Mat imgTemp = img.clone();
    if(event==EVENT_LBUTTONDOWN)
    {
        cout<<"Left Button Clicked "<<x<<","<<y<<endl;
        leftDown = true;
        leftup = true;
        cor0.x = x;
        cor0.y = y;
        cor1.x = x;
        cor1.y = y;
        cor2.x = x;
        cor2.y = y;
    }
    if(event==EVENT_LBUTTONUP)
    {
        cout<<"Left Button Released "<<x<<","<<y<<endl;
        leftup = true;
        leftDown = false;
        cor2.x = x;
        cor2.y = y;

        rectangle(imgTemp, cor0, cor2, Scalar(0,255,0), 2);
        imshow("Original",imgTemp);
    }
    if(leftDown==true&&leftup==false) //when the left button is down
    {
        cout<<"Left Down "<<x<<","<<y<<endl;
        
    }
    if(leftDown==true&&leftup==true) //when the selection is done
    { 
    	cout<<"None Down "<<x<<","<<y<<endl;

    	

    	cor0.x = cor1.x-(cor2.x-cor1.x);
        cor0.y = cor1.y-(cor2.y-cor1.y);
        if(cor0.x<0)
        	cor0.x=0;
        if(cor0.y<0)
        	cor0.y=0;
        
        if(cor2.x>imgTemp.cols)
        	cor2.x=imgTemp.cols;
        if(cor2.y<imgTemp.rows)
        	cor2.y=imgTemp.rows;

		cor2.x = x;
        cor2.y = y;
        rectangle(imgTemp, cor0, cor2, Scalar(0,255,0), 2);
        imshow("Original",imgTemp);

        
        box = Rect(cor0,cor2);
    }

    imgTemp.release();
}
int main(int argc, char** argv)
{
	
   VideoCapture cap(argv[1]);
   //Mat img;
   int pC=1, bC=1, cC=1, vC=1;
   
   while(1)
   {
		cap>>img;
		if(img.rows>480)
			resize(img, img, Size(), 0.5, 0.5);
		namedWindow("Original");
		imshow("Original",img);
		ostringstream per,car,bac, veh;
	   per<<"/home/arush/Codes/cropObject/person/";
	   car<<"/home/arush/Codes/cropObject/car/";
	   bac<<"/home/arush/Codes/cropObject/back/";
	   veh<<"/home/arush/Codes/cropObject/vehicle/";

		setMouseCallback("Original",mouse_call); //setting the mouse callback for selecting the region with mouse
		char key = char(waitKey());
        if(key=='q')
        	exit(0);
        if(key=='c')// car
        {
        	cout<<"Saved side of the car!\n";
        	imshow("box", img(box));
        	cC++;
        	car<<cC<<".jpg";
        	imwrite(car.str(), img(box));
        }
        if(key=='b')// car back
        {
        	cout<<"Saved backside of the car!\n";
        	imshow("box", img(box));
        	bC++;
        	bac<<bC<<".jpg";
        	imwrite(bac.str(), img(box));

        }	
        if(key=='p')// person
        {
        	
        	imshow("box", img(box));
        	pC++;
        	per<<pC<<".jpg";
        	imwrite(per.str(), img(box));
        	cout<<"Saved the person! \n"<<per.str();
        }
        if(key=='v')// vehicle
        {
        	cout<<"Saved the vehicle!\n";
        	imshow("box", img(box));
        	vC++;
        	veh<<vC<<".jpg";
        	imwrite(veh.str(), img(box));
        }	

   }
   

   return 0;
}
