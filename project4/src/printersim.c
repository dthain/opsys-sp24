/*
This is a toy gcode interpreter used to simulate a 3D printer,
for the purposes of a scheduling problem in operating systems.

It only understands the following opcodes:

G00 X# Y# (reposition to x y quickly)
G01 X# Y# (linear draw to position x y)
G02 X# Y# I# J# (clockwise circular arc)
G03 X# Y# I# J# (counterclockwise circular arc)

It will draw these slowly using the gfx library.

To invoke it, just run:
./printersim circuit.gcode
*/

#include "gfx.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/* microseconds per pixel */
int speed = 200;

/* size of the screen*/
int xsize = 500;
int ysize = 500;

/* draw line in time proportional to length */

void slow_draw_line( double x1, double y1, double x2, double y2 )
{
	double length = sqrt(pow(x2-x1,2)+pow(y2-y1,2));

	double dx = (x2-x1)/length;
	double dy = (y2-y1)/length;
	double t;

	double lastx = x1;
	double lasty = y1;

	for(t=0;t<length;t+=1.0) {
		double x = x1 + dx*t;
		double y = y1 + dy*t;
		gfx_line(lastx,lasty,x,y);
		gfx_flush();
		lastx = x;
		lasty = y;
		usleep(speed);
	}

	gfx_line(lastx,lasty,x2,y2);
}

/* draw a clockwise arc */

void slow_draw_arc_cw( double cx, double cy, double radius, double start, double stop )
{
	double lastx = cx + radius * cos(start);
	double lasty = cy + radius * sin(start);
	double t;
	double step = (stop-start)/60;

	for(t=start+step;t<stop;t+=step) {
		double x = cx + radius * cos(t);
		double y = cy + radius * sin(t);
		slow_draw_line(lastx,lasty,x,y);
		lastx = x;
		lasty = y;
	}

}

/* draw a counter-clockwise arc */

void slow_draw_arc_ccw( double cx, double cy, double radius, double start, double stop )
{
	double lastx = cx + radius * cos(stop);
	double lasty = cy + radius * sin(stop);
	double t;
	double step = (stop-start)/60;

	for(t=stop-step;t>=start;t-=step) {
		double x = cx + radius * cos(t);
		double y = cy + radius * sin(t);
		slow_draw_line(lastx,lasty,x,y);
		lastx = x;
		lasty = y;
	}

}

/* read gcode commands line by line */

int parse_simple_gcode( FILE *file )
{
	double x,y,i,j;
	double xpos = 0;
	double ypos = 0;

	char line[1024];

	while(fgets(line,sizeof(line),file)) {
		if(sscanf(line,"G00 X%lf Y%lf",&x,&y)==2) {
			xpos = x;
			ypos = y;
		} else if(sscanf(line,"G01 X%lf Y%lf",&x,&y)==2) {
			slow_draw_line(xpos,ypos,x,y);
			xpos = x;
			ypos = y;
		} else if(sscanf(line,"G02 X%lf Y%lf I%lf J%lf",&x,&y,&i,&j)==4) {
			double radius = sqrt(pow(xpos-i,2)+pow(ypos-j,2));
			double end = atan2(ypos-j,xpos-i);
			double start = atan2(y-j,x-i);     
			while(end<start) end+=2*M_PI;
			slow_draw_arc_cw(i,j,radius,start,end);
			xpos = x;
			ypos = y;
		} else if(sscanf(line,"G03 X%lf Y%lf I%lf J%lf",&x,&y,&i,&j)==4) {
			double radius = sqrt(pow(xpos-i,2)+pow(ypos-j,2)); 
			double start = atan2(ypos-j,xpos-i);
			double end = atan2(y-j,x-i);     
			while(end<start) end+=2*M_PI;
			slow_draw_arc_ccw(i,j,radius,start,end);
			xpos = x;
			ypos = y;
		} else {
			fprintf(stderr,"unsupported code: %s\n",line);
			return 0;
		}
	}

	return 1;
}

int main( int argc, char *argv[] )
{
	if(argc!=2) {
		printf("use: %s <filename>\n",argv[0]);
		exit(1);
	}

	FILE *file = fopen(argv[1],"r");
	if(!file) {
		fprintf(stderr,"%s: couldn't open %s: %s\n",argv[0],argv[1],strerror(errno));
		return 0;
	}

	gfx_open(xsize,ysize,"GCode Simulator");
	gfx_color(100,100,255);

	parse_simple_gcode(file);

	sleep(5);

	return 0;
}

