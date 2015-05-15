
#pragma once

#include <SDL.h>

#include <filestore/types.h>
#include <display/displayobject.h>
#include <display/state.h>


//internal use only
typedef struct {

	//The Display object in question
	DisplayObject* display;

	//These aren't in the respective DisplayObjects because
	//this Display acts as a layout manager for its children.
	//This rect gets communicated via SDL_Context->set_viewport()
	SDL_Rect rect;

} Child;


//the layout manager, and event distributor
class Display
{
	public:
		Display(Selection* init_selection);
		~Display();

		void render();
		void resize();
		void request_render(Uint32 component);

		void on_key(SDL_KeyboardEvent &e);
		void on_text(SDL_TextInputEvent &e);
		void on_wheel(SDL_MouseWheelEvent &e);
		void on_click(SDL_MouseButtonEvent &e);
		void on_motion(SDL_MouseMotionEvent &e);

		void on_selection(Selection* new_selection);
		void on_state_change();

	private:
		//shared state between the children (includes the current Selection*)
		//all children are given a pointer to this storage area
		State state;

		//the view currently under the mouse
		Child* current;

		Child cli;
		Child subtags;
		Child info;
		Child grid;
		Child thumbs;

		//the mouses current position
		SDL_MouseMotionEvent mouse;

		void render_child(Child& child);
		void resize_child(Child& child);
		void update_mouse();
		void send_selector();
};
