// simply call CheckBegin and Flip alternately to run the game;
//Check returns false if the user is trying to quit

typedef unsigned long RGBA;
bool CheckBegin(RGBA clearcolor=0);
void Flip(); // flips the screen, frame locked to 60 hz
void GameMain(); // you write this :)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// input
bool IsKeyDown(int key); // use windows VK_ codes for special keys, eg VK_LEFT; use capital chars for letter keys eg 'A', '0'. use VK_LBUTTON and VK_RBUTTON for mouse buttons. 
void ResetKeys();

