// big_planView.cpp : implementation of the CBig_planView class
//

#include "stdafx.h"
#include "big_plan.h"

#include "big_planDoc.h"
#include "big_planView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BYTE *data;
BYTE *data_dis;
#define MAX_BUFFER_LEN	3145728
#define WIDTH			1024
#define HEIGHT			768

//#define THRESHOLD		100

#define charMaxWidth	2 //应该近似于要识别的文字大小,越小越能突显线条（文字），小于该大小的字将不可见
#define ASSAME_STRICT	30 //越大，要求的图像变化越明显才有效

#define LEFT			0
#define RIGHT			1
#define UP				2
#define DOWN			3

#define HORIZONTAL		0
#define VERTICAL		1

#define RGBMARK		RGB(255, 0, 0)

COLORREF getColor2(int x, int y){
	int pos;
	BYTE r,g,b;
	pos = (WIDTH * y + x) * 4;

	b = data_dis[pos];
	g = data_dis[pos+1];
	r = data_dis[pos+2];

	return RGB(r, g, b);
}

COLORREF getColor(int x, int y){
	int pos;
	BYTE r,g,b;
	pos = (WIDTH * y + x) * 4;

	b = data[pos];
	g = data[pos+1];
	r = data[pos+2];

//	只保留特定的颜色区间
//	if(b < THRESHOLD || g < THRESHOLD || r < THRESHOLD){
//		b = g = r = 0;
//	}

	return RGB(r, g, b);
}

void setColor(int x, int y, COLORREF color){
	int pos;
	pos = (WIDTH * y + x) * 4;

	data[pos] = GetBValue(color);
	data[pos+1] = GetGValue(color);
	data[pos+2] = GetRValue(color);
}


void setColor2(int x, int y, COLORREF color){
	int pos;
	pos = (WIDTH * y + x) * 4;

	data_dis[pos] = GetBValue(color);
	data_dis[pos+1] = GetGValue(color);
	data_dis[pos+2] = GetRValue(color);
}

void copyColor(int x, int y){
	int pos;
	pos = (WIDTH * y + x) * 4;
	data_dis[pos] = data[pos];
	data_dis[pos+1] = data[pos+1];
	data_dis[pos+2] = data[pos+2];
}

bool colorAsSame(COLORREF a, COLORREF b){
	BYTE aR = GetRValue(a);
	BYTE aG = GetGValue(a);
	BYTE aB = GetBValue(a);
	BYTE bR = GetRValue(b);
	BYTE bG = GetGValue(b);
	BYTE bB = GetBValue(b);
	if((abs(aR-bR) > ASSAME_STRICT || abs(aG-bG) > ASSAME_STRICT || abs(aB-bB) > ASSAME_STRICT))
		return false;
	return true;
}

bool colorAsSame2(int x, int y, int HorV){
	int x2, y2, x2_1, y2_1, x2_2, y2_2;
	switch(HorV){
	case HORIZONTAL:
		x2 = x==WIDTH-1? x : x+1;
		y2 = y;
		x2_1 = x2_2 = x2;
		y2_1 = y==0 ? 0 : y-1;
		y2_2 = y==HEIGHT-1 ? y : y+1;
		break;
	case VERTICAL:
		x2 = x;
		y2 = y==HEIGHT-1? y : y+1;
		x2_1 = x==0 ? 0 : x -1;
		x2_2 = x==WIDTH-1? x : x+1;
		y2_1 = y2_2 = y2;
		break;
	}
	int pos, pos2, pos2_1, pos2_2;
	pos = (WIDTH * y + x) * 4;
	pos2 = (WIDTH * y2 + x2) * 4;
	pos2_1 = (WIDTH * y2_1 + x2_1) * 4;
	pos2_2 = (WIDTH * y2_2 + x2_2) * 4;
	BYTE R = data[pos+2];
	BYTE G = data[pos+1];
	BYTE B = data[pos];
	BYTE R2 = data[pos2+2];
	BYTE G2 = data[pos2+1];
	BYTE B2 = data[pos2];
	BYTE R2_1 = data[pos2_1+2];
	BYTE G2_1 = data[pos2_1+1];
	BYTE B2_1 = data[pos2_1];
	BYTE R2_2 = data[pos2_2+2];
	BYTE G2_2 = data[pos2_2+1];
	BYTE B2_2 = data[pos2_2];
	if((abs(R-R2) > ASSAME_STRICT || abs(G-G2) > ASSAME_STRICT || abs(B-B2) > ASSAME_STRICT)
		&&(abs(R-R2_1) > ASSAME_STRICT || abs(G-G2_1) > ASSAME_STRICT || abs(B-B2_1) > ASSAME_STRICT)
		&&(abs(R-R2_2) > ASSAME_STRICT || abs(G-G2_2) > ASSAME_STRICT || abs(B-B2_2) > ASSAME_STRICT))
		return false;
	return true;
}

void markSharp(){
	COLORREF colorOri;
	COLORREF colorTar;
	int sameNum = 0;
	int posRecodeX[charMaxWidth];
	int posRecodeY[charMaxWidth];
	bool recodeing = false;
	//H
	for(int y=0; y< HEIGHT; y++){
		for(int x=0, colorOri = getColor(0, y); x< WIDTH-1; x++){
			colorTar = getColor(x+1, y);
			if(!colorAsSame(colorOri, colorTar)){
//			if(!colorAsSame2(x, y, HORIZONTAL)){
				if(recodeing){
					//TODO 十字交叉的地方会省略，补上
					
					//记录下来的点
					for(int i=0; i<sameNum; i++){
//						setColor2(posRecodeX[i]+1, posRecodeY[i], RGBMARK);
						copyColor(posRecodeX[i]+1, posRecodeY[i]);
					}
				}
				sameNum = 1;
				recodeing = true;
			}else{
				if(recodeing){
					sameNum ++;
					if(sameNum > charMaxWidth){
						recodeing = false;
						sameNum = 0;
					}
				}
			}
			if(sameNum > 0){
				posRecodeX[sameNum - 1] = x;
				posRecodeY[sameNum - 1] = y;
			}
			colorOri = colorTar;
		}
	}
	//V
	for(int x=0; x< WIDTH; x++){
		for(int y=0, colorOri = getColor(x, 0); y< HEIGHT-1; y++){
			colorTar = getColor(x, y+1);
			if(!colorAsSame(colorOri, colorTar)){
//			if(!colorAsSame2(x, y, VERTICAL)){
				if(recodeing){
					for(int i=0; i<sameNum; i++){
//						setColor2(posRecodeX[i], posRecodeY[i]+1, RGBMARK);
						copyColor(posRecodeX[i], posRecodeY[i]+1);
					}
				}
				sameNum = 1;
				recodeing = true;
			}else{
				if(recodeing){
					sameNum ++;
					if(sameNum > charMaxWidth){
						recodeing = false;
						sameNum = 0;
					}
				}
			}
			if(sameNum > 0){
				posRecodeX[sameNum - 1] = x;
				posRecodeY[sameNum - 1] = y;
			}
			colorOri = colorTar;
		}
	}
}

void magicData(){
	markSharp();
}

void initData(){
	data = new BYTE[MAX_BUFFER_LEN];
	data_dis = new BYTE[MAX_BUFFER_LEN];
	memset(data_dis, 1, MAX_BUFFER_LEN);

	FILE *file = fopen("E:\\big_plan\\fb_half", "rb");
	if(file == NULL){
		printf("open failed");
	}
	fseek(file,0,2); 
	long fileSize = ftell(file); 
	printf("fileSize:%d", fileSize);
	fseek(file,0,0); 
	unsigned int readLen = 0;
	long pos = 0;
	do{ 
		readLen = fread(data+pos,sizeof(char),MAX_BUFFER_LEN,file); 
		if(readLen > 0) 
		{ 
			pos += readLen; 
		} 
	}while(pos < fileSize); 
}


/////////////////////////////////////////////////////////////////////////////
// CBig_planView

IMPLEMENT_DYNCREATE(CBig_planView, CView)

BEGIN_MESSAGE_MAP(CBig_planView, CView)
	//{{AFX_MSG_MAP(CBig_planView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBig_planView construction/destruction

CBig_planView::CBig_planView()
{
	initData();
	magicData();
}

CBig_planView::~CBig_planView()
{
}

BOOL CBig_planView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBig_planView drawing

void CBig_planView::OnDraw(CDC* pDC)
{
	CBig_planDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	int x, y;
	for(y=0; y<HEIGHT;y++){
		for(x=0;x<WIDTH;x++){
			pDC->SetPixel(x, y, getColor2(x, y));
		}	
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBig_planView printing

BOOL CBig_planView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBig_planView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBig_planView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBig_planView diagnostics

#ifdef _DEBUG
void CBig_planView::AssertValid() const
{
	CView::AssertValid();
}

void CBig_planView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBig_planDoc* CBig_planView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBig_planDoc)));
	return (CBig_planDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBig_planView message handlers
