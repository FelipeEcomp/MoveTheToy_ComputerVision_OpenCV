/*
 *
 * Feito por: Felipe Pinheiro e Bianca Santana
 *
 */

#include <sstream>
#include <string>
#include <iostream>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

//Valores mínimos e máximos do filtro HSV (regula o thresholding pelos trackbars)
//cabeça
int H_MIN1 = 0;//19
int H_MAX1 = 256;//218
int S_MIN1 = 0;//170
int S_MAX1 = 256;//256
int V_MIN1 = 0;//0
int V_MAX1 = 236;//236

//braço esquerdo
int H_MIN2 = 47;
int H_MAX2 = 83;
int S_MIN2 = 32;
int S_MAX2 = 256;
int V_MIN2 = 75;
int V_MAX2 = 236;

//braço direito
int H_MIN3 = 99;
int H_MAX3 = 114;
int S_MIN3 = 211;
int S_MAX3 = 256;
int V_MIN3 = 0;
int V_MAX3 = 236;

//braço corpo
int H_MIN4 = 115;//172
int H_MAX4 = 256;//256
int S_MIN4 = 151;//188
int S_MAX4 = 256;//256
int V_MIN4 = 0;//0
int V_MAX4 = 236;//236


//Largura e Altura
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;

//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS=50;

//Tamanho minimo e maximo do objeto
const int MIN_OBJECT_AREA = 20*20; // caso o objeto seja menor, isso sera considerado ruido
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;

//Nomes das janelas
const string windowName = "Original";
const string windowName1 = "HSV";
const string windowName2 = "ThresholdedCabeca"; //1
const string windowName3 = "ThresholdedBracoEsq"; //2
const string windowName4 = "ThresholdedBracoDir"; //3
const string windowName5 = "ThresholdedCorpo"; //4


//const string windowName3 = "After Morphological Operations";
const string trackbarWindowName1 = "TrackbarsCabeca";
const string trackbarWindowName2 = "TrackbarsBracoEsq";
const string trackbarWindowName3 = "TrackbarsBracoDir";
const string trackbarWindowName4 = "TrackbarsCorpo";

void on_trackbar( int, void* )
{




}
string intToString(int number){ //função para int -> string, para as coordenadas


    std::stringstream ss;
    ss << number;
    return ss.str();
}

void createTrackbars(){
   //método para criar os trackbars

//cabeça
    namedWindow(trackbarWindowName1,0);
    //Cria os trackbars
    char TrackbarName1[50];
    sprintf( TrackbarName1, "H_MIN", H_MIN1);
    sprintf( TrackbarName1, "H_MAX", H_MAX1);
    sprintf( TrackbarName1, "S_MIN", S_MIN1);
    sprintf( TrackbarName1, "S_MAX", S_MAX1);
    sprintf( TrackbarName1, "V_MIN", V_MIN1);
    sprintf( TrackbarName1, "V_MAX", V_MAX1);

    //Cria as trackbars na janela

    createTrackbar( "H_MIN", trackbarWindowName1, &H_MIN1, H_MAX1, on_trackbar );
    createTrackbar( "H_MAX", trackbarWindowName1, &H_MAX1, H_MAX1, on_trackbar );
    createTrackbar( "S_MIN", trackbarWindowName1, &S_MIN1, S_MAX1, on_trackbar );
    createTrackbar( "S_MAX", trackbarWindowName1, &S_MAX1, S_MAX1, on_trackbar );
    createTrackbar( "V_MIN", trackbarWindowName1, &V_MIN1, V_MAX1, on_trackbar );
    createTrackbar( "V_MAX", trackbarWindowName1, &V_MAX1, V_MAX1, on_trackbar );


    //braço esquerdo
    namedWindow(trackbarWindowName2,0);
    //Cria os trackbars
    char TrackbarName2[50];
    sprintf( TrackbarName2, "H_MIN", H_MIN2);
    sprintf( TrackbarName2, "H_MAX", H_MAX2);
    sprintf( TrackbarName2, "S_MIN", S_MIN2);
    sprintf( TrackbarName2, "S_MAX", S_MAX2);
    sprintf( TrackbarName2, "V_MIN", V_MIN2);
    sprintf( TrackbarName2, "V_MAX", V_MAX2);

    //Cria as trackbars na janela

    createTrackbar( "H_MIN", trackbarWindowName2, &H_MIN2, H_MAX2, on_trackbar );
    createTrackbar( "H_MAX", trackbarWindowName2, &H_MAX2, H_MAX2, on_trackbar );
    createTrackbar( "S_MIN", trackbarWindowName2, &S_MIN2, S_MAX2, on_trackbar );
    createTrackbar( "S_MAX", trackbarWindowName2, &S_MAX2, S_MAX2, on_trackbar );
    createTrackbar( "V_MIN", trackbarWindowName2, &V_MIN2, V_MAX2, on_trackbar );
    createTrackbar( "V_MAX", trackbarWindowName2, &V_MAX2, V_MAX2, on_trackbar );

    //braço direito
    namedWindow(trackbarWindowName3,0);
    //Cria os trackbars
    char TrackbarName3[50];
    sprintf( TrackbarName3, "H_MIN", H_MIN3);
    sprintf( TrackbarName3, "H_MAX", H_MAX3);
    sprintf( TrackbarName3, "S_MIN", S_MIN3);
    sprintf( TrackbarName3, "S_MAX", S_MAX3);
    sprintf( TrackbarName3, "V_MIN", V_MIN3);
    sprintf( TrackbarName3, "V_MAX", V_MAX3);

    //Cria as trackbars na janela

    createTrackbar( "H_MIN", trackbarWindowName3, &H_MIN3, H_MAX3, on_trackbar );
    createTrackbar( "H_MAX", trackbarWindowName3, &H_MAX3, H_MAX3, on_trackbar );
    createTrackbar( "S_MIN", trackbarWindowName3, &S_MIN3, S_MAX3, on_trackbar );
    createTrackbar( "S_MAX", trackbarWindowName3, &S_MAX3, S_MAX3, on_trackbar );
    createTrackbar( "V_MIN", trackbarWindowName3, &V_MIN3, V_MAX3, on_trackbar );
    createTrackbar( "V_MAX", trackbarWindowName3, &V_MAX3, V_MAX3, on_trackbar );

    //Corpo
    namedWindow(trackbarWindowName4,0);
    //Cria os trackbars
    char TrackbarName4[50];
    sprintf( TrackbarName4, "H_MIN", H_MIN4);
    sprintf( TrackbarName4, "H_MAX", H_MAX4);
    sprintf( TrackbarName4, "S_MIN", S_MIN4);
    sprintf( TrackbarName4, "S_MAX", S_MAX4);
    sprintf( TrackbarName4, "V_MIN", V_MIN4);
    sprintf( TrackbarName4, "V_MAX", V_MAX4);

    //Cria as trackbars na janela

    createTrackbar( "H_MIN", trackbarWindowName4, &H_MIN4, H_MAX4, on_trackbar );
    createTrackbar( "H_MAX", trackbarWindowName4, &H_MAX4, H_MAX4, on_trackbar );
    createTrackbar( "S_MIN", trackbarWindowName4, &S_MIN4, S_MAX4, on_trackbar );
    createTrackbar( "S_MAX", trackbarWindowName4, &S_MAX4, S_MAX4, on_trackbar );
    createTrackbar( "V_MIN", trackbarWindowName4, &V_MIN4, V_MAX4, on_trackbar );
    createTrackbar( "V_MAX", trackbarWindowName4, &V_MAX4, V_MAX4, on_trackbar );


}
void drawObject1(int x, int y,Mat &frame){
   //Desenha algo quando o objeto eh reconhecido
    circle(frame,Point(x,y),20,Scalar(255,0,0),2);
    putText(frame,intToString(x)+","+intToString(y),Point(x,y+30),1,1,Scalar(0,255,0),2);
}
void drawObject2(int x, int y,Mat &frame){
   //Desenha algo quando o objeto eh reconhecido
    circle(frame,Point(x,y),20,Scalar(0,255,0),2);
    putText(frame,intToString(x)+","+intToString(y),Point(x,y+30),1,1,Scalar(0,255,0),2);
}
void drawObject3(int x, int y,Mat &frame){
   //Desenha algo quando o objeto eh reconhecido
    circle(frame,Point(x,y),20,Scalar(0,0,255),2);
    putText(frame,intToString(x)+","+intToString(y),Point(x,y+30),1,1,Scalar(0,255,0),2);
}

void drawObject4(int x, int y,Mat &frame){
   //Desenha algo quando o objeto eh reconhecido
    circle(frame,Point(x,y),20,Scalar(0,235,255),2);
    putText(frame,intToString(x)+","+intToString(y),Point(x,y+30),1,1,Scalar(0,255,0),2);
}

void morphOps(Mat &thresh){

    //Função para usar o diate e erode, melhorando assim o thresholding

    Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
    //dilate with larger element so make sure object is nicely visible
    Mat dilateElement = getStructuringElement( MORPH_RECT,Size(8,8));

    erode(thresh,thresh,erodeElement);
    erode(thresh,thresh,erodeElement);


    dilate(thresh,thresh,dilateElement);
    dilate(thresh,thresh,dilateElement);



}

int main()
{

    bool trackObjects = true; // checa se o objeto foi detectado
    bool useMorphOps = true; //decide se vai usar o dilate e erode


    Mat HSVCabeca;
    Mat HSVBracoEsq;
    Mat HSVBracoDir;
    Mat HSVCorpo;

    Mat threshold1;
    Mat threshold2;
    Mat threshold3;
    Mat threshold4;

    Mat imageROIFace;
    Mat maskFace;
    Mat mickeyFace;

    Mat imageROIEsq;
    Mat maskEsq;
    Mat mickeyEsq;

    Mat imageROIDir;
    Mat maskDir;
    Mat mickeyDir;

    Mat imageROICorpo;
    Mat maskCorpo;
    Mat mickeyCorpo;



    //localização do objeto
    int x1=0, y1=0;
    int x2=0, y2=0;
    int x3=0, y3=0;
    int x4=0, y4=0;

    //chama os trackbars para o HSV
    createTrackbars();

    //mickey
    mickeyFace = imread("C:\\Users\\Felipe\\Desktop\\ComputacaoVisual\\Animation\\claudinhoCabeca.png");
    mickeyEsq = imread("C:\\Users\\Felipe\\Desktop\\ComputacaoVisual\\Animation\\claudinhoMao1.png");
    mickeyDir = imread("C:\\Users\\Felipe\\Desktop\\ComputacaoVisual\\Animation\\claudinhoMao2.png");
    mickeyCorpo = imread("C:\\Users\\Felipe\\Desktop\\ComputacaoVisual\\Animation\\claudinhoCorpo.png");

    //mask
    maskFace = imread("C:\\Users\\Felipe\\Desktop\\ComputacaoVisual\\Animation\\claudinhoCabecaMascara.png",0);
    maskEsq = imread("C:\\Users\\Felipe\\Desktop\\ComputacaoVisual\\Animation\\claudinhoMao1Mascara.png",0);
    maskDir = imread("C:\\Users\\Felipe\\Desktop\\ComputacaoVisual\\Animation\\claudinhoMao2Mascara.png",0);
    maskCorpo = imread("C:\\Users\\Felipe\\Desktop\\ComputacaoVisual\\Animation\\claudinhoCorpoMascara.png",0);


   //pega video da camera
    VideoCapture capture(0);
    if(!capture.isOpened()){
           cout << "Erro ao abrir video" << endl;
           return -1;
    }

    int frame_width=   capture.get(CV_CAP_PROP_FRAME_WIDTH);
    int frame_height=   capture.get(CV_CAP_PROP_FRAME_HEIGHT);

    //cria a variável para gravar o video, contendo o caminho onde será salvo o video
    VideoWriter video("C:\\Users\\Felipe\\Desktop\\ComputacaoVisual\\Animation\\Boneco.avi",-1,10, Size(frame_width,frame_height),true);
    if ( !video.isOpened() )
      {
           cout << "ERRO: Falha ao escrever video" << endl;
           return -1;
      }


    while(1){
        //matriz para guardar cada frame
        Mat cameraFeed;
        Mat fundo;

        //armazena os frames na matriz
        capture >> cameraFeed;

        //fundo do boneco
        fundo = imread("C:\\Users\\Felipe\\Desktop\\ComputacaoVisual\\Animation\\fundo.png");


        //printa um texto na tela
        putText(fundo,"Feito por: Felipe e Bianca",Point(15,463),1,1,Scalar(0,255,0),1);
        putText(fundo,"Mova os membros do nosso amigo!!!",Point(0,50),1,2,Scalar(0,0,255),1);


        //converte os frames de BGR para HSV
        cvtColor(cameraFeed,HSVCabeca,COLOR_BGR2HSV);
        cvtColor(cameraFeed,HSVBracoEsq,COLOR_BGR2HSV);
        cvtColor(cameraFeed,HSVBracoDir,COLOR_BGR2HSV);
        cvtColor(cameraFeed,HSVCorpo,COLOR_BGR2HSV);


        //filtra de HSV para a matriz threshold
        inRange(HSVCabeca,Scalar(H_MIN1,S_MIN1,V_MIN1),Scalar(H_MAX1,S_MAX1,V_MAX1),threshold1);
        //filtra de HSV para a matriz threshold
        inRange(HSVBracoEsq,Scalar(H_MIN2,S_MIN2,V_MIN2),Scalar(H_MAX2,S_MAX2,V_MAX2),threshold2);
        //filtra de HSV para a matriz threshold
        inRange(HSVBracoDir,Scalar(H_MIN3,S_MIN3,V_MIN3),Scalar(H_MAX3,S_MAX3,V_MAX3),threshold3);
        //filtra de HSV para a matriz threshold
        inRange(HSVCorpo,Scalar(H_MIN4,S_MIN4,V_MIN4),Scalar(H_MAX4,S_MAX4,V_MAX4),threshold4);

        //faz a operação de dilate e erode para retirar ruido
        if(useMorphOps){
        morphOps(threshold1);
        morphOps(threshold2);
        morphOps(threshold3);
        morphOps(threshold4);
        }


        //braço esquerdo na cena
        imageROIEsq = fundo(Rect (110, 220, mickeyEsq.cols, mickeyEsq.rows));
        mickeyEsq.copyTo(imageROIEsq, maskEsq);

        //braço direito na cena
        imageROIDir = fundo(Rect (360, 220, mickeyDir.cols, mickeyDir.rows));
        mickeyDir.copyTo(imageROIDir, maskDir);

        //corpo na cena
        imageROICorpo = fundo(Rect (250, 200, mickeyCorpo.cols, mickeyCorpo.rows));
        mickeyCorpo.copyTo(imageROICorpo, maskCorpo);

        //coloca a face na cena
        imageROIFace = fundo(Rect (250, 100, mickeyFace.cols, mickeyFace.rows));
        mickeyFace.copyTo(imageROIFace, maskFace);



        if(trackObjects){
            Mat temp1;
            Mat temp2;
            Mat temp3;
            Mat temp4;

            //copia temporaria
            threshold1.copyTo(temp1);
            threshold2.copyTo(temp2);
            threshold3.copyTo(temp3);
            threshold4.copyTo(temp4);



            vector< vector<Point> > contours1;
            vector< vector<Point> > contours2;
            vector< vector<Point> > contours3;
            vector< vector<Point> > contours4;
            vector<Vec4i> hierarchy1;
            vector<Vec4i> hierarchy2;
            vector<Vec4i> hierarchy3;
            vector<Vec4i> hierarchy4;


            //encontra os contornos da imagem
            findContours(temp1,contours1,hierarchy1,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
            findContours(temp2,contours2,hierarchy2,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
            findContours(temp3,contours3,hierarchy3,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
            findContours(temp4,contours4,hierarchy4,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );


            //utiliza o metodo Moments para encontrar o objeto fltrado
            double refArea1 = 0;
            double refArea2 = 0;
            double refArea3 = 0;
            double refArea4 = 0;

            bool CabecaFound = false;
            bool BracoEsqFound = false;
            bool BracoDirFound = false;
            bool CorpoFound = false;


            if (hierarchy2.size() > 0) {
                int numObjects2 = hierarchy2.size();

                //se o numero de objetos for muito grande, isso sera consderado ruido
                if(numObjects2<MAX_NUM_OBJECTS){
                    for (int index = 0; index >= 0; index = hierarchy2[index][0]) {

                        Moments moment2 = moments((cv::Mat)contours2[index]);
                        double area2 = moment2.m00;

                        //se a area do objeto é menor que 20 px by 20px, isso eh ruido
                        //se a área é 3/2 do tamanho da imagem, filtro mal ajustado
                        if(area2>MIN_OBJECT_AREA && area2<MAX_OBJECT_AREA && area2>refArea2){
                            x2 = moment2.m10/area2;
                            y2 = moment2.m01/area2;

                            BracoEsqFound = true;
                            refArea2 = area2;

                        }else{
                            BracoEsqFound = false;
                       // drawBracoEsqBoneco(338,240,cameraFeed);
                    }

                    }
                    //incrementa a quantidade
                    int quant  = 0;
                    char text[255];
                    sprintf(text, "Quantidade %d", (int)quant);


                    if(BracoEsqFound ==true){ //se apareceu o objeto

                        //putText(cameraFeed,"REC",Point(0,50),2,1,Scalar(0,0,255),2);
                        //desenha um objeto
                        drawObject2(x2,y2,cameraFeed);

                            Mat r;
                            int len = max(mickeyEsq.cols, mickeyEsq.rows);
                                Point2f pt(139, 5);

                                //limita a revolução da braço dir
                                if(360-y2>90)  r = getRotationMatrix2D(pt,300, 1.0);
                                else if(360-y2<0)  r = getRotationMatrix2D(pt,0, 1.0);
                                else r = getRotationMatrix2D(pt, -360+y2, 1.0);

                            //putText(fundo,intToString(-360+y2),Point(0,50),1,2,Scalar(0,0,255),2);

                                warpAffine(imageROIEsq, imageROIEsq, r, Size(140, 122));
                       // }
                       // video.write(cameraFeed);
                    }
                }else putText(cameraFeed,"Muito ruído!",Point(0,50),1,2,Scalar(0,0,255),2);
            }
            if (hierarchy3.size() > 0) {
                int numObjects3 = hierarchy3.size();

                //se o numero de objetos for muito grande, isso sera consderado ruido
                if(numObjects3<MAX_NUM_OBJECTS){
                    for (int index = 0; index >= 0; index = hierarchy3[index][0]) {

                        Moments moment3 = moments((cv::Mat)contours3[index]);
                        double area3 = moment3.m00;

                        //se a area do objeto é menor que 20 px by 20px, isso eh ruido
                        //se a área é 3/2 do tamanho da imagem, filtro mal ajustado
                        if(area3>MIN_OBJECT_AREA && area3<MAX_OBJECT_AREA && area3>refArea3){
                            x3 = moment3.m10/area3;
                            y3 = moment3.m01/area3;
                            BracoDirFound = true;
                            refArea3 = area3;


                        }else{
                              BracoDirFound = false;
                             // drawBracoDirBoneco(509,240,cameraFeed);
                          }

                    }
                    //incrementa a quantidade
                    int quant  = 0;
                    char text[255];
                    sprintf(text, "Quantidade %d", (int)quant);


                    if(BracoDirFound ==true){ //se apareceu o objeto

                        //putText(cameraFeed,"REC",Point(0,50),2,1,Scalar(0,0,255),2);
                        //desenha um objeto
                        drawObject3(x3,y3,cameraFeed);
                        //if((cameraFeed.cols > mickeyDir.cols+x3 && cameraFeed.rows > mickeyDir.rows+y3)&&(x3-100>0 && y3-100>0)){

                               Mat r2;
                            int len2 = max(mickeyDir.cols, mickeyDir.rows);
                                Point2f pt2(5, 5);

                                //limita a revolução da braço dir
                                if(360-y3>70)  r2 = getRotationMatrix2D(pt2,70, 1.0);
                                else if(360-y3<10)  r2 = getRotationMatrix2D(pt2,10, 1.0);
                                else r2 = getRotationMatrix2D(pt2, 360-y3, 1.0);


                                warpAffine(imageROIDir, imageROIDir, r2, Size(140, 122));

                        //}


                    }
                }else putText(cameraFeed,"Muito ruído!",Point(0,50),1,2,Scalar(0,0,255),2);
            }

            if (hierarchy4.size() > 0) {
                int numObjects4 = hierarchy4.size();

                //se o numero de objetos for muito grande, isso sera consderado ruido
                if(numObjects4<MAX_NUM_OBJECTS){
                    for (int index = 0; index >= 0; index = hierarchy4[index][0]) {

                        Moments moment4 = moments((cv::Mat)contours4[index]);
                        double area4 = moment4.m00;

                        //se a area do objeto é menor que 20 px by 20px, isso eh ruido
                        //se a área é 3/2 do tamanho da imagem, filtro mal ajustado
                        if(area4>MIN_OBJECT_AREA && area4<MAX_OBJECT_AREA && area4>refArea4){
                            x4 = moment4.m10/area4;
                            y4 = moment4.m01/area4;
                            CorpoFound = true;
                            refArea4 = area4;

                        }else {
                            CorpoFound = false;
                           // drawCorpoBoneco(423,200,cameraFeed);
                        }

                    }
                    //incrementa a quantidade
                    int quant  = 0;
                    char text[255];
                    sprintf(text, "Quantidade %d", (int)quant);

                    if(CorpoFound ==true){ //se apareceu o objeto
                        drawObject4(x4,y4,cameraFeed);

                        //põe o rosto do mickey na cena
                        //essa condição eh pq se passar dos limites da camera da erro
                       // if((cameraFeed.cols > mickeyCorpo.cols+x4 && cameraFeed.rows > mickeyCorpo.rows+y4)&&(x4-50>0 && y4-50>0)){

                                                   }
                   // }
                }else{

                    putText(cameraFeed,"Muito ruído!",Point(0,50),1,2,Scalar(0,0,255),2);
                }
            }
            if (hierarchy1.size() > 0) {
                int numObjects1 = hierarchy1.size();

                //se o numero de objetos for muito grande, isso sera consderado ruido
                if(numObjects1<MAX_NUM_OBJECTS){
                    for (int index = 0; index >= 0; index = hierarchy1[index][0]) {

                        Moments moment1 = moments((cv::Mat)contours1[index]);
                        double area1 = moment1.m00;

                        //se a area do objeto é menor que 20 px by 20px, isso eh ruido
                        //se a área é 3/2 do tamanho da imagem, filtro mal ajustado
                        if(area1>MIN_OBJECT_AREA && area1<MAX_OBJECT_AREA && area1>refArea1){
                            x1 = moment1.m10/area1;
                            y1 = moment1.m01/area1;
                            CabecaFound = true;
                            refArea1 = area1;

                        }else {
                            CabecaFound = false;
                           // drawCabecaBoneco(423,200,cameraFeed);
                        }

                    }
                    //incrementa a quantidade
                    int quant  = 0;
                    char text[255];
                    sprintf(text, "Quantidade %d", (int)quant);

                    if(CabecaFound ==true){ //se apareceu o objeto
                        drawObject1(x1,y1,cameraFeed);


                                Mat r3;
                            int len3 = max(mickeyFace.cols, mickeyFace.rows);
                                Point2f pt3(65, 162);

                                //limita a revolução da cabeça
                                if(x1>410)  r3 = getRotationMatrix2D(pt3, 410, 1.0);
                                else if(x1<330)  r3 = getRotationMatrix2D(pt3, 330, 1.0);
                                else  r3 = getRotationMatrix2D(pt3, x1+1, 1.0);

                                warpAffine(imageROIFace, imageROIFace, r3, Size(100, 125));

                        //}
                    }
                }else{

                    putText(cameraFeed,"Muito ruído!",Point(0,50),1,2,Scalar(0,0,255),2);
                }
            }


        }

            video.write(fundo); //grava o video

        //show frames
        imshow(windowName2,threshold1);
        imshow(windowName3,threshold2);
        imshow(windowName4,threshold3);
        imshow(windowName5,threshold4);
        imshow(windowName,cameraFeed);
        imshow("Boneco",fundo);




        char c = (char)waitKey(33);
        if( c == 27 ) break;
    }






    return 0;
}
