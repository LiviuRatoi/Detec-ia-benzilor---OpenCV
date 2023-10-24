#include "opencv2/opencv.hpp"
#include<opencv2/highgui.hpp>

using namespace cv;
using namespace std;
int main(int argc, char* argv[])
{

	VideoCapture video(0);
	video.open("proiect_pi.mp4");

	if (!video.isOpened())
		return -1;

	Mat frame;
	video.read(frame);
	Mat edges;
	Mat edges_out;
	Mat edges_outP;
	Mat out;

	int frameWidth = video.get(cv::CAP_PROP_FRAME_WIDTH);
	int frameHeigth = video.get(cv::CAP_PROP_FRAME_HEIGHT);

	char esc_key = 0;


	while (video.read(frame) && esc_key != 27)
	{
		imshow("Video original", frame);

		Canny(frame, edges, 762, 1132);

		cvtColor(edges, edges_out, COLOR_GRAY2BGR);

		edges_outP = edges_out.clone();


		std::vector <Vec4i> linesP;
		HoughLinesP(edges, linesP, 1, CV_PI / 150, 1, 0, 1);

		//Draw the lines

		for (size_t i = 0; i < linesP.size(); i++)
		{
			Vec4i l = linesP[i];
			line(edges_outP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 128, 0), 3, LINE_AA);
			line(frame, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 128, 0), 3, LINE_AA);
		}

		imshow("Zona de interes - Canny", edges);

		imshow("Marcarea liniilor - Hough TRansform ", edges_outP * 7);

		imshow("Detectie linii", frame);
		esc_key = waitKey(10);
	}

	if (esc_key != 27) {               // if the user did not press esc (i.e. we reached the end of the video)
		waitKey(0);                         // hold the windows open to allow the "end of video" message to show
	}

	video.release();

	// Destroy all windows
	destroyAllWindows();

	system("PAUSE");
	return 0;

}