
#define MAX_NO_TEXTURES 3

#define CUBE_TEXTURE 0
#define FCUBE_TEXTURE 1
#define MCUBE_TEXTURE 2

GLuint texture_id[MAX_NO_TEXTURES];

float xrot;
float yrot;
float xspeed;			// X Rotation Speed
float yspeed;			// Y Rotation Speed

float ratio;
float	z=-5.0f;			// Depth Into The Screen

GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]=	{ 0.0f, 0.0f, 2.0f, 1.0f };

GLuint	filter;				// Which Filter To Use
bool	light;				// Lighting ON/OFF
bool 	blend;				// Blending OFF/ON? ( NEW )
bool	lp;					// L Pressed?
bool	fp;					// F Pressed?
bool	bp;					// B Pressed? ( NEW )

void LoadGLTextures (void)
{
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
   glGenTextures (3, texture_id);

   image_t   temp_image;

   glBindTexture ( GL_TEXTURE_2D, texture_id [0] );
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
   tgaLoad  ( "glass.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY );

   glBindTexture ( GL_TEXTURE_2D, texture_id [1] );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   tgaLoad  ( "glass.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY );

   glBindTexture ( GL_TEXTURE_2D, texture_id [2] );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
   tgaLoad  ( "glass.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY );
}
