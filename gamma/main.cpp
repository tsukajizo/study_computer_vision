
#include "highgui.h"

void cv_ApplyLUT(IplImage* src, IplImage* dst, uchar *lut);
void cv_CreateGammaTable(double gamma, uchar *lut);

int main(int argc , char** argv){
  IplImage* img = cvLoadImage(argv[1]);
  IplImage* out = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,3);
  uchar LUT[256];
  cv_CreateGammaTable(2.2,LUT);
  cv_ApplyLUT(img,out,LUT);

  cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE );
  cvShowImage( "Exapmle1" , img );
  cvNamedWindow("Example2", CV_WINDOW_AUTOSIZE );
  cvShowImage( "Exapmle2" , out );
  cvWaitKey(0);
  cvReleaseImage(&img);
  cvReleaseImage(&out);
  cvDestroyWindow( "Example1" );
  cvDestroyWindow( "Example2" );
}

void cv_CreateGammaTable(double gamma, uchar *lut){

      //ガンマ補正テーブルの作成
      int i;
      for (i = 0; i < 256; i++){
          lut[i] = (int)(pow((double)i / 255.0, 1.0 / gamma) * 255.0);
      }
}

void cv_ApplyLUT(IplImage* src, IplImage* dst, uchar *lut){
    //CvMatへ変換
    CvMat lut_mat = cvMat(1, 256, CV_8UC1, lut);
    //ルックアップテーブル変換
    cvLUT(src, dst, &lut_mat);
}
