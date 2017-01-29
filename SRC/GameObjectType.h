/*
This class gives a unqiue key to each object depending on its name. This makes it easier to 
work out collisions between objects. This class also makes it easier to compare different game entities.

Author : Chris Child

Reference : Chris Child, 2nd Year Asteroids Project 
*/
#ifndef __GAMEOBJECTTYPE__H__
#define __GAMEOBJECTTYPE__H__

class GameObjectType
{
public:
	/* Constructor */
	explicit GameObjectType(char const * const pTypeName)
		: mTypeName(pTypeName), mTypeID(HashName(pTypeName))
	{}

	/* Get Methods */
	unsigned long GetTypeID() const { return mTypeID; }
	char const * const GetTypeName() const { return mTypeName; }

	/* Overloading methods */
	bool operator< (GameObjectType const & o) const { return (GetTypeID() < o.GetTypeID()); }
	bool operator== (GameObjectType const & o) const { return (GetTypeID() == o.GetTypeID()); }
	bool operator!= (GameObjectType const & o) const { return (GetTypeID() != o.GetTypeID()); }

	/* Give a hash key to each name */
	static unsigned long HashName(char const * const pTypeName);

private:
	unsigned long mTypeID;			// The Entity ID
	char const * mTypeName;			// The Entity name
};

#endif