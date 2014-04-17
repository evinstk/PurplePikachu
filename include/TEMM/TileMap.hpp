#ifndef TEMM_TILEMAP_HPP
#define TEMM_TILEMAP_HPP

namespace temm
{

	class TileMap
	{
	public:
		enum Tile
		{
			Grass = 17,

			GrassRidgeLeftTop = 6,
			GrassRidgeLeft = 11,
			GrassRidgeLeftBottom = 16,

			GrassRidgeRightTop = 10,
			GrassRidgeRight = 15,
			GrassRidgeRightBottom = 20,

			GrassRidgeBottomLeft = 22,
			GrassRidgeBottom = 23,
			GrassRidgeBottomRight = 24,

			GrassCornerBottomLeft = 21,
			GrassCornerBottomRight = 25,

			GrassCornerTopLeft = 1,
			GrassCornerTopRight = 5,

			TypeCount = 14,
		};
	};

}

#endif