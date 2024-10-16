#include "BiomSetter.h"
#include <iostream>
void BiomeSetter::Initialize()
{
	// Biome sollen sp�ter via Engine hinzugef�gt werden k�nnen.  

	// "Dessert"
	m_biomes.push_back(Biome(1, 0, 0, 0));
	// "Forest"
	m_biomes.push_back(Biome(2,0.05, 0.05, 0.05));
	// "Grassland"
	m_biomes.push_back(Biome(3, 0.2, 0.2, 0.2));
	// "Jungle"
	m_biomes.push_back(Biome(4, 0.3, 0.3, 0.3));
	// "Mountains"
	m_biomes.push_back(Biome(5,0.25, 0.25, 0.25));
	// "Ocean"
	m_biomes.push_back(Biome(6, 0.15, 0.15, 0.15));
	// "Tundra"
	m_biomes.push_back(Biome(7, 0.3, 0.3, 0.3));
}


int BiomeSetter::GetBiome(std::vector<float> properties)
{
	std::vector<Biome> possibleBiomes;
	for (auto& i_biome : m_biomes)
	{
		if (i_biome.MatchConditions(properties))
		{
			possibleBiomes.push_back(i_biome);
		}
	}

	Biome biomeToReturn(possibleBiomes[0]);
	float curVal = biomeToReturn.GetDiffVal(properties);

	for (auto &i_biome : possibleBiomes)
	{
		if (i_biome.GetDiffVal(properties))
		{
			biomeToReturn = i_biome; 
			curVal = biomeToReturn.GetDiffVal(properties);
		} 
	}
	return biomeToReturn.GetID();
}
