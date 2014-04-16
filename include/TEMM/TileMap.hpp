#ifndef TEMM_TILEMAP_HPP
#define TEMM_TILEMAP_HPP

namespace temm
{

	class TileMap
	{
	public:
		enum Type
		{
			Grass,

			GrassRidgeLeftTop,
			GrassRidgeLeft,
			GrassRidgeLeftBottom,

			GrassRidgeRightTop,
			GrassRidgeRight,
			GrassRidgeRightBottom,

			GrassRidgeBottomLeft,
			GrassRidgeBottom,
			GrassRidgeBottomRight,

			GrassCornerBottomLeft,
			GrassCornerBottomRight,

			TypeCount,
		};
	};

}

#endif