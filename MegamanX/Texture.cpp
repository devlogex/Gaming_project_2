#include "Texture.h"



Texture::Texture(const char * filepath, D3DCOLOR transColor)
{
	Init(filepath, transColor);
}

void Texture::Init(const char * filepath, D3DCOLOR transColor)
{
	direction = Right;
	HRESULT result;
	D3DXIMAGE_INFO info;
	result = D3DXGetImageInfoFromFile(filepath, &info);
	Width = info.Width;
	Height = info.Height;
	if (result != D3D_OK)
	{
		MessageBox(WINDOW->getHandleWindow(), "Không the khoi tao TEXTURE", "Loi", MB_ICONERROR);
		PostQuitMessage(0);
	}

	result = D3DXCreateTextureFromFileEx(
		GRAPHICS->GetDevice(),
		filepath,
		info.Width,
		info.Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transColor,
		&info,
		NULL,
		&texture);

	if (result != D3D_OK)
	{
		MessageBox(WINDOW->getHandleWindow(), "Không the khoi tao TEXTURE", "Loi", MB_ICONERROR);
		PostQuitMessage(0);
	}
}

void Texture::RenderTexture(int x, int y, RECT * r)
{
	GRAPHICS->GetSprite()->Draw(
		texture,
		r,
		0,
		&D3DXVECTOR3((float)x, (float)y, 0),
		D3DCOLOR_XRGB(255, 255, 255)
	);
}

Texture::Texture()
{
}

Texture::~Texture()
{
}
