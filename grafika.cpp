#include <GL/glut.h>

#include <glm/glm.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <assert.h>



#include "triangulate.h"



static const float EPSILON=0.0000000001f;



// Pop up menu identifiers

int  mainMenu, ACTION_menu, LINE_COLOR_menu, FILL_COLOR_menu;



// Constant definitions for Menus

#define RED 1

#define GREEN 2

#define BLUE 3

#define ORANGE 4

#define BLACK 5

#define WHITE 6

#define PINK 7

#define DARK_GRAY 8

#define LIGHT_GRAY 9

#define BROWN 10

#define BARNEY_PURPLE 11

#define PASTEL_PINK 12

#define PUMPKIN_ORANGE 13

#define GOLD 14

#define LIME 15

#define AQUA 16



#define POLYGON_option 1

#define CLIPPING_option 2

#define Exit_option 3



///////////////////////////////////////////////////////////////////////

// dimiourgia twn structs

struct point_s{

	int point_num = 0;

	int max_point_num = 0;

	int state = 0;

	float x = 0;

	float y = 0;

};

typedef struct point_s point_t;



struct triangle_s{

	int triangle_num = 0;

	float x1 = 0.0;

	float y1 = 0.0;

	float x2 = 0.0;

	float y2 = 0.0;

	float x3 = 0.0;

	float y3 = 0.0;

};

typedef struct triangle_s triangle_t;



struct poligon_s{

	int poligon_exists = 0;

	int poligon_num = 0;

	int max_poligon_num = 0;

	int poligon_id = 0;

	float r_f = 0.0;

	float g_f = 0.0;

	float b_f = 0.0;

	float r_l = 0.0;

	float g_l = 0.0;

	float b_l = 0.0;

	point_t* point_array = NULL;

	triangle_t* triangle_array = NULL;

};

typedef struct poligon_s poligon_t;

////////////////////////////////////////////////////////////////////////////////////////



poligon_t* poligon_array = NULL;



int windowWidth  = 500;     // Windowed mode's width

int windowHeight = 600;     // Windowed mode's height

int windowPosX   = 50;      // Windowed mode's top-left corner x

int windowPosY   = 50;      // Windowed mode's top-left corner y



bool fullScreenMode = false; // Full-screen or windowed mode?



// menu status

int menuFlag = 0;



int show_triangles = 0;



int point_f = 0;

int new_poligon = 0;

int new_clipping = 0;

int draw_clipper_points = 0;

point_t wmin ;

point_t wmax ;

float motion_x = 0.5;

float motion_y = 0.5;

int motion_f = 0;



//////////////

int paradigma = 0;

int lll = 0;

//////////////



float red_f = 1.0;

float green_f = 1.0;

float blue_f = 1.0;



float red_l = 0.0;

float green_l = 0.0;

float blue_l = 0.0;



int final_line_intersection();

void delete_poligon();

void create_poligon_array();

void create_point_array(int position);

void add_poligon(float r_f, float g_f, float b_f, float r_l, float g_l, float b_l);

void add_point(int position, float x, float y);

void new_poligon_off();

void delete_poligon();

int get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y);

int final_line_intersection();

void mouse( int button, int state, int x, int y );

void keyboard(unsigned char key, int x, int y);

void specialKeys(int key, int x, int y);

void point(float x, float y);

void line(float x1, float y1, float x2, float y2, float r, float g, float b);

void print_poligon_line(int id);

void print_line(int id);

void print_point(int id);

void triangulation(float x1, float y1, float x2, float y2, float x3, float y3 );

void triangulation_poligons(int id, int re_triangl);

void show_triangulation_poligons(int id);

void final_triangulation_poligons();

void processMenuStatus(int status, int x, int y);

void processACTIONMenu(int option);

void processLINE_COLORMenu(int option);

void processFILL_COLORMenu(int option);

void processMainMenu(int option);

void createPopupMenus();

void display();

void reshape( int w, int h);

void initOpenGL();

void start_clipping(point_t wMin, point_t wMax);

void print_clipper_squer();

//float Triangulate::Area(const Vector2dVector &contour);

//bool Triangulate::InsideTriangle(float Ax, float Ay,float Bx, float By,float Cx, float Cy,float Px, float Py);

//bool Triangulate::Snip(const Vector2dVector &contour,int u,int v,int w,int n,int *V);

//bool Triangulate::Process(const Vector2dVector &contour,Vector2dVector &result);



////////////////////////////////////////////////////////////////////////

//dimiourgia tou pinaka me ta poligona

void create_poligon_array(){

	poligon_array = (poligon_t*)malloc(6*sizeof(poligon_t));

	poligon_array[0].max_poligon_num = 5;

	poligon_array[0].poligon_num = 0;

	poligon_array[0].poligon_id = 1;

}



/////////////////////////////////////////////////////////////////////

//dimiourgia tou pinaka me ta points gia to kathe poligono

void create_point_array(int position){



	poligon_array[position].point_array = (point_t*)malloc(6*sizeof(point_t));

	poligon_array[position].point_array[0].max_point_num = 5;

	poligon_array[position].point_array[0].point_num = 0;

}



/////////////////////////////////////////////////////////////////////

//prosthiki enos poligonou me orismata ta xromata gia to fill kai gia to perigrama

void add_poligon(float r_f, float g_f, float b_f, float r_l, float g_l, float b_l){



	int next_position = poligon_array[0].poligon_num + 1;



	if(next_position > poligon_array[0].max_poligon_num){

		int array_size = poligon_array[0].max_poligon_num;

		poligon_array = (poligon_t*)realloc(poligon_array, (array_size+6)*sizeof(poligon_t));

		poligon_array[0].max_poligon_num += 5;

	}



	poligon_array[0].poligon_num ++;

	poligon_array[next_position].poligon_id = poligon_array[0].poligon_id;

	poligon_array[next_position].poligon_exists = 1;

	poligon_array[next_position].r_f = r_f;

	poligon_array[next_position].g_f = g_f;

	poligon_array[next_position].b_f = b_f;

	poligon_array[next_position].r_l = r_l;

	poligon_array[next_position].g_l = g_l;

	poligon_array[next_position].b_l = b_l;



	create_point_array(next_position);

}



/////////////////////////////////////////////////////////////////////

//prosthiki enos point sto poligono me id = posistion kai x,y oi sintetagmenes tou

void add_point(int position, float x, float y){



	int next_position = poligon_array[position].point_array[0].point_num + 1;



	if(next_position > poligon_array[position].point_array[0].max_point_num){

		int array_size = poligon_array[position].point_array[0].max_point_num;

		poligon_array[position].point_array = (point_t*)realloc(poligon_array[position].point_array, (array_size+6)*sizeof(point_t));

		poligon_array[position].point_array[0].max_point_num += 5;

	}



	poligon_array[position].point_array[0].point_num ++;

	poligon_array[position].point_array[next_position].x = x;

	poligon_array[position].point_array[next_position].y = y;

	poligon_array[position].point_array[next_position].state = 0;



	printf("-> poligon %d  --> max point = %d\n",poligon_array[0].poligon_id, poligon_array[position].point_array[0].max_point_num);

	printf("              --> point num = %d\n\n", poligon_array[position].point_array[0].point_num);

}



/////////////////////////////////////////////////////////////////////

//otan kanoume apokopi ananewnoume ton kentriko pinaka me ta kenourgia shmeia

void udate_point_array(int id, point_t* new_points){



	int new_poly_size = new_points[0].point_num;



	poligon_array[id].point_array = (point_t*)realloc(new_points, (new_poly_size+1)*sizeof(point_t));



	poligon_array[id].point_array[0].point_num = new_poly_size;



	triangulation_poligons(id, 1);

}



/////////////////////////////////////////////////////////////////////

//to kaloume otan teliosoume tin prosthiki shmeiwn se ena poligono 

//kai elegxei an h teleftea grammh temnei tis upoloipes. An nai to aporriptei

void new_poligon_off(){

	

    new_poligon = 0;

    if(final_line_intersection()){

		delete_poligon();

	}

	if(poligon_array[poligon_array[0].poligon_id].point_array[0].point_num < 3){

		delete_poligon();

	}

	triangulation_poligons(poligon_array[0].poligon_id, 0);

    poligon_array[0].poligon_id ++;



    createPopupMenus();



	red_f = 1.0;

    green_f = 1.0;

    blue_f = 1.0;



	red_l = 0.0;

	green_l = 0.0;

	blue_l = 0.0;

}



/////////////////////////////////////////////////////////////////////

//kaleitai stin periptosi pou exoume tomh dyo plevrwn tou poligounou 

//kai to telefteo poligono pou kaname add

void delete_poligon(){

	int id = poligon_array[0].poligon_id;

	free(poligon_array[id].point_array);

	poligon_array[0].poligon_id --;

	poligon_array[0].poligon_num --;

	if(new_poligon){

    	new_poligon_off();

    }

}



/////////////////////////////////////////////////////////////////////

//dinoume tessera shmeia kai mas epistrefei ean ta dio efthygrama tmhmata pou prokiptoun temnontai 'h oxi...

int get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y)

{

    float s1_x, s1_y, s2_x, s2_y;

    s1_x = p1_x - p0_x;     

    s1_y = p1_y - p0_y;

    s2_x = p3_x - p2_x;     

    s2_y = p3_y - p2_y;



    float s, t;

    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);

    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);



    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)

    {

        return 1;

    }



    return 0;

}

/////////////////////////////////////////////////////////////////////

//olo afto sta sxolia ypotithete oti tha xorize ena poligono se polla ean proekiptan polla poligona meta tin apokopi

//alla den doulepse pote.... :( 

/*void split_poligon(int id){



	int see_all_points = 0;

	int start = 0;

	int add = 0;

	int finish = 0;



	int point_num = poligon_array[id].point_array[0].point_num;

	int see_point_num = 0;

	int current_point = 0;



	while(!see_all_points){



		if(poligon_array[id].point_array[current_point+1].state == 2){

			start = 1;

		}else{

			current_point = (current_point+1) % point_num;

		}

		if(start){

			if(poligon_array[id].point_array[current_point+1].state == 2){

				float r_f = poligon_array[id].r_f; 

				float g_f = poligon_array[id].g_f; 

				float b_f = poligon_array[id].b_f;  

				float r_l = poligon_array[id].r_l;  

				float g_l = poligon_array[id].g_l;  

				float b_l = poligon_array[id].b_l; 

				add_poligon(r_f, g_f, b_f, r_l, g_l, b_l);



				int position = poligon_array[0].poligon_id; 

				float x = poligon_array[id].point_array[current_point].x;

				float y = poligon_array[id].point_array[current_point].y;

				add_point(position, x, y);



				see_point_num ++;

				current_point = (current_point+1) % point_num;



			}else if(poligon_array[id].point_array[current_point+1].state == 0){



				int position = poligon_array[0].poligon_id; 

				float x = poligon_array[id].point_array[current_point].x;

				float y = poligon_array[id].point_array[current_point].y;

				add_point(position, x, y);



				see_point_num ++;

				current_point = (current_point+1) % point_num;

				

			}else if(poligon_array[id].point_array[current_point+1].state == 1){



				int position = poligon_array[0].poligon_id; 

				float x = poligon_array[id].point_array[current_point].x;

				float y = poligon_array[id].point_array[current_point].y;

				add_point(position, x, y);



				new_poligon_off();



				see_point_num ++;

				current_point = (current_point+1) % point_num;

			}

		}	

		if(see_point_num == point_num){

			see_point_num = 1;

		}

	}

	poligon_array[id].poligon_exists = 0;

}



/////////////////////////////////////////////////////////////////////

//afto ypotithete pali oti tha anixneve an ena poligono pou prokyptei apo tin apokopi prepei na xwristei i oxi....

//alla oute ki afto doulepse.............. 



void check_for_intersection(int id){



	int answer = 0;



	int point_num = poligon_array[id].point_array[0].point_num;



	if(point_num > 3){



		for(int i = 0; i<point_num; i++){

			int k = (i+1) % point_num; 



			float p0_x = poligon_array[id].point_array[i+1].x;

			float p0_y = poligon_array[id].point_array[i+1].y;

			float p1_x = poligon_array[id].point_array[k+1].x;

			float p1_y = poligon_array[id].point_array[k+1].y;

			float p2_x, p2_y, p3_x, p3_y;



			for(int I = 0; I<point_num; I++){

				int K = (I+1) % point_num; 



				if((i != I)){



					p2_x = poligon_array[id].point_array[I+1].x;

					p2_y = poligon_array[id].point_array[I+1].y;

					p3_x = poligon_array[id].point_array[K+1].x;

					p3_y = poligon_array[id].point_array[K+1].y;



				



	



					if(((p0_x == wmin.x) && (p1_x == wmin.x) && (p2_x == wmin.x) && (p3_x == wmin.x))){

						poligon_array[id].point_array[i+1].state = 1;

						poligon_array[id].point_array[k+1].state = 2;

						poligon_array[id].point_array[I+1].state = 1;

						poligon_array[id].point_array[K+1].state = 2;



						answer = 1;



						printf("\nx point %d = 1\n",i+1);

						printf("x point %d = 2\n",k+1);

						printf("x point %d = 1\n",I+1);

						printf("x point %d = 2\n\n",K+1);

					}



					if(((p0_x == wmax.x) && (p1_x == wmax.x) && (p2_x == wmax.x) && (p3_x == wmax.x))){

						poligon_array[id].point_array[i+1].state = 1;

						poligon_array[id].point_array[k+1].state = 2;

						poligon_array[id].point_array[I+1].state = 1;

						poligon_array[id].point_array[K+1].state = 2;



						answer = 1;



						printf("\nx point %d = 1\n",i+1);

						printf("x point %d = 2\n",k+1);

						printf("x point %d = 1\n",I+1);

						printf("x point %d = 2\n\n",K+1);

					}



					if(((p0_y == wmin.y) && (p1_y == wmin.y) && (p2_y == wmin.y) && (p3_y == wmin.y))){

						poligon_array[id].point_array[i+1].state = 1;

						poligon_array[id].point_array[k+1].state = 2;

						poligon_array[id].point_array[I+1].state = 1;

						poligon_array[id].point_array[K+1].state = 2;



						answer = 1;



						printf("y point %d = 1\n",i+1);

						printf("y point %d = 2\n",k+1);

						printf("y point %d = 1\n",I+1);

						printf("y point %d = 2\n",K+1);

					}



					if(((p0_y == wmax.y) && (p1_y == wmax.y) && (p2_y == wmax.y) && (p3_y == wmax.y))){

						poligon_array[id].point_array[i+1].state = 1;

						poligon_array[id].point_array[k+1].state = 2;

						poligon_array[id].point_array[I+1].state = 1;

						poligon_array[id].point_array[K+1].state = 2;



						answer = 1;



						printf("y point %d = 1\n",i+1);

						printf("y point %d = 2\n",k+1);

						printf("y point %d = 1\n",I+1);

						printf("y point %d = 2\n",K+1);

					}

				}

			}

		}  

	}

	if(answer){

		split_poligon(id);

	}

}*/



/////////////////////////////////////////////////////////////////////

//kaleitai kathe fora pou prosthetoume mia kainouria akmi sto poligono mas .. kai apanta ean temnei kapoia allh  'h oxi

int final_line_intersection(){

	int i;

	int id = poligon_array[0].poligon_id;

	int point_num = poligon_array[id].point_array[0].point_num;



	if(point_num >= 4){



		if(new_poligon){

			float p0_x = poligon_array[id].point_array[point_num].x;

			float p0_y = poligon_array[id].point_array[point_num].y;

			float p1_x = poligon_array[id].point_array[point_num-1].x;

			float p1_y = poligon_array[id].point_array[point_num-1].y;

			float p2_x, p2_y, p3_x, p3_y;



			for(i=2; i<point_num-1; i++){

				

				p2_x = poligon_array[id].point_array[i].x;

				p2_y = poligon_array[id].point_array[i].y;

				p3_x = poligon_array[id].point_array[i-1].x;

				p3_y = poligon_array[id].point_array[i-1].y;



				if(get_line_intersection(p0_x, p0_y, p1_x, p1_y, p2_x, p2_y, p3_x, p3_y)){

					return 1;

				}

			}

		}else{



			float p0_x = poligon_array[id].point_array[point_num].x;

			float p0_y = poligon_array[id].point_array[point_num].y;

			float p1_x = poligon_array[id].point_array[1].x;

			float p1_y = poligon_array[id].point_array[1].y;

			float p2_x, p2_y, p3_x, p3_y;



			for(i=3; i<point_num; i++){

				

				p2_x = poligon_array[id].point_array[i].x;

				p2_y = poligon_array[id].point_array[i].y;

				p3_x = poligon_array[id].point_array[i-1].x;

				p3_y = poligon_array[id].point_array[i-1].y;



				if(get_line_intersection(p0_x, p0_y, p1_x, p1_y, p2_x, p2_y, p3_x, p3_y)){

					return 1;

				}

			}

		}

	}

	return 0;

}



///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////

//oi pente parakato sinartiseis einai ypefthines gia tin apokopi 

//me kiria tin start_cliping pou pernei san orisma tis dio diagonies 

//korifes tou paralilogramou apokopis kai telika enimerwnei tous vasikous pinakes me ta nea shmeia





// Returns x-value of point of intersectipn of two 

// lines 

float x_intersect(float x1, float y1, float x2, float y2, 

                float x3, float y3, float x4, float y4) 

{ 

    float num = (x1*y2 - y1*x2) * (x3-x4) - 

              (x1-x2) * (x3*y4 - y3*x4); 

    float den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4); 

    return num/den; 

} 

  

// Returns y-value of point of intersectipn of 

// two lines 

float y_intersect(float x1, float y1, float x2, float y2, 

                float x3, float y3, float x4, float y4) 

{ 

    float num = (x1*y2 - y1*x2) * (y3-y4) - 

              (y1-y2) * (x3*y4 - y3*x4); 

    float den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4); 

    return num/den; 

} 

  

// This functions clips all the edges w.r.t one clip 

// edge of clipping area 

void clip(int id, float x1, float y1, float x2, float y2) 

{ 

	point_t* new_points = NULL;



	new_points = (point_t*)malloc(100*sizeof(point_t));



	int poly_size = poligon_array[id].point_array[0].point_num;

	int new_poly_size = 0;

  

    // (ix,iy),(kx,ky) are the co-ordinate values of 

    // the points 

    for (int i = 0; i < poly_size; i++) 

    { 



    	



        // i and k form a line in polygon 

        int k = (i+1) % poly_size; 

        float ix = poligon_array[id].point_array[i+1].x, iy = poligon_array[id].point_array[i+1].y; 

        float kx = poligon_array[id].point_array[k+1].x, ky = poligon_array[id].point_array[k+1].y; 

  

        // Calculating position of first point 

        // w.r.t. clipper line 

        float i_pos = (x2-x1) * (iy-y1) - (y2-y1) * (ix-x1); 

  

        // Calculating position of second point 

        // w.r.t. clipper line 

        float k_pos = (x2-x1) * (ky-y1) - (y2-y1) * (kx-x1); 

  

        // Case 1 : When both points are inside 

        if (i_pos < 0  && k_pos < 0) 

        { 

        	lll = 0;

            //Only second point is added 

            new_points[new_poly_size+1].x = kx; 

            new_points[new_poly_size+1].y = ky;

            new_points[new_poly_size+1].state = 0; 

            new_poly_size++; 

        } 

  

        // Case 2: When only first point is outside 

        else if (i_pos >= 0  && k_pos < 0) 

        { 

        	if(lll){

        		printf("@@@@@@\n");

        	}

        	lll = 0;

            // Point of intersection with edge 

            // and the second point is added 

            new_points[new_poly_size+1].x = x_intersect(x1, 

                              y1, x2, y2, ix, iy, kx, ky); 

            new_points[new_poly_size+1].y = y_intersect(x1, 

                              y1, x2, y2, ix, iy, kx, ky); 

            new_points[new_poly_size+1].state = 0; 

            new_poly_size++; 

  

            new_points[new_poly_size+1].x = kx; 

            new_points[new_poly_size+1].y = ky;

            new_points[new_poly_size+1].state = 0;  

            new_poly_size++; 

        } 

  

        // Case 3: When only second point is outside 

        else if (i_pos < 0  && k_pos >= 0) 

        { 

        	lll = 1;

            //Only point of intersection with edge is added 

            new_points[new_poly_size+1].x = x_intersect(x1, 

                              y1, x2, y2, ix, iy, kx, ky); 

            new_points[new_poly_size+1].y = y_intersect(x1, 

                              y1, x2, y2, ix, iy, kx, ky); 

            new_points[new_poly_size+1].state = 0; 

            new_poly_size++; 

        } 

  

        // Case 4: When both points are outside 

        else

        { 

        	lll = 0;

            //No points are added 

        } 

    } 

    // Copying new points into original array 

    // and changing the no. of vertices 

    new_points[0].point_num = new_poly_size;

    udate_point_array(id,new_points);

} 

  

// Implements Sutherland–Hodgman algorithm 

void suthHodgClip(int id, float ax, float ay, float bx, float by, float cx, float cy, float dx, float dy) 

{ 



	float clipper_points[][2] = {{ax,ay}, {bx,by}, 

                                 {cx,cy}, {dx,dy} }; 

    //i and k are two consecutive indexes 

    for (int i=0; i<4; i++) 

    { 

        int k = (i+1) % 4; 

  

        // We pass the current array of vertices, it's size 

        // and the end points of the selected clipper line 

        clip(id, clipper_points[i][0], clipper_points[i][1], clipper_points[k][0], clipper_points[k][1]); 

    } 

} 





void start_clipping(point_t wMin, point_t wMax){



	int i;

	int poligon_num = poligon_array[0].poligon_num;



	printf("poligon_num = %d\n", poligon_num);









	for(i=1; i<=poligon_num; i++){





		if(poligon_array[i].poligon_exists ){



			int point_num = poligon_array[i].point_array[0].point_num;

			int new_poly_size = 0;



			suthHodgClip(i, wMin.x, wMin.y, wMin.x, wMax.y, wMax.x, wMax.y, wMax.x, wMin.y); 



			if(poligon_array[i].point_array[0].point_num == 0){

				poligon_array[i].poligon_exists = 0;

			}

		}

		//check_for_intersection(i);



		printf("point num == %d\n", poligon_array[i].point_array[0].point_num);

	}

}

///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////

//H mouse 

void mouse( int button, int state, int x, int y )

{





    //me to deksi pliktro an sxediazame poligono to stamatame

    if( button == GLUT_RIGHT_BUTTON  && state == GLUT_UP)

    {

    	if(new_poligon){

    		new_poligon_off();

    	}

    	

    }



   //me to meseo den kanoume tipota

    if( button == GLUT_MIDDLE_BUTTON && state == GLUT_UP )

    {

       

    }



    //otan sikosoume to aristero pliktro oloklirounoume to orthogonio apokopis kai kaloume tin antistoixh synarthsh

    if( button == GLUT_LEFT_BUTTON && state == GLUT_UP ){







    	int WIDTH = glutGet(GLUT_WINDOW_WIDTH)/2;

		int HEIGHT = glutGet(GLUT_WINDOW_HEIGHT)/2;



		float p_x = (float)(x - WIDTH)/WIDTH;

		float p_y = -((float)(y - HEIGHT)/HEIGHT);



    	if(new_clipping == 2){



    		wmax.x = p_x;

    		wmax.y = p_y;



    		draw_clipper_points = 0;



    		if((wmax.x > wmin.x && wmax.y > wmin.y) || (wmax.x < wmin.x && wmax.y < wmin.y)){

    			start_clipping(wmin, wmax);

    		}

    		

    		new_clipping = 0;

    		motion_f = 0;



    		createPopupMenus();

    	}

    }



    //me to aristero pliktro an exei patithei apo to menu gia new poligono ksekina tin diadikasia tou neou poligonou

    //an exei patithei apo to menou gia apokopi kseninaei i diadikadia tis apokopis

    //kai stis dio periptoseis kanoume detach to deksi pliktro apo to menu kai otan teliosoume ksanakanoume create to menu

    if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )

    {

    	int WIDTH = glutGet(GLUT_WINDOW_WIDTH)/2;

		int HEIGHT = glutGet(GLUT_WINDOW_HEIGHT)/2;



		float p_x = (float)(x - WIDTH)/WIDTH;

		float p_y = -((float)(y - HEIGHT)/HEIGHT);



    	if(new_poligon){



			glutDetachMenu(GLUT_RIGHT_BUTTON);



		    add_point(poligon_array[0].poligon_id, p_x, p_y);

		    if(final_line_intersection()){

		    	delete_poligon();

		    }

    	}else if(new_clipping){



    		glutDetachMenu(GLUT_RIGHT_BUTTON);



    		draw_clipper_points = 1;



    		if(new_clipping == 1){

    			new_clipping ++;

    			wmin.x = p_x;

    			wmin.y = p_y;

	    	}

    	}

	}

    glutPostRedisplay();

}



///////////////////////////////////////////////////////////////////

//tin motion tin xrisimopioume mono otan kanoume apokopi gia na emfanisoume to parallhlogrammo to opoio tha apokopsei

void motion(int x,int y){



	if(new_clipping){

		if(draw_clipper_points){



			int WIDTH = glutGet(GLUT_WINDOW_WIDTH)/2;

			int HEIGHT = glutGet(GLUT_WINDOW_HEIGHT)/2;



			motion_x = (float)(x - WIDTH)/WIDTH;

			motion_y = -((float)(y - HEIGHT)/HEIGHT);



			motion_f = 1;

		}

	}

	glutPostRedisplay();

}



///////////////////////////////////////////////////////////////////

//me to pliktro 'esc' klinei to parathiro mas

//kai me to 't' ksekinaei tin apokipi

void keyboard(unsigned char key, int x, int y) {

	switch (key) {

	case 27:     // ESC key

		exit(0);

		break;

	case 'T':

	case 't':

		show_triangles = !show_triangles;

		break;

   }

}



////////////////////////////////////////////////////////////////////////

//me to F1 kanoume fullscreen 

void specialKeys(int key, int x, int y) {

   switch (key) {

      case GLUT_KEY_F1:    // F1: Toggle between full-screen and windowed mode

         fullScreenMode = !fullScreenMode;         // Toggle state

         if (fullScreenMode) {                     // Full-screen mode

            windowPosX   = glutGet(GLUT_WINDOW_X); // Save parameters for restoring later

            windowPosY   = glutGet(GLUT_WINDOW_Y);

            windowWidth  = glutGet(GLUT_WINDOW_WIDTH);

            windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

            glutFullScreen();                      // Switch into full screen

         } else {                                         // Windowed mode

            glutReshapeWindow(windowWidth, windowHeight); // Switch into windowed mode

            glutPositionWindow(windowPosX, windowPosX);   // Position top-left corner

         }

   }

}



////////////////////////////////////////////////////////////////////////

//afti ektelite apo tin display otan theloume na emfanizete to parallilogrammo apokopis 

//vasika afti einai pou to zografizei

void print_clipper_squer(){



	if((motion_x > wmin.x && motion_y > wmin.y) || (motion_x < wmin.x && motion_y < wmin.y)){

    	glColor3f(0.0f,1.0f,0.0f);

    }else{

    	glColor3f(1.0f,0.0f,0.0f);

    }

    glLineWidth(2);

    glBegin(GL_LINE_LOOP);

		glVertex2f(wmin.x, wmin.y);

		glVertex2f(wmin.x, motion_y);

		glVertex2f(motion_x, motion_y);

		glVertex2f(motion_x, wmin.y);

	glEnd();

	glFlush();

}



////////////////////////////////////////////////////////////////////////

//kathe fora pou theloume na emfanizete ena shmeio kaloume tin point me tis sintetagmenes tou shmeiou

void point(float x, float y){



	glColor3f(0.0f,0.0f,0.0f);

	glPointSize(5.0f);//set point size to 10 pixels

    glBegin(GL_POINTS); //starts drawing of points

      glVertex2f(x,y);

    glEnd();//end drawing of points



    //glFlush();  // Render now

}



////////////////////////////////////////////////////////////////////////

//kathe fora pou theloume na emfanizete ena efthigramo tmima kaloume tin line me tis sintetagmenes kai to xroma tou theloume na exei(rgb)

void line(float x1, float y1, float x2, float y2, float r, float g, float b){



	glColor3f(r, g, b);

	glLineWidth(3);

	glBegin(GL_LINES);

		glVertex2f(x1, y1);

		glVertex2f(x2, y2);

	glEnd();

}



////////////////////////////////////////////////////////////////////////

//sximatizei to perigrama enos poligonou (id) alla xwris tin teleftea akmh

//diladi tin kaloume kata tin diarkeia dimiourgias enos poligounou

void print_poligon_line(int id){



	if(poligon_array[id].poligon_exists){

		int i;

		int point_num = poligon_array[id].point_array[0].point_num;

		if(point_num > 1){

			for(i=2; i<=point_num; i++){

				float x1 = poligon_array[id].point_array[i-1].x;

				float y1 = poligon_array[id].point_array[i-1].y;

				float x2 = poligon_array[id].point_array[i].x;

				float y2 = poligon_array[id].point_array[i].y;

				float r  = poligon_array[id].r_l;

				float g  = poligon_array[id].g_l;

				float b  = poligon_array[id].b_l;

				line(x1, y1, x2, y2, r, g, b);

			}

		}

	}

}





////////////////////////////////////////////////////////////////////////

//edw sximatizoume olo to perigramma enos poligonou (id)

void print_line(int id){



	if(poligon_array[id].poligon_exists){



		int i;

		int point_num = poligon_array[id].point_array[0].point_num;

		if(point_num > 1){

			for(i=2; i<=point_num; i++){

				float x1 = poligon_array[id].point_array[i-1].x;

				float y1 = poligon_array[id].point_array[i-1].y;

				float x2 = poligon_array[id].point_array[i].x;

				float y2 = poligon_array[id].point_array[i].y;

				float r  = poligon_array[id].r_l;

				float g  = poligon_array[id].g_l;

				float b  = poligon_array[id].b_l;

				line(x1, y1, x2, y2, r, g, b);

			}

			float x1 = poligon_array[id].point_array[1].x;

			float y1 = poligon_array[id].point_array[1].y;

			float x2 = poligon_array[id].point_array[point_num].x;

			float y2 = poligon_array[id].point_array[point_num].y;

			float r  = poligon_array[id].r_l;

			float g  = poligon_array[id].g_l;

			float b  = poligon_array[id].b_l;

			line(x1, y1, x2, y2, r, g, b);

		}

	}



}



////////////////////////////////////////////////////////////////////////

//edo zografizoume oles tis korifes enos poligonou (id)

void print_point(int id){



	if(poligon_array[id].poligon_exists){



		int i;

		for(i=1; i<=poligon_array[id].point_array[0].point_num; i++){

			///////

			/*if((i == 1)||(i == poligon_array[id].point_array[0].point_num)){

				float x = poligon_array[id].point_array[i].x;

				float y = poligon_array[id].point_array[i].y;

				point(x, y);

			}*/

			/////

			float x = poligon_array[id].point_array[i].x;

			float y = poligon_array[id].point_array[i].y;

			point(x, y);

		}

	}

}



////////////////////////////////////////////////////////////////////////

//edo zografizoume to perigrama enos trigonou me prasino xroma 

//diladi tin kaloume otan emfanizoume tin trigonopoiisi

void triangulation(float x1, float y1, float x2, float y2, float x3, float y3 ) {



	glColor3f(0.0, 1.0, 0.0);



	glBegin(GL_LINE_LOOP);

		glVertex2f(x1, y1);

		glVertex2f(x2, y2);

		glVertex2f(x3, y3);

	glEnd();

}



////////////////////////////////////////////////////////////////////////

//edo ipologizoume ta trigona pou prokiptoun apo tin trigonopioiisi

//i parametros re_triagl pernei times 0 - 1 

//an parei (1) paei na pei pos iparxoun ta trigona kai emeis ta ksana ipoloogizoume (afto ginete meta tin apokopi) 

void triangulation_poligons(int id, int re_triangl) {



	if(poligon_array[id].poligon_exists){



		Vector2dVector a;

		Vector2dVector result;



		int i;

		int point_num = poligon_array[id].point_array[0].point_num;



		for(i=1; i<=point_num; i++){

			float x = poligon_array[id].point_array[i].x;

			float y = poligon_array[id].point_array[i].y;

			a.push_back( Vector2d(x,y));

		}



		Triangulate::Process(a,result);



		int tcount = result.size()/3;



		if(re_triangl){

			free(poligon_array[id].triangle_array);

			poligon_array[id].triangle_array = (triangle_t*)malloc((tcount+1)*sizeof(triangle_t));

			poligon_array[id].triangle_array[0].triangle_num = tcount;

		}else{

			poligon_array[id].triangle_array = (triangle_t*)malloc((tcount+1)*sizeof(triangle_t));

			poligon_array[id].triangle_array[0].triangle_num = tcount;

		}



		for (i=0; i<tcount; i++){

		    const Vector2d &p1 = result[i*3+0];

		    const Vector2d &p2 = result[i*3+1];

		    const Vector2d &p3 = result[i*3+2];

		    poligon_array[id].triangle_array[i+1].x1 = p1.GetX();

		    poligon_array[id].triangle_array[i+1].y1 = p1.GetY();

		    poligon_array[id].triangle_array[i+1].x2 = p2.GetX();

		    poligon_array[id].triangle_array[i+1].y2 = p2.GetY();

			poligon_array[id].triangle_array[i+1].x3 = p3.GetX();

			poligon_array[id].triangle_array[i+1].y3 = p3.GetY();

	  	}

	}

}



////////////////////////////////////////////////////////////////////////

//edo emfanizoume ola ta trigona pou exoun prokipsei apo tin trigonopoiisi tou poligonou me to id pou dinete

void show_triangulation_poligons(int id) {



	if(poligon_array[id].poligon_exists){



		int i;

		int triangle_num = poligon_array[id].triangle_array[0].triangle_num;



		for (i=1; i<=triangle_num; i++){

			float x1 = poligon_array[id].triangle_array[i].x1;

		    float y1 = poligon_array[id].triangle_array[i].y1;

		    float x2 = poligon_array[id].triangle_array[i].x2;

		    float y2 = poligon_array[id].triangle_array[i].y2;

			float x3 = poligon_array[id].triangle_array[i].x3;

			float y3 = poligon_array[id].triangle_array[i].y3;

			triangulation(x1, y1, x2, y2, x3, y3);	

		}

	}

}



////////////////////////////////////////////////////////////////////////

//me aftin emfanizoume ola ta trigona pou prokiptoun apo tin trigonopoiisi apo ola ta poligona

void final_triangulation_poligons(){



	int i;

	int poligon_num = poligon_array[0].poligon_num;

	for(i=1; i<=poligon_num; i++){

		show_triangulation_poligons(i);

	}

	

}



///////////////////////////////////////////////////////////////////////////

//edo gemizoume me xroma ena poligono me id aftou pou pername san orisma xrisimipiontas ta trigona

void fill_poligon(int id) {



	if(poligon_array[id].poligon_exists){



		int i;

		int triangle_num = poligon_array[id].triangle_array[0].triangle_num;



		float r  = poligon_array[id].r_f;

		float g  = poligon_array[id].g_f;

		float b  = poligon_array[id].b_f;

		glColor3f(r, g, b);



		for (i=1; i<=triangle_num; i++){

			float x1 = poligon_array[id].triangle_array[i].x1;

		    float y1 = poligon_array[id].triangle_array[i].y1;

		    float x2 = poligon_array[id].triangle_array[i].x2;

		    float y2 = poligon_array[id].triangle_array[i].y2;

			float x3 = poligon_array[id].triangle_array[i].x3;

			float y3 = poligon_array[id].triangle_array[i].y3;

			glBegin(GL_POLYGON);

				glVertex2f(x1, y1);

				glVertex2f(x2, y2);

				glVertex2f(x3, y3);

			glEnd();

		}

	}

}



///////////////////////////////////////////////////////////////////////////

//edo gemizoume me xroma ola ta poligona

void final_fill_poligons(){



	int i;

	int poligon_num = poligon_array[0].poligon_num;

	for(i=1; i<=poligon_num; i++){

		fill_poligon(i);

	}



}



///////////////////////////////////////////////////////////////////////////

//xrisimopiite gia na mas enimeronei gia tin katastasi tou menou

void processMenuStatus(int status, int x, int y) {



	if (status == GLUT_MENU_IN_USE)

		menuFlag = 1;

	else

		menuFlag = 0;

}



///////////////////////////////////////////////////////////////////////////

//edo leme ti ginete ean patithei to ACTION  apo to menou 

//me to EXIT termatizei to programa

//me to POLYGON enimeromoume mia global metavliti oti eimaste se leitourgia dimiourgias poligounou kai prosthetoume ena poligono adio ston pinaka mas

//me to CLIPPING enimeromoume mia glogal metavliti oti eimaste se leitourgia apokopis

void processACTIONMenu(int option) {



	switch (option) {



	case Exit_option: 

		exit(0); break;

	case POLYGON_option: 

		new_poligon = 1;

		add_poligon(red_f, green_f, blue_f, red_l, green_l, blue_l); break;

	case CLIPPING_option: 

		new_clipping = 1; break;

	}

}



///////////////////////////////////////////////////////////////////////////

//edo emfanizoume ta option gia to line colore kai enimeronoume tis antistixes metavlites

void processLINE_COLORMenu(int option) {



	switch (option) {

	case BLACK 			: red_l = 0.0f;  green_l = 0.0f;   blue_l = 0.0f;  break;

	case WHITE 			: red_l = 1.0f;  green_l = 1.0f;   blue_l = 1.0f;  break;

	case RED 			: red_l = 1.0f;  green_l = 0.0f;   blue_l = 0.0f;  break;

	case GREEN 			: red_l = 0.0f;  green_l = 1.0f;   blue_l = 0.0f;  break;

	case BLUE 			: red_l = 0.0f;  green_l = 0.0f;   blue_l = 1.0f;  break;

	case ORANGE 		: red_l = 1.0f;  green_l = 0.5f;   blue_l = 0.5f;  break;

	case PINK 			: red_l = 1.0f;  green_l = 0.0f;   blue_l = 1.0f;  break;		

	case DARK_GRAY 		: red_l = 0.25f; green_l = 0.25f;  blue_l = 0.25f; break;		

	case LIGHT_GRAY 	: red_l = 0.75f; green_l = 0.75f;  blue_l = 0.75f; break;

	case BROWN 			: red_l = 0.60f; green_l = 0.40f;  blue_l = 0.12f; break;

	case BARNEY_PURPLE  : red_l = 0.60f; green_l = 0.40f;  blue_l = 0.70f; break;

	case PASTEL_PINK 	: red_l = 0.98f; green_l = 0.04f;  blue_l = 0.7f;  break;

	case PUMPKIN_ORANGE : red_l = 0.98f; green_l = 0.625f; blue_l = 0.12f; break;

	case GOLD 			: red_l = 1.0f;  green_l = 0.70f;  blue_l = 0.0f;  break;

	case LIME 			: red_l = 0.2f;  green_l = 1.0f;  blue_l = 0.0f;  break;

	case AQUA 	  		: red_l = 0.0f;  green_l = 1.0f;   blue_l = 1.0;   break;

	}

}



///////////////////////////////////////////////////////////////////////////

//edo emfanizoume ta option gia to fill color kai enimeronoume tis antistixes metavlites

void processFILL_COLORMenu(int option) {



	switch (option) {

	case BLACK 			: red_f = 0.0f;  green_f = 0.0f;   blue_f = 0.0f;  break;

	case WHITE 			: red_f = 1.0f;  green_f = 1.0f;   blue_f = 1.0f;  break;

	case RED 			: red_f = 1.0f;  green_f = 0.0f;   blue_f = 0.0f;  break;

	case GREEN 			: red_f = 0.0f;  green_f = 1.0f;   blue_f = 0.0f;  break;

	case BLUE 			: red_f = 0.0f;  green_f = 0.0f;   blue_f = 1.0f;  break;

	case ORANGE 		: red_f = 1.0f;  green_f = 0.5f;   blue_f = 0.5f;  break;

	case PINK 			: red_f = 1.0f;  green_f = 0.0f;   blue_f = 1.0f;  break;		

	case DARK_GRAY 		: red_f = 0.25f; green_f = 0.25f;  blue_f = 0.25f; break;		

	case LIGHT_GRAY 	: red_f = 0.75f; green_f = 0.75f;  blue_f = 0.75f; break;

	case BROWN 			: red_f = 0.60f; green_f = 0.40f;  blue_f = 0.12f; break;

	case BARNEY_PURPLE  : red_f = 0.60f; green_f = 0.40f;  blue_f = 0.70f; break;

	case PASTEL_PINK 	: red_f = 0.98f; green_f = 0.04f;  blue_f = 0.7f;  break;

	case PUMPKIN_ORANGE : red_f = 0.98f; green_f = 0.625f; blue_f = 0.12f; break;

	case GOLD 			: red_f = 1.0f;  green_f = 0.70f;  blue_f = 0.0f;  break;

	case LIME 			: red_f = 0.2f;  green_f = 1.0f;   blue_f = 0.0f;  break;

	case AQUA    		: red_f = 0.0f;  green_f = 1.0f;   blue_f = 1.0;   break;

	}

}



///////////////////////////////////////////////////////////////////////////

//edo den exoume na kanoume kati giati sto main menu exoume mono anadyomena menu

void processMainMenu(int option) {



}



///////////////////////////////////////////////////////////////////////////

//edo kanoume create to menu mas kai kanoume attach to deksi pliktro

void createPopupMenus() {



	LINE_COLOR_menu = glutCreateMenu(processLINE_COLORMenu);



	glutAddMenuEntry("Black", BLACK);

	glutAddMenuEntry("White", WHITE);

	glutAddMenuEntry("Red", RED);

	glutAddMenuEntry("Green", GREEN);

	glutAddMenuEntry("Blue", BLUE);

	glutAddMenuEntry("Orange", ORANGE);

	glutAddMenuEntry("Pink", PINK);

	glutAddMenuEntry("Dark_Gray", DARK_GRAY);

	glutAddMenuEntry("Light_Gray", LIGHT_GRAY);

	glutAddMenuEntry("Brown", BROWN);

	glutAddMenuEntry("Barney_Purple", BARNEY_PURPLE);

	glutAddMenuEntry("Pastel_Pink", PASTEL_PINK);

	glutAddMenuEntry("Pumpkin_Orange", PUMPKIN_ORANGE);

	glutAddMenuEntry("Gold", GOLD);

	glutAddMenuEntry("Lime", LIME);

	glutAddMenuEntry("Aqua", AQUA);

	

	FILL_COLOR_menu = glutCreateMenu(processFILL_COLORMenu);



	glutAddMenuEntry("Black", BLACK);

	glutAddMenuEntry("White", WHITE);

	glutAddMenuEntry("Red", RED);

	glutAddMenuEntry("Green", GREEN);

	glutAddMenuEntry("Blue", BLUE);

	glutAddMenuEntry("Orange", ORANGE);

	glutAddMenuEntry("Pink", PINK);

	glutAddMenuEntry("Dark_Gray", DARK_GRAY);

	glutAddMenuEntry("Light_Gray", LIGHT_GRAY);

	glutAddMenuEntry("Brown", BROWN);

	glutAddMenuEntry("Barney_Purple", BARNEY_PURPLE);

	glutAddMenuEntry("Pastel_Pink", PASTEL_PINK);

	glutAddMenuEntry("Pumpkin_Orange", PUMPKIN_ORANGE);

	glutAddMenuEntry("Gold", GOLD);

	glutAddMenuEntry("Lime", LIME);

	glutAddMenuEntry("Aqua", AQUA);

	

	ACTION_menu = glutCreateMenu(processACTIONMenu);



	glutAddMenuEntry("POLYGON", POLYGON_option);

	glutAddMenuEntry("CLIPPING", CLIPPING_option);

	glutAddMenuEntry("Exit", Exit_option);



	mainMenu = glutCreateMenu(processMainMenu);



	glutAddSubMenu("ACTION", ACTION_menu);

	glutAddSubMenu("LINE_COLOR", LINE_COLOR_menu);

	glutAddSubMenu("FILL_COLOR", FILL_COLOR_menu);





	// attach the menu to the right button

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	

	// this will allow us to know if the menu is active

	glutMenuStatusFunc(processMenuStatus);

}



///////////////////////////////////////////////////////////////////////////

//H display einai ypefthini gia to ti tha emfanizete kai ti exei sto parathiro mas

void display() 

{ 

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );



  	int i,j;



  	if (show_triangles == 0){



	  	for(i=1; i<=poligon_array[0].poligon_num;i++){

	  		if(!new_poligon){

		  		fill_poligon(i);

		  		print_line(i);

		  		print_point(i);

			}else{

	  			if(poligon_array[i].poligon_id == poligon_array[0].poligon_id){

					print_point(i);

					print_poligon_line(i);

				}else{

					fill_poligon(i);

		  			print_line(i);

				}

	  		}	

	  	}

  	}else{

  		final_fill_poligons();

  		final_triangulation_poligons();

  		for(i=1; i<=poligon_array[0].poligon_num;i++){

  			print_point(i);

  		}

  	}



  	if(motion_f){

  		print_clipper_squer();

  	}



    glutSwapBuffers();

}



void reshape( int w, int h){

	glViewport(0,0,w,h);

}



void initOpenGL(){

	glClearColor(1.0, 1.0, 1.0, 1.0);

}



/* Main function: GLUT runs as a console application starting at main()  */

int main(int argc, char** argv) {

   glutInit(&argc, argv);



   create_poligon_array();



   glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL );



   glutInitWindowSize(600, 500);

                  // Initialize GLUT

   glutCreateWindow("PoLygoNoYo!!!!"); // Create a window with the given title

     // Set the window's initial width & height

   initOpenGL();



   createPopupMenus();



   glutMouseFunc( mouse );

   glutMotionFunc( motion );



   glutSpecialFunc(specialKeys); // Register callback handler for special-key event

   glutKeyboardFunc(keyboard);   // Register callback handler for special-key event



   glutDisplayFunc(display); // Register display callback handler for window re-paint

   glutIdleFunc(display);

   glutReshapeFunc( reshape );

   glutMainLoop();           // Enter the event-processing loop

   return 0;

}





///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////

//kai apo edo kai kato eina sinartiseis oi opies eina ipefthines gia tin trigonopoihsh

float Triangulate::Area(const Vector2dVector &contour)

{



  int n = contour.size();



  float A=0.0f;



  for(int p=n-1,q=0; q<n; p=q++)

  {

    A+= contour[p].GetX()*contour[q].GetY() - contour[q].GetX()*contour[p].GetY();

  }

  return A*0.5f;

}



   /*

     InsideTriangle decides if a point P is Inside of the triangle

     defined by A, B, C.

   */

bool Triangulate::InsideTriangle(float Ax, float Ay,

                      float Bx, float By,

                      float Cx, float Cy,

                      float Px, float Py)



{

  float ax, ay, bx, by, cx, cy, apx, apy, bpx, bpy, cpx, cpy;

  float cCROSSap, bCROSScp, aCROSSbp;



  ax = Cx - Bx;  ay = Cy - By;

  bx = Ax - Cx;  by = Ay - Cy;

  cx = Bx - Ax;  cy = By - Ay;

  apx= Px - Ax;  apy= Py - Ay;

  bpx= Px - Bx;  bpy= Py - By;

  cpx= Px - Cx;  cpy= Py - Cy;



  aCROSSbp = ax*bpy - ay*bpx;

  cCROSSap = cx*apy - cy*apx;

  bCROSScp = bx*cpy - by*cpx;



  return ((aCROSSbp >= 0.0f) && (bCROSScp >= 0.0f) && (cCROSSap >= 0.0f));

};



bool Triangulate::Snip(const Vector2dVector &contour,int u,int v,int w,int n,int *V)

{

  int p;

  float Ax, Ay, Bx, By, Cx, Cy, Px, Py;



  Ax = contour[V[u]].GetX();

  Ay = contour[V[u]].GetY();



  Bx = contour[V[v]].GetX();

  By = contour[V[v]].GetY();



  Cx = contour[V[w]].GetX();

  Cy = contour[V[w]].GetY();



  if ( EPSILON > (((Bx-Ax)*(Cy-Ay)) - ((By-Ay)*(Cx-Ax))) ) return false;



  for (p=0;p<n;p++)

  {

    if( (p == u) || (p == v) || (p == w) ) continue;

    Px = contour[V[p]].GetX();

    Py = contour[V[p]].GetY();

    if (InsideTriangle(Ax,Ay,Bx,By,Cx,Cy,Px,Py)) return false;

  }



  return true;

}



bool Triangulate::Process(const Vector2dVector &contour,Vector2dVector &result)

{

  /* allocate and initialize list of Vertices in polygon */



  int n = contour.size();

  if ( n < 3 ) return false;



  int *V = new int[n];



  /* we want a counter-clockwise polygon in V */



  if ( 0.0f < Area(contour) )

    for (int v=0; v<n; v++) V[v] = v;

  else

    for(int v=0; v<n; v++) V[v] = (n-1)-v;



  int nv = n;



  /*  remove nv-2 Vertices, creating 1 triangle every time */

  int count = 2*nv;   /* error detection */



  for(int m=0, v=nv-1; nv>2; )

  {

    /* if we loop, it is probably a non-simple polygon */

    if (0 >= (count--))

    {

      //** Triangulate: ERROR - probable bad polygon!

      return false;

    }



    /* three consecutive vertices in current polygon, <u,v,w> */

    int u = v  ; if (nv <= u) u = 0;     /* previous */

    v = u+1; if (nv <= v) v = 0;     /* new v    */

    int w = v+1; if (nv <= w) w = 0;     /* next     */



    if ( Snip(contour,u,v,w,nv,V) )

    {

      int a,b,c,s,t;



      /* true names of the vertices */

      a = V[u]; b = V[v]; c = V[w];



      /* output Triangle */

      result.push_back( contour[a] );

      result.push_back( contour[b] );

      result.push_back( contour[c] );



      m++;



      /* remove v from remaining polygon */

      for(s=v,t=v+1;t<nv;s++,t++) V[s] = V[t]; nv--;



      /* resest error detection counter */

      count = 2*nv;

    }

  }



  delete V;



  return true;

}





