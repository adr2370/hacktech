// tesscv.cpp:
// Using Tesseract API with OpenCV

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <tesseract/baseapi.h>
#include <iostream>

int main(int argc, char** argv)
{
    int words, wordLengths;
    char* out;
    int rotNum = 0;
    do {
	    // Load image
    	cv::Mat im = cv::imread(argv[1], 1);
    	if (!im.data)
    	{
    		std::cout << "Cannot open source image!" << std::endl;
    		return -1;
    	}
    	
    	//rotate the image rotNum times
    	/** Rotating the image after Warp */

        cv::Mat rotated, warp_dst, rot_mat;
        for (int i = 0; i < rotNum; i++) {
            warp_dst = cv::Mat::zeros( im.rows, im.cols, im.type() );
            /// Compute a rotation matrix with respect to the center of the image
            cv::Point center = cv::Point( warp_dst.cols/2, warp_dst.rows/2 );
            double angle = -90.0;
            double scale = 0.6;

            /// Get the rotation matrix with the specifications above
            rot_mat = cv::getRotationMatrix2D( center, angle, scale );

            /// Rotate the warped image
            cv::warpAffine( im, rotated, rot_mat, warp_dst.size() );
            im = rotated;
        }

    	cv::Mat gray;
    	cv::cvtColor(im, gray, CV_BGR2GRAY);
    	// ...other image pre-processing here...
        cv::Mat binary_image;
        cv::threshold(gray,binary_image, 50, 255, CV_THRESH_BINARY);
        //cv::imshow("binary_image",binary_image);
        //cv::waitKey(0);
    	// Pass it to Tesseract API
    	tesseract::TessBaseAPI tess;
    	//tess.Init("C:/Tesseract-OCR/tessdata/", "eng");
    	tess.Init(NULL, "eng", tesseract::OEM_DEFAULT);
    	tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
    	tess.SetImage((uchar*)gray.data, gray.cols, gray.rows, 1, gray.cols);

    	// Get the text
    	out = tess.GetUTF8Text();
	
        words = 0;
        wordLengths = 0;
        int currWordLength = 0;
        for (int i = 0; i < strlen(out); i++) {
            if (isalpha(out[i])) {
                currWordLength++;
            } else {
                if(currWordLength > 0) {
                    words++;
                    wordLengths += currWordLength;
                    currWordLength = 0;
                }
            }
        }
        rotNum++;
    } while (rotNum < 4 && words * 3 > wordLengths);
    std::cout << out << std::endl;

    //cv::namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
    //cv::imshow( "Display Image", gray );
    //cv::waitKey(0);
	return 0;
}
