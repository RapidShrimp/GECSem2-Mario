#include "Collisions.h"
#include "Character.h"

Collisions* Collisions::m_instance = nullptr;

Collisions::~Collisions()
{
	m_instance = nullptr;
}

Collisions* Collisions::Instance()
{
	return nullptr;
}

Collisions::Collisions()
{
}
