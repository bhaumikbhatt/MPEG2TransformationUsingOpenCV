#include "affine.h"

int main( int argc, char **argv)
{


	/*----------------------- Declaring the variables ----------------------*/
	
	int i=0;
	int j=0;
	
	Point2f srcTri[3];
	Point2f dstTri[3];

	Mat rot_mat( 2, 3, CV_32FC1 );
	Mat warp_mat( 2, 3, CV_32FC1 );

	// Output variables
	Mat src, warp_dst, warp_rotate_dst;



	/*------------------------- Loading the Image --------------------------*/
	
	// Going to 'root' from 'Source_Code'

	if(chdir("..")!=EXIT_SUCCESS)
	{
		perror("Executing command 'cd ..'");
	}

	// Change Directory
	
	if(chdir("./Original_Frames/")!=EXIT_SUCCESS)
	{
		perror("Accessing Directory 'Original_Frames'");
	}

	// Load the Image
	
	src = imread( "Frame_no_02129.ppm", 1 );

	// Back to 'root'

	if(chdir("..")!=EXIT_SUCCESS)
	{
		perror("Executing command 'cd ..'");
	}



	/*---------------------- Affine Transform : Warp -----------------------*/

	// Setting up the output image parameters

	warp_dst = Mat::zeros( src.rows, src.cols, src.type() );


	// Setting parameters for matrix computation
	
	srcTri[0] = Point2f( 0,0 );
	srcTri[1] = Point2f( src.cols - 1, 0 );
	srcTri[2] = Point2f( 0, src.rows - 1 );
	srcTri[3] = Point2f( src.cols - 1, src.rows - 1 );

	dstTri[0] = Point2f( src.cols*1.00, src.rows*1.00 );
	dstTri[1] = Point2f( src.cols*0.00, src.rows*1.00 );
	dstTri[2] = Point2f( src.cols*1.00, src.rows*0.00 );
	dstTri[3] = Point2f( src.cols*0.00, src.rows*0.00 );


	// Calculate the Affine Transform matrix

	warp_mat = getAffineTransform( srcTri, dstTri );


	// Applying the Affine Transform to the src image

	warpAffine( src, warp_dst, warp_mat, warp_dst.size() );



	/*-------------------- Affine Transform : Rotate -----------------------*/

	// Compute the Rotation Matrix Parameters

	Point center = Point( warp_dst.cols/2, warp_dst.rows/2 );
	double angle = ROTATION_ANGLE;
	double scale = ISOTROPIC_SCALE_FACTOR;

	// Generate the Rotation Matrix

	rot_mat = getRotationMatrix2D( center, angle, scale );

	// Rotate the Image

	warpAffine( warp_dst, warp_rotate_dst, rot_mat, warp_dst.size() );


	/*------------------------- Storing the Image ---------------------------*/

	// Change Directory
	
	if(chdir("./Transformed_Frames/")!=EXIT_SUCCESS)
	{
		perror("Accessing Directory 'Transformed_Frames'");
	}

	// Storing the Image
	
	imwrite("src.ppm", warp_dst);

	// Back to 'root'

	if(chdir("..")!=EXIT_SUCCESS)
	{
		perror("Executing command 'cd ..'");
	}

	return EXIT_SUCCESS;
}
