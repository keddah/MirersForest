#include "Controllers.h"

Input::Input(SDL_Scancode button)
{
	primaryKey = button;
}

Input::Input(SDL_Scancode button1, SDL_Scancode button2)
{
	primaryKey = button1;
	secondaryKey = button2;

}

SDL_Scancode Input::GetPrimaryKey() const
{
	return primaryKey;
}

SDL_Scancode Input::GetSecondaryKey() const
{
	return secondaryKey;
}
