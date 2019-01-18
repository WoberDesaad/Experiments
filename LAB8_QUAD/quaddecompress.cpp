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

void print_quad(struct quad_node* node);
void build_tree(struct quad_node* node, ifstream* in);
void get_colors(struct quad_node* node, Image* I, int width);

#define NE 0
#define NW 1
#define SW 2
#define SE 3


struct quad_node {
	int x_start, y_start;
	int width, height;
	char color[4];
	struct quad_node* children[4];
	bool leaf;
};

int main(int argc, char *argv[]){		
	//Get file name from command line
	if(argc != 2){
		cout << "You need to enter a file name to decompress\n";
		return -1;
	}
	string file = argv[1];
	
	ifstream in(file);
	
	int width, height;
	
	in.read((char*)&width, sizeof(width));
	in.read((char*)&height, sizeof(height));
	
	//cout << "Width: " << width << ", Height: " << height << "\n";
	 
	Image* I = new Image(width, height, 0);
		
	struct quad_node tree_root;
	tree_root.x_start = 0;
	tree_root.y_start = 0;
	tree_root.width = width;
	tree_root.height = height;
	tree_root.color[0] = 0;
	tree_root.color[1] = 0;
	tree_root.color[2] = 0;
	tree_root.color[3] = 0;
	tree_root.children[NW] = NULL;
	tree_root.children[NE] = NULL;
	tree_root.children[SW] = NULL;
	tree_root.children[SE] = NULL;
	
	build_tree(&tree_root, &in);
	
	//print_quad(&tree_root);
	
	get_colors(&tree_root, I, width);
	
	
	
	I->write("out.png");
	
	return 0;
}

void get_colors(struct quad_node* node, Image* I, int width){
	if(!node->leaf){
		//cout << "Branch\n";
		get_colors(node->children[NW], I, width);
		get_colors(node->children[NE], I, width);
		get_colors(node->children[SW], I, width);
		get_colors(node->children[SE], I, width);
	}
	else
	{
		//cout << "LEAF\n";
		for(int y = node->y_start; y < node->y_start+node->height; y++){
			for(int x = node->x_start; x < node->x_start+node->width; x++){
				I->data[y*width*4+x*4] = node->color[0];
				I->data[y*width*4+x*4+1] = node->color[1];
				I->data[y*width*4+x*4+2] = node->color[2];
				I->data[y*width*4+x*4+3] = node->color[3];
			}
		}
	}
}

void build_tree(struct quad_node* node, ifstream* in){
	char d;
	if(in->eof()){
		return;
	}
	in->read((char*)&d, sizeof(d));
	//cout << (int)d; 
	if(d == 0){
		//branch
		//call build tree and for all children
		//cout << node->width << " " << node->height << "\n";
		node->leaf = false;
		
		node->children[NE] = new struct quad_node;
		node->children[NW] = new struct quad_node;
		node->children[SW] = new struct quad_node;
		node->children[SE] = new struct quad_node;	
		
		int w1 = node->width/2;
		int w2 = node->width - w1;
		int h1 = node->height/2;
		int h2 = node->height-h1;
		
		//cout << "\nw1: " << node->x_start+w1 << "\n";
		
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
		
		
		//NW
		build_tree(node->children[NW], in);
		//NE
		build_tree(node->children[NE], in);
		//SW
		build_tree(node->children[SW], in);
		//SE
		build_tree(node->children[SE], in);
	}else if(d == 1){
		//leaf
		in->read(node->color, 4);
		//cout << " " << (int)node->color[0] << " " << (int)node->color[1] << " "  << (int)node->color[2] << " "  << (int)node->color[3] << "\n";
		node->leaf = true;
		//cout << "Width: " << node->width << ", Height: " << node->height << ", X: " << node->x_start << ", Y: " << node->y_start << "\n";
	}else{
		//cout << "ERROR!\n";
		in->close();
		return;
	}
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