//Robert Appelmann
//Optimization Techniques

//#include <mmintrin.h>	//mmx
//#include <xmmintrin.h>	//sse
//#include <emmintrin.h>	//sse2
//#include <pmmintrin.h>	//sse3
//#include <tmmintrin.h>	//ssse3
//#include <smmintrin.h>	//sse4.1
//#include <nmmintrin.h>	//sse4.2
//#include <immintrin.h>	//avx, avx2

#include <iostream>
#include "pngops.h"	//JIMS PNG IMAGE OPERATIONS
#include <chrono>	//Timing
#include <cstdlib>
#include <cmath>
#include <deque>
#include <math.h>
#include <fstream>

using namespace std;

#define NE 0
#define NW 1
#define SW 2
#define SE 3


int all_the_same_in_node(struct quad_node* node, int compression_level, Image* I, char* color);
void print_quad(struct quad_node* node);
void write_file(struct quad_node* node, ofstream * outFile);

struct quad_node {
	int x_start, y_start;
	int width, height;
	char color[4];
	struct quad_node* children[4];
	bool leaf;
};

int main(int argc, char *argv[]){		
	//Get file name from command line
	if(argc != 3){
		cout << "You need to enter a file name and a compression level (1-100)" << "\n";
		return -1;
	}
	string file = argv[1];
	int compression_level = atoi(argv[2]);	
	
	Image* I = new Image(file);
	struct quad_node* root = new struct quad_node;
	root->x_start = 0;
	root->y_start = 0;
	root->width = I->w;
	root->height = I->h;
	root->children[0] = NULL;
	root->children[1] = NULL;
	root->children[2] = NULL;
	root->children[3] = NULL;
	root->leaf = true;
	
	//cout << "Width: " << I->w << " Height: " << I->h << "\n"; 
	
	
	//make queue of all nodes
	deque<struct quad_node*> nodes_to_check;
	nodes_to_check.push_back(root);
	
	struct quad_node* node;
	
	//for each node in queue, if not all the same, break node into smaller nodes and add as the children of the node
	while(nodes_to_check.size() > 0)
	{
		node = nodes_to_check.front();
		nodes_to_check.pop_front();
		//cout << "x: " << node->x_start << " y: " << node->y_start << " w: " << node->width << " h: " << node->height << "\n";
		int return_val = all_the_same_in_node(node, compression_level, I, node->color);
		//cout << "All the same: " << return_val << "\n";
		if(return_val == -1)
		{
			node->leaf = false;
			
			node->children[NE] = new struct quad_node;
			node->children[NW] = new struct quad_node;
			node->children[SW] = new struct quad_node;
			node->children[SE] = new struct quad_node;	
			
			int w1 = node->width/2;
			int w2 = node->width - w1;
			int h1 = node->height/2;
			int h2 = node->height-h1;
			
			node->children[NW]->x_start = node->x_start;
			node->children[NW]->y_start = node->y_start;
			node->children[NW]->width = w1;
			node->children[NW]->height = h1;
			node->children[NW]->children[0] = NULL;
			node->children[NW]->children[1] = NULL;
			node->children[NW]->children[2] = NULL;
			node->children[NW]->children[3] = NULL;
			node->children[NW]->leaf = true;
			
			node->children[NE]->x_start = node->x_start + w1;
			node->children[NE]->y_start = node->y_start;
			node->children[NE]->width = w2;
			node->children[NE]->height = h1;
			node->children[NE]->children[0] = NULL;
			node->children[NE]->children[1] = NULL;
			node->children[NE]->children[2] = NULL;
			node->children[NE]->children[3] = NULL;
			node->children[NE]->leaf = true;
			
			node->children[SE]->x_start = node->x_start + w1;
			node->children[SE]->y_start = node->y_start + h1;
			node->children[SE]->width = w2;
			node->children[SE]->height = h2;
			node->children[SE]->children[0] = NULL;
			node->children[SE]->children[1] = NULL;
			node->children[SE]->children[2] = NULL;
			node->children[SE]->children[3] = NULL;
			node->children[SE]->leaf = true;
			
			node->children[SW]->x_start = node->x_start;
			node->children[SW]->y_start = node->y_start + h1;
			node->children[SW]->width = w1;
			node->children[SW]->height = h2;
			node->children[SW]->children[0] = NULL;
			node->children[SW]->children[1] = NULL;
			node->children[SW]->children[2] = NULL;
			node->children[SW]->children[3] = NULL;
			node->children[SW]->leaf = true;
			
			nodes_to_check.push_back(node->children[NE]);
			nodes_to_check.push_back(node->children[NW]);
			nodes_to_check.push_back(node->children[SE]);
			nodes_to_check.push_back(node->children[SW]);
		}
	}
	
	//once queue empty, output quadtree to file
	
	//cout << "\n\n";
	
	//print_quad(root);
	
	string newFile = argv[1];
	newFile += ".z";
	
	ofstream outFile;
	outFile.open(newFile);
	
	outFile.write((char*)&I->w, sizeof(I->w));
	outFile.write((char*)&I->h, sizeof(I->h));
	
	write_file(root, &outFile);
	
	outFile.close();
	
	return 0;
}

void write_file(struct quad_node* node, ofstream * outFile){
	if(node->leaf){
		char c = 1;
		outFile->write(&c, 1);
		//cout << (int)c << " " << (int)node->color[0] << " " << (int)node->color[1] << " "  << (int)node->color[2] << " "  << (int)node->color[3] << "\n";
		
		(*outFile) << node->color[0];
		(*outFile) << node->color[1];
		(*outFile) << node->color[2];
		(*outFile) << node->color[3];
	}
	else
	{
		char c = 0;
		outFile->write(&c, 1);
		//cout << (int)c << "\n"; 
		write_file(node->children[NW], outFile);
		write_file(node->children[NE], outFile);
		write_file(node->children[SW], outFile);
		write_file(node->children[SE], outFile);
	
	}
}

float color_distance(float r1, float g1, float b1, float a1, float r2, float g2, float b2, float a2 )
{
	
	return sqrt((r2-r1)*(r2-r1)+(g2-g1)*(g2-g1)+(b2-b1)*(b2-b1)+(a2-a1)*(a2-a1));
}

int all_the_same_in_node(struct quad_node* node, int compression_level, Image* I, char* color)
{	
	float total_r = 0, total_g = 0, total_b = 0, total_a = 0;
	int count = 0;
	
	for(int y = node->y_start; y < (node->y_start + node->height); y++)
	{
		for(int x = node->x_start; x < (node->x_start + node->width); x++)
		{
			float r2 = (float)I->data[x*4+y*I->w*4 + 0];
			float g2 = (float)I->data[x*4+y*I->w*4 + 1];
			float b2 = (float)I->data[x*4+y*I->w*4 + 2];
			float a2 = (float)I->data[x*4+y*I->w*4 + 3];
			
			total_r += r2;
			total_g += g2;
			total_b += b2;
			total_a += a2;
			count++;
			
		}
	}
	
	round(total_r /= count);
	round(total_g /= count);
	round(total_b /= count);
	round(total_a /= count);
	
	if(total_r > 255){
		total_r = 255;
	}
	if(total_r < 0){
		total_r = 0;
	}
	if(total_g > 255){
		total_g = 255;
	}
	if(total_g < 0){
		total_g = 0;
	}
	if(total_b > 255){
		total_b = 255;
	}
	if(total_b < 0){
		total_b = 0;
	}
	if(total_a > 255){
		total_a = 255;
	}
	if(total_a < 0){
		total_a = 0;
	}
	
	for(int y = node->y_start; y < (node->y_start + node->height); y++)
	{
		for(int x = node->x_start; x < (node->x_start + node->width); x++)
		{
			float r2 = (float)I->data[x*4+y*I->w*4 + 0];
			float g2 = (float)I->data[x*4+y*I->w*4 + 1];
			float b2 = (float)I->data[x*4+y*I->w*4 + 2];
			float a2 = (float)I->data[x*4+y*I->w*4 + 3];
			
			float distance = color_distance(total_r,total_g,total_b,total_a,r2,g2,b2,a2);
				
			if(distance > (2.05*compression_level))
				return -1;
			
		}
	}
	//cout << "All the Same!\n";
	
	color[0] = (char)total_r;
	color[1] = (char)total_g;
	color[2] = (char)total_b;
	color[3] = (char)total_a;
	
	return 0;
}

void print_quad(struct quad_node* node)
{
	if(node->leaf){
		cout << "x: " << node->x_start << " y: " << node->y_start << " w: " << node->width << " h: " << node->height << "  COLOR: 0x" << node->color[0] << node->color[1] << node->color[2] << node->color[3] << "\n";
	}
	else
	{
		print_quad(node->children[NW]);
		print_quad(node->children[NE]);
		print_quad(node->children[SW]);
		print_quad(node->children[SE]);
	
	}
}
