#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char	file_nen_huffman[20]		=	"compress.txt";
char	file_giai_nen_huffman[20]	=	"decompress.txt";

char 	*bang_ma_hoa_huffman[256];

struct	cay_huffman{
	int		ki_tu;
	int		tan_so;
	struct	cay_huffman	*ki_tu_tiep_theo;
	struct	cay_huffman	*con_trai;
	struct	cay_huffman	*con_phai;
};

void 	in_bang_ma_hoa_huffman(char *bang_ma_hoa_huffman[], int bang_tan_so[]);

struct	cay_huffman	*sap_xep_cay_huffman(struct	cay_huffman *huffman);

int 	kiem_tra_la_huffman(struct cay_huffman *nut_kiem_tra);

int		dem_so_ki_tu_khac_nhau(int bang_tan_so[]);

void 	nen_file_huffman();

void 	giai_nen_file_huffman();

void 	xay_dung_ma_huffman(struct cay_huffman *huffman, char chuoi_ma_hoa[], int index);

struct  cay_huffman *xay_dung_cay_huffman();

struct 	cay_huffman *copy_2_nut(struct	cay_huffman *nut_chuyen_den, struct cay_huffman *nut_nguon);

int 	hien_thi_menu_con();
int main()
{
	int lua_chon_menu	=	3;
	do
	{
		printf("\n ************************ THUAT NEN HUFFMAN ************************");
		printf("\n |     Menu :                                                      |");
		printf("\n |              * Nen file                       (Nhan phim 1)     |");
		printf("\n |              * Giai nen file                  (nhan phim 2)     |");
		printf("\n |              * Thoat chuong trinh             (nhan phim 0)     |");
		printf("\n |                                                                 |");
		printf("\n *******************************************************************");
		printf("\n       Chuc nang ban chon la :   ");
		scanf("%d", &lua_chon_menu);
		if( (lua_chon_menu == 1)  || (lua_chon_menu == 2) || (lua_chon_menu == 0) )	
		{
			break;
		}
	}
	while( 1 );
	switch(lua_chon_menu)
	{
		case 1 : 
		{
			nen_file_huffman();
			break;
		}
		case 2 : 
		{
			giai_nen_file_huffman();
			break;
		}
		case 0 : 
		{
			printf("\n Thoat chuong trinh !");
			break;
		}		
	}
	return 0;
}

void 	nen_file_huffman()
{
	FILE 	* con_tro_file_dau_vao;
	int 	lua_chon_menu;
	int 	c;
	char 	file_dau_vao[1000];
	int		bang_tan_so[256];
	do
	{
		printf("\n ____________________________ Nen File______________________________ ");
		printf("\n ");
		printf("\n  Nhap vao duong dan FILE can nen :     ");
		fflush(stdin);
		scanf("%s", &file_dau_vao);
		con_tro_file_dau_vao	=	fopen (file_dau_vao,"rb");
		if (con_tro_file_dau_vao==NULL) 
		{
			printf("\n ************************ CO LOI XAY RA ***************************");
			perror("\n Khong the mo file dau vao");
			printf("\n ************************ CO LOI XAY RA ***************************");
			return;
		}
		
		for(c = 0; c<256; c++)
	  	{
	  		bang_tan_so[c]	=	0;
	  	}
	  	while((c=fgetc(con_tro_file_dau_vao)) != EOF)
	  	{
	  		bang_tan_so[c]++;
	  	}
	  	fclose (con_tro_file_dau_vao);
		
		int	tong_so_ki_tu	=	dem_so_ki_tu_khac_nhau(bang_tan_so);
		if(tong_so_ki_tu > 1)
	  	{  		
	    	FILE 	* con_tro_file_nen;
			struct  cay_huffman	*huffman;
			int		tong_so_bits_nen	=	0;
			
			int 	dem_bits	=	0;
			int		vi_tri_bit_hien_tai	=	8;
			int 	i;
			int		ki_tu_ma_hoa	=	0;
			int		tong_so_ki_tus	=	0;
			
			huffman 	=	xay_dung_cay_huffman(bang_tan_so);
			char	chuoi_ma_hoa[256];
			xay_dung_ma_huffman(huffman,chuoi_ma_hoa, 0);	
			
			con_tro_file_dau_vao	=	fopen (file_dau_vao,"rb");
			con_tro_file_nen 		= 	fopen (file_nen_huffman,"wb");
			for(i=0; i<256;i++)
			{
				if(bang_tan_so[i] != 0)
				{
					tong_so_bits_nen	+=	strlen(bang_ma_hoa_huffman[i]) * bang_tan_so[i];
				}
			}
			fwrite(&tong_so_bits_nen, sizeof(int), 1, con_tro_file_nen);
			fwrite(bang_tan_so, sizeof(int), 256, con_tro_file_nen);
			
			while((c=fgetc(con_tro_file_dau_vao)) != EOF)
			{
				int	leng	=	strlen(bang_ma_hoa_huffman[c]);
				for(i = 0; i<leng; i++)
				{
					if(dem_bits == 8)
					{
						fwrite(&ki_tu_ma_hoa, sizeof(char), 1, con_tro_file_nen);
						tong_so_ki_tus++;
						ki_tu_ma_hoa	=	0;
						dem_bits		=	0;
						vi_tri_bit_hien_tai		=	8;
						i--;
					}
					else
					{
						int d 			= 	*(bang_ma_hoa_huffman[c]+i) - '0';
						ki_tu_ma_hoa	+=	d << (vi_tri_bit_hien_tai-1);
						dem_bits++;
						vi_tri_bit_hien_tai--;
					}
				}
			}
			if(dem_bits != 0)
			{
				fwrite(&ki_tu_ma_hoa, sizeof(char), 1, con_tro_file_nen);
			}
			fclose (con_tro_file_dau_vao);
			fclose (con_tro_file_nen);
			
		  	printf("\n __________________________Ket Qua Nen File_________________________ ");
		    printf("\n");
		    printf("\n Da nen file %s thanh cong, file nen luu trong %s \n", file_dau_vao, file_nen_huffman);
			printf("\n __________________________Ket Qua Nen File_________________________ ");
	  	}
	  	else
	  	{
	  		printf("Co it hon 2 ki tu de lap cay HUFFMAN");
	  	}
	  	
	    lua_chon_menu	=	hien_thi_menu_con();
		if ( ( lua_chon_menu == 1 )	||	( lua_chon_menu == 0 ) )
		{
			break;
		}	
	}
	while( 1 );
	if ( lua_chon_menu == 1 )
	{
		main();
	}
	if ( lua_chon_menu == 0 )
	{
		exit(1);
	}
	return;
}
int 	hien_thi_menu_con()
{
	int lua_chon_menu;
	printf("\n");
	printf("\n |   Menu:                                                         |");
	printf("\n |     * Tro ve menu chinh        (nhan phim 1)                    |");
	printf("\n |     * Thoat chuong trinh       (nhan phim 0)                    |");	
	printf("\n     Chuc nang ban chon la :   ");
	scanf("%d", &lua_chon_menu);
	printf("\n |_________________________________________________________________|");
	printf("\n ");
	return lua_chon_menu;
}
void 	giai_nen_file_huffman()
{
	char file_dau_vao[1000];
	int lua_chon_menu;
	
	do
	{
		printf("\n _________________________ Giai nen File____________________________ ");
		printf("\n ");
		printf("\n  Nhap vao duong dan FILE can giai nen :     ");
		fflush(stdin);
		scanf("%s", &file_dau_vao);
		
		FILE 	* con_tro_file_nen;
		FILE 	* con_tro_file_giai_nen;
		int		bang_tan_so[256];
		con_tro_file_giai_nen	=	fopen(file_giai_nen_huffman, "wb");
		con_tro_file_nen		=	fopen (file_dau_vao,"rb");
		int 	i = 0;
		int 	tong_so_bits_nen;
		
		fread(&tong_so_bits_nen, sizeof(int), 1,con_tro_file_nen );
		fread(bang_tan_so, sizeof(int), 256, con_tro_file_nen);
		
		struct  cay_huffman	*huffman;
		
		huffman 	=	xay_dung_cay_huffman(bang_tan_so);
		
		int	vi_tri_bit_hien_tai	=	8;
		struct 	cay_huffman	*nut_chay	=	huffman;
		int k;
		while(!feof(con_tro_file_nen))
		{
			int	ki_tu_ma_hoa;
			fread(&ki_tu_ma_hoa, sizeof(char), 1,con_tro_file_nen );
			if(tong_so_bits_nen < 8) {
				vi_tri_bit_hien_tai	=	tong_so_bits_nen;
			}	
			int dem_bits 	=	8;
			for(k=vi_tri_bit_hien_tai; k>0; k--)
			{
				int	bit	=	(ki_tu_ma_hoa >> (dem_bits-1) ) & 1;
				if( bit == 0)
				{
					nut_chay	=	nut_chay->con_trai;
				}
				else
				{
					nut_chay	=	nut_chay->con_phai;
				}
				if(kiem_tra_la_huffman(nut_chay) == 1)
				{
					fwrite(&(nut_chay->ki_tu), sizeof(char), 1, con_tro_file_giai_nen);
					nut_chay	=	huffman;
				}
				dem_bits--;
				tong_so_bits_nen--;
			}
		}
		fclose (con_tro_file_giai_nen);
		fclose (con_tro_file_nen);
		
		printf("\n ________________________Ket Qua Giai File_________________________ ");
	    printf("\n");
		printf("\n Giai Nen File Thanh Cong \n");
		printf("\n");
		printf("\n ________________________Ket Qua Giai File_________________________ ");
		
		lua_chon_menu	=	hien_thi_menu_con();
		if ( ( lua_chon_menu == 1 )	||	( lua_chon_menu == 0 ) )
		{
			break;
		}	
	}
	while( 1 );
	if ( lua_chon_menu == 1 )
	{
		main();
	}
	if ( lua_chon_menu == 0 )
	{
		exit(1);
	}
}

struct 	cay_huffman *copy_2_nut(struct	cay_huffman *nut_chuyen_den, struct cay_huffman *nut_nguon)
{
	nut_chuyen_den->ki_tu		=	nut_nguon->ki_tu;
	nut_chuyen_den->tan_so		=	nut_nguon->tan_so;
	nut_chuyen_den->con_trai	=	nut_nguon->con_trai;
	nut_chuyen_den->con_phai	=	nut_nguon->con_phai;
	
	return nut_chuyen_den;
}

void 	xay_dung_ma_huffman(struct cay_huffman *huffman, char chuoi_ma_hoa[], int index)
{
	if(huffman->con_trai != 0)
	{
		chuoi_ma_hoa[index]	=	'0';
		xay_dung_ma_huffman(huffman->con_trai, chuoi_ma_hoa, index + 1);
	}
	
	if(huffman->con_phai != 0)
	{
		chuoi_ma_hoa[index]	=	'1';
		xay_dung_ma_huffman(huffman->con_phai,  chuoi_ma_hoa, index + 1);
	}
	
	if(kiem_tra_la_huffman(huffman) == 1)
	{
		int i;
		bang_ma_hoa_huffman[huffman->ki_tu]	=	(char *) malloc(sizeof(char) * index);
		for(i=0; i<index; i++)
		{
			*(bang_ma_hoa_huffman[huffman->ki_tu] + i)	=	chuoi_ma_hoa[i];
		}
		*(bang_ma_hoa_huffman[huffman->ki_tu] + index)	=	'\0';
	}
}

struct  	cay_huffman *xay_dung_cay_huffman(int bang_tan_so[])
{
	struct	cay_huffman	*huffman;
	
	huffman		=	(struct cay_huffman *) malloc(sizeof(struct cay_huffman));
	huffman->ki_tu_tiep_theo	=	0;
	huffman->con_trai	=	0;
	huffman->con_phai	=	0;
	int i;
	for(i=0; i<256; i++)
	{
		if(bang_tan_so[i] > 0)
		{
			struct	cay_huffman *nut_moi;
			nut_moi		=	(struct cay_huffman *) malloc(sizeof(struct cay_huffman));
			nut_moi->con_trai	=	0;
			nut_moi->con_phai	=	0;
			nut_moi->ki_tu		=	i;
			nut_moi->tan_so		=	bang_tan_so[i];
			nut_moi->ki_tu_tiep_theo	=	huffman;
			huffman				=	nut_moi;
		}
				
	}
	
	huffman	=	sap_xep_cay_huffman(huffman);
	struct	cay_huffman *temp_huffman	=	huffman;
	
	while(temp_huffman->ki_tu_tiep_theo != 0 && temp_huffman->ki_tu_tiep_theo->ki_tu_tiep_theo !=0)
	{
		struct	cay_huffman	*nut_moi;
		nut_moi		=	(struct cay_huffman *) malloc(sizeof(struct cay_huffman));
		
		struct	cay_huffman	*con_trai_moi;
		con_trai_moi	=	(struct cay_huffman *) malloc(sizeof(struct cay_huffman));
		
		struct	cay_huffman	*con_phai_moi;
		con_phai_moi	=	(struct cay_huffman *) malloc(sizeof(struct cay_huffman));
		
		con_trai_moi	=	copy_2_nut(con_trai_moi, temp_huffman);
		con_phai_moi	=	copy_2_nut(con_phai_moi, temp_huffman->ki_tu_tiep_theo);
		
		nut_moi->con_trai	=	con_trai_moi;
		nut_moi->con_phai	=	con_phai_moi;
		nut_moi->ki_tu		=	256;
		nut_moi->tan_so		=	con_trai_moi->tan_so	+	con_phai_moi->tan_so;
		nut_moi->ki_tu_tiep_theo	=	temp_huffman->ki_tu_tiep_theo->ki_tu_tiep_theo;
		
		free(temp_huffman->ki_tu_tiep_theo);
		free(temp_huffman);
		
		temp_huffman		=	nut_moi;
		temp_huffman		=	sap_xep_cay_huffman(temp_huffman);
	}
	huffman	=	temp_huffman;
	return huffman;
}

struct		cay_huffman	*sap_xep_cay_huffman(struct	cay_huffman *huffman)
{
	struct	cay_huffman *bien_chay_1	=	huffman;
	
	while(bien_chay_1->ki_tu_tiep_theo->ki_tu_tiep_theo != 0)
	{
		struct	cay_huffman *bien_chay_2	=	bien_chay_1->ki_tu_tiep_theo;
		while(bien_chay_2->ki_tu_tiep_theo!=0)
		{
			if(bien_chay_1->tan_so > bien_chay_2->tan_so)
			{
				int	ki_tu	=	bien_chay_1->ki_tu;
				int	tan_so	=	bien_chay_1->tan_so;
				struct	cay_huffman *con_trai	=	bien_chay_1->con_trai;
				struct	cay_huffman *con_phai	=	bien_chay_1->con_phai;
				
				bien_chay_1->ki_tu		=	bien_chay_2->ki_tu;
				bien_chay_1->tan_so		=	bien_chay_2->tan_so;
				bien_chay_1->con_trai	=	bien_chay_2->con_trai;
				bien_chay_1->con_phai	=	bien_chay_2->con_phai;
				
				bien_chay_2->con_trai	=	con_trai;
				bien_chay_2->con_phai	=	con_phai;	
				bien_chay_2->ki_tu		=	ki_tu;
				bien_chay_2->tan_so		=	tan_so;
			}
			bien_chay_2	=	bien_chay_2->ki_tu_tiep_theo;
		}
		bien_chay_1	=	bien_chay_1->ki_tu_tiep_theo;
	}
	return	huffman;
}

int		dem_so_ki_tu_khac_nhau(int bang_tan_so[])
{
	int tong_so_ki_tu	=	0;
	int	i;
	for(i=0; i<256;i++)
	{
		if(bang_tan_so[i] > 0)
		{
			tong_so_ki_tu++;
		}
	}
	return	tong_so_ki_tu;
}

int 	kiem_tra_la_huffman(struct cay_huffman *nut_kiem_tra)
{
	if(nut_kiem_tra->con_trai == 0 && nut_kiem_tra->con_phai == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void 	in_bang_ma_hoa_huffman(char *bang_ma_hoa_huffman[], int bang_tan_so[])
{
	int i;
	for(i=0; i<256; i++) 
	{
		if(bang_ma_hoa_huffman[i] != 0)
		{
			printf("%3d %20s %5d \n", i, bang_ma_hoa_huffman[i], bang_tan_so[i]);
		}
	}
}