/* this is the game's starting point */
/* currently doesnt do anyting other than test move and the sound */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "universe.h"
#include "sound.h"

/* TODO:
 * Change position to a matrix
 * Implement mouse use */
int main() {
	/* window variables */
	Display* display;
	int screen;
	unsigned long background;
	XSetWindowAttributes attributes;
	Window window;
	/* event variables */
	XEvent event;
	Bool inFocous = True;
	/* binary representation of the keys */
	char keysReturned[32];
	/* position variables */
	struct Position position = { 0x10000000, 0x10000000, 0x10000000 };
	struct Direction direction = { 0x0, 0x0, 0x0 };
	struct Velocity velocity = { 0x0, 0x0, 0x0 };
	/* time variables */
	struct timespec time1;
	struct timespec time2;
	int32_t i = 0;

	/* open the display */
	display = XOpenDisplay(NULL);
	if(!display){
		fprintf(stderr, "Failed to open display\n");
		return 1;
	}
	else{
		printf("Opened display\n");
	}
	/* get the default screen of the display */
	screen = DefaultScreen(display);
	/* make the window black */
	background = BlackPixel(display, screen);
	/* set the background color to that black */
	attributes.background_pixel = background;
	/* notify us when the window structure changes, or we recieve input from the keyboard or mouse */
	attributes.event_mask = StructureNotifyMask | 
		KeyPressMask | KeyReleaseMask | 
		ButtonPressMask | PointerMotionMask |
		FocusChangeMask;
	/* create the window */
	window = XCreateWindow(display, RootWindow(display, screen), 
			0, 0, 500, 500, 0, CopyFromParent, InputOutput, CopyFromParent, 
			CWBackPixel | CWEventMask, &attributes);
	/* make the window go on screen */
	XMapWindow(display,window);

	/* check for when the window actually displays */
	do{
		XNextEvent(display, &event);
	}while(event.type != MapNotify);
	printf("window opened\n");

	/* test keyboard input */
	/* XGrabKeyboard(display, window, False, GrabModeAsync, GrabModeAsync, CurrentTime); */
	XGrabPointer(display, window, False, ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask | PointerMotionMask 
			, GrabModeAsync, GrabModeAsync, window, None, CurrentTime);
	for(int i = 0; i<32; i++){
		keysReturned[i] = 0;
	}
	/* get the keyboard input and change the position with it */
	printf("position before : \nx = %llX\ny = %llX\nz = %llX\n", position.x, position.y,position.z);
	clock_gettime(CLOCK_REALTIME, &time1);
	do{	
		if(XCheckTypedEvent(display, FocusOut, &event)){
			XUngrabPointer(display, CurrentTime);
			inFocous = False;
		}
		else if(XCheckTypedEvent(display, FocusIn, &event)){
			XGrabPointer(display, window, False, ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask | PointerMotionMask 
					, GrabModeAsync, GrabModeAsync, window, None, CurrentTime);
			inFocous = True;
		}
		clock_gettime(CLOCK_REALTIME, &time2);
		if( ((time2.tv_nsec - time1.tv_nsec) >= 16666667 || (time2.tv_nsec - time1.tv_nsec) < 0) ){
			/* printf("elapsed time : %lld\n", time2.tv_nsec - time1.tv_nsec); */
			time1 = time2;
			/* printf("pending: %d\n", XEventsQueued(display,QueuedAfterReading)); */
			XQueryKeymap(display, keysReturned);
			/* printf("keys pressed: ");
			for(int i = 0; i<32; i++){
				printf("%d=%02hhx ",i,keysReturned[i]);
			}
			printf("\n"); */

			drag(&velocity, 100);
			if(keysReturned[3] & 0x02){
				velocity.x += 0x1000;
			}
			if(keysReturned[4] & 0x80){
				velocity.x -= 0x1000;
			}
			if(keysReturned[5] & 0x01){
				velocity.y += 0x1000;
			}
			if(keysReturned[4] & 0x40){
				velocity.y -= 0x1000;
			}
			if(keysReturned[8] & 0x02){
				velocity.z += 0x1000;
			}
			if(keysReturned[6] & 0x04){
				velocity.z -= 0x1000;
			}
			printf("position : \nx = %llX\ny = %llX\nz = %llX\n", position.x, position.y,position.z);
			move(&position, &velocity);
			if(inFocous){
				XWarpPointer(display, window, window, 0, 0, 500, 500, 250, 250);
			}
			XSync(display, True);
		}
	}while(!(keysReturned[1] & 0x02));
	XUngrabKeyboard(display, CurrentTime);
	XUngrabPointer(display, CurrentTime);
	/* mouse input  */ 
	do{
		XNextEvent(display, &event);
	}while(event.type != ButtonPress);
	printf("mouse pressed\n");
	do{
		XNextEvent(display, &event);
	}while(event.type != MotionNotify);
	printf("mouse moved\n");

	printf("position after  : \nx = %llX\ny = %llX\nz = %llX\n", position.x, position.y,position.z);

	/* test the sound */
	sound_test();

	printf("All tests over. Ending program.\n");

	XDestroyWindow(display,window);
	XCloseDisplay(display);
	return 0;
}
