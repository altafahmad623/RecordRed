#include <bits/stdc++.h>
#include <dirent.h>
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/cvconfig.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int extractRed()
{
    string vidname;
    cout<<"Enter the video to be Done\n";
    cin>>vidname;
    //open the video file for reading
    VideoCapture cap("//home//altaf//Video Effect//VDO//"+vidname+".avi");

    // if not success, exit program
    if (cap.isOpened() == false)
    {
        cout << "Cannot open the video file" << endl;
        cin.get(); //wait for any key press
        //return -1;
    }


    VideoWriter write;
    VideoCapture c(0);
    //Define names of the window
    String window_name_of_original_video = "Original Video";
    String red_converted = "Video with the Extracted red frames";
    string filename = "//home//altaf//Video Effect//VDO//"+vidname+"_redextract.avi";
    // Create a window with above namesint fcc = CV_FOURCC('D','I','V','3');
    int fcc = CV_FOURCC('D','I','V','3');
	int fps = 25;
	Size fsize (c.get(CV_CAP_PROP_FRAME_WIDTH),c.get(CV_CAP_PROP_FRAME_HEIGHT));

	write = VideoWriter(filename,fcc,fps,fsize);

    namedWindow(window_name_of_original_video, WINDOW_NORMAL);
    namedWindow(red_converted, WINDOW_NORMAL);

    while (true)
    {
        Mat frame;
        bool bSuccess = cap.read(frame); // read a new frame from video 
        if (bSuccess == false)
        {
            cout << "Found the end of the video" << endl;
            break;
        }

        
        vector<Mat> grayPlanes;
        split(frame, grayPlanes);
        Mat red_Frame = grayPlanes[2];
        
        write.write(red_Frame);
        //show the frames in the created windows
        imshow(window_name_of_original_video, frame);
        //imshow(red_converted,grayPlanes[0]);
        //imshow(red_converted, grayPlanes[1]);
        imshow(red_converted, grayPlanes[2]);

        //wait for for 10 ms until any key is pressed.  
        //If the 'Esc' key is pressed, break the while loop.
        //If the any other key is pressed, continue the loop 
        //If any key is not pressed withing 10 ms, continue the loop
        if (waitKey(10) == 27)
        {
            cout << "Esc key is pressed by user. Stoppig the video" << endl;
            break;
        }
    }
    return 0;
}
int capture()
{
	VideoCapture c(0);
	VideoWriter write;
	
	if(!c.isOpened()){cout<<"Error while opening your webcam\n";cin.ignore();return -1;}
	string winName = "Feed";
	string vidname;
	cout<<"Enter Video Title\n";
	cin>>vidname;
	string filename = "//home//altaf//Video Effect//VDO//"+vidname+".avi";
	int fcc = CV_FOURCC('D','I','V','3');
	int fps = 25;
	cv::Size fsize (c.get(CV_CAP_PROP_FRAME_WIDTH),c.get(CV_CAP_PROP_FRAME_HEIGHT));

	write = VideoWriter(filename,fcc,fps,fsize);

	if(!write.isOpened()){cout<<"Error while saving your video\n";cin.ignore();return -1;}
	time_t start, end;

	Mat feed;
	int pref_scorecounter = 0;
	int pref_timeduration;
    time_t pref_timestart = time(0);
    do
	{
        pref_scorecounter++;
        time_t pref_timefinish = time(0);
        pref_timeduration = pref_timefinish - pref_timestart;
		bool success = c.read(feed);
		if(!success){cout<<"Error while processing your video\n";cin.ignore();return -1;}
		write.write(feed);
		imshow(winName,feed);
		switch(waitKey(10))
		{
		case 27:
			return 0;
		}
    } while( pref_timeduration < 16 );

}
void gaussianFilter()
{
    string vidname;
    cout<<"Enter the video to be Done\n";
    cin>>vidname;
    //open the video file for reading
    VideoCapture cap("//home//altaf//Video Effect//VDO//"+vidname+".avi");

    // if not success, exit program
    if (cap.isOpened() == false)
    {
        cout << "Cannot open the video file" << endl;
        cin.get(); //wait for any key press
        //return -1;
    }


    VideoWriter write;
    VideoCapture c(0);
    //Define names of the window
    String window_name_of_original_video = "Original Video";
    String window_name_of_video_blurred_with_5x5_kernel = "Video Blurred with 5 x 5 Gaussian Kernel";
    string filename = "//home//altaf//Video Effect//VDO//"+vidname+"_blurred.avi";
    // Create a window with above namesint fcc = CV_FOURCC('D','I','V','3');
    int fcc = CV_FOURCC('D','I','V','3');
	int fps = 25;
	cv::Size fsize (c.get(CV_CAP_PROP_FRAME_WIDTH),c.get(CV_CAP_PROP_FRAME_HEIGHT));

	write = VideoWriter(filename,fcc,fps,fsize);

    namedWindow(window_name_of_original_video, WINDOW_NORMAL);
    namedWindow(window_name_of_video_blurred_with_5x5_kernel, WINDOW_NORMAL);

    while (true)
    {
        Mat frame;
        bool bSuccess = cap.read(frame); // read a new frame from video 
        if (bSuccess == false)
        {
            cout << "Found the end of the video" << endl;
            break;
        }

        //Blur the frame with 5x5 Gaussian kernel
        Mat frame_blurred_with_5x5_kernel;
        GaussianBlur(frame, frame_blurred_with_5x5_kernel, Size(5, 5), 0);
        write.write(frame_blurred_with_5x5_kernel);
        //show the frames in the created windows
        imshow(window_name_of_original_video, frame);
        imshow(window_name_of_video_blurred_with_5x5_kernel, frame_blurred_with_5x5_kernel);

        //wait for for 10 ms until any key is pressed.  
        //If the 'Esc' key is pressed, break the while loop.
        //If the any other key is pressed, continue the loop 
        //If any key is not pressed withing 10 ms, continue the loop
        if (waitKey(10) == 27)
        {
            cout << "Esc key is pressed by user. Stoppig the video" << endl;
            break;
        }
    }
}
class logMan
{
    public:
        
        logMan()
        {
            accessGranted = 0;
        }
        bool login()//function to login when username and password are known
        {
            cout<<"Enter Username and Pass:\nUser : ";
            cin>>usernameAtt;
            //userName = retrieveFile(usernameAtt+".dat");
            ifstream read;
            read.open("data//"+usernameAtt+".dat");
            read >> userName;
            read >> password;
            //cout<<userName<<endl;
            //getline(read, userName);
            //getline(read,password);
            if(usernameAtt==userName){
                cout<<"Password : ";
                cin>>passAtt;
                //password = retrieveFile(passAtt+".dat");
                if(passAtt== password)
                {
                    cout<<"Welcome\n";
                    return true;
                }
                else
                {
                    cout<<"Wrong password"<<endl;
                    return false;
                    login();
                }
                
            }
            else
            {
                cout<<"Wrong Username"<<endl;
                return false;
                login();
            }
            
        }
        string retrieveFile(string p_file)
        {
            string line;
            fstream file;
            file.open(p_file, ios::in);
            if(file.is_open())
            {
                getline(file,line);
            }
            file.close();
            return line;
        }

    private:
        string password ;
        string userName ;
        string usernameAtt;
        string passAtt;
        bool accessGranted;
};
class regis
{
    public:
        void regtere()
        {
            cout<<"Enter New User Name\n";
            cin>>username;
            cout<<"Enter Your password\n";
            cin>>password;
            fstream file;
            file.open("data//"+username+".dat",ios::out);
            file << username <<"\n"<< password;
            file.close();
        }
    private:
        string username, password;    
};
void peep()
{
    DIR *dir;
    struct  dirent *ent;
    if ((dir = opendir ("//home//altaf//Video Effect//VDO")) != NULL) 
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) 
        {
            printf ("%s\n", ent->d_name);
        }
        closedir (dir);
    } 
    else 
    {
        /* could not open directory */
        perror ("");
        //return EXIT_FAILURE;
    }
    
}
int main()
{
    int k=1,t=1;
    while(k!=0)
    {
        cout<<"Press 1 to login\n2 to register\n3 to Exit\n";
        cin>>k;
        if(k==1)
        {
            logMan loginManager;
            if(loginManager.login())
            {
                while(t!=0)
                {
                    cout<<"Select: \n1 to record 10 sec video\n2 to take red frame\n3 to Apply Gausian Filter\n4 to look at the files created\nAny other key to exit\n";
                    cin>>t;
                    switch (t)
                    {
                    case 1:
                        cout<<"The CAM will now record the video\n";
                        capture();
                        break;
                    case 2:
                        cout<<"Red Filter will now be applied\n";    
                        extractRed();
                        break;
                    case 3:
                        cout<<"Gaussian Filter\n";
                        gaussianFilter();
                        break;  
                    case 4:
                        cout<<"THe files created are:\n";
                        peep();
                        break;      
                    default:
                        t=0;
                        break;
                    }
                }
            }
            else
            {
                cout<<"Wrong User or password\n";
                continue;
            }
            
        }
        else if(k==2)
        {
            regis regMan;
            regMan.regtere();
        }   
        else
        {
            return 0;
        }
        

    }


}