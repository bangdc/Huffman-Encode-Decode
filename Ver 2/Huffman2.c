#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char 	*bangMa[256];

struct	cayHuffman{
	int		chuCai;
	int		tanSuat;
	struct	cayHuffman	*conTrai;
	struct	cayHuffman	*conPhai;
};
/*--------------------------kiemTraLa-------------------------------
|  Ten Ham 		kiemTraLa
|
|  Muc Dich:  	Kiem tra 1 nut cua cay huffman co phai la la khong?
|
|  Dau Vao:
|				struct cayHuffman *nutKiemTra
|               	-Nut cua cay Huffman can kiem tra
|
|  Ket Qua:  
|				1	- 	Neu nut la la
|				2	-	Neu nut khong phai la.
*-------------------------------------------------------------------*/
int 	kiemTraLa(struct cayHuffman *nutKiemTra);
/*--------------------------tongSoChuCai-------------------------------
|  Ten Ham 		tongSoChuCai
|
|  Muc Dich:  	Tinh tong so ki tu khac nhau trong van ban can nen.
|
|  Dau Vao:
|				int	bangTanSuat[]
|               	-Bang tan suat cua 256 ki tu ASCII xuat hien trong van ban. 
|
|  Ket Qua:  
|				int tong so ki tu khac nhau trong van ban.
*-------------------------------------------------------------------*/
int		tongSoChuCai(int bangTanSuat[]);
/*--------------------------nenFile-------------------------------
|  Ten Ham 		nenFile
|
|  Muc Dich:  	Chuong Trinh Nen File Bang Thuat Toan Huffman
|
|  Dau Vao:		Khong Co
|
|  Ket Qua:  
|				- 	Chuong trinh yeu cau nhap vao file can nen du lieu
|				-	Thong ke tan suat ki tu trong file
|				- 	Xay dung cay Huffman.
|				- 	Xay dung bang Ma Huffman
|				- 	Nen va tao file nen theo dinh dang .huffman
*-------------------------------------------------------------------*/
void 	nenFile();
/*--------------------------giaiNenFile-------------------------------
|  Ten Ham 		giaiNenFile
|
|  Muc Dich:  	Chuong Trinh Giai Nen File Bang Thuat Toan Huffman
|
|  Dau Vao:		Khong Co
|
|  Ket Qua:  
|				- 	Chuong trinh yeu cau nhap vao file nen dinh dang .huffman
|				-	Doc xuat du lieu can giai nen
|				- 	Xay dung cay Huffman.
|				- 	Giai nen va tao file theo dinh dang ban dau
*-------------------------------------------------------------------*/
void 	giaiNenFile();
/*--------------------------xayDungMaHuffman-------------------------
|  Ten Ham 		xayDungMaHuffman
|
|  Muc Dich:  	Xay Dung Ma Huffman Tu Cay Huffman
|
|  Dau Vao:
|				struct cayHuffman *huffman
|               	-	Cay Huffman Hoan Chinh
|				char 	chuoiMaHoa[]
|					-	Chuoi Ma Hoa Huffman
|				int 	index
|					- 	Vi Tri Ki Tu Ma Hoa Trong Chuoi Ma Hoa
|
|  Ket Qua:  
|				1	- 	Xay Dung Bang Huffman Luu Trong Mang char bangMa[256].
*-------------------------------------------------------------------*/
void 	xayDungMaHuffman(struct cayHuffman *huffman, char chuoiMaHoa[], int index);
/*--------------------------dungCayHuffman-------------------------------
|  Ten Ham 		dungCayHuffman
|
|  Muc Dich:  	Xay Dung Cay Huffman Tu Bang Tan Suat
|
|  Dau Vao:
|				int  bangTanSuat[]
|               	-	Bang Tan Suat Cua Cac Ki Tu Trong Van Ban
|
|  Ket Qua:  
|				1	- 	struct cayHuffman *huffman
|					- 	Tra Ra Nut Goc Cua Cay Huffman
*-------------------------------------------------------------------*/
struct  cayHuffman *dungCayHuffman(int bangTanSuat[]);

int main()
{
	int luaChonChucNang	=	3;
	do
	{
		printf("\n *******************Chuong Trinh Nen Huffman *************");
		printf("\n |                                                       |");
		printf("\n |              * Nen file                       (1)     |");
		printf("\n |              * Giai nen file                  (2)     |");
		printf("\n |                                                       |");
		printf("\n *********************************************************\n");
		scanf("%d", &luaChonChucNang);
		if( (luaChonChucNang == 1)  || (luaChonChucNang == 2)  )	
		{
			break;
		}
	}
	while( 1 );
	switch(luaChonChucNang)
	{
		case 1 : 
		{
			nenFile();
			break;
		}
		case 2 : 
		{
			giaiNenFile();
			break;
		}		
	}
	return 0;
}

void 	nenFile()
{
	clock_t thoiGianBatDau, thoiGianKetThuc;
	char 	fileDauVao[1000];
	char	fileNen[1000];
	FILE 	* pDauVao;
	FILE 	* pFileNen;
	struct  cayHuffman	*huffman;
  	int 	tongSoBits	=	0;
	int		tongSoBitsNen	=	0;
	
	int c,i;
	int demBits	=	0;
	int	viTriBit	=	8;

	int	kiTuMaHoa	=	0;
	
	int		bangTanSuat[256];
	printf("\n File Can Nen Huffman: ");
	fflush(stdin);
	scanf("%s", &fileDauVao);
	
	pDauVao	=	fopen (fileDauVao,"rb");
	
	if (pDauVao==NULL) 
	{
		printf("\n Khong the mo file nen\n");
		return;
	}
	thoiGianBatDau	=	clock();
	printf("\n Dang Xay Dung Bang Tan So... \n");
	for(i = 0; i<256; i++)
  	{
  		bangTanSuat[i]	=	0;
  	}
  	
  	while((c=fgetc(pDauVao)) != EOF)
  	{
  		bangTanSuat[c]++;
  	}
  	thoiGianKetThuc		=	clock();
  	printf("\n Xong Xay Dung Bang Tan So %f Giay\n", (double)(thoiGianKetThuc - thoiGianBatDau) / CLOCKS_PER_SEC);
  	fclose (pDauVao);
  	
	if(tongSoChuCai(bangTanSuat) > 1)
  	{  		
  		thoiGianBatDau	=	clock();
  		printf("\n Dang Xay Dung Cay Huffman... \n");
  		huffman 	=	dungCayHuffman(bangTanSuat);
  		thoiGianKetThuc		=	clock();
  		printf("\n Xong Xay Dung Cay Huffman %f Giay\n", (double)(thoiGianKetThuc - thoiGianBatDau) / CLOCKS_PER_SEC);
  		
  		thoiGianBatDau	=	clock();
  		printf("\n Dang Xay Dung Bang Ma... \n");
		char	chuoiMaHoa[256];
		xayDungMaHuffman(huffman,chuoiMaHoa, 0);
		thoiGianKetThuc		=	clock();	
		printf("\n Xong Xay Dung Bang Ma %f Giay\n", (double)(thoiGianKetThuc - thoiGianBatDau) / CLOCKS_PER_SEC);
		
		printf("\n Bat Dau Qua Trinh Nen FILE... \n");
		thoiGianBatDau	=	clock();
		pDauVao			=	fopen (fileDauVao,"rb");
		strcpy(fileNen, fileDauVao);
		strcat (fileNen,".huffman");
		pFileNen 		= 	fopen (fileNen,"wb");
		
		for(i=0; i<256;i++)
		{
			if(bangTanSuat[i] > 0)
			{
				tongSoBitsNen	+=	strlen(bangMa[i]) * bangTanSuat[i];
			}
		}
		
		fwrite(&tongSoBitsNen, sizeof(int), 1, pFileNen);
		fwrite(bangTanSuat, sizeof(int), 256, pFileNen);
		
		while((c=fgetc(pDauVao)) != EOF)
		{
			tongSoBits	+=	8;
			int	leng	=	strlen(bangMa[c]);
			for(i = 0; i<leng; i++)
			{
				if(demBits == 8)
				{
					fwrite(&kiTuMaHoa, sizeof(char), 1, pFileNen);
					kiTuMaHoa	=	0;
					demBits	=	0;
					viTriBit	=	8;
					i--;
				}
				else
				{
					int d 		= 	*(bangMa[c]+i) - '0';
					kiTuMaHoa	+=	d << (viTriBit-1);
					demBits++;
					viTriBit--;
				}
			}
		}
		
		if(demBits != 0)
		{
			fwrite(&kiTuMaHoa, sizeof(char), 1, pFileNen);
		}
		thoiGianKetThuc		=	clock();	
		printf("\n Ket Thuc Qua Trinh Nen FILE %f Giay\n", (double)(thoiGianKetThuc - thoiGianBatDau) / CLOCKS_PER_SEC);
		printf("\n Ti Le Nen %f \n", (float)tongSoBitsNen/tongSoBits);
		printf("\n File Nen La %s \n", fileNen);
		fclose (pDauVao);
		fclose (pFileNen);
  	}
  	else
  	{
  		printf("Co it hon 2 ki tu de lap cay HUFFMAN");
  	}
}

void 	giaiNenFile()
{
	char 	fileGiaiNen[1000];
	char	fileNen[1000];
	FILE 	* pFileNen;
	FILE 	* pFileGiaiNen;
	int		bangTanSuat[256];
	int 	k, i;
	int 	tongSoBitsNen;
	clock_t	thoiGianBatDau, thoiGianKetThuc;
	printf("\n File Giai Nen Huffman Dinh Dang .huffman: ");
	fflush(stdin);
	scanf("%s", &fileNen);
	if(strstr(fileNen, ".huffman") == NULL)
	{
		printf("\n Khong phai la file nen dinh dang .huffman.\n");
		return;
	}
	pFileNen	=	fopen (fileNen,"rb");
	if (pFileNen==NULL) 
	{
		printf("\n Khong the mo file nen %s !\n", fileNen);
		return;
	}
	thoiGianBatDau	=	clock();
  	printf("\n Dang Xay Dung Cay Huffman... \n");
	int x	=	strlen(fileNen) - 8;
	strncpy(fileGiaiNen, fileNen, x);
	fileGiaiNen[x]	=	'\0';
	
	pFileGiaiNen	=	fopen(fileGiaiNen, "wb");
	
	fread(&tongSoBitsNen, sizeof(int), 1,pFileNen );
	fread(bangTanSuat, sizeof(int), 256, pFileNen);
	
	struct  cayHuffman	*huffman;
	
	huffman 	=	dungCayHuffman(bangTanSuat);
	thoiGianKetThuc		=	clock();
  	printf("\n Xong Xay Dung Cay Huffman %f Giay\n", (double)(thoiGianKetThuc - thoiGianBatDau) / CLOCKS_PER_SEC);
  	
  	thoiGianBatDau	=	clock();
  	printf("\n Bat Dau Giai Nen... \n");
  	
	int	viTriBit	=	8;
	struct 	cayHuffman	*tempNode	=	huffman;
	int	kiTuMaHoa;
	
	while(!feof(pFileNen))
	{
		fread(&kiTuMaHoa, sizeof(char), 1,pFileNen );
	
		if(tongSoBitsNen < 8) {
			viTriBit	=	tongSoBitsNen;
		}	
		int demBits 	=	8;
		for(k=viTriBit; k>0; k--)
		{
			int	bit	=	(kiTuMaHoa >> (demBits-1) ) & 1;
			if( bit == 0)
			{
				tempNode	=	tempNode->conTrai;
			}
			else
			{
				tempNode	=	tempNode->conPhai;
			}
			if(kiemTraLa(tempNode) == 1)
			{
				fwrite(&(tempNode->chuCai), sizeof(char), 1, pFileGiaiNen);
				tempNode	=	huffman;
			}
			demBits--;
			tongSoBitsNen--;
		}
	}
	fclose (pFileGiaiNen);
	fclose (pFileNen);
	thoiGianKetThuc		=	clock();
	printf("\n Giai Nen File Thanh Cong %s Trong %f Giay\n", fileGiaiNen, (double)(thoiGianKetThuc - thoiGianBatDau) / CLOCKS_PER_SEC);
}

void 	xayDungMaHuffman(struct cayHuffman *huffman, char chuoiMaHoa[], int index)
{
	
	if(huffman->conTrai != 0)
	{
		chuoiMaHoa[index]	=	'0';
		xayDungMaHuffman(huffman->conTrai, chuoiMaHoa, index + 1);
	}
	
	if(huffman->conPhai	!= 0)
	{
		chuoiMaHoa[index]	=	'1';
		xayDungMaHuffman(huffman->conPhai,  chuoiMaHoa, index + 1);
	}
	
	if(kiemTraLa(huffman) == 1)
	{
		int i;
		bangMa[huffman->chuCai]	=	(char *) malloc(sizeof(char) * index);
		for(i=0; i<index; i++)
		{
			*(bangMa[huffman->chuCai] + i)	=	chuoiMaHoa[i];
		}
		*(bangMa[huffman->chuCai] + index)	=	'\0';
	}
}

struct  cayHuffman *dungCayHuffman(int bangTanSuat[])
{
	int i, k;
	int n 	=	tongSoChuCai(bangTanSuat);
	struct cayHuffman *bangTanSuatHuffman[n];
	k	=	0;
	
	for(i=0; i<256; i++)
	{
		if(bangTanSuat[i] > 0)
		{
			bangTanSuatHuffman[k]			=	(struct cayHuffman *) malloc(sizeof(struct cayHuffman));
			bangTanSuatHuffman[k]->conTrai	=	0;
			bangTanSuatHuffman[k]->conPhai	=	0;
			bangTanSuatHuffman[k]->tanSuat	=	bangTanSuat[i];
			bangTanSuatHuffman[k]->chuCai	=	i;
			k++;
		}				
	}
	
	while(n > 1)
	{
		int max;
		for(i=0; i<(n-1); i++ )
		{
			max = i;
			for(k = (i+1); k<n; k++)
			{
				if(bangTanSuatHuffman[k]->tanSuat > bangTanSuatHuffman[max]->tanSuat) max = k;
			}
			if(i != max)
			{
				int	chuCai	=	bangTanSuatHuffman[i]->chuCai;
				int	tanSuat	=	bangTanSuatHuffman[i]->tanSuat;
				struct	cayHuffman *conTrai	=	bangTanSuatHuffman[i]->conTrai;
				struct	cayHuffman *conPhai	=	bangTanSuatHuffman[i]->conPhai;
				
				bangTanSuatHuffman[i]->chuCai			=	bangTanSuatHuffman[max]->chuCai;
				bangTanSuatHuffman[i]->tanSuat			=	bangTanSuatHuffman[max]->tanSuat;
				bangTanSuatHuffman[i]->conTrai			=	bangTanSuatHuffman[max]->conTrai;
				bangTanSuatHuffman[i]->conPhai			=	bangTanSuatHuffman[max]->conPhai;
				
				bangTanSuatHuffman[max]->conTrai		=	conTrai;
				bangTanSuatHuffman[max]->conPhai		=	conPhai;	
				bangTanSuatHuffman[max]->chuCai			=	chuCai;
				bangTanSuatHuffman[max]->tanSuat		=	tanSuat;
			}
		}
		struct	cayHuffman *nhanhTrai	=	bangTanSuatHuffman[i]->conTrai;
		struct	cayHuffman *nhanhPhai	=	bangTanSuatHuffman[i]->conPhai;
		nhanhPhai		=	(struct cayHuffman *) malloc(sizeof(struct cayHuffman));
		
		nhanhPhai->conTrai		=	bangTanSuatHuffman[n-1]->conTrai;
		nhanhPhai->conPhai		=	bangTanSuatHuffman[n-1]->conPhai;	
		nhanhPhai->chuCai		=	bangTanSuatHuffman[n-1]->chuCai;
		nhanhPhai->tanSuat		=	bangTanSuatHuffman[n-1]->tanSuat;
		free(bangTanSuatHuffman[n-1]);
		
		nhanhTrai		=	(struct cayHuffman *) malloc(sizeof(struct cayHuffman));
		nhanhTrai->conTrai		=	bangTanSuatHuffman[n-2]->conTrai;
		nhanhTrai->conPhai		=	bangTanSuatHuffman[n-2]->conPhai;	
		nhanhTrai->chuCai		=	bangTanSuatHuffman[n-2]->chuCai;
		nhanhTrai->tanSuat		=	bangTanSuatHuffman[n-2]->tanSuat;
		
		bangTanSuatHuffman[n-2]->conTrai	=	nhanhTrai;
		bangTanSuatHuffman[n-2]->conPhai	=	nhanhPhai;
		bangTanSuatHuffman[n-2]->chuCai		=	256;
		bangTanSuatHuffman[n-2]->tanSuat	=	nhanhTrai->tanSuat + nhanhPhai->tanSuat;
		
		n--;
	}
	
	return bangTanSuatHuffman[0];
}

int		tongSoChuCai(int bangTanSuat[])
{
	int count	=	0;
	int	i;
	for(i=0; i<256;i++)
	{
		if(bangTanSuat[i] > 0)
		{
			count++;
		}
	}
	return	count;
}

int 	kiemTraLa(struct cayHuffman *nutKiemTra)
{
	if(nutKiemTra->conTrai == 0 && nutKiemTra->conPhai == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
