#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include "head.h"
using namespace std;
extern Game game;//ȫ��Ψһ��game���� 
pixel content[900][1200];
pixel Save[200][100];
int time_=0;
pixel convert_pixel(char b, char g, char r) {
	pixel p;
	p.b = b;
	p.g = g;
	p.r = r;
	return p;
}
void chartlet_robot(int row,int col,int dir,int height){//row,col��������˵ĺ������꣬dir������ 
	switch(dir){
		case 0:{ ifstream up;//������ķ�ʽ���ļ� 
	           	int i=0;
			 	up.open(up_robot,ifstream::in|ifstream::binary);
			    up.seekg(54,up.beg);//�ƶ�ָ��,���ļ���ͷ�ƶ�54�պõ���һ�����ؿ鿪ʼ��λ��
				char* buffer0 = new char[27000];
				up.read(buffer0,27000);
				for(int y=0;y<150;y++){
					for(int x=0;x<60;x++){
						Save[y][x] = convert_pixel(buffer0[i], buffer0[i + 1], buffer0[i + 2]);
						i=i+3;					
					}
				}
				int m,n;
				m=450-150*(row-col)+120;
				n=675-75*(col+row)+(height-1)*35;
				for(int y=0;y<150;y++){
					for(int x=0;x<60;x++){
						if(((Save[y][x].b==164)&&(Save[y][x].g==73)&&(Save[y][x].r==163))||
						   ((Save[y][x].b==180)&&(Save[y][x].g==106)&&(Save[y][x].r==178))||
						   ((Save[y][x].b==190)&&(Save[y][x].g==133)&&(Save[y][x].r==180))||
						   ((Save[y][x].b==190)&&(Save[y][x].g==132)&&(Save[y][x].r==180))||
						   ((Save[y][x].b==189)&&(Save[y][x].g==132)&&(Save[y][x].r==180))||
						   ((Save[y][x].b==188)&&(Save[y][x].g==131)&&(Save[y][x].r==179))||
						   ((Save[y][x].b==172)&&(Save[y][x].g==91)&&(Save[y][x].r==170))||
						   ((Save[y][x].b==164)&&(Save[y][x].g==74)&&(Save[y][x].r==163))||
						   ((Save[y][x].b==197)&&(Save[y][x].g==165)&&(Save[y][x].r==163))||
						   ((Save[y][x].b==178)&&(Save[y][x].g==101)&&(Save[y][x].r==175))||
						   ((Save[y][x].b==175)&&(Save[y][x].g==96)&&(Save[y][x].r==174))||
						   ((Save[y][x].b==180)&&(Save[y][x].g==107)&&(Save[y][x].r==176))||
						   ((Save[y][x].b==194)&&(Save[y][x].g==159)&&(Save[y][x].r==175))){
							continue;
						}
						else
					  content[y+n][x+m]=Save[y][x];
					}
				}	
				delete []buffer0;
			    up.close();
		        break;}
		case 1:{ifstream down;//������ķ�ʽ���ļ� 
			 	int i=0;
				 down.open(down_robot,ifstream::in|ifstream::binary);
			    down.seekg(54,down.beg);//�ƶ�ָ��,���ļ���ͷ�ƶ�54�պõ���һ�����ؿ鿪ʼ��λ��
				char*buffer1=new char[27000];
				down.read(buffer1,27000);
				for(int y=0;y<150;y++){
					for(int x=0;x<60;x++){
						Save[y][x]= convert_pixel(buffer1[i], buffer1[i + 1], buffer1[i + 2]);
						i=i+3;					
					}
				}
				int m,n;
				m=450-150*(row-col)+120;

				n=675-75*(col+row)+(height-1)*35;
				for(int y=0;y<150;y++){
					for(int x=0;x<60;x++){
						if(((Save[y][x].b==164)&&(Save[y][x].g==73)&&(Save[y][x].r==163))||
						   ((Save[y][x].b==180)&&(Save[y][x].g==106)&&(Save[y][x].r==178))||
						   ((Save[y][x].b==190)&&(Save[y][x].g==133)&&(Save[y][x].r==180))||
						   ((Save[y][x].b==190)&&(Save[y][x].g==132)&&(Save[y][x].r==180))||
						   ((Save[y][x].b==189)&&(Save[y][x].g==132)&&(Save[y][x].r==180))||
						   ((Save[y][x].b==188)&&(Save[y][x].g==131)&&(Save[y][x].r==179))||
						   ((Save[y][x].b==172)&&(Save[y][x].g==91)&&(Save[y][x].r==170))||
						   ((Save[y][x].b==164)&&(Save[y][x].g==74)&&(Save[y][x].r==163))||
						   ((Save[y][x].b==197)&&(Save[y][x].g==165)&&(Save[y][x].r==163))||
						   ((Save[y][x].b==178)&&(Save[y][x].g==101)&&(Save[y][x].r==175))||
						   ((Save[y][x].b==175)&&(Save[y][x].g==96)&&(Save[y][x].r==174))||
						   ((Save[y][x].b==180)&&(Save[y][x].g==107)&&(Save[y][x].r==176))||
						   ((Save[y][x].b==194)&&(Save[y][x].g==159)&&(Save[y][x].r==175))){
							continue;
						}
						else
						content[y+n][x+m]=Save[y][x];
					}
				}
				delete []buffer1;
			    down.close();
			break;}
		case 2:{ifstream le;//������ķ�ʽ���ļ� 
		        int i=0;
	            le.open(left_robot,ifstream::in|ifstream::binary);
			    le.seekg(54,le.beg);//�ƶ�ָ��,���ļ���ͷ�ƶ�54�պõ���һ�����ؿ鿪ʼ��λ��
				char*buffer2=new char[27000];
				le.read(buffer2,27000);
				for(int y=0;y<150;y++){
					for(int x=0;x<60;x++){
						Save[y][x]= convert_pixel(buffer2[i], buffer2[i + 1], buffer2[i + 2]);
						i=i+3;					
					}
				}
				int m,n;
				m=450-150*(row-col)+120;
				n=675-75*(col+row)+(height-1)*35;
				for(int y=0;y<150;y++){
					for(int x=0;x<60;x++){
						if(((Save[y][x].b==164)&&(Save[y][x].g==73)&&(Save[y][x].r==163))||
						   ((Save[y][x].b==180)&&(Save[y][x].g==106)&&(Save[y][x].r==178))||
						   ((Save[y][x].b==190)&&(Save[y][x].g==133)&&(Save[y][x].r==180))||
						   ((Save[y][x].b==190)&&(Save[y][x].g==132)&&(Save[y][x].r==180))||
						   ((Save[y][x].b==189)&&(Save[y][x].g==132)&&(Save[y][x].r==180))||
						   ((Save[y][x].b==188)&&(Save[y][x].g==131)&&(Save[y][x].r==179))||
						   ((Save[y][x].b==172)&&(Save[y][x].g==91)&&(Save[y][x].r==170))||
						   ((Save[y][x].b==164)&&(Save[y][x].g==74)&&(Save[y][x].r==163))||
						   ((Save[y][x].b==197)&&(Save[y][x].g==165)&&(Save[y][x].r==163))||
						   ((Save[y][x].b==178)&&(Save[y][x].g==101)&&(Save[y][x].r==175))||
						   ((Save[y][x].b==175)&&(Save[y][x].g==96)&&(Save[y][x].r==174))||
						   ((Save[y][x].b==180)&&(Save[y][x].g==107)&&(Save[y][x].r==176))||
						   ((Save[y][x].b==194)&&(Save[y][x].g==159)&&(Save[y][x].r==175))){
							continue;
						}
						else
						content[y+n][x+m]=Save[y][x];
					}
				}
				delete []buffer2;
			    le.close();
			    break;}
		case 3:{ifstream ri;//������ķ�ʽ���ļ� 
			 	int i=0;
				 ri.open(right_robot,ifstream::in|ifstream::binary);
			    ri.seekg(54,ri.beg);//�ƶ�ָ��,���ļ���ͷ�ƶ�54�պõ���һ�����ؿ鿪ʼ��λ��
				char*buffer3=new char[27000];
				ri.read(buffer3,27000);
				for(int y=0;y<150;y++){
					for(int x=0;x<60;x++){
						Save[y][x] = convert_pixel(buffer3[i], buffer3[i + 1], buffer3[i + 2]);
						i=i+3;					
					}
				}
				int m,n;
				m=450-150*(row-col)+120;
				n=675-75*(col+row)+(height-1)*35;
				for(int y=0;y<150;y++){
					for(int x=0;x<60;x++){
						if(((Save[y][x].b==164)&&(Save[y][x].g==73)&&(Save[y][x].r==163))||
						   ((Save[y][x].b==180)&&(Save[y][x].g==106)&&(Save[y][x].r==178))||
						   ((Save[y][x].b==190)&&(Save[y][x].g==133)&&(Save[y][x].r==180))||
						   ((Save[y][x].b==190)&&(Save[y][x].g==132)&&(Save[y][x].r==180))||
						   ((Save[y][x].b==189)&&(Save[y][x].g==132)&&(Save[y][x].r==180))||
						   ((Save[y][x].b==188)&&(Save[y][x].g==131)&&(Save[y][x].r==179))||
						   ((Save[y][x].b==172)&&(Save[y][x].g==91)&&(Save[y][x].r==170))||
						   ((Save[y][x].b==164)&&(Save[y][x].g==74)&&(Save[y][x].r==163))||
						   ((Save[y][x].b==197)&&(Save[y][x].g==165)&&(Save[y][x].r==163))||
						   ((Save[y][x].b==178)&&(Save[y][x].g==101)&&(Save[y][x].r==175))||
						   ((Save[y][x].b==175)&&(Save[y][x].g==96)&&(Save[y][x].r==174))||
						   ((Save[y][x].b==180)&&(Save[y][x].g==107)&&(Save[y][x].r==176))||
						   ((Save[y][x].b==194)&&(Save[y][x].g==159)&&(Save[y][x].r==175))){
							continue;
						}
						else
						content[y+n][x+m]=Save[y][x];
					}
				}
				delete []buffer3;
			    ri.close();
			break;
	}}
}; 
void draw_a_normal_cell(int row,int col,int height,int exist_light){
	 if(height==0)			 return;
	 else{
	 	for(int i=1;i<height;i++){
	 		for(int k=450+(col-row)*150,j=675-75*(col+row)+(i-1)*35;j<=675-75*(col+row)+(i-1)*35+35;j++){//дѭ�� 
			     for(int y=j,x=k;x<=k+150;y--,x+=2){
			     		if(y==j||j==675-75*(col+row)+(i-1)*35||j==675-75*(col+row)+(i-1)*35+35||y==j-75||y==j-1||y==j-74||j==675-75*(col+row)+(i-1)*35+34||j==675-75*(col+row)+(i-1)*35+1){
					content[y][x].b=0;
 		   			content[y][x].g=0;
 		   			content[y][x].r=0;
 		   			content[y-1][x-1].b=0;
 		   			content[y-1][x-1].g=0;
 		   			content[y-1][x-1].r=0;
 		   			content[y-1][x].b=0;
 		   			content[y-1][x].g=0;
 		   			content[y-1][x].r=0;
 		   			content[y][x-1].b=0;
 		   			content[y][x-1].g=0;
 		   			content[y][x-1].r=0; 
			        }
			        else{
		 		 	content[y][x].b=0;
 		   			content[y][x].g=0;
 		   			content[y][x].r=255;
 		   			content[y-1][x-1].b=0;
 		   			content[y-1][x-1].g=0;
 		   			content[y-1][x-1].r=255;
 		   			content[y-1][x].b=0;
 		   			content[y-1][x].g=0;
 		   			content[y-1][x].r=255;
 		   			content[y][x-1].b=0;
 		   			content[y][x-1].g=0;
 		   			content[y][x-1].r=255; 	 
				  }
				  }
	         }
	         for(int k=600+(col-row)*150,j=600-75*(col+row)+(i-1)*35;j<=600-75*(col+row)+(i-1)*35+35;j++){
	         	for(int y=j,x=k;x<k+150;x+=2,y++){
	         		if(y==j||j==600-75*(col+row)+(i-1)*35||j==600-75*(col+row)+(i-1)*35+35||y==j+75||y==j+1||y==j+74||j==600-75*(col+row)+(i-1)*35+34||j==600-75*(col+row)+(i-1)*35+1){
	         			content[y][x].b=0;
 		   			content[y][x].g=0;
 		   			content[y][x].r=0;
 		   			content[y-1][x-1].b=0;
 		   			content[y-1][x-1].g=0;
 		   			content[y-1][x-1].r=0;
 		   			content[y-1][x].b=0;
 		   			content[y-1][x].g=0;
 		   			content[y-1][x].r=0;
 		   			content[y][x-1].b=0;
 		   			content[y][x-1].g=0;
 		   			content[y][x-1].r=0; 
					 }
	         		else{
				    content[y][x].b=0;
 		   			content[y][x].g=0;
 		   			content[y][x].r=255;
 		   			content[y-1][x-1].b=0;
 		   			content[y-1][x-1].g=0;
 		   			content[y-1][x-1].r=255;
 		   			content[y-1][x].b=0;
 		   			content[y-1][x].g=0;
 		   			content[y-1][x].r=255;
 		   			content[y][x-1].b=0;
 		   			content[y][x-1].g=0;
 		   			content[y][x-1].r=255; 
				    }
				 }
			 }
		 }
		for(int i=450+(col-row)*150,j=675-75*(col+row)+(height-1)*35;i<=600+(col-row)*150;i+=2,j--){//дѭ�� 
			     for(int y=j,x=i;x<i+150;y++,x+=2){
 	       				if(i==450-(row-col)*150|| i==452-(row-col)*150||i==598-(row-col)*150||i==600-(row-col)*150||y==j||y==j-1||x==i+148||x==i+146){
					content[y][x].b=0;
 		   			content[y][x].g=0;
 		   			content[y][x].r=0;
 		   			content[y-1][x-1].b=0;
 		   			content[y-1][x-1].g=0;
 		   			content[y-1][x-1].r=0;
 		   			content[y-1][x].b=0;
 		   			content[y-1][x].g=0;
 		   			content[y-1][x].r=0;
 		   			content[y][x-1].b=0;
 		   			content[y][x-1].g=0;
 		   			content[y][x-1].r=0; 
			        }
		   			else
		   			if(exist_light==-1){
		   			content[y][x].b=255;
 		   			content[y][x].g=0;
 		   			content[y][x].r=0;
 		   			content[y-1][x-1].b=255;
 		   			content[y-1][x-1].g=0;
 		   			content[y-1][x-1].r=0;
 		   			content[y-1][x].b=255;
 		   			content[y-1][x].g=0;
 		   			content[y-1][x].r=0;
 		   			content[y][x-1].b=255;
 		   			content[y][x-1].g=0;
 		   			content[y][x-1].r=0; 
		           }
		           else{
		           	content[y][x].b=0;
 		   			content[y][x].g=255;
 		   			content[y][x].r=255;
 		   			content[y-1][x-1].b=0;
 		   			content[y-1][x-1].g=255;
 		   			content[y-1][x-1].r=255;
 		   			content[y-1][x].b=0;
 		   			content[y-1][x].g=255;
 		   			content[y-1][x].r=255;
 		   			content[y][x-1].b=0;
 		   			content[y][x-1].g=255;
 		   			content[y][x-1].r=255; 
				   }
		   }
         }
}
//�����content��ֱ���ÿ�����Ӧ��û��ʲô��ͻ�Ͳ����ɣ� 
}	
//ƴ��---���ж������ǵڼ���ͼ�ˣ��Ӵ�autosave��ʼ���0��ͼ��Ȼ��ÿ�μ�1����������ȥ�� 
void draw_the_original_map(){//���������ȫ����game.map_initȥ����Ѱ�� 
	ofstream map;
	map.open(origin,ios::binary);//��ʱ��ôд��֮���ٸ�,���Ǳ����ʼ��ͼ����������--�����������һЩ�� 
	BMPFileHeader bfh={{'B','M'},1200*900*3+0x36,0,0,0x36};
	BMPInfoHeader bih={0x28,1200,900,1,24,0,1200*900*3,0};
	map.write((char*)&bfh,14);
	map.write((char*)&bih,40);
	for(int y=899;y>=0;y--){
		for(int x=0;x<1200;x++){
			content[y][x].r=164;
			content[y][x].g=73;
			content[y][x].b=163;
		}
	}//д��һ����ɫ����	
	for(int i=0;i<game.map_init.row;i++){
		for(int j=0;j<game.map_init.col;j++){
			draw_a_normal_cell(i,j,game.map_init.cells[i][j].height,game.map_init.cells[i][j].light_id);
			if(game.map_init.cells[i][j].robot){
					chartlet_robot(game.map_init.robot.pos.y,game.map_init.robot.pos.x,game.map_init.robot.dir,game.map_init.cells[i][j].height);  
			}
		}
	}  
	map.write((char*)content,sizeof(content));
	map.close();
	return;
}
/*��������֡��Ӵ��������������ĵƵĻ���---��������ͨ�ĵơ�*/
void string_splicing(string path,int id,string savepath,int time){
  for(int i=0;i<=100;i++){
  	if(path[i]=='%'&&path[i+2]=='d'){
  		int n=path[i+1]-'0';//������̸�������ˣ�ҪС���ַ���int֮��Ĳ�� 
  		if(id>=(int)pow(10,n+1)){
  		savepath=path.substr(0,i)+std::to_string(id+time)+".bmp";
		  break;}
	  else{//��ͳ����������Ǽ�λ�����ٸ���n����Ҫ���ϼ����� 
	  	int c=get_digit(id+time);
	  	savepath=path.substr(0,i);
	  	for(int i=1;i<=n-c;i++){
	  		savepath=savepath+'0';
		  }
		  savepath=savepath+std::to_string(id+time)+".bmp";
		  break;
	  }
    }
  }
  save(savepath);
}

void draw_a_lighted_cell(int row,int col,int height){
	 if(height==0)			 return;
	 else{
	 	for(int i=1;i<height;i++){
	 		for(int k=450-(row-col)*150,j=675-75*(col+row)+(i-1)*35;j<=675-75*(col+row)+(i-1)*35+35;j++){//дѭ�� 
			     for(int y=j,x=k;x<=k+150;y--,x+=2){
			     		if(y==j||j==675-75*(col+row)+(i-1)*35||j==675-75*(col+row)+(i-1)*35+35||y==j-75||y==j-1||y==j-74||j==675-75*(col+row)+(i-1)*35+34||j==675-75*(col+row)+(i-1)*35+1){
					content[y][x].b=0;
 		   			content[y][x].g=0;
 		   			content[y][x].r=0;
 		   			content[y-1][x-1].b=0;
 		   			content[y-1][x-1].g=0;
 		   			content[y-1][x-1].r=0;
 		   			content[y-1][x].b=0;
 		   			content[y-1][x].g=0;
 		   			content[y-1][x].r=0;
 		   			content[y][x-1].b=0;
 		   			content[y][x-1].g=0;
 		   			content[y][x-1].r=0; 
			        }
			        else{
		 		 	content[y][x].b=0;
 		   			content[y][x].g=0;
 		   			content[y][x].r=255;
 		   			content[y-1][x-1].b=0;
 		   			content[y-1][x-1].g=0;
 		   			content[y-1][x-1].r=255;
 		   			content[y-1][x].b=0;
 		   			content[y-1][x].g=0;
 		   			content[y-1][x].r=255;
 		   			content[y][x-1].b=0;
 		   			content[y][x-1].g=0;
 		   			content[y][x-1].r=255; 	 
				  }
				  }
	         }
	         for(int k=600-(row-col)*150,j=600-75*(col+row)+(i-1)*35;j<=600-75*(col+row)+(i-1)*35+35;j++){
	         	for(int y=j,x=k;x<k+150;x+=2,y++){
	         		if(y==j||j==600-75*(col+row)+(i-1)*35||j==600-75*(col+row)+(i-1)*35+35||y==j+75||y==j+1||y==j+74||j==600-75*(col+row)+(i-1)*35+34||j==600-75*(col+row)+(i-1)*35+1){
	         			content[y][x].b=0;
 		   			content[y][x].g=0;
 		   			content[y][x].r=0;
 		   			content[y-1][x-1].b=0;
 		   			content[y-1][x-1].g=0;
 		   			content[y-1][x-1].r=0;
 		   			content[y-1][x].b=0;
 		   			content[y-1][x].g=0;
 		   			content[y-1][x].r=0;
 		   			content[y][x-1].b=0;
 		   			content[y][x-1].g=0;
 		   			content[y][x-1].r=0; 
					 }
	         		else{
				    content[y][x].b=0;
 		   			content[y][x].g=0;
 		   			content[y][x].r=255;
 		   			content[y-1][x-1].b=0;
 		   			content[y-1][x-1].g=0;
 		   			content[y-1][x-1].r=255;
 		   			content[y-1][x].b=0;
 		   			content[y-1][x].g=0;
 		   			content[y-1][x].r=255;
 		   			content[y][x-1].b=0;
 		   			content[y][x-1].g=0;
 		   			content[y][x-1].r=255; 
				    }
				 }
			 }
		 }
		for(int i=450-(row-col)*150,j=675-75*(col+row)+(height-1)*35;i<=600-(row-col)*150;i+=2,j--){//дѭ�� 
			     for(int y=j,x=i;x<i+150;y++,x+=2){
 	       				if(i==450-(row-col)*150|| i==452-(row-col)*150||i==598-(row-col)*150||i==600-(row-col)*150||y==j||y==j-1||x==i+148||x==i+146){
					content[y][x].b=0;
 		   			content[y][x].g=0;
 		   			content[y][x].r=0;
 		   			content[y-1][x-1].b=0;
 		   			content[y-1][x-1].g=0;
 		   			content[y-1][x-1].r=0;
 		   			content[y-1][x].b=0;
 		   			content[y-1][x].g=0;
 		   			content[y-1][x].r=0;
 		   			content[y][x-1].b=0;
 		   			content[y][x-1].g=0;
 		   			content[y][x-1].r=0; 
			        }
		   			else{
		           	content[y][x].b=0;
 		   			content[y][x].g=128;
 		   			content[y][x].r=255;
 		   			content[y-1][x-1].b=0;
 		   			content[y-1][x-1].g=128;
 		   			content[y-1][x-1].r=255;
 		   			content[y-1][x].b=0;
 		   			content[y-1][x].g=128;
 		   			content[y-1][x].r=255;
 		   			content[y][x-1].b=0;
 		   			content[y][x-1].g=128;
 		   			content[y][x-1].r=255; 
				   }
		   }
         }
}
	return;
}
string to_string(int n){
	int m=n;
	int i=0,j=0;
	char s[100];
	char ss[100];
	while(m>0)
	{
		s[i++]= m%10 + '0';
		m/=10;
	}
	s[i]='\0';
 
	i=i-1;
	while(i>=0)
	{
		ss[j++]=s[i--];
	}
	ss[j]='\0';
 
	return ss;
}
int get_digit(int number){
	if(number==0){
		return 0;
	}
	int digit;
	for(int i=1;i<=10;i++){
		if((number/(int)pow(10,i))==0){
			digit=i;
            break;		
		}
	}
	return digit;
}//ͳ��n��λ�� 
void save(string path) {
	 fstream map;//�������ڣ������������������û�гɹ����ļ� ������·���������ʱ��Ҫ��/ \���ż��� 
	 map.open(path.c_str(),ios::binary| std::ios::out);
    BMPFileHeader bfh={{'B','M'},1200*900*3+0x36,0,0,0x36};
	BMPInfoHeader bih={0x28,1200,900,1,24,0,1200*900*3,0};
	map.write((char*)&bfh,14);
	map.write((char*)&bih,40);
	for(int y=899;y>=0;y--){
		for(int x=0;x<1200;x++){
			content[y][x].r=164;
			content[y][x].g=73;
			content[y][x].b=163;
		}
	}//д��һ����ɫ����	
	for(int i=0;i<game.map_run.row;i++){
		for(int j=0;j<game.map_run.col;j++){
                 			if(game.map_init.cells[i][j].light_id==-1){//���һ��ʼû�е�-��ô��ʼ���ն�����ͨ�ķ��飬��ô�ͼ�򵥵��ػ�һ����ͨ���� 
			draw_a_normal_cell(i,j,game.map_init.cells[i][j].height,game.map_init.cells[i][j].light_id);
			}
			else {//����Ǵ������ĵ�-���ǵ�������ɫ 
				if(game.map_run.lights[game.map_run.cells[i][j].light_id].lighten){
					draw_a_lighted_cell(i,j,game.map_init.cells[i][j].height);//���Ƶĺ���-��һ����ɫ���� 
				}
				else{
				draw_a_normal_cell(i,j,game.map_init.cells[i][j].height,game.map_init.cells[i][j].light_id);
			   }
			}

		}
	}
	   
	for(int i=0;i<game.map_run.row;i++){
		for(int j=0;j<game.map_run.col;j++){
			if(game.map_run.cells[i][j].robot){
					chartlet_robot(game.map_run.robot.pos.y,game.map_run.robot.pos.x,game.map_run.robot.dir,game.map_init.cells[i][j].height);  
			}
		}	
	}
	map.write((char*)content,sizeof(content));
	map.close();
	return;
	 // ����д�����ԣ�Ӧ�����ø�����ȫ�ֱ�����ȡ��ͼ״̬��
	 //�������������ʱ�� 
}
void auto_save(){
	if(game.save_path.empty()) return;//�ر��Զ�����ĵȼ۱�ʾ 
	else{
		string auto_path;
		string_splicing(game.save_path,game.auto_save_id,auto_path,time_);//�߼�����ϸ����΢�� 
		//path�ɺ������ɣ��ȴ���߼���----const char  ---������string  
	    time_++; 
	}
}

